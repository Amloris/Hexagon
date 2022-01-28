#include "hxpch.h"

#include "VertexArray.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Hexagon {

	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: HX_CORE_ASSERT(false, "RenderAPI::None is not supported"); return nullptr;
			case RendererAPI::API::OpenGL: return new OpenGLVertexArray();
		}

		HX_CORE_ASSERT(false, "Invalid RenderAPI!")
		return nullptr;
	}

}