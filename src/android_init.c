#include "GLFW/glfw3.h"
#include "internal.h"
#include <android/input.h>
#include <android/keycodes.h>
#include <android/looper.h>
#include <jni.h>

#if defined(_GLFW_ANDROID)
#include <pthread.h>
#include <string.h>

extern int main();

/*
char[5] getKeyName(int scancode)
{
	switch (scancode)
	{
		case AKEYCODE_UNKNOWN: return "Unkno";
	}
}
*/

static void createKeyTables(void)
{
	memset(_glfw.android.keycodes, -1, sizeof(_glfw.android.keycodes));
	memset(_glfw.android.scancodes, -1, sizeof(_glfw.android.scancodes));
	memset(_glfw.android.keynames, -1, sizeof(_glfw.android.keynames));

	_glfw.android.keycodes[AKEYCODE_SPACE] = GLFW_KEY_SPACE;
	_glfw.android.keycodes[AKEYCODE_APOSTROPHE] = GLFW_KEY_APOSTROPHE;
	_glfw.android.keycodes[AKEYCODE_COMMA] = GLFW_KEY_COMMA;
	_glfw.android.keycodes[AKEYCODE_MINUS] = GLFW_KEY_MINUS;
	_glfw.android.keycodes[AKEYCODE_PERIOD] = GLFW_KEY_PERIOD;
	_glfw.android.keycodes[AKEYCODE_SLASH] = GLFW_KEY_SLASH;

	_glfw.android.keycodes[AKEYCODE_0] = GLFW_KEY_0;
	_glfw.android.keycodes[AKEYCODE_1] = GLFW_KEY_1;
	_glfw.android.keycodes[AKEYCODE_2] = GLFW_KEY_2;
	_glfw.android.keycodes[AKEYCODE_3] = GLFW_KEY_3;
	_glfw.android.keycodes[AKEYCODE_4] = GLFW_KEY_4;
	_glfw.android.keycodes[AKEYCODE_5] = GLFW_KEY_5;
	_glfw.android.keycodes[AKEYCODE_6] = GLFW_KEY_6;
	_glfw.android.keycodes[AKEYCODE_7] = GLFW_KEY_7;
	_glfw.android.keycodes[AKEYCODE_8] = GLFW_KEY_8;
	_glfw.android.keycodes[AKEYCODE_9] = GLFW_KEY_9;

	_glfw.android.keycodes[AKEYCODE_SEMICOLON] = GLFW_KEY_SEMICOLON;
	_glfw.android.keycodes[AKEYCODE_EQUALS] = GLFW_KEY_EQUAL;

	_glfw.android.keycodes[AKEYCODE_A] = GLFW_KEY_A;
	_glfw.android.keycodes[AKEYCODE_B] = GLFW_KEY_B;
	_glfw.android.keycodes[AKEYCODE_C] = GLFW_KEY_C;
	_glfw.android.keycodes[AKEYCODE_D] = GLFW_KEY_D;
	_glfw.android.keycodes[AKEYCODE_E] = GLFW_KEY_E;
	_glfw.android.keycodes[AKEYCODE_F] = GLFW_KEY_F;
	_glfw.android.keycodes[AKEYCODE_G] = GLFW_KEY_G;
	_glfw.android.keycodes[AKEYCODE_H] = GLFW_KEY_H;
	_glfw.android.keycodes[AKEYCODE_I] = GLFW_KEY_I;
	_glfw.android.keycodes[AKEYCODE_J] = GLFW_KEY_J;
	_glfw.android.keycodes[AKEYCODE_K] = GLFW_KEY_K;
	_glfw.android.keycodes[AKEYCODE_L] = GLFW_KEY_L;
	_glfw.android.keycodes[AKEYCODE_M] = GLFW_KEY_M;
	_glfw.android.keycodes[AKEYCODE_N] = GLFW_KEY_N;
	_glfw.android.keycodes[AKEYCODE_O] = GLFW_KEY_O;
	_glfw.android.keycodes[AKEYCODE_P] = GLFW_KEY_P;
	_glfw.android.keycodes[AKEYCODE_Q] = GLFW_KEY_Q;
	_glfw.android.keycodes[AKEYCODE_R] = GLFW_KEY_R;
	_glfw.android.keycodes[AKEYCODE_S] = GLFW_KEY_S;
	_glfw.android.keycodes[AKEYCODE_T] = GLFW_KEY_T;
	_glfw.android.keycodes[AKEYCODE_U] = GLFW_KEY_U;
	_glfw.android.keycodes[AKEYCODE_V] = GLFW_KEY_V;
	_glfw.android.keycodes[AKEYCODE_W] = GLFW_KEY_W;
	_glfw.android.keycodes[AKEYCODE_X] = GLFW_KEY_X;
	_glfw.android.keycodes[AKEYCODE_Y] = GLFW_KEY_Y;
	_glfw.android.keycodes[AKEYCODE_Z] = GLFW_KEY_Z;

	_glfw.android.keycodes[AKEYCODE_LEFT_BRACKET] = GLFW_KEY_LEFT_BRACKET;
	_glfw.android.keycodes[AKEYCODE_BACKSLASH] = GLFW_KEY_BACKSLASH;
	_glfw.android.keycodes[AKEYCODE_RIGHT_BRACKET] = GLFW_KEY_RIGHT_BRACKET;
	_glfw.android.keycodes[AKEYCODE_GRAVE] = GLFW_KEY_GRAVE_ACCENT;

	_glfw.android.keycodes[AKEYCODE_ESCAPE] = GLFW_KEY_ESCAPE;
	_glfw.android.keycodes[AKEYCODE_ENTER] = GLFW_KEY_ENTER;
	_glfw.android.keycodes[AKEYCODE_TAB] = GLFW_KEY_TAB;
	_glfw.android.keycodes[AKEYCODE_DEL] = GLFW_KEY_BACKSPACE;
	_glfw.android.keycodes[AKEYCODE_INSERT] = GLFW_KEY_INSERT;
	_glfw.android.keycodes[AKEYCODE_FORWARD_DEL] = GLFW_KEY_DELETE;
	_glfw.android.keycodes[AKEYCODE_DPAD_RIGHT] = GLFW_KEY_RIGHT;
	_glfw.android.keycodes[AKEYCODE_DPAD_LEFT] = GLFW_KEY_LEFT;
	_glfw.android.keycodes[AKEYCODE_DPAD_DOWN] = GLFW_KEY_DOWN;
	_glfw.android.keycodes[AKEYCODE_DPAD_UP] = GLFW_KEY_UP;
	_glfw.android.keycodes[AKEYCODE_PAGE_UP] = GLFW_KEY_PAGE_UP;
	_glfw.android.keycodes[AKEYCODE_PAGE_DOWN] = GLFW_KEY_PAGE_DOWN;
	_glfw.android.keycodes[AKEYCODE_MOVE_HOME] = GLFW_KEY_HOME;
	_glfw.android.keycodes[AKEYCODE_MOVE_END] = GLFW_KEY_END;
	_glfw.android.keycodes[AKEYCODE_CAPS_LOCK] = GLFW_KEY_CAPS_LOCK;
	_glfw.android.keycodes[AKEYCODE_SCROLL_LOCK] = GLFW_KEY_SCROLL_LOCK;
	_glfw.android.keycodes[AKEYCODE_NUM_LOCK] = GLFW_KEY_NUM_LOCK;
	_glfw.android.keycodes[AKEYCODE_SYSRQ] = GLFW_KEY_PRINT_SCREEN;
	_glfw.android.keycodes[AKEYCODE_BREAK] = GLFW_KEY_PAUSE;

	_glfw.android.keycodes[AKEYCODE_F1] = GLFW_KEY_F1;
	_glfw.android.keycodes[AKEYCODE_F2] = GLFW_KEY_F2;
	_glfw.android.keycodes[AKEYCODE_F3] = GLFW_KEY_F3;
	_glfw.android.keycodes[AKEYCODE_F4] = GLFW_KEY_F4;
	_glfw.android.keycodes[AKEYCODE_F5] = GLFW_KEY_F5;
	_glfw.android.keycodes[AKEYCODE_F6] = GLFW_KEY_F6;
	_glfw.android.keycodes[AKEYCODE_F7] = GLFW_KEY_F7;
	_glfw.android.keycodes[AKEYCODE_F8] = GLFW_KEY_F8;
	_glfw.android.keycodes[AKEYCODE_F9] = GLFW_KEY_F9;
	_glfw.android.keycodes[AKEYCODE_F10] = GLFW_KEY_F10;
	_glfw.android.keycodes[AKEYCODE_F11] = GLFW_KEY_F11;
	_glfw.android.keycodes[AKEYCODE_F12] = GLFW_KEY_F12;

	_glfw.android.keycodes[AKEYCODE_NUMPAD_0] = GLFW_KEY_KP_0;
	_glfw.android.keycodes[AKEYCODE_NUMPAD_1] = GLFW_KEY_KP_1;
	_glfw.android.keycodes[AKEYCODE_NUMPAD_2] = GLFW_KEY_KP_2;
	_glfw.android.keycodes[AKEYCODE_NUMPAD_3] = GLFW_KEY_KP_3;
	_glfw.android.keycodes[AKEYCODE_NUMPAD_4] = GLFW_KEY_KP_4;
	_glfw.android.keycodes[AKEYCODE_NUMPAD_5] = GLFW_KEY_KP_5;
	_glfw.android.keycodes[AKEYCODE_NUMPAD_6] = GLFW_KEY_KP_6;
	_glfw.android.keycodes[AKEYCODE_NUMPAD_7] = GLFW_KEY_KP_7;
	_glfw.android.keycodes[AKEYCODE_NUMPAD_8] = GLFW_KEY_KP_8;
	_glfw.android.keycodes[AKEYCODE_NUMPAD_9] = GLFW_KEY_KP_9;
	_glfw.android.keycodes[AKEYCODE_NUMPAD_DOT] = GLFW_KEY_KP_DECIMAL;
	_glfw.android.keycodes[AKEYCODE_NUMPAD_DIVIDE] = GLFW_KEY_KP_DIVIDE;
	_glfw.android.keycodes[AKEYCODE_NUMPAD_MULTIPLY] = GLFW_KEY_KP_MULTIPLY;
	_glfw.android.keycodes[AKEYCODE_NUMPAD_SUBTRACT] = GLFW_KEY_KP_SUBTRACT;
	_glfw.android.keycodes[AKEYCODE_NUMPAD_ADD] = GLFW_KEY_KP_ADD;
	_glfw.android.keycodes[AKEYCODE_NUMPAD_ENTER] = GLFW_KEY_KP_ENTER;
	_glfw.android.keycodes[AKEYCODE_NUMPAD_EQUALS] = GLFW_KEY_KP_EQUAL;

	_glfw.android.keycodes[AKEYCODE_SHIFT_LEFT] = GLFW_KEY_LEFT_SHIFT;
	_glfw.android.keycodes[AKEYCODE_ALT_LEFT] = GLFW_KEY_LEFT_ALT;
	_glfw.android.keycodes[AKEYCODE_CTRL_LEFT] = GLFW_KEY_LEFT_CONTROL;
	_glfw.android.keycodes[AKEYCODE_META_LEFT] = GLFW_KEY_LEFT_SUPER;
	_glfw.android.keycodes[AKEYCODE_SHIFT_RIGHT] = GLFW_KEY_RIGHT_SHIFT;
	_glfw.android.keycodes[AKEYCODE_ALT_RIGHT] = GLFW_KEY_RIGHT_ALT;
	_glfw.android.keycodes[AKEYCODE_CTRL_RIGHT] = GLFW_KEY_RIGHT_CONTROL;
	_glfw.android.keycodes[AKEYCODE_META_RIGHT] = GLFW_KEY_RIGHT_SUPER;
	_glfw.android.keycodes[AKEYCODE_MENU] = GLFW_KEY_MENU;

	for (int scancode = 0; scancode < 290; scancode++)
	{
		if (_glfw.android.keycodes[scancode] > 0)
		{
			_glfw.android.scancodes[_glfw.android.keycodes[scancode]] = scancode;
			//_glfw.android.keynames[scancode] = getKeyName(scancode);
		}
	}
}

int translateMouseButton(int32_t mouse_button)
{
	switch(mouse_button)
	{
		case AMOTION_EVENT_BUTTON_PRIMARY:
			return GLFW_MOUSE_BUTTON_1;
		case AMOTION_EVENT_BUTTON_SECONDARY:
			return GLFW_MOUSE_BUTTON_2;
		case AMOTION_EVENT_BUTTON_TERTIARY:
			return GLFW_MOUSE_BUTTON_3;
	}

	return -1;
}

void handle_cmd(struct android_app* app, int32_t cmd)
{
	switch (cmd)
	{
		case APP_CMD_SAVE_STATE:
			break;
		case APP_CMD_INIT_WINDOW:
		{
			if(app->window)
			{
				_glfw.android.app = app;
				_glfw.android.native_activity = _glfw.android.app->activity;
				_glfw.android.java_vm = _glfw.android.native_activity->vm;

				createKeyTables();
			}
			break;
		}
		case APP_CMD_TERM_WINDOW:
		{
			_GLFWwindow* window = _glfw.windowListHead;
			_glfwInputWindowCloseRequest(window);
			break;
		}
		case APP_CMD_GAINED_FOCUS:
			_glfw.windowListHead->android.is_window_focused = true;
			break;
		case APP_CMD_LOST_FOCUS:
			_glfw.windowListHead->android.is_window_focused = false;
			break;
		case APP_CMD_CONFIG_CHANGED:
		{
			// TODO: Add a better way of detecting Orientation Change
			//int current_orientation = AConfiguration_getOrientation(app->config);

			int current_width, current_height;
			_glfwGetWindowSizeAndroid(_glfw.windowListHead, &current_width, &current_height);
			_glfwSetWindowSizeAndroid(_glfw.windowListHead, current_height, current_width);

			break;
		}
		default:
			break;
	}
}

static int translateKey(int32_t scancode)
{
	if (scancode < sizeof(_glfw.android.keycodes) / sizeof(_glfw.android.keycodes[0]))
		return _glfw.android.keycodes[scancode];

	return GLFW_KEY_UNKNOWN;
}

static int translateState(int state)
{
	int mods = 0;
	
	if(state & AMETA_SHIFT_ON)
		mods |= GLFW_MOD_SHIFT;
	if(state & AMETA_CTRL_ON)
		mods |= GLFW_MOD_CONTROL;
	if(state & AMETA_ALT_ON)
		mods |= GLFW_MOD_ALT;
	if(state & AMETA_META_ON)
		mods |= GLFW_MOD_SUPER;
	if(state & AMETA_CAPS_LOCK_ON)
		mods |= GLFW_MOD_CAPS_LOCK;
	if(state & AMETA_NUM_LOCK_ON)
		mods |= GLFW_MOD_NUM_LOCK;

	return mods;
}

int32_t handle_app_input(struct android_app* app, AInputEvent* event)
{
	// https://github.com/ocornut/imgui/blob/master/backends/imgui_impl_android.cpp
	int32_t event_type = AInputEvent_getType(event);
	int32_t meta_key_state = AKeyEvent_getMetaState(event);

	switch(event_type)
	{
	case AINPUT_EVENT_TYPE_KEY:
	{
		int32_t key = AKeyEvent_getKeyCode(event);
		int32_t key_action = AKeyEvent_getAction(event);

		// TODO: Test the modifier keys
		switch(key_action)
		{
			case AKEY_EVENT_ACTION_DOWN:
				_glfwInputKey(_glfw.windowListHead, translateKey(key), key, GLFW_PRESS, translateState(meta_key_state));
			case AKEY_EVENT_ACTION_UP:
				_glfwInputKey(_glfw.windowListHead, translateKey(key), key, GLFW_RELEASE, translateState(meta_key_state));
		}

		break;
	}
	case AINPUT_EVENT_TYPE_MOTION:
	{
		int32_t motion_input_action = AMotionEvent_getAction(event);
		int32_t event_pointer_index = (motion_input_action & AMOTION_EVENT_ACTION_POINTER_INDEX_MASK) >> AMOTION_EVENT_ACTION_POINTER_INDEX_SHIFT;
		motion_input_action &= AMOTION_EVENT_ACTION_MASK;

		_glfw.windowListHead->android.mouse_pos_x = AMotionEvent_getX(event, event_pointer_index);
		_glfw.windowListHead->android.mouse_pos_y = AMotionEvent_getY(event, event_pointer_index);

		switch(motion_input_action)
		{
		case AMOTION_EVENT_ACTION_DOWN:
		{
			if((AMotionEvent_getToolType(event, event_pointer_index) == AMOTION_EVENT_TOOL_TYPE_FINGER)
				|| (AMotionEvent_getToolType(event, event_pointer_index) == AMOTION_EVENT_TOOL_TYPE_UNKNOWN))
			{
				_glfwInputMouseClick(_glfw.windowListHead, GLFW_MOUSE_BUTTON_1, GLFW_PRESS, translateState(meta_key_state));
			}

			break;
		}
		case AMOTION_EVENT_ACTION_UP:
		{
			if((AMotionEvent_getToolType(event, event_pointer_index) == AMOTION_EVENT_TOOL_TYPE_FINGER)
				|| (AMotionEvent_getToolType(event, event_pointer_index) == AMOTION_EVENT_TOOL_TYPE_UNKNOWN))
			{
				_glfwInputMouseClick(_glfw.windowListHead, GLFW_MOUSE_BUTTON_1, GLFW_RELEASE, translateState(meta_key_state));
			}

			break;
		}

		// Taken From: https://stackoverflow.com/a/75718929/21319499
		static int32_t pressed_mouse_buttons;
		case AMOTION_EVENT_ACTION_BUTTON_PRESS:
		{
			pressed_mouse_buttons = AMotionEvent_getButtonState(event);

			_glfwInputMouseClick(_glfw.windowListHead, translateMouseButton(pressed_mouse_buttons), GLFW_PRESS, translateState(meta_key_state)); // TODO: Use Modifier Key

			break;
		}
		case AMOTION_EVENT_ACTION_BUTTON_RELEASE:
		{
			// AMotionEvent_getButtonState returns 0 for mouse button release
			// TODO: Explain in detail here
			int32_t mouse_button_state = AMotionEvent_getButtonState(event);
			int32_t meta_key_state = AKeyEvent_getMetaState(event);

			int32_t released_mouse_buttons = (mouse_button_state ^ pressed_mouse_buttons) & pressed_mouse_buttons;
			pressed_mouse_buttons = mouse_button_state;

			_glfwInputMouseClick(_glfw.windowListHead, translateMouseButton(released_mouse_buttons), GLFW_RELEASE, translateState(meta_key_state)); // TODO: Use Modifier Key

			break;
		}
		case AMOTION_EVENT_ACTION_SCROLL:
		{
			float delta_x = AMotionEvent_getAxisValue(event, AMOTION_EVENT_AXIS_HSCROLL, 0);
			float delta_y = AMotionEvent_getAxisValue(event, AMOTION_EVENT_AXIS_VSCROLL, 0);

			LOGI("%f, %f\n", delta_x, delta_y);

			_glfwInputScroll(_glfw.windowListHead, delta_x, delta_y);
		}
		default:
			break;
		}
	}
		return 1;
	default:
		break;
	}

	return 0;
}

void android_main(struct android_app* app)
{
	LOGI("Hello There!");

	app->onAppCmd = handle_cmd;
	app->onInputEvent = handle_app_input;

	pthread_create(&(pthread_t){0}, NULL, (void*)&main, NULL);

	int events;
	struct android_poll_source* source;
	do
	{
		if(ALooper_pollAll(0, NULL, &events, (void**)&source) >= 0)
		{
			if(source)
			{
				source->process(app, source);
			}
		}
	} while(!app->destroyRequested);
}

GLFWbool _glfwConnectAndroid(int platformID, _GLFWplatform* platform)
{
	const _GLFWplatform android =
	{
		GLFW_PLATFORM_ANDROID,
		_glfwInitAndroid,
		_glfwTerminateAndroid,
		// Input
		_glfwGetCursorPosAndroid,
		_glfwSetCursorPosAndroid,
		_glfwSetCursorModeAndroid,
		_glfwSetRawMouseMotionAndroid,
		_glfwRawMouseMotionSupportedAndroid,
		_glfwCreateCursorAndroid,
		_glfwCreateStandardCursorAndroid,
		_glfwDestroyCursorAndroid,
		_glfwSetCursorAndroid,
		_glfwGetScancodeNameAndroid,
		_glfwGetKeyScancodeAndroid,
		_glfwSetClipboardStringAndroid,
		_glfwGetClipboardStringAndroid,
		// Joystick
		_glfwInitJoysticksNull,
		_glfwTerminateJoysticksNull,
		_glfwPollJoystickNull,
		_glfwGetMappingNameNull,
		_glfwUpdateGamepadGUIDNull,
		// Monitor
		_glfwFreeMonitorAndroid,
		_glfwGetMonitorPosAndroid,
		_glfwGetMonitorContentScaleAndroid,
		_glfwGetMonitorWorkareaAndroid,
		_glfwGetVideoModesAndroid,
		_glfwGetVideoModeAndroid,
		_glfwGetGammaRampAndroid,
		_glfwSetGammaRampAndroid,
		// Window
		_glfwCreateWindowAndroid,
		_glfwDestroyWindowAndroid,
		_glfwSetWindowTitleAndroid,
		_glfwSetWindowIconAndroid,
		_glfwGetWindowPosAndroid,
		_glfwSetWindowPosAndroid,
		_glfwGetWindowSizeAndroid,
		_glfwSetWindowSizeAndroid,
		_glfwSetWindowSizeLimitsAndroid,
		_glfwSetWindowAspectRatioAndroid,
		_glfwGetFramebufferSizeAndroid,
		_glfwGetWindowFrameSizeAndroid,
		_glfwGetWindowContentScaleAndroid,
		_glfwIconifyWindowAndroid,
		_glfwRestoreWindowAndroid,
		_glfwMaximizeWindowAndroid,
		_glfwShowWindowAndroid,
		_glfwHideWindowAndroid,
		_glfwRequestWindowAttentionAndroid,
		_glfwFocusWindowAndroid,
		_glfwSetWindowMonitorAndroid,
		_glfwWindowFocusedAndroid,
		_glfwWindowIconifiedAndroid,
		_glfwWindowVisibleAndroid,
		_glfwWindowMaximizedAndroid,
		_glfwWindowHoveredAndroid,
		_glfwFramebufferTransparentAndroid,
		_glfwGetWindowOpacityAndroid,
		_glfwSetWindowResizableAndroid,
		_glfwSetWindowDecoratedAndroid,
		_glfwSetWindowFloatingAndroid,
		_glfwSetWindowOpacityAndroid,
		_glfwSetWindowMousePassthroughAndroid,
		_glfwPollEventsAndroid,
		_glfwWaitEventsAndroid,
		_glfwWaitEventsTimeoutAndroid,
		_glfwPostEmptyEventAndroid,
		// EGL
		_glfwGetEGLPlatformAndroid,
		_glfwGetEGLNativeDisplayAndroid,
		_glfwGetEGLNativeWindowAndroid,
		// Vulkan
		_glfwGetRequiredInstanceExtensionsAndroid,
		_glfwGetPhysicalDevicePresentationSupportAndroid,
		_glfwCreateWindowSurfaceAndroid,
	};

	*platform = android;
	return GLFW_TRUE;
}

GLFWbool _glfwInitAndroid(void)
{
	// init
	while(!_glfw.android.app);

	return GLFW_TRUE;
}

void _glfwTerminateAndroid(void)
{
	_glfwTerminateEGL();

	ANativeActivity_finish(_glfw.android.native_activity);
}

#endif // _GLFW_ANDROID

// jobject log = (*env)->FindClass(env, "android/util/Log");
// jmethodID log_i = (*env)->GetStaticMethodID(env, log, "i", "(Ljava/lang/String;Ljava/lang/String;)I");
// jstring tag = (*env)->NewStringUTF(env, "GLFW_ANDROID_JNI");
// jstring msg = (*env)->NewStringUTF(env, "Hello From JNI!!");
// (*env)->CallStaticIntMethod(env, log, log_i, tag, msg);
