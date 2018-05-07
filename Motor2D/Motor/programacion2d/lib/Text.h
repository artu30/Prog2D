class Text {
public:
	float getYPos();
	float getXPos();
	int getXIncrement();
	int getColorR();
	int getColorG();
	int getColorB();
	int getFontToText();

	void setYPos(float y);
	void setXPos(float x);
	void setXIncrement(int inc);
	void setColorR(int inc);
	void setColorG(int inc);
	void setColorB(int inc);
	void setFontToText(int f);

	Text(float x, float y, int xInc, int colorR, int colorG, int colorB, int f);
private:
	float mPosY;
	float mPosX;
	int mXIncrement;
	int mColorR;
	int mColorG;
	int mColorB;
	int mFontToText;
};
