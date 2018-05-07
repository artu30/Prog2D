#include <litegfx.h>
#include <stb_image.h>
#include <stb_truetype.h>
#include <iostream>
#include <glfw3.h>
#include <Font.h>
#include <textureManager.h>
#include <iostream>
#include <fstream>

Font::Font() {};

Vec2 Font::getTextSize(const char* text) const {
	stbtt_aligned_quad *quad = new stbtt_aligned_quad();
	float xPos = 0;
	float yPos = 0;

	int textLength = strlen(text);

	float textPosX = 0;
	float textPosY = 0;
	float initialSize = 0;
	float finalSize = 0;
	for (int i = 0; i < textLength; i++) {
		int charIndex(text[i] - 32);

		stbtt_GetBakedQuad(mCharData.data(), mPwh, mPwh, charIndex, &xPos, &yPos, quad, true);
		if (i == 0) {
			initialSize = quad->x0;
		}
		if (i == textLength - 1) {
			finalSize = quad->x1;
		}
		
		if ((quad->y1 - quad->y0) > textPosY) {
			textPosY = quad->y1 - quad->y0;
		}
	}
	textPosX = finalSize - initialSize;

	Vec2 sizeToReturn(textPosX, textPosY);

	return sizeToReturn;
}
float Font::getHeight() const {
	return 60;
}
ltex_t* Font::getTexture() {
	return mTexture;
}
std::vector<stbtt_bakedchar> Font::getCharData() {
	return mCharData;
}
int Font::getPwh() {
	return mPwh;
}

void Font::setTexture(ltex_t* t) {
	mTexture = t;
}
void Font::setCharData(std::vector<stbtt_bakedchar> charData) {
	mCharData = charData;
}
void Font::setPwh(int wh) {
	mPwh = wh;
}

Font* Font::load(const char* filename, float height) {
	std::ifstream i(filename, std::ios::binary);
	if (!i.is_open()) {
		return nullptr;
	}

	i.seekg(0, std::ios::end);
	long fileSize = i.tellg();
	i.seekg(0, std::ios::beg);

	std::vector<char> buffer(sizeof(char) * fileSize);

	i.read(buffer.data(), fileSize);

	i.close();
	size_t size = 16;
	std::vector<uint8_t> pixels(size * size);

	std::vector<stbtt_bakedchar> charData(128);

	while (stbtt_BakeFontBitmap((unsigned char*)buffer.data(), 0, height, pixels.data(), size, size, 32, 96, charData.data()) <= 0) {
		size *= 2;
		pixels.resize(size * size);
	}

	std::vector<uint8_t> colorPixels;
	for (auto iterator = pixels.begin(); iterator != pixels.end(); iterator++) {
		colorPixels.push_back(static_cast<unsigned char>(255));
		colorPixels.push_back(static_cast<unsigned char>(255));
		colorPixels.push_back(static_cast<unsigned char>(255));
		colorPixels.push_back(*iterator);
	}

	ltex_t *fontTexture = ltex_alloc(size, size, 0);
	ltex_setpixels(fontTexture, colorPixels.data());

	Font * font = new Font();
	font->setTexture(fontTexture);
	font->setCharData(charData);
	font->setPwh(size);

	return font;
}

void Font::draw(const char* text, const Vec2& pos) const {
	stbtt_aligned_quad *quad = new stbtt_aligned_quad();
	float xPos = pos.getX();
	float yPos = pos.getY();

	int textLength = strlen(text);
	
	float textPosX = 0;
	float textPosY = 0;
	for (int i = 0; i < textLength; i++) {
		int charIndex(text[i] - 32);
		
		stbtt_GetBakedQuad(mCharData.data(), mPwh, mPwh, charIndex, &xPos, &yPos, quad, true);
		
		ltex_drawrotsized(mTexture, quad->x0, quad->y0, 0, 0, 0, quad->x1 - quad->x0, quad->y1 - quad->y0, quad->s0, quad->t0, quad->s1, quad->t1);
	}
}