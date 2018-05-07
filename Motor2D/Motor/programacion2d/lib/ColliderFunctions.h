bool checkCircleCircle(const Vec2& pos1, float radius1, const Vec2& pos2, float radius2);

bool checkCircleRect(const Vec2& circlePos, float circleRadius, const Vec2& rectPos, const Vec2& rectSize);

bool checkRectRect(const Vec2& rectPos1, const Vec2& rectSize1, const Vec2& rectPos2, const Vec2& rectSize2);

bool checkCirclePixels(const Vec2& circlePos, float circleRadius, const Vec2& pixelPos, const Vec2& pixelsSize, const uint8_t* pixels);

bool checkPixelsPixels(const Vec2& pixelPos1, const Vec2& pixelsSize1, const uint8_t* pixels1, const Vec2& pixelPos2, const Vec2& pixelsSize2, const uint8_t* pixels2);

bool checkPixelsRect(const Vec2& pixelPos, const Vec2& pixelsSize, const uint8_t* pixels, const Vec2& rectPos, const Vec2& rectSize);

float clamp(float x, float a, float b);
float max(float a, float b);
float min(float a, float b);