#include <litegfx.h>
#include <stb_image.h>
#include <stb_truetype.h>
#include <iostream>
#include <glfw3.h>
#include <Text.h>

Text::Text(float x, float y, int xInc, int colorR, int colorG, int colorB, int f) {
	mPosX = x;
	mPosY = y;
	mXIncrement = xInc;
	mColorR = colorR;
	mColorG = colorG;
	mColorB = colorB;
	mFontToText = f;
}

float Text::getYPos() {
	return mPosY;
}
float Text::getXPos() {
	return mPosX;
}
int Text::getXIncrement() {
	return mXIncrement;
}
int Text::getColorR() {
	return mColorR;
}
int Text::getColorG() {
	return mColorG;
}
int Text::getColorB() {
	return mColorB;
}
int Text::getFontToText() {
	return mFontToText;
}

void Text::setYPos(float y) {
	mPosY = y;
}
void Text::setXPos(float x) {
	mPosX = x;
}
void Text::setXIncrement(int inc) {
	mXIncrement = inc;
}
void Text::setColorR(int r) {
	mColorR = r;
}
void Text::setColorG(int g) {
	mColorG = g;
}
void Text::setColorB(int b) {
	mColorB = b;
}
void Text::setFontToText(int f) {
	mFontToText = f;
}