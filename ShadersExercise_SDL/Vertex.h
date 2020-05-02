#pragma once
#include<GL/glew.h>
struct DebugVertex {
	glm::vec4 position;
};
struct Vertex {
	glm::vec4 position;
	glm::vec4 color;
	glm::vec3 normala;
	void setPosition(glm::vec4 Pos) {
		position = Pos;
	}
	void setColor(glm::vec4 Col) {
		color = Col;
	}
	void setNormal(	unsigned int indexOfVertex, 
					const std::unordered_map<unsigned int, std::vector<unsigned int>>& indeksiPoligona,
					const std::vector<glm::vec3>& polygonNormals) {
		// jer u pozivu ove funkcije se ide od [0, vertices.size()]
		normala = glm::vec3(0.0f);
		//indexOfVertex += 1;
		auto it = indeksiPoligona.find(indexOfVertex);
		if (it != indeksiPoligona.end()) {
			std::vector<unsigned int> poligoniKojimaVertexPripada = it->second;

			for (auto& pV : poligoniKojimaVertexPripada) {
				normala = normala + polygonNormals[pV];
			}
			normala /= poligoniKojimaVertexPripada.size();
			//normala = glm::normalize(normala);
		}
		// ---koristimo kao boju pa daj da ide od [-1,1]->[0,1]
		//normala = (normala + glm::vec3(1.0f)) / 2.0f;
	}
};