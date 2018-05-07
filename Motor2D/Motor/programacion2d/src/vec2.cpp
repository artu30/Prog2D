#include <cmath>
#include <vec2.h>

Vec2::Vec2() {
	Init(0, 0);
}

Vec2::Vec2(float coord_x, float coord_y) {
	Init(coord_x, coord_y);
}

Vec2::Vec2(const Vec2& pos) {
	m_x = pos.getX();
	m_y = pos.getY();
}

float Vec2::getX() const {
	return m_x;
}

float Vec2::getY() const {
	return m_y;
}

void Vec2::setX(float newX) {
	m_x = newX;
}

void Vec2::setY(float newY) {
	m_y = newY;
}

Vec2 Vec2::operator+(const Vec2 vec1) const {
	Vec2 newVec;

	newVec.setX(getX() + vec1.getX());
	newVec.setY(getY() + vec1.getY());
	return newVec;
}

Vec2 Vec2::operator-(const Vec2 vec1) const {
	Vec2 newVec;

	newVec.setX(getX() - vec1.getX());
	newVec.setY(getY() - vec1.getY());
	return newVec;
}

Vec2 Vec2::operator*(const Vec2 vec1) const {
	Vec2 newVec;

	newVec.setX(getX() * vec1.getX());
	newVec.setY(getY() * vec1.getY());
	return newVec;
}

Vec2 Vec2::operator/(const Vec2 vec1) const {
	Vec2 newVec;

	newVec.setX(getX() / vec1.getX());
	newVec.setY(getY() / vec1.getY());
	return newVec;
}

Vec2 Vec2::operator +(float scalar) const {
	Vec2 newVec;

	newVec.setX(getX() + scalar);
	newVec.setY(getY() + scalar);
	return newVec;
}
Vec2 Vec2::operator -(float scalar) const {
	Vec2 newVec;

	newVec.setX(getX() - scalar);
	newVec.setY(getY() - scalar);
	return newVec;
}
Vec2 Vec2::operator *(float scalar) const {
	Vec2 newVec;

	newVec.setX(getX() * scalar);
	newVec.setY(getY() * scalar);
	return newVec;
}
Vec2 Vec2::operator /(float scalar) const {
	Vec2 newVec;

	newVec.setX(getX() / scalar);
	newVec.setY(getY() / scalar);
	return newVec;
}

void Vec2::Init(float coord_x, float coord_y) {
	setX(coord_x);
	setY(coord_y);
}

Vec2 Vec2::abs() const{
	Vec2 newVec;

	if (getX() < 0) {
		newVec.setX(::abs(getX()));
	}
	if (getY() < 0) {
		newVec.setY(::abs(getY()));
	}

	return newVec;
}

float Vec2::length() const {
	float firstCoord = getX();
	float secondCoord = getY();

	float l = sqrt((firstCoord * firstCoord) + (secondCoord * secondCoord));

	return l;
}

Vec2 Vec2::normal() const {
	Vec2 newVec;

	float l = length();

	if (l != 0) {
		newVec.setX(getX() / l);
		newVec.setY(getY() / l);

		return newVec;
	}
	else {
		return *this;
	}
}

float Vec2::scalarProduct(const Vec2 vec1) const {
	float scalarProduct = (getX() * vec1.getX()) + (getY() * vec1.getY());

	return scalarProduct;
}

float Vec2::angle(const Vec2 vector) const {
	float angle = atan2((getY() - vector.getY()), vector.getX() - getX());
	angle = angle * RAD_TO_DEGRE;
	
	if (angle < 0) {
		angle = 360 + angle;
	}

	return angle;
}

float Vec2::distance(const Vec2 vector) const {
	float a = vector.getX() - getX();
	float b = vector.getY() - getY();
	float dist = sqrt(a * a + b * b);

	return dist;
}
