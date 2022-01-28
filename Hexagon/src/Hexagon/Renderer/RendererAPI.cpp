#include "hxpch.h"

#include "RendererAPI.h"

namespace Hexagon {

	RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;   // Hardcoded for OpenGL.  It is the only supported API currently.

}