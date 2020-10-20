#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "stb_image.h"

#include "Shader.h"
#include "Renderer.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"

#include "Cube.h"
#include "Game.h"
#include "Snake.h"
#include "Inputs.h"


int main(void)
{
    GLFWwindow* window;
    
    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(width, height, "Snake 3D", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Initialize glad: load all OpenGL function pointers */
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    
    glEnable(GL_DEPTH_TEST);

    Game game;

    Renderer renderer;

    // Colors
    const glm::vec3 colorTarget(0.0f, 1.0f, 0.0f);
    const glm::vec3 colorSnake(1.0f, 0.7f, 0.0f);
    const glm::vec3 colorGround(0.2f, 0.4f, 0.4f); 
    const glm::vec3 colorBackground(0.1f, 0.2f, 0.3f); 
    const glm::vec3 colorWall(0.2f, 0.4f, 0.4f); 

    // Scale Values
    float scaleValueBlock = TAILLE_BLOC / factorConversionFloat;
    const glm::vec3 scaleTarget(scaleValueBlock * 0.9, scaleValueBlock * 0.9, scaleValueBlock * 0.9);
    const glm::vec3 scaleSnake(scaleValueBlock, scaleValueBlock, scaleValueBlock);
    const glm::vec3 scaleWall(scaleValueBlock, scaleValueBlock, scaleValueBlock * 1.1);


    // Create all data for a cube
    VertexArray cubeVAO;
    VertexBuffer cubeVBO(Cube::Vertices, Cube::getSizeVertices());
    VertexBufferLayout cubeLayout;
    cubeLayout.Push<float>(3);
    cubeLayout.Push<float>(1);
    cubeVAO.AddBuffer(cubeVBO, cubeLayout);
    Shader cubeShader("res/shaders/cube.shader");
    
    // Create all data for the ground
    float groundVertices[] = {
        0.0f, 0.0f,     // 0 Bottom Left
        1.0f, 0.0f,     // 1 Bottom Right
        1.0f, 1.0f,     // 2 Top Right
        0.0f, 1.0f      // 3 Top Left
    };
    unsigned int groundIndices[] = {
        0, 1, 2,
        0, 2, 3
    };
    VertexArray groundVAO;
    VertexBuffer groundVBO(groundVertices, sizeof(groundVertices));
    VertexBufferLayout groundLayout;
    groundLayout.Push<float>(2);
    groundVAO.AddBuffer(groundVBO, groundLayout);
    IndexBuffer groundIBO(groundIndices, 6);
    groundVAO.Unbind();
    // Shader for the ground
    Shader groundShader("res/shaders/ground.shader");
    glm::mat4 modelGround = glm::mat4(1.0f);
    glm::mat4 mvpGround = renderer.getProj() * renderer.getView() * modelGround;
    groundShader.Bind();
    groundShader.SetUniform3f("u_color", colorGround.r, colorGround.g, colorGround.b);
    groundShader.SetUniformMat4("mvp", mvpGround);

    Snake snake;

    // First Target Cube spawn on the map
    Cube* targetCube = game.SpawnTarget(snake);

        
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        // input
        processInput(window, snake);

        snake.move();

        // Si Head touche le targetCube
        if (snake[0].getX() == targetCube->getX() 
         && snake[0].getY() == targetCube->getY())
        {
            snake.hitCube();
            targetCube = game.SpawnTarget(snake);
        }

        /* Render here */
        glClearColor(colorBackground.r, colorBackground.g, colorBackground.b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Draw the ground
        renderer.DrawElements(groundVAO, groundIBO, groundShader, glm::vec3(0.0f), colorGround, glm::vec3(1.0f));

        // Draw Target
        renderer.DrawArrays(cubeVAO, cubeShader, targetCube->getPosition(), colorTarget, scaleTarget);

        // When Hitting Cube, draw the Last Static One Cube
        if (snake.getNewSpawnedCube() != nullptr)
        {
            Cube newSpawnedCube = *(snake.getNewSpawnedCube());
            renderer.DrawArrays(cubeVAO, cubeShader, newSpawnedCube.getPosition(), colorSnake, scaleSnake);
        }       

        // Draw Snake
        for (size_t i = 0; i < snake.getLength(); i++)
            renderer.DrawArrays(cubeVAO, cubeShader, snake[i].getPosition(), colorSnake, scaleSnake);

        // Draw Block Cubes Side Map
        Cube BlockSideWest(-TAILLE_BLOC / 2, -TAILLE_BLOC / 2 - TAILLE_BLOC);
        Cube BlockSideEast((NB_BLOCS_WIDTH * TAILLE_BLOC) + TAILLE_BLOC / 2, -TAILLE_BLOC / 2 - TAILLE_BLOC);
        Cube BlockSideNorth(-TAILLE_BLOC / 2 - TAILLE_BLOC, (NB_BLOCS_WIDTH * TAILLE_BLOC) + TAILLE_BLOC / 2);
        Cube BlockSideSouth(-TAILLE_BLOC / 2 - TAILLE_BLOC, -TAILLE_BLOC / 2);
        for (size_t i = 0; i < NB_BLOCS_WIDTH + 2; i++)
        {
            BlockSideWest.setY(BlockSideWest.getY() + TAILLE_BLOC);
            renderer.DrawArrays(cubeVAO, cubeShader, BlockSideWest.getPosition(), colorWall, scaleWall);

            BlockSideEast.setY(BlockSideEast.getY() + TAILLE_BLOC);
            renderer.DrawArrays(cubeVAO, cubeShader, BlockSideEast.getPosition(), colorWall, scaleWall);

            BlockSideNorth.setX(BlockSideNorth.getX() + TAILLE_BLOC);
            renderer.DrawArrays(cubeVAO, cubeShader, BlockSideNorth.getPosition(), colorWall, scaleWall);

            BlockSideSouth.setX(BlockSideSouth.getX() + TAILLE_BLOC);
            renderer.DrawArrays(cubeVAO, cubeShader, BlockSideSouth.getPosition(), colorWall, scaleWall);
        }
        

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }


    glfwTerminate();
    return 0;
}


