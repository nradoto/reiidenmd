#include "genesis.h"

#include "resources.h"

static void joyEvent(u16 joy, u16 changed, u16 state);

fix32 movx;
fix32 movy;
s16 xpos = 0;
s16 ypos = 18;
s16 yorder;
s16 xorder;
uint8_t cursor = 0;

void myJoyHandler( u16 joy, u16 changed, u16 state)
{
	if (joy == JOY_1)
	{
		if (state & BUTTON_START)
		{
			VDP_drawText("player 1 pressed START button ", 0, 0);
		}
		else if (changed & BUTTON_START)
		{
			VDP_drawText("player 1 released START button", 0, 0);
		}
		if (state & BUTTON_DOWN)
		{
			VDP_drawText(">", 14, ypos+1);
			ypos=ypos+1;
		}
		if (state & BUTTON_UP)
		{
			VDP_drawText(">", 14, ypos-1);
			ypos=ypos-1;
		}
	}
//	if (joy != JOY_1)
//		{
//			VDP_drawText(">", 14, ypos);
//		}
}

void poslimit()
{
	if (ypos < 18)
	{
		ypos=18;
	}
	if (ypos > 21)
	{
		ypos=21;
	}
}

static void handleInput()
		{
		    u16 value = JOY_readJoypad(JOY_1);

		    if (value & BUTTON_UP) yorder = -1;
		    else if (value & BUTTON_DOWN) yorder = +1;
		    else yorder = 0;

		    if (value & BUTTON_LEFT) xorder = -1;
		    else if (value & BUTTON_RIGHT) xorder = +1;
		    else xorder = 0;
		}
int main()
{
	JOY_init();
	JOY_setEventHandler( &myJoyHandler );

	while(1)
	{
		//read input
		//move sprite
		//update score
		//draw current screen (logo, start screen, settings, game, gameover, credits...)
		VDP_drawBitmap(PLAN_A, &logo, 0, 0);
			//VDP_drawText("Highly responsive to prayers", 5, 6);
			VDP_drawText(">", 14, ypos);
			VDP_drawText("Start", 15, 18);
			VDP_drawText("Continue", 15, 19);
			VDP_drawText("Options",15,20);
			VDP_drawText("Exit",15,21);
			VDP_drawText("1995 ZUNSoft, 2017 Spaztron64", 5, 26);




		//wait for screen refresh
		VDP_waitVSync();
	}
	if (cursor == 0) VDP_drawText(">",14,18);
}

