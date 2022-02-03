#include "hxpch.h"

#include "Texture.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLTexture.h"

namespace Hexagon
{
	Ref<Texture2D> Texture2D::Create(const std::string& path) 
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: HX_CORE_ASSERT(false, "RenderAPI::None is not supported"); return nullptr;
			case RendererAPI::API::OpenGL: return std::make_shared<OpenGLTexture2D>(path);
		}

		HX_CORE_ASSERT(false, "Invalid RenderAPI!")
		return nullptr;
	}
}