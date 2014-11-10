#include "stdafx.h"
#include "Compressor.h"


Compressor::Compressor()
{
}


Compressor::~Compressor()
{
}

void Compressor::Compress(const char *p_sFilePath)
{
	FILE* file;
	struct BMPHeader header;
	//char buffer[SIZE];
	unsigned char *pixels, buffer[SIZE];

	fopen_s(&file, p_sFilePath, "rb");
	

	fread(buffer, 1, SIZE, file);
	fclose(file);

	memcpy(&header, buffer, sizeof(struct BMPHeader));
	pixels = buffer + header.offset;

	int x = 0, y = 0;

	std::vector<PIXEL*> vpixels;

	std::string finishedpixels = "";

	unsigned char b1, r1, g1, b2, r2, g2;

	int counter = 0;

	for (int i = 0; i < SIZE; i+=3)
	{
		if (i >= SIZE)
			break;

		if (i == 0)
		{
			b1 = pixels[i];
			g1 = pixels[i + 1];
			r1 = pixels[i + 2];
			counter++;
		}
		else
		{
			b2 = pixels[i];
			g2 = pixels[i + 1];
			r2 = pixels[i + 2];

			if (b1 == b2 && r1 == r2 && g1 == g2)
			{
				counter++;
			}
			else
			{
				finishedpixels += std::to_string(counter);
				counter = 1;
				finishedpixels += std::to_string(b1) + std::to_string(g1) + std::to_string(r1);

				b1 = b2;
				r1 = r2;
				g1 = g2;
			}
		}
		
		/*PIXEL *pixel = new PIXEL;

		if (x >= 256)
		{
			x = 0;
			y++;

			m_vPixels.push_back(vpixels);

			vpixels.clear();
		}

		pixel->x = x;
		pixel->y = y;

		pixel->b = pixels[i];
		pixel->g = pixels[i+1];
		pixel->r = pixels[i+2];

		x++;

		vpixels.push_back(pixel);*/
	}

	//m_vPixels.push_back(vpixels);

	//std::cout << finishedpixels << std::endl;

	/*BITS b = *(BITS*)(&m_vPixels[30][111]->b);

	

	std::cout << b.b1 << std::endl;
	std::cout << b.b2 << std::endl;
	std::cout << b.b3 << std::endl;
	std::cout << b.b4 << std::endl;
	std::cout << b.b5 << std::endl;
	std::cout << b.b6 << std::endl;
	std::cout << b.b7 << std::endl;
	std::cout << b.b8 << std::endl;

	b = *(BITS*)(&m_vPixels[30][111]->g);

	std::cout << b.b1 << std::endl;
	std::cout << b.b2 << std::endl;
	std::cout << b.b3 << std::endl;
	std::cout << b.b4 << std::endl;
	std::cout << b.b5 << std::endl;
	std::cout << b.b6 << std::endl;
	std::cout << b.b7 << std::endl;
	std::cout << b.b8 << std::endl;

	b = *(BITS*)(&m_vPixels[30][111]->r);

	std::cout << b.b1 << std::endl;
	std::cout << b.b2 << std::endl;
	std::cout << b.b3 << std::endl;
	std::cout << b.b4 << std::endl;
	std::cout << b.b5 << std::endl;
	std::cout << b.b6 << std::endl;
	std::cout << b.b7 << std::endl;
	std::cout << b.b8 << std::endl;

	std::cout << m_vPixels[30][111]->r << std::endl;*/

	//std::cout << buffer;

	/*int size;

	std::ifstream filestream;
	filestream.open(p_sFilePath);
	if (!filestream.is_open())
	{
		std::cout << "Not open muthafucka" << std::endl;
	}
	else
	{
		filestream >> size;

		std::cout << size << std::endl;
	}*/

	std::ofstream output("example.txt");

	if (output.is_open())
	{
		output << finishedpixels;
	}
}