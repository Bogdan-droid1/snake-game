#include "../headerfiles/GameClass.h"
#include <iostream>
#include <random>
#include <chrono>

using namespace std::chrono_literals;
using std::get;

Game::Game()
{
    for (int16_t i = 0;i < 10;i++)
    {
        grid.at(i) = { '-', '-', '-', '-', '-', '-', '-', '-', '-', '-' };
    }
    snake.reserve(50);
    snake.push_back({ 0, 1, 'B', 0});
    snake.push_back({ 0, 0, 'O', 0});

    grid.at(0).at(0) = 'O';
    grid.at(0).at(1) = 'B';

    get<0>(lastHeadPos) = 0;
    get<1>(lastHeadPos) = 0;

    trySpawnApple();
}


void Game::trySpawnApple()
{
    if (apple)
        return;

    bool finished = 0;
    while (!finished)
    {
        std::random_device rd, rd2;
        std::uniform_int_distribution <int16_t> dist(0, 9);
        grid.at(dist(rd)).at(dist(rd2)) = 'A';
        finished = 1;
        for (int16_t i = 0;i < snake.size();i++)
        {
            if (grid.at(get<0>(snake.at(i))).at(get<1>(snake.at(i))) == 'A')
            {
                finished = 0;

                if (i == 0)
                    grid.at(get<0>(snake.at(i))).at(get<1>(snake.at(i))) = 'B';
                else
                    grid.at(get<0>(snake.at(i))).at(get<1>(snake.at(i))) = 'O';

                break;
            }
        }
    }
   apple = 1;
}


bool Game::isGameOver()
{
    if (isdead())
    {
        std::cout << "\n" << "YOU LOST! :(";
        return true;
    }
    else if (snake.size() == 99)
    {
        std::cout << "\n" << "YOU WON! :o";
        return true;
    }
    return false;
}


bool Game::isdead()
{
    auto snakeColideWall = [this]() {
        return (input == 'w' || input == 's' || input == 'd' || input == 'a')
            && get<0>(snake.at(0)) == get<0>(lastHeadPos) && get<1>(snake.at(0)) == get<1>(lastHeadPos);
        };

    if (snakeColideWall())
    {
        return true;
    }

    for (int16_t i = 1;i < snake.size();i++)
    {
        if (get<0>(snake.at(0)) == get<0>(snake.at(i)) && get<1>(snake.at(0)) == get<1>(snake.at(i)))
        {
            return true;
        }
    }
    return false;
}


void Game::handleInput(GLFWwindow* window)
{
    auto start = std::chrono::steady_clock::now();
    while (std::chrono::steady_clock::now() - start < 0.45s)
    {
        processInput(window);
        glfwPollEvents();
    }
    get<0>(lastHeadPos) = get<0>(snake.at(0));
    get<1>(lastHeadPos) = get<1>(snake.at(0));

    if (input == 'w' && get<0>(snake.at(0)) != 0)
    {
        if (grid.at(get<0>(snake.at(0)) - 1).at(get<1>(snake.at(0))) == 'A')
        {
            apple = 0;
            snake.push_back(snake.at(snake.size() - 1));
            for (int i = snake.size() - 2;i > 0;i--)
            {
                get<0>(snake.at(i)) = get<0>(snake.at(i - 1));
                get<1>(snake.at(i)) = get<1>(snake.at(i - 1));
                get<3>(snake.at(i)) = get<3>(snake.at(i - 1));
            }
        }
        else
        {
            for (int i = snake.size() - 1;i > 0;i--)
            {
                get<0>(snake.at(i)) = get<0>(snake.at(i - 1));
                get<1>(snake.at(i)) = get<1>(snake.at(i - 1));
                get<3>(snake.at(i)) = get<3>(snake.at(i - 1));
            }
        }
        get<0>(snake.at(0))--;
        get<3>(snake.at(0)) = 90;

        for (int i = 0;i < 10;i++)
        {
            for (int j = 0;j < 10;j++)
            {
                if (grid.at(i).at(j) == 'O' || grid.at(i).at(j) == 'B')
                    grid.at(i).at(j) = '-';
            }
        }

        for (int i = 0;i < snake.size();i++)
        {
            grid.at(get<0>(snake.at(i))).at(get<1>(snake.at(i))) = get<2>(snake.at(i));
        }
    }
    else if (input == 's' && get<0>(snake.at(0)) != 9)
    {
        if (grid.at(get<0>(snake.at(0)) + 1).at(get<1>(snake.at(0))) == 'A')
        {
            apple = 0;
            snake.push_back(snake.at(snake.size() - 1));
            for (int i = snake.size() - 2;i > 0;i--)
            {
                get<0>(snake.at(i)) = get<0>(snake.at(i - 1));
                get<1>(snake.at(i)) = get<1>(snake.at(i - 1));
                get<3>(snake.at(i)) = get<3>(snake.at(i - 1));
            }
        }
        else
        {
            for (int i = snake.size() - 1;i > 0;i--)
            {
                get<0>(snake.at(i)) = get<0>(snake.at(i - 1));
                get<1>(snake.at(i)) = get<1>(snake.at(i - 1));
                get<3>(snake.at(i)) = get<3>(snake.at(i - 1));
            }
        }
        get<0>(snake.at(0))++;
        get<3>(snake.at(0)) = -90;


        for (int i = 0;i < 10;i++)
        {
            for (int j = 0;j < 10;j++)
            {
                if (grid.at(i).at(j) == 'O' || grid.at(i).at(j) == 'B')
                    grid.at(i).at(j) = '-';
            }
        }

        for (int i = 0;i < snake.size();i++)
        {
            grid.at(get<0>(snake.at(i))).at(get<1>(snake.at(i))) = get<2>(snake.at(i));
        }
    }
    else if (input == 'd' && get<1>(snake.at(0)) != 9)
    {
        if (grid.at(get<0>(snake.at(0))).at(get<1>(snake.at(0)) + 1) == 'A')
        {
            apple = 0;
            snake.push_back(snake.at(snake.size() - 1));
            for (int i = snake.size() - 2;i > 0;i--)
            {
                get<0>(snake.at(i)) = get<0>(snake.at(i - 1));
                get<1>(snake.at(i)) = get<1>(snake.at(i - 1));
                get<3>(snake.at(i)) = get<3>(snake.at(i - 1));
            }
        }
        else
        {
            for (int i = snake.size() - 1;i > 0;i--)
            {
                get<0>(snake.at(i)) = get<0>(snake.at(i - 1));
                get<1>(snake.at(i)) = get<1>(snake.at(i - 1));
                get<3>(snake.at(i)) = get<3>(snake.at(i - 1));
            }
        }
        get<1>(snake.at(0))++;
        get<3>(snake.at(0)) = 0;


        for (int i = 0;i < 10;i++)
        {
            for (int j = 0;j < 10;j++)
            {
                if (grid.at(i).at(j) == 'O' || grid.at(i).at(j) == 'B')
                    grid.at(i).at(j) = '-';
            }
        }

        for (int i = 0;i < snake.size();i++)
        {
            grid.at(get<0>(snake.at(i))).at(get<1>(snake.at(i))) = get<2>(snake.at(i));
        }
    }
    else if (input == 'a' && get<1>(snake.at(0)) != 0)
    {
        if (grid.at(get<0>(snake.at(0))).at(get<1>(snake.at(0)) - 1) == 'A')
        {
            apple = 0;
            snake.push_back(snake.at(snake.size() - 1));
            for (int i = snake.size() - 2;i > 0;i--)
            {
                get<0>(snake.at(i)) = get<0>(snake.at(i - 1));
                get<1>(snake.at(i)) = get<1>(snake.at(i - 1));
                get<3>(snake.at(i)) = get<3>(snake.at(i - 1));
            }
        }
        else
        {
            for (int i = snake.size() - 1;i > 0;i--)
            {
                get<0>(snake.at(i)) = get<0>(snake.at(i - 1));
                get<1>(snake.at(i)) = get<1>(snake.at(i - 1));
                get<3>(snake.at(i)) = get<3>(snake.at(i - 1));
            }
        }
        get<1>(snake.at(0))--;
        get<3>(snake.at(0)) = 180;


        for (int i = 0;i < 10;i++)
        {
            for (int j = 0;j < 10;j++)
            {
                if (grid.at(i).at(j) == 'O' || grid.at(i).at(j) == 'B')
                    grid.at(i).at(j) = '-';
            }
        }


        for (int i = 0;i < snake.size();i++)
        {
            grid.at(get<0>(snake.at(i))).at(get<1>(snake.at(i))) = get<2>(snake.at(i));
        }
    }
}


void Game::processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && input != 's')
        input = 'w';
    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS && input != 'w')
        input = 's';
    else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS && input != 'd')
        input = 'a';
    else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS && input != 'a')
        input = 'd';
}
