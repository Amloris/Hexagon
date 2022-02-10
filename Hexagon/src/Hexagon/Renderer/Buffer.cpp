#include "hxpch.h"

#include "Hexagon/Renderer/Buffer.h"
#include "Hexagon/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Hexagon {


	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size) {
		switch (Renderer::GetAPI()) 
		{
			case RendererAPI::API::None:
				HX_CORE_ASSERT(false, "RenderAPI::None is not supported");
				return nullptr;
			case RendererAPI::API::OpenGL:
				return CreateRef<OpenGLVertexBuffer>(vertices, size);
		}

		HX_CORE_ASSERT(false, "Invalid RenderAPI!")
		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t size) {
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:
				HX_CORE_ASSERT(false, "RenderAPI::None is not supported");
				return nullptr;
			case RendererAPI::API::OpenGL:
				return CreateRef<OpenGLIndexBuffer>(indices, size);
		}

		HX_CORE_ASSERT(false, "Invalid RenderAPI!")
		return nullptr;
	}

}