
#ifndef MODEL_H
#define MODEL_H
#pragma once


#include "stb_image.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "mesh.h"
#include "shader_wrapper.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>

#include"vec3.h"
#include"vec2.h"

using namespace std;

unsigned int TextureFromFile(const char* path, const string& directory, bool gamma = false);

class Model
{
public:
    // Данные модели 
    vector<Tex> textures_loaded; // (оптимизация) сохраняем все загруженные текстуры, чтобы убедиться, что они не загружены более одного раза
    vector<Mesh> meshes;
    string directory;
    bool gammaCorrection;

    // Конструктор, который в качестве аргумента использует путь к 3D-модели
    Model(string const& path, bool gamma = false) : gammaCorrection(gamma)
    {
        loadModel(path);
    }

    // Выполняем отрисовку модели и всех её мешей
    void Draw(shader_wrapper shader)
    {
        for (unsigned int i = 0; i < meshes.size(); i++)
            meshes[i].Draw(shader);
    }

private:
    // Загружаем модель с помощью Assimp и сохраняем полученные меши в векторе meshes
    void loadModel(string const& path)
    {
        // Чтение файла с помощью Assimp 
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

        // Проверка на ошибки
        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // если НЕ 0
        {
            cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << endl;
            return;
        }

        // Получение пути к файлу
        directory = path.substr(0, path.find_last_of('/'));

        // Рекурсивная обработка корневого узла Assimp
        processNode(scene->mRootNode, scene);
    }

    // Рекурсивная обработка узла. Обрабатываем каждый отдельный меш, расположенный в узле, и повторяем этот процесс для своих дочерних узлов (если таковы вообще имеются)
    void processNode(aiNode* node, const aiScene* scene)
    {
        // Обрабатываем каждый меш текущего узла
        for (unsigned int i = 0; i < node->mNumMeshes; i++)
        {
            // Узел содержит только индексы объектов в сцене.
            // Сцена же содержит все данные; узел - это лишь способ организации данных
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            meshes.push_back(processMesh(mesh, scene));
        }
        // После того, как мы обработали все меши (если таковые имелись), мы начинаем рекурсивно обрабатывать каждый из дочерних узлов
        for (unsigned int i = 0; i < node->mNumChildren; i++)
        {
            processNode(node->mChildren[i], scene);
        }

    }

    Mesh processMesh(aiMesh* mesh, const aiScene* scene)
    {
        // Данные для заполнения
        vector<Vertex> vertices;
        vector<unsigned int> indices;
        vector<Tex> textures;

        // Цикл по всем вершинам меша
        for (unsigned int i = 0; i < mesh->mNumVertices; i++)
        {
            Vertex vertex;
            vec3 vector; // объявляем промежуточный вектор, т.к. Assimp использует свой собственный векторный класс, который не преобразуется напрямую в тип glm::vec3, поэтому сначала мы передаем данные в этот промежуточный вектор типа glm::vec3

            // Координаты
            vector.set_a1(mesh->mVertices[i].x);
            vector.set_a2(mesh->mVertices[i].y);
            vector.set_a3(mesh->mVertices[i].z);
            vertex.Position = vector;

            // Нормали
            vector.set_a1(mesh->mNormals[i].x);
            vector.set_a2(mesh->mNormals[i].y);
            vector.set_a3(mesh->mNormals[i].z);
            vertex.Normal = vector;

            // Текстурные координаты
            if (mesh->mTextureCoords[0]) // если меш содержит текстурные координаты
            {
                vec2 vec;
                // Вершина может содержать до 8 различных текстурных координат. Мы предполагаем, что мы не будем использовать модели,
                // в которых вершина может содержать несколько текстурных координат, поэтому мы всегда берем первый набор (0)
                vec.set_a1(mesh->mTextureCoords[0][i].x);
                vec.set_a2(mesh->mTextureCoords[0][i].y);
                vertex.TexCoords = vec;
            }
            else
                vertex.TexCoords = vec2(0.0f, 0.0f);

            // Касательный вектор
            vector.set_a1(mesh->mTangents[i].x);
            vector.set_a2(mesh->mTangents[i].y);
            vector.set_a3(mesh->mTangents[i].z);
            vertex.Tangent = vector;

            // Вектор бинормали
            vector.set_a1(mesh->mBitangents[i].x);
            vector.set_a2(mesh->mBitangents[i].y);
            vector.set_a3(mesh->mBitangents[i].z);
            vertex.Bitangent = vector;
            vertices.push_back(vertex);
        }

        // Теперь проходимся по каждой грани меша (грань - это треугольник меша) и извлекаем соответствующие индексы вершин
        for (unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            aiFace face = mesh->mFaces[i];
            // Получаем все индексы граней и сохраняем их в векторе indices
            for (unsigned int j = 0; j < face.mNumIndices; j++)
                indices.push_back(face.mIndices[j]);
        }
        // Обрабатываем материалы
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
        // Мы вводим соглашение об именах сэмплеров в шейдерах. Каждая диффузная текстура будет называться 'texture_diffuseN',
        // где N - это порядковый номер от 1 до MAX_SAMPLER_NUMBER. 
        // То же самое относится и к другим текстурам:
        // диффузная - texture_diffuseN
        // отражения - texture_specularN
        // нормали - texture_normalN

        // 1. Диффузные карты
        vector<Tex> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

        // 2. Карты отражения
        vector<Tex> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

        // 3. Карты нормалей
        std::vector<Tex> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
        textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());

        // 4. Карты высот
        std::vector<Tex> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
        textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

        // Возвращаем mesh-объект, созданный на основе полученных данных
        return Mesh(vertices, indices, textures);
    }

    // Проверяем все текстуры материалов заданного типа и загружам текстуры, если они еще не были загружены.
    // Необходимая информация возвращается в виде struct Texture
    vector<Tex> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName)
    {
        vector<Tex> textures;
        for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
        {
            aiString str;
            mat->GetTexture(type, i, &str);
            // Проверяем, не была ли текстура загружена ранее, и если - да, то пропускаем загрузку новой текстуры и переходим к следующей итерации
            bool skip = false;
            for (unsigned int j = 0; j < textures_loaded.size(); j++)
            {
                if (std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
                {
                    textures.push_back(textures_loaded[j]);
                    skip = true; // текстура с тем же путем к файлу уже загружена, переходим к следующей (оптимизация)
                    break;
                }
            }
            if (!skip)
            {   // Если текстура еще не была загружена - загружаем её
                Tex texture;
                texture.id = TextureFromFile(str.C_Str(), this->directory);
                texture.type = typeName;
                texture.path = str.C_Str();
                textures.push_back(texture);
                textures_loaded.push_back(texture);  // сохраняем её в массиве с уже загруженными текстурами, тем самым гарантируя, что у нас не появятся дубликаты текстур
            }
        }
        return textures;
    }
};

inline unsigned int TextureFromFile(const char* path, const string& directory, bool gamma)
{
    string filename = string(path);
    filename = directory + '/' + filename;

    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}

#endif //MODEL_H