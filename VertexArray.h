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

	// TODO(j-ka11): maybe delete.
	void addIndexBuffer(IndexBuffer* indexBuffer);
	void addVertexBuffer(VertexBuffer* vertexBuffer);
private:
	unsigned int m_RendererID;

	Buffer* indexBuffer;
	vector<Buffer*> vertexBuffers;
};
