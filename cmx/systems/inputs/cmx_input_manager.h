#pragma once

#include "cmx_input_action.h"

// lib
#include "tinyxml2.h"
#include <spdlog/spdlog.h>
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#include <glm/ext/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// std
#include <string>
#include <unordered_map>

namespace cmx
{

class InputManager
{
  public:
    InputManager(class CmxWindow &, const std::string &filepath = ".input-manager.xml");
    ~InputManager();

    void save();
    void saveAs(const std::string &);
    void load();

    template <typename T>
    void bindAxis(const std::string &name, void (T::*callbackFunction)(float, glm::vec2), T *instance);
    template <typename T>
    void bindButton(const std::string &name, void (T::*callbackFunction)(float, int), T *instance);
    void addInput(const std::string &name, class InputAction *);
    void pollEvents(float dt);
    void setMouseCapture(bool);

    void renderSettings();

  private:
    const std::string filepath;
    bool gamepadDetected{false};
    std::unordered_map<std::string, class InputAction *> inputDictionary;
    class CmxWindow &window;
};

template <typename T>
inline void InputManager::bindAxis(const std::string &name, void (T::*callbackFunction)(float, glm::vec2), T *instance)
{
    auto mappedInput = inputDictionary.find(name);
    if (mappedInput == inputDictionary.end())
    {
        spdlog::warn("InputManager: attempt at binding non existant input '{0}'", name);
        return;
    }
    else
    {
        mappedInput->second->bind([instance, callbackFunction](float dt, glm::vec2 value) {
            if (instance)
                (instance->*callbackFunction)(dt, value);
            else
                spdlog::warn("InputManager: action being called on deleted object");
        });
        spdlog::info("InputManager: '{0}' bound to new function", name);
    }
}

template <typename T>
inline void InputManager::bindButton(const std::string &name, void (T::*callbackFunction)(float, int), T *instance)
{
    auto mappedInput = inputDictionary.find(name);
    if (mappedInput == inputDictionary.end())
    {
        spdlog::warn("InputManager: attempt at binding non existant input '{0}'", name);
        return;
    }
    else
    {
        mappedInput->second->bind([instance, callbackFunction](float dt, int val) {
            if (instance)
                (instance->*callbackFunction)(dt, val);
            else
                spdlog::warn("InputManager: action being called on deleted object");
        });
        spdlog::info("InputManager: '{0}' bound to new function", name);
    }
}

} // namespace cmx
