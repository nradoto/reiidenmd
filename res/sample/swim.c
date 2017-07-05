/*******************************************/
/***
/*** Swimmer Bmp2Tile sample
/*** 20 August 2003 (C) Kaneda
/***
/*** "Swimmer" and all gfx (c)Tehkan LTD
/***
/*** Need GenKit 1.2+
/***
/*** http://www.consoledev.fr.st
/*******************************************/
#include "genesis.h"

/* callback of our data */
extern uint back_pal[];
extern uint back_omap_HSize;
extern uint back_omap_VSize;
extern uint back_omap[];
extern uint back_Number;
extern ulong back[];

extern uint tree_pal[];
extern uint tree_HSize;
extern uint tree_VSize;
extern ulong tree[];

extern uint swimmer_pal[];
extern uint swimmer0_HSize;
extern uint swimmer0_VSize;
extern ulong swimmer0[];
extern uint swimmer1_HSize;
extern uint swimmer1_VSize;
extern ulong swimmer1[];

/* made our life easier! */
#define TREE_NB		tree_HSize*tree_VSize
#define SWIM0_NB	swimmer0_HSize*swimmer0_VSize
#define SWIM1_NB	swimmer1_HSize*swimmer1_VSize

/* X range of our swimmer */
#define MIN_X	16
#define MAX_X	150

#define PAL0	0
#define PAL1	1
#define PAL2	2
#define PAL3	3

/***** MODIFY THE WIDTH ****/
/***** see INIT_GFX     ****/
uint  extWIDTH;
/* must be HERE! see sega.asm */
uchar ResetState;

void Init_GFX();

void main()
{
	uint i,j,k;
	ulong adr;
	uint spr_posX, spr_posY;
	uchar spr_frame;
    	register uint joy;   
    	
/*** Genny init stuff ******/
	Init_GFX();
	RAZ();
	
/*** Load our tiles ******/	
	
	/* uncompress the compressed tiles */
	adr = 32;
	unpack(back, GFX_WRITE_ADDR( adr ), 3597);
	adr = 32 * (back_Number+1);
	unpack(tree, GFX_WRITE_ADDR( adr ), 578);	
	
	/* load uncompressed tiles (binary or not) */
	dma_vram_copy(swimmer0,32*(TREE_NB+back_Number+1),32*SWIM0_NB);
	dma_vram_copy(swimmer1,32*(TREE_NB+back_Number+SWIM0_NB+1),32*SWIM1_NB);
	
	wait_sync();
	
/*** Draw our tiles ******/

	/* according a map */
	for(j=0; j< back_omap_VSize; j++)
	{
		for(i=0;i< back_omap_HSize;i++)
		{
			k = back_omap[ (i + (j*back_omap_HSize))];
			show_tiles(k+1, k+1, PAL0, i, j, BPLAN, 0, 0, 0);
		}
	}
	
	/* a full tile */
	for(i=0;i<tree_VSize;i++)
	{
		k = back_Number+1 + (i*tree_HSize);
		show_tiles(k, k+tree_HSize-1, PAL1, 6, 14+i, APLAN, 1, 0, 0);
	}
	
/*** Init colors ****/
	set_colors(0,back_pal);
	set_colors(1,tree_pal);
	set_colors(2,swimmer_pal);
	wait_sync();
	
/*********/		
	init_joypad();
		
	spr_posX = 80;
	spr_posY = 150;
	spr_frame = 0;
	/* 0x700 = 4x2 sprite */
	/* 0x4000 = priority 0 (under APLAN) and PAL2 */
	def_sprite(1,spr_posX,spr_posY,0x700,0x4000 | (TREE_NB+back_Number+1) );
	show_sprite(1,1);
	wait_sync();
		
	while(1)
	{		
    		joy= read_joypad1()& 0xff;
    		
    		/* see sega.asm */
    		if (joy == BUTTON_A+BUTTON_B+BUTTON_C+BUTTON_S)
	       		ResetState=1;

       		/* update the mov, change the gfx every 8 */
       		spr_frame++;
       		spr_frame%=8;
       		
		if (joy & JOY_UP)
		{
	       		if (spr_posY > 2)	spr_posY -= 2;
	       	}
	       	else if (joy & JOY_DOWN)
	       	{
	       		if (spr_posY < 194)	spr_posY += 2;
	       	}
	       	else
		{	     
	       		spr_frame = 0;
			if (spr_posY < 194)	spr_posY += 1; 
		}

		if (joy & JOY_LEFT)
		{
	       		if (spr_posX > MIN_X)	spr_posX -=2;
	       	}
	       	else if (joy & JOY_RIGHT)
	       	{
			if (spr_posX < MAX_X)	spr_posX +=2;
		}

		/* update sprite */
		def_sprite(1,spr_posX,spr_posY,0x700,0x4000 | (TREE_NB+back_Number+1+ (spr_frame/4)*SWIM0_NB) );
		show_sprite(1,1);
		wait_sync();
	}	
}


/*****************  Initialize GFX  ****************/
/* Read the comment for more info on each register */
/***************************************************/
void Init_GFX()
{
    register uint *pw;

    pw = (uint *) GFXCNTL;

    *pw = 0x8016;   /* reg. 0 - Enable HBL */
    *pw = 0x8174;   /* reg. 1 - Enable display, VBL, DMA + VCell size (28) */
    *pw = 0x8230;   /* reg. 2 - Plane A =$30*$400=$C000 */
    *pw = 0x832C;   /* reg. 3 - Window  =$2C*$400=$B000 */
    *pw = 0x8407;   /* reg. 4 - Plane B =$7*$2000=$E000 */
    *pw = 0x855F;   /* reg. 5 - sprite table begins at $BE00=$5F*$200 */
    *pw = 0x8600;   /* reg. 6 - not used */
    *pw = 0x8700;   /* reg. 7 - Background Color number*/
    *pw = 0x8800;   /* reg. 8 - not used */
    *pw = 0x8900;   /* reg. 9 - not used */
    *pw = 0x8a01;   /* reg 10 - HInterrupt timing */
    *pw = 0x8b00;   /* reg 11 - $0000abcd a=extr.int b=vscr cd=hscr */
    *pw = 0x8c00;   /* reg 12 - hcell mode + shadow/highight + interlaced mode */
    *pw = 0x8d2E;   /* reg 13 - HScoll Table = $B800 */
    *pw = 0x8e00;   /* reg 14 - not used */
    *pw = 0x8f02;   /* reg 15 - auto increment data */
    *pw = 0x9000;   /* reg 16 - scrl screen v&h size */
    
    extWIDTH = 32;
    
    *pw = 0x9100;   /* reg 17 - window hpos */
    *pw = 0x92ff;   /* reg 18 - window vpos */
};