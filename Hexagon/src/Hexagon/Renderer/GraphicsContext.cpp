#include "hxpch.h"

#include "Hexagon/Renderer/GraphicsContext.h"
#include "Hexagon/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLContext.h"

namespace Hexagon {

	Scope<GraphicsContext> GraphicsContext::Create(void* window)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    HX_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
		}

		HX_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}