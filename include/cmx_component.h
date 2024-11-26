#pragma once

#include "cmx_world.h"

// lib
#include <memory>
#include <vulkan/vulkan_core.h>

namespace cmx
{

class Component
{
  public:
    Component() = default;
    ~Component() = default;

    virtual void update() {};
    virtual void render(VkCommandBuffer, VkPipelineLayout){};

    void despawn();

    // getters and setters :: begin
    void setParent(class Actor *actor)
    {
        parent = actor;
    }

    Actor *getParent()
    {
        return parent;
    }
    // getters and setters :: end

    // friend functions
    friend void World::addComponent(std::shared_ptr<Component>);

  protected:
    class Actor *parent;
};

} // namespace cmx
