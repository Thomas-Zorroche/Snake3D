#include "Cube.h"
#include "VertexBuffer.h"



void Cube::Print() const
{
	std::cout << "(" << X << "," << Y << ")" << std::endl;
}

void Cube::move(Direction direction, int speed)
{
	switch (direction)
	{
	case LEFT:
		X -= speed;
		break;
	case RIGHT:
		X += speed;
		break;
	case UP:
		Y += speed;
		break;
	case DOWN:
		Y -= speed;
		break;
	}
}

glm::vec3 Cube::getPosition() const
{
	float xf = (float)(X / factorConversionFloat);
	float yf = (float)(Y / factorConversionFloat);
	return glm::vec3(xf, yf, zDepth);
}

Direction Cube::DirectionBetweenCubes(const Cube& otherCube) const
{
	int deltaX = X - otherCube.getX();
	int deltaY = Y - otherCube.getY();

	// Alors les Cubes sont alignés verticalement
	if (deltaX == 0)
	{
		if (deltaY < 0)
			return UP;
		else
			return DOWN;
	}
	else if (deltaY == 0)
	{
		if (deltaX < 0)
			return RIGHT;
		else
			return LEFT;
	}
	else
	{
		return RIGHT;
	}
}

int Cube::IsCubeOutsideMap() const
{
	if (X == (TAILLE_BLOC * NB_BLOCS_WIDTH) + TAILLE_BLOC / 2)
		return RIGHT;

	if (X <= 0)
		return LEFT;

	if (Y == (TAILLE_BLOC * NB_BLOCS_WIDTH) + TAILLE_BLOC / 2)
		return UP;

	if (Y <= 0)
		return DOWN;

	return -1;
}

	/*VertexArray cubeVAO;
	VertexBuffer cubeVBO(Cube::Vertices, Cube::getSizeVertices());
	VertexBufferLayout cubeLayout;
	cubeLayout.Push<float>(3);
	cubeLayout.Push<float>(1);
	cubeVAO.AddBuffer(cubeVBO, cubeLayout);
	Shader cubeShader("res/shaders/cube.shader");*/

// Static Variables

const float Cube::Vertices[] = {
	// Coordinates        // 1.0f = Shadow
	-0.5f, -0.5f, -0.5f,  1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,
	-0.5f,  0.5f, -0.5f,  1.0f,
	-0.5f, -0.5f, -0.5f,  1.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,

	-0.5f,  0.5f,  0.5f,  0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f,
	-0.5f, -0.5f, -0.5f,  1.0f,
	-0.5f, -0.5f, -0.5f,  1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,

	 0.5f,  0.5f,  0.5f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,

	-0.5f, -0.5f, -0.5f,  1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,
	-0.5f, -0.5f, -0.5f,  1.0f,

	-0.5f,  0.5f, -0.5f,  1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f,
};

