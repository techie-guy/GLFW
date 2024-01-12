#include "GLFW/glfw3.h"
#include "android_native_app_glue.h"
#include "internal.h"
#include <android/native_activity.h>
#include <jni.h>
#include <string.h>
#include <android/window.h>

#if defined(_GLFW_ANDROID)

GLFWbool _glfwCreateWindowAndroid(_GLFWwindow* window, const _GLFWwndconfig* wndconfig, const _GLFWctxconfig* ctxconfig, const _GLFWfbconfig* fbconfig)
{
	window->android.app = _glfw.android.app;
	window->android.native_window = _glfw.android.app->window;

	ANativeWindow_acquire(window->android.app->window);

	if(!window->android.native_window)
	{
		return GLFW_FALSE;
	}

	ANativeWindow_setBuffersGeometry(window->android.native_window, wndconfig->width, wndconfig->height, 0);

	if(ctxconfig->client != GLFW_NO_API)
	{
		if(ctxconfig->source == GLFW_EGL_CONTEXT_API || ctxconfig->source == GLFW_NATIVE_CONTEXT_API)
		{
			if (!_glfwInitEGL())
				return GLFW_FALSE;
			if (!_glfwCreateContextEGL(window, ctxconfig, fbconfig))
				return GLFW_FALSE;
		}

		if (!_glfwRefreshContextAttribs(window, ctxconfig))
			return GLFW_FALSE;
	}

	return GLFW_TRUE;
}

void _glfwDestroyWindowAndroid(_GLFWwindow* window)
{
	if(window->context.destroy)
		window->context.destroy(window);

	ANativeWindow_release(window->android.native_window);
}

void _glfwSetWindowTitleAndroid(_GLFWwindow* window, const char* title)
{
}

void _glfwSetWindowIconAndroid(_GLFWwindow* window, int count, const GLFWimage* images)
{
}

void _glfwGetWindowPosAndroid(_GLFWwindow* window, int* xpos, int* ypos)
{
}

void _glfwSetWindowPosAndroid(_GLFWwindow* window, int xpos, int ypos)
{
}

void _glfwGetWindowSizeAndroid(_GLFWwindow* window, int* width, int* height)
{
	*width = ANativeWindow_getWidth(window->android.native_window);
	*height = ANativeWindow_getHeight(window->android.native_window);
}

void _glfwSetWindowSizeAndroid(_GLFWwindow* window, int width, int height)
{
	ANativeWindow_setBuffersGeometry(window->android.native_window, width, height, 0);
}

void _glfwSetWindowSizeLimitsAndroid(_GLFWwindow* window, int minwidth, int minheight, int maxwidth, int maxheight)
{
}

void _glfwSetWindowAspectRatioAndroid(_GLFWwindow* window, int numer, int denom)
{
}

void _glfwGetFramebufferSizeAndroid(_GLFWwindow* window, int* width, int* height)
{
	_glfwGetWindowSizeAndroid(window, width, height);
}

void _glfwGetWindowFrameSizeAndroid(_GLFWwindow* window, int* left, int* top, int* right, int* bottom)
{
}

void _glfwGetWindowContentScaleAndroid(_GLFWwindow* window, float* xscale, float* yscale)
{
}

void _glfwIconifyWindowAndroid(_GLFWwindow* window)
{
}

void _glfwRestoreWindowAndroid(_GLFWwindow* window)
{
}

void _glfwMaximizeWindowAndroid(_GLFWwindow* window)
{
}

void _glfwShowWindowAndroid(_GLFWwindow* window)
{
}

void _glfwHideWindowAndroid(_GLFWwindow* window)
{
}

void _glfwRequestWindowAttentionAndroid(_GLFWwindow* window)
{
}

void _glfwFocusWindowAndroid(_GLFWwindow* window)
{
}

void _glfwSetWindowMonitorAndroid(_GLFWwindow* window, _GLFWmonitor* monitor, int xpos, int ypos, int width, int height, int refreshRate)
{
}

GLFWbool _glfwWindowFocusedAndroid(_GLFWwindow* window)
{
	return _glfw.windowListHead->android.is_window_focused;
}

GLFWbool _glfwWindowIconifiedAndroid(_GLFWwindow* window)
{
	return GLFW_FALSE;
}

GLFWbool _glfwWindowVisibleAndroid(_GLFWwindow* window)
{
	return GLFW_TRUE;
}

GLFWbool _glfwWindowMaximizedAndroid(_GLFWwindow* window)
{
	return GLFW_TRUE;
}

GLFWbool _glfwWindowHoveredAndroid(_GLFWwindow* window)
{
	return GLFW_TRUE;
}

GLFWbool _glfwFramebufferTransparentAndroid(_GLFWwindow* window)
{
	return GLFW_FALSE;
}

float _glfwGetWindowOpacityAndroid(_GLFWwindow* window)
{
	return 1.0f;
}

void _glfwSetWindowResizableAndroid(_GLFWwindow* window, GLFWbool enabled)
{
}

void _glfwSetWindowDecoratedAndroid(_GLFWwindow* window, GLFWbool enabled)
{
}

void _glfwSetWindowFloatingAndroid(_GLFWwindow* window, GLFWbool enabled)
{
}

void _glfwSetWindowOpacityAndroid(_GLFWwindow* window, float opacity)
{
}

void _glfwSetWindowMousePassthroughAndroid(_GLFWwindow* window, GLFWbool enabled)
{
}

void _glfwPollEventsAndroid(void)
{
}

void _glfwWaitEventsAndroid(void)
{
}

void _glfwWaitEventsTimeoutAndroid(double timeout)
{
}

void _glfwPostEmptyEventAndroid(void)
{
}

// Input
void _glfwGetCursorPosAndroid(_GLFWwindow* window, double* xpos, double* ypos)
{
	*xpos = _glfw.windowListHead->android.mouse_pos_x;
	*ypos = _glfw.windowListHead->android.mouse_pos_y;
}

void _glfwSetCursorPosAndroid(_GLFWwindow* window, double xpos, double ypos)
{
}

void _glfwSetCursorModeAndroid(_GLFWwindow* window, int mode)
{
}

void _glfwSetRawMouseMotionAndroid(_GLFWwindow *window, GLFWbool enabled)
{
}

GLFWbool _glfwRawMouseMotionSupportedAndroid(void)
{
	return GLFW_TRUE;
}

GLFWbool _glfwCreateCursorAndroid(_GLFWcursor* cursor, const GLFWimage* image, int xhot, int yhot)
{
	return GLFW_TRUE;
}

GLFWbool _glfwCreateStandardCursorAndroid(_GLFWcursor* cursor, int shape)
{
	return GLFW_TRUE;
}

void _glfwDestroyCursorAndroid(_GLFWcursor* cursor)
{
}

void _glfwSetCursorAndroid(_GLFWwindow* window, _GLFWcursor* cursor)
{
}

const char* _glfwGetScancodeNameAndroid(int scancode)
{
	return "";
}

int _glfwGetKeyScancodeAndroid(int key)
{
	return _glfw.android.scancodes[key];
}

void _glfwSetClipboardStringAndroid(const char* string)
{
	JavaVM* vm = _glfw.android.java_vm;
	JNIEnv* env;

	(*vm)->AttachCurrentThread(vm, &env, NULL);

	jclass activity_class = (*env)->GetObjectClass(env, _glfw.android.native_activity->clazz);
	jobject activity_class_object = _glfw.android.native_activity->clazz;

	jobject get_system_service = (*env)->GetMethodID(env, activity_class, "getSystemService", "(Ljava/lang/String;)Ljava/lang/Object;");

	jstring clipboard_service = (*env)->NewStringUTF(env, "clipboard");
	jobject clipboard_manager = (*env)->CallObjectMethod(env, activity_class_object, get_system_service, clipboard_service);
	jclass clipboard_manager_class = (*env)->GetObjectClass(env, clipboard_manager);

	jclass clip_data_class = (*env)->FindClass(env, "android/content/ClipData");

	jmethodID new_plain_text = (*env)->GetStaticMethodID(env, clip_data_class, "newPlainText", "(Ljava/lang/CharSequence;Ljava/lang/CharSequence;)Landroid/content/ClipData;");

	jstring text = (*env)->NewStringUTF(env, string);

	jobject clip_data = (*env)->CallStaticObjectMethod(env, clip_data_class, new_plain_text, text, text);

	jmethodID set_primary_clip = (*env)->GetMethodID(env, clipboard_manager_class, "setPrimaryClip", "(Landroid/content/ClipData;)V");
	(*env)->CallVoidMethod(env, clipboard_manager, set_primary_clip, clip_data);

	(*vm)->DetachCurrentThread(vm);
}

const char* _glfwGetClipboardStringAndroid(void)
{
	JavaVM* vm = _glfw.android.java_vm;
	JNIEnv* env;

	const char* clipboard_string = "";

	(*vm)->AttachCurrentThread(vm, &env, NULL);

	jclass activity_class = (*env)->GetObjectClass(env, _glfw.android.native_activity->clazz);
	jobject activity_class_object = _glfw.android.native_activity->clazz;

	jobject get_system_service = (*env)->GetMethodID(env, activity_class, "getSystemService", "(Ljava/lang/String;)Ljava/lang/Object;");

	// https://developer.android.com/reference/android/content/Context#CLIPBOARD_SERVICE
	jstring clipboard_service = (*env)->NewStringUTF(env, "clipboard");
	jobject clipboard_manager = (*env)->CallObjectMethod(env, activity_class_object, get_system_service, clipboard_service);

	jclass clipboard_manager_class = (*env)->GetObjectClass(env, clipboard_manager);
	jmethodID get_primary_clip = (*env)->GetMethodID(env, clipboard_manager_class, "getPrimaryClip", "()Landroid/content/ClipData;");
	jobject clip_data = (*env)->CallObjectMethod(env, clipboard_manager, get_primary_clip);

	if(!clip_data)
	{
		LOGI("ClipData Null");
		return clipboard_string;
	}

	jclass clip_data_class = (*env)->GetObjectClass(env, clip_data);
	jmethodID get_item_count = (*env)->GetMethodID(env, clip_data_class, "getItemCount", "()I");
	jint item_count = (*env)->CallIntMethod(env, clip_data, get_item_count);

	if(item_count == 0)
	{
		LOGI("No Items");
		return clipboard_string;
	}

	jmethodID get_item = (*env)->GetMethodID(env, clip_data_class, "getItemAt", "(I)Landroid/content/ClipData$Item;");
	jobject clip_data_item = (*env)->CallObjectMethod(env, clip_data, get_item, 0);

	if(!clip_data_item)
	{
		LOGI("Null Data");
		return clipboard_string;
	}

	jclass clip_data_item_class = (*env)->GetObjectClass(env, clip_data_item);
	jmethodID get_text_method = (*env)->GetMethodID(env, clip_data_item_class, "getText", "()Ljava/lang/CharSequence;");
	jobject text_object = (*env)->CallObjectMethod(env, clip_data_item, get_text_method);
	if (!text_object)
	{
		LOGI("Null Text Object");
		return clipboard_string;
	}

	jstring text = (jstring)text_object;
	clipboard_string = (*env)->GetStringUTFChars(env, text, NULL);

	(*vm)->DetachCurrentThread(vm);

	return clipboard_string;
}

// EGL
EGLenum _glfwGetEGLPlatformAndroid(EGLint** attribs)
{
	return GLFW_FALSE;
}

EGLNativeDisplayType _glfwGetEGLNativeDisplayAndroid(void)
{
	return EGL_DEFAULT_DISPLAY;
}

EGLNativeWindowType _glfwGetEGLNativeWindowAndroid(_GLFWwindow* window)
{
	return window->android.native_window;
}

// Vulkan
void _glfwGetRequiredInstanceExtensionsAndroid(char** extensions)
{
	if (!_glfw.vk.KHR_surface || !_glfw.vk.KHR_android_surface)
		return;

	extensions[0] = "VK_KHR_surface";
	extensions[1] = "VK_KHR_android_surface";
}

GLFWbool _glfwGetPhysicalDevicePresentationSupportAndroid(VkInstance instance, VkPhysicalDevice device, uint32_t queuefamily)
{
	// PFN_vkGetPhysicalDeviceAndroidPresentationSupportKHR vkGetPhysicalDeviceAndroidPresentationSupportKHR;
 //
	// vkGetPhysicalDeviceAndroidPresentationSupportKHR =
	// (PFN_vkGetPhysicalDeviceAndroidPresentationSupportKHR)
	// vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceAndroidPresentationSupportKHR");
 //
	// if (!vkGetPhysicalDeviceAndroidPresentationSupportKHR)
	// {
	// 	_glfwInputError(GLFW_API_UNAVAILABLE,
	// 					"Android: Vulkan instance missing VK_KHR_android_surface extension");
	// 	return VK_NULL_HANDLE;
	// }
 //
	// return vkGetPhysicalDeviceAndroidPresentationSupportKHR(device,
	// 														queuefamily,
	// 													 _glfw.android.app->window);

	return GLFW_TRUE;
}

VkResult _glfwCreateWindowSurfaceAndroid(VkInstance instance, _GLFWwindow* window, const VkAllocationCallbacks* allocator, VkSurfaceKHR* surface)
{
	VkResult err;
	VkAndroidSurfaceCreateInfoKHR sci;
	PFN_vkCreateAndroidSurfaceKHR vkCreateAndroidSurfaceKHR;

	vkCreateAndroidSurfaceKHR = (PFN_vkCreateAndroidSurfaceKHR)vkGetInstanceProcAddr(instance, "vkCreateAndroidSurfaceKHR");
	if (!vkCreateAndroidSurfaceKHR)
	{
		_glfwInputError(GLFW_API_UNAVAILABLE,
						"Android: Vulkan instance missing VK_KHR_android_surface extension");
		return VK_ERROR_EXTENSION_NOT_PRESENT;
	}

	memset(&sci, 0, sizeof(sci));
	sci.sType = VK_STRUCTURE_TYPE_ANDROID_SURFACE_CREATE_INFO_KHR;
	sci.pNext = NULL,
	sci.flags = 0,
	sci.window = _glfw.android.app->window;

	err = vkCreateAndroidSurfaceKHR(instance, &sci, allocator, surface);
	if (err)
	{
		_glfwInputError(GLFW_PLATFORM_ERROR,
						"Android: Failed to create Vulkan surface: %s",
				  _glfwGetVulkanResultString(err));
	}

	return err;
}


GLFWAPI struct android_app* glfwGetAndroidApp(void)
{
	_GLFW_REQUIRE_INIT_OR_RETURN(NULL);

	if (_glfw.platform.platformID != GLFW_PLATFORM_ANDROID)
	{
		_glfwInputError(GLFW_PLATFORM_UNAVAILABLE,
						"Android: Platform not initialized");
		return NULL;
	}

	return _glfw.android.app;
}

#endif // _GLFW_ANDROID
