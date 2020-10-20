#pragma once

#define TAILLE_BLOC 50
#define NB_BLOCS_WIDTH 1000 / TAILLE_BLOC

#define zDepth 0.05f
#define factorConversionFloat 1000.0f

const float width = 720.0f;
const float height = 720.0f;

class Snake;
class Cube;

class Game
{
public:
	Cube* SpawnTarget(const Snake& snake);

private:
};

