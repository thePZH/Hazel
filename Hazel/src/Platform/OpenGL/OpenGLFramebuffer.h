#pragma once

#include "Hazel/Renderer/Framebuffer.h"

namespace Hazel {

	class OpenGLFramebuffer : public Framebuffer
	{
	public:
		OpenGLFramebuffer(const FramebufferSpecification& spec);
		virtual ~OpenGLFramebuffer();

		void Invalidate();

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual void Resize(uint32_t width, uint32_t height) override;
		virtual int ReadPixel(uint32_t attachmentIndex, int x, int y) override;

		virtual void ClearAttachment(uint32_t attachmentIndex, int value) override;

		virtual uint32_t GetColorAttachmentRendererID(uint32_t index = 0) const override { HZ_CORE_ASSERT(index < m_ColorAttachments.size()); return m_ColorAttachments[index]; }

		virtual const FramebufferSpecification& GetSpecification() const override { return m_Specification; }
	private:
		uint32_t m_RendererID = 0;																			// framebuffer ID
		FramebufferSpecification m_Specification;															// 尺寸,附件的描述，采样点数

		std::vector<FramebufferTextureSpecification> m_ColorAttachmentSpecifications;						// 所有颜色附件描述
		FramebufferTextureSpecification m_DepthAttachmentSpecification = FramebufferTextureFormat::None;	// 深度附件描述，只有1个

		std::vector<uint32_t> m_ColorAttachments;															// 所有颜色附件的ID
		uint32_t m_DepthAttachment = 0;																		// 深度附件ID
	};

}
