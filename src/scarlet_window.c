// Scarlet SWS backend. Copyright (c) 2026 Scarlet contributors.
// Distributed under the zlib/libpng license; see LICENSE.md.
#include "internal.h"
#include <string.h>
#include <time.h>

static void unavailable(const char* feature)
{ _glfwInputError(GLFW_FEATURE_UNAVAILABLE, "Scarlet: %s is unavailable", feature); }
static GLFWbool checked(int result, const char* operation)
{
    if (result >= 0) return GLFW_TRUE;
    _glfwInputError(GLFW_PLATFORM_ERROR, "Scarlet: %s failed (%d)", operation, result);
    return GLFW_FALSE;
}
static void resize(_GLFWwindow* window, int width, int height)
{
    if (window->scarlet.width == width && window->scarlet.height == height) return;
    window->scarlet.width = width; window->scarlet.height = height;
    _glfwInputFramebufferSize(window, width, height);
    _glfwInputWindowSize(window, width, height);
}
GLFWbool _glfwCreateWindowScarlet(_GLFWwindow* window, const _GLFWwndconfig* config,
                                 const _GLFWctxconfig* context, const _GLFWfbconfig* fb)
{
    if (context->client != GLFW_NO_API)
    {
        _glfwInputError(GLFW_API_UNAVAILABLE, "Scarlet: OpenGL contexts are unavailable; use GLFW_NO_API for Vulkan");
        return GLFW_FALSE;
    }
    if (!checked(sws_window_create_ex("org.glfw.application", "GLFW", config->width,
                     config->height, config->resizable, &window->scarlet.id), "create window"))
        return GLFW_FALSE;
    window->scarlet.width = config->width;
    window->scarlet.height = config->height;
    window->scarlet.visible = GLFW_TRUE;
    if (window->monitor && !checked(sws_window_fullscreen(window->scarlet.id, 1), "fullscreen"))
        return GLFW_FALSE;
    if (window->monitor) _glfwInputMonitorWindow(window->monitor, window);
    if (!config->visible) _glfwHideWindowScarlet(window);
    if (config->maximized) _glfwMaximizeWindowScarlet(window);
    if (config->focused && config->visible) _glfwFocusWindowScarlet(window);
    return GLFW_TRUE;
}
void _glfwDestroyWindowScarlet(_GLFWwindow* window)
{
    if (window->scarlet.id) checked(sws_window_destroy(window->scarlet.id), "destroy window");
    if (window->monitor && window->monitor->window == window) _glfwInputMonitorWindow(window->monitor, NULL);
    window->scarlet.id = 0;
}
void _glfwSetWindowTitleScarlet(_GLFWwindow* window, const char* title)
{ checked(sws_window_title(window->scarlet.id, title), "set title"); }
void _glfwGetWindowSizeScarlet(_GLFWwindow* window, int* width, int* height)
{
    uint32_t w, h;
    if (checked(sws_window_size(window->scarlet.id, &w, &h), "get size"))
    { window->scarlet.width = w; window->scarlet.height = h; }
    if (width) *width = window->scarlet.width;
    if (height) *height = window->scarlet.height;
}
void _glfwGetFramebufferSizeScarlet(_GLFWwindow* window, int* w, int* h)
{ _glfwGetWindowSizeScarlet(window, w, h); }
void _glfwSetWindowSizeScarlet(_GLFWwindow* window, int w, int h)
{ if (checked(sws_window_resize(window->scarlet.id, w, h), "resize")) resize(window, w, h); }
void _glfwGetWindowContentScaleScarlet(_GLFWwindow* window, float* x, float* y)
{ if (x) *x = 1.f; if (y) *y = 1.f; }
void _glfwShowWindowScarlet(_GLFWwindow* window)
{ if (checked(sws_window_action(window->scarlet.id, SWS_WINDOW_SHOW), "show")) window->scarlet.visible = GLFW_TRUE; }
void _glfwHideWindowScarlet(_GLFWwindow* window)
{ if (checked(sws_window_action(window->scarlet.id, SWS_WINDOW_HIDE), "hide")) window->scarlet.visible = GLFW_FALSE; }
void _glfwFocusWindowScarlet(_GLFWwindow* window)
{ checked(sws_window_action(window->scarlet.id, SWS_WINDOW_RAISE), "raise"); }
void _glfwMaximizeWindowScarlet(_GLFWwindow* window)
{ if (checked(sws_window_action(window->scarlet.id, SWS_WINDOW_MAXIMIZE), "maximize")) { window->scarlet.maximized = GLFW_TRUE; _glfwInputWindowMaximize(window, GLFW_TRUE); } }
void _glfwRestoreWindowScarlet(_GLFWwindow* window)
{ if (checked(sws_window_action(window->scarlet.id, SWS_WINDOW_RESTORE), "restore")) { window->scarlet.maximized = GLFW_FALSE; _glfwInputWindowMaximize(window, GLFW_FALSE); } }
void _glfwSetWindowMonitorScarlet(_GLFWwindow* window, _GLFWmonitor* monitor, int x, int y, int w, int h, int refreshRate)
{
    if (!checked(sws_window_fullscreen(window->scarlet.id, monitor != NULL), "fullscreen")) return;
    if (window->monitor && window->monitor->window == window) _glfwInputMonitorWindow(window->monitor, NULL);
    _glfwInputWindowMonitor(window, monitor);
    if (monitor) _glfwInputMonitorWindow(monitor, window);
    else _glfwSetWindowSizeScarlet(window, w, h);
}
GLFWbool _glfwWindowFocusedScarlet(_GLFWwindow* w) { return w->scarlet.focused; }
GLFWbool _glfwWindowVisibleScarlet(_GLFWwindow* w) { return w->scarlet.visible; }
GLFWbool _glfwWindowIconifiedScarlet(_GLFWwindow* w) { return GLFW_FALSE; }
GLFWbool _glfwWindowMaximizedScarlet(_GLFWwindow* w) { return w->scarlet.maximized; }
GLFWbool _glfwWindowHoveredScarlet(_GLFWwindow* w) { return w->scarlet.entered; }
GLFWbool _glfwFramebufferTransparentScarlet(_GLFWwindow* w) { return GLFW_FALSE; }
float _glfwGetWindowOpacityScarlet(_GLFWwindow* w) { return 1.f; }
void _glfwGetCursorPosScarlet(_GLFWwindow* w, double* x, double* y)
{ if (x) *x = w->scarlet.xcursor; if (y) *y = w->scarlet.ycursor; }
void _glfwSetCursorModeScarlet(_GLFWwindow* w, int mode)
{
    if (mode != GLFW_CURSOR_NORMAL && mode != GLFW_CURSOR_DISABLED)
    { unavailable("cursor mode"); return; }
    checked(sws_window_pointer_lock(w->scarlet.id, mode == GLFW_CURSOR_DISABLED), "pointer lock");
}
GLFWbool _glfwRawMouseMotionSupportedScarlet(void) { return GLFW_TRUE; }
void _glfwSetRawMouseMotionScarlet(_GLFWwindow* window, GLFWbool enabled) { }

static int modifiers(_GLFWwindow* w)
{
    int mods = w->scarlet.lockMods;
    if (w->keys[GLFW_KEY_LEFT_SHIFT] == GLFW_PRESS || w->keys[GLFW_KEY_RIGHT_SHIFT] == GLFW_PRESS) mods |= GLFW_MOD_SHIFT;
    if (w->keys[GLFW_KEY_LEFT_CONTROL] == GLFW_PRESS || w->keys[GLFW_KEY_RIGHT_CONTROL] == GLFW_PRESS) mods |= GLFW_MOD_CONTROL;
    if (w->keys[GLFW_KEY_LEFT_ALT] == GLFW_PRESS || w->keys[GLFW_KEY_RIGHT_ALT] == GLFW_PRESS) mods |= GLFW_MOD_ALT;
    if (w->keys[GLFW_KEY_LEFT_SUPER] == GLFW_PRESS || w->keys[GLFW_KEY_RIGHT_SUPER] == GLFW_PRESS) mods |= GLFW_MOD_SUPER;
    return mods;
}
static int pollEvents(void)
{
    SwsEvent e;
    int result, found = 0;
    while ((result = sws_poll_event(&e)) > 0)
    {
        found = 1;
        _GLFWwindow* w = _glfw.windowListHead;
        while (w && w->scarlet.id != e.window_id) w = w->next;
        if (!w) continue;
        if (e.kind == SWS_EVENT_CONFIGURE) { resize(w, e.width, e.height); continue; }
        if (e.kind == SWS_EVENT_DESTROYED) { _glfwInputWindowCloseRequest(w); continue; }
        if (e.kind == SWS_EVENT_FOCUS)
        {
            w->scarlet.focused = e.value != 0;
            _glfwInputWindowFocus(w, w->scarlet.focused);
            continue;
        }
        if (e.kind != SWS_EVENT_INPUT) continue;
        if (e.type == 1) // evdev EV_KEY
        {
            int action = e.value ? GLFW_PRESS : GLFW_RELEASE;
            if (e.code >= 0x110 && e.code <= 0x117)
            {
                int button = e.code - 0x110;
                if (button == 1) button = GLFW_MOUSE_BUTTON_RIGHT;
                else if (button == 2) button = GLFW_MOUSE_BUTTON_MIDDLE;
                _glfwInputMouseClick(w, button, action, modifiers(w));
            }
            else if (e.code < 256)
            {
                int key = _glfw.scarlet.keycodes[e.code];
                if (e.value == 1 && key == GLFW_KEY_CAPS_LOCK) w->scarlet.lockMods ^= GLFW_MOD_CAPS_LOCK;
                if (e.value == 1 && key == GLFW_KEY_NUM_LOCK) w->scarlet.lockMods ^= GLFW_MOD_NUM_LOCK;
                int mods = modifiers(w), bit = 0;
                if (key == GLFW_KEY_LEFT_SHIFT || key == GLFW_KEY_RIGHT_SHIFT) bit = GLFW_MOD_SHIFT;
                if (key == GLFW_KEY_LEFT_CONTROL || key == GLFW_KEY_RIGHT_CONTROL) bit = GLFW_MOD_CONTROL;
                if (key == GLFW_KEY_LEFT_ALT || key == GLFW_KEY_RIGHT_ALT) bit = GLFW_MOD_ALT;
                if (key == GLFW_KEY_LEFT_SUPER || key == GLFW_KEY_RIGHT_SUPER) bit = GLFW_MOD_SUPER;
                if (e.value) mods |= bit; else mods &= ~bit;
                _glfwInputKey(w, key, e.code, action, mods);
                // SWS exposes evdev positions here. Text currently uses a US layout;
                // IME composition requires a separate SWS text-input context.
                if (e.value && key >= GLFW_KEY_SPACE && key <= GLFW_KEY_GRAVE_ACCENT)
                {
                    unsigned int ch = key;
                    if (key >= GLFW_KEY_A && key <= GLFW_KEY_Z)
                    { if (!(((mods & GLFW_MOD_SHIFT) != 0) ^ ((mods & GLFW_MOD_CAPS_LOCK) != 0))) ch += 'a' - 'A'; }
                    else if (mods & GLFW_MOD_SHIFT)
                    {
                        const char* plain = "1234567890-=[]\\;',./`";
                        const char* shifted = "!@#$%^&*()_+{}|:\"<>?~";
                        const char* at = strchr(plain, key);
                        if (at) ch = shifted[at - plain];
                    }
                    _glfwInputChar(w, ch, mods, !(mods & (GLFW_MOD_CONTROL | GLFW_MOD_ALT | GLFW_MOD_SUPER)));
                }
            }
        }
        else if (e.type == 2 || e.type == 3) // EV_REL / EV_ABS, already in surface coordinates
        {
            if (e.type == 2 && (e.code == 8 || e.code == 6))
            { _glfwInputScroll(w, e.code == 6 ? e.value : 0, e.code == 8 ? e.value : 0); continue; }
            if (e.code > 1) continue;
            double* value = e.code ? &w->scarlet.ycursor : &w->scarlet.xcursor;
            if (e.type == 2) *value += e.value; else *value = e.value;
            if (!w->scarlet.entered) { w->scarlet.entered = GLFW_TRUE; _glfwInputCursorEnter(w, GLFW_TRUE); }
            _glfwInputCursorPos(w, w->scarlet.xcursor, w->scarlet.ycursor);
        }
    }
    if (result < 0) { checked(result, "poll events"); return 1; }
    return found;
}
void _glfwPollEventsScarlet(void) { pollEvents(); }
void _glfwWaitEventsTimeoutScarlet(double timeout)
{
    uint64_t start = _glfwPlatformGetTimerValue();
    double frequency = (double) _glfwPlatformGetTimerFrequency();
    unsigned int wake = __atomic_load_n(&_glfw.scarlet.wakeup, __ATOMIC_ACQUIRE);
    while (!pollEvents())
    {
        if (__atomic_load_n(&_glfw.scarlet.wakeup, __ATOMIC_ACQUIRE) != wake) break;
        double elapsed = (double) (_glfwPlatformGetTimerValue() - start) / frequency;
        if (elapsed >= timeout) break;
        double remaining = timeout - elapsed;
        struct timespec delay = { 0, remaining < .002 ? (long) (remaining * 1e9) : 2000000 };
        nanosleep(&delay, NULL);
    }
}
void _glfwWaitEventsScarlet(void) { _glfwWaitEventsTimeoutScarlet(1e30); }
void _glfwPostEmptyEventScarlet(void) { __atomic_fetch_add(&_glfw.scarlet.wakeup, 1, __ATOMIC_RELEASE); }
int _glfwGetKeyScancodeScarlet(int key) { return _glfw.scarlet.scancodes[key]; }
const char* _glfwGetScancodeNameScarlet(int scancode)
{
    static char name[2];
    if (scancode < 0 || scancode >= 256) { _glfwInputError(GLFW_INVALID_VALUE, "Scarlet: Invalid scancode"); return NULL; }
    int key = _glfw.scarlet.keycodes[scancode];
    if (key < GLFW_KEY_SPACE || key > GLFW_KEY_GRAVE_ACCENT) return NULL;
    name[0] = (char) (key >= GLFW_KEY_A && key <= GLFW_KEY_Z ? key + 'a' - 'A' : key);
    return name;
}

// Native experimental surface ABI, shared with the SGFX and Vulkan-Loader forks.
typedef struct VkScarletSurfaceCreateInfoSGFX {
    VkStructureType sType;
    const void* pNext;
    VkFlags flags;
    uint32_t window;
} VkScarletSurfaceCreateInfoSGFX;
typedef VkResult (APIENTRY *PFN_vkCreateScarletSurfaceSGFX)(VkInstance, const VkScarletSurfaceCreateInfoSGFX*, const VkAllocationCallbacks*, VkSurfaceKHR*);
typedef VkBool32 (APIENTRY *PFN_vkGetPhysicalDeviceScarletPresentationSupportSGFX)(VkPhysicalDevice, uint32_t);
void _glfwGetRequiredInstanceExtensionsScarlet(char** extensions)
{
    if (!_glfw.vk.KHR_surface || !_glfw.vk.SGFX_scarlet_surface) return;
    extensions[0] = "VK_KHR_surface";
    extensions[1] = "VK_SGFX_scarlet_surface";
}
GLFWbool _glfwGetPhysicalDevicePresentationSupportScarlet(VkInstance instance, VkPhysicalDevice device, uint32_t family)
{
    PFN_vkGetPhysicalDeviceScarletPresentationSupportSGFX query =
        (PFN_vkGetPhysicalDeviceScarletPresentationSupportSGFX) _glfw.vk.GetInstanceProcAddr(instance, "vkGetPhysicalDeviceScarletPresentationSupportSGFX");
    return query ? query(device, family) : GLFW_FALSE;
}
VkResult _glfwCreateWindowSurfaceScarlet(VkInstance instance, _GLFWwindow* window, const VkAllocationCallbacks* allocator, VkSurfaceKHR* surface)
{
    PFN_vkCreateScarletSurfaceSGFX create = (PFN_vkCreateScarletSurfaceSGFX)
        _glfw.vk.GetInstanceProcAddr(instance, "vkCreateScarletSurfaceSGFX");
    if (!create) return VK_ERROR_EXTENSION_NOT_PRESENT;
    VkScarletSurfaceCreateInfoSGFX info = { (VkStructureType) 0x7f530001, NULL, 0, window->scarlet.id };
    return create(instance, &info, allocator, surface);
}

void _glfwSetWindowIconScarlet(_GLFWwindow* window, int count, const GLFWimage* images)
{
    unavailable("SetWindowIcon");
}

void _glfwGetWindowPosScarlet(_GLFWwindow* window, int* xpos, int* ypos)
{
    if (xpos) *xpos = 0; if (ypos) *ypos = 0;
    unavailable("GetWindowPos");
}

void _glfwSetWindowPosScarlet(_GLFWwindow* window, int xpos, int ypos)
{
    unavailable("SetWindowPos");
}

void _glfwSetWindowSizeLimitsScarlet(_GLFWwindow* window, int minwidth, int minheight, int maxwidth, int maxheight)
{
    unavailable("SetWindowSizeLimits");
}

void _glfwSetWindowAspectRatioScarlet(_GLFWwindow* window, int n, int d)
{
    unavailable("SetWindowAspectRatio");
}

void _glfwGetWindowFrameSizeScarlet(_GLFWwindow* window, int* left, int* top, int* right, int* bottom)
{
    if (left) *left = 0; if (top) *top = 0; if (right) *right = 0; if (bottom) *bottom = 0;
    unavailable("GetWindowFrameSize");
}

void _glfwIconifyWindowScarlet(_GLFWwindow* window)
{
    unavailable("IconifyWindow");
}

void _glfwSetWindowResizableScarlet(_GLFWwindow* window, GLFWbool enabled)
{
    unavailable("SetWindowResizable");
}

void _glfwSetWindowDecoratedScarlet(_GLFWwindow* window, GLFWbool enabled)
{
    unavailable("SetWindowDecorated");
}

void _glfwSetWindowFloatingScarlet(_GLFWwindow* window, GLFWbool enabled)
{
    unavailable("SetWindowFloating");
}

void _glfwSetWindowMousePassthroughScarlet(_GLFWwindow* window, GLFWbool enabled)
{
    unavailable("SetWindowMousePassthrough");
}

void _glfwSetWindowOpacityScarlet(_GLFWwindow* window, float opacity)
{
    unavailable("SetWindowOpacity");
}

void _glfwRequestWindowAttentionScarlet(_GLFWwindow* window)
{
    unavailable("RequestWindowAttention");
}

void _glfwSetCursorPosScarlet(_GLFWwindow* window, double x, double y)
{
    unavailable("SetCursorPos");
}

GLFWbool _glfwCreateCursorScarlet(_GLFWcursor* cursor, const GLFWimage* image, int xhot, int yhot)
{
    unavailable("CreateCursor");
    return 0;
}

GLFWbool _glfwCreateStandardCursorScarlet(_GLFWcursor* cursor, int shape)
{
    unavailable("CreateStandardCursor");
    return 0;
}

void _glfwDestroyCursorScarlet(_GLFWcursor* cursor)
{

}

void _glfwSetCursorScarlet(_GLFWwindow* window, _GLFWcursor* cursor)
{
    unavailable("SetCursor");
}

void _glfwSetClipboardStringScarlet(const char* string)
{
    unavailable("SetClipboardString");
}

const char* _glfwGetClipboardStringScarlet(void)
{
    unavailable("GetClipboardString");
    return 0;
}

EGLenum _glfwGetEGLPlatformScarlet(EGLint** attribs)
{
    unavailable("GetEGLPlatform");
    return 0;
}

EGLNativeDisplayType _glfwGetEGLNativeDisplayScarlet(void)
{
    unavailable("GetEGLNativeDisplay");
    return 0;
}

EGLNativeWindowType _glfwGetEGLNativeWindowScarlet(_GLFWwindow* window)
{
    unavailable("GetEGLNativeWindow");
    return 0;
}
