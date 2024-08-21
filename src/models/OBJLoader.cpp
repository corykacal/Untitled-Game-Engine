#include "OBJLoader.h"

Model* OBJLoader::LoadOBJ(const std::string& filePath) {
    OBJData data;
    if (!loadDataFromFile(filePath, data)) {
        return nullptr;
    }

    return new OBJModel(data.vertexData, data.indices);
}

bool OBJLoader::loadDataFromFile(const std::string& filePath, OBJData& data) {
    std::ifstream file = FileHelper::openFile(filePath);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filePath << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string type;
        iss >> type;

        if (type == "v") {
            data.vertices.push_back(readVec3(iss));
        } else if (type == "vt") {
            data.uvs.push_back(readVec2(iss));
        } else if (type == "vn") {
            data.normals.push_back(readVec3(iss));
        } else if (type == "f") {
            processFace(iss, data);
        }
    }

    return true;
}

glm::vec3 OBJLoader::readVec3(std::istringstream& iss) {
    glm::vec3 vec;
    iss >> vec.x >> vec.y >> vec.z;
    return vec;
}

glm::vec2 OBJLoader::readVec2(std::istringstream& iss) {
    glm::vec2 vec;
    iss >> vec.x >> vec.y;
    return vec;
}

void OBJLoader::processFace(std::istringstream& iss, OBJData& data) {
    std::string v1, v2, v3;
    iss >> v1 >> v2 >> v3;

    addIndex(data);
    addIndex(data);
    addIndex(data);

    processVertexData(v1, data);
    processVertexData(v2, data);
    processVertexData(v3, data);
}

void OBJLoader::addIndex(OBJData& data) {
    data.indices.push_back({static_cast<GLuint>(data.indices.size())});
}

void OBJLoader::processVertexData(const std::string& vertexData, OBJData& data) {
    std::istringstream iss(vertexData);
    std::string token;
    std::vector<int> indices;

    while (std::getline(iss, token, '/')) {
        indices.push_back(token.empty() ? -1 : std::stoi(token) - 1);
    }

    Vertex vertex;
    vertex.Position = data.vertices[indices[0]];
    vertex.TexCoords = (indices[1] != -1) ? data.uvs[indices[1]] : glm::vec2(0.0f, 0.0f);
    vertex.Normal = (indices[2] != -1) ? data.normals[indices[2]] : glm::vec3(0.0f, 1.0f, 0.0f);
    vertex.Color = glm::vec4(1.0f);
    vertex.TexIndex = 0.0f;

    data.vertexData.push_back(vertex);
}