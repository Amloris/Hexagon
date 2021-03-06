#include "hxpch.h"

#include <glad/glad.h>

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Hexagon {

	//This will only live here temporarily!
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Float:   return GL_FLOAT;
			case ShaderDataType::Float2:  return GL_FLOAT;
			case ShaderDataType::Float3:  return GL_FLOAT;
			case ShaderDataType::Float4:  return GL_FLOAT;
			case ShaderDataType::Mat3:	  return GL_FLOAT;
			case ShaderDataType::Mat4:	  return GL_FLOAT;
			case ShaderDataType::Int:	  return GL_INT;
			case ShaderDataType::Int2:	  return GL_INT;
			case ShaderDataType::Int3:	  return GL_INT;
			case ShaderDataType::Int4:	  return GL_INT;
			case ShaderDataType::Bool:	  return GL_BOOL;
		}

		HX_CORE_ASSERT(false, "Unknown ShaderDataType:ShaderDataTypeToOpenGLBaseType!");
		return 0;
	};

	OpenGLVertexArray::OpenGLVertexArray() 
	{
		HX_PROFILE_FUNCTION();

		glCreateVertexArrays(1, &m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		HX_PROFILE_FUNCTION();

		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const 
	{
		HX_PROFILE_FUNCTION();

		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		HX_PROFILE_FUNCTION();

		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
	{
		HX_PROFILE_FUNCTION();

		HX_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(m_VertexBufferIndex);
			glVertexAttribPointer(m_VertexBufferIndex,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.Offset);
			m_VertexBufferIndex++;
		}

		//Add to list of vertex buffers
		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
	{
		HX_PROFILE_FUNCTION();

		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();

		//Add to index buffer
		m_IndexBuffer = indexBuffer;
	}

}
