#pragma once
#include<vector>
#include"vec3.h"
#include"vec2.h"
#include"shader_wrapper.h"
#include<string>


struct Vertex {
    vec3 Position;
    vec3 Normal;
    vec2 TexCoords;
    vec3 Tangent;
    vec3 Bitangent;
};

struct Tex {
    unsigned int id;
    std::string type;
    std::string path;
};

class Mesh {
public:
    // mesh-данные
    std::vector<Vertex>       vertices;
    std::vector<unsigned int> indices;
    std::vector<Tex>      textures;

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Tex> textures);
    void Draw(shader_wrapper& shader);
private:
    // Данные для рендеринга
    unsigned int VAO, VBO, EBO;

    void setupMesh();
};

