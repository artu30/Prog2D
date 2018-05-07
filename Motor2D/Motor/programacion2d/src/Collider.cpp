#include <vec2.h>
#include <cstdint>
#include <ColliderFunctions.h>
#include <Collider.h>

/* ------------------------------------------------------- */
/* ------------------- CIRCLE COLLIDER ------------------- */
/* ------------------------------------------------------- */
bool CircleCollider::collides(const Collider& other) const {
	float radius = mCircleSize.getX() / 2;
	if (radius < mCircleSize.getY() / 2) {
		radius = mCircleSize.getY() / 2;
	}

	bool collision = other.collides(mCirclePos, radius);
	return collision;
}
bool CircleCollider::collides(const Vec2& circlePos, float circleRadius) const {
	float radius = mCircleSize.getX() / 2;
	if (radius < mCircleSize.getY() / 2) {
		radius = mCircleSize.getY() / 2;
	}

	bool collision = checkCircleCircle(mCirclePos, radius, circlePos, circleRadius);
	return collision;
}
bool CircleCollider::collides(const Vec2& rectPos, const Vec2& rectSize) const {
	float radius = mCircleSize.getX() / 2;
	if (radius < mCircleSize.getY() / 2) {
		radius = mCircleSize.getY() / 2;
	}

	bool collision = checkCircleRect(mCirclePos, radius, rectPos, rectSize);
	return collision;
}
bool CircleCollider::collides(const Vec2& pixelPos, const Vec2& pixelsSize, const uint8_t* pixels) const {
	float radius = mCircleSize.getX() / 2;
	if (radius < mCircleSize.getY() / 2) {
		radius = mCircleSize.getY() / 2;
	}

	bool collision = checkCirclePixels(mCirclePos, radius, pixelPos, pixelsSize, pixels);
	return collision;
}

/* ------------------------------------------------------- */
/* -------------------- RECT COLLIDER -------------------- */
/* ------------------------------------------------------- */
bool RectCollider::collides(const Collider& other) const {
	bool collision = other.collides(​mRectPos, mRectSize);
	return collision;
}
bool RectCollider::collides(const Vec2& circlePos, float circleRadius) const {
	bool collision = checkCircleRect(circlePos, circleRadius, ​mRectPos, mRectSize);
	return collision;
}
bool RectCollider::collides(const Vec2& rectPos, const Vec2& rectSize) const {
	bool collision = checkRectRect(​mRectPos, mRectSize, rectPos, rectSize);
	return collision;
}
bool RectCollider::collides(const Vec2& pixelPos, const Vec2& pixelsSize, const uint8_t* pixels) const {
	bool collision = checkPixelsRect(pixelPos, pixelsSize, pixels, ​mRectPos, mRectSize);
	return collision;
}

/* ------------------------------------------------------- */
/* -------------------- PIXEL COLLIDER ------------------- */
/* ------------------------------------------------------- */
bool PixelsCollider::collides(const Collider& other) const {
	bool collision = other.collides(mPixelPos, mPixelSize, mPixels);
	return collision;
}
bool PixelsCollider::collides(const Vec2& circlePos, float circleRadius) const {
	bool collision = checkCirclePixels(circlePos, circleRadius, mPixelPos, mPixelSize, mPixels);
	return collision;
}
bool PixelsCollider::collides(const Vec2& rectPos, const Vec2& rectSize) const {
	bool collision = checkPixelsRect(mPixelPos, mPixelSize, mPixels, rectPos, rectSize);
	return collision;
}
bool PixelsCollider::collides(const Vec2& pixelPos, const Vec2& pixelsSize, const uint8_t* pixels) const {
	bool collision = checkPixelsPixels(mPixelPos, mPixelSize, mPixels, pixelPos, pixelsSize, pixels);
	return collision;
}