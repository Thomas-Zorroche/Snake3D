#include "Game.h"
#include "Snake.h"

#include <cstdlib>  // for rand(), srand()
#include <ctime>    // for time()

// Spawn random target cubes on the map
Cube* Game::SpawnTarget(const Snake& snake)
{
    srand(time(0));
    int x, y = 0;
    bool OnTheSnake = false;
    do
    {
        OnTheSnake = false;
        x = (rand() % (2 * NB_BLOCS_WIDTH)) * (TAILLE_BLOC / 2);
        y = (rand() % (2 * NB_BLOCS_WIDTH)) * (TAILLE_BLOC / 2);
        for (size_t i = 0; i < snake.getCubes().size(); i++)
        {
            if (x == snake.getCubes()[i].getX() && y == snake.getCubes()[i].getY())
                OnTheSnake = true;
        }
    } while (OnTheSnake || (x % TAILLE_BLOC == 0 || y % TAILLE_BLOC == 0));

    return new Cube(x, y);
}