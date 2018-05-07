#include <vector>
#include <vec2.h>

class Font {
public:
	static Font* load(const char* filename, float height);
	void draw(const char* text, const Vec2& pos) const;
	float getHeight() const;

	Vec2 getTextSize(const char* text) const;
	ltex_t* getTexture();
	std::vector<stbtt_bakedchar> getCharData();
	int getPwh();
	
	void setTexture(ltex_t* t);
	void setCharData(std::vector<stbtt_bakedchar> charData);
	void setPwh(int wh);
protected:
	Font();

private:
	ltex_t* mTexture;
	std::vector<stbtt_bakedchar> mCharData;
	int mPwh;
};