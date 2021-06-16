#include "Texture.h"

Texture::Texture(int width, int height) :m_width(width), m_height(height),
m_pixels(new pixel[width * height])
{	}

Texture::~Texture()
{
	delete[] m_pixels;
}

pixel* const Texture::getPixel(int x, int y)
{
	assert(y < m_height || x < m_height);
	return &(m_pixels[y*m_width + x]);
}


pixel* Texture::getPixel()
{
	return m_pixels;
}

void Texture::setCollor(int x, int y, int r, int g, int b, int a)
{

	if (x < 0 || y < 0 || x >= m_width || y >= m_height) {
		//std::cout << "Error in setting color. Bad coordinates.\n";
		return;
	}

	if (r >= 256 || g >= 256 || b > 256 || a >= 256 || r < 0 || g < 0 || b < 0 || a < 0) {
		//std::cout << "Error in setting color! Bad color.\n";
		return;
	}

	auto color = &m_pixels[((m_height - y)*m_width) + x];

	color->r = (INT8)r;
	color->g = (INT8)g;
	color->b = (INT8)b;
	color->a = (INT8)a;
}



