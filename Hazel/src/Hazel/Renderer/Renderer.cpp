#include "hxpch.h"

#include "Renderer.h"

namespace Hexagon {

	RendererAPI Renderer::s_RendererAPI = RendererAPI::OpenGL;  //Hardcoded for OpenGL.  It is the only supported API currently.

}