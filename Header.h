#ifndef HEADER_H
#define HEADER_H

#include <Math.h>
#include <iostream>
#include <string> 

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

#define FPS 120
#define FallAcceleration 1000.0
#define BonusMoveSpeed 150.0
#define FieldSize 10

#define GemSize 64

using namespace sf;

enum GemType
{
	coal,
	iron,
	gold,
	glowstone,
	redstone,
	diamond,
	magma,
	obsidian  
};


class Gem
{
private:
	Texture tex;
	Image img;
	Sprite GemTex;
	GemType type;
	int score;

public:

	double display_x, display_y;
	int mat_x, mat_y;
	int size = 64;
	double speedx = 0; // with falling acceleration
	double speedy = 0; //constant

	   	 
	Gem() {};
	Gem(int pos_x, int pos_y, int m_x, int m_y, GemType gemtype);
	~Gem() {};

	void Move(int startx, int starty);
	void DrawGem(RenderWindow *window);
	int GetScore();
	GemType getType();
	void setType(GemType newtype);
	void changeImage();


};


enum BonusType
{
	bomb,
	colorchange,
};

class Bonus
{
private:
	Texture tex;
	Image img;
	Sprite BonusTex;
	BonusType type;


public:
	 Bonus() {};
	 Bonus(double pos_x, double pos_y, int m_x, int m_y, BonusType bonustype);
	~Bonus() {};

	 void bombCreator(int m_x, int m_y);
	 void colorchangeCreator(int m_x, int m_y);
	 void extrapointsCreator(int m_x, int m_y);
	 virtual void Action(int m_x, int m_y);
	BonusType getType();
	void setType(BonusType type);
	Texture getTexture();
	void setTexture(Texture tex);
	Image getImage();
	void setImage(Image img);
	Sprite getSprite();
	void setSprite(Sprite BonusTex);
	void DrawBonus(RenderWindow *window);

	void BonusMove(int startx, int starty);

	double display_x, display_y;
	int mat_x, mat_y;
	int bonussize = 64;
	double speedx = 0.0; 
	double speedy = 0.0; 


};
class Bomb : public Bonus
{
private:
	Texture tex;
	Image img;
	Sprite BonusTex;
	BonusType type;
public:
	Bomb() {};
	Bomb(double pos_x, double pos_y, int m_x, int m_y, BonusType bonustype);
	~Bomb() {};

	void Action(int m_x, int m_y);
};
class ColorChange : public Bonus
{
private:
	Texture tex;
	Image img;
	Sprite BonusTex;
	BonusType type;
public:
	ColorChange() {};
	ColorChange(double pos_x, double pos_y, int m_x, int m_y, BonusType bonustype);
	~ColorChange() {};
	void Action(int m_x, int m_y);
};
struct SelectedGems
{
	int Fgemx = -1, Fgemy = -1;
	int Sgemx = -1, Sgemy = -1;
};



class FieldManager : protected Gem, protected Bonus
{

public:
	FieldManager();
	~FieldManager();

	void FixField();
	void GemFall(int x_t, int y_t);

	void ToDispCoords(int x, int y, int* new_x, int* new_y);
	void DeleteGem(Gem *gem);
	void DeleteBonus(int i, Bonus* bonus);
	void DeleteAnimations();
	void DeleteBonuses();
	

	Gem* getGem(int i, int j);
	void setGem(int i, int j, Gem* gem);
	Bonus* getBonus(int i);
	void setBonus(int i, Bonus *bonus);

	int PlayerScore = 0;

private:
	Gem ***GemsField;
	Bonus **BonusMass;


};



class FieldRender
{

public:
	FieldRender() {};
	~FieldRender() {};
	
	void ToMatCoords(int disp_x, int disp_y, int* mat_x, int* mat_y);
	   
	void FieldUpdate(FieldManager *Matrix); // values
	void PrintGems(FieldManager *Matrix, RenderWindow *window);  // draw
	void PrintBonuses(FieldManager *Matrix, RenderWindow *window); // draw
	bool AnimationPlaying(FieldManager *Matrix);
	bool LineCheck(FieldManager *Matrix);
	bool CheckRepeat( Gem **mass, int num, Gem* gem);

	void Swap(FieldManager *Matrix, SelectedGems *selected);

};



void GameProcess(FieldManager *Matrix, FieldRender *Field, RenderWindow *window);
void Actions(FieldManager *Matrix, FieldRender *Field, RenderWindow *window, SelectedGems *Selected, bool *Gameover, RectangleShape *rect);
void DeathScreen(FieldManager *Matrix, FieldRender *Field, RenderWindow *window);
void MainMenu(FieldManager *Matrix, FieldRender *Field, RenderWindow *window);

#endif HEADER_H