#include "MainGame.h"
#include<iostream>
#include<GL/glew.h>
#include<glm/glm.hpp>
MainGame::MainGame()
{
	_screenWidth = 1250;
	_screenHeight = 600;
	_gameState = GameState::PLAY;

}

MainGame::~MainGame()
{
}
void MainGame::run() {
	initSystems();

	

	gameLoop();
}


// --- WINDOW OPTION FLAGS
//	INVISIBLE = 0x1
//	FULLSCREEN = 0x2
//	BORDERLESS = 0x4
//	RESIZABLE = 0x8
// --- --- --- --- ---
void MainGame::initShaders() {
	_colorProgram.compileShaders("./Shaders/colorShading.vert", "./Shaders/colorShading.frag");
	_colorProgram.addAttribute("vertexPositionModel");
	_colorProgram.addAttribute("vertexColorModel");
	_colorProgram.addAttribute("vertexNormalModel");
	_colorProgram.linkShaders();

	_trivialProgram.compileShaders("./Shaders/trivialShader.vert", "./Shaders/trivialShader.frag");
	_trivialProgram.addAttribute("vertexPositionModel");
	_trivialProgram.addAttribute("vertexColorModel");
	_trivialProgram.linkShaders();
}
void MainGame::initSystems() {
	SDL_Init(SDL_INIT_EVERYTHING);
	 
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	_window.initWindow("Shaders Exercise with SDL", _screenWidth, _screenHeight, 568, 368, WindowFlags::RESIZABLE /*| WindowFlags::BORDERLESS*/);
	//_window.initWindow("Shaders Exercise with SDL", _screenWidth, _screenHeight, 50, 70, 0x0);

	_exercise.init(&_inputManager, &_colorProgram, &_trivialProgram);

	initShaders();

	_colorProgram.use();
	_exercise.sendConstUniforms(&_colorProgram);
	_colorProgram.unuse();
	
	//_trivialProgram.use();
	//_exercise.sendConstUniforms(&_trivialProgram);
	//_trivialProgram.unuse();

	glEnable(GL_DEPTH_TEST);
}

void MainGame::gameLoop() {
	while (_gameState != GameState::EXIT) {
		_inputManager.update();
		
		processInput();

		_exercise.update();

		drawGame();
	}
}

void MainGame::drawGame() {
	//glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, GLsizei(_window.getScreenWidth()), GLsizei(_window.getScreenHeight()));

	/*std::cout << _screenWidth << " " << _screenHeight << std::endl;
	glm::mat4 projectionMatrix = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f);
	GLint pUniform = _colorProgram.getUniformLocation("P");
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);*/
	
	_colorProgram.use();
	_exercise.draw(&_colorProgram);
	_colorProgram.unuse();

	_trivialProgram.use();
	_exercise.drawOsi(&_trivialProgram);
	_trivialProgram.unuse();


	_window.swapBuffer();

}
void MainGame::processInput() {

	SDL_Event evnt;
	while (SDL_PollEvent(&evnt) == true) {
		switch (evnt.type) {
		case SDL_QUIT:
			_gameState = GameState::EXIT;
			break;
		case SDL_MOUSEMOTION:
			_inputManager.setMouseCoords(evnt.motion.x, evnt.motion.y);
			//std::cout << evnt.motion.x << " " << evnt.motion.y << std::endl;
			break;
		case SDL_MOUSEBUTTONDOWN:
			_inputManager.keyPressed(evnt.button.button);
			//std::cout << evnt.motion.x << " " << evnt.motion.y << std::endl;
			break;
		case SDL_MOUSEBUTTONUP:
			_inputManager.keyRelease(evnt.button.button);
			break;
		case SDL_KEYDOWN:
			_inputManager.keyPressed(evnt.key.keysym.sym);
			break;
		case SDL_KEYUP:
			_inputManager.keyRelease(evnt.key.keysym.sym);
			break;
		}
	}
}