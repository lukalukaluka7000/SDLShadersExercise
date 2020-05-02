#pragma once
#include<GL/glew.h>
#include<glm/glm.hpp>
#include<string>
#include"IOManager.h"
#include<glm/gtx/transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<unordered_map>

struct Object {
	Object() : id(0), Position(0), color(0), scaleValue(0.0f), filePath("") {	}
	Object(GLuint Id, glm::vec4 Pos, glm::vec4 Col, float Scale, std::string filePath, bool clockWise = true) :
		id(Id), Position(Pos), color(Col), scaleValue(Scale)
	{
		IOManager::readOBJ(filePath, vertices, poligons);

		sredisteTijela = determineMinMaxPoints();

		float prebaciUIshodiste_data[16] = {
		   1.0f, 0.0f, 0.0f, 0.0f,
		   0.0f, 1.0f, 0.0f, 0.0f,
		   0.0f, 0.0f, 1.0f, 0.0f,
		   -sredisteTijela.x, -sredisteTijela.y, -sredisteTijela.z, 1.0f };
		glm::mat4x4 prebaciUIshodiste = glm::make_mat4x4(prebaciUIshodiste_data);

		int br = 0;
		float x_n, y_n, z_n;
		const float DG = -1.0f; const float GG = 1.0f;
		if (id != 4) {
			for (auto& v : vertices) {
				//postaviti u ishodiste
				glm::vec4 transformedVector = glm::transpose(prebaciUIshodiste) * glm::vec4(v.x, v.y, v.z, 1.0f);

				//skaliraj na [-1,1] jer tna taj nacin postizes da mozes prikazat bilo koji .obj
				x_n = (GG - DG) * ((transformedVector.x - xmin) / (xmax - xmin)) + DG;
				y_n = (GG - DG) * ((transformedVector.y - ymin) / (ymax - ymin)) + DG;
				z_n = (GG - DG) * ((transformedVector.z - zmin) / (zmax - zmin)) + DG;

				//x_n = (xmax - xmin) * ((v.x - xmin) / (xmax - xmin)) + xmin;
				//y_n = (ymax - ymin) * ((v.y - ymin) / (ymax - ymin)) + ymin;
				//z_n = (zmax - zmin) * ((v.z - zmin) / (zmax - zmin)) + zmin;

				vertices[br] = glm::vec4(x_n, y_n, z_n, 1.0f);
				br++;
			}
		}
		clockWiseOrientationOfObject = clockWise;
		determineNormalPolygons();
		setIndeksiPoligona();
	}
	glm::vec3 determineMinMaxPoints() {
		float sumaX = 0.0f, sumaY = 0.0f, sumaZ = 0.0f;
		for (auto& v : vertices) {
			if (v.x < xmin) xmin = v.x;
			if (v.y < ymin) ymin = v.y;
			if (v.z < zmin) zmin = v.z;

			if (v.x > xmax) xmax = v.x;
			if (v.y > ymax) ymax = v.y;
			if (v.z > zmax) zmax = v.z;

			sumaX += v.x;
			sumaY += v.y;
			sumaZ += v.z;
		}
		float vrojVrhova = float(vertices.size());
		glm::vec3 sredisteTijela = glm::vec3(sumaX / vrojVrhova, sumaY / vrojVrhova, sumaZ / vrojVrhova);
		return sredisteTijela;
	}

	void determineNormalPolygons() {
		for (auto& p : poligons) {
			// vrhovi V0 -> V1 -> V2
			glm::vec3 V0(vertices[p.x-1]);
			glm::vec3 V1(vertices[p.y-1]);
			glm::vec3 V2(vertices[p.z-1]);
			if(clockWiseOrientationOfObject==true)
				polygonNormals.push_back(glm::normalize(glm::cross(V1 - V0, V2 - V0)));
			else
				polygonNormals.push_back(glm::normalize(glm::cross(V2 - V0, V1 - V0)));
		}
	}
	void setIndeksiPoligona() {
		unsigned int polygonIndex;
		for (unsigned int vertexIndex = 0; vertexIndex < vertices.size(); vertexIndex++) {
			
			polygonIndex = 0;
			for (auto& p : poligons) {

				if (p.x-1 == vertexIndex || p.y-1 == vertexIndex || p.z-1 == vertexIndex) {
					indeksiPoligona[vertexIndex].push_back(polygonIndex);
				}
				polygonIndex++;
			}

		}
	}
	GLuint id;
	glm::vec4 Position;
	glm::vec4 color;
	float scaleValue;
	std::string filePath;
	std::vector<glm::vec4> vertices;
	std::vector<glm::vec3> poligons;
	std::vector<glm::vec3> polygonNormals;
	bool clockWiseOrientationOfObject = true;
	// ---indeksi poligona u kojima se sve key-vrh nalazi---  je sizeof(vertices)
	std::unordered_map<unsigned int, std::vector<unsigned int>> indeksiPoligona;

	glm::vec3 sredisteTijela;
	const int BIG_NUM = 100000;
	float xmin = BIG_NUM, xmax = -BIG_NUM;
	float ymin = BIG_NUM, ymax = -BIG_NUM;
	float zmin = BIG_NUM, zmax = -BIG_NUM;
};