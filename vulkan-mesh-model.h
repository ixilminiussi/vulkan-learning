#pragma once
#include <assimp/scene.h>
#include <glm/glm.hpp>
#include <vector>

#include "vulkan-mesh.h"

class VulkanMeshModel
{
  public:
    VulkanMeshModel();
    VulkanMeshModel(std::vector<VulkanMesh> meshesP);
    ~VulkanMeshModel();

    size_t getMeshCount() const
    {
        return meshes.size();
    };

    VulkanMesh *getMesh(size_t index);

    glm::mat4 getModel() const
    {
        return model;
    };

    void setModel(glm::mat4 modelP)
    {
        model = modelP;
    }

    void destroyMeshModel();

    static std::vector<std::string> loadMaterials(const aiScene *scene);
    static VulkanMesh loadMesh(vk::PhysicalDevice physicalDeviceP, vk::Device deviceP, vk::Queue transferQueue,
                               vk::CommandPool transferCommandPool, aiMesh *mesh, const aiScene *scene,
                               std::vector<int> matToTex);
    static std::vector<VulkanMesh> loadNode(vk::PhysicalDevice physicalDeviceP, vk::Device deviceP,
                                            vk::Queue transferQueue, vk::CommandPool transferCommandPool, aiNode *node,
                                            const aiScene *scene, std::vector<int> matToTex);

  private:
    std::vector<VulkanMesh> meshes;
    glm::mat4 model;
};
