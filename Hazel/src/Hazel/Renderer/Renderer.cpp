#include "hzpch.h"

#include "Renderer.h"

namespace Hazel {

	RendererAPI Renderer::s_RendererAPI = RendererAPI::OpenGL;  //Hardcoded for OpenGL.  It is the only supported API currently.

}