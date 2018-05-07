#include <litegfx.h>
#include <textureManager.h>
#include <stb_image.h>

ltex_t* loadTexture(const char* filename) {
	int xPos = 0;
	int yPos = 0;
	unsigned char* bytesArray = stbi_load(filename, &xPos, &yPos, nullptr, 4);

	ltex_t* texture = ltex_alloc(xPos, yPos, 0);

	ltex_setpixels(texture, bytesArray);

	stbi_image_free(bytesArray);

	return texture;
}