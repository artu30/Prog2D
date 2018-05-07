enum CollisionType {
	COLLISION_NONE,
	COLLISION_CIRCLE,
	COLLISION_RECT,
	COLLISION_PIXELS
};

class Sprite {
public:
	typedef void(*CallbackFunc)(Sprite&, float);

	Sprite(const ltex_t* tex, int hframes = 1, int vframes = 1);

	~Sprite();

	const ltex_t* getTexture () const;
	void          setTexture (const ltex_t* tex);

	lblend_t getBlend () const;
	void     setBlend (lblend_t mode);

	float getRed   () const;
	float getGreen () const;
	float getBlue  () const;
	float getAlpha () const;
	void setColor  (float r, float g, float b, float a);

	const Vec2 getPosition () const;
	void       setPosition (const Vec2 pos);

	void setSize(const Vec2 size);

	float getAngle () const;
	void  setAngle (float angle);

	const Vec2 getScale () const;
	void       setScale (const Vec2 scale);

	// Tamaño de un frame multiplicado por la escala
	Vec2 getSize() const;

	// Este valor se pasa a ltex_drawrotsized en el pintado
	// para indicar el pivote de rotación
	const Vec2 getPivot () const;
	void       setPivot (const Vec2 pivot);

	int  getHframes () const;
	int  getVframes () const;
	void setFrames  (int hframes, int vframes);

	// Veces por segundo que se cambia el frame de animación
	int  getFps () const;
	void setFps (int fps);

	// Frame actual de animación
	float getCurrentFrame () const;
	void  setCurrentFrame (int frame);

	void update(float deltaTime);

	void draw() const;

	void            setCollisionType (CollisionType type);
	CollisionType   getCollisionType () const;
	const Collider* getCollider      () const;
	bool            collides         (const Sprite& other) const;

	CallbackFunc getCallback()                      { return mCallback;     }
	void         setCallback(CallbackFunc callback) { mCallback = callback; }
	
	void* getUserData ()           { return mUserData; }
	void  setUserData (void* data) { mUserData = data; }

	bool getCanJump() { return mCanJump; }
	void setCanJump(bool canJump) { mCanJump = canJump; }

private:
	const ltex_t*   mTexture;
	lblend_t        mBlend;
	float           mRed;
	float           mGreen;
	float           mBlue;
	float           mAlpha;
	Vec2            mPosition;
	Vec2            mSize;
	float           mAngle;
	Vec2            mScale;
	Vec2            mPivot;
	int             mHFrames;
	int             mVFrames;
	int             mFps;
	float           mCurrentFrame;
	CollisionType   mCollisionType;
	const Collider* mCollider;
	uint8_t*        mPixels;
	CallbackFunc    mCallback;
	void*		    mUserData;
	bool            mCanJump;
};