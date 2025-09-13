#pragma once

#include <vector>
#include <array>
#include <tuple>
#include "../headerfiles/RendererClass.h"


class Game
{
public:

    Game();

    void Run()
    {
        Renderer renderer;
        while (!isGameOver() && !glfwWindowShouldClose(renderer.window))
        {
            handleInput(renderer.window);

            trySpawnApple();

            renderer.render(grid, snake);

            glfwSwapBuffers(renderer.window);
        }
    }
public:

    char input = 'd';
private:

    std::vector <std::tuple<int16_t, int16_t, char, int16_t>> snake;
    std::array <std::array <char, 10>, 10> grid;
    std::tuple<int16_t, int16_t> lastHeadPos;
    bool apple = 0;

    void trySpawnApple();

    bool isGameOver();

    bool isdead();

    void handleInput(GLFWwindow* window);

    void processInput(GLFWwindow* window);
};
