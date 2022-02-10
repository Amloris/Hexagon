#pragma once

#include <glad/glad.h>

#include "Hexagon/Renderer/Texture.h"

namespace Hexagon
{
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(uint32_t width, uint32_t height);
		OpenGLTexture2D(const std::string& path);
		virtual ~OpenGLTexture2D();

		virtual uint32_t GetWidth() const override { return m_Width; }
		virtual uint32_t GetHeight() const override { return m_Height; }

		virtual void SetData(void* data, uint32_t size) override;

		virtual void Bind(uint32_t slot = 0) const override;
	private:
		std::string m_Path;   // Only kept around for debug/dev builds (hot-reloading textures).  An asset manager should be in charge of doing texture reloading in the future.
		uint32_t m_Width;
		uint32_t m_Height;
		uint32_t m_RendererID;
		GLenum m_Internalformat, m_DataFormat;
	};

}
