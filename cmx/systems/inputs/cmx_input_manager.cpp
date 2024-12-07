#include "cmx_input_manager.h"

// cmx
#include "cmx_input_action.h"
#include "cmx_window.h"

// lib
#include <GLFW/glfw3.h>

// std
#include <cstdlib>
#include <spdlog/spdlog.h>
#include <unordered_map>

namespace cmx
{

InputManager::InputManager(CmxWindow &window, const std::unordered_map<std::string, InputAction *> &inputDictionary)
    : window{window}, inputDictionary{inputDictionary}
{
    gamepadDetected = glfwJoystickPresent(GLFW_JOYSTICK_1);
    glfwSetInputMode(window.getGLFWwindow(), GLFW_STICKY_KEYS, GLFW_TRUE);
}

InputManager::~InputManager()
{
    for (auto &pair : inputDictionary)
    {
        delete pair.second;
    }
    inputDictionary.clear();
}

void InputManager::addInput(const std::string &name, InputAction *newInput)
{
    inputDictionary[name] = newInput;
}

void InputManager::pollEvents(float dt)
{
    glfwPollEvents();

    for (auto &[name, input] : inputDictionary)
    {
        if (auto button = static_cast<ButtonAction *>(input))
        {
            button->poll(window, dt);
        }
        if (auto button = static_cast<AxisAction *>(input))
        {
            button->poll(window, dt);
        }
    }
}

void InputManager::setMouseCapture(bool b)
{
    (b) ? glfwSetInputMode(window.getGLFWwindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED)
        : glfwSetInputMode(window.getGLFWwindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

} // namespace cmx
