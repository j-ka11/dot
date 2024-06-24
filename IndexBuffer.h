#pragma once

#include <vector>

#define GLEW_STATIC
#include "GL/glew.h"

#include "ErrorDirectives.h"

using namespace std;
class IndexBuffer {
public:
	IndexBuffer() {}
	IndexBuffer(unsigned int* indices, unsigned int count);
	IndexBuffer(vector<unsigned int> indices);
	~IndexBuffer();

	void bind() const;
	void unBind() const;

	inline unsigned int getCount() const { return m_Count; }
private:
	unsigned int m_RendererID;
	unsigned int m_Count;
};
