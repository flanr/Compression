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
	//char buffer[SIZE];
	unsigned char *pixels, buffer[SIZE];

	fopen_s(&file, p_sFilePath, "rb");
	

	fread(buffer, 1, SIZE, file);
	fclose(file);

	memcpy(&header, buffer, sizeof(struct BMPHeader));
	pixels = buffer + header.offset;

	int x = 0, y = 0;
	unsigned char b1, r1, g1, b2, r2, g2;

	char counter = 0;
	char countercounter = 0;

	int size = 0;

	{

		for (int i = 0; i < SIZE; i += 3)
		{
			if (i >= SIZE)
				break;

			if (i == 0)
			{
				b1 = pixels[i];
				g1 = pixels[i + 1];
				r1 = pixels[i + 2];
				counter++;
				if (counter > 255)
				{
					counter = 0;
					countercounter++;
				}
			}
			else
			{
				b2 = pixels[i];
				g2 = pixels[i + 1];
				r2 = pixels[i + 2];

				if (b1 == b2 && r1 == r2 && g1 == g2)
				{
					counter++;
					if (counter > 255)
					{
						counter = 0;
						countercounter++;
					}
				}
				else
				{
					size+=2;
					counter = 1;
					countercounter = 0;
					size += 3;
					b1 = b2;
					r1 = r2;
					g1 = g2;
				}
			}
		}
	}
	
	unsigned char *finishedChars = new unsigned char[size];

	int charcounter = 0;

	counter = 0;
	countercounter = 1;

	for (int i = 0; i < SIZE; i += 3)
	{
		if (i >= SIZE)
			break;

		if (i == 0)
		{
			b1 = pixels[i];
			g1 = pixels[i + 1];
			r1 = pixels[i + 2];
			if ((int)counter == 255 || counter < 0)
			{
				counter = 0;
				countercounter++;
			}
			else
			{
				counter++;
			}
		}
		else
		{
			b2 = pixels[i];
			g2 = pixels[i + 1];
			r2 = pixels[i + 2];

			if (b1 == b2 && r1 == r2 && g1 == g2)
			{
				if ((int)counter == 255 || counter < 0)
				{
					counter = 0;
					countercounter++;
				}
				else
				{
					counter++;
				}


			}
			else
			{
				finishedChars[charcounter++] = countercounter;
				finishedChars[charcounter++] = counter;
				counter = 1;
				countercounter = 1;
				finishedChars[charcounter++] = b1;
				finishedChars[charcounter++] = g1;
				finishedChars[charcounter++] = r1;
				b1 = b2;
				r1 = r2;
				g1 = g2;
			}
		}
	}

	std::ofstream outputChar("exampleChar.txt");

	if (outputChar.is_open())
	{
		outputChar << finishedChars;
	}

	
}

void Compressor::Decompress(const char *p_sFilePath)
{
	

	//of.write((char*)&header, header.size);

	std::ifstream istream("exampleChar.txt", std::ifstream::ate | std::ifstream::binary | std::ifstream::in);
	int size = istream.tellg();
	istream.close();

	FILE* file;

	unsigned char *pixels, buffer[SIZE];

	unsigned char secondbuffer;

	fopen_s(&file, "exampleChar.txt", "rb");


	fread(buffer, 1, SIZE, file);
	fclose(file);

	std::cout << buffer[0];

	bool countingtimes = true;

	int bgrcount = 0;

	int timesFound = 0;

	unsigned char b, g, r;

	unsigned char characters[SIZE];

	for (int i = 0; i < size; i++)
	{
		unsigned char currentChar = buffer[i];

		if (countingtimes)
		{
			timesFound = (int)buffer[i] * 255 + buffer[i+1];
			i++;
			countingtimes = false;
			bgrcount = 0;
		}
		else
		{
			b = buffer[i++];
			g = buffer[i++];
			r = buffer[i];

			for (int x = 0; x < timesFound; x++)
			{
				characters[x] = b;
				x++;
				characters[x] = g;
				x++;
				characters[x] = r;
			}

			countingtimes = true;
		}
	}
}