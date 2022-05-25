#pragma once

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <string>
#include <stdexcept>

typedef unsigned char UCHAR;
/// \TODO: Probably change to a more standardised image loader
namespace ag
{
	namespace asset
	{
		// Loads a texture into a byte array.
		UCHAR* LoadTexture(std::string path, int* width, int* height)
		{
			int texChannels;
			UCHAR* pixels = stbi_load(path.c_str(), width, height, &texChannels, STBI_rgb_alpha);

			if (!pixels)
			{
				throw std::runtime_error("Failed loading texture asset at path " + path);
			}

			return pixels;
		}

		void UnloadTexture(UCHAR* texture)
		{
			stbi_image_free(texture);
		}
	}
}