#include "Renderer.h"

#include "Game.h"


Renderer::Renderer()
{
	proj = glm::perspective(glm::radians(25.0f), width / height, 0.1f, 100.0f);
	view = glm::translate(glm::mat4(1.0f), glm::vec3(-0.5f, -0.5f, -3.0f));
	view = glm::rotate(view, glm::radians(-30.0f), glm::vec3(1.0f, 0.0f, 0.0f));
}

void Renderer::DrawElements(const VertexArray& va, const IndexBuffer& ib, Shader& shader, glm::vec3 translation, const glm::vec3& color, const glm::vec3& scaleValue) const
{
	// Transformations
	glm::mat4 model = glm::translate(glm::mat4(1.0f), translation);
	model = glm::scale(model, scaleValue);
	glm::mat4 mvp = proj * view * model;

	// Shaders & Uniforms
	shader.Bind();
	shader.SetUniform3f("u_color", color.r, color.g, color.b);
	shader.SetUniformMat4("mvp", mvp);

	va.Bind();
	ib.Bind();
	glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, 0);
}

void Renderer::DrawArrays(const VertexArray& va, Shader& shader, glm::vec3 translation, const glm::vec3& color, const glm::vec3& scaleValue) const
{
	// Transformations
	glm::mat4 model = glm::translate(glm::mat4(1.0f), translation);
	model = glm::scale(model, scaleValue);
	glm::mat4 mvp = proj * view * model;

	// Shaders & Uniforms
	shader.Bind();
	shader.SetUniform3f("u_color", color.r, color.g, color.b);
	shader.SetUniformMat4("mvp", mvp);

	va.Bind();
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Renderer::Clear(float r, float g, float b, float a) const
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT);
}
