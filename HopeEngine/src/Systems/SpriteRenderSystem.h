#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include <entityx/entityx.h>
using namespace entityx;

// Resources
#include "../Renderer/Shader.h"
#include "../Renderer/Texture.h"

// Components
#include "../Components/SpriteComponent.h"
#include "../Components/PositionComponent.h"

class SpriteRenderSystem : public System<SpriteRenderSystem>
{
	Shader shader;
	GLuint quadVAO;
public:
	explicit SpriteRenderSystem(Shader &_shader) : shader(_shader) {
		initRenderData();
	}

	void initRenderData()
	{
		// Configure VAO/VBO
		GLuint VBO;
		GLfloat vertices[] = {
			// Pos      // Tex
			0.0f, 1.0f, 0.0f, 1.0f,
			1.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 0.0f,

			0.0f, 1.0f, 0.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f,
			1.0f, 0.0f, 1.0f, 0.0f
		};

		glGenVertexArrays(1, &this->quadVAO);
		glGenBuffers(1, &VBO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindVertexArray(this->quadVAO);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void update(EntityManager &entities, EventManager &events, TimeDelta dt) override
	{
		this->shader.Use();
		entities.each<SpriteComponent, PositionComponent>([&](Entity entity, SpriteComponent &sprite, PositionComponent &position)
		{
			//std::cout << "rendering sprite " << sprite.texture.ID << " - " << position.position.x << ", " << position.position.y << std::endl;
			// Prepare transformations
			mat4 model(1.0f);
			model = glm::translate(model, vec3(position.position, 0.0f));  // First translate (transformations are: scale happens first, then rotation and then finall translation happens; reversed order)

			model = glm::translate(model, vec3(0.5f * sprite.size.x, 0.5f * sprite.size.y, 0.0f)); // Move origin of rotation to center of quad
			model = glm::rotate(model, sprite.rotation, vec3(0.0f, 0.0f, 1.0f)); // Then rotate
			model = glm::translate(model, vec3(-0.5f * sprite.size.x, -0.5f * sprite.size.y, 0.0f)); // Move origin back

			model = glm::scale(model, vec3(sprite.size, 1.0f)); // Last scale

			this->shader.SetMatrix4("model", model);

			// Render textured quad
			this->shader.SetVector3f("spriteColor", sprite.color);

			glActiveTexture(GL_TEXTURE0);
			sprite.texture.Bind();

			glBindVertexArray(this->quadVAO);
			glDrawArrays(GL_TRIANGLES, 0, 6);
			glBindVertexArray(0);
		});
	}
};