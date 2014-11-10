// Compression.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Compressor.h"


int _tmain(int argc, _TCHAR* argv[])
{
	Compressor comp;

	comp.Compress("image.bmp");

	system("pause");

	return 0;
}

/*
// main.c

#include <stdint.h>
#include <string.h>
#include <stdio.h>

#define SIZE 196608

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

int main()
{
FILE* file;
struct BMPHeader header;
char buffer[SIZE], *pixels;

file = fopen("image.bmp", "rb");
fread(buffer, 1, SIZE, file);
fclose(file);

memcpy(&header, buffer, sizeof(struct BMPHeader));
pixels = buffer + header.offset;

return 0;
}
*/