#pragma once //protecting from circular includes

#include"Window.h"
#include"InputManager.h"
#include"Exercise.h"
enum class GameState { PLAY, EXIT };

class MainGame
{
public:
	MainGame();
	~MainGame();

	void run();
	void drawGame();


private:
	void initSystems();
	void initShaders();
	void gameLoop();
	void processInput();

	int _screenWidth;
	int _screenHeight;

	GameState _gameState;
	Window _window;
	InputManager _inputManager;
	GLSLProgram _colorProgram;
	GLSLProgram _trivialProgram;

	Exercise _exercise;
};

