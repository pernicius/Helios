#pragma once

#include "HeliosEngine/Renderer/Texture.h"

#include <glad/gl.h>


namespace HeliosEngine {


	class GLTexture2D : public Texture2D
	{
	public:
		GLTexture2D(uint32_t width, uint32_t height);
		GLTexture2D(const std::string& path);
		~GLTexture2D();

		uint32_t GetWidth() const override { return m_Width; }
		uint32_t GetHeight() const override { return m_Height; }
		uint32_t GetRendererID() const override { return m_RendererID; }

		const std::string& GetPath() const override { return m_Path; }

		void SetData(void* data, uint32_t size) override;

		void Bind(uint32_t slot = 0) const override;

		bool IsLoaded() const override { return m_IsLoaded; }

		bool operator==(const Texture& other) const override
		{
			return m_RendererID == other.GetRendererID();
		}
	private:
		std::string m_Path;
		bool m_IsLoaded = false;
		uint32_t m_Width, m_Height;
		uint32_t m_RendererID;
		GLenum m_InternalFormat, m_DataFormat;
	};


} // namespace HeliosEngine
