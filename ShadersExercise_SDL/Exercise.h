#pragma once
#include<vector>
#include<glm/glm.hpp>
#include"InputManager.h"
#include"GLSLProgram.h"
#include"Sprite.h"
#include"Object.h"
#include"GLSLProgram.h"
class Exercise
{
public:
	enum ProgramMode { GET_VERTICES = 0x1 };
	~Exercise();
	void init(InputManager* inputManager, GLSLProgram* colorProgram, GLSLProgram* trivialProgram);
	void update();

	void draw(GLSLProgram* colorProgram);
	void drawOsi(GLSLProgram* trivialProgram);

	void sendConstUniforms(GLSLProgram* colorProgram);

	unsigned int getCurrentStateFlag() { return _currentStateFlag; }

private:
	void updateViewAndProjection();
	void sendDataToOpenGL();
	void setupVertexArrays();
	

	InputManager* _inputManager;
	/*GLSLProgram* _colorProg;*/
	glm::vec2 previousMousePosition = glm::vec2(0.0f);
	unsigned int _currentStateFlag;// = ProgramMode::GETTING_POINTS;

	int _ymin = 0, _ymax = -0;
	int _xmin = 0, _xmax = -0;

	glm::vec3 _O{}, _G{}, _V{};
	glm::vec3 _pocOc{}, _pocGl{}, _pocV;
	std::vector<Object> _objects;

	glm::mat4 _model, _view, _projection;
	glm::mat4 _viewMat, _projMat;
	glm::mat4x4 _T, _P;

	glm::vec3 currentLightPos = glm::vec3(-3.5f, 3.5f, 0.0f);


	//GLuint _vboTeddyID;
	GLuint _theVBO;
	GLuint _theIBO;

	GLuint _vboOsiID;
	GLuint _iboOsiID;
	//65 video umjesto svih ovih gornjih 4 napravis: (kao da se svi objekti nalaze u jednom bufferu (tj. u dva jer imas i indekse))
	// Gluint _theVbo;
	// GLuint _theIbo;
	//GLuint _vaoCubeID;
	//GLuint _vaoTeddyID;
	GLuint _vaoOsiID;
	GLuint _allVAOs[100]; // zasad 10 mac objeckata
};

