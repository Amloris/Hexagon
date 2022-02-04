#include "hxpch.h"

#include "Renderer.h"
#include "Shader.h"

#include "Platform/OpenGL/OpenGLShader.h"


namespace Hexagon {

	Shader* Shader::Create(const std::string& filepath)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: HX_CORE_ASSERT(false, "RenderAPI::None is not supported"); return nullptr;
			case RendererAPI::API::OpenGL: return new OpenGLShader(filepath);
		}

		HX_CORE_ASSERT(false, "Invalid RenderAPI!")
		return nullptr;
	}

	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: HX_CORE_ASSERT(false, "RenderAPI::None is not supported"); return nullptr;
			case RendererAPI::API::OpenGL: return new OpenGLShader(vertexSrc, fragmentSrc);
		}

		HX_CORE_ASSERT(false, "Invalid RenderAPI!")
		return nullptr;
	}

}