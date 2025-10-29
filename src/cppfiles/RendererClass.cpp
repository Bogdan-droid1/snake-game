#include "../headerfiles/RendererClass.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <openglErrorReporting.h>


using std::get;

static void Framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

Renderer::Renderer()
{
	glfwSetErrorCallback(error_callback);

	if (!glfwInit())
		exit(EXIT_FAILURE);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
#endif

	window = glfwCreateWindow(800, 800, "Snake", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	enableReportGlErrors();


	float vertices[] = {
	-0.8f, -0.8f, 0.0f,  0.0f, 0.0f,
	-0.8f,  0.8f, 0.0f,  0.0f, 1.0f,
	 0.8f, -0.8f, 0.0f,  1.0f, 0.0f,
	 0.8f,  0.8f, 0.0f,  1.0f, 1.0f
	};
	uint32_t indecies[] = {
		0, 1, 2,
		1, 2, 3
	};

	
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);
	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glGenBuffers(1, &m_EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);


	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indecies), indecies, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	float widthWindow = 800.0f, heightWindow = 800.0f;
	Framebuffer_size_callback(window, widthWindow, heightWindow);
	glfwSetFramebufferSizeCallback(window, Framebuffer_size_callback);

	const char* vertexPath = SHADERS_PATH"vShader.glsl";
	const char* fragmentPath = SHADERS_PATH"fShader.glsl";
	m_shader.start(vertexPath, fragmentPath);
	m_shader.use();


	const char* texPath = RESOURCES_PATH"snake_head.jpg";
	m_texHead.Init(texPath, GL_RGB);

	texPath = RESOURCES_PATH"snake_body.jpg";
	m_texBody.Init(texPath, GL_RGB);

	texPath = RESOURCES_PATH"apple.jpg";
	m_texApple.Init(texPath, GL_RGB);

	texPath = RESOURCES_PATH"backGround.jpg";
	m_texBackground.Init(texPath, GL_RGB);

	texPath = RESOURCES_PATH"Start-scene.PNG";
	m_StartScene.Init(texPath, GL_RGBA);

	texPath = RESOURCES_PATH"Scene-You Won!.PNG";
	m_StartScene.Init(texPath, GL_RGBA);

	texPath = RESOURCES_PATH"Scene-You Lost!.PNG";
	m_StartScene.Init(texPath, GL_RGBA);
}

Renderer::~Renderer()
{
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
	glDeleteBuffers(1, &m_EBO);
	glfwDestroyWindow(window);

	glfwTerminate();
}

void Renderer::render(const std::array <std::array <char, 10>, 10>& grid, const std::vector <std::tuple<int16_t, int16_t, char, int16_t>> &snake, int isWin)
{
	glClearColor(0.3f, 0.5f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	if (gameState == gameStart)
	{
		m_shader.setInt("texture", 4); //Start-scene.PNG
		m_shader.setMat4("mat", glm::mat4(1.0f));
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		return;
	}
	else if (gameState == gameEnd)
	{
		if (isWin == 1)
			m_shader.setInt("texture", 5);
		else if (isWin == 2)
			m_shader.setInt("texture", 6);

		m_shader.setMat4("mat", glm::mat4(1.0f));
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		return;
	}


	for (uint16_t j = 0;j <= 9;j++)
	{
		glm::mat4 mat = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f, 0.1f, 0.0f));
		mat = glm::translate(mat, glm::vec3(-7.35f + j + 0.625f * j, 7.35f, 0.0f));
		glm::mat4 rot = glm::mat4(1.0f);
		for (uint16_t i = 0;i <= 9;i++)
		{
			rot = glm::mat4(1.0f);
			mat = glm::translate(mat, glm::vec3(0.0f, -1.625f * (i >= 1), 0.0f));

			for (int t = 0;t < snake.size();t++)
			{
				if (get<0>(snake.at(t)) == i && get<1>(snake.at(t)) == j)
					rot = glm::rotate(rot, glm::radians((float)get<3>(snake.at(t))), glm::vec3(0.0f, 0.0f, 1.0f));
			}
			m_shader.setMat4("mat", mat * rot);
			m_shader.setInt("texture", setTexture(grid, i, j));
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}
	}

	//glfwSwapBuffers(window);
}

int16_t Renderer::setTexture(const std::array <std::array <char, 10>, 10>& grid, uint16_t i, uint16_t j) const
{
	if (grid.at(i).at(j) == 'B')
		return 0; //snake head Texture
	else if (grid.at(i).at(j) == 'O')
		return 1; //snake body Texture
	else if (grid.at(i).at(j) == 'A')
		return 2; //apple Texture
	else if (grid.at(i).at(j) == '-')
		return 3; //background Texture
}
