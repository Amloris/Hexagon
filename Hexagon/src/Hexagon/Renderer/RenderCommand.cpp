#include "hxpch.h"

#include "Hexagon/Renderer/RenderCommand.h"

namespace Hexagon 
{

	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();

}