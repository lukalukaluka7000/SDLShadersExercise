#include "Exercise.h"
#include<SDL/SDL.h>
#include<glm/glm.hpp>
#include<glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include<iostream>
#include<random>

#include<GL/glut.h>
#include"IOManager.h"
#include"Object.h"
#include"Vertex.h"
#include <time.h>

const int BIG_NUM = 100000;
Exercise::~Exercise() {
	//glDeleteBuffers(1, &_vboTeddyID);
	//glDeleteBuffers(1, &_iboTeddyID);
	glDeleteBuffers(1, &_vboOsiID);
	glDeleteBuffers(1, &_iboOsiID);
	
	glDeleteBuffers(1, &_theVBO);
	glDeleteBuffers(1, &_theIBO);

	glDeleteBuffers(1, &_vaoOsiID);
	glDeleteBuffers(10, _allVAOs);
	
	// projekt koncipiran da se iz Exercise barata sa bufferima
	// a iz GLSLPrograma se barata programom, fino
	// ovo radim is GLSLProgram, ovdi deleteam samo buffere
	//glUseProgram(0);
	//glDeleteProgram(_programId);
}
void Exercise::init(InputManager* inputManager, GLSLProgram* colorProgram, GLSLProgram* trivialProgram) {

	_inputManager = inputManager;

	// create random generator
	std::mt19937 randomEngine;
	randomEngine.seed(time(nullptr));
	std::uniform_real_distribution<float> rYPos(.5f, 2.0f);

	IOManager::getOcisteGledisteViewUp("./Assets/ociste_glediste.txt", _O, _G, _V);
	_pocOc = _O; _pocGl = _G; _pocV = _V;
	_objects.push_back(Object(1, glm::vec4(0.0f, 3.0f, 0.0f, 1.0f), glm::vec4(0.0f, 255.0f, 0.0f, 255.0f), 0.4f, "./Assets/teddy.obj"));
	//_objects.push_back(Object(3, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec4(0.0f, 255.0f, 0.0f, 255.0f), .5f, "./Assets/kocka.obj"));

	_objects.push_back(Object(2, glm::vec4(-5.0f, rYPos(randomEngine), 0.0f, 1.0f), glm::vec4(0.0f, 255.0f, 0.0f, 255.0f), .5f,		"./Assets/cube.obj"));
	_objects.push_back(Object(3, glm::vec4(-3.0f, rYPos(randomEngine), 0.0f, 1.0f), glm::vec4(0.0f, 255.0f, 0.0f, 255.0f), .5f,		"./Assets/cube.obj"));
	_objects.push_back(Object(3, glm::vec4(-1.0f, rYPos(randomEngine), 0.0f, 1.0f), glm::vec4(0.0f, 255.0f, 0.0f, 255.0f), .5f,		"./Assets/cube.obj"));
	_objects.push_back(Object(3, glm::vec4(1.0f,  rYPos(randomEngine), 0.0f, 1.0f), glm::vec4(0.0f, 255.0f, 0.0f, 255.0f), .5f,		"./Assets/cube.obj"));
	_objects.push_back(Object(3, glm::vec4(3.0f,  rYPos(randomEngine), 0.0f, 1.0f), glm::vec4(0.0f, 255.0f, 0.0f, 255.0f), .5f,		"./Assets/cube.obj"));
												  																							
	_objects.push_back(Object(3, glm::vec4(-4.0f, rYPos(randomEngine), -1.0f, 1.0f), glm::vec4(0.0f, 255.0f, 0.0f, 255.0f),  .5f,	"./Assets/cube.obj"));
	_objects.push_back(Object(3, glm::vec4(-2.0f, rYPos(randomEngine), -1.0f, 1.0f), glm::vec4(0.0f, 255.0f, 0.0f, 255.0f),  .5f,	"./Assets/cube.obj"));
	_objects.push_back(Object(3, glm::vec4( 0.0f, rYPos(randomEngine),  -1.0f, 1.0f), glm::vec4(0.0f, 255.0f, 0.0f, 255.0f),  .5f,	"./Assets/cube.obj"));
	_objects.push_back(Object(3, glm::vec4( 2.0f, rYPos(randomEngine),  -1.0f, 1.0f), glm::vec4(0.0f, 255.0f, 0.0f, 255.0f),  .5f,	"./Assets/cube.obj"));
																																		
	_objects.push_back(Object(2, glm::vec4(-5.0f, rYPos(randomEngine), -2.0f, 1.0f), glm::vec4(0.0f, 255.0f, 0.0f, 255.0f), .5f,	"./Assets/cube.obj"));
	_objects.push_back(Object(3, glm::vec4(-3.0f, rYPos(randomEngine), -2.0f, 1.0f), glm::vec4(0.0f, 255.0f, 0.0f, 255.0f), .5f,	"./Assets/cube.obj"));
	_objects.push_back(Object(3, glm::vec4(-1.0f, rYPos(randomEngine), -2.0f, 1.0f), glm::vec4(0.0f, 255.0f, 0.0f, 255.0f), .5f,	"./Assets/cube.obj"));
	_objects.push_back(Object(3, glm::vec4(1.0f,  rYPos(randomEngine), -2.0f, 1.0f), glm::vec4(0.0f, 255.0f, 0.0f, 255.0f), .5f,	"./Assets/cube.obj"));
	_objects.push_back(Object(3, glm::vec4(3.0f,  rYPos(randomEngine), -2.0f, 1.0f), glm::vec4(0.0f, 255.0f, 0.0f, 255.0f), .5f,	"./Assets/cube.obj"));

	_objects.push_back(Object(3, glm::vec4(4.5f, rYPos(randomEngine), 0.0f, 1.0f), glm::vec4(0.0f, 255.0f, 0.0f, 255.0f), .5f, "./Assets/cube.obj"));
	_objects.push_back(Object(3, glm::vec4(7.5f, rYPos(randomEngine), 0.0f, 1.0f), glm::vec4(0.0f, 255.0f, 0.0f, 255.0f), .5f, "./Assets/cube.obj"));

	_objects.push_back(Object(4, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec4(0.0f, 255.0f, 0.0f, 255.0f), 1.0f, "./Assets/plane.obj", false));
	sendDataToOpenGL();
	setupVertexArrays();

	_currentStateFlag |= ProgramMode::GET_VERTICES;
}
glm::mat4 setModelMat(glm::vec4 pos, float scaleValue) {
	//matrica modela
	float T1_Modeltranslate[16] = {
	   1.0f, 0.0f, 0.0f, pos.x,
	   0.0f, 1.0f, 0.0f, pos.y,
	   0.0f, 0.0f, 1.0f, pos.z,
	   0.0f, 0.0f, 0.0f, 1.0f };
	glm::mat4x4 T1_ModelTra = glm::make_mat4x4(T1_Modeltranslate);
	float T1_Modelscale[16] = {
		  scaleValue, 0.0f, 0.0f, 0.0f,
		   0.0f, scaleValue, 0.0f, 0.0f,
		   0.0f, 0.0f, scaleValue, 0.0f,
		   0.0f, .0f, .0f,		1.0f };
	glm::mat4x4 T1_ModelSca = glm::make_mat4x4(T1_Modelscale);

	// moras transponirat zbog zbunjujuceg poretka u glm-u -> T1_ModelTraT * T1_ModelScaT
	glm::mat4 modelMat = glm::transpose(T1_ModelSca * T1_ModelTra);
	return modelMat;
}
void Exercise::sendDataToOpenGL() {
	//---CREATE VBO, IBO, ---

	// --- color SHADER ---
	if (_theVBO == 0) {
		glGenBuffers(1, &_theVBO);
	}
	if (_theIBO == 0) {
		glGenBuffers(1, &_theIBO);
	}

	int total_vertices = 0; int total_indices = 0;
	std::vector<Vertex> vertexData; Vertex vertex;
	std::vector<GLushort> indices;
	for (auto& obj : _objects) {
		total_vertices += obj.vertices.size();
		total_indices += obj.poligons.size() * 3;
	}
	GLintptr currentOffsetVBO = 0;
	GLintptr currentOffsetIBO = 0;
	glBindBuffer(GL_ARRAY_BUFFER, _theVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * total_vertices, NULL, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _theIBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * total_indices, NULL, GL_STATIC_DRAW);

	for (auto& obj : _objects) {
		vertexData.clear();
		for (int i = 0; i < obj.vertices.size(); i++) {
			vertex.setPosition(obj.vertices[i]);
			vertex.setColor(glm::vec4(rand() / (float)RAND_MAX, rand() / (float)RAND_MAX, rand() / (float)RAND_MAX, 1.0f));
			vertex.setNormal(i, obj.indeksiPoligona, obj.polygonNormals);
			vertexData.push_back(vertex);
		}

		indices.clear();
		for (int i = 0; i < obj.poligons.size(); i++) {
			indices.push_back((GLushort)(obj.poligons[i].x - 1));
			indices.push_back((GLushort)(obj.poligons[i].y - 1));
			indices.push_back((GLushort)(obj.poligons[i].z - 1));
		}
		
		glBindBuffer(GL_ARRAY_BUFFER, _theVBO);

		glBufferSubData(GL_ARRAY_BUFFER, currentOffsetVBO, vertexData.size() * sizeof(Vertex), &vertexData.front());
		currentOffsetVBO += vertexData.size() * sizeof(Vertex);
		std::cout << "VBO: " << currentOffsetVBO << std::endl;
		// ovo sad pribacimo doli u draw!!! ILI koristi VAO
		/*glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));*/

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _theIBO);
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, currentOffsetIBO, indices.size() * sizeof(GLushort), &indices.front());
		currentOffsetIBO += indices.size() * sizeof(GLushort);
		std::cout << "IBO: "<< currentOffsetIBO << std::endl;
	}



	// -- TRIVIAL SHADER -> JUST DRAW AS IT IS
	if (_vboOsiID == 0) {
		glGenBuffers(1, &_vboOsiID);
	}
	if (_iboOsiID == 0) {
		glGenBuffers(1, &_iboOsiID);
	}

	GLfloat verticesOsi[] = {
		-2.5f, 0.0, 0.0, 1.0,
		1.0f,0.0f,0.0f,1.0f,

		100.0f, 0.0, 0.0, 1.0,
		1.0f,0.0f,0.0f,1.0f,

		0.0, -2.5f, 0.0, 1.0,
		0.0f,1.0f,0.0f,1.0f,

		0.0, 100.0f, 0.0, 1.0,
		0.0f,1.0f,0.0f,1.0f,

		0.0, 0.0, -2.5f, 1.0,
		0.0f,0.0f,1.0f,1.0f,

		0.0, 0.0, 100.0f, 1.0,
		0.0f,0.0f,1.0f,1.0f,
	};
	GLushort indicesOsi[] = { 0,1, 2,3, 4,5 };
	// osi
	
	glBindBuffer(GL_ARRAY_BUFFER, _vboOsiID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesOsi), verticesOsi, GL_STATIC_DRAW);
	//glEnableVertexAttribArray(0); // no longer need to enable that but there is bigger problem
	//glEnableVertexAttribArray(1);
	// ovo sad pribacimo doli u draw!!! ILI koristi VAO
	/*glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 4));*/

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _iboOsiID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesOsi), indicesOsi, GL_STATIC_DRAW);

	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//vertexData, indices, verticesOis, indicesOsi .CLEARRRR WE DONT NNED THAT ANYMORE EVERTYTHING IS ON GPU
	vertexData.clear();
	indices.clear();
}
void Exercise::setupVertexArrays() {
	
	// --- color SHADER ---
	GLsizeiptr currentOffset = 0;
	int currentVAO = 0;
	for (auto& obj : _objects) {
		if (_allVAOs[currentVAO] == 0) {
			glGenVertexArrays(1, &_allVAOs[currentVAO]);
		}
		glBindVertexArray(_allVAOs[currentVAO]); // sve nakon ovoga je stanje koje VAO pamti!!!
		glBindBuffer(GL_ARRAY_BUFFER, _theVBO);
		glEnableVertexAttribArray(0);	glEnableVertexAttribArray(1); glEnableVertexAttribArray(2);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)currentOffset);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(currentOffset + sizeof(float) * 4));
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (char*)(currentOffset + sizeof(float) * 8));


		currentOffset += _objects[currentVAO].vertices.size() * sizeof(Vertex);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _theIBO);
		currentVAO++;
	}

	// -- TRIVIAL SHADER -> JUST DRAW AS IT IS
	glGenVertexArrays(1, &_vaoOsiID);
	glBindVertexArray(_vaoOsiID);
	glBindBuffer(GL_ARRAY_BUFFER, _vboOsiID);
	glEnableVertexAttribArray(0);	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 4));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _iboOsiID);
}
void Exercise::sendConstUniforms(GLSLProgram* colorProgram) {

	// sending ambient light
	glm::vec4 ambientData(0.42f, 0.42f, 0.42f, 1.0f);
	GLint ambientLightUniform = colorProgram->getUniformLocation("ambientLight");
	glUniform4fv(ambientLightUniform, 1, &ambientData[0]);

}

void Exercise::update() {

	//manage ociste
	const float MOVIN_SPEED = 0.005f;
	glm::vec3 viewDirection = _G - _O;
	if (_inputManager->isKeyDown(SDLK_q)) {
		_O.y = _O.y + MOVIN_SPEED;
	}
	if (_inputManager->isKeyDown(SDLK_e)) {
		_O.y = _O.y - MOVIN_SPEED;
	}
	if (_inputManager->isKeyDown(SDLK_w)) {
		_O += MOVIN_SPEED * glm::normalize(viewDirection);
	}
	if (_inputManager->isKeyDown(SDLK_s)) {
		_O -= MOVIN_SPEED * glm::normalize(viewDirection);
	}
	if (_inputManager->isKeyDown(SDLK_a)) {
		glm::vec3 strafingAxisL = glm::cross(glm::normalize(viewDirection), _pocV);
		_O -= MOVIN_SPEED * strafingAxisL;
	}
	if (_inputManager->isKeyDown(SDLK_d)) {
		glm::vec3 strafingAxisR = glm::cross(glm::normalize(viewDirection), _pocV);
		_O += MOVIN_SPEED * strafingAxisR;
	}
	if (_inputManager->isKeyDown(SDLK_r)) {
		_O = _pocOc; _G = _pocGl;
	}

	// manage glediste
	glm::vec2 diffMouseVector = _inputManager->getMouseCoords() - previousMousePosition;
	//glm::vec3 viewDirection = _G - _O;
	if (glm::length(diffMouseVector) > 0.0f) {
		if (glm::length(diffMouseVector) > 50.0f) {
			previousMousePosition = _inputManager->getMouseCoords();
		}
		else {
			// horizontal rotation
			_G = glm::mat3(glm::rotate(-diffMouseVector.x * (MOVIN_SPEED/2.0f), _pocV)) * viewDirection;
			// vertical rotation
			glm::vec3 verticalRotationAxis = glm::cross(_G, _pocV);
			_G = glm::mat3(glm::rotate(-diffMouseVector.y * (MOVIN_SPEED/2.0f), verticalRotationAxis)) * _G;
			previousMousePosition = _inputManager->getMouseCoords();
		}
	}

	if (_inputManager->isKeyDown(SDLK_l)) {
		currentLightPos.x += 5*MOVIN_SPEED;
	}
	if (_inputManager->isKeyDown(SDLK_k)) {
		currentLightPos.x -= 5*MOVIN_SPEED;
	}
	updateViewAndProjection();
}

void Exercise::draw(GLSLProgram* colorProgram) {
	
	// with light it would be useful to send as a const uniform kojeg je reda distanca u nazivniku
	glm::vec3 lightPosData = currentLightPos;
	GLint lightPositionUniform = colorProgram->getUniformLocation("lightPositionWorld");
	glUniform3fv(lightPositionUniform, 1, &lightPosData[0]);

	GLint projMatUniform = colorProgram->getUniformLocation("projection");
	glUniformMatrix4fv(projMatUniform, 1, GL_FALSE, &_projMat[0][0]);
	GLint viewMatUniform = colorProgram->getUniformLocation("view");
	glUniformMatrix4fv(viewMatUniform, 1, GL_FALSE, &_viewMat[0][0]);
	GLint eyePosUniform = colorProgram->getUniformLocation("eyePositionWorld");
	glUniform3fv(eyePosUniform, 1, &_O[0]);

	// draw all objects - ovdje ispod su bile sve stvari koje smo u VAO spremili a to su bindanje buffera, namjestanja attrippointera i bindanje indexa
	GLintptr currentOffsetIBO = 0;
	glm::mat4 ModelMat; int currentVAO = 0;
	for (auto& obj : _objects) {
		glBindVertexArray(_allVAOs[currentVAO]);
		ModelMat = setModelMat(obj.Position, obj.scaleValue);
		GLint modelMatUniform = colorProgram->getUniformLocation("model");
		glUniformMatrix4fv(modelMatUniform, 1, GL_FALSE, &ModelMat[0][0]);
		glDrawElements(GL_TRIANGLES, obj.poligons.size() * 3, GL_UNSIGNED_SHORT, (void*)currentOffsetIBO);

		currentOffsetIBO += obj.poligons.size() * 3 * sizeof(GLushort);
		currentVAO++;
	}
	glBindVertexArray(0);
	
}
void Exercise::drawOsi(GLSLProgram* trivialProgram) {
	glm::mat4 ModelMat;

	// draw osi - ovdje ispod su bile sve stvari koje smo u VAO spremili a to su bindanje buffera, namjestanja attrippointera i bindanje indexa
	glBindVertexArray(_vaoOsiID);
	ModelMat = setModelMat(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), 10.0f);
	GLint modelMatUniform = trivialProgram->getUniformLocation("model");
	GLint projMatUniform = trivialProgram->getUniformLocation("projection");
	GLint viewMatUniform = trivialProgram->getUniformLocation("view");
	glUniformMatrix4fv(projMatUniform, 1, GL_FALSE, &_projMat[0][0]);
	glUniformMatrix4fv(viewMatUniform, 1, GL_FALSE, &_viewMat[0][0]);
	glUniformMatrix4fv(modelMatUniform, 1, GL_FALSE, &ModelMat[0][0]);

	glDrawElements(GL_LINES, 6, GL_UNSIGNED_SHORT,0);
	glBindVertexArray(0);
}
void Exercise::updateViewAndProjection() {

	// MATRICA TRANSFORMACIJE POGLEDA, dakle ModelView matrica
	float T1_data[16] = {
		   1.0f, 0.0f, 0.0f, 0.0f,
		   0.0f, 1.0f, 0.0f, 0.0f,
		   0.0f, 0.0f, 1.0f, 0.0f,
		   -_O.x, -_O.y, -_O.z, 1.0f };
	glm::mat4x4 T1 = glm::make_mat4x4(T1_data);
	// G = Gl;
	glm::vec3 Glokalni = _G - _O; // uzmimo novi G jer smo sada u ishodistu i on je novi naravno

	// odredivanje osi - skica na mobitelu
	glm::vec3 z = _G - _O; //z(G.x - O.x, G.y - O.y, G.z - O.z);
	z = glm::normalize(z);
	//float H = glm::distance(G,O);

	glm::vec3 viewUp(_V.x, _V.y, _V.z);
	viewUp = glm::normalize(viewUp);

	//automatski normaliziran jer su z i viewUp takvi vec
	glm::vec3 x = glm::cross(z, viewUp);
	glm::vec3 y = glm::cross(x, z);

	float Ruku_data[16] = {
		   x.x,  y.x,  z.x,  0.0f,
		   x.y,  y.y,  z.y,  0.0f,
		   x.z,	 y.z,  z.z,  0.0f,
		   0.0f, 0.0f, 0.0f, 1.0f };
	glm::mat4x4 Ruku = glm::make_mat4x4(Ruku_data);

	// zrcaliti os jer je ks oka lijevi, a nas ks scene je desni
	float Tz_data[16] = {
		   1.0f,  0.0f,  0.0f,  0.0f,
		   0.0f,  1.0f,  0.0f,  0.0f,
		   0.0f,  0.0f, -1.0f,  0.0f,
		   0.0f,  0.0f,  0.0f,  1.0f };
	glm::mat4x4 Tz = glm::make_mat4x4(Tz_data);

	
	// moras transponirat zbog zbunjujuceg poretka u glm-u -> TzT * RukuT * T1T
	_view = glm::transpose(T1 * Ruku * Tz);
	_viewMat = glm::lookAt(glm::vec3(_O.x, _O.y, _O.z), glm::vec3(_G.x, _G.y, _G.z), glm::vec3(_V.x, _V.y, _V.z));


	// MATRICA PERSPEKTIVNE PROJEKTCIJE, dakle projection matrix
	float H = sqrt(pow(_O.x - _G.x, 2) + pow(_O.y - _G.y, 2) + pow(_O.z - _G.z, 2));
	//H = glm::length(Glokalni);
	//H = sqrt(pow(O.x - G.x, 2) + pow(O.y - G.y, 2) + pow(O.z - G.z, 2));
	//std::cout << "Ociste  : " << _O.x << " " << _O.y << " " << _O.z << std::endl;
	//std::cout << "Glediste: " << _G.x << " " << _G.y << " " << _G.z << std::endl;
	//std::cout << "H: " << H << std::endl;
	
	//_projMat = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f);
	_projMat = glm::frustum(-1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -2.0f);
	//glm::mat4 projMat = glm::perspective(90.0f, 400.0f/400.0f, 1.0f, -1.0f);


	float fov = (90 - 45) * ((H - 0.0f) / (20.0f - 0.0f)) + 45;
	float S = 1.0f / (tan((fov / 2.0f) * (3.14f / 180.0f)));

	float H_data[16] = {
			S,  0.0f,  0.0f,  0.0f,
			0.0f,  S,  0.0f,  0.0f,
			0.0f,  0.0f,  1.0f,  1.0f / H,
			0.0f,  0.0f,  0.0f,  0.0f };
	_P = glm::make_mat4x4(H_data);
	//glm::mat4 projection = glm::transpose(P);
	_projection = _P;
	
}