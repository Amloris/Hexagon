#include "hxpch.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include"Platform/OpenGL/OpenGLContext.h"

namespace Hexagon 
{

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		HX_CORE_ASSERT(windowHandle, "Window handle is null!");
	}

	void OpenGLContext::Init()
	{
		HX_PROFILE_FUNCTION();

		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		HX_CORE_ASSERT(status, "Failed to initialize Glad!");

		HX_CORE_INFO("OpenGL Info:");
		HX_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		HX_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		HX_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));

		#ifdef HX_ENABLE_ASSERTS
			int versionMajor;
			int versionMinor;
			glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
			glGetIntegerv(GL_MINOR_VERSION, &versionMinor);

			HX_CORE_INFO("  OpenGL Version: {0}.{1}", versionMajor, versionMinor);

			HX_CORE_ASSERT(versionMajor > 4 || (versionMajor == 4 && versionMinor >= 5), "Hexagon requires at least OpenGL version 4.5!");
		#endif
	}

	void OpenGLContext::SwapBuffers()
	{
		HX_PROFILE_FUNCTION();

		glfwSwapBuffers(m_WindowHandle);
	}

}