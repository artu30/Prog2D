#include <vec2.h>
#include <vector>
#include <litegfx.h>
#include <glfw3.h>
#include <cstdint>
#include "pugixml.hpp"
#include <textureManager.h>
#include <ColliderFunctions.h>
#include <Collider.h>
#include <Sprite.h>
#include <World.h>

inline std::string extractPath(const std::string& filename) {
	std::string filenameCopy = filename;
	while (filenameCopy.find("\\") != std::string::npos) {
		filenameCopy.replace(filenameCopy.find("\\"), 1, "/");
	}
	filenameCopy = filenameCopy.substr(0, filenameCopy.rfind('/'));

	if (filenameCopy.size() > 0) filenameCopy += "/";

	return filenameCopy;
}

float World::getClearRed   () const { return mClearRed;   }
float World::getClearGreen () const { return mClearGreen; }
float World::getClearBlue  () const { return mClearBlue;  }

const ltex_t* World::getBackground(size_t layer) const {
	if (layer >= 0 && layer < mBackgrounds.size()) {
		return mBackgrounds.at(layer).mBackgroundTexture;
	}
	else {
		return nullptr;
	}
}

float World::getScrollRatio(size_t layer) const {
	if (layer >= 0 && layer < mBackgrounds.size()) {
		return mBackgrounds.at(layer).mScrollRatio;
	}
	else {
		return 0.0f;
	}
}
void World::setScrollRatio(size_t layer, float ratio) {
	if (layer >= 0 && layer < mBackgrounds.size()) {
		mBackgrounds.at(layer).mScrollRatio = ratio;
	}
}

const Vec2& World::getScrollSpeed(size_t layer) const {
	if (layer >= 0 && layer < mBackgrounds.size()) {
		return mBackgrounds.at(layer).mScrollSpeed;
	}
	else {
		return Vec2();
	}
}

void World::setScrollSpeed(size_t layer, const Vec2& speed) {
	if (layer >= 0 && layer < mBackgrounds.size()) {
		mBackgrounds.at(layer).mScrollSpeed.setX(speed.getX());
		mBackgrounds.at(layer).mScrollSpeed.setY(speed.getY());
	}
}

const Vec2& World::getCameraPosition() const {
	return mCameraPosition;
}

void World::setCameraPosition(const Vec2& pos) {
	mCameraPosition.setX(pos.getX());
	mCameraPosition.setY(pos.getY());
}

void World::addSprite(Sprite* sprite) {
	mSprites.push_back(sprite);
}

void World::removeSprite(Sprite& sprite) {
	for (auto it = mSprites.begin(); it < mSprites.end(); it++) {
		if (sprite.getTexture() == (*it)->getTexture()) {
			it = mSprites.erase(it);
		}
	}
}

void World::update(float deltaTime) {
	// Llamamos callback
	if (mSprites.at(0)->getCallback()) {
		Sprite::CallbackFunc func = mSprites.at(0)->getCallback();

		func(*mSprites.at(0), deltaTime);
	}

	int count = 0;
	for (auto it = mBackgrounds.begin(); it != mBackgrounds.end(); it++) {
		it->mBackgroundPosition.setX(it->mBackgroundPosition.getX() + (getScrollSpeed(count).getX() * deltaTime));
		it->mBackgroundPosition.setY(it->mBackgroundPosition.getY() + (getScrollSpeed(count).getY() * deltaTime));

		count++;
	}

	for (auto it = mSprites.begin(); it < mSprites.end(); it++) {
		(*it)->update(deltaTime);
	}
}

void World::draw(const Vec2& screenSize) {
	if (mWorldSize.getX() < mMapSize.getX()) {
		mWorldSize = mMapSize;
	}
	
	lgfx_clearcolorbuffer(mClearRed, mClearGreen, mClearBlue);

	Vec2 newCameraPos;
	newCameraPos.setX(clamp(mCameraPosition.getX(), mWorldSize.getX() - screenSize.getX(), 0.0f));
	newCameraPos.setY(clamp(mCameraPosition.getY(), mWorldSize.getY() - screenSize.getY(), 0.0f));

	setCameraPosition(newCameraPos);

	lgfx_setorigin(mCameraPosition.getX(), mCameraPosition.getY());

	// Pinto los fondos
	int count = 0;
	for (auto it = mBackgrounds.begin(); it != mBackgrounds.end(); it++) {
		float u1 = 0.0f;
		float v1 = 0.0f;
		float u2 = 0.0f;
		float v2 = 0.0f;

		/* En este punto resto a 1 el ratio de cada mapa por una premisa. Si la camara se mueve a una velocidad
		y el mapa (por ejemplo el de nivel) se mueve a la misma velocidad a la derecha, nunca se verá su incremento visual, 
		sin embargo, si este fondo en concreto no se mueve (ya que es el nivel) la camara delimita que porción vamos a ver.
		Del mismo modo con el resto de fondos, si el segundo se mueve un 0.2 más lento (1 - 0.8) que la cámara se moverá más lento que el 
		primer nivel y más rápido que los sucesivos, y así con los demás fondos */
		float posX = mCameraPosition.getX() * (1 - getScrollRatio(count));
		float posY = mCameraPosition.getY() * (1 - getScrollRatio(count));

		u1 = -mBackgrounds.at(count).mBackgroundPosition.getX() / static_cast<float>(getBackground(count)->width);
		v1 = -mBackgrounds.at(count).mBackgroundPosition.getY() / static_cast<float>(getBackground(count)->height);

		u2 = u1 + mWorldSize.getX() / static_cast<float>(getBackground(count)->width);
		v2 = v1 + mWorldSize.getY() / static_cast<float>(getBackground(count)->height);

		ltex_drawrotsized(getBackground(count), posX, posY, 0.0f, 0.0f, 0.0f, mWorldSize.getX(), mWorldSize.getY(), u1, v1, u2, v2);
		
		count++;
	}

	// Pinto los tiles
	for (auto iterator = mMapTiles.begin(); iterator != mMapTiles.end(); iterator++) {
		int columnInTexture = iterator->mTileId % mTileColumns;
		int rowInTexture = iterator->mTileId / mTileColumns;

		float stepU = 1.0f / mTileColumns;
		float stepV = 1.0f / mTileRows;

		float u1 = static_cast<float>(columnInTexture) * stepU;
		float v1 = static_cast<float>(rowInTexture) * stepV;
		float u2 = u1 + stepU;
		float v2 = v1 + stepV;

		ltex_drawrotsized(mTilesTexture, iterator->mTilePos.getX(), iterator->mTilePos.getY(), 0.0f, 0.5f, 0.5f, iterator->mTileSize.getX(), iterator->mTileSize.getY(), u1, v1, u2, v2);
	}
	
	// Pinto los sprites de la escena
	for (auto it = mSprites.begin(); it < mSprites.end(); it++) {
		(*it)->draw();
	}
}

bool World::loadMap(const char* filename, uint16_t firstColId) {
	pugi::xml_document doc; 
	pugi::xml_parse_result result = doc.load_file(filename); 
	
	if (result) {
		std::string path = extractPath(filename);

		std::string texturePath = path + "tiles.png";
		ltex_t* map = loadTexture(texturePath.c_str());

		mTilesTexture = map;

		pugi::xml_node mapNode = doc.child("map");
		int numTilesWidth = mapNode.attribute("width").as_int();
		int numTilesHeight = mapNode.attribute("height").as_int();
		int tileWidth = mapNode.attribute("tilewidth").as_int();
		int tileHeight = mapNode.attribute("tileheight").as_int();

		pugi::xml_node tileSetNode = doc.child("map").child("tileset");
		int tileCount = tileSetNode.attribute("tilecount").as_int();
		int columns = tileSetNode.attribute("columns").as_int();
		int firstgid = tileSetNode.attribute("firstgid").as_int();

		int rows = tileCount / columns;
		mTileColumns = columns;
		mTileRows = rows;

		int mapWidth = tileWidth * numTilesWidth;
		int mapHeight = tileHeight * numTilesHeight;
		mMapSize.setX(static_cast<float>(mapWidth));
		mMapSize.setY(static_cast<float>(mapHeight));

		Vec2 tileSize(tileWidth, tileHeight);
		int cut = firstgid - firstColId;

		int countX = 0;
		int countY = 0;
		int columnsInMap = mapWidth / tileWidth;
		for (pugi::xml_node tileNode = mapNode.child("layer").child("data").child("tile"); tileNode; tileNode = tileNode.next_sibling("tile")) {
			int gid = tileNode.attribute("gid").as_int();

			if (gid > cut) {
				Tile newTile;
				newTile.mTileId = gid - firstgid;
				newTile.mTileSize = tileSize;

				float posX = countX * tileWidth;
				float posY = countY * tileHeight;

				newTile.mTilePos.setX(posX + tileWidth / 2);
				newTile.mTilePos.setY(posY + tileHeight / 2);

				mMapTiles.push_back(newTile);
			}

			if (countX >= columnsInMap - 1) {
				countY++;
				countX = 0;
			}
			else {
				countX++;
			}
		}

		return true;
	}
	else {
		return false;
	}
}

Vec2 World::getMapSize() const {
	return mMapSize;
}

bool World::moveSprite(Sprite& sprite, const Vec2& amount) {
	// Si la escala es negativa, los calculos de colision saldran mal
	Vec2 spriteSize;
	if (sprite.getSize().getX() < 0) {
		spriteSize.setX(sprite.getSize().getX() * -1);
	}
	else {
		spriteSize.setX(sprite.getSize().getX());
	}
	spriteSize.setY(sprite.getSize().getY());

	// Colision en X
	Vec2 newPosition;
	newPosition.setX(sprite.getPosition().getX() + amount.getX());
	newPosition.setY(sprite.getPosition().getY());
	
	bool collisionInX = false;
	for (auto iterator = mMapTiles.begin(); iterator != mMapTiles.end(); iterator++) {
		if (checkRectRect(newPosition, spriteSize, iterator->mTilePos, iterator->mTileSize)) {
			collisionInX = true;
		}
	}

	if (!collisionInX) {
		sprite.setPosition(newPosition);
	}
	else {
		newPosition.setX(sprite.getPosition().getX());
	}

	// Colision en Y
	newPosition.setY(sprite.getPosition().getY() + amount.getY());

	bool collisionInY = false;
	for (auto iterator = mMapTiles.begin(); iterator != mMapTiles.end(); iterator++) {
		if (checkRectRect(newPosition, spriteSize, iterator->mTilePos, iterator->mTileSize)) {
			if (newPosition.getY() < iterator->mTilePos.getY()) {
				sprite.setCanJump(true);
			}
			collisionInY = true;
		}
	}

	if (!collisionInY) {
		sprite.setPosition(newPosition);
	}

	if (collisionInX || collisionInX) {
		return true;
	}

	return false;
}

float World::clamp(float x, float u, float l) {
	return min(u, max(x, l));
}