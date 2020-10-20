#pragma once

#include <glad/glad.h>
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

#include <iostream>

// OpenGL Maths Library
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

static void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

static void GLCheckError()
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error] : " << error << std::endl;
	}
}

class Renderer
{
private:
	glm::mat4 proj;
	glm::mat4 view;
public:
	Renderer();
	void DrawElements(const VertexArray& va, const IndexBuffer& ib, Shader& shader, glm::vec3 translation, const glm::vec3& color, const glm::vec3& scaleValue) const;
	void DrawArrays(const VertexArray& va, Shader& shader, glm::vec3 position, const glm::vec3& translation, const glm::vec3& scaleValue) const;
	void Clear(float r = 0.1f, float g = 0.1f, float b = 0.15f, float a = 1.0f) const;

	// Getters
	inline glm::mat4 getProj() const { return proj; }
	inline glm::mat4 getView() const { return view; }
};