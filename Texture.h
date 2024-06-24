#pragma once

#include <string>
#include <iostream>

#include "stb_image.h"

#include "ErrorDirectives.h"

using namespace std;
class Texture {
private:
	unsigned int m_RendererID;
	string m_FilePath;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_BPP; //last one is bits per pixel
public:
	Texture(const string& filepath);
	~Texture();

	void bind(unsigned int slot = 0) const; //optional parameter...default is 0	
	void unBind() const;

	inline int getWidth() const { return m_Width; }
	inline int getHeight() const { return m_Height; }
};
