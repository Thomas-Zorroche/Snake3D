#pragma once

#include <iostream>

#include "glm/glm.hpp"

#include "Game.h"

enum Direction
{
	LEFT = 0, RIGHT, UP, DOWN
};


class Cube
{
private:
	int X, Y;
	
public:
    const static float Vertices[];

	// Constructors
	Cube() : X(TAILLE_BLOC / 2), Y(TAILLE_BLOC / 2) {}
	Cube(int x, int y) : X(x), Y(y) {}

	// Getters
	inline int getX() const { return X; }
	inline int getY() const { return Y; }
	static int getSizeVertices() { return 6 * 36 * sizeof(float); }

	// Setters
	inline void setX(int x) { X = x; }
	inline void setY(int y) { Y = y; }
	glm::vec3 getPosition() const;

	void Print() const;
	void move(Direction direction, int speed);

	Direction DirectionBetweenCubes(const Cube& otherCube) const;
	int IsCubeOutsideMap() const;
};



