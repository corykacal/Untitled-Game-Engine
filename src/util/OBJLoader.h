#ifndef OBJLOADER_H
#define OBJLOADER_H

#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>

#include "../models/OBJModel.h"
#include "../util/FileHelper.h"
#include "../models/Model.h"
#include "../../vendor/glm/vec4.hpp"
#include "../../vendor/glm/vec3.hpp"
#include "../../vendor/glm/vec2.hpp"

class OBJLoader {
public:
    static Model* LoadOBJ(const std::string& filePath);

private:
    struct OBJData {
        std::vector<glm::vec3> vertices;
        std::vector<glm::vec2> uvs;
        std::vector<glm::vec3> normals;
        std::vector<Vertex> vertexData;
        std::vector<Index> indices;
    };

    static bool loadDataFromFile(const std::string& filePath, OBJData& data);
    static glm::vec3 readVec3(std::istringstream& iss);
    static glm::vec2 readVec2(std::istringstream& iss);
    static void processFace(std::istringstream& iss, OBJData& data);
    static void addIndex(OBJData& data);
    static void processVertexData(const std::string& vertexData, OBJData& data);
};

#endif // OBJLOADER_H