# cmx/systems/rendering/CMakeLists.txt
cmake_minimum_required(VERSION 3.10)

add_library(rendering
    cmx_camera_component.cpp
    cmx_default_render_system.cpp
    cmx_mesh_actor.cpp
    cmx_mesh_component.cpp
    cmx_device.cpp
    cmx_model.cpp
    cmx_buffer.cpp
    cmx_descriptors.cpp
    cmx_pipeline.cpp
    cmx_renderer.cpp
    cmx_swap_chain.cpp
    cmx_window.cpp
)

target_link_libraries(rendering PRIVATE external cmx spdlog glfw vulkan dl pthread X11 Xxf86vm Xrandr Xi)
