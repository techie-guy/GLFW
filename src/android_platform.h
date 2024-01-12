#include "internal.h"

#include <android/log.h>
#include <android/input.h>
#include <android/keycodes.h>
#include <android/looper.h>
#include <android_native_app_glue.h>
#include <jni.h>

typedef VkFlags VkAndroidSurfaceCreateFlagsKHR;

typedef struct VkAndroidSurfaceCreateInfoKHR {
	VkStructureType                   sType;
	const void*                       pNext;
	VkAndroidSurfaceCreateFlagsKHR    flags;
	struct ANativeWindow*             window;
} VkAndroidSurfaceCreateInfoKHR;

typedef VkResult (APIENTRY* PFN_vkCreateAndroidSurfaceKHR)(VkInstance,const VkAndroidSurfaceCreateInfoKHR*,const VkAllocationCallbacks*,VkSurfaceKHR*);

typedef VkBool32 (APIENTRY *PFN_vkGetPhysicalDeviceAndroidPresentationSupportKHR)(VkPhysicalDevice,uint32_t,struct ANativeWindow*);

#define GLFW_ANDROID_WINDOW_STATE _GLFWwindowAndroid android;
#define GLFW_ANDROID_LIBRARY_WINDOW_STATE _GLFWlibraryAndroid android;
#define GLFW_ANDROID_MONITOR_STATE _GLFWmonitorAndroid android;
#define GLFW_ANDROID_CURSOR_STATE

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "GLFW_ANDROID", __VA_ARGS__))

typedef struct _GLFWwindowAndroid
{
	struct android_app* app;
	ANativeWindow* native_window;

	float mouse_pos_x;
	float mouse_pos_y;

	GLFWbool is_window_focused;
} _GLFWwindowAndroid;

typedef struct _GLFWmonitorAndroid
{
	GLFWgammaramp ramp;
} _GLFWmonitorAndroid;

typedef struct _GLFWlibraryAndroid
{
	struct android_app* app;
	ANativeActivity* native_activity;
	JavaVM* java_vm;

	short int keycodes[290];
	short int scancodes[GLFW_KEY_LAST + 1];
	char keynames[GLFW_KEY_LAST + 1][5];
} _GLFWlibraryAndroid;

GLFWbool _glfwConnectAndroid(int platformId, _GLFWplatform* platform);

GLFWbool _glfwInitAndroid(void);
void _glfwTerminateAndroid(void);

// input
void _glfwGetCursorPosAndroid(_GLFWwindow* window, double* xpos, double* ypos);
void _glfwSetCursorPosAndroid(_GLFWwindow* window, double xpos, double ypos);
void _glfwSetCursorModeAndroid(_GLFWwindow* window, int mode);
void _glfwSetRawMouseMotionAndroid(_GLFWwindow *window, GLFWbool enabled);
GLFWbool _glfwRawMouseMotionSupportedAndroid(void);
GLFWbool _glfwCreateCursorAndroid(_GLFWcursor* cursor, const GLFWimage* image, int xhot, int yhot);
GLFWbool _glfwCreateStandardCursorAndroid(_GLFWcursor* cursor, int shape);
void _glfwDestroyCursorAndroid(_GLFWcursor* cursor);
void _glfwSetCursorAndroid(_GLFWwindow* window, _GLFWcursor* cursor);
const char* _glfwGetScancodeNameAndroid(int scancode);
int _glfwGetKeyScancodeAndroid(int key);
void _glfwSetClipboardStringAndroid(const char* string);
const char* _glfwGetClipboardStringAndroid(void);

// monitor
void _glfwPollMonitorsAndroid(void);
void _glfwFreeMonitorAndroid(_GLFWmonitor* monitor);
void _glfwGetMonitorPosAndroid(_GLFWmonitor* monitor, int* xpos, int* ypos);
void _glfwGetMonitorContentScaleAndroid(_GLFWmonitor* monitor, float* xscale, float* yscale);
void _glfwGetMonitorWorkareaAndroid(_GLFWmonitor* monitor, int* xpos, int* ypos, int* width, int* height);
GLFWvidmode* _glfwGetVideoModesAndroid(_GLFWmonitor* monitor, int* found);
void _glfwGetVideoModeAndroid(_GLFWmonitor* monitor, GLFWvidmode* mode);
GLFWbool _glfwGetGammaRampAndroid(_GLFWmonitor* monitor, GLFWgammaramp* ramp);
void _glfwSetGammaRampAndroid(_GLFWmonitor* monitor, const GLFWgammaramp* ramp);
//void _glfwSetVideoModeX11(_GLFWmonitor* monitor, const GLFWvidmode* desired);

// window
GLFWbool _glfwCreateWindowAndroid(_GLFWwindow* window, const _GLFWwndconfig* wndconfig, const _GLFWctxconfig* ctxconfig, const _GLFWfbconfig* fbconfig);
void _glfwDestroyWindowAndroid(_GLFWwindow* window);
void _glfwSetWindowTitleAndroid(_GLFWwindow* window, const char* title);
void _glfwSetWindowIconAndroid(_GLFWwindow* window, int count, const GLFWimage* images);
void _glfwGetWindowPosAndroid(_GLFWwindow* window, int* xpos, int* ypos);
void _glfwSetWindowPosAndroid(_GLFWwindow* window, int xpos, int ypos);
void _glfwGetWindowSizeAndroid(_GLFWwindow* window, int* width, int* height);
void _glfwSetWindowSizeAndroid(_GLFWwindow* window, int width, int height);
void _glfwSetWindowSizeLimitsAndroid(_GLFWwindow* window, int minwidth, int minheight, int maxwidth, int maxheight);
void _glfwSetWindowAspectRatioAndroid(_GLFWwindow* window, int numer, int denom);
void _glfwGetFramebufferSizeAndroid(_GLFWwindow* window, int* width, int* height);
void _glfwGetWindowFrameSizeAndroid(_GLFWwindow* window, int* left, int* top, int* right, int* bottom);
void _glfwGetWindowContentScaleAndroid(_GLFWwindow* window, float* xscale, float* yscale);
void _glfwIconifyWindowAndroid(_GLFWwindow* window);
void _glfwRestoreWindowAndroid(_GLFWwindow* window);
void _glfwMaximizeWindowAndroid(_GLFWwindow* window);
void _glfwShowWindowAndroid(_GLFWwindow* window);
void _glfwHideWindowAndroid(_GLFWwindow* window);
void _glfwRequestWindowAttentionAndroid(_GLFWwindow* window);
void _glfwFocusWindowAndroid(_GLFWwindow* window);
void _glfwSetWindowMonitorAndroid(_GLFWwindow* window, _GLFWmonitor* monitor, int xpos, int ypos, int width, int height, int refreshRate);
GLFWbool _glfwWindowFocusedAndroid(_GLFWwindow* window);
GLFWbool _glfwWindowIconifiedAndroid(_GLFWwindow* window);
GLFWbool _glfwWindowVisibleAndroid(_GLFWwindow* window);
GLFWbool _glfwWindowMaximizedAndroid(_GLFWwindow* window);
GLFWbool _glfwWindowHoveredAndroid(_GLFWwindow* window);
GLFWbool _glfwFramebufferTransparentAndroid(_GLFWwindow* window);
float _glfwGetWindowOpacityAndroid(_GLFWwindow* window);
void _glfwSetWindowResizableAndroid(_GLFWwindow* window, GLFWbool enabled);
void _glfwSetWindowDecoratedAndroid(_GLFWwindow* window, GLFWbool enabled);
void _glfwSetWindowFloatingAndroid(_GLFWwindow* window, GLFWbool enabled);
void _glfwSetWindowOpacityAndroid(_GLFWwindow* window, float opacity);
void _glfwSetWindowMousePassthroughAndroid(_GLFWwindow* window, GLFWbool enabled);
void _glfwPollEventsAndroid(void);
void _glfwWaitEventsAndroid(void);
void _glfwWaitEventsTimeoutAndroid(double timeout);
void _glfwPostEmptyEventAndroid(void);

// egl
EGLenum _glfwGetEGLPlatformAndroid(EGLint** attribs);
EGLNativeDisplayType _glfwGetEGLNativeDisplayAndroid(void);
EGLNativeWindowType _glfwGetEGLNativeWindowAndroid(_GLFWwindow* window);

// vulkan
void _glfwGetRequiredInstanceExtensionsAndroid(char** extensions);
GLFWbool _glfwGetPhysicalDevicePresentationSupportAndroid(VkInstance instance, VkPhysicalDevice device, uint32_t queuefamily);
VkResult _glfwCreateWindowSurfaceAndroid(VkInstance instance, _GLFWwindow* window, const VkAllocationCallbacks* allocator, VkSurfaceKHR* surface);

