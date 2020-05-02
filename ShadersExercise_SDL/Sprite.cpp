//#include "Sprite.h"
//#include"Object.h"
//#include<vector>
//#include"Vertex.h"
//#include<iostream>
//#include<random>
//#include "Exercise.h"
//Sprite::Sprite()
//{
//	starts of by setting your vbo to null	
//	_vboTeddyID = 0;
//	_iboTeddyID = 0;
//	_vboOsiID = 0;
//	_iboOsiID = 0;
//}
//
//
//Sprite::~Sprite()
//{
//	brisi ga ako postoji
//	if (_vboTeddyID != 0) {
//		glDeleteBuffers(1, &_vboTeddyID);
//	}
//	if (_iboTeddyID != 0) {
//		glDeleteBuffers(1, &_iboTeddyID);
//	}
//	if (_vboOsiID != 0) {
//		glDeleteBuffers(1, &_vboOsiID);
//	}
//	if (_iboOsiID != 0) {
//		glDeleteBuffers(1, &_iboOsiID);
//	}
//}
//
//void Sprite::init(Object mojObj) {
//	_objects.push_back(mojObj);
//
//	std::vector<glm::vec4> boje;
//	boje.push_back(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
//	boje.push_back(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
//	boje.push_back(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
//	boje.push_back(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
//	boje.push_back(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
//	boje.push_back(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
//	boje.push_back(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
//	boje.push_back(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
//	 prep the data to upload 	// ---- EXTRAHIRANJE PODATAKA IZ OBJ, OVO JAKO OPTIMIRAT TREBA
//	
//}
//glm::mat4 setModelMat(glm::vec4 pos, float scaleValue) {
//	matrica modela
//	float T1_Modeltranslate[16] = {
//	   1.0f, 0.0f, 0.0f, pos.x,
//	   0.0f, 1.0f, 0.0f, pos.y,
//	   0.0f, 0.0f, 1.0f, pos.z,
//	   0.0f, 0.0f, 0.0f, 1.0f };
//	glm::mat4x4 T1_ModelTra = glm::make_mat4x4(T1_Modeltranslate);
//	float T1_Modelscale[16] = {
//		  scaleValue, 0.0f, 0.0f, 0.0f,
//		   0.0f, scaleValue, 0.0f, 0.0f,
//		   0.0f, 0.0f, scaleValue, 0.0f,
//		   0.0f, .0f, .0f,		1.0f };
//	glm::mat4x4 T1_ModelSca = glm::make_mat4x4(T1_Modelscale);
//
//	 moras transponirat zbog zbunjujuceg poretka u glm-u -> T1_ModelTraT * T1_ModelScaT
//	glm::mat4 modelMat = glm::transpose(T1_ModelSca * T1_ModelTra);
//	return modelMat;
//}
//render the sprite
//void Sprite::draw(GLSLProgram* colorProgram, glm::mat4& ProjMat, glm::mat4& ViewMat) {
//	colorProgram->use();
//	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
//
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)offsetof(Vertex, position));
//	glEnableVertexAttribArray(1);
//	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)offsetof(Vertex, color));
//
//	std::vector<Vertex> vertexData; int indexOfVert; Vertex vertex;
//	for (int i = 0; i < _brojPoligona; i++) {
//		vertexData.clear();
//		for (int j = 0; j < 3; j++) {
//			indexOfVert = _poligoni[i][j] - 1; //0 ,3, 6, 9, 12, 15 ...
//			//vertexData[i * 3 + j].position = vertices[indexOfVert];
//			vertex.setPosition(_vrhovi[indexOfVert]);
//			vertex.setColor(glm::vec4(rand() / (float)RAND_MAX, rand() / (float)RAND_MAX, rand() / (float)RAND_MAX, 1.0f));
//			vertexData.push_back(vertex);
//		}
//		
//		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 3, &vertexData.front(), GL_STATIC_DRAW);
//		glDrawArrays(GL_TRIANGLES, 0, 3);//GL_LINE_LOOP
//	}
//	
//
//	glDisableVertexAttribArray(0);
//	glDisableVertexAttribArray(1);
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//	
//	glBindBuffer(GL_ARRAY_BUFFER, _vboTeddyID);
//
//	GLint projMatUniform = colorProgram->getUniformLocation("projection");
//	glUniformMatrix4fv(projMatUniform, 1, GL_FALSE, &ProjMat[0][0]);
//	GLint viewMatUniform = colorProgram->getUniformLocation("view");
//	glUniformMatrix4fv(viewMatUniform, 1, GL_FALSE, &ViewMat[0][0]);
//	
//	glm::mat4 ModelMat;
//	for (auto& obj : _objects) {
//		ModelMat = setModelMat(obj.Position, obj.scaleValue);
//		GLint modelMatUniform = colorProgram->getUniformLocation("model");
//		glUniformMatrix4fv(modelMatUniform, 1, GL_FALSE, &ModelMat[0][0]);
//		glDrawElements(GL_TRIANGLES, _poligoni.size() * 3, GL_UNSIGNED_SHORT, 0);
//	}
//	
//
//
//	glBindBuffer(GL_ARRAY_BUFFER, _vboOsiID);
//	glDrawElements(GL_LINES, 6, GL_UNSIGNED_SHORT, 0);
//
//	glBindBuffer(GL_ARRAY_BUFFER, _osiID);
//
//	struct Os {
//		glm::vec4 pos;
//		glm::vec4 color;
//		void setPos(glm::vec4 Pos) {
//			pos = Pos;
//		}
//		void setColor(glm::vec4 Col) {
//			color = Col;
//		}
//	};
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)offsetof(Os, pos));
//	glEnableVertexAttribArray(1);
//	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)offsetof(Os, color));
//
//	std::vector<Os> osiData; 
//	for (int i = 0; i < _osi.size(); i++) {
//		Os os;
//		os.setPos(_osi[i]); 
//		if (i == 0 || i == 1) os.setColor(glm::vec4(255.0f, 0.0f, 0.0f, 255.0f));
//		if (i == 2 || i == 3) os.setColor(glm::vec4(0.0f, 255.0f, 0.0f, 255.0f));
//		if (i == 4 || i == 5) os.setColor(glm::vec4(0.0f, 0.0f, 255.0f, 255.0f));
//		osiData.push_back(os);
//	}
//	std::vector<Os> osData;
//
//	osData.clear(); osData.push_back(osiData[0]); osData.push_back(osiData[1]);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(Os) * 2, &osData.front(), GL_STATIC_DRAW);
//	glDrawArrays(GL_LINE_STRIP, 0, 2);
//
//	osData.clear(); osData.push_back(osiData[2]); osData.push_back(osiData[3]);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(Os) * 2, &osData.front(), GL_STATIC_DRAW);
//	glDrawArrays(GL_LINE_STRIP, 0, 2);
//
//	osData.clear(); osData.push_back(osiData[4]); osData.push_back(osiData[5]);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(Os) * 2, &osData.front(), GL_STATIC_DRAW);
//	glDrawArrays(GL_LINE_STRIP, 0, 2);
//
//	//NASTAVAK - NA OSI NADODAT JOS PIZDARIJE JER JER MI OVAJ VBOid ZA OBJECT JE SPECIFICAN SALJEN 1000 BUFERA HAHAH
//	// DODAJ INPUT MANAGER DA MOZES MIJENJAT OCISTE
//	// OTIDI NA VIDEO 8. WHY GLUSHORT UZMI KOD ZA IBO id I PRILAGODI I NACRTAJ NA TOUCH OVE BUFFERE SVE IMA SMISLA
//	//glBindBuffer(GL_ARRAY_BUFFER, _vboID);
//	////orphan the buffer with this nullptr so he deletes buffer and not overwrites it and gives us brand new buffer
//	//glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(DebugVertex), nullptr, GL_DYNAMIC_DRAW);
//	////upload the data
//	//glBufferSubData(GL_ARRAY_BUFFER, 0, _vertices.size() * sizeof(DebugVertex), _vertices.data());
//	//glBindBuffer(GL_ARRAY_BUFFER, 0);
//
//	colorProgram->unuse();
//
//	glDisableVertexAttribArray(0);
//	glDisableVertexAttribArray(1);
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//}