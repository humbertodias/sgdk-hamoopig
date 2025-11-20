//////////////////////////////////////////////////////////////////////////////
// HAMOOPI(G) by GameDevBoss (Daniel Moura) 2015-2022                       //
// www.youtube.com/c/GameDevBoss                                            //
// HAMOOPIG É GRATUITO E SEMPRE SERÁ - HAMOOPIG IS FREE AND ALWAYS WILL BE  //
// O CONHECIMENTO DEVE SER COMPARTILHADO - KNOWLEDGE MUST BE SHARED         //
//////////////////////////////////////////////////////////////////////////////
// SPECIAL THANKS                                                           //
// SIR MACHO                                                                //
// TITAN DOOM                                                               //
//////////////////////////////////////////////////////////////////////////////

#include <genesis.h>
#include "sprite.h"
#include "gfx.h"
#include "sound.h"
#include "game_types.h"
#include "globals.h"
#include "player.h"
#include "input.h"
#include "fsm.h"
#include "physics.h"
#include "graphics.h"
#include "hud.h"
#include "init.h"
#include "collision.h"
#include "debug.h"



int main() /************** MAIN **************/
{
    //Inicializacao da VDP (Video Display Processor)
	SYS_disableInts();
	 VDP_init();                    //Inicializa a VDP (Video Display Processor)
	 VDP_setScreenWidth320();       //Resolucao padrao de 320x224 (Largura)
	 VDP_setScreenHeight224();      //Resolucao padrao de 320x224 (Altura)
	 VDP_setTextPlane(BG_A);        //Textos serao desenhados no BG_A
	 VDP_setTextPalette(PAL1);      //Textos serao desenhados com a ultima cor da PAL0
	 SPR_init();       				//SPR_initEx(u16 vramSize)
	 VDP_setBackgroundColor(0);     //Range 0-63 //4 Paletas de 16 cores = 64 cores
	SYS_enableInts();
	
	//XGM_setPCM(SFX_ARG, arg_sfx, sizeof(arg_sfx)); 
	//XGM_setPCM(SFX_FATAL, fatalfury_sfx, sizeof(fatalfury_sfx)); 

	//////////////////////////////////////////////////////I.A. (config)
	fase = 4; //manter o valor igual a 1
	faseMAX = 8; //configurado para 8 fases no maximo (escolher valor de 1 a 8)
	
	IAP2 = FALSE;

	//DIFICULDADE DA IA

	//SE O TEMPO DE ATAQUE ESTIVER ENTRE tempoMinIAataque E tempoMaxIAataque SIGNIFICA QUE O PLAYER 2 ATACA
	tempoMinIAataque[1] =  60; //escolher valor de 2 a 255
	tempoMinIAataque[2] =  60;
	tempoMinIAataque[3] =  50;
	tempoMinIAataque[4] =  50;
	tempoMinIAataque[5] =  40;
	tempoMinIAataque[6] =  30;
	tempoMinIAataque[7] =  20;
	tempoMinIAataque[8] =  10;

	tempoMaxIAataque[1] = 100; //escolher valor de 2 a 255 (valor deve ser maior que o respectivo no tempoMinIAataque)
	tempoMaxIAataque[2] = 100;
	tempoMaxIAataque[3] = 100;
	tempoMaxIAataque[4] = 100;
	tempoMaxIAataque[5] =  55;
	tempoMaxIAataque[6] =  60;
 	tempoMaxIAataque[7] =  50;
	tempoMaxIAataque[8] =  80;

	//QUANTO MENOR O VALOR, MAIS A IA DO PLAYER 2 DEFENDE
	defesaIA[1] =  50; //escolher valor de 10 a 255, valor menor ou igual a 10 = sempre defende
	defesaIA[2] =  50;
	defesaIA[3] =  10;
	defesaIA[4] =  10;
	defesaIA[5] =  90;
	defesaIA[6] =  60;
	defesaIA[7] =  30;
	defesaIA[8] =  15;

	P2fase[1] = 2; //escolha do Player 2 em cada fase: 1="haohmaru", 2="gillius"
	P2fase[2] = 1;
	P2fase[3] = 2;
	P2fase[4] = 1;
	P2fase[5] = 2;
	P2fase[6] = 1;
	P2fase[7] = 2;
	P2fase[8] = 1;
	//////////////////////////////////////////////////////I.A. (config)
	
    while(TRUE) /// LOOP PRINCIPAL ///
    {
        gFrames++; 
		if(gPing2  == 1){ gPing2 = -1; } gPing2++;  //var 'gPing2'  (50%) variacao: 0 ; 1
		if(gPing4  == 3){ gPing4 = -1; } gPing4++;  //var 'gPing4'  (25%) variacao: 0 ; 1 ; 2 ; 3
		if(gPing10 == 9){ gPing10= -1; } gPing10++; //var 'gPing10' (10%) variacao: 0 ; 1 ; 2 ; 3 ; 4 ; 5 ; 6 ; 7 ; 8 ; 9
		
		if(gRoom==1) //TELA HAMOOPIG --------------------------------------------------------------
		{
			FUNCAO_INPUT_SYSTEM(); //Verifica os joysticks 
			
			//inicializacao
			if(gFrames==1)
			{
				//XGM_startPlay(music_stage8);
				//XGM_isPlaying(); //FIX

				//PAL_setPaletteColors(0, (u16 *)palette_black, CPU); 
				//BG_B
				VDP_loadTileSet(room_0_bgb.tileset, 1, DMA); //Load the tileset
				VDP_setTileMapEx(BG_B,room_0_bgb.tilemap, TILE_ATTR_FULL(PAL2, 0, FALSE, FALSE, 1), 0, 0, 0, 0, 40, 28, DMA);
				//BG_A
				VDP_loadTileSet(room_0_bga.tileset, 501, DMA); //Load the tileset
				VDP_setTileMapEx(BG_A,room_0_bga.tilemap, TILE_ATTR_FULL(PAL3, 0, FALSE, FALSE, 501), 0, 0, 0, 0, 40, 28, DMA);
				
				//FADE IN
				memcpy(&palette[32], room_0_bgb.palette->data, 18 * 2);  
				memcpy(&palette[48], room_0_bga.palette->data, 18 * 2);  
				PAL_fadeIn(0, (4 * 16) - 1, palette, 20, FALSE);   
			}
			
			if(gFrames==60*2)
			{
				PAL_fadeOutAll(20, FALSE);
				waitMs(200);
			}
			
			//gFrames=60*5; 
			if( (gFrames>=60*2) || (P[1].key_JOY_START_status==1 && gFrames>10) || (P[2].key_JOY_START_status==1 && gFrames>10) ){
				CLEAR_VDP();
				gRoom=9;
				gDescompressionExit=10;
				//if(P[1].key_JOY_START_status==1 || P[1].key_JOY_START_status==2){gRoom=2; XGM_setPCM(P1_SFX, snd_confirm, sizeof(snd_confirm)); XGM_startPlayPCM(P1_SFX, 1, SOUND_PCM_CH3); }
				gFrames=1;
				P[1].id=1; PAL_setPalette(PAL2, spr_ryo_pal1.palette->data, CPU); 
				P[2].id=1; PAL_setPalette(PAL3, spr_ryo_pal1.palette->data, CPU);
			};
		}
		
		if(gRoom==9) //DESCOMPRESSION -------------------------------------------------------------
		{
			GE[1].sprite = SPR_addSpriteExSafe(&spr_point,  0, 225, TILE_ATTR(PAL3, FALSE, FALSE, FALSE), SPR_FLAG_AUTO_VISIBILITY | SPR_FLAG_AUTO_VRAM_ALLOC | SPR_FLAG_AUTO_TILE_UPLOAD);
			GE[2].sprite = SPR_addSpriteExSafe(&spr_point,  0, 225, TILE_ATTR(PAL3, FALSE, FALSE, FALSE), SPR_FLAG_AUTO_VISIBILITY | SPR_FLAG_AUTO_VRAM_ALLOC | SPR_FLAG_AUTO_TILE_UPLOAD);
			GE[3].sprite = SPR_addSpriteExSafe(&spr_point,  0, 225, TILE_ATTR(PAL3, FALSE, FALSE, FALSE), SPR_FLAG_AUTO_VISIBILITY | SPR_FLAG_AUTO_VRAM_ALLOC | SPR_FLAG_AUTO_TILE_UPLOAD);
			
			if(gFrames==20)
			{
				if (GE[1].sprite){ SPR_releaseSprite(GE[1].sprite); GE[1].sprite = NULL; }
				if (GE[2].sprite){ SPR_releaseSprite(GE[2].sprite); GE[2].sprite = NULL; }
				if (GE[3].sprite){ SPR_releaseSprite(GE[3].sprite); GE[3].sprite = NULL; }
				gRoom=gDescompressionExit;
				gFrames=1; 
				CLEAR_VDP();
			}
			
		}
		
		if(gRoom==10) //IN GAME -------------------------------------------------------------------
		{
			//buffer de especiais para P1
			if(P[1].hitPause==0 && P[1].bufferSpecial!=0){
				PLAYER_STATE(1, P[1].bufferSpecial);
				P[1].bufferSpecial=0;
			}

			//buffer de especiais para P2
			if(P[2].hitPause==0 && P[2].bufferSpecial!=0){
				PLAYER_STATE(2, P[2].bufferSpecial);
				P[2].bufferSpecial=0;
			}
			
			
			/*//HWA bebado
			if( P[1].id==8 && P[1].bebado>0){ P[1].bebado--; }
			if( P[1].bebado>1 ){
				if(P[1].palID==1){ PAL_setPalette(PAL2, spr_hwa_pal1b.palette->data, CPU); } //hwa
				if(P[1].palID==2){ PAL_setPalette(PAL2, spr_hwa_pal2b.palette->data, CPU); } //hwa
			}
			if( P[1].bebado==1 ){
				if(P[1].palID==1){ PAL_setPalette(PAL2, spr_hwa_pal1.palette->data, CPU); } //hwa
				if(P[1].palID==2){ PAL_setPalette(PAL2, spr_hwa_pal2.palette->data, CPU); } //hwa
			}
			if( P[2].id==8 && P[2].bebado>0){ P[2].bebado--;  }
			if( P[2].bebado>1 ){
				if(P[2].palID==1){ PAL_setPalette(PAL3, spr_hwa_pal1b.palette->data, CPU); } //hwa
				if(P[2].palID==2){ PAL_setPalette(PAL3, spr_hwa_pal2b.palette->data, CPU); } //hwa
			}
			if( P[2].bebado==1 ){
				if(P[2].palID==1){ PAL_setPalette(PAL3, spr_hwa_pal1.palette->data, CPU); } //hwa
				if(P[2].palID==2){ PAL_setPalette(PAL3, spr_hwa_pal2.palette->data, CPU); } //hwa
			}
			*/
			
			//codigo de "SLOW MOTION KO"
			if((P[1].energiaBase==0 || P[2].energiaBase==0) && gFrames>100)
			{
				gPauseSystem=1;
				gPauseKoTimer++;
				if(gPauseKoTimer>=90 && gPauseKoTimer<=320)
				{
					if(gPing2==0){gPauseSystem=0;}
					if(gPing2==1){gPauseSystem=1;}
				}
				if(gPauseKoTimer>320)
				{
					gPauseSystem=0;
				}
			}else{
				gPauseKoTimer=0;
			}
			
			if(gFrames == 1){ 
				gPodeMover=0;
				FUNCAO_INICIALIZACAO(); //Inicializacao
			}
			if(gFrames<=355){ 
				FUNCAO_ROUND_INIT(); //Rotina de Letreiramento de inicio dos rounds
			}else{
				if(gPauseSystem==0) {
					FUNCAO_RELOGIO(); //HUD relogio
					FUNCAO_BARRAS_DE_ENERGIA(); //HUD barras
				}
				if(P[1].energiaBase==0 || P[2].energiaBase==0){ 
					gPodeMover=0; 
				}
			}
			
			//libera os graficos dos sparks
			if(Spark1_countDown>0){ 
				Spark1_countDown--; 
				if(Spark1_countDown==1) { 
					if(Spark[1]){ SPR_releaseSprite(Spark[1]); Spark[1] = NULL; }
				} 
			}
			if(Spark2_countDown>0){ 
				Spark2_countDown--; 
				if(Spark2_countDown==1) { 
					if(Spark[2]){ SPR_releaseSprite(Spark[2]); Spark[2] = NULL; }
				} 
			}
			
			if(doubleHitStep==1 && P[1].hitPause==0 && P[2].hitPause==0){ doubleHitStep=2; }
			
			if(gPauseSystem==0)
			{
				FUNCAO_INPUT_SYSTEM(); //Verifica os joysticks 
				
				FUNCAO_ANIMACAO(); //Atualiza animacao
				
				FUNCAO_FSM(); //FSM = Finite State Machine (Maquina de Estados)
				
				FUNCAO_PHYSICS(); //Funcoes de Fisica
				
				FUNCAO_CAMERA_BGANIM();
				
				FUNCAO_SAMSHOFX(); //Efeitos do jogo SS2
				
				if(gDebug == 1){ FUNCAO_DEBUG(); } //Debug
			}
			
		}
		
		if(gRoom==11) //AFTER MATCH ---------------------------------------------------------------
		{
			FUNCAO_INPUT_SYSTEM(); //Verifica os joysticks 
		}
		
		//--- FINALIZACOES ---//
		// VDP_showFPS(1);        //Mostra a taxa de FPS
		SPR_update();          //Atualiza (desenha) os sprites
        SYS_doVBlankProcess(); //Wait for screen refresh and do all SGDK VBlank tasks
    }
	
    return 0;
}

//--- FUNCOES ---//

