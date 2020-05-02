#define _CRT_SECURE_NO_WARNINGS
#include "IOManager.h"
#include<fstream>
#include<iostream>
#include<cstdio>

void IOManager::readOBJ(const std::string& filePath, std::vector<glm::vec4>& vrhovi, std::vector<glm::vec3>& poligoni) {
    vrhovi.clear(); poligoni.clear();

    std::vector<std::string> objData;
    std::string line;
    std::ifstream file(filePath);
    if (!file) std::cerr << "Could not open file for read!" << std::endl;

    if (file.is_open()) {
        while (std::getline(file, line))
        {
            objData.push_back(line);
        }
        file.close();
    }

    char id;
    float x, y, z;
    for (int i = 0; i < objData.size(); i++) {
        int k = std::sscanf(objData[i].c_str(), " %c %f%f%f", &id, &x, &y, &z);
        glm::vec4 vrh;
        glm::vec3 pol;
        if (k == 4 && objData[i][0] == 'v') {
            vrh.x = x; vrh.y = y; vrh.z = z; vrh.w = 1.0f;
            vrhovi.push_back(vrh);
        }
        else if (k == 4 && objData[i][0] == 'f') {
            pol.x = x; pol.y = y; pol.z = z;
            poligoni.push_back(pol);
        }
    }
    std::cout << "Vrhovi: " << vrhovi.size() << std::endl;
    std::cout << "Poly: " << poligoni.size() << std::endl;

}

void IOManager::getOcisteGledisteViewUp(const std::string& filePath, glm::vec3& O, glm::vec3& G, glm::vec3& V) {

    std::vector<std::string> objData;
    std::string line;
    std::ifstream file(filePath);
    if (!file) std::cerr << "Could not open file for read!" << std::endl;

    if (file.is_open()) {
        while (std::getline(file, line))
        {
            objData.push_back(line);
        }
        file.close();
    }
    char id;
    float x, y, z;
    for (int i = 0; i < objData.size(); i++) {
        int k = std::sscanf(objData[i].c_str(), " %c %f%f%f", &id, &x, &y, &z);
        std::cout << id << std::endl;
        if (k == 4 && objData[i][0] == 'O' && id == objData[i][0]) {
            O.x = x; O.y = y; O.z = z;
        }
        else if (k == 4 && objData[i][0] == 'G' && id == objData[i][0]) {
            G.x = x; G.y = y; G.z = z;
        }
        else if (k == 4 && objData[i][0] == 'V' && id == objData[i][0]) {
            V.x = x; V.y = y; V.z = z;
        }
        std::cout << std::endl;
    }
}
bool IOManager::readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer) {
    std::ifstream file(filePath, std::ios::binary); //binary format, raw bytes

    if (file.fail()) {
        perror(filePath.c_str());
        return false;
    }

    //how big a file is (buffer in parameters)
    //seek to end of file, determine how many bytes long
    //seek to end
    file.seekg(0, std::ios::end);

    //get the file size
    int fileSize = file.tellg(); // return how many bytes before current location
    file.seekg(0, std::ios::beg);

    //reduce the file size by any heade bytes that might be present
    fileSize -= file.tellg();

    //read in file in buffer

    //first resize to the actual file size
    buffer.resize(fileSize);
    //file >> nesto nesto, ali bolje jejk
    file.read((char*)&(buffer[0]), fileSize);
    file.close();
    return true;

}
bool IOManager::readFileToBuffer(std::string filePath, std::string& buffer) {
    std::ifstream file(filePath, std::ios::binary); //binary format, raw bytes

    if (file.fail()) {
        perror(filePath.c_str());
        return false;
    }

    //how big a file is (buffer in parameters)
    //seek to end of file, determine how many bytes long
    //seek to end
    file.seekg(0, std::ios::end);

    //get the file size
    int fileSize = file.tellg(); // return how many bytes before current location
    file.seekg(0, std::ios::beg);

    //reduce the file size by any heade bytes that might be present
    fileSize -= file.tellg();

    //read in file in buffer

    //first resize to the actual file size
    buffer.resize(fileSize);
    //file >> nesto nesto, ali bolje jejk
    file.read((char*)&(buffer[0]), fileSize);
    file.close();
    return true;

}