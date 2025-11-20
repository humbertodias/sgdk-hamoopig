#include <genesis.h>
#include "init.h"
#include "globals.h"
#include "gfx.h"
#include "sprite.h"

void FUNCAO_INICIALIZACAO()
{
	gPodeMover=0;
	doubleHitStep=0;
	
	//BG_B
	gInd_tileset=1; //Antes de carregar o Background, definir o ponto de inicio de carregamento na VRAM
	
	//Load the tileset 'BGB1'
	if(gBG_Choice==1){ 
		gBG_Width = 512; // Largura do Cenario em pixels!
		gScrollValue=-(gBG_Width-320)/2;
		VDP_loadTileSet(gfx_bgb1.tileset,gInd_tileset,DMA); 
		VDP_setTileMapEx(BG_B,gfx_bgb1.tilemap,TILE_ATTR_FULL(PAL0,0,FALSE,FALSE,gInd_tileset),0,0,0,0,gBG_Width/8,28,DMA_QUEUE);
		PAL_setPalette(PAL0, gfx_bgb1.palette->data, CPU);
		gInd_tileset += gfx_bgb1.tileset->numTile;
	} 
	
	//Load the tileset 'BGB2'
	if(gBG_Choice==2){ 
		gBG_Width = 512; // Largura do Cenario em pixels!
		gScrollValue=-(gBG_Width-320)/2;
		VDP_loadTileSet(gfx_bgb2.tileset,gInd_tileset,DMA); 
		VDP_setTileMapEx(BG_B,gfx_bgb2.tilemap,TILE_ATTR_FULL(PAL0,0,FALSE,FALSE,gInd_tileset),0,0,0,0,gBG_Width/8,28,DMA_QUEUE);
		PAL_setPalette(PAL0, gfx_bgb2.palette->data, CPU);
		gInd_tileset += gfx_bgb2.tileset->numTile;
	} 
	
	//load palette HUD in PAL1, GFX load AFTER round intro...
	//PALETA DA HUD!!!
	PAL_setPalette(PAL1, spr_point.palette->data, CPU); 
	
	u8 divisoes = 22;
	gAlturaPiso = (224/divisoes)*divisoes-1; gAlturaPiso-=4;
	
	for(i=1; i<=2; i++) {
		P[i].key_JOY_countdown[2]=0;
		P[i].key_JOY_countdown[4]=0;
		P[i].key_JOY_countdown[6]=0;
		P[i].key_JOY_countdown[8]=0;
	}
	
	//P1
	P[1].energia = 96;
	P[1].energiaBase = 96;
	P[1].energiaSP = 0;
	P[1].rageTimerCountdown=RAGETIMER;
	P[1].wins = 0;
	P[1].x = (gBG_Width/2)-80; //P[1].x = (320/4);
	P[1].y = gAlturaPiso;
	P[1].hitPause = 0;
	P[1].direcao = 1;
	P[1].state = 610; //610, Intro State!
	P[1].puloTimer = 0;
	P[1].dataMBox[0] = -BODYSPACE;
	P[1].dataMBox[1] = -60;
	P[1].dataMBox[2] = +BODYSPACE;
	P[1].dataMBox[3] = - 1;
	P[1].paleta = PAL2;
	P[1].cicloInteracoesGravidade = CIGD; //CIGD eh uma definicao global! ver inicio do codigo
	P[1].cicloInteracoesGravidadeCont = 0;
	P[1].fball.active = 0;
	P[1].bufferSpecial = 0;
	P[1].hitCounter = 0;
	P[1].stateMoveType = 0;
	
	//P2
	P[2].energia = 96;
	P[2].energiaBase = 96;
	P[2].energiaSP = 0;
	P[2].rageTimerCountdown=RAGETIMER;
	P[2].wins = 0;
	P[2].x = (gBG_Width/2)+80; //P[2].x = (320/4)*3;
	P[2].y = gAlturaPiso;
	P[2].hitPause = 0;
	P[2].direcao = -1;
	P[2].state = 610; //610, Intro State!
	P[2].puloTimer = 0;
	P[2].dataMBox[0] = -BODYSPACE;
	P[2].dataMBox[1] = -60;
	P[2].dataMBox[2] = +BODYSPACE;
	P[2].dataMBox[3] = - 1;
	P[2].paleta = PAL3;
	P[2].cicloInteracoesGravidade = CIGD; //CIGD eh uma definicao global! ver inicio do codigo
	P[2].cicloInteracoesGravidadeCont = 0;
	P[2].fball.active = 0;
	P[2].bufferSpecial = 0;
	P[2].hitCounter = 0;
	P[2].stateMoveType = 0;


	//Para verificar a vantagem ou desvantagem em relacao aos frames
	frameAdvCounterP1 = 0;
	lastFrameAdvCounterP1 = 0;
	frameAdvCounterP2 = 0;
	lastFrameAdvCounterP2 = 0;

	/*
	P[1].sombra = SPR_addSpriteExSafe(&spr_sombra, P[1].x-P[1].axisX, P[1].y-2, TILE_ATTR(PAL1, FALSE, FALSE, FALSE), SPR_FLAG_AUTO_VISIBILITY | SPR_FLAG_AUTO_VRAM_ALLOC | SPR_FLAG_AUTO_TILE_UPLOAD);
	SPR_setVRAMTileIndex(P[1].sombra, 1492); //define uma posicao especifica para o GFX na VRAM
	if(gSombraStyle==2)
	{
		P[2].sombra = SPR_addSpriteExSafe(&spr_sombra, P[2].x-P[1].axisX, P[2].y-2, TILE_ATTR(PAL1, FALSE, FALSE, FALSE), SPR_FLAG_AUTO_VISIBILITY | SPR_FLAG_AUTO_VRAM_ALLOC | SPR_FLAG_AUTO_TILE_UPLOAD);
	}
	*/
	
	//reset Graphic Elements
	if (GE[ 1].sprite){ SPR_releaseSprite(GE[ 1].sprite); GE[ 1].sprite = NULL; }
	if (GE[ 2].sprite){ SPR_releaseSprite(GE[ 2].sprite); GE[ 2].sprite = NULL; }
	if (GE[ 3].sprite){ SPR_releaseSprite(GE[ 3].sprite); GE[ 3].sprite = NULL; }
	if (GE[ 4].sprite){ SPR_releaseSprite(GE[ 4].sprite); GE[ 4].sprite = NULL; }
	if (GE[ 5].sprite){ SPR_releaseSprite(GE[ 5].sprite); GE[ 5].sprite = NULL; }
	if (GE[ 6].sprite){ SPR_releaseSprite(GE[ 6].sprite); GE[ 6].sprite = NULL; }
	if (GE[ 7].sprite){ SPR_releaseSprite(GE[ 7].sprite); GE[ 7].sprite = NULL; }
	if (GE[ 8].sprite){ SPR_releaseSprite(GE[ 8].sprite); GE[ 8].sprite = NULL; }
	if (GE[ 9].sprite){ SPR_releaseSprite(GE[ 9].sprite); GE[ 9].sprite = NULL; }
	if (GE[10].sprite){ SPR_releaseSprite(GE[10].sprite); GE[10].sprite = NULL; }
	if (GE[11].sprite){ SPR_releaseSprite(GE[11].sprite); GE[11].sprite = NULL; }
	if (GE[12].sprite){ SPR_releaseSprite(GE[12].sprite); GE[12].sprite = NULL; }
	if (GE[13].sprite){ SPR_releaseSprite(GE[13].sprite); GE[13].sprite = NULL; }
	if (GE[14].sprite){ SPR_releaseSprite(GE[14].sprite); GE[14].sprite = NULL; }
	if (GE[15].sprite){ SPR_releaseSprite(GE[15].sprite); GE[15].sprite = NULL; }
	if (GE[16].sprite){ SPR_releaseSprite(GE[16].sprite); GE[16].sprite = NULL; }
	if (GE[17].sprite){ SPR_releaseSprite(GE[17].sprite); GE[17].sprite = NULL; }
	if (GE[18].sprite){ SPR_releaseSprite(GE[18].sprite); GE[18].sprite = NULL; }
	if (GE[19].sprite){ SPR_releaseSprite(GE[19].sprite); GE[19].sprite = NULL; }
	if (GE[20].sprite){ SPR_releaseSprite(GE[20].sprite); GE[20].sprite = NULL; }
	
	gClockTimer=60; //Relogio, timer de 1 seg
	gClockLTimer=9; //Digito esquerdo do Relogio
	gClockRTimer=9; //Digito direito do Relogio
	gRound=1;       //Round Number
	
	
	if(RELEASE==0)
	{
		Rect1BB1_Q1 = SPR_addSprite(&spr_rect_bb, -8, -8, TILE_ATTR(PAL1, FALSE, FALSE, FALSE));
		SPR_setVRAMTileIndex(Rect1BB1_Q1, 1453); //define uma posicao especifica para o GFX na VRAM
		Rect1BB1_Q2 = SPR_addSprite(&spr_rect_bb, -8, -8, TILE_ATTR(PAL1, FALSE, FALSE, FALSE));
		SPR_setVRAMTileIndex(Rect1BB1_Q2, 1453); //define uma posicao especifica para o GFX na VRAM
		Rect1BB1_Q3 = SPR_addSprite(&spr_rect_bb, -8, -8, TILE_ATTR(PAL1, FALSE, FALSE, FALSE));
		SPR_setVRAMTileIndex(Rect1BB1_Q1, 1453); //define uma posicao especifica para o GFX na VRAM
		Rect1BB1_Q4 = SPR_addSprite(&spr_rect_bb, -8, -8, TILE_ATTR(PAL1, FALSE, FALSE, FALSE));
		SPR_setVRAMTileIndex(Rect1BB1_Q2, 1453); //define uma posicao especifica para o GFX na VRAM
		Rect1HB1_Q1 = SPR_addSprite(&spr_rect_hb, -8, -8, TILE_ATTR(PAL1, FALSE, FALSE, FALSE));
		SPR_setVRAMTileIndex(Rect1HB1_Q1, 1454); //define uma posicao especifica para o GFX na VRAM
		Rect1HB1_Q2 = SPR_addSprite(&spr_rect_hb, -8, -8, TILE_ATTR(PAL1, FALSE, FALSE, FALSE));
		SPR_setVRAMTileIndex(Rect1HB1_Q2, 1454); //define uma posicao especifica para o GFX na VRAM
		Rect1HB1_Q3 = SPR_addSprite(&spr_rect_hb, -8, -8, TILE_ATTR(PAL1, FALSE, FALSE, FALSE));
		SPR_setVRAMTileIndex(Rect1HB1_Q1, 1454); //define uma posicao especifica para o GFX na VRAM
		Rect1HB1_Q4 = SPR_addSprite(&spr_rect_hb, -8, -8, TILE_ATTR(PAL1, FALSE, FALSE, FALSE));
		SPR_setVRAMTileIndex(Rect1HB1_Q2, 1454); //define uma posicao especifica para o GFX na VRAM
		
		Rect2BB1_Q1 = SPR_addSprite(&spr_rect_bb, -8, -8, TILE_ATTR(PAL1, FALSE, FALSE, FALSE));
		SPR_setVRAMTileIndex(Rect2BB1_Q1, 1453); //define uma posicao especifica para o GFX na VRAM
		Rect2BB1_Q2 = SPR_addSprite(&spr_rect_bb, -8, -8, TILE_ATTR(PAL1, FALSE, FALSE, FALSE));
		SPR_setVRAMTileIndex(Rect2BB1_Q2, 1453); //define uma posicao especifica para o GFX na VRAM
		Rect2BB1_Q3 = SPR_addSprite(&spr_rect_bb, -8, -8, TILE_ATTR(PAL1, FALSE, FALSE, FALSE));
		SPR_setVRAMTileIndex(Rect2BB1_Q1, 1453); //define uma posicao especifica para o GFX na VRAM
		Rect2BB1_Q4 = SPR_addSprite(&spr_rect_bb, -8, -8, TILE_ATTR(PAL1, FALSE, FALSE, FALSE));
		SPR_setVRAMTileIndex(Rect2BB1_Q2, 1453); //define uma posicao especifica para o GFX na VRAM
		Rect2HB1_Q1 = SPR_addSprite(&spr_rect_hb, -8, -8, TILE_ATTR(PAL1, FALSE, FALSE, FALSE));
		SPR_setVRAMTileIndex(Rect2HB1_Q1, 1454); //define uma posicao especifica para o GFX na VRAM
		Rect2HB1_Q2 = SPR_addSprite(&spr_rect_hb, -8, -8, TILE_ATTR(PAL1, FALSE, FALSE, FALSE));
		SPR_setVRAMTileIndex(Rect2HB1_Q2, 1454); //define uma posicao especifica para o GFX na VRAM
		Rect2HB1_Q3 = SPR_addSprite(&spr_rect_hb, -8, -8, TILE_ATTR(PAL1, FALSE, FALSE, FALSE));
		SPR_setVRAMTileIndex(Rect2HB1_Q1, 1454); //define uma posicao especifica para o GFX na VRAM
		Rect2HB1_Q4 = SPR_addSprite(&spr_rect_hb, -8, -8, TILE_ATTR(PAL1, FALSE, FALSE, FALSE));
		SPR_setVRAMTileIndex(Rect2HB1_Q2, 1454); //define uma posicao especifica para o GFX na VRAM
		
		SPR_setHFlip(Rect1BB1_Q2, TRUE);
		SPR_setVFlip(Rect1BB1_Q3, TRUE);
		SPR_setHFlip(Rect1BB1_Q4, TRUE); SPR_setVFlip(Rect1BB1_Q4, TRUE);
		SPR_setHFlip(Rect1HB1_Q2, TRUE);
		SPR_setVFlip(Rect1HB1_Q3, TRUE);
		SPR_setHFlip(Rect1HB1_Q4, TRUE); SPR_setVFlip(Rect1HB1_Q4, TRUE);
		
		SPR_setHFlip(Rect2BB1_Q2, TRUE);
		SPR_setVFlip(Rect2BB1_Q3, TRUE);
		SPR_setHFlip(Rect2BB1_Q4, TRUE); SPR_setVFlip(Rect2BB1_Q4, TRUE);
		SPR_setHFlip(Rect2HB1_Q2, TRUE);
		SPR_setVFlip(Rect2HB1_Q3, TRUE);
		SPR_setHFlip(Rect2HB1_Q4, TRUE); SPR_setVFlip(Rect2HB1_Q4, TRUE);
		
		SPR_setDepth(Rect1BB1_Q1, 1);
		SPR_setDepth(Rect1BB1_Q2, 1);
		SPR_setDepth(Rect1BB1_Q3, 1);
		SPR_setDepth(Rect1BB1_Q4, 1);
		SPR_setDepth(Rect1HB1_Q1, 1);
		SPR_setDepth(Rect1HB1_Q2, 1);
		SPR_setDepth(Rect1HB1_Q3, 1);
		SPR_setDepth(Rect1HB1_Q4, 1);
		
		SPR_setDepth(Rect2BB1_Q1, 1);
		SPR_setDepth(Rect2BB1_Q2, 1);
		SPR_setDepth(Rect2BB1_Q3, 1);
		SPR_setDepth(Rect2BB1_Q4, 1);
		SPR_setDepth(Rect2HB1_Q1, 1);
		SPR_setDepth(Rect2HB1_Q2, 1);
		SPR_setDepth(Rect2HB1_Q3, 1);
		SPR_setDepth(Rect2HB1_Q4, 1);
	}
	
	//Intro State, Player Start
	//P[1].sprite = SPR_addSpriteExSafe(&spr_point, P[1].x-P[1].axisX, P[1].y-P[1].axisY, TILE_ATTR(PAL2, FALSE, FALSE, FALSE), SPR_FLAG_AUTO_VISIBILITY | SPR_FLAG_AUTO_VRAM_ALLOC | SPR_FLAG_AUTO_TILE_UPLOAD);
	//P[2].sprite = SPR_addSpriteExSafe(&spr_point, P[2].x-P[2].axisX, P[2].y-P[2].axisY, TILE_ATTR(PAL3, FALSE, FALSE, FALSE), SPR_FLAG_AUTO_VISIBILITY | SPR_FLAG_AUTO_VRAM_ALLOC | SPR_FLAG_AUTO_TILE_UPLOAD);
	PLAYER_STATE(1,100);
	PLAYER_STATE(2,100);
	
	SPR_setHFlip(P[2].sprite, TRUE);
	
	//Define a paleta dos players...
	P[1].palID=cursorP1ColorChoice;
	P[2].palID=cursorP2ColorChoice; 
	
	if( P[1].id==P[2].id && P[1].palID==P[2].palID)
	{
		//se ambos os players forem iguais e com a mesma paleta...
		P[1].palID=1; //Por padrao, P1 fica com a paleta 1
		P[2].palID=2; //Por padrao, P2 fica com a paleta 2 'cor alternativa'
	}
	
	//--P1--
	
	if(P[1].id== 1 && P[1].palID==1){ PAL_setPalette(PAL2, spr_ryo_pal1.palette->data, CPU); } //ryo
	if(P[1].id== 1 && P[1].palID==2){ PAL_setPalette(PAL2, spr_ryo_pal2.palette->data, CPU); } //ryo
	
	//--P2--
	
	if(P[2].id== 1 && P[2].palID==1){ PAL_setPalette(PAL3, spr_ryo_pal1.palette->data, CPU); } //ryo
	if(P[2].id== 1 && P[2].palID==2){ PAL_setPalette(PAL3, spr_ryo_pal2.palette->data, CPU); } //ryo
	
	//AXIS
	if(RELEASE==0)
	{
		if (GE[1].sprite){ SPR_releaseSprite(GE[1].sprite); GE[1].sprite = NULL; }
		if (GE[2].sprite){ SPR_releaseSprite(GE[2].sprite); GE[2].sprite = NULL; }
		GE[1].sprite = SPR_addSprite(&spr_point, P[1].x-4, P[1].y-5, TILE_ATTR(PAL1, FALSE, FALSE, FALSE));
		GE[2].sprite = SPR_addSprite(&spr_point, P[2].x-4, P[2].y-5, TILE_ATTR(PAL1, FALSE, FALSE, FALSE));
		SPR_setVRAMTileIndex(GE[1].sprite, 1455); //define uma posicao especifica para o GFX na VRAM
		SPR_setVRAMTileIndex(GE[2].sprite, 1455); //define uma posicao especifica para o GFX na VRAM
		SPR_setVisibility(GE[1].sprite, HIDDEN);
		SPR_setVisibility(GE[2].sprite, HIDDEN);
		
		//DEPTH
		SPR_setDepth(GE[1].sprite, 1 );
		SPR_setDepth(GE[2].sprite, 2 );
	}
	
	//depth 3 e 4 reservados
	if (P[1].sprite){ SPR_setDepth(P[1].sprite,  5 ); } 
	if (P[2].sprite){ SPR_setDepth(P[2].sprite,  6 ); } 
	//depth 7 e 8 reservados
	//if(P[1].sombra){ SPR_setDepth(P[1].sombra, 98 ); }
	//if(gSombraStyle==2){ SPR_setDepth(P[2].sombra, 99 ); }
}

void FUNCAO_ROUND_INIT()
{
	gPodeMover=1;
}

void FUNCAO_ROUND_RESTART()
{
	
}

void CLEAR_VDP()
{
	SYS_disableInts();
	 SPR_reset();
	 //VDP_resetSprites();
	 //VDP_releaseAllSprites();
	 //SPR_defragVRAM();
	 VDP_clearPlane(BG_A, TRUE);
	 VDP_clearPlane(BG_B, TRUE);	
	 VDP_setTextPlane(BG_A);  
	 VDP_setHorizontalScroll(BG_B, 0); 
	 VDP_setVerticalScroll(BG_B, 0); 
	 VDP_setHorizontalScroll(BG_A, 0); 
	 VDP_setVerticalScroll(BG_A, 0);
	 VDP_setBackgroundColor(0);
	 VDP_resetScreen();
	 //PAL_setPaletteColors(0, (u16*) palette_black, CPU);
	SYS_enableInts();
	gInd_tileset=0;
}

//EOF - END OF FILE; by GAMEDEVBOSS 2015-2022