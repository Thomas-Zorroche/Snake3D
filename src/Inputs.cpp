#include "Inputs.h"

#include "Snake.h"


// Inputs
void processInput(GLFWwindow* window, Snake& snake)
{
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        snake.setDirection(LEFT);
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        snake.setDirection(RIGHT);
    }
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        snake.setDirection(UP);
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        snake.setDirection(DOWN);
    }
}