#define DEGRE_TO_RAD 0.01745329252f
#define RAD_TO_DEGRE 57.2958f

class Vec2 {
public:
	Vec2();
	Vec2(float coord_x, float coord_y);
	Vec2(const Vec2& pos);
	
	float getX() const;
	float getY() const;
	void setX(float newX);
	void setY(float newY);

	Vec2 operator +(const Vec2 vec1) const;
	Vec2 operator -(const Vec2 vec1) const;
	Vec2 operator *(const Vec2 vec1) const;
	Vec2 operator /(const Vec2 vec1) const;

	Vec2 operator +(float scalar) const;
	Vec2 operator -(float scalar) const;
	Vec2 operator *(float scalar) const;
	Vec2 operator /(float scalar) const;

	Vec2 abs() const;
	float length() const;
	Vec2 normal() const;
	float scalarProduct(const Vec2 vec1) const;
	float angle(const Vec2 vector) const;
	float distance(const Vec2 vector) const;

private:
	float m_x;
	float m_y;
	void Init(float coord_X, float coord_y);
};