#pragma once

// lib
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

// std
#include <string>

namespace cmx
{

class CmxWindow
{
  public:
    CmxWindow(int w, int h, std::string name);
    ~CmxWindow();

    CmxWindow(const CmxWindow &) = delete;
    CmxWindow &operator=(const CmxWindow &) = delete;

    bool shouldClose()
    {
        return glfwWindowShouldClose(window);
    }
    VkExtent2D getExtent()
    {
        return {static_cast<uint32_t>(width), static_cast<uint32_t>(height)};
    }
    bool wasWindowResized()
    {
        return framebufferResized;
    }
    void resetWindowResizedFlag()
    {
        framebufferResized = false;
    }

    void createWindowSurface(VkInstance instance, VkSurfaceKHR *surface);

  private:
    static void framebufferResizeCallback(GLFWwindow *window, int width, int height);
    void initWindow();

    int width;
    int height;
    bool framebufferResized = false;

    std::string windowName;
    GLFWwindow *window;
};
} // namespace cmx