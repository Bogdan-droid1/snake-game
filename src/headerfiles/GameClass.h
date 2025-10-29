#pragma once

#include <vector>
#include <array>
#include <tuple>
#include "../headerfiles/RendererClass.h"


class Game
{
public:

    Game();

    void Run();

    void startGame();

public:

    char input = 'd', lastinput = '0';
    bool mouseclicked = 0;
private:

    Renderer renderer;
    std::vector <std::tuple<int16_t, int16_t, char, int16_t>> snake;
    std::array <std::array <char, 10>, 10> grid;
    std::tuple<int16_t, int16_t> lastHeadPos;
    bool apple = 0, gameStarted = 0;

    void trySpawnApple();

    bool isGameOver();

    int16_t isWin();

    bool isdead();

    void handleInput(GLFWwindow* window);

    void processInput(GLFWwindow* window);

    void ifmenu(GLFWwindow* window, Renderer& renderer);
};
