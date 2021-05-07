/*************************************

Proyecto AEV: Katamari 3DS

Alumnos: 	Nieves Codoñer Gil
			Antoni Garcés Gallardo
			Cristina Padró Ferragut

Curso 2020-2021

*************************************/
#include <citro2d.h>

#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_SPRITES   768
#define SCREEN_WIDTH  400
#define SCREEN_HEIGHT 240
#define CHARACTER_SPEED 2
#define TIMER_TIME 50000

#define SCREEN_MAX_WIDTH_SPRITES  400
#define SCREEN_MAX_HEIGHT_SPRITES 240


// Simple sprite struct
typedef struct
{
	C2D_Sprite spr;
	float dx, dy; // velocity
	int posx, posy;
	bool visible;
	int size;
} Sprite;

// Consider background as sprite(easier)
typedef struct
{
	C2D_Sprite spr;
} Background;

// Katamari status to switch animations
enum statusPlayer
{
	IDLE = 0,
	RIGHT = 1,
	LEFT = 2,
	UP = 3,
	DOWN = 4
};

// Main character (Katamari)
typedef struct
{
	C2D_Sprite spr;
	int posx, posy;
	float dx, dy;
	bool visible;
	int size;
	int status;
	int objectCounter;
} Katamari;


//SpriteSheets 
static C2D_SpriteSheet backgroundSheet,katamariSheet,spriteSheet_normal,spriteSheet_pink, backgroundSheet_menu, spriteSheet_buttons, spriteSheet_creditos;


//static C2D_SpriteSheet item_spritesheets[3];
// Static variables such as sprites
static Sprite sprites[MAX_SPRITES];
static size_t numSprites = MAX_SPRITES/2;
Sprite *sprite = &sprites[MAX_SPRITES];
static int COLLISION_DISTANCE  = 20;

//background
static Background background;

//katamari (main character)
static Katamari katamaris[MAX_SPRITES];

//- Variable for number of objects picked up
static int objectsCounter = 0;
static int currentSize =  1;
//TO DO - Variable for objective size of Katamari (random number between 3 and 10)
static int objectiveSize = 7;
static int nivel = 0;
static int menus = 1;
static bool exitButton = false;
//---------------------------------------------------------------------------------
static void initBackground() {
//---------------------------------------------------------------------------------
	if (menus > 0) {
		C2D_SpriteFromSheet(&background.spr, backgroundSheet_menu, menus-1);
		C2D_SpriteSetCenter(&background.spr, 0.0f, 0.0f);
		C2D_SpriteSetPos(&background.spr, 0.0f, 0.0f);
		C2D_SpriteSetRotation(&background.spr, C3D_Angle(0));
		C2D_SpriteSetDepth(&background.spr, 0.1f);
	}
//---------------------------------------------------------------------------------
	else {
		C2D_SpriteFromSheet(&background.spr, backgroundSheet, nivel);
		C2D_SpriteSetCenter(&background.spr, 0.0f, 0.0f);
		C2D_SpriteSetPos(&background.spr, 0.0f, 0.0f);
		C2D_SpriteSetRotation(&background.spr, C3D_Angle(0));
		C2D_SpriteSetDepth(&background.spr, 0.1f);
	}
}

//---------------------------------------------------------------------------------
static void initSprites() {
//---------------------------------------------------------------------------------
	srand(time(NULL));
	C2D_SpriteSheet variable;
	if (menus > 0) {
		variable = spriteSheet_buttons;
		//Menu principal
		if (menus == 1) {
			for (size_t i = 0; i < MAX_SPRITES; i++) {
				Sprite* sprite = &sprites[i];
				if (i < 4) {
					if (i == 0) {
						//START
						C2D_SpriteFromSheet(&sprite->spr, variable, i);
						C2D_SpriteSetCenter(&sprite->spr, 0.5f, 0.5f);
						C2D_SpriteSetPos(&sprite->spr, 75.0f, 173.0f);
						//C2D_SpriteSetRotation(&sprite->spr, C3D_Angle(rand() / (float)RAND_MAX));
						// Set sprites above background
						C2D_SpriteSetDepth(&sprite->spr, 0.3f);

						sprite->dx = 75.0f;
						sprite->dy = 173.0f;

						sprites[i].visible = true;
						sprites[i].size = 1;
						//START
					}
					if (i == 1) {
						//MENU
						C2D_SpriteFromSheet(&sprite->spr, variable, i);
						C2D_SpriteSetCenter(&sprite->spr, 0.5f, 0.5f);
						C2D_SpriteSetPos(&sprite->spr, 0.0f, 0.0f);
						//C2D_SpriteSetRotation(&sprite->spr, C3D_Angle(rand() / (float)RAND_MAX));
						// Set sprites above background
						C2D_SpriteSetDepth(&sprite->spr, 0.3f);

						sprite->dx = 0.0f;
						sprite->dy = 0.0f;

						sprites[i].visible = false;
						sprites[i].size = 2;
						//MENU
					}
					if (i == 2) {
						//EXIT
						C2D_SpriteFromSheet(&sprite->spr, variable, i);
						C2D_SpriteSetCenter(&sprite->spr, 0.5f, 0.5f);
						C2D_SpriteSetPos(&sprite->spr, 325.0f, 173.0f);
						//C2D_SpriteSetRotation(&sprite->spr, C3D_Angle(rand() / (float)RAND_MAX));
						// Set sprites above background
						C2D_SpriteSetDepth(&sprite->spr, 0.3f);

						sprite->dx = 325.0f;
						sprite->dy = 173.0f;

						sprites[i].visible = true;
						sprites[i].size = 3;
						//EXIT
					}
					if (i == 3) {
						//CREDITOS
						C2D_SpriteFromSheet(&sprite->spr, variable, i);
						C2D_SpriteSetCenter(&sprite->spr, 0.5f, 0.5f);
						C2D_SpriteSetPos(&sprite->spr, 200.0f, 200.0f);
						//C2D_SpriteSetRotation(&sprite->spr, C3D_Angle(rand() / (float)RAND_MAX));
						// Set sprites above background
						C2D_SpriteSetDepth(&sprite->spr, 0.3f);

						sprite->dx = 200.0f;
						sprite->dy = 200.0f;

						sprites[i].visible = true;
						sprites[i].size = 4;
						//CREDITOS
					}
				}
			}
		}
		//Derrota
		if (menus == 2) {
			for (size_t i = 0; i < MAX_SPRITES; i++) {
				Sprite* sprite = &sprites[i];
				if (i < 4) {
					if (i == 0) {
						//START
						C2D_SpriteFromSheet(&sprite->spr, variable, i);
						C2D_SpriteSetCenter(&sprite->spr, 0.5f, 0.5f);
						C2D_SpriteSetPos(&sprite->spr, 0.0f, 0.0f);
						//C2D_SpriteSetRotation(&sprite->spr, C3D_Angle(rand() / (float)RAND_MAX));
						// Set sprites above background
						C2D_SpriteSetDepth(&sprite->spr, 0.3f);

						sprite->dx = 0.0f;
						sprite->dy = 0.0f;

						sprites[i].visible = false;
						sprites[i].size = 1;
						//START
					}
					if (i == 1) {
						//MENU
						C2D_SpriteFromSheet(&sprite->spr, variable, i);
						C2D_SpriteSetCenter(&sprite->spr, 0.5f, 0.5f);
						C2D_SpriteSetPos(&sprite->spr, 75.0f, 173.0f);
						//C2D_SpriteSetRotation(&sprite->spr, C3D_Angle(rand() / (float)RAND_MAX));
						// Set sprites above background
						C2D_SpriteSetDepth(&sprite->spr, 0.3f);

						sprite->dx = 75.0f;
						sprite->dy = 173.0f;

						sprites[i].visible = true;
						sprites[i].size = 2;
						//MENU
					}
					if (i == 2) {
						//EXIT
						C2D_SpriteFromSheet(&sprite->spr, variable, i);
						C2D_SpriteSetCenter(&sprite->spr, 0.5f, 0.5f);
						C2D_SpriteSetPos(&sprite->spr, 325.0f, 173.0f);
						//C2D_SpriteSetRotation(&sprite->spr, C3D_Angle(rand() / (float)RAND_MAX));
						// Set sprites above background
						C2D_SpriteSetDepth(&sprite->spr, 0.3f);

						sprite->dx = 325.0f;
						sprite->dy = 173.0f;

						sprites[i].visible = true;
						sprites[i].size = 3;
						//EXIT
					}
					if (i == 3) {
						//CREDITOS
						C2D_SpriteFromSheet(&sprite->spr, variable, i);
						C2D_SpriteSetCenter(&sprite->spr, 0.5f, 0.5f);
						C2D_SpriteSetPos(&sprite->spr, 200.0f, 200.0f);
						//C2D_SpriteSetRotation(&sprite->spr, C3D_Angle(rand() / (float)RAND_MAX));
						// Set sprites above background
						C2D_SpriteSetDepth(&sprite->spr, 0.3f);

						sprite->dx = 200.0f;
						sprite->dy = 200.0f;

						sprites[i].visible = true;
						sprites[i].size = 4;
						//CREDITOS
					}
				}
			}
		}
		//Victoria (posible mezclar con derrota?)
		if (menus == 3) {
			for (size_t i = 0; i < MAX_SPRITES; i++) {
				Sprite* sprite = &sprites[i];
				if (i < 4) {
					if (i == 0) {
						//START
						C2D_SpriteFromSheet(&sprite->spr, variable, i);
						C2D_SpriteSetCenter(&sprite->spr, 0.5f, 0.5f);
						C2D_SpriteSetPos(&sprite->spr, 0.0f, 0.0f);
						//C2D_SpriteSetRotation(&sprite->spr, C3D_Angle(rand() / (float)RAND_MAX));
						// Set sprites above background
						C2D_SpriteSetDepth(&sprite->spr, 0.3f);

						sprite->dx = 0.0f;
						sprite->dy = 0.0f;

						sprites[i].visible = false;
						sprites[i].size = 1;
						//START
					}
					if (i == 1) {
						//MENU
						C2D_SpriteFromSheet(&sprite->spr, variable, i);
						C2D_SpriteSetCenter(&sprite->spr, 0.5f, 0.5f);
						C2D_SpriteSetPos(&sprite->spr, 75.0f, 173.0f);
						//C2D_SpriteSetRotation(&sprite->spr, C3D_Angle(rand() / (float)RAND_MAX));
						// Set sprites above background
						C2D_SpriteSetDepth(&sprite->spr, 0.3f);

						sprite->dx = 75.0f;
						sprite->dy = 173.0f;

						sprites[i].visible = true;
						sprites[i].size = 2;
						//MENU
					}
					if (i == 2) {
						//EXIT
						C2D_SpriteFromSheet(&sprite->spr, variable, i);
						C2D_SpriteSetCenter(&sprite->spr, 0.5f, 0.5f);
						C2D_SpriteSetPos(&sprite->spr, 325.0f, 173.0f);
						//C2D_SpriteSetRotation(&sprite->spr, C3D_Angle(rand() / (float)RAND_MAX));
						// Set sprites above background
						C2D_SpriteSetDepth(&sprite->spr, 0.3f);

						sprite->dx = 325.0f;
						sprite->dy = 173.0f;

						sprites[i].visible = true;
						sprites[i].size = 3;
						//EXIT
					}
					if (i == 3) {
						//CREDITOS
						C2D_SpriteFromSheet(&sprite->spr, variable, i);
						C2D_SpriteSetCenter(&sprite->spr, 0.5f, 0.5f);
						C2D_SpriteSetPos(&sprite->spr, 200.0f, 200.0f);
						//C2D_SpriteSetRotation(&sprite->spr, C3D_Angle(rand() / (float)RAND_MAX));
						// Set sprites above background
						C2D_SpriteSetDepth(&sprite->spr, 0.3f);

						sprite->dx = 200.0f;
						sprite->dy = 200.0f;

						sprites[i].visible = true;
						sprites[i].size = 4;
						//CREDITOS
					}
				}
			}
		}
		//Creditos
		if (menus == 4) {
			for (size_t i = 0; i < MAX_SPRITES; i++) {
				Sprite* sprite = &sprites[i];
				//BOTONES
				if (i < 4) {
					if (i == 0) {
						//START
						C2D_SpriteFromSheet(&sprite->spr, variable, i);
						C2D_SpriteSetCenter(&sprite->spr, 0.5f, 0.5f);
						C2D_SpriteSetPos(&sprite->spr, 0.0f, 0.0f);
						//C2D_SpriteSetRotation(&sprite->spr, C3D_Angle(rand() / (float)RAND_MAX));
						// Set sprites above background
						C2D_SpriteSetDepth(&sprite->spr, 0.3f);

						sprite->dx = 0.0f;
						sprite->dy = 0.0f;

						sprites[i].visible = false;
						sprites[i].size = 1;
						//START
					}
					if (i == 1) {
						//MENU
						C2D_SpriteFromSheet(&sprite->spr, variable, i);
						C2D_SpriteSetCenter(&sprite->spr, 0.5f, 0.5f);
						C2D_SpriteSetPos(&sprite->spr, 200.0f, 200.0f);
						//C2D_SpriteSetRotation(&sprite->spr, C3D_Angle(rand() / (float)RAND_MAX));
						// Set sprites above background
						C2D_SpriteSetDepth(&sprite->spr, 0.3f);

						sprite->dx = 200.0f;
						sprite->dy = 200.0f;

						sprites[i].visible = true;
						sprites[i].size = 2;
						//MENU
					}
					if (i == 2) {
						//EXIT
						C2D_SpriteFromSheet(&sprite->spr, variable, i);
						C2D_SpriteSetCenter(&sprite->spr, 0.5f, 0.5f);
						C2D_SpriteSetPos(&sprite->spr, 325.0f, 173.0f);
						//C2D_SpriteSetRotation(&sprite->spr, C3D_Angle(rand() / (float)RAND_MAX));
						// Set sprites above background
						C2D_SpriteSetDepth(&sprite->spr, 0.3f);

						sprite->dx = 325.0f;
						sprite->dy = 173.0f;

						sprites[i].visible = false;
						sprites[i].size = 3;
						//EXIT
					}
					if (i == 3) {
						//CREDITOS
						C2D_SpriteFromSheet(&sprite->spr, variable, i);
						C2D_SpriteSetCenter(&sprite->spr, 0.5f, 0.5f);
						C2D_SpriteSetPos(&sprite->spr, 0.0f, 0.0f);
						//C2D_SpriteSetRotation(&sprite->spr, C3D_Angle(rand() / (float)RAND_MAX));
						// Set sprites above background
						C2D_SpriteSetDepth(&sprite->spr, 0.3f);

						sprite->dx = 0.0f;
						sprite->dy = 0.0f;

						sprites[i].visible = false;
						sprites[i].size = 3;
						//CREDITOS
					}
				}
				//ICONOS
				if (i < 7) {
					if (i == 4) {
						C2D_SpriteFromSheet(&sprite->spr, spriteSheet_creditos, 0);
						C2D_SpriteSetCenter(&sprite->spr, 0.5f, 0.5f);
						C2D_SpriteSetPos(&sprite->spr, 100.0f, 175.0f);
						//C2D_SpriteSetRotation(&sprite->spr, C3D_Angle(rand() / (float)RAND_MAX));
						// Set sprites above background
						C2D_SpriteSetDepth(&sprite->spr, 0.3f);

						sprite->dx = 100.0f;
						sprite->dy = 175.0f;

						sprites[i].visible = true;
						sprites[i].size = 1;
						//START
					}
					if (i == 5) {
						//MENU
						C2D_SpriteFromSheet(&sprite->spr, spriteSheet_creditos, 1);
						C2D_SpriteSetCenter(&sprite->spr, 0.5f, 0.5f);
						C2D_SpriteSetPos(&sprite->spr, 200.0f, 140.0f);
						//C2D_SpriteSetRotation(&sprite->spr, C3D_Angle(rand() / (float)RAND_MAX));
						// Set sprites above background
						C2D_SpriteSetDepth(&sprite->spr, 0.3f);

						sprite->dx = 200.0f;
						sprite->dy = 140.0f;

						sprites[i].visible = true;
						sprites[i].size = 1;
						//MENU
					}
					if (i == 6) {
						//EXIT
						C2D_SpriteFromSheet(&sprite->spr, spriteSheet_creditos, 2);
						C2D_SpriteSetCenter(&sprite->spr, 0.5f, 0.5f);
						C2D_SpriteSetPos(&sprite->spr, 300.0f, 175.0f);
						//C2D_SpriteSetRotation(&sprite->spr, C3D_Angle(rand() / (float)RAND_MAX));
						// Set sprites above background
						C2D_SpriteSetDepth(&sprite->spr, 0.3f);

						sprite->dx = 300.0f;
						sprite->dy = 175.0f;

						sprites[i].visible = true;
						sprites[i].size = 1;
						//EXIT
					}
				}
			}
			variable = spriteSheet_creditos;
		}
	}

	else {
		for (size_t i = 0; i < MAX_SPRITES; i++)
		{


			if (nivel == 0) { variable = spriteSheet_pink; }
			else { variable = spriteSheet_normal; }

			Sprite* sprite = &sprites[i];
		if (i < 6) {

			C2D_SpriteFromSheet(&sprite->spr, variable, i);
			C2D_SpriteSetCenter(&sprite->spr, 0.5f, 0.5f);
			C2D_SpriteSetPos(&sprite->spr, rand() % SCREEN_MAX_WIDTH_SPRITES, rand() % SCREEN_MAX_HEIGHT_SPRITES);
			C2D_SpriteSetRotation(&sprite->spr, C3D_Angle(rand() / (float)RAND_MAX));
			// Set sprites above background
			C2D_SpriteSetDepth(&sprite->spr, 0.3f);

			sprite->dx = rand() * 2.0f / RAND_MAX - 4.0f;
			sprite->dy = rand() * 2.0f / RAND_MAX - 4.0f;

			sprites[i].visible = true;
			sprites[i].size = i / 2;

			// Check for collision with the screen boundaries
			/*
			if (sprite->spr.params.pos.y < sprite->spr.params.pos.h / 2.0f && sprite->dy < (sprite->spr.params.pos.h))
				sprite->dy = sprite->dy + 30;
			if (sprite->spr.params.pos.y > (SCREEN_MAX_HEIGHT_SPRITES - (sprite->spr.params.pos.h / 2.0f)) && sprite->dy > 0.0f)
				sprite->dy = sprite->dy - 30;
			if (sprite->spr.params.pos.x > (SCREEN_MAX_WIDTH_SPRITES - (sprite->spr.params.pos.w / 2.0f)) && sprite->dx > 0.0f)
				sprite->dx = sprite->dx - 30;
			if (sprite->spr.params.pos.x < sprite->spr.params.pos.w / 2.0f && sprite->dx < (sprite->spr.params.pos.w))
				sprite->dx = sprite->dx - 30;
				*/

			if ((sprite->spr.params.pos.x < sprite->spr.params.pos.w / 2.0f && sprite->dx < 0.0f) ||
				(sprite->spr.params.pos.x > (SCREEN_WIDTH - (sprite->spr.params.pos.w / 2.0f)) && sprite->dx > 0.0f))
				sprite->dx = -sprite->dx;

			if ((sprite->spr.params.pos.y < sprite->spr.params.pos.h / 2.0f && sprite->dy < 0.0f) ||
				(sprite->spr.params.pos.y > (SCREEN_HEIGHT - (sprite->spr.params.pos.h / 2.0f)) && sprite->dy > 0.0f))
				sprite->dy = -sprite->dy;

			//Set Sprite Scale
			if (sprites[i].size == 0) { C2D_SpriteSetScale(&sprites[i].spr, 0.5f, 0.5f); }
			if (sprites[i].size == 1) { C2D_SpriteSetScale(&sprites[i].spr, 1.0f, 1.0f); }
			if (sprites[i].size == 2) { C2D_SpriteSetScale(&sprites[i].spr, 1.5f, 1.5f); }
		}




		}
	}
}

static void initKatamari(){
 Katamari *katamari = &katamaris[0];
	C2D_SpriteFromSheet(&katamari->spr, katamariSheet, 0);
	C2D_SpriteSetCenter(&katamari->spr, 0.5f, 0.5f);
	C2D_SpriteSetPos(&katamari->spr, 200.0f, 110.0f);

	// Set sprite above background
	C2D_SpriteSetDepth(&katamari->spr, 0.3f);
	katamari->dx = 200.0f;
	katamari->dy = 110.0f;
	katamari->size = katamari->size + 1;

}
 void setKatamariSize(int cont)
{
	Katamari *katamari = &katamaris[0];
	
		if (cont == 1){C2D_SpriteSetScale(&katamari->spr,1.0f,1.0f);}
		if (cont == 2){C2D_SpriteSetScale(&katamari->spr,1.5f,1.5f);}
		if (cont == 3){C2D_SpriteSetScale(&katamari->spr,2.0f,2.0f);}
		if (cont == 4){C2D_SpriteSetScale(&katamari->spr,2.5f,2.5f);}
		if (cont == 5){C2D_SpriteSetScale(&katamari->spr, 3.0f, 3.0f);}
		if(cont == 6){C2D_SpriteSetScale(&katamari->spr, 3.5f, 3.5f);}
		if (cont == 7){C2D_SpriteSetScale(&katamari->spr,4.0f,4.0f);}
		currentSize = cont;
}

//---------------------------------------------------------------------------------
static void movePlayer(u32 kHeld) {
//---------------------------------------------------------------------------------
	Katamari *katamari = &katamaris[0];

	if (kHeld & KEY_UP) {
		// Check for collision with the screen boundaries
		if (katamari->spr.params.pos.y < katamari->spr.params.pos.h / 2.0f && katamari->dy < (katamari->spr.params.pos.h))
			katamari->dy = (katamari->spr.params.pos.h / 2);
		C2D_SpriteFromSheet(&katamari->spr, katamariSheet, 3);
		C2D_SpriteSetCenter(&katamari->spr, 0.5f, 0.5f);
		C2D_SpriteSetPos(&katamari->spr, katamari->dx, katamari->dy);
		C2D_SpriteSetDepth(&katamari->spr, 0.3f);
		setKatamariSize(katamari-> size);
		katamari->dy = katamari->dy- 1;	
	}
	else if (kHeld & KEY_DOWN) {
		// Check for collision with the screen boundaries
		if (katamari->spr.params.pos.y > (SCREEN_HEIGHT - (katamari->spr.params.pos.h / 2.0f)) && katamari->dy > 0.0f)
			katamari->dy = SCREEN_HEIGHT - (katamari->spr.params.pos.h / 2);
		C2D_SpriteFromSheet(&katamari->spr, katamariSheet, 0);
		C2D_SpriteSetCenter(&katamari->spr, 0.5f, 0.5f);
		C2D_SpriteSetPos(&katamari->spr, katamari->dx, katamari->dy);
		C2D_SpriteSetDepth(&katamari->spr, 0.3f);
		setKatamariSize(katamari-> size);
		katamari->dy = katamari->dy + 1;
	}
	else if (kHeld & KEY_RIGHT) {
		// Check for collision with the screen boundaries
		if (katamari->spr.params.pos.x > (SCREEN_WIDTH - (katamari->spr.params.pos.w / 2.0f)) && katamari->dx > 0.0f)
			katamari->dx = SCREEN_WIDTH - (katamari->spr.params.pos.w / 2);
		C2D_SpriteFromSheet(&katamari->spr, katamariSheet, 2);
		C2D_SpriteSetCenter(&katamari->spr, 0.5f, 0.5f);
		C2D_SpriteSetPos(&katamari->spr, katamari->dx, katamari->dy);
		C2D_SpriteSetDepth(&katamari->spr, 0.3f);
		setKatamariSize(katamari-> size);
		katamari->dx = katamari->dx + 1;
	}
	else if (kHeld & KEY_LEFT) {
		// Check for collision with the screen boundaries
		if (katamari->spr.params.pos.x < katamari->spr.params.pos.w / 2.0f && katamari->dx < (katamari->spr.params.pos.w))
			katamari->dx = (katamari->spr.params.pos.w / 2);
		C2D_SpriteFromSheet(&katamari->spr, katamariSheet, 1);
		C2D_SpriteSetCenter(&katamari->spr, 0.5f, 0.5f);
		C2D_SpriteSetPos(&katamari->spr, katamari->dx, katamari->dy);
		C2D_SpriteSetDepth(&katamari->spr, 0.3f);
		setKatamariSize(katamari-> size);
		katamari->dx = katamari->dx - 1;
	}
	

}

static void checkCollisions()
{
	Katamari *katamari = &katamaris[0];
			for (size_t j = 0; j < numSprites; j++)
			{
				if (sprites[j].visible == true)
				{
					if(katamari->size == 2) COLLISION_DISTANCE = 40;
					if(katamari->size == 5) COLLISION_DISTANCE = 50;
					if(katamari->size == 6) COLLISION_DISTANCE = 60;
					if ((abs(katamari->spr.params.pos.x - sprites[j].spr.params.pos.x) < COLLISION_DISTANCE) 
					&& (abs(katamari->spr.params.pos.y - sprites[j].spr.params.pos.y) < COLLISION_DISTANCE))
					{
						if (menus > 0) {
							//START
							if (sprites[j].size == 1 && menus != 4) {
								nivel = 0;
								menus = 0;
								// Initialize sprites
								initSprites();
								//Initialize player
								initKatamari();
								// Initialize background
								initBackground();
								objectsCounter = 0;
								katamaris->size = 1;
								COLLISION_DISTANCE = 20;
							}
							else if (menus == 4){
								katamari->size = katamari->size + 1;
								//object j  disappears
								sprites[j].visible = false;
							}
							//MENU
							if (sprites[j].size == 2) {
								nivel = 0;
								menus = 1;
								sprites[4].visible = false;
								sprites[5].visible = false;
								sprites[6].visible = false;
								// Initialize sprites
								initSprites();
								//Initialize player
								initKatamari();
								// Initialize background
								initBackground();
								objectsCounter = 0;
								katamaris->size = 1;
								COLLISION_DISTANCE = 20;
							}
							//EXIT
							if (sprites[j].size == 3) {
								exitButton = true;
							}
							//CREDITOS
							if (sprites[j].size == 4) {
								nivel = 0;
								menus = 4;
								// Initialize sprites
								initSprites();
								//Initialize player
								initKatamari();
								// Initialize background
								initBackground();
								objectsCounter = 0;
								katamaris->size = 1;
								COLLISION_DISTANCE = 20;
							}
						}
						else if (katamari->size > sprites[j].size) {
							katamari->size = katamari->size + 1;
						//object j  disappears
							sprites[j].visible = false;
							objectsCounter++;
							}
					
					}
				}
			}
}



/*
//---------------------------------------------------------------------------------
static void moveSprites() {
//---------------------------------------------------------------------------------
	for (size_t i = 0; i < numSprites; i++)
	{
		Sprite *sprite = &sprites[i];
		if (i == 3)
		{
			//------------------------------
		}
		else
		{
			C2D_SpriteMove(&sprite->spr, sprite->dx, sprite->dy);
			C2D_SpriteRotateDegrees(&sprite->spr, 1.0f);

			// Check for collision with the screen boundaries
			if ((sprite->spr.params.pos.x < sprite->spr.params.pos.w / 2.0f && sprite->dx < 0.0f) ||
				(sprite->spr.params.pos.x > (SCREEN_WIDTH - (sprite->spr.params.pos.w / 2.0f)) && sprite->dx > 0.0f))
				sprite->dx = -sprite->dx;

			if ((sprite->spr.params.pos.y < sprite->spr.params.pos.h / 2.0f && sprite->dy < 0.0f) ||
				(sprite->spr.params.pos.y > (SCREEN_HEIGHT - (sprite->spr.params.pos.h / 2.0f)) && sprite->dy > 0.0f))
				sprite->dy = -sprite->dy;
		}
	}
}
*/

static void drawScene()
{	
	C2D_DrawSprite(&background.spr);
	// sprites - objects
	for (size_t i = 0; i < numSprites; i ++){
		// objects picked up by the katamari => objects are not drawn
		if(sprites[i].visible == true){
			C2D_DrawSprite(&sprites[i].spr);
		}
	}
	Katamari *katamari = &katamaris[0];
	// Katamari
	for (size_t i = 0; i < 1; i ++){
		if (katamari-> size  == 1){
			C2D_DrawSprite(&katamaris[i].spr);
		}else {
			C2D_DrawSprite(&katamaris[i].spr);
			setKatamariSize(katamari-> size);
		}
		
	}
}


//---------------------------------------------------------------------------------
int main(int argc, char* argv[]) {
//---------------------------------------------------------------------------------
	// Initialize filesystem to load sprites
  	romfsInit();
	// Initialize C2D and C3D libraries for screens
	gfxInitDefault();
	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
	C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
	C2D_Prepare();
	consoleInit(GFX_BOTTOM, NULL);

	// Create screens
	C3D_RenderTarget* top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);

	//Background for the different levels
	// 
	backgroundSheet = C2D_SpriteSheetLoad("romfs:/gfx/background.t3x");
	if (!backgroundSheet)
		svcBreak(USERBREAK_PANIC);

	backgroundSheet_menu = C2D_SpriteSheetLoad("romfs:/gfx/menus.t3x");
	if (!backgroundSheet_menu)
		svcBreak(USERBREAK_PANIC);

	spriteSheet_pink = C2D_SpriteSheetLoad("romfs:/gfx/sprites_pink.t3x");
	if (!spriteSheet_pink)
		svcBreak(USERBREAK_PANIC);

	spriteSheet_buttons = C2D_SpriteSheetLoad("romfs:/gfx/buttons.t3x");
	if (!spriteSheet_buttons)
		svcBreak(USERBREAK_PANIC);

	spriteSheet_creditos = C2D_SpriteSheetLoad("romfs:/gfx/sprites_creditos.t3x");
	if (!spriteSheet_creditos)
		svcBreak(USERBREAK_PANIC);

	spriteSheet_normal = C2D_SpriteSheetLoad("romfs:/gfx/sprites_normal.t3x");
	if (!spriteSheet_normal)
		svcBreak(USERBREAK_PANIC);


		katamariSheet = C2D_SpriteSheetLoad("romfs:/gfx/katamari.t3x");
	if (!katamariSheet)
		svcBreak(USERBREAK_PANIC);


	// Initialize background
	initBackground();
	// Initialize sprites
	initSprites();
	//Initialize player
	initKatamari();

	//Timer in seconds
	double timer = TIMER_TIME;
	//TO DO - Variable for current size of Katamari
	
	
	

	printf("\x1b[16;15H\x1b[47;30mKATAMARI 3DS\x1b[0m");	
	printf("\x1b[18;0H\x1b[47;30mMake the Katamari as big as possible within the time limit\x1b[0m");
	//"Menu" options on top left corner
	printf("\x1b[1;0HHold START to exit.");
	printf("\x1b[3;0HMove character with DPAD");
	printf("\x1b[7;0HKatamari size objective: %d", objectiveSize);

	// Main loop
	while (aptMainLoop())
	{
		//Timer set/reset
		if (menus == 1) { timer = TIMER_TIME; }
		//Timer stops on credits & victory
		if (menus == 2 || menus == 3 || menus == 4) { timer = 0; }
		//Timer
		if (timer == 1) {
			//Make unnecesary sprites invisible
			sprites[4].visible = false;
			sprites[5].visible = false;
			sprites[6].visible = false;
			timer = 0;
			menus = 2;
			nivel = 0;
			initSprites();
			//Initialize player
			initKatamari();
			// Initialize background
			initBackground();
			objectsCounter = 0;
			katamaris->size = 1;
			COLLISION_DISTANCE = 20;
		}
		if (objectsCounter + 1 == objectiveSize) { 
			nivel += 1; 
			// Initialize sprites
			initSprites();
			//Initialize player
			initKatamari();
			// Initialize background
			initBackground();
			objectsCounter = 0;
			katamaris->size = 1;
			COLLISION_DISTANCE = 20;

		}
		hidScanInput();
		
		//hidKeysDown returns information about which buttons have been just pressed (and they weren't in the previous frame)
		u32 kDown = hidKeysDown();
		//hidKeysHeld returns information about which buttons have are held down in this frame
		u32 kHeld = hidKeysHeld();
		//hidKeysUp returns information about which buttons have been just released
		//u32 kUp = hidKeysUp();

		if (kDown & KEY_START) break;
		movePlayer(kHeld);
		
		//moveSprites();
		checkCollisions();
		//Timer countdown
		if(timer > 0) timer--;
		//Checks if exit button touched
		if (exitButton) break;
		// Render the scene
		//top
		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		C2D_TargetClear(top, C2D_Color32f(0.0f, 0.0f, 0.0f, 1.0f));
		C2D_SceneBegin(top);

		drawScene();
		C3D_FrameEnd(0);

		//Print timer
		printf("\x1b[5;0HTimer countdown: %f", timer);
		printf("\x1b[9;0HKatamari current size: %d", currentSize);
		printf("\x1b[11;0HNumber of objects picked up: %d", objectsCounter);
		
	}

	// Delete graphics
	C2D_SpriteSheetFree(spriteSheet_pink);
	C2D_SpriteSheetFree(spriteSheet_normal);
	C2D_SpriteSheetFree(katamariSheet);
	C2D_SpriteSheetFree(backgroundSheet);
	C2D_SpriteSheetFree(backgroundSheet_menu); 
	C2D_SpriteSheetFree(spriteSheet_buttons);
	C2D_SpriteSheetFree(spriteSheet_creditos);


	

	// Deinit libs
	C2D_Fini();
	C3D_Fini();
	gfxExit();
	romfsExit();
	return 0;
}
