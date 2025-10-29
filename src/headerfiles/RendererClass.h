#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <array>
#include <tuple>
#include "../headerfiles/ShaderClass.h"
#include "../headerfiles/TextureClass.h"



static void error_callback(int error, const char* description)
{
	std::cout << "Error: " << description << "\n";
}

enum GameState {
	gameStart = 0,
	gameLoop,
	gameEnd
};

class Renderer
{
public:

	Renderer();
	~Renderer();
	void render(const std::array <std::array <char, 10>, 10>& grid, const std::vector <std::tuple<int16_t, int16_t, char, int16_t>>& snake, int isWin);
public:

	GLFWwindow* window = nullptr;
	GameState gameState = gameStart;
private:

	int16_t setTexture(const std::array <std::array <char, 10>, 10>& grid, uint16_t i, uint16_t j) const;
private:

	Shader m_shader;
	Texture m_texHead, m_texBody, m_texApple, m_texBackground;
	Texture m_StartScene, m_SceneYouWon, m_SceneYouLost;
	uint32_t m_VBO, m_VAO, m_EBO;
};
