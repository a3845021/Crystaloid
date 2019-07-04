#ifndef __CRYSTALOID_SCENE_H__
#define __CRYSTALOID_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <iostream>
#include <math.h>
#include <algorithm>

using namespace std;
using namespace cocos2d;
using namespace CocosDenshion;
using namespace ui;

enum PSCENE {START, GAME, OVER};

struct Crystal
{
	Sprite *sprite;	
	int type;
};

struct Electron
{
	Sprite *sprite;
	float velX;
	float velY;
};

struct Player
{
	Sprite *sprite;
	int life;
	int score;
};

struct Bonus
{
	Sprite *sprite;
	int myType;
	string fn[3] = { "bonus_1.png", "bonus_2.png", "bonus_3.png" };
	float velX = 0;
	float velY = -10;
};

class Crystaloid : public Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
	virtual void update(float dt);
	bool onTouchStart(Touch *touch, Event *event);
	bool onTouchMove(Touch *touch, Event *event);
	bool onTouchEnd(Touch *touch, Event *event);
	void updateCrystal(Sprite *sprite, int num);
	void showWin();
    void createBorder();
	void createLevel();
	void gameOver();
	void startMenu();
	void continueGame();
	void resetVelocity(float dt);
	void startedPosition();
	void startGame();
	void clearLevel();

	template <class T1, class T2>
	bool checkPaddleCollision(T1 &_A, T2 _B);

	// variables
	vector<Crystal> crystals;
	vector<Bonus> bonuses;
	Player player;
	Label *score;
	Label *life;
	Electron electron;
	Size visibleSize;
	float touchPosX;
	string maps[10];
	float oY;
	float velocity;
	bool isStarted;
	Size borderSize;
	int pseudoScene;

    CREATE_FUNC(Crystaloid);
};

#endif // __CRYSTALOID_SCENE_H__
