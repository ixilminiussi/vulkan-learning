#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <stb_image.h>

#include <stdexcept>
#include <vector>

#include "vulkan-mesh-model.h"
#include "vulkan-mesh.h"
#include "vulkan-utilities.h"

struct ViewProjection
{
    glm::mat4 projection;
    glm::mat4 view;
};

class VulkanRenderer
{
  public:
#ifdef NDEBUG
    static const bool enableValidationLayers = false;
#else
    static const bool enableValidationLayers = true;
#endif
    static const std::vector<const char *> validationLayers;

    VulkanRenderer();
    ~VulkanRenderer();

    int init(GLFWwindow *windowP);
    void draw();
    void clean();

    void updateModel(int modelId, glm::mat4 modelP);
    int createMeshModel(const std::string &filename);

  private:
    GLFWwindow *window;
    vk::Instance instance;
    vk::Queue graphicsQueue; // Handles to queue (no value stored)
    VkDebugUtilsMessengerEXT debugMessenger;

    struct
    {
        vk::PhysicalDevice physicalDevice;
        vk::Device logicalDevice;
    } mainDevice;

    vk::SurfaceKHR surface;
    vk::Queue presentationQueue;
    vk::SwapchainKHR swapchain;
    vk::Format swapchainImageFormat;
    vk::Extent2D swapchainExtent;
    std::vector<SwapchainImage> swapchainImages;

    vk::PipelineLayout pipelineLayout;
    vk::RenderPass renderPass;
    vk::Pipeline graphicsPipeline;

    std::vector<vk::Framebuffer> swapchainFramebuffers;
    vk::CommandPool graphicsCommandPool;
    std::vector<vk::CommandBuffer> commandBuffers;

    std::vector<vk::Semaphore> imageAvailable;
    std::vector<vk::Semaphore> renderFinished;
    const int MAX_FRAME_DRAWS = 2; // Should be less than the number of swapchain images, here 3 (could cause bugs)
    int currentFrame = 0;
    std::vector<vk::Fence> drawFences;

    std::vector<VulkanMesh> meshes;

    vk::DescriptorSetLayout descriptorSetLayout;
    std::vector<vk::Buffer> vpUniformBuffer;
    std::vector<vk::DeviceMemory> vpUniformBufferMemory;
    vk::DescriptorPool descriptorPool;
    std::vector<vk::DescriptorSet> descriptorSets;

    ViewProjection viewProjection;
    vk::DeviceSize minUniformBufferOffet;
    size_t modelUniformAlignement;
    Model *modelTransferSpace;
    const int MAX_OBJECTS = 20;
    std::vector<vk::Buffer> modelUniformBufferDynamic;
    std::vector<vk::DeviceMemory> modelUniformBufferMemoryDynamic;

    vk::PushConstantRange pushConstantRange;

    vk::Image depthBufferImage;
    vk::DeviceMemory depthBufferImageMemory;
    vk::ImageView depthBufferImageView;

    std::vector<VkImage> textureImages;
    std::vector<vk::ImageView> textureImageViews;
    std::vector<VkDeviceMemory> textureImageMemory;

    vk::Sampler textureSampler;
    vk::DescriptorPool samplerDescriptorPool;
    vk::DescriptorSetLayout samplerDescriptorSetLayout;
    std::vector<vk::DescriptorSet> samplerDescriptorSets;

    std::vector<VulkanMeshModel> meshModels;

    vk::SampleCountFlagBits msaaSamples{vk::SampleCountFlagBits::e1};
    vk::Image colorImage;
    vk::DeviceMemory colorImageMemory;
    vk::ImageView colorImageView;

    // Instance
    void createInstance();
    bool checkInstanceExtensionSupport(const std::vector<const char *> &checkExtensions);
    bool checkValidationLayerSupport();
    std::vector<const char *> getRequiredExtensions();

    // Debug
    void setupDebugMessenger();
    void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT &createInfo);
    VkResult createDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT *pCreateInfo,
                                          const VkAllocationCallbacks *pAllocator,
                                          VkDebugUtilsMessengerEXT *pDebugMessenger);
    void destroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger,
                                       const VkAllocationCallbacks *pAllocator);

    // Devices
    void getPhysicalDevice();
    bool checkDeviceSuitable(vk::PhysicalDevice device);
    QueueFamilyIndices getQueueFamilies(vk::PhysicalDevice device);
    void createLogicalDevice();

    // Surface and swapchain
    vk::SurfaceKHR createSurface();
    bool checkDeviceExtensionSupport(vk::PhysicalDevice device);
    SwapchainDetails getSwapchainDetails(vk::PhysicalDevice device);
    void createSwapchain();
    vk::SurfaceFormatKHR chooseBestSurfaceFormat(const std::vector<vk::SurfaceFormatKHR> &formats);
    vk::PresentModeKHR chooseBestPresentationMode(const std::vector<vk::PresentModeKHR> &presentationModes);
    vk::Extent2D chooseSwapExtent(const vk::SurfaceCapabilitiesKHR &surfaceCapabilities);
    vk::ImageView createImageView(vk::Image image, vk::Format format, vk::ImageAspectFlagBits aspectFlags,
                                  uint32_t mipLevels);

    // Graphics pipeline
    void createGraphicsPipeline();
    vk::ShaderModule createShaderModule(const std::vector<char> &code);
    void createRenderPass();

    // Buffers
    void createFramebuffers();
    void createGraphicsCommandPool();
    void createGraphicsCommandBuffers();
    void recordCommands(uint32_t currentImage);

    // Descriptor sets
    void createDescriptorSetLayout();
    void createUniformBuffers();
    void createDescriptorPool();
    void createDescriptorSets();
    void updateUniformBuffers(uint32_t imageIndex);

    // Data alignment and dynamic buffers
    void allocateDynamicBufferTransferSpace();

    // Push constants
    void createPushConstantRange();

    // Depth
    void createDepthBufferImage();
    vk::Image createImage(uint32_t width, uint32_t height, uint32_t mipLevels, vk::SampleCountFlagBits numSamples,
                          vk::Format format, vk::ImageTiling tiling, vk::ImageUsageFlags useFlags,
                          vk::MemoryPropertyFlags propFlags, vk::DeviceMemory *imageMemory);
    vk::Format chooseSupportedFormat(const std::vector<vk::Format> &formats, vk::ImageTiling tiling,
                                     vk::FormatFeatureFlags featureFlags);

    // Draw
    void createSynchronisation();

    // Textures
    stbi_uc *loadTextureFile(const std::string &filename, int *width, int *height, vk::DeviceSize *imageSize);
    int createTextureImage(const std::string &filename, uint32_t &mipLevels);
    int createTexture(const std::string &filename);

    // Sampler
    void createTextureSampler();
    int createTextureDescriptor(vk::ImageView textureImageView);
    void createColorBufferImage();
};
