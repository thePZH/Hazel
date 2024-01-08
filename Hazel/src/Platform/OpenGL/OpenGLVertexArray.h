#pragma once

#include "Hazel/Renderer/VertexArray.h"

namespace Hazel {
	// 它维护n个vertexbuffer和1个indexbuffer的引用，并不是维护他们的原生内存
	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;

		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const { return m_VertexBuffers; }
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; }
	private:
		uint32_t m_RendererID;
		uint32_t m_VertexBufferIndex = 0;
		std::vector<Ref<VertexBuffer>> m_VertexBuffers;	// 不太懂，本程序内只要顶点缓冲区满了，就发出drawcall，之后再刷新缓冲区并重新记录，并不需要多个，可能是为了适配多种顶点布局的情况吧
		Ref<IndexBuffer> m_IndexBuffer;
	};

}
