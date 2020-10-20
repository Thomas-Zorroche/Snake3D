#include "Snake.h"

Snake::Snake()
	: direction(RIGHT), dirSaved(RIGHT), LastDirection(RIGHT), speed(10), length(2),
	changeDir(false), isMoving(false), changeSide(false)
{
	arrayCube.push_back(Cube(TAILLE_BLOC + TAILLE_BLOC / 2, TAILLE_BLOC / 2));
	arrayCube.push_back(Cube(TAILLE_BLOC / 2, TAILLE_BLOC / 2));
	Head = &arrayCube[0];
	newSpawnedCube = nullptr;
}


Snake::~Snake()
{
	delete(newSpawnedCube);
}


/*
-- On duplique Head
-- On bouge Head vers la direction du joueur
-- On bouge Last vers le Last - 1
-- On supprime last quand les deux mouvement sont terminés
*/
void Snake::move()
{
	// On change de direction si multiple de 50 ET non multiple de 100
	if (changeDir && Head->getX() % TAILLE_BLOC == TAILLE_BLOC / 2
		&& Head->getY() % TAILLE_BLOC == TAILLE_BLOC / 2)
	{
		changeDir = false;
		direction = dirSaved;
	}

	if (abs(Head->getX()) % TAILLE_BLOC == TAILLE_BLOC / 2
		&& abs(Head->getY()) % TAILLE_BLOC == TAILLE_BLOC / 2)
	{
		// A la fin de chaque mouvement, on supprimer le dernier cube
		if (isMoving) //  && newSpawnedCube == nullptr
		{
			// Delete last cube
			arrayCube.pop_back();
			length--;
			Head = &arrayCube[0];
		}

		// If Snake hits himself : EndGame
		for (size_t i = 1; i < length; i++)
		{
			if (Head->getX() == arrayCube[i].getX() && Head->getY() == arrayCube[i].getY())
			{
				arrayCube.erase(arrayCube.begin() + 2, arrayCube.end());
				length = 2;
				break;
			}
		}

		// Passer d'un côté à un autre de la map
		changeSide = false;
		switch (Head->IsCubeOutsideMap())
		{
		case RIGHT:
			Head->setX(-TAILLE_BLOC / 2);
			changeSide = true;
			break;
		case LEFT:
			Head->setX((TAILLE_BLOC * NB_BLOCS_WIDTH) + TAILLE_BLOC / 2);
			changeSide = true;
			break;
		case UP:
			Head->setY(-TAILLE_BLOC / 2);
			changeSide = true;
			break;
		case DOWN:
			Head->setY((TAILLE_BLOC * NB_BLOCS_WIDTH) + TAILLE_BLOC / 2);
			changeSide = true;
			break;
		case -1:
			break;
		}

		// Si le Serpent n'est pas totalement passé de l'autre côté
		if (length > 2 && !(arrayCube[length - 2].IsCubeOutsideMap() == -1))
			changeSide = true;

		// If a new Cube has spawned, we add it at the end
		if (newSpawnedCube != nullptr)
		{
			arrayCube.insert(arrayCube.end(), *newSpawnedCube);
			newSpawnedCube = nullptr;
			Head = &arrayCube[0];
			length++;
		}

		// On duplique la tête
		Cube secondCube = Cube(*Head);
		arrayCube.insert(arrayCube.begin() + 1, secondCube);
		length++;
		Head = &arrayCube[0];
	}

	// On bouge Head vers la direction du joueur et Last vers la direction trouvée
	Head->move(direction, speed);
	if (!changeSide)
		LastDirection = arrayCube[length - 1].DirectionBetweenCubes(arrayCube[length - 2]);
	arrayCube[length - 1].move(LastDirection, speed);
	isMoving = true;
}


void Snake::hitCube()
{
	// Duplication of the last cube
	newSpawnedCube = new Cube(arrayCube[length - 1]);
}


void Snake::setDirection(Direction newDirection)
{
	if (direction == LEFT && newDirection != RIGHT || direction == RIGHT && newDirection != LEFT
		|| direction == UP && newDirection != DOWN || direction == DOWN && newDirection != UP)
	{
		changeDir = true;
	}
	dirSaved = newDirection;
}

Cube Snake::operator[](int index) const
{
	if (index < 0 || index >= length)
		throw std::out_of_range("error Snake: index out of range");
	
	return arrayCube[index];
}
