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
#include <string.h>

GLFWbool _glfwConnectScarlet(int platformID, _GLFWplatform* platform)
{
    const _GLFWplatform scarlet =
    {
        .platformID = GLFW_PLATFORM_SCARLET,
        .init = _glfwInitScarlet,
        .terminate = _glfwTerminateScarlet,
        .getCursorPos = _glfwGetCursorPosScarlet,
        .setCursorPos = _glfwSetCursorPosScarlet,
        .setCursorMode = _glfwSetCursorModeScarlet,
        .setRawMouseMotion = _glfwSetRawMouseMotionScarlet,
        .rawMouseMotionSupported = _glfwRawMouseMotionSupportedScarlet,
        .createCursor = _glfwCreateCursorScarlet,
        .createStandardCursor = _glfwCreateStandardCursorScarlet,
        .destroyCursor = _glfwDestroyCursorScarlet,
        .setCursor = _glfwSetCursorScarlet,
        .getScancodeName = _glfwGetScancodeNameScarlet,
        .getKeyScancode = _glfwGetKeyScancodeScarlet,
        .setClipboardString = _glfwSetClipboardStringScarlet,
        .getClipboardString = _glfwGetClipboardStringScarlet,
        .initJoysticks = _glfwInitJoysticksNull,
        .terminateJoysticks = _glfwTerminateJoysticksNull,
        .pollJoystick = _glfwPollJoystickNull,
        .getMappingName = _glfwGetMappingNameNull,
        .updateGamepadGUID = _glfwUpdateGamepadGUIDNull,
        .freeMonitor = _glfwFreeMonitorScarlet,
        .getMonitorPos = _glfwGetMonitorPosScarlet,
        .getMonitorContentScale = _glfwGetMonitorContentScaleScarlet,
        .getMonitorWorkarea = _glfwGetMonitorWorkareaScarlet,
        .getVideoModes = _glfwGetVideoModesScarlet,
        .getVideoMode = _glfwGetVideoModeScarlet,
        .getGammaRamp = _glfwGetGammaRampScarlet,
        .setGammaRamp = _glfwSetGammaRampScarlet,
        .createWindow = _glfwCreateWindowScarlet,
        .destroyWindow = _glfwDestroyWindowScarlet,
        .setWindowTitle = _glfwSetWindowTitleScarlet,
        .setWindowIcon = _glfwSetWindowIconScarlet,
        .getWindowPos = _glfwGetWindowPosScarlet,
        .setWindowPos = _glfwSetWindowPosScarlet,
        .getWindowSize = _glfwGetWindowSizeScarlet,
        .setWindowSize = _glfwSetWindowSizeScarlet,
        .setWindowSizeLimits = _glfwSetWindowSizeLimitsScarlet,
        .setWindowAspectRatio = _glfwSetWindowAspectRatioScarlet,
        .getFramebufferSize = _glfwGetFramebufferSizeScarlet,
        .getWindowFrameSize = _glfwGetWindowFrameSizeScarlet,
        .getWindowContentScale = _glfwGetWindowContentScaleScarlet,
        .iconifyWindow = _glfwIconifyWindowScarlet,
        .restoreWindow = _glfwRestoreWindowScarlet,
        .maximizeWindow = _glfwMaximizeWindowScarlet,
        .showWindow = _glfwShowWindowScarlet,
        .hideWindow = _glfwHideWindowScarlet,
        .requestWindowAttention = _glfwRequestWindowAttentionScarlet,
        .focusWindow = _glfwFocusWindowScarlet,
        .setWindowMonitor = _glfwSetWindowMonitorScarlet,
        .windowFocused = _glfwWindowFocusedScarlet,
        .windowIconified = _glfwWindowIconifiedScarlet,
        .windowVisible = _glfwWindowVisibleScarlet,
        .windowMaximized = _glfwWindowMaximizedScarlet,
        .windowHovered = _glfwWindowHoveredScarlet,
        .framebufferTransparent = _glfwFramebufferTransparentScarlet,
        .getWindowOpacity = _glfwGetWindowOpacityScarlet,
        .setWindowResizable = _glfwSetWindowResizableScarlet,
        .setWindowDecorated = _glfwSetWindowDecoratedScarlet,
        .setWindowFloating = _glfwSetWindowFloatingScarlet,
        .setWindowOpacity = _glfwSetWindowOpacityScarlet,
        .setWindowMousePassthrough = _glfwSetWindowMousePassthroughScarlet,
        .pollEvents = _glfwPollEventsScarlet,
        .waitEvents = _glfwWaitEventsScarlet,
        .waitEventsTimeout = _glfwWaitEventsTimeoutScarlet,
        .postEmptyEvent = _glfwPostEmptyEventScarlet,
        .getEGLPlatform = _glfwGetEGLPlatformScarlet,
        .getEGLNativeDisplay = _glfwGetEGLNativeDisplayScarlet,
        .getEGLNativeWindow = _glfwGetEGLNativeWindowScarlet,
        .getRequiredInstanceExtensions = _glfwGetRequiredInstanceExtensionsScarlet,
        .getPhysicalDevicePresentationSupport = _glfwGetPhysicalDevicePresentationSupportScarlet,
        .createWindowSurface = _glfwCreateWindowSurfaceScarlet
    };

    *platform = scarlet;
    return GLFW_TRUE;
}

int _glfwInitScarlet(void)
{
    if (sws_get_display(&_glfw.scarlet.display) < 0)
    {
        _glfwInputError(GLFW_PLATFORM_ERROR, "Scarlet: Cannot connect to SWS");
        return GLFW_FALSE;
    }
    memset(_glfw.scarlet.keycodes, -1, sizeof(_glfw.scarlet.keycodes));
    memset(_glfw.scarlet.scancodes, -1, sizeof(_glfw.scarlet.scancodes));
    _glfw.scarlet.keycodes[1] = GLFW_KEY_ESCAPE;
    _glfw.scarlet.keycodes[2] = GLFW_KEY_1;
    _glfw.scarlet.keycodes[3] = GLFW_KEY_2;
    _glfw.scarlet.keycodes[4] = GLFW_KEY_3;
    _glfw.scarlet.keycodes[5] = GLFW_KEY_4;
    _glfw.scarlet.keycodes[6] = GLFW_KEY_5;
    _glfw.scarlet.keycodes[7] = GLFW_KEY_6;
    _glfw.scarlet.keycodes[8] = GLFW_KEY_7;
    _glfw.scarlet.keycodes[9] = GLFW_KEY_8;
    _glfw.scarlet.keycodes[10] = GLFW_KEY_9;
    _glfw.scarlet.keycodes[11] = GLFW_KEY_0;
    _glfw.scarlet.keycodes[12] = GLFW_KEY_MINUS;
    _glfw.scarlet.keycodes[13] = GLFW_KEY_EQUAL;
    _glfw.scarlet.keycodes[14] = GLFW_KEY_BACKSPACE;
    _glfw.scarlet.keycodes[15] = GLFW_KEY_TAB;
    _glfw.scarlet.keycodes[16] = GLFW_KEY_Q;
    _glfw.scarlet.keycodes[17] = GLFW_KEY_W;
    _glfw.scarlet.keycodes[18] = GLFW_KEY_E;
    _glfw.scarlet.keycodes[19] = GLFW_KEY_R;
    _glfw.scarlet.keycodes[20] = GLFW_KEY_T;
    _glfw.scarlet.keycodes[21] = GLFW_KEY_Y;
    _glfw.scarlet.keycodes[22] = GLFW_KEY_U;
    _glfw.scarlet.keycodes[23] = GLFW_KEY_I;
    _glfw.scarlet.keycodes[24] = GLFW_KEY_O;
    _glfw.scarlet.keycodes[25] = GLFW_KEY_P;
    _glfw.scarlet.keycodes[26] = GLFW_KEY_LEFT_BRACKET;
    _glfw.scarlet.keycodes[27] = GLFW_KEY_RIGHT_BRACKET;
    _glfw.scarlet.keycodes[28] = GLFW_KEY_ENTER;
    _glfw.scarlet.keycodes[29] = GLFW_KEY_LEFT_CONTROL;
    _glfw.scarlet.keycodes[30] = GLFW_KEY_A;
    _glfw.scarlet.keycodes[31] = GLFW_KEY_S;
    _glfw.scarlet.keycodes[32] = GLFW_KEY_D;
    _glfw.scarlet.keycodes[33] = GLFW_KEY_F;
    _glfw.scarlet.keycodes[34] = GLFW_KEY_G;
    _glfw.scarlet.keycodes[35] = GLFW_KEY_H;
    _glfw.scarlet.keycodes[36] = GLFW_KEY_J;
    _glfw.scarlet.keycodes[37] = GLFW_KEY_K;
    _glfw.scarlet.keycodes[38] = GLFW_KEY_L;
    _glfw.scarlet.keycodes[39] = GLFW_KEY_SEMICOLON;
    _glfw.scarlet.keycodes[40] = GLFW_KEY_APOSTROPHE;
    _glfw.scarlet.keycodes[41] = GLFW_KEY_GRAVE_ACCENT;
    _glfw.scarlet.keycodes[42] = GLFW_KEY_LEFT_SHIFT;
    _glfw.scarlet.keycodes[43] = GLFW_KEY_BACKSLASH;
    _glfw.scarlet.keycodes[44] = GLFW_KEY_Z;
    _glfw.scarlet.keycodes[45] = GLFW_KEY_X;
    _glfw.scarlet.keycodes[46] = GLFW_KEY_C;
    _glfw.scarlet.keycodes[47] = GLFW_KEY_V;
    _glfw.scarlet.keycodes[48] = GLFW_KEY_B;
    _glfw.scarlet.keycodes[49] = GLFW_KEY_N;
    _glfw.scarlet.keycodes[50] = GLFW_KEY_M;
    _glfw.scarlet.keycodes[51] = GLFW_KEY_COMMA;
    _glfw.scarlet.keycodes[52] = GLFW_KEY_PERIOD;
    _glfw.scarlet.keycodes[53] = GLFW_KEY_SLASH;
    _glfw.scarlet.keycodes[54] = GLFW_KEY_RIGHT_SHIFT;
    _glfw.scarlet.keycodes[55] = GLFW_KEY_KP_MULTIPLY;
    _glfw.scarlet.keycodes[56] = GLFW_KEY_LEFT_ALT;
    _glfw.scarlet.keycodes[57] = GLFW_KEY_SPACE;
    _glfw.scarlet.keycodes[58] = GLFW_KEY_CAPS_LOCK;
    _glfw.scarlet.keycodes[59] = GLFW_KEY_F1;
    _glfw.scarlet.keycodes[60] = GLFW_KEY_F2;
    _glfw.scarlet.keycodes[61] = GLFW_KEY_F3;
    _glfw.scarlet.keycodes[62] = GLFW_KEY_F4;
    _glfw.scarlet.keycodes[63] = GLFW_KEY_F5;
    _glfw.scarlet.keycodes[64] = GLFW_KEY_F6;
    _glfw.scarlet.keycodes[65] = GLFW_KEY_F7;
    _glfw.scarlet.keycodes[66] = GLFW_KEY_F8;
    _glfw.scarlet.keycodes[67] = GLFW_KEY_F9;
    _glfw.scarlet.keycodes[68] = GLFW_KEY_F10;
    _glfw.scarlet.keycodes[69] = GLFW_KEY_NUM_LOCK;
    _glfw.scarlet.keycodes[70] = GLFW_KEY_SCROLL_LOCK;
    _glfw.scarlet.keycodes[71] = GLFW_KEY_KP_7;
    _glfw.scarlet.keycodes[72] = GLFW_KEY_KP_8;
    _glfw.scarlet.keycodes[73] = GLFW_KEY_KP_9;
    _glfw.scarlet.keycodes[74] = GLFW_KEY_KP_SUBTRACT;
    _glfw.scarlet.keycodes[75] = GLFW_KEY_KP_4;
    _glfw.scarlet.keycodes[76] = GLFW_KEY_KP_5;
    _glfw.scarlet.keycodes[77] = GLFW_KEY_KP_6;
    _glfw.scarlet.keycodes[78] = GLFW_KEY_KP_ADD;
    _glfw.scarlet.keycodes[79] = GLFW_KEY_KP_1;
    _glfw.scarlet.keycodes[80] = GLFW_KEY_KP_2;
    _glfw.scarlet.keycodes[81] = GLFW_KEY_KP_3;
    _glfw.scarlet.keycodes[82] = GLFW_KEY_KP_0;
    _glfw.scarlet.keycodes[83] = GLFW_KEY_KP_DECIMAL;
    _glfw.scarlet.keycodes[87] = GLFW_KEY_F11;
    _glfw.scarlet.keycodes[88] = GLFW_KEY_F12;
    _glfw.scarlet.keycodes[96] = GLFW_KEY_KP_ENTER;
    _glfw.scarlet.keycodes[97] = GLFW_KEY_RIGHT_CONTROL;
    _glfw.scarlet.keycodes[98] = GLFW_KEY_KP_DIVIDE;
    _glfw.scarlet.keycodes[99] = GLFW_KEY_PRINT_SCREEN;
    _glfw.scarlet.keycodes[100] = GLFW_KEY_RIGHT_ALT;
    _glfw.scarlet.keycodes[102] = GLFW_KEY_HOME;
    _glfw.scarlet.keycodes[103] = GLFW_KEY_UP;
    _glfw.scarlet.keycodes[104] = GLFW_KEY_PAGE_UP;
    _glfw.scarlet.keycodes[105] = GLFW_KEY_LEFT;
    _glfw.scarlet.keycodes[106] = GLFW_KEY_RIGHT;
    _glfw.scarlet.keycodes[107] = GLFW_KEY_END;
    _glfw.scarlet.keycodes[108] = GLFW_KEY_DOWN;
    _glfw.scarlet.keycodes[109] = GLFW_KEY_PAGE_DOWN;
    _glfw.scarlet.keycodes[110] = GLFW_KEY_INSERT;
    _glfw.scarlet.keycodes[111] = GLFW_KEY_DELETE;
    _glfw.scarlet.keycodes[119] = GLFW_KEY_PAUSE;
    _glfw.scarlet.keycodes[125] = GLFW_KEY_LEFT_SUPER;
    _glfw.scarlet.keycodes[126] = GLFW_KEY_RIGHT_SUPER;
    _glfw.scarlet.keycodes[127] = GLFW_KEY_MENU;
    for (int sc = 0; sc < 256; sc++)
        if (_glfw.scarlet.keycodes[sc] >= 0)
            _glfw.scarlet.scancodes[_glfw.scarlet.keycodes[sc]] = sc;
    _GLFWmonitor* monitor = _glfwAllocMonitor("Scarlet SWS", 0, 0);
    if (!monitor) return GLFW_FALSE;
    _glfwInputMonitor(monitor, GLFW_CONNECTED, _GLFW_INSERT_FIRST);
    return GLFW_TRUE;
}
void _glfwTerminateScarlet(void) { }
