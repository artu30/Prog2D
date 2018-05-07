class Collider {
public:
	virtual bool collides(const Collider& other) const = 0;
	virtual bool collides(const Vec2& circlePos, float circleRadius) const = 0;
	virtual bool collides(const Vec2& rectPos, const Vec2& rectSize) const = 0;
	virtual bool collides(const Vec2& pixelPos, const Vec2& pixelsSize, const uint8_t* pixels) const = 0;
};

class CircleCollider : public Collider {
public:
	CircleCollider(const Vec2 &circlePosition, const Vec2 &circleSize) : mCirclePos(circlePosition), mCircleSize(circleSize) { }

	bool collides(const Collider& other) const;
	bool collides(const Vec2& circlePos, float circleRadius) const;
	bool collides(const Vec2& rectPos, const Vec2& rectSize) const;
	bool collides(const Vec2& pixelPos, const Vec2& pixelsSize, const uint8_t* pixels) const;
private:
	const Vec2& mCirclePos;
	const Vec2& mCircleSize;
};

class RectCollider : public Collider {
public:
	RectCollider(const Vec2 &rectPosition, const Vec2& size) : ​mRectPos(rectPosition), mRectSize(size) {}

	bool collides(const Collider& other) const;
	bool collides(const Vec2& circlePos, float circleRadius) const;
	bool collides(const Vec2& rectPos, const Vec2& rectSize) const;
	bool collides(const Vec2& pixelPos, const Vec2& pixelsSize, const uint8_t* pixels) const;
private:
	const Vec2& ​mRectPos;
	const Vec2& mRectSize;
};

class PixelsCollider : public Collider {
public:
	PixelsCollider(const Vec2 &pixelsPosition, const Vec2& size, uint8_t* pixels) : mPixelPos(pixelsPosition), mPixelSize(size) {
		mPixels = pixels;
	}

	bool collides(const Collider& other) const;
	bool collides(const Vec2& circlePos, float circleRadius) const;
	bool collides(const Vec2& rectPos, const Vec2& rectSize) const;
	bool collides(const Vec2& pixelPos, const Vec2& pixelsSize, const uint8_t* pixels) const;
private:
	const Vec2& mPixelPos;
	const Vec2& mPixelSize;
	uint8_t* mPixels;
};