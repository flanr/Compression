#pragma once

#include "stdafx.h"

#pragma pack(push, 1)
struct BMPHeader
{
	uint16_t signature;		// 0x4D42
	uint32_t size;				// unreliable
	uint16_t res0;				// reserved 0
	uint16_t res1;				// reserved 0
	uint32_t offset;			// to start of image
	uint32_t hdrsize;			// 40
	uint32_t width;
	uint32_t height;
	uint16_t planes;			// 1
	uint16_t bpp;					// 1, 4, 8 or 24
	uint32_t compress;		// 0 = none, 1 = rle-8, 2=rle-4
	uint32_t total;				// size in bytes incl padding
	uint32_t h_res;
	uint32_t v_res;
	uint32_t num_color;
	uint32_t imp_color;
};
#pragma pack(pop)

struct BITS
{
	bool b1 : 1;
	bool b2 : 1;
	bool b3 : 1;
	bool b4 : 1;
	bool b5 : 1;
	bool b6 : 1;
	bool b7 : 1;
	bool b8 : 1;
};

struct BITMAPFILEHEADER
{

};

struct PIXEL
{
	unsigned char r, g, b;
	int x, y;
};

class Compressor
{
public:
	Compressor();
	~Compressor();

	void Compress(const char *p_sFilePath);

	void Decompress(const char *p_sFilePath);

private:
	std::vector<std::vector<PIXEL*>> m_vPixels;

	BMPHeader header;
};

