#include <vec2.h>
#include <litegfx.h>
#include <cstdint>
#include <textureManager.h>
#include <Collider.h>
#include <Sprite.h>

Sprite::Sprite(const ltex_t* tex, int hframes, int vframes) {
	mTexture = tex;

	mHFrames = hframes;
	mVFrames = vframes;

	mBlend = BLEND_ALPHA;

	mRed = 0;
	mGreen = 0;
	mBlue = 0;
	mAlpha = 0;

	mPosition.setX(0);
	mPosition.setY(0);

	mAngle = 0;

	mScale.setX(1);
	mScale.setY(1);

	mPivot.setX(0);
	mPivot.setY(0);

	mFps = 8;

	mCurrentFrame = 0;

	mSize.setX(0);
	mSize.setX(1);

	mPixels = nullptr;

	mCanJump = true;
}

Sprite::~Sprite() {
	delete[]mCollider;
	mCollider = nullptr;

	delete[]mPixels;
	mPixels = nullptr;

	delete[] mTexture;
	mTexture = nullptr;
}

const ltex_t* Sprite::getTexture      () const { return mTexture;      }
lblend_t      Sprite::getBlend        () const { return mBlend;        }
float         Sprite::getRed          () const { return mRed;          }
float         Sprite::getGreen        () const { return mGreen;        }
float         Sprite::getBlue         () const { return mBlue;         }
float         Sprite::getAlpha        () const { return mAlpha;        }
const Vec2    Sprite::getPosition     () const { return mPosition;     }
float         Sprite::getAngle        () const { return mAngle;        }
const Vec2    Sprite::getScale        () const { return mScale;        }
const Vec2    Sprite::getPivot        () const { return mPivot;        }
int           Sprite::getHframes      () const { return mHFrames;      }
int           Sprite::getVframes      () const { return mVFrames;      }
int           Sprite::getFps          () const { return mFps;          }
float         Sprite::getCurrentFrame () const { return mCurrentFrame; }


void Sprite::setTexture      (const ltex_t* tex)                  { mTexture = tex;                                         }
void Sprite::setBlend        (lblend_t mode)                      { mBlend = mode;                                          }
void Sprite::setColor        (float r, float g, float b, float a) { mRed = r; mGreen = g; mBlue = b; mAlpha = a;            }
void Sprite::setPosition     (const Vec2 pos)                     { mPosition.setX(pos.getX()); mPosition.setY(pos.getY()); }
void Sprite::setSize         (const Vec2 size)                    { mSize.setX(size.getX()); mSize.setY(size.getY());       }
void Sprite::setAngle        (float angle)                        { mAngle = angle;                                         }
void Sprite::setScale        (const Vec2 scale)                   { mScale.setX(scale.getX()); mScale.setY(scale.getY());   }
void Sprite::setPivot        (const Vec2 pivot)                   { mPivot.setX(pivot.getX()); mPivot.setY(pivot.getY());   }
void Sprite::setFrames       (int hframes, int vframes)           { mHFrames = hframes; mVFrames = vframes;                 }
void Sprite::setFps          (int fps)                            { mFps = fps;                                             }
void Sprite::setCurrentFrame (int frame)                          { mCurrentFrame = static_cast<float>(frame);              }

Vec2 Sprite::getSize() const {
	Vec2 size;

	float frameWidth = static_cast<float>(getTexture()->width) / static_cast<float>(getHframes());
	float frameHeight = static_cast<float>(getTexture()->height) / static_cast<float>(getVframes());

	size.setX(frameWidth * getScale().getX());
	size.setY(frameHeight * getScale().getY());

	return size;
}

void Sprite::update(float deltaTime) {
	// Actualizo el frame actual y si se pasa de los limites, lo reseteo
	if (getCurrentFrame() < getHframes()) {
		mCurrentFrame += getFps() * deltaTime;
	}
	else if (getCurrentFrame() < 0.0f) {
		setCurrentFrame(getHframes());
	}
	else {
		setCurrentFrame(0);
	}

	setSize(getSize());
}

void Sprite::draw() const {
	int currentFrame = static_cast<int>(getCurrentFrame());

	float frameWidth = static_cast<float>(getTexture()->width) / static_cast<float>(getHframes());
	float frameHeight = static_cast<float>(getTexture()->height) / static_cast<float>(getVframes());

	// Calculo las coordenadas del frame actual (sabiendo que solo hay una fila)
	float u0 = frameWidth * currentFrame / getTexture()->width;
	float v0 = 0;
	float u1 = frameWidth * (currentFrame + 1) / getTexture()->width;
	float v1 = 1;
	
	Vec2 spritePosition = getPosition();

	lgfx_setcolor(getRed(), getGreen(), getBlue(), 1);
	lgfx_setblend(getBlend());

	// Pinto el sprite
	ltex_drawrotsized(getTexture(), spritePosition.getX(), spritePosition.getY(), getAngle(), getPivot().getX(), getPivot().getY(), mSize.getX(), mSize.getY(), u0, v0, u1, v1);
}

void Sprite::setCollisionType(CollisionType type) {
	mCollisionType = type;

	mCollider = nullptr;

	setSize(getSize());
	if (mSize.getX() < 0) {
		mSize.setX(mSize.getX() * -1);
	}

	float maxSize = mSize.getX();
	if (mSize.getY() > maxSize) {
		maxSize = mSize.getY();
	}

	switch (mCollisionType) {
		case COLLISION_NONE:
			mCollider = nullptr;
			break;
		case COLLISION_CIRCLE:
			mCollider = new CircleCollider(mPosition, mSize);
			break;
		case COLLISION_RECT:
			mCollider = new RectCollider(mPosition, mSize);
			break;
		case COLLISION_PIXELS:
			delete[]mPixels;
			mPixels = nullptr;

			mPixels = new uint8_t[static_cast<int>(mSize.getX()) * static_cast<int>(mSize.getY()) * 4];

			ltex_getpixels(mTexture, mPixels);
			mCollider = new PixelsCollider(mPosition, mSize, mPixels);
			break;
	}
}

CollisionType Sprite::getCollisionType() const {
	return mCollisionType;
}

const Collider* Sprite::getCollider() const{
	return mCollider;
}

bool Sprite::collides(const Sprite& other) const {
	if (getCollider() && other.getCollider()) {
		bool collision = mCollider->collides(*other.getCollider());

		return collision;
	}
	else {
		return false;
	}
}