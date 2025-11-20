#include <genesis.h>
#include "graphics.h"
#include "globals.h"
#include "player.h"
#include "fsm.h"
#include "init.h"

void FUNCAO_ANIMACAO()
{
	//CONTROLE DE ANIMACAO E END ANIMATION
	gASG_system = 0; //A.S.G.S. Anti Sprite Glitch System; (Evita a troca simultanea de sprites dos players)
	
	for(i=1; i<=2; i++)
	{
		if (P[i].hitPause==0) {
			
			P[i].frameTimeAtual++; 
			if(P[i].frameTimeAtual>P[i].frameTimeTotal && gASG_system==0) //hora de trocar o frame!
			{
				P[i].animFrame++;
				if(P[i].animFrame>P[i].animFrameTotal) //hora de trocar ou recarregar a animacao!
				{
					gASG_system = 1;
					
					//---FSM CHARS ini--------------------------------------------------
					//ryo 105
					//if(P[i].id==1 && P[i].state==105){ P[i].x+=16*P[i].direcao; }
					//richard 106
					//if(P[i].id==4 && P[i].state==106){ P[i].x+=24*P[i].direcao; }
					//duck 106
					//if(P[i].id==6 && P[i].state==106){ P[i].x+=40*P[i].direcao; }
					//billy 105
					//if(P[i].id==10 && P[i].state==105){ P[i].x+=180*P[i].direcao; }
					//---FSM CHARS end--------------------------------------------------
					
					if(P[i].state==100){ PLAYER_STATE(i,100); }
					if(P[i].state==200){ PLAYER_STATE(i,200); }
					
					// estes aqui previnem bug, caso o tempo de animacao dos Aereos seja definido errado
					// e o player nao tenha tempo de chegar ao solo...
					if(P[i].state==300 || P[i].state==310 || P[i].state==320){ PLAYER_STATE(i,100); }
					if(P[i].state==301 || P[i].state==302 || P[i].state==303){ PLAYER_STATE(i,100); }
					if(P[i].state==304 || P[i].state==305 || P[i].state==306){ PLAYER_STATE(i,100); }
					if(P[i].state==311 || P[i].state==312 || P[i].state==313){ PLAYER_STATE(i,100); }
					if(P[i].state==314 || P[i].state==315 || P[i].state==316){ PLAYER_STATE(i,100); }
					if(P[i].state==321 || P[i].state==322 || P[i].state==323){ PLAYER_STATE(i,100); }
					if(P[i].state==324 || P[i].state==325 || P[i].state==326){ PLAYER_STATE(i,100); }
					if(P[i].state==410){ PLAYER_STATE(i,410); }
					if(P[i].state==420){ PLAYER_STATE(i,420); }
					if(P[i].state==470 || P[i].state==471 || P[i].state==472){ if(P[i].key_JOY_DOWN_status>0){ PLAYER_STATE(i,200); }else{ PLAYER_STATE(i,100); } }
					if(P[i].state==601){ PLAYER_STATE(i,200); }
					if(P[i].state==602){ PLAYER_STATE(i,100); }
					if(P[i].state==603){ P[i].y-=1; P[i].puloTimer=1; PLAYER_STATE(i,310); }
					if(P[i].state==604){ P[i].y-=1; P[i].puloTimer=1; PLAYER_STATE(i,300); }
					if(P[i].state==605){ P[i].y-=1; P[i].puloTimer=1; PLAYER_STATE(i,320); }
					if(P[i].state==607){ PLAYER_STATE(i,100); } //virando em pe
					if(P[i].state==608){ PLAYER_STATE(i,200); } //virando abaixado
					if(P[i].state>=101 && P[i].state<=106){ PLAYER_STATE(i,100); }
					if(P[i].state==107){ PLAYER_STATE(i,108); }
					if(P[i].state==108){ PLAYER_STATE(i,108); }
					if(P[i].state==109){ PLAYER_STATE(i,100); }
					if(P[i].state==110){ PLAYER_STATE(i,109); }
					if(P[i].state==113){ PLAYER_STATE(i,100); }
					if(P[i].state>=151 && P[i].state<=156){ PLAYER_STATE(i,100); }
					if(P[i].state>=201 && P[i].state<=206){ PLAYER_STATE(i,200); }
					if(P[i].state==207){ PLAYER_STATE(i,208); }
					if(P[i].state==208){ PLAYER_STATE(i,208); }
					if(P[i].state==209){ PLAYER_STATE(i,200); }
					if(P[i].state==210){ PLAYER_STATE(i,209); }
					if(P[i].state>=501 && P[i].state<=507)
					{ 
						//desativado, pois eh possivel ir para andar, correr ou parado de acordo com as teclas direcionais pressionadas
						//PLAYER_STATE(i,100);
						
						if(P[i].direcao==1)
						{
							if(P[i].key_JOY_LEFT_status>0)
							{ 
								if(P[i].key_JOY_countdown[4]==0){ PLAYER_STATE(i,410); }else{ 
									if(P[i].inputArray[1]==4 && P[i].inputArray[0]==4){ PLAYER_STATE(i,471);  }else{ PLAYER_STATE(i,410); }
								}
							}
							if(P[i].key_JOY_RIGHT_status>0)
							{ 
								if(P[i].key_JOY_countdown[6]==0){ PLAYER_STATE(i,420); }else{ 
									if(P[i].inputArray[1]==6 && P[i].inputArray[0]==6){ PLAYER_STATE(i,472);  }else{ PLAYER_STATE(i,420); } 
								}
							}
							if(P[i].key_JOY_LEFT_status==0 && P[i].key_JOY_RIGHT_status==0){ PLAYER_STATE(i,100); } //end walk
						}else{
							if(P[i].key_JOY_LEFT_status>0)
							{ 
								if(P[i].key_JOY_countdown[4]==0){ PLAYER_STATE(i,420); }else{ 
									if(P[i].inputArray[1]==6 && P[i].inputArray[0]==6){ PLAYER_STATE(i,472);  }else{ PLAYER_STATE(i,420); } 
								}
							}
							if(P[i].key_JOY_RIGHT_status>0)
							{ 
								if(P[i].key_JOY_countdown[6]==0){ PLAYER_STATE(i,410); }else{ 
									if(P[i].inputArray[1]==4 && P[i].inputArray[0]==4){ PLAYER_STATE(i,471);  }else{ PLAYER_STATE(i,410); }
								}
							}
							if(P[i].key_JOY_LEFT_status==0 && P[i].key_JOY_RIGHT_status==0){ PLAYER_STATE(i,100); } //end walk
						}
						
						/*
						if(P[i].direcao==1)
						{
							
							
							if(P[i].key_JOY_LEFT_status==0 && P[i].key_JOY_RIGHT_status==0){ PLAYER_STATE(i,100); 
							}else if(P[i].key_JOY_LEFT_status>0){ 
								if(P[i].key_JOY_countdown[4]==0){ PLAYER_STATE(i,410); }else{ PLAYER_STATE(i,471); }
							}else if(P[i].key_JOY_RIGHT_status>0){ 
								if(P[i].key_JOY_countdown[6]==0){ PLAYER_STATE(i,420); }else{ PLAYER_STATE(i,472); }
							}
						}else{
							if(P[i].key_JOY_LEFT_status==0 && P[i].key_JOY_RIGHT_status==0){ PLAYER_STATE(i,100); 
							}else if(P[i].key_JOY_LEFT_status>0){ 
								if(P[i].key_JOY_countdown[4]==0){ PLAYER_STATE(i,420); }else{ PLAYER_STATE(i,472);}
							}else if(P[i].key_JOY_RIGHT_status>0){ 
								if(P[i].key_JOY_countdown[6]==0){ PLAYER_STATE(i,410); }else{ PLAYER_STATE(i,471);}
							}
							
						}
						*/
					} //end hurts
					if(P[i].state==511 || P[i].state==512){ PLAYER_STATE(i,200); }
					if(P[i].state==552){ PLAYER_STATE(i,100); } //end queda
					if(P[i].state==570){ if(P[i].energiaBase>0){ PLAYER_STATE(i,552); }else{ PLAYER_STATE(i,570); } } //end pulos
					if(P[i].state==606){ PLAYER_STATE(i,100); } //end pulos
					if(P[i].state==610){ PLAYER_STATE(i,100); } //end Intro
					if(P[i].state==611 || P[i].state==612 || P[i].state==613 || P[i].state==614){ FUNCAO_ROUND_RESTART(); } //end WIN Pose
					if(P[i].state==615){ FUNCAO_ROUND_RESTART(); } //end time lose
					if(P[i].state==618){ PLAYER_STATE(i,100); } //end Rage Explosion
					if(P[i].state>=700 && P[i].state<=790){ PLAYER_STATE(i,100); } //end magias

					if(P[i].state == 800){ PLAYER_STATE(i,100); } //agarrao - fim do inicio
					if(P[i].state == 801){ PLAYER_STATE(i,100); } //agarrao - se pegar, fim do primeiro movimento do player
					if(P[i].state == 802){ PLAYER_STATE(i,100); } //agarrao - se pegar, fim do segundo movimento do player
					if(P[i].state == 803){ PLAYER_STATE(i,100); } //agarrao - segar, fim do estado do inimigo
				}
				P[i].frameTimeAtual=1;
				P[i].frameTimeTotal = P[i].dataAnim[P[i].animFrame];
				
				//hpig 1.1 anti glitch animation overflow
				if(P[i].sprite)
				{
					u16 totalreal = P[i].sprite->animation->numFrame;
					if( (P[i].animFrame-1) < totalreal)
					{ 
						SPR_setAnimAndFrame(P[i].sprite, 0, P[i].animFrame-1); //set the animation if is OK
						FUNCAO_DEPTH(i);
					}
				}
				FUNCAO_FSM_HITBOXES(i); //Atualiza as Hurt / Hitboxes
			}else if(P[i].frameTimeAtual>P[i].frameTimeTotal && gASG_system==1){ //A.S.G.S. 
				if(P[i].frameTimeAtual>1){ P[i].frameTimeAtual--; }
			}
			//*NOTA: No caso do SS2, a animacao abaixando é encurtada (para se abaixar mais rapido) caso se mantenha pressionado para baixo apos o pulo //end pulos 
			/*samsho2*/ if(P[i].state==606 && P[i].animFrame==2 && P[i].frameTimeAtual>=3 && P[i].key_JOY_DOWN_status>=1){ PLAYER_STATE(i,200); } 
		}
	}
	FUNCAO_SPR_POSITION(); //Define a posicao do Sprite
}


void FUNCAO_SPR_POSITION()
{
	//ajusta posicao do sprite
	if(P[1].direcao== 1){ SPR_setPosition(P[1].sprite, P[1].x-(P[1].w-P[1].axisX)-camPosX, P[1].y-P[1].axisY); }
	if(P[1].direcao==-1){ SPR_setPosition(P[1].sprite, P[1].x- P[1].axisX        -camPosX, P[1].y-P[1].axisY); }
	if(P[2].direcao== 1){ SPR_setPosition(P[2].sprite, P[2].x-(P[2].w-P[2].axisX)-camPosX, P[2].y-P[2].axisY); }
	if(P[2].direcao==-1){ SPR_setPosition(P[2].sprite, P[2].x- P[2].axisX        -camPosX, P[2].y-P[2].axisY); }
	
	/*
	if(gSombraStyle==2)
	{
		SPR_setPosition(P[1].sombra, P[1].x-32-camPosX, gAlturaPiso-5); // *NOTA: A sombra do SS2 tem 80px, entao desloquei -40px no eixo X
		SPR_setPosition(P[2].sombra, P[2].x-32-camPosX, gAlturaPiso-5); // para que ela ficasse perfeitamente alinhada aos players 
	}else{
		if(gPing2==0){ SPR_setPosition(P[1].sombra, P[1].x-32-camPosX, gAlturaPiso-5); }
		if(gPing2==1){ SPR_setPosition(P[1].sombra, P[2].x-32-camPosX, gAlturaPiso-5); }
	}
	*/
}


void FUNCAO_CAMERA_BGANIM()
{
	//---------------------------------------------------------------------------------------------new cam ini
	//Metodo novo, hamoopig 1.1
	//Calcula o meio da tela, para centralizar a camera
	if (P[1].x > P[2].x) {
		gMeioDaTela = (P[2].x + ((P[1].x - P[2].x)/2)) - (320 / 2);
	} else {
		gMeioDaTela = (P[1].x + ((P[2].x - P[1].x)/2)) - (320 / 2);
	}

	//Posiciona a camera
	camPosX = gMeioDaTela;

	//Limites do cenario
	if( camPosX < 0 ){ camPosX = 0; } 
	if( camPosX > gBG_Width-320 ){ camPosX = gBG_Width-320; }

	//Movimenta o BG
	if(camPosXanterior != camPosX) {
		VDP_setHorizontalScroll(BG_B, camPosX*-1);
		camPosXanterior=camPosX;
	}
	//---------------------------------------------------------------------------------------------new cam end
}


void FUNCAO_SAMSHOFX() //ESPECIFICO DO SAMURAI SHODOWN 2
{
	//ESPECIFICO DE SAMURAI SHODOW. AJUSTE DA BARRA DE RAGE
	if(P[1].energiaSP ==  0){  P[1].rageLvl=0; }
	if(P[1].energiaSP >   0 && P[1].energiaSP<=15){ P[1].rageLvl=0; }
	if(P[1].energiaSP >= 16 && P[1].energiaSP<=31){ P[1].rageLvl=1; }
	if(P[1].energiaSP >= 32){  P[1].rageLvl=2; }
	
	if(P[2].energiaSP ==  0){  P[2].rageLvl=0; }
	if(P[2].energiaSP >   0 && P[2].energiaSP<=15){ P[2].rageLvl=0; }
	if(P[2].energiaSP >= 16 && P[2].energiaSP<=31){ P[2].rageLvl=1; }
	if(P[2].energiaSP >= 32){  P[2].rageLvl=2; }
	
	//ESPECIFICO DO SAMURAI SHODOW. ESPADA PISCANDO E SOMBRA
	/*
	if(gSombraStyle==1)
	{
		if(gPing2==0)
		{ 
			//P1
			if(gSombraStyle==2){ SPR_setVisibility(P[1].sombra, VISIBLE); }
			//P2
			if(gSombraStyle==2){ SPR_setVisibility(P[2].sombra, HIDDEN); }
		}
		if(gPing2==1)
		{ 
			//P1
			if(gSombraStyle==2){ SPR_setVisibility(P[1].sombra, HIDDEN); }
			//P2
			if(gSombraStyle==2){ SPR_setVisibility(P[2].sombra, VISIBLE); }
		}
	}
	*/
	
}






