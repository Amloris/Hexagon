#pragma once


namespace Hexagon {

	enum class RendererAPI
	{
		None = 0,        // Headless
		OpenGL = 1, 
	};

	class Renderer
	{
	public:
		inline static RendererAPI GetAPI() { return s_RendererAPI; }
		//inline static RendererAPI SetAPI(RendererAPI renderAPI) { s_RendererAPI = renderAPI;  }  //If this is set before the renderer, and the context, and the application, then everything should choose the correct API
	private:
		static RendererAPI s_RendererAPI;

	};


}