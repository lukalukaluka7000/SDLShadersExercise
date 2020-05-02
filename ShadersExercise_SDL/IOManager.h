#pragma once
#include<string>
#include<glm/glm.hpp>
#include<vector>
class IOManager
{
public:
	static void readOBJ(const std::string& filePath, std::vector<glm::vec4>& vrhovi, std::vector<glm::vec3>& poligoni);
	static void getOcisteGledisteViewUp(const std::string& filePath, glm::vec3& O, glm::vec3& G, glm::vec3& V);

	static bool readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer); //vector of chars
	static bool readFileToBuffer(std::string filePath, std::string& buffer); //vector of chars
};

