#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Game.h"
#include "Cube.h"

#include <vector>
#include <iostream>



class Snake
{
private:
	std::vector<Cube> arrayCube;
	Cube* Head;
	Cube* newSpawnedCube;
	int speed;
	int length;
	Direction direction;
	Direction dirSaved;				// Direction Taken by the player, saved when the cube will be in the center of a case
	Direction LastDirection;		// Direction of the Last Cube
	bool changeDir;
	bool isMoving;
	bool changeSide;

public:
	// Constructor & Destructor
	Snake();
	~Snake();

	// Getters
	inline std::vector<Cube> getCubes() const { return arrayCube; }
	inline Cube* getNewSpawnedCube() const { return newSpawnedCube; }
	inline int getLength() const { return length; }

	void move();
	void hitCube();
	void setDirection(Direction newDirection);

	// Read []
	Cube operator[](int index) const;
};


