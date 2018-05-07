struct Background {
	const ltex_t* mBackgroundTexture;
	Vec2          mBackgroundPosition;
	float         mScrollRatio;
	Vec2          mScrollSpeed;
};

struct Tile {
	int     mTileId;
	Vec2    mTileSize;
	Vec2    mTilePos;
};

class World {
public:
	World(float clearRed = 0.15f, float clearGreen = 0.15f, float clearBlue = 0.15f,
		const ltex_t* back0 = nullptr, const ltex_t* back1 = nullptr,
		const ltex_t* back2 = nullptr, const ltex_t* back3 = nullptr) {

		mClearRed   = clearRed;
		mClearGreen = clearGreen;
		mClearBlue  = clearBlue;

		Vec2 initPos(0.0f, 0.0f);

		if (back0) {
			Background bkgnd1;

			bkgnd1.mBackgroundTexture = back0;
			bkgnd1.mBackgroundPosition = initPos;
			bkgnd1.mScrollRatio = 0.0f;
			bkgnd1.mScrollSpeed = Vec2();

			mBackgrounds.push_back(bkgnd1);
		}

		if (back1) {
			Background bkgnd2;

			bkgnd2.mBackgroundTexture = back1;
			bkgnd2.mBackgroundPosition = initPos;
			bkgnd2.mScrollRatio = 0.0f;
			bkgnd2.mScrollSpeed = Vec2();

			mBackgrounds.push_back(bkgnd2);
		}
		
		if (back2) {
			Background bkgnd3;

			bkgnd3.mBackgroundTexture = back2;
			bkgnd3.mBackgroundPosition = initPos;
			bkgnd3.mScrollRatio = 0.0f;
			bkgnd3.mScrollSpeed = Vec2();

			mBackgrounds.push_back(bkgnd3);
		}

		if (back3) {
			Background bkgnd4;

			bkgnd4.mBackgroundTexture = back3;
			bkgnd4.mBackgroundPosition = initPos;
			bkgnd4.mScrollRatio = 0.0f;
			bkgnd4.mScrollSpeed = Vec2();

			mBackgrounds.push_back(bkgnd4);
		}

		mCameraPosition.setX(0.0f);
		mCameraPosition.setY(0.0f);

		mWorldSize.setX(0.0f);
		mWorldSize.setY(0.0f);
		for (auto it = mBackgrounds.begin(); it != mBackgrounds.end(); it++) {
			if (it->mBackgroundTexture->width > mWorldSize.getX()) {
				mWorldSize = Vec2(static_cast<float>(it->mBackgroundTexture->width), static_cast<float>(it->mBackgroundTexture->height));
			}
		}

		mMapSize.setX(0.0f);
		mMapSize.setY(0.0f);
	}
	
	float         getClearRed       ()                                 const;
	float         getClearGreen     ()                                 const;
	float         getClearBlue      ()                                 const;
	const ltex_t* getBackground     (size_t layer)                     const;
	float         getScrollRatio    (size_t layer)                     const;
	void          setScrollRatio    (size_t layer, float ratio);
	const Vec2&   getScrollSpeed    (size_t layer)                     const;
	void          setScrollSpeed    (size_t layer, const Vec2& speed);
	const Vec2&   getCameraPosition ()                                 const;
	void          setCameraPosition (const Vec2& pos);
	void          addSprite         (Sprite* sprite);
	void          removeSprite      (Sprite& sprite);
	void          update            (float deltaTime);
	void          draw              (const Vec2& screenSize);

	bool loadMap    (const char* filename, uint16_t firstColId); 
	Vec2 getMapSize ()                                           const; 
	bool moveSprite (Sprite& sprite, const Vec2& amount);

	float clamp(float x, float u, float l);

private:
	float                   mClearRed;
	float                   mClearGreen;
	float                   mClearBlue;
	std::vector<Sprite*>    mSprites;
	std::vector<Background> mBackgrounds;
	Vec2                    mCameraPosition;
	Vec2                    mWorldSize;
	Vec2                    mMapSize;
	std::vector<Tile>       mMapTiles;
	ltex_t*                 mTilesTexture;
	int                     mTileColumns;
	int                     mTileRows;
};