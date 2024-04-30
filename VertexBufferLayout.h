#pragma once

#include <vector>
#include <string>

#include <GL/glew.h>

using namespace std;
enum class ShaderDataType {
	NONE = 0, FLOAT, FLOAT2, FLOAT3, FLOAT4, MAT3, MAT4, INT, INT2, INT3, INT4, BOOL
};

static unsigned int shaderDataTypeSize(ShaderDataType type) {

	switch (type) {
	case ShaderDataType::FLOAT:     return 4;
	case ShaderDataType::FLOAT2:    return 4 * 2;
	case ShaderDataType::FLOAT3:    return 4 * 3;
	case ShaderDataType::FLOAT4:    return 4 * 4;
	case ShaderDataType::MAT3:      return 4 * 3 * 3;
	case ShaderDataType::MAT4:      return 4 * 4 * 4;
	case ShaderDataType::INT:       return 4;
	case ShaderDataType::INT2:      return 4 * 2;
	case ShaderDataType::INT3:      return 4 * 3;
	case ShaderDataType::INT4:      return 4 * 3;
	case ShaderDataType::BOOL:      return 4 * 1;
	}

	return 0;
}

struct VertexBufferElement {
	string name;
	ShaderDataType type;
	unsigned int size;     //of one element in bytes
	unsigned int offset;   //how far into the vertex is this attribute
	bool normalized;

	VertexBufferElement() {}

	VertexBufferElement(ShaderDataType elementType, const string& elementName, bool elementNormalized = false) {
		name = elementName;
		type = elementType;
		size = shaderDataTypeSize(elementType);
		offset = 0; //need context before calculating true offset
		normalized = elementNormalized;
	}

	const GLint getComponentCount() const {

		switch (type) {
		case ShaderDataType::FLOAT:     return 1;
		case ShaderDataType::FLOAT2:    return 2;
		case ShaderDataType::FLOAT3:    return 3;
		case ShaderDataType::FLOAT4:    return 4;
		case ShaderDataType::MAT3:      return 3 * 3;
		case ShaderDataType::MAT4:      return 4 * 4;
		case ShaderDataType::INT:       return 1;
		case ShaderDataType::INT2:      return 2;
		case ShaderDataType::INT3:      return 3;
		case ShaderDataType::INT4:      return 4;
		case ShaderDataType::BOOL:      return 1;
		}

		return 0;

	}
};

class VertexBufferLayout {
public:
	VertexBufferLayout() {}

	VertexBufferLayout(const initializer_list<VertexBufferElement>& elements) {
		m_Elements = elements;

		calculateOffsetsAndStride();
	}

	inline const vector<VertexBufferElement>& getElements() const { return m_Elements; }
	inline const unsigned int getStride() const { return m_Stride; }
private:
	vector<VertexBufferElement> m_Elements;
	unsigned int m_Stride = 0;    //default...how many bytes is one vertex

	void calculateOffsetsAndStride() {

		unsigned int takeoff = 0;
		m_Stride = 0;
		for (auto& element : m_Elements) {
			element.offset = takeoff;
			takeoff += element.size;
			m_Stride += element.size;
		}

	}
};
