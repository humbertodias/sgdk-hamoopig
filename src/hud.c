#include <genesis.h>
#include "hud.h"
#include "globals.h"
#include "sprite.h"

void FUNCAO_RELOGIO()
{
	/*
	if(gClockTimer>0 && (gClockLTimer>0 || gClockRTimer>0) && (P[1].energiaBase>0 && P[2].energiaBase>0) ){ gClockTimer--; }
	//temporario
	if(gClockLTimer==0 && gClockRTimer==1){ gClockLTimer=9; gClockRTimer=9; }
	
	if(gClockTimer==0)
	{
		gClockRTimer--;
		SPR_releaseSprite(ClockR);
		if(gClockRTimer==9){ ClockR = SPR_addSpriteEx(&spr_n9, 161, 22, TILE_ATTR(PAL1, FALSE, FALSE, FALSE), SPR_FLAG_DISABLE_DELAYED_FRAME_UPDATE | SPR_FLAG_AUTO_VISIBILITY | SPR_FLAG_AUTO_VRAM_ALLOC | SPR_FLAG_AUTO_TILE_UPLOAD); }
		if(gClockRTimer==8){ ClockR = SPR_addSpriteEx(&spr_n8, 161, 22, TILE_ATTR(PAL1, FALSE, FALSE, FALSE), SPR_FLAG_DISABLE_DELAYED_FRAME_UPDATE | SPR_FLAG_AUTO_VISIBILITY | SPR_FLAG_AUTO_VRAM_ALLOC | SPR_FLAG_AUTO_TILE_UPLOAD); }
		if(gClockRTimer==7){ ClockR = SPR_addSpriteEx(&spr_n7, 161, 22, TILE_ATTR(PAL1, FALSE, FALSE, FALSE), SPR_FLAG_DISABLE_DELAYED_FRAME_UPDATE | SPR_FLAG_AUTO_VISIBILITY | SPR_FLAG_AUTO_VRAM_ALLOC | SPR_FLAG_AUTO_TILE_UPLOAD); }
		if(gClockRTimer==6){ ClockR = SPR_addSpriteEx(&spr_n6, 161, 22, TILE_ATTR(PAL1, FALSE, FALSE, FALSE), SPR_FLAG_DISABLE_DELAYED_FRAME_UPDATE | SPR_FLAG_AUTO_VISIBILITY | SPR_FLAG_AUTO_VRAM_ALLOC | SPR_FLAG_AUTO_TILE_UPLOAD); }
		if(gClockRTimer==5){ ClockR = SPR_addSpriteEx(&spr_n5, 161, 22, TILE_ATTR(PAL1, FALSE, FALSE, FALSE), SPR_FLAG_DISABLE_DELAYED_FRAME_UPDATE | SPR_FLAG_AUTO_VISIBILITY | SPR_FLAG_AUTO_VRAM_ALLOC | SPR_FLAG_AUTO_TILE_UPLOAD); }
		if(gClockRTimer==4){ ClockR = SPR_addSpriteEx(&spr_n4, 161, 22, TILE_ATTR(PAL1, FALSE, FALSE, FALSE), SPR_FLAG_DISABLE_DELAYED_FRAME_UPDATE | SPR_FLAG_AUTO_VISIBILITY | SPR_FLAG_AUTO_VRAM_ALLOC | SPR_FLAG_AUTO_TILE_UPLOAD); }
		if(gClockRTimer==3){ ClockR = SPR_addSpriteEx(&spr_n3, 161, 22, TILE_ATTR(PAL1, FALSE, FALSE, FALSE), SPR_FLAG_DISABLE_DELAYED_FRAME_UPDATE | SPR_FLAG_AUTO_VISIBILITY | SPR_FLAG_AUTO_VRAM_ALLOC | SPR_FLAG_AUTO_TILE_UPLOAD); }
		if(gClockRTimer==2){ ClockR = SPR_addSpriteEx(&spr_n2, 161, 22, TILE_ATTR(PAL1, FALSE, FALSE, FALSE), SPR_FLAG_DISABLE_DELAYED_FRAME_UPDATE | SPR_FLAG_AUTO_VISIBILITY | SPR_FLAG_AUTO_VRAM_ALLOC | SPR_FLAG_AUTO_TILE_UPLOAD); }
		if(gClockRTimer==1){ ClockR = SPR_addSpriteEx(&spr_n1, 161, 22, TILE_ATTR(PAL1, FALSE, FALSE, FALSE), SPR_FLAG_DISABLE_DELAYED_FRAME_UPDATE | SPR_FLAG_AUTO_VISIBILITY | SPR_FLAG_AUTO_VRAM_ALLOC | SPR_FLAG_AUTO_TILE_UPLOAD); }
		if(gClockRTimer==0){ ClockR = SPR_addSpriteEx(&spr_n0, 161, 22, TILE_ATTR(PAL1, FALSE, FALSE, FALSE), SPR_FLAG_DISABLE_DELAYED_FRAME_UPDATE | SPR_FLAG_AUTO_VISIBILITY | SPR_FLAG_AUTO_VRAM_ALLOC | SPR_FLAG_AUTO_TILE_UPLOAD); }
		SPR_setVRAMTileIndex(ClockR, 1447); //define uma posicao especifica para o GFX na VRAM
		if(ClockR){ SPR_setDepth(ClockR, 255); }
		
		if(gClockRTimer==-1)
		{
			if(gClockLTimer>0)
			{
				gClockLTimer--;
				SPR_releaseSprite(ClockL);
				if(gClockLTimer==9){ ClockL = SPR_addSpriteEx(&spr_n9, 146, 22, TILE_ATTR(PAL1, FALSE, FALSE, FALSE), SPR_FLAG_DISABLE_DELAYED_FRAME_UPDATE | SPR_FLAG_AUTO_VISIBILITY | SPR_FLAG_AUTO_VRAM_ALLOC | SPR_FLAG_AUTO_TILE_UPLOAD); }
				if(gClockLTimer==8){ ClockL = SPR_addSpriteEx(&spr_n8, 146, 22, TILE_ATTR(PAL1, FALSE, FALSE, FALSE), SPR_FLAG_DISABLE_DELAYED_FRAME_UPDATE | SPR_FLAG_AUTO_VISIBILITY | SPR_FLAG_AUTO_VRAM_ALLOC | SPR_FLAG_AUTO_TILE_UPLOAD); }
				if(gClockLTimer==7){ ClockL = SPR_addSpriteEx(&spr_n7, 146, 22, TILE_ATTR(PAL1, FALSE, FALSE, FALSE), SPR_FLAG_DISABLE_DELAYED_FRAME_UPDATE | SPR_FLAG_AUTO_VISIBILITY | SPR_FLAG_AUTO_VRAM_ALLOC | SPR_FLAG_AUTO_TILE_UPLOAD); }
				if(gClockLTimer==6){ ClockL = SPR_addSpriteEx(&spr_n6, 146, 22, TILE_ATTR(PAL1, FALSE, FALSE, FALSE), SPR_FLAG_DISABLE_DELAYED_FRAME_UPDATE | SPR_FLAG_AUTO_VISIBILITY | SPR_FLAG_AUTO_VRAM_ALLOC | SPR_FLAG_AUTO_TILE_UPLOAD); }
				if(gClockLTimer==5){ ClockL = SPR_addSpriteEx(&spr_n5, 146, 22, TILE_ATTR(PAL1, FALSE, FALSE, FALSE), SPR_FLAG_DISABLE_DELAYED_FRAME_UPDATE | SPR_FLAG_AUTO_VISIBILITY | SPR_FLAG_AUTO_VRAM_ALLOC | SPR_FLAG_AUTO_TILE_UPLOAD); }
				if(gClockLTimer==4){ ClockL = SPR_addSpriteEx(&spr_n4, 146, 22, TILE_ATTR(PAL1, FALSE, FALSE, FALSE), SPR_FLAG_DISABLE_DELAYED_FRAME_UPDATE | SPR_FLAG_AUTO_VISIBILITY | SPR_FLAG_AUTO_VRAM_ALLOC | SPR_FLAG_AUTO_TILE_UPLOAD); }
				if(gClockLTimer==3){ ClockL = SPR_addSpriteEx(&spr_n3, 146, 22, TILE_ATTR(PAL1, FALSE, FALSE, FALSE), SPR_FLAG_DISABLE_DELAYED_FRAME_UPDATE | SPR_FLAG_AUTO_VISIBILITY | SPR_FLAG_AUTO_VRAM_ALLOC | SPR_FLAG_AUTO_TILE_UPLOAD); }
				if(gClockLTimer==2){ ClockL = SPR_addSpriteEx(&spr_n2, 146, 22, TILE_ATTR(PAL1, FALSE, FALSE, FALSE), SPR_FLAG_DISABLE_DELAYED_FRAME_UPDATE | SPR_FLAG_AUTO_VISIBILITY | SPR_FLAG_AUTO_VRAM_ALLOC | SPR_FLAG_AUTO_TILE_UPLOAD); }
				if(gClockLTimer==1){ ClockL = SPR_addSpriteEx(&spr_n1, 146, 22, TILE_ATTR(PAL1, FALSE, FALSE, FALSE), SPR_FLAG_DISABLE_DELAYED_FRAME_UPDATE | SPR_FLAG_AUTO_VISIBILITY | SPR_FLAG_AUTO_VRAM_ALLOC | SPR_FLAG_AUTO_TILE_UPLOAD); }
				if(gClockLTimer==0){ ClockL = SPR_addSpriteEx(&spr_n0, 146, 22, TILE_ATTR(PAL1, FALSE, FALSE, FALSE), SPR_FLAG_DISABLE_DELAYED_FRAME_UPDATE | SPR_FLAG_AUTO_VISIBILITY | SPR_FLAG_AUTO_VRAM_ALLOC | SPR_FLAG_AUTO_TILE_UPLOAD); }
				SPR_setVRAMTileIndex(ClockL, 1441); //define uma posicao especifica para o GFX na VRAM
				gClockRTimer=9;
				SPR_releaseSprite(ClockR);
				ClockR = SPR_addSpriteEx(&spr_n9, 161, 22, TILE_ATTR(PAL1, FALSE, FALSE, FALSE), SPR_FLAG_DISABLE_DELAYED_FRAME_UPDATE | SPR_FLAG_AUTO_VISIBILITY | SPR_FLAG_AUTO_VRAM_ALLOC | SPR_FLAG_AUTO_TILE_UPLOAD);
				SPR_setVRAMTileIndex(ClockR, 1447); //define uma posicao especifica para o GFX na VRAM
				if(ClockL){ SPR_setDepth(ClockL, 255); }
			}
		}
		gClockTimer=38; //reset Clock Count timer
	}
	*/
	
	//if(gClockRTimer==-1 && gClockRTimer==-1)
	//{ 
		/*TIMER OVER!*/ 
		//ClockR = SPR_addSpriteEx(&spr_n0, 160, 32, TILE_ATTR(PAL1, FALSE, FALSE, FALSE), SPR_FLAG_DISABLE_DELAYED_FRAME_UPDATE | SPR_FLAG_AUTO_VISIBILITY | SPR_FLAG_AUTO_VRAM_ALLOC | SPR_FLAG_AUTO_TILE_UPLOAD);
		//SPR_setVRAMTileIndex(ClockR,1707); //define uma posicao especifica para o GFX na VRAM
	//}
}

void FUNCAO_BARRAS_DE_ENERGIA()
{
	
	for(i=1; i<=2; i++)
	{
		if( P[i].energia != P[i].energiaBase )
		{ 
			if(P[i].energia > P[i].energiaBase){ P[i].energia--; } //decrementa a 'energia' aos poucos, até igualar a 'energiaBase'
			if(P[i].energia < P[i].energiaBase){ P[i].energia++; } //incrementa a 'energia' aos poucos, até igualar a 'energiaBase'
		} 
		
		u8 subEnergyPos;
		if(GE[2+i].sprite)
		{
			if(                           P[i].energia== 96){ SPR_setAnimAndFrame(GE[2+i].sprite, 0, 0); subEnergyPos= 0;
			}else if(P[i].energia<  96 && P[i].energia>= 88){ SPR_setAnimAndFrame(GE[2+i].sprite, 0, 1); subEnergyPos= 1;
			}else if(P[i].energia<  88 && P[i].energia>= 80){ SPR_setAnimAndFrame(GE[2+i].sprite, 0, 2); subEnergyPos= 2;
			}else if(P[i].energia<  80 && P[i].energia>= 72){ SPR_setAnimAndFrame(GE[2+i].sprite, 0, 3); subEnergyPos= 3;
			}else if(P[i].energia<  72 && P[i].energia>= 64){ SPR_setAnimAndFrame(GE[2+i].sprite, 0, 4); subEnergyPos= 4;
			}else if(P[i].energia<  64 && P[i].energia>= 56){ SPR_setAnimAndFrame(GE[2+i].sprite, 0, 5); subEnergyPos= 5;
			}else if(P[i].energia<  56 && P[i].energia>= 48){ SPR_setAnimAndFrame(GE[2+i].sprite, 0, 6); subEnergyPos= 6;
			}else if(P[i].energia<  48 && P[i].energia>= 40){ SPR_setAnimAndFrame(GE[2+i].sprite, 0, 7); subEnergyPos= 7;
			}else if(P[i].energia<  40 && P[i].energia>= 32){ SPR_setAnimAndFrame(GE[2+i].sprite, 0, 8); subEnergyPos= 8;
			}else if(P[i].energia<  32 && P[i].energia>= 24){ SPR_setAnimAndFrame(GE[2+i].sprite, 0, 9); subEnergyPos= 9;
			}else if(P[i].energia<  24 && P[i].energia>= 16){ SPR_setAnimAndFrame(GE[2+i].sprite, 0,10); subEnergyPos=10;
			}else if(P[i].energia<  16 && P[i].energia>=  8){ SPR_setAnimAndFrame(GE[2+i].sprite, 0,11); subEnergyPos=11;
			}else if(P[i].energia<   8 && P[i].energia>=  1){ SPR_setAnimAndFrame(GE[2+i].sprite, 0,12); subEnergyPos=12;
			}else if(                     P[i].energia==  0){ SPR_setAnimAndFrame(GE[2+i].sprite, 0,12); subEnergyPos=12;
			}
		}
		if(GE[4+i].sprite)
		{
			if(i==1){ SPR_setPosition(GE[4+i].sprite,  40+(subEnergyPos*8), 12); }
			if(i==2){ SPR_setPosition(GE[4+i].sprite, 280-(subEnergyPos*8), 12); }
		}
		
		int a=0;
		if(subEnergyPos== 0){ a= 96; }
		if(subEnergyPos== 1){ a= 88; }
		if(subEnergyPos== 2){ a= 80; }
		if(subEnergyPos== 3){ a= 72; }
		if(subEnergyPos== 4){ a= 64; }
		if(subEnergyPos== 5){ a= 56; }
		if(subEnergyPos== 6){ a= 48; }
		if(subEnergyPos== 7){ a= 40; }
		if(subEnergyPos== 8){ a= 32; }
		if(subEnergyPos== 9){ a= 24; }
		if(subEnergyPos==10){ a= 16; }
		if(subEnergyPos==11){ a=  8; }
		if(subEnergyPos==12){ a=  0; }
		if(GE[4+i].sprite){ SPR_setAnimAndFrame(GE[4+i].sprite, 0, (P[i].energia-a) ); }
		
		//Exibe a barra de especial, e fica piscando, caso seja == 32
		/*
		if(P[i].energiaSP<32)
		{
			SPR_setAnimAndFrame(GE[6+i].sprite, 0, P[i].energiaSP);
		}else{
			if(gPing2==1){
				SPR_setAnimAndFrame(GE[6+i].sprite, 0, 32);
			}else{
				SPR_setAnimAndFrame(GE[6+i].sprite, 0, 33);
			}
		}
		*/
		
	}
	
	//if(P[1].energiaSP>=32){ SPR_setVisibility(GE[ 9].sprite, VISIBLE); }else{ SPR_setVisibility(GE[ 9].sprite, HIDDEN); }
	//if(P[2].energiaSP>=32){ SPR_setVisibility(GE[10].sprite, VISIBLE); }else{ SPR_setVisibility(GE[10].sprite, HIDDEN); }
	
}
