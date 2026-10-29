//========================================================================
// GLFW 3.5 Scarlet port - www.glfw.org
//------------------------------------------------------------------------
// Copyright (c) 2016 Google Inc.
// Copyright (c) 2016-2017 Camilla Löwy <elmindreda@glfw.org>
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would
//    be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such, and must not
//    be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source
//    distribution.
//
//========================================================================

#include "internal.h"
void _glfwFreeMonitorScarlet(_GLFWmonitor* monitor) { }
void _glfwGetMonitorPosScarlet(_GLFWmonitor* monitor, int* x, int* y)
{ if (x) *x = 0; if (y) *y = 0; }
void _glfwGetMonitorContentScaleScarlet(_GLFWmonitor* monitor, float* x, float* y)
{ uint32_t scale = 1000; sws_get_output_scale(&scale); if (x) *x = scale/1000.f; if (y) *y = scale/1000.f; }
void _glfwGetMonitorWorkareaScarlet(_GLFWmonitor* monitor, int* x, int* y, int* w, int* h)
{ _glfwGetMonitorPosScarlet(monitor, x, y); if (w) *w = _glfw.scarlet.display.width; if (h) *h = _glfw.scarlet.display.height; }
GLFWbool _glfwGetVideoModeScarlet(_GLFWmonitor* monitor, GLFWvidmode* mode)
{
    if (sws_get_display(&_glfw.scarlet.display) < 0) return GLFW_FALSE;
    *mode = (GLFWvidmode) { _glfw.scarlet.display.width, _glfw.scarlet.display.height, 8, 8, 8, 0 };
    return GLFW_TRUE;
}
GLFWvidmode* _glfwGetVideoModesScarlet(_GLFWmonitor* monitor, int* found)
{
    GLFWvidmode* mode = _glfw_calloc(1, sizeof(*mode));
    *found = 0;
    if (!mode) return NULL;
    if (!_glfwGetVideoModeScarlet(monitor, mode)) { _glfw_free(mode); return NULL; }
    *found = 1;
    return mode;
}
GLFWbool _glfwGetGammaRampScarlet(_GLFWmonitor* monitor, GLFWgammaramp* ramp)
{ _glfwInputError(GLFW_FEATURE_UNAVAILABLE, "Scarlet: Gamma ramps are unavailable"); return GLFW_FALSE; }
void _glfwSetGammaRampScarlet(_GLFWmonitor* monitor, const GLFWgammaramp* ramp)
{ _glfwInputError(GLFW_FEATURE_UNAVAILABLE, "Scarlet: Gamma ramps are unavailable"); }
