#include "internal.h"

#include <stdlib.h>
#include <string.h>
#include <math.h>

// Get Actual Data

static GLFWvidmode getVideoMode(void)
{
    GLFWvidmode mode;
    mode.width = 1080;
    mode.height = 2640;
    mode.redBits = 8;
    mode.greenBits = 8;
    mode.blueBits = 8;
    mode.refreshRate = 60;
    return mode;
}

void _glfwPollMonitorsAndroid()
{
	const float dpi = 141.f;
    const GLFWvidmode mode = getVideoMode();
    _GLFWmonitor* monitor = _glfwAllocMonitor("Android Monitor",
                                              (int) (mode.width * 25.4f / dpi),
                                              (int) (mode.height * 25.4f / dpi));
    _glfwInputMonitor(monitor, GLFW_CONNECTED, _GLFW_INSERT_FIRST);
}

void _glfwFreeMonitorAndroid(_GLFWmonitor* monitor)
{
	_glfwFreeGammaArrays(&monitor->null.ramp);
}

void _glfwGetMonitorPosAndroid(_GLFWmonitor* monitor, int* xpos, int* ypos)
{
	if (xpos)
        *xpos = 0;
    if (ypos)
        *ypos = 0;
}

void _glfwGetMonitorContentScaleAndroid(_GLFWmonitor* monitor, float* xscale, float* yscale)
{
	if (xscale)
        *xscale = 1.f;
    if (yscale)
        *yscale = 1.f;
}

void _glfwGetMonitorWorkareaAndroid(_GLFWmonitor* monitor, int* xpos, int* ypos, int* width, int* height)
{
	const GLFWvidmode mode = getVideoMode();

    if (xpos)
        *xpos = 0;
    if (ypos)
        *ypos = 10;
    if (width)
        *width = mode.width;
    if (height)
        *height = mode.height - 10;
}

GLFWvidmode* _glfwGetVideoModesAndroid(_GLFWmonitor* monitor, int* found)
{
	GLFWvidmode* mode = _glfw_calloc(1, sizeof(GLFWvidmode));
    *mode = getVideoMode();
    *found = 1;
    return mode;
}

void _glfwGetVideoModeAndroid(_GLFWmonitor* monitor, GLFWvidmode* mode)
{
	*mode = getVideoMode();
}

GLFWbool _glfwGetGammaRampAndroid(_GLFWmonitor* monitor, GLFWgammaramp* ramp)
{
	if (!monitor->android.ramp.size)
    {
        unsigned int i;

        _glfwAllocGammaArrays(&monitor->android.ramp, 256);

        for (i = 0;  i < monitor->android.ramp.size;  i++)
        {
            const float gamma = 2.2f;
            float value;
            value = i / (float) (monitor->null.ramp.size - 1);
            value = powf(value, 1.f / gamma) * 65535.f + 0.5f;
            value = _glfw_fminf(value, 65535.f);

            monitor->android.ramp.red[i]   = (unsigned short) value;
            monitor->android.ramp.green[i] = (unsigned short) value;
            monitor->android.ramp.blue[i]  = (unsigned short) value;
        }
    }

    _glfwAllocGammaArrays(ramp, monitor->android.ramp.size);
    memcpy(ramp->red,   monitor->android.ramp.red,   sizeof(short) * ramp->size);
    memcpy(ramp->green, monitor->android.ramp.green, sizeof(short) * ramp->size);
    memcpy(ramp->blue,  monitor->android.ramp.blue,  sizeof(short) * ramp->size);
    return GLFW_TRUE;
}

void _glfwSetGammaRampAndroid(_GLFWmonitor* monitor, const GLFWgammaramp* ramp)
{
	if (monitor->android.ramp.size != ramp->size)
    {
        _glfwInputError(GLFW_PLATFORM_ERROR, "Android: Gamma ramp size must match current ramp size");
        return;
    }

    memcpy(monitor->android.ramp.red,   ramp->red,   sizeof(short) * ramp->size);
    memcpy(monitor->android.ramp.green, ramp->green, sizeof(short) * ramp->size);
    memcpy(monitor->android.ramp.blue,  ramp->blue,  sizeof(short) * ramp->size);
}
