#pragma once

#include <vector>
#include <memory>
#include <experimental/filesystem>
#include <unordered_map>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>

#include "Rendering/Mesh.h"
#include "Rendering/Texture.h"
#include "Rendering/Uniform.h"
#include "Rendering/Camera.h"

class ShaderProgram;

struct PhongGPUMaterial
{
    uint64_t diffTexture = -1;
    uint64_t specTexture = -1;
    uint64_t opacityTexture = -1;
    float opacity = 1.0f;
    float Ns = -1.0f;
    glm::vec4 diffColor;
    glm::vec4 specColor;
    glm::vec4 emissiveColor;
};


class ModelImporter
{
public:
    explicit ModelImporter(const std::experimental::filesystem::path& filename);
    ModelImporter(const std::experimental::filesystem::path& filename, int test);

    std::vector<std::shared_ptr<Mesh>> getMeshes() const;

    void draw(const ShaderProgram& sp) const;
    void multiDraw(const ShaderProgram& sp) const;
    void drawCulled(const ShaderProgram& sp, Camera& cam, float angle, float ratio, float near, float far) const;

    void registerUniforms(ShaderProgram& sp) const;

private:
    Assimp::Importer m_importer;
    const aiScene* m_scene;
    std::vector<std::shared_ptr<Mesh>> m_meshes;
    std::unordered_map<std::string, std::shared_ptr<Texture>> m_texturemap;
    std::vector<PhongGPUMaterial> m_gpuMaterials;
    Buffer m_gpuMaterialBuffer;

    std::vector<unsigned> m_gpuMaterialIndices;
    Buffer m_gpuMaterialIndicesBuffer;

    std::vector<glm::mat4> m_modelMatrices;
    Buffer m_modelMatrixBuffer;

    std::shared_ptr<Uniform<int>> m_meshIndexUniform;
    std::shared_ptr<Uniform<int>> m_materialIndexUniform;

    // multi-draw buffers
    std::vector<GLsizei> m_counts;
    std::vector<uint64_t> m_starts;
    std::vector<int> m_baseVertexOffsets;
    std::vector<unsigned> m_allTheIndices;
    std::vector<glm::vec3> m_allTheVertices;
    std::vector<glm::vec3> m_allTheNormals;
    std::vector<glm::vec3> m_allTheTexCoords;

    Buffer m_multiDrawIndexBuffer;
    Buffer m_multiDrawVertexBuffer;
    Buffer m_multiDrawNormalBuffer;
    Buffer m_multiDrawTexCoordBuffer;
    VertexArray m_multiDrawVao;
};
