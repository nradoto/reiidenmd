#include "genesis.h"

#include "resources.h"
#include "sound.h"

fix32 movx;
fix32 movy;
s16 xpos = 0;
s16 ypos = 18;
s16 yorder;
s16 xorder;
uint8_t cursor = 0;
uint8_t options = 0;

void mainmenu()
{
		if (options==0)
		{
		//VDP_drawText("Highly responsive to prayers", 5, 6);
			VDP_clearTextArea(15, 18, 10, 7);
			VDP_clearTextArea(15, 18, 10, 7);
					VDP_drawText(">", 14, ypos);
					VDP_drawText("Start", 15, 18);
					VDP_drawText("Continue", 15, 19);
					VDP_drawText("Options",15,20);
					VDP_drawText("Exit",15,21);
					VDP_drawText("1995 ZUNSoft, 2017 Spaztron64", 5, 26);
					//if (ypos>21 && options == 0)
					//{
					//	ypos=ypos-1;
					//}

		}
}
void optionsmenu()
{
						options=1;
							VDP_clearTextArea(15, 18, 10, 7);
							VDP_clearTextArea(15, 18, 10, 7);
								VDP_drawText(">", 14, ypos);
								VDP_drawText("Rank", 15, 18);
								VDP_drawText("Music", 15, 19);
								VDP_drawText("Lives",15,20);
								VDP_drawText("Sound Test",15,21);
								VDP_drawText("Quit",15,22);
								//if (ypos<18)
							//	{
							//		ypos=ypos+1;
								//}
								//if (ypos>22 && options == 1)
								//{
								//	ypos=ypos-1;
								//}
			}

void myJoyHandler( u16 joy, u16 changed, u16 state)
{
	if (joy == JOY_1)
	{
		if (state & BUTTON_START)
		{
			VDP_drawText("player 1 pressed START button ", 0, 0);
			if (ypos==20)
			optionsmenu();
			else if (ypos==22 && options==1)
			options=0;
			mainmenu();
			if (ypos==21 && options==1)
			{
			SND_startPlay_XGM(angel);
			}
		}
		else if (changed & BUTTON_START)
		{
			VDP_clearTextBG(PLAN_A, 0, 0, 50);
		}
		if (state & BUTTON_DOWN)
		{
			VDP_drawText(">", 14, ypos+1);
			ypos=ypos+1;

		}
		else if (changed & BUTTON_DOWN)
		{VDP_clearText(12, ypos-1, 3);
		VDP_clearText(12, ypos+1, 3);}
		if (state & BUTTON_UP)
		{
			VDP_drawText(">", 14, ypos-1);
			ypos=ypos-1;
		}
			else if (changed & BUTTON_UP)
			{VDP_clearText(12, ypos+1, 3);
			VDP_clearText(12, ypos-1, 3);}
		}
}
//	if (joy != JOY_1)
//		{
//			VDP_drawText(">", 14, ypos);
//		}
void screen()
{//read input
		//move sprite
		//update score
		//draw current screen (logo, start screen, settings, game, gameover, credits...)
		VDP_drawBitmap(PLAN_B, &logo, 0, 0);

}

int main()
{
	VDP_setScreenWidth320();
	VDP_setScreenHeight240();
	JOY_init();
	JOY_setEventHandler( &myJoyHandler );
	screen();
	mainmenu();

	while(1)
	{
		if (ypos<18)
							{
								ypos=ypos+1;
							}
							if (ypos>22 && options == 1)
							{
								ypos=ypos-1;
							}
							if (ypos>21 && options == 0)
							{
								ypos=ypos-1;
							}


		//wait for screen refresh
		VDP_waitVSync();
	}
}

