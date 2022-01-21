#pragma once

#include <string>

namespace Hazel {

	class Shader
	{
	public:
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~Shader();

		void Bind() const;
		void Unbind() const;  //Generally just for debugging

	private:
		uint32_t m_RenderID;
	};
}