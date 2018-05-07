#include <vec2.h>
#include <stdio.h>
#include <cstdint>
#include <algorithm>
#include <ColliderFunctions.h>

bool checkCircleCircle(const Vec2& pos1, float radius1, const Vec2& pos2, float radius2) {
	float distanceBetweenCenters = pos1.distance(pos2);
	
	if (distanceBetweenCenters < (radius1 + radius2)) {
		return true;
	}
	else {
		return false;
	}
}

bool checkCircleRect(const Vec2& circlePos, float circleRadius, const Vec2& rectPos, const Vec2& rectSize) {
	float midX = rectSize.getX() / 2;
	float midY = rectSize.getY() / 2;

	Vec2 firstRectFirstPos(rectPos.getX() - midX, rectPos.getY() - midY);
	Vec2 firstRectLastPos(rectPos.getX() + midX, rectPos.getY() + midY);

	float closestX = clamp(circlePos.getX(), firstRectFirstPos.getX(), firstRectLastPos.getX());
	float closestY = clamp(circlePos.getY(), firstRectFirstPos.getY(), firstRectLastPos.getY());
	Vec2 closestPoint(closestX, closestY);

	float distanceBetweenPointAndCenter = circlePos.distance(closestPoint);
	
	if (distanceBetweenPointAndCenter < circleRadius) {
		return true;
	}
	else {
		return false;
	}
}

bool checkRectRect(const Vec2& rectPos1, const Vec2& rectSize1, const Vec2& rectPos2, const Vec2& rectSize2) {
	float midX = rectSize1.getX() / 2;
	float midY = rectSize1.getY() / 2;

	Vec2 firstRectFirstPos(rectPos1.getX() - midX, rectPos1.getY() - midY);
	Vec2 firstRectLastPos(rectPos1.getX() + midX, rectPos1.getY() + midY);

	float mid2X = rectSize2.getX() / 2;
	float mid2Y = rectSize2.getY() / 2;

	Vec2 secondRectFirstPos(rectPos2.getX() - mid2X, rectPos2.getY() - mid2Y);
	Vec2 secondRectLastPos(rectPos2.getX() + mid2X, rectPos2.getY() + mid2Y);

	bool xFirstInsideSecond = (firstRectFirstPos.getX() < secondRectLastPos.getX()) && (firstRectLastPos.getX() > secondRectFirstPos.getX());
	bool yFirstInsideSecond = (firstRectFirstPos.getY() < secondRectLastPos.getY()) && (firstRectLastPos.getY() > secondRectFirstPos.getY());

	if (xFirstInsideSecond && yFirstInsideSecond) {
		return true;
	}
	else {
		return false;
	}
}

bool checkPixelsPixels(const Vec2& pixelPos1, const Vec2& pixelsSize1, const uint8_t* pixels1, const Vec2& pixelPos2, const Vec2& pixelsSize2, const uint8_t* pixels2) {
	const int pixels1Size = static_cast<int>(pixelsSize1.getX()) * static_cast<int>(pixelsSize1.getY());
	uint8_t *alphaPixels1 = new uint8_t[pixels1Size];

	const int pixels2Size = static_cast<int>(pixelsSize2.getX()) * static_cast<int>(pixelsSize2.getY());
	uint8_t *alphaPixels2 = new uint8_t[pixels2Size];

	int alphaIndex = 0;
	int isAlpha = 1;
	for (int i = 0; i < pixels1Size * 4; i++) {
		if (isAlpha == 4) {
			alphaPixels1[alphaIndex] = pixels1[i];
			alphaIndex++;
			isAlpha = 1;
		}
		else {
			isAlpha++;
		}
	}

	alphaIndex = 0;
	isAlpha = 1;
	for (int j = 0; j < pixels2Size * 4; j++) {
		if (isAlpha == 4) {
			alphaPixels2[alphaIndex] = pixels2[j];
			alphaIndex++;
			isAlpha = 1;
		}
		else {
			isAlpha++;
		}
	}

	float pixel1MidX = pixelsSize1.getX() / 2;
	float pixel1MidY = pixelsSize1.getY() / 2;
	Vec2 firstRectFirstPos(pixelPos1.getX() - pixel1MidX, pixelPos1.getY() - pixel1MidY);
	Vec2 firstRectLastPos(pixelPos1.getX() + pixel1MidX, pixelPos1.getY() + pixel1MidY);

	float pixel2MidX = pixelsSize2.getX() / 2;
	float pixel2MidY = pixelsSize2.getY() / 2;
	Vec2 secondRectFirstPos(pixelPos2.getX() - pixel2MidX, pixelPos2.getY() - pixel2MidY);
	Vec2 secondRectLastPos(pixelPos2.getX() + pixel2MidX, pixelPos2.getY() + pixel2MidY);

	bool xFirstInsideSecond = (firstRectFirstPos.getX() < secondRectLastPos.getX()) && (firstRectLastPos.getX() > secondRectFirstPos.getX());
	bool yFirstInsideSecond = (firstRectFirstPos.getY() < secondRectLastPos.getY()) && (firstRectLastPos.getY() > secondRectFirstPos.getY());

	if (xFirstInsideSecond && yFirstInsideSecond) {
		// First pixels rect first and last position (top-left & right-bottom)
		int firstRectFirstPosX = static_cast<int>(pixelPos1.getX()) - static_cast<int>(pixel1MidX);
		int firstRectFirstPosY = static_cast<int>(pixelPos1.getY()) - static_cast<int>(pixel1MidY);
		int firstRectLastPosX = static_cast<int>(pixelPos1.getX()) + static_cast<int>(pixel1MidX);
		int firstRectLastPosY = static_cast<int>(pixelPos1.getY()) + static_cast<int>(pixel1MidY);

		// Second pixels rect first and last position (top-left & right-bottom)
		int secondRectFirstPosX = static_cast<int>(pixelPos2.getX()) - static_cast<int>(pixel2MidX);
		int secondRectFirstPosY = static_cast<int>(pixelPos2.getY()) - static_cast<int>(pixel2MidY);
		int secondRectLastPosX = static_cast<int>(pixelPos2.getX()) + static_cast<int>(pixel2MidX);
		int secondRectLastPosY = static_cast<int>(pixelPos2.getY()) + static_cast<int>(pixel2MidY);

		// Collision rectangle position (top-left & right-bottom)
		float firstPointX = max(static_cast<float>(firstRectFirstPosX), static_cast<float>(secondRectFirstPosX));
		float firstPointY = max(static_cast<float>(firstRectFirstPosY), static_cast<float>(secondRectFirstPosY));
		float secondPointX = min(static_cast<float>(firstRectLastPosX), static_cast<float>(secondRectLastPosX));
		float secondPointY = min(static_cast<float>(firstRectLastPosY), static_cast<float>(secondRectLastPosY));

		// Relative first position to first rectangle
		int pixels1FirstPosX = static_cast<int>(firstPointX) - firstRectFirstPosX;
		int pixels1FirstPosY = static_cast<int>(firstPointY) - firstRectFirstPosY;
		// Relative second position to first rectangle
		int pixels1SecondPosX = static_cast<int>(secondPointX) - firstRectFirstPosX;
		int pixels1SecondPosY = static_cast<int>(secondPointY) - firstRectFirstPosY;

		// Relative first position to second rectangle
		int pixels2FirstPosX = static_cast<int>(firstPointX) - secondRectFirstPosX;
		int pixels2FirstPosY = static_cast<int>(firstPointY) - secondRectFirstPosY;

		int i2 = pixels2FirstPosY;
		int j2 = pixels2FirstPosX;

		for (int i = pixels1FirstPosY; i < pixels1SecondPosY; i++) {
			for (int j = pixels1FirstPosX; j < pixels1SecondPosX; j++) {
				int position = i * static_cast<int>(pixelsSize1.getX()) + j;
				int position2 = i2 * static_cast<int>(pixelsSize1.getX()) + j2;
				
				if (alphaPixels1[position] >= 128 && alphaPixels2[position2] >= 128) {
					delete[]alphaPixels1;
					delete[]alphaPixels2;
					
					return true;
				}
				j2++;
			}
			i2++;
			j2 = pixels2FirstPosX;
		}
	}

	delete[]alphaPixels1;
	delete[]alphaPixels2;

	return false;
}

bool checkCirclePixels(const Vec2& circlePos, float circleRadius, const Vec2& pixelPos, const Vec2& pixelsSize, const uint8_t* pixels) {
	const int alphaPixelsSize = static_cast<int>(pixelsSize.getX()) * static_cast<int>(pixelsSize.getY());
	uint8_t *alphaPixels1 = new uint8_t[alphaPixelsSize];

	int alphaIndex = 0;
	int isAlpha = 1;
	for (int i = 0; i < alphaPixelsSize * 4; i++) {
		if (isAlpha == 4) {
			alphaPixels1[alphaIndex] = pixels[i];
			alphaIndex++;
			isAlpha = 1;
		}
		else {
			isAlpha++;
		}
	}

	float pixelMidX = pixelsSize.getX() / 2;
	float pixelMidY = pixelsSize.getY() / 2;
	Vec2 firstRectFirstPos(pixelPos.getX() - pixelMidX, pixelPos.getY() - pixelMidY);
	Vec2 firstRectLastPos(pixelPos.getX() + pixelMidX, pixelPos.getY() + pixelMidY);

	float closestX = clamp(circlePos.getX(), firstRectFirstPos.getX(), firstRectLastPos.getX());
	float closestY = clamp(circlePos.getY(), firstRectFirstPos.getY(), firstRectLastPos.getY());
	Vec2 closestPoint(closestX, closestY);

	float distanceBetweenPointAndCenter = circlePos.distance(closestPoint);

	if (distanceBetweenPointAndCenter < circleRadius) {
		Vec2 circleFirstPos(circlePos.getX() - circleRadius, circlePos.getY() - circleRadius);
		Vec2 circleSize(circleRadius * 2, circleRadius * 2);

		// First pixels rect first and last position (top-left & right-bottom)
		int firstRectFirstPosX = static_cast<int>(pixelPos.getX()) - static_cast<int>(pixelMidX);
		int firstRectFirstPosY = static_cast<int>(pixelPos.getY()) - static_cast<int>(pixelMidY);
		int firstRectLastPosX = static_cast<int>(pixelPos.getX()) + static_cast<int>(pixelMidX);
		int firstRectLastPosY = static_cast<int>(pixelPos.getY()) + static_cast<int>(pixelMidY);

		// Circle rect first and last position (top-left & right-bottom)
		int secondRectFirstPosX = static_cast<int>(circlePos.getX()) - static_cast<int>(circleRadius);
		int secondRectFirstPosY = static_cast<int>(circlePos.getY()) - static_cast<int>(circleRadius);
		int secondRectLastPosX = static_cast<int>(circlePos.getX()) + static_cast<int>(circleRadius);
		int secondRectLastPosY = static_cast<int>(circlePos.getY()) + static_cast<int>(circleRadius);

		// Collision rectangle position (top-left & right-bottom)
		float firstPointX = max(static_cast<float>(firstRectFirstPosX), static_cast<float>(secondRectFirstPosX));
		float firstPointY = max(static_cast<float>(firstRectFirstPosY), static_cast<float>(secondRectFirstPosY));
		float secondPointX = min(static_cast<float>(firstRectLastPosX), static_cast<float>(secondRectLastPosX));
		float secondPointY = min(static_cast<float>(firstRectLastPosY), static_cast<float>(secondRectLastPosY));

		// Relative first position to first rectangle
		int pixels1FirstPosX = static_cast<int>(firstPointX) - firstRectFirstPosX;
		int pixels1FirstPosY = static_cast<int>(firstPointY) - firstRectFirstPosY;
		// Relative second position to first rectangle
		int pixels1SecondPosX = static_cast<int>(secondPointX) - firstRectFirstPosX;
		int pixels1SecondPosY = static_cast<int>(secondPointY) - firstRectFirstPosY;

		for (int i = pixels1FirstPosY; i < pixels1SecondPosY; i++) {
			for (int j = pixels1FirstPosX; j < pixels1SecondPosX; j++) {
				int position = i * static_cast<int>(pixelsSize.getX()) + j;

				if (alphaPixels1[position] >= 128) {
					Vec2 closestPoint2(firstRectFirstPos.getX() + j, firstRectFirstPos.getY() + i);
					if (circlePos.distance(closestPoint2) < circleRadius) {
						delete[]alphaPixels1;

						return true;
					}
				}
			}
		}
	}

	delete[]alphaPixels1;
	return false;
}

bool checkPixelsRect(const Vec2& pixelPos, const Vec2& pixelsSize, const uint8_t* pixels, const Vec2& rectPos, const Vec2& rectSize) {
	const int pixels1Size = static_cast<int>(pixelsSize.getX()) * static_cast<int>(pixelsSize.getY());
	uint8_t *alphaPixels1 = new uint8_t[pixels1Size];

	int alphaIndex = 0;
	int isAlpha = 1;
	for (int i = 0; i < pixels1Size * 4; i++) {
		if (isAlpha == 4) {
			alphaPixels1[alphaIndex] = pixels[i];
			alphaIndex++;
			isAlpha = 1;
		}
		else {
			isAlpha++;
		}
	}

	float pixel1MidX = pixelsSize.getX() / 2;
	float pixel1MidY = pixelsSize.getY() / 2;
	Vec2 firstRectFirstPos(pixelPos.getX() - pixel1MidX, pixelPos.getY() - pixel1MidY);
	Vec2 firstRectLastPos(pixelPos.getX() + pixel1MidX, pixelPos.getY() + pixel1MidY);

	float pixel2MidX = rectSize.getX() / 2;
	float pixel2MidY = rectSize.getY() / 2;
	Vec2 secondRectFirstPos(rectPos.getX() - pixel2MidX, rectPos.getY() - pixel2MidY);
	Vec2 secondRectLastPos(rectPos.getX() + pixel2MidX, rectPos.getY() + pixel2MidY);

	bool xFirstInsideSecond = (firstRectFirstPos.getX() < secondRectLastPos.getX()) && (firstRectLastPos.getX() > secondRectFirstPos.getX());
	bool yFirstInsideSecond = (firstRectFirstPos.getY() < secondRectLastPos.getY()) && (firstRectLastPos.getY() > secondRectFirstPos.getY());

	if (xFirstInsideSecond && yFirstInsideSecond) {
		// First pixels rect first and last position (top-left & right-bottom)
		int firstRectFirstPosX = static_cast<int>(pixelPos.getX()) - static_cast<int>(pixel1MidX);
		int firstRectFirstPosY = static_cast<int>(pixelPos.getY()) - static_cast<int>(pixel1MidY);
		int firstRectLastPosX = static_cast<int>(pixelPos.getX()) + static_cast<int>(pixel1MidX);
		int firstRectLastPosY = static_cast<int>(pixelPos.getY()) + static_cast<int>(pixel1MidY);

		// Second rect first and last position (top-left & right-bottom)
		int secondRectFirstPosX = static_cast<int>(rectPos.getX()) - static_cast<int>(pixel2MidX);
		int secondRectFirstPosY = static_cast<int>(rectPos.getY()) - static_cast<int>(pixel2MidY);
		int secondRectLastPosX = static_cast<int>(rectPos.getX()) + static_cast<int>(pixel2MidX);
		int secondRectLastPosY = static_cast<int>(rectPos.getY()) + static_cast<int>(pixel2MidY);

		// Collision rectangle position (top-left & right-bottom)
		float firstPointX = max(static_cast<float>(firstRectFirstPosX), static_cast<float>(secondRectFirstPosX));
		float firstPointY = max(static_cast<float>(firstRectFirstPosY), static_cast<float>(secondRectFirstPosY));
		float secondPointX = min(static_cast<float>(firstRectLastPosX), static_cast<float>(secondRectLastPosX));
		float secondPointY = min(static_cast<float>(firstRectLastPosY), static_cast<float>(secondRectLastPosY));

		// Relative first position to first rectangle
		int pixels1FirstPosX = static_cast<int>(firstPointX) - firstRectFirstPosX;
		int pixels1FirstPosY = static_cast<int>(firstPointY) - firstRectFirstPosY;
		// Relative second position to first rectangle
		int pixels1SecondPosX = static_cast<int>(secondPointX) - firstRectFirstPosX;
		int pixels1SecondPosY = static_cast<int>(secondPointY) - firstRectFirstPosY;

		for (int i = pixels1FirstPosY; i < pixels1SecondPosY; i++) {
			for (int j = pixels1FirstPosX; j < pixels1SecondPosX; j++) {
				int position = i * static_cast<int>(pixelsSize.getX()) + j;

				if (alphaPixels1[position] >= 128) {
					delete[]alphaPixels1;

					return true;
				}
			}
		}
	}

	delete[]alphaPixels1;

	return false;
}

float clamp(float x, float a, float b) {
	return max(a, min(x, b));
}

float max(float a, float b) {
	if (a > b) {
		return a;
	}
	else {
		return b;
	}
}

float min(float a, float b) {
	if (a < b) {
		return a;
	}
	else {
		return b;
	}
}