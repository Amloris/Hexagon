#pragma once

#include "RenderCommand.h"

#include "Shader.h"
#include "OrthographicCamera.h"

namespace Hexagon {

	class Renderer
	{
	public:
		static void BeginScene(OrthographicCamera& camera); // ToDo: Scene parameters
		static void EndScene();

		static void Submit(const std::shared_ptr<Shader>& shader, 
			               const std::shared_ptr<VertexArray>& vertexArray, 
			               const glm::mat4& transform = glm::mat4(1.0f));


		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData 
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* s_SceneData;
	};

}