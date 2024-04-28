#pragma once

#include <iostream>

#include "ErrorDirectives.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"

using namespace std;

class VertexArray {
public:
	VertexArray();
	~VertexArray() {}

	void bind() const;
	void unBind() const;

	void addVertexBuffer(VertexBuffer* vBuffer);
	void addIndexBuffer(IndexBuffer* iBuffer);

private:
	unsigned int m_RendererID;
	vector<VertexBuffer*> m_VertexBuffers;
	IndexBuffer* m_IndexBuffer;
};