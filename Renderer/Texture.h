#pragma once

#include <Windows.h>
#include <memory>
#include "SDL.h"
#include <cassert>
#include <iostream>


struct pixel
{
#if SDL_BYTEORDER == SDL_LIL_ENDIAN
	INT8 b;
	INT8 g;
	INT8 r;
	INT8 a;
#else
	INT8 a;
	INT8 r;
	INT8 g;
	INT8 b;
#endif

};


class Texture
{
public:
	explicit Texture(int width, int height);
	~Texture();
	pixel* const getPixel(int x, int y);
	pixel* getPixel();
	void setCollor(int x, int y, int r, int g, int b, int a);

	int Width() { return m_width; }
	int Height() { return m_height; }

private:
	int m_width;
	int m_height;
	pixel* const m_pixels;
	//std::unique_ptr<DirectX::XMINT4[]> m_pixels;

};

