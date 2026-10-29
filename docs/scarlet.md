# Native Scarlet backend

This fork adds the `GLFW_PLATFORM_SCARLET` platform, using Scarlet Window Server
(SWS) for windows, display dimensions, focus, resize events, evdev keyboard/mouse
input, and pointer lock. Use `GLFW_NO_API` when creating a Vulkan window.
The keyboard currently uses a US layout; IME composition is not implemented.

Vulkan uses Scarlet's installed `libvulkan.so.1`. Required instance extensions
are `VK_KHR_surface` and the experimental `VK_SGFX_scarlet_surface`, implemented
by the matching Scarlet Vulkan-Loader and SGFX forks. Standard swapchain calls
then present to the SWS window. The private extension values are not assigned
by Khronos, and the SGFX ICD is not Vulkan conformant.

Install one native `/lib/libsws_client_c.so` shared by GLFW and the ICD.
The application must destroy its swapchains and Vulkan surfaces before destroying
the GLFW window. Library loading uses Scarlet's eager/global loader mode.

OpenGL/EGL contexts, clipboard integration, custom cursors, window positioning,
window appearance changes, gamma ramps, and joystick devices are unavailable.
Unsupported operations report GLFW errors. Event waiting polls the SWS queue
with a bounded sleep and honors cross-thread `glfwPostEmptyEvent` wakeups.

Build recipes, pinned dependencies, CI and runtime archives are maintained in
[scarlet-bundle-lwjgl](https://github.com/petitstrawberry/scarlet-bundle-lwjgl).
This repository contains the GLFW port sources. The backend can also be selected
with `GLFW_BUILD_SCARLET` when supplying the native SWS C headers and library to
CMake.
