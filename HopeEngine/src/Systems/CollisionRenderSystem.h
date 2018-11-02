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
#include "../Components/BoxColliderComponent.h"

class BoxCollisionRenderSystem : public System<BoxCollisionRenderSystem>
{
	Shader shader;
	GLuint quadVAO;
public:
	explicit BoxCollisionRenderSystem(Shader &_shader) : shader(_shader) {
		initRenderData();
	}

	void initRenderData()
	{
		// Configure VAO/VBO
		GLuint VBO;
		GLfloat vertices[] = {
			// Pos
			0.0f, 1.0f,
			1.0f, 0.0f,
			0.0f, 0.0f,

			0.0f, 1.0f,
			1.0f, 1.0f, 
			1.0f, 0.0f
		};

		glGenVertexArrays(1, &this->quadVAO);
		glGenBuffers(1, &VBO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindVertexArray(this->quadVAO);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void update(EntityManager &entities, EventManager &events, TimeDelta dt) override
	{
		this->shader.Use();
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		entities.each<BoxColliderComponent>([&](Entity entity, BoxColliderComponent &boxCollider)
		{
			//std::cout << "rendering wireframe " << boxCollider.topLeft.x << ", " << boxCollider.topLeft.y << ", " << boxCollider.bottomRight.x << ", " << boxCollider.bottomRight.y << std::endl;
			vec2 size = boxCollider.bottomRight - boxCollider.topLeft;
			//std::cout << "size " << size.x << ", " << size.y << std::endl;
			// Prepare transformations
			mat4 model(1.0f);
			model = glm::translate(model, vec3(boxCollider.topLeft, 0.0f));
			model = glm::scale(model, vec3(size, 1.0f));

			this->shader.SetMatrix4("model", model);

			// wire color
			this->shader.SetVector3f("wireColor", vec3(1.0f, 0.0f, 0.0f));

			glBindVertexArray(this->quadVAO);
			glDrawArrays(GL_TRIANGLES, 0, 6);
			glBindVertexArray(0);
		});
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
};