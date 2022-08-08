#pragma once

#include "HeliosEngine/Renderer/Buffer.h"

#include "GLFW/glfw3.h"


namespace HeliosEngine {


	class GLVertexBuffer : public VertexBuffer
	{
	public:
		GLVertexBuffer(float* vertices, uint32_t size);
		~GLVertexBuffer();

		void Bind() const override;
		void Unbind() const override;
	private:
		uint32_t m_RendererID;
	};


	class GLIndexBuffer : public IndexBuffer
	{
	public:
		GLIndexBuffer(uint32_t* indices, uint32_t count);
		~GLIndexBuffer();

		void Bind() const override;
		void Unbind() const override;

		virtual uint32_t GetCount() const override { return m_Count; };
	private:
		uint32_t m_RendererID;
		uint32_t m_Count;
	};


} // namespace HeliosEngine
