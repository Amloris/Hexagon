#pragma once

#include <glm/glm.hpp>

#include "Hexagon/Renderer/VertexArray.h"

namespace Hexagon
{

	class RendererAPI
	{
	public:
		enum class API
		{
			None = 0,        // Headless
			OpenGL = 1,
		};

	public:
		virtual ~RendererAPI() = default;

		virtual void Init() = 0;

		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) = 0;

		inline static API GetAPI() { return s_API; }
		//inline static RendererAPI SetAPI(RendererAPI renderAPI) { s_RendererAPI = renderAPI;  }  //If this is set before the renderer, and the context, and the application, then everything should choose the correct API

		static Scope<RendererAPI> Create();
	private:
		static API s_API;
	};
	
}
