#include "hxpch.h"

#include "Hexagon/Renderer/Renderer.h"
#include "Hexagon/Renderer/Shader.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Hexagon {

	Ref<Shader> Shader::Create(const std::string& filepath)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: HX_CORE_ASSERT(false, "RenderAPI::None is not supported"); return nullptr;
			case RendererAPI::API::OpenGL: return CreateRef<OpenGLShader>(filepath);
		}

		HX_CORE_ASSERT(false, "Invalid RenderAPI!")
		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: HX_CORE_ASSERT(false, "RenderAPI::None is not supported"); return nullptr;
			case RendererAPI::API::OpenGL: return CreateRef<OpenGLShader>(name, vertexSrc, fragmentSrc);
		}

		HX_CORE_ASSERT(false, "Invalid RenderAPI!")
		return nullptr;
	}

	void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
	{
		HX_CORE_ASSERT(!Exists(name), "Shader already exists in shader library!");  // Check if shader already exists...
		m_Shaders[name] = shader;       // Add Shader
	}

	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		auto& name = shader->GetName();
		Add(name, shader);
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& filePath)
	{
		auto shader = Shader::Create(filePath);
		Add(shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filePath)
	{
		auto shader = Shader::Create(filePath);
		Add(name, shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Get(const std::string& name)
	{
		HX_CORE_ASSERT(Exists(name), "Shader does not exists in shader library!");
		return m_Shaders[name];
	}

	bool ShaderLibrary::Exists(const std::string& name) const
	{
		return m_Shaders.find(name) != m_Shaders.end();
	}


}