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

#include <sws_client.h>
#include <scarlet_ui_window.h>
#define GLFW_SCARLET_WINDOW_STATE _GLFWwindowScarlet scarlet;
#define GLFW_SCARLET_LIBRARY_WINDOW_STATE _GLFWlibraryScarlet scarlet;
typedef struct _GLFWwindowScarlet {
    uint32_t id;
    int width, height, fbwidth, fbheight, lockMods;
    int reportedWidth, reportedHeight, reportedFbWidth, reportedFbHeight;
    uint32_t reportedScale;
    int outerX, outerY;
    unsigned int clientButtons, frameButtons;
    SwsSceneGeometry geometry;
    ScarletUiFrame* frame;
    GLFWbool visible, focused, iconified, maximized, entered;
    double xcursor, ycursor;
} _GLFWwindowScarlet;
typedef struct _GLFWlibraryScarlet {
    SwsDisplay display;
    void* ui;
    uint32_t (*frameAbi)(void);
    int32_t (*frameInsets)(uint32_t,uint32_t,ScarletUiInsets*);
    ScarletUiFrame* (*frameCreate)(void);
    int32_t (*frameConfigure)(ScarletUiFrame*,const char*,uint32_t,uint32_t,uint32_t,uint32_t);
    int32_t (*frameRender)(ScarletUiFrame*,ScarletUiFrameView*);
    int32_t (*framePointer)(ScarletUiFrame*,uint32_t,int32_t,int32_t,uint32_t*);
    int32_t (*frameDirty)(ScarletUiFrame*);
    void (*frameDestroy)(ScarletUiFrame*);
    int keycodes[256], scancodes[GLFW_KEY_LAST + 1];
    unsigned int wakeup;
} _GLFWlibraryScarlet;


GLFWbool _glfwConnectScarlet(int platformID, _GLFWplatform* platform);
int _glfwInitScarlet(void);
void _glfwTerminateScarlet(void);

void _glfwFreeMonitorScarlet(_GLFWmonitor* monitor);
void _glfwGetMonitorPosScarlet(_GLFWmonitor* monitor, int* xpos, int* ypos);
void _glfwGetMonitorContentScaleScarlet(_GLFWmonitor* monitor, float* xscale, float* yscale);
void _glfwGetMonitorWorkareaScarlet(_GLFWmonitor* monitor, int* xpos, int* ypos, int* width, int* height);
GLFWvidmode* _glfwGetVideoModesScarlet(_GLFWmonitor* monitor, int* found);
GLFWbool _glfwGetVideoModeScarlet(_GLFWmonitor* monitor, GLFWvidmode* mode);
GLFWbool _glfwGetGammaRampScarlet(_GLFWmonitor* monitor, GLFWgammaramp* ramp);
void _glfwSetGammaRampScarlet(_GLFWmonitor* monitor, const GLFWgammaramp* ramp);

GLFWbool _glfwCreateWindowScarlet(_GLFWwindow* window, const _GLFWwndconfig* wndconfig, const _GLFWctxconfig* ctxconfig, const _GLFWfbconfig* fbconfig);
void _glfwDestroyWindowScarlet(_GLFWwindow* window);
void _glfwSetWindowTitleScarlet(_GLFWwindow* window, const char* title);
void _glfwSetWindowIconScarlet(_GLFWwindow* window, int count, const GLFWimage* images);
void _glfwSetWindowMonitorScarlet(_GLFWwindow* window, _GLFWmonitor* monitor, int xpos, int ypos, int width, int height, int refreshRate);
void _glfwGetWindowPosScarlet(_GLFWwindow* window, int* xpos, int* ypos);
void _glfwSetWindowPosScarlet(_GLFWwindow* window, int xpos, int ypos);
void _glfwGetWindowSizeScarlet(_GLFWwindow* window, int* width, int* height);
void _glfwSetWindowSizeScarlet(_GLFWwindow* window, int width, int height);
void _glfwSetWindowSizeLimitsScarlet(_GLFWwindow* window, int minwidth, int minheight, int maxwidth, int maxheight);
void _glfwSetWindowAspectRatioScarlet(_GLFWwindow* window, int n, int d);
void _glfwGetFramebufferSizeScarlet(_GLFWwindow* window, int* width, int* height);
void _glfwGetWindowFrameSizeScarlet(_GLFWwindow* window, int* left, int* top, int* right, int* bottom);
void _glfwGetWindowContentScaleScarlet(_GLFWwindow* window, float* xscale, float* yscale);
void _glfwIconifyWindowScarlet(_GLFWwindow* window);
void _glfwRestoreWindowScarlet(_GLFWwindow* window);
void _glfwMaximizeWindowScarlet(_GLFWwindow* window);
GLFWbool _glfwWindowMaximizedScarlet(_GLFWwindow* window);
GLFWbool _glfwWindowHoveredScarlet(_GLFWwindow* window);
GLFWbool _glfwFramebufferTransparentScarlet(_GLFWwindow* window);
void _glfwSetWindowResizableScarlet(_GLFWwindow* window, GLFWbool enabled);
void _glfwSetWindowDecoratedScarlet(_GLFWwindow* window, GLFWbool enabled);
void _glfwSetWindowFloatingScarlet(_GLFWwindow* window, GLFWbool enabled);
void _glfwSetWindowMousePassthroughScarlet(_GLFWwindow* window, GLFWbool enabled);
float _glfwGetWindowOpacityScarlet(_GLFWwindow* window);
void _glfwSetWindowOpacityScarlet(_GLFWwindow* window, float opacity);
void _glfwSetRawMouseMotionScarlet(_GLFWwindow *window, GLFWbool enabled);
GLFWbool _glfwRawMouseMotionSupportedScarlet(void);
void _glfwShowWindowScarlet(_GLFWwindow* window);
void _glfwRequestWindowAttentionScarlet(_GLFWwindow* window);
void _glfwHideWindowScarlet(_GLFWwindow* window);
void _glfwFocusWindowScarlet(_GLFWwindow* window);
GLFWbool _glfwWindowFocusedScarlet(_GLFWwindow* window);
GLFWbool _glfwWindowIconifiedScarlet(_GLFWwindow* window);
GLFWbool _glfwWindowVisibleScarlet(_GLFWwindow* window);
void _glfwPollEventsScarlet(void);
void _glfwWaitEventsScarlet(void);
void _glfwWaitEventsTimeoutScarlet(double timeout);
void _glfwPostEmptyEventScarlet(void);
void _glfwGetCursorPosScarlet(_GLFWwindow* window, double* xpos, double* ypos);
void _glfwSetCursorPosScarlet(_GLFWwindow* window, double x, double y);
void _glfwSetCursorModeScarlet(_GLFWwindow* window, int mode);
GLFWbool _glfwCreateCursorScarlet(_GLFWcursor* cursor, const GLFWimage* image, int xhot, int yhot);
GLFWbool _glfwCreateStandardCursorScarlet(_GLFWcursor* cursor, int shape);
void _glfwDestroyCursorScarlet(_GLFWcursor* cursor);
void _glfwSetCursorScarlet(_GLFWwindow* window, _GLFWcursor* cursor);
void _glfwSetClipboardStringScarlet(const char* string);
const char* _glfwGetClipboardStringScarlet(void);
const char* _glfwGetScancodeNameScarlet(int scancode);
int _glfwGetKeyScancodeScarlet(int key);

EGLenum _glfwGetEGLPlatformScarlet(EGLint** attribs);
EGLNativeDisplayType _glfwGetEGLNativeDisplayScarlet(void);
EGLNativeWindowType _glfwGetEGLNativeWindowScarlet(_GLFWwindow* window);

void _glfwGetRequiredInstanceExtensionsScarlet(char** extensions);
GLFWbool _glfwGetPhysicalDevicePresentationSupportScarlet(VkInstance instance, VkPhysicalDevice device, uint32_t queuefamily);
VkResult _glfwCreateWindowSurfaceScarlet(VkInstance instance, _GLFWwindow* window, const VkAllocationCallbacks* allocator, VkSurfaceKHR* surface);

