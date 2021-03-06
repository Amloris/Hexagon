#pragma once

#include "Hexagon/Renderer/RenderCommand.h"

#include "Hexagon/Renderer/Shader.h"
#include "Hexagon/Renderer/OrthographicCamera.h"

namespace Hexagon {

	class Renderer
	{
	public:
		static void Init();
		static void Shutdown();

		static void OnWindowResize(uint32_t width, uint32_t height);

		static void BeginScene(OrthographicCamera& camera); // ToDo: Scene parameters
		static void EndScene();

		static void Submit(const Ref<Shader>& shader, 
			               const Ref<VertexArray>& vertexArray, 
			               const glm::mat4& transform = glm::mat4(1.0f));


		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData 
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static Scope<SceneData> s_SceneData;
	};

}