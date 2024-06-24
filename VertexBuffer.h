#pragma once

#include <vector>

#include "VertexBufferLayout.h"
#include "Vertex.h"
#include "ErrorDirectives.h"

class VertexBuffer {
public:
	VertexBuffer() {}
	VertexBuffer(const void* vertices, unsigned int size);
	VertexBuffer(vector<Vertex> vertices);
	~VertexBuffer();

	void bind() const;
	void unBind() const;

	inline const VertexBufferLayout& getLayout() const { return m_Layout; }
	inline void setLayout(const VertexBufferLayout& layout) { m_Layout = layout; }

private:
	unsigned int m_RendererID;
	VertexBufferLayout m_Layout;
};
