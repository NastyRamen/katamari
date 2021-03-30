// Simple citro2d sprite drawing example
// Images borrowed from:
//   https://kenney.nl/assets/space-shooter-redux
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


// Simple sprite struct
typedef struct
{
	C2D_Sprite spr;
	float dx, dy; // velocity
} Sprite;

typedef struct
{
	C2D_Sprite spr;
	float dx, dy; // velocity
} Background;


static C2D_SpriteSheet spriteSheet,backgroundSheet;
static Sprite sprites[MAX_SPRITES];
static size_t numSprites = MAX_SPRITES/2;
static Background background;

/*
//  Text buffer --- ????????????
C2D_TextBuf g_staticBuf, g_dynamicBuf;
C2D_Text g_staticText[4];
*/

Sprite *sprite = &sprites[MAX_SPRITES];



static void initBackground()
{
	//---------------------------------------------------------------------------------
	C2D_SpriteFromSheet(&background.spr, backgroundSheet, 0);
	C2D_SpriteSetCenter(&background.spr, 0.0f, 0.0f);
	C2D_SpriteSetPos(&background.spr, 0.0f, 0.0f);
	C2D_SpriteSetRotation(&background.spr, C3D_Angle(0));
	C2D_SpriteSetDepth(&background.spr, 0.1f);

}


//---------------------------------------------------------------------------------
static void initSprites() {
//---------------------------------------------------------------------------------
	//size_t numImages = C2D_SpriteSheetCount(spriteSheet);
	srand(time(NULL));

	for (size_t i = 0; i < MAX_SPRITES; i++)
	{
		Sprite *sprite = &sprites[i];
		if(i!=3){
		C2D_SpriteFromSheet(&sprite->spr,  spriteSheet, i);
		C2D_SpriteSetCenter(&sprite->spr, 0.5f, 0.5f);
		C2D_SpriteSetPos(&sprite->spr, rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT);
		C2D_SpriteSetRotation(&sprite->spr, C3D_Angle(rand() / (float)RAND_MAX));
		// se encarga de ponerlos encima del background
		C2D_SpriteSetDepth(&sprite->spr, 0.3f);
		}else if (i==3){
			C2D_SpriteFromSheet(&sprite->spr, spriteSheet, i);
			C2D_SpriteSetCenter(&sprite->spr, 0.5f, 0.5f);
			C2D_SpriteSetPos(&sprite->spr, rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT);
			C2D_SpriteSetDepth(&sprite->spr, 0.3f);
		}
		
	}
	/*
	for (size_t i = 0; i < MAX_SPRITES; i++)
	{
		//puntero a la estructura Sprite
		Sprite *sprite = &sprites[i];	
		
		//if (i != 3 )
		//{ // Random image, position, rotation and speed
			C2D_SpriteFromSheet(&sprite->spr, spriteSheet, i);
			C2D_SpriteSetCenter(&sprite->spr, 0.5f, 0.5f);
			C2D_SpriteSetPos(&sprite->spr, rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT);
			C2D_SpriteSetRotation(&sprite->spr, C3D_Angle(rand() / (float)RAND_MAX));
			sprite->dx = rand() * 4.0f / RAND_MAX - 2.0f;
			sprite->dy = rand() * 4.0f / RAND_MAX - 2.0f;
		//}
		
		if (i == 3){
			C2D_SpriteFromSheet(&sprite->spr, spriteSheet, i);
			C2D_SpriteSetCenter(&sprite->spr, 0.5f, 0.5f);
			C2D_SpriteSetPos(&sprite->spr, rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT);
			sprite->dx = rand() * 4.0f / RAND_MAX - 2.0f;
			sprite->dy = rand() * 4.0f / RAND_MAX - 2.0f;


		}
		
		
	}
	*/
}


static void movePlayer(u32 kHeld)
{
	Sprite *sprite = &sprites[3];


	if (kHeld & KEY_UP)
	{
	C2D_SpriteFromSheet(&sprite->spr, spriteSheet, 3);
	C2D_SpriteSetCenter(&sprite->spr, 0.5f, 0.5f);
	C2D_SpriteSetPos(&sprite->spr, sprite->dx, sprite->dy);
	C2D_SpriteSetDepth(&sprite->spr, 0.3f);
	
	//C2D_SpriteMove(&sprite->spr, sprite->dx, sprite->dy);
	sprite->dy = sprite->dy- 1;
	
			
		
	}else
	if (kHeld & KEY_DOWN)
	{
	C2D_SpriteFromSheet(&sprite->spr, spriteSheet, 3);
	C2D_SpriteSetCenter(&sprite->spr, 0.5f, 0.5f);
	C2D_SpriteSetPos(&sprite->spr, sprite->dx, sprite->dy);
	C2D_SpriteSetDepth(&sprite->spr, 0.3f);
	
	//C2D_SpriteMove(&sprite->spr, sprite->dx, sprite->dy);
	sprite->dy = sprite->dy + 1;

	
	}
	else if (kHeld & KEY_RIGHT)
	{
	
	
	C2D_SpriteFromSheet(&sprite->spr, spriteSheet, 3);
	C2D_SpriteSetCenter(&sprite->spr, 0.5f, 0.5f);
	C2D_SpriteSetPos(&sprite->spr, sprite->dx, sprite->dy);
	C2D_SpriteSetDepth(&sprite->spr, 0.3f);
	
	//C2D_SpriteMove(&sprite->spr, sprite->dx, sprite->dy);
	sprite->dx = sprite->dx + 1;
	}
	else if (kHeld & KEY_LEFT)
	{
	
	
	C2D_SpriteFromSheet(&sprite->spr, spriteSheet, 3);
	C2D_SpriteSetCenter(&sprite->spr, 0.5f, 0.5f);
	C2D_SpriteSetPos(&sprite->spr, sprite->dx, sprite->dy);
	C2D_SpriteSetDepth(&sprite->spr, 0.3f);
	
	//C2D_SpriteMove(&sprite->spr, sprite->dx, sprite->dy);
	sprite->dx = sprite->dx - 1;
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


static void sceneInit(void)
{
	// Create two text buffers: one for static text, and another one for
	// dynamic text - the latter will be cleared at each frame.
	g_staticBuf  = C2D_TextBufNew(4096); // support up to 4096 glyphs in the buffer
	g_dynamicBuf = C2D_TextBufNew(4096);

	// Optimize the static text strings
	C2D_TextOptimize(&g_staticText[1]);
}

static void sceneRender(float size)
{
	C2D_TextBufClear(g_dynamicBuf);
	// Draw static text strings
	C2D_DrawText(&g_staticText[1], C2D_AtBaseline | C2D_WithColor, 16.0f, 210.0f, 0.5f, 0.5f, 0.75f, C2D_Color32f(2.0f,0.0f,0.0f,3.0f));

	char buf[160];
	C2D_Text dynText;

	snprintf(buf,sizeof(buf),"Timer countdown: %zu/%u", numSprites, MAX_SPRITES);
	C2D_TextParse(&dynText, g_dynamicBuf, buf);
	C2D_TextOptimize(&dynText);
	C2D_DrawText(&dynText, C2D_AlignCenter, 150.0f, 90.0f, 0.5f, 0.5f, 0.5f);

	snprintf(buf,sizeof(buf),"Size objective:     %6.2f%%", C3D_GetProcessingTime() * 6.0f);
	C2D_TextParse(&dynText, g_dynamicBuf, buf);
	C2D_TextOptimize(&dynText);
	C2D_DrawText(&dynText, C2D_AlignCenter, 150.0f, 110.0f, 0.5f, 0.5f, 0.5f);

	snprintf(buf,sizeof(buf),"Current size:     %6.2f%%", C3D_GetDrawingTime() * 6.0f);
	C2D_TextParse(&dynText, g_dynamicBuf, buf);
	C2D_TextOptimize(&dynText);
	C2D_DrawText(&dynText, C2D_AlignCenter, 150.0f, 130.0f, 0.5f, 0.5f, 0.5f);

	snprintf(buf,sizeof(buf),"Number of objects picked up:  %6.2f%%", C3D_GetCmdBufUsage() * 100.0f);
	C2D_TextParse(&dynText, g_dynamicBuf, buf);
	C2D_TextOptimize(&dynText);
	C2D_DrawText(&dynText, C2D_AlignCenter, 150.0f, 150.0f, 0.5f, 0.5f, 0.5f);

	snprintf(buf,sizeof(buf),"Timer:  %6.2f%%", C3D_GetCmdBufUsage() * 100.0f);
	C2D_TextParse(&dynText, g_dynamicBuf, buf);
	C2D_TextOptimize(&dynText);
	C2D_DrawText(&dynText, C2D_AlignCenter, 150.0f, 170.0f, 0.5f, 0.5f, 0.5f);
}

C2D_TextBuf g_staticBuf;
C2D_Text g_staticText[4];
*/
//---------------------------------------------------------------------------------
int main(int argc, char* argv[]) {
//---------------------------------------------------------------------------------
	// Init libs
	romfsInit();
	gfxInitDefault();
	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
	C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
	C2D_Prepare();
	consoleInit(GFX_BOTTOM, NULL);

	// Create screens
	C3D_RenderTarget* top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);

	//Load background 
	backgroundSheet = C2D_SpriteSheetLoad("romfs:/gfx/background.t3x");
	if (!backgroundSheet)
		svcBreak(USERBREAK_PANIC);

	// Load graphics
	spriteSheet = C2D_SpriteSheetLoad("romfs:/gfx/sprites.t3x");
		if (!spriteSheet) svcBreak(USERBREAK_PANIC);

		

	// Initialize background
	initBackground();

	// Initialize sprites
	initSprites();

	//C3D_RenderTarget *bot = C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT);

	//sceneInit();
	//float size = 0.5f;

	//Timer in seconds
	double timer = 100000;
	//TO DO - Variable for current size of Katamari
	int currentSize = 1;
	//TO DO - Variable for objective size of Katamari (random number between 3 and 10)
	int objectiveSize = 0;
	//TO DO - Variable for number of objects picked up
	int objectsCounter = 0;

	printf("\x1b[16;15H\x1b[47;30mKATAMARI 3DS\x1b[0m");	
	printf("\x1b[18;0H\x1b[47;30mMake the Katamari as big as possible within the time limit\x1b[0m");
	//"Menu" options on top left corner
	printf("\x1b[1;0HHold START to exit.");
	printf("\x1b[3;0HMove character with DPAD");
	printf("\x1b[7;0HKatamari size objective: %d", objectiveSize);

	// Main loop
	while (aptMainLoop())
	{
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
		
		//Timer countdown
		if(timer > 0) timer--;

		// Render the scene
		//top
		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		C2D_TargetClear(top, C2D_Color32f(0.0f, 0.0f, 0.0f, 1.0f));
		C2D_SceneBegin(top);
		
		for (size_t i = 0; i < numSprites; i ++)
			C2D_DrawSprite(&sprites[i].spr);

		C2D_DrawSprite(&background.spr);
		C3D_FrameEnd(0);
		/*
		//bot
		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		C2D_TargetClear(bot, C2D_Color32(0x68, 0xB0, 0xD8, 0xFF));
		C2D_SceneBegin(bot);
		sceneRender(size);
		*/
		//Print timer
		printf("\x1b[5;0HTimer countdown: %f", timer);
		printf("\x1b[9;0HKatamari current size: %d", currentSize);
		printf("\x1b[11;0HNumber of objects picked up: %d", objectsCounter);
		
	}

	// Delete graphics
	C2D_SpriteSheetFree(spriteSheet);
	

	// Deinit libs
	C2D_Fini();
	C3D_Fini();
	gfxExit();
	romfsExit();
	return 0;
}
