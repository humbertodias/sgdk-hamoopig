#include <genesis.h>
#include "debug.h"
#include "globals.h"

void FUNCAO_CHECK_FRAME_ADVANTAGE() {
	if ((P[1].control == TRUE  && P[2].control == TRUE  && frameAdvCounterP1 != 0) ||
	    (P[1].control == FALSE && P[2].control == FALSE && frameAdvCounterP1 != 0)) {
		
		//P!
		lastFrameAdvCounterP1 = frameAdvCounterP1;
		frameAdvCounterP1 = 0;

		//P2
		lastFrameAdvCounterP2 = frameAdvCounterP2;
		frameAdvCounterP2 = 0;

	} else {

		if (P[1].control && !P[2].control) {
			frameAdvCounterP1++;
			frameAdvCounterP2--;
			
		} else if (!P[1].control && P[2].control) {
			frameAdvCounterP1--;
			frameAdvCounterP2++;
			
		}
	}
}

void FUNCAO_DEBUG()
{
	//Atencao! O debug só é funcional se você não printar sprites em cima dos seus caracteres alfanuméricos!
	// Procure pelo comando: SPR_setVRAMTileIndex(GE[XX].sprite, 1441); 
	// Onde, 1441 é o comeco dos tiles alfanumericos, e 1535 é o final desses tiles!
	
	//Debug em texto, desativado:
	VDP_drawText("HAMOOPIG ENGINE", 1, 1);
	sprintf(gStr, "P1-> %i,%i S:%i T:%i/%i F:%i/%i    ", P[1].x, P[1].y, P[1].state, P[1].frameTimeAtual, P[1].frameTimeTotal, P[1].animFrame, P[1].animFrameTotal ); 
	sprintf(gStr, "P1-> S:%i T:%i/%i F:%i/%i    ", P[1].state, P[1].frameTimeAtual, P[1].frameTimeTotal, P[1].animFrame, P[1].animFrameTotal ); 
	VDP_drawText(gStr, 1, 2);
	sprintf(gStr, "P2-> S:%i T:%i/%i F:%i/%i    ", P[2].state, P[2].frameTimeAtual, P[2].frameTimeTotal, P[2].animFrame, P[2].animFrameTotal ); 
	VDP_drawText(gStr, 1, 3);
	sprintf(gStr, "UP:%i DOWN:%i LEFT:%i RIGHT:%i ATK_B:%i  ", P[1].joyDirTimer[8], P[1].joyDirTimer[2], P[1].joyDirTimer[4], P[1].joyDirTimer[6], P[1].attackButton ); 
	

	u8 dist = 0;
	if (P[1].x > P[2].x) {
		dist = P[1].x - P[2].x;
	} else {
		dist = P[2].x - P[1].x;
	}

	KLog_U2("P1 state: ", P[1].state, ", P2 state: ", P[2].state);
	KLog_U2("P1 x: ", P[1].x, ", P2 x: ", P[2].x);
	KLog_U2("P1 y: ", P[1].y, ", P2 y: ", P[2].y);
	KLog_U1("Distancia entre P1 e P2: ", dist);
	KLog_U2("P1 hits: ", P[1].hitCounter, ", P2 hits: ", P[2].hitCounter);

	FUNCAO_CHECK_FRAME_ADVANTAGE();
	KLog_S2("P1 frame adv: ", lastFrameAdvCounterP1, ", P2 frame adv: ", lastFrameAdvCounterP2);



	if(RELEASE==0)
	{
		SPR_setPosition(GE[1].sprite, P[1].x-4-camPosX, P[1].y-5);
		SPR_setPosition(GE[2].sprite, P[2].x-4-camPosX, P[2].y-5);
	}
	
	if(RELEASE==0)
	{
		//P1
		//bodyboxes
		if(P[1].dataBBox[0]==0 && P[1].dataBBox[2]==0){
			SPR_setPosition(Rect1BB1_Q1,-8,-8); SPR_setPosition(Rect1BB1_Q2,-8,-8); SPR_setPosition(Rect1BB1_Q3,-8,-8); SPR_setPosition(Rect1BB1_Q4,-8,-8);
		}else{
			SPR_setPosition(Rect1BB1_Q1, P[1].x+P[1].dataBBox[0]  -camPosX, P[1].y+P[1].dataBBox[1]);
			SPR_setPosition(Rect1BB1_Q2, P[1].x+P[1].dataBBox[2]-8-camPosX, P[1].y+P[1].dataBBox[1]);
			SPR_setPosition(Rect1BB1_Q3, P[1].x+P[1].dataBBox[0]  -camPosX, P[1].y+P[1].dataBBox[3]-8);
			SPR_setPosition(Rect1BB1_Q4, P[1].x+P[1].dataBBox[2]-8-camPosX, P[1].y+P[1].dataBBox[3]-8);
		}
		//hitboxes
		if(P[1].dataHBox[0]==0 && P[1].dataHBox[2]==0){
			SPR_setPosition(Rect1HB1_Q1,-8,-8); SPR_setPosition(Rect1HB1_Q2,-8,-8); SPR_setPosition(Rect1HB1_Q3,-8,-8); SPR_setPosition(Rect1HB1_Q4,-8,-8);
		}else{
			SPR_setPosition(Rect1HB1_Q1, P[1].x+P[1].dataHBox[0]  -camPosX, P[1].y+P[1].dataHBox[1]);
			SPR_setPosition(Rect1HB1_Q2, P[1].x+P[1].dataHBox[2]-8-camPosX, P[1].y+P[1].dataHBox[1]);
			SPR_setPosition(Rect1HB1_Q3, P[1].x+P[1].dataHBox[0]  -camPosX, P[1].y+P[1].dataHBox[3]-8);
			SPR_setPosition(Rect1HB1_Q4, P[1].x+P[1].dataHBox[2]-8-camPosX, P[1].y+P[1].dataHBox[3]-8);
		}

		//P2
		//bodyboxes
		if(P[2].dataBBox[0]==0 && P[2].dataBBox[2]==0){
			SPR_setPosition(Rect2BB1_Q1,-8,-8); SPR_setPosition(Rect2BB1_Q2,-8,-8); SPR_setPosition(Rect2BB1_Q3,-8,-8); SPR_setPosition(Rect2BB1_Q4,-8,-8);
		}else{
			SPR_setPosition(Rect2BB1_Q1, P[2].x+P[2].dataBBox[0]  -camPosX, P[2].y+P[2].dataBBox[1]);
			SPR_setPosition(Rect2BB1_Q2, P[2].x+P[2].dataBBox[2]-8-camPosX, P[2].y+P[2].dataBBox[1]);
			SPR_setPosition(Rect2BB1_Q3, P[2].x+P[2].dataBBox[0]  -camPosX, P[2].y+P[2].dataBBox[3]-8);
			SPR_setPosition(Rect2BB1_Q4, P[2].x+P[2].dataBBox[2]-8-camPosX, P[2].y+P[2].dataBBox[3]-8);
		}
		//hitboxes
		if(P[2].dataHBox[0]==0 && P[2].dataHBox[2]==0){
			SPR_setPosition(Rect2HB1_Q1,-8,-8); SPR_setPosition(Rect2HB1_Q2,-8,-8); SPR_setPosition(Rect2HB1_Q3,-8,-8); SPR_setPosition(Rect2HB1_Q4,-8,-8);
		}else{
			SPR_setPosition(Rect2HB1_Q1, P[2].x+P[2].dataHBox[0]  -camPosX, P[2].y+P[2].dataHBox[1]);
			SPR_setPosition(Rect2HB1_Q2, P[2].x+P[2].dataHBox[2]-8-camPosX, P[2].y+P[2].dataHBox[1]);
			SPR_setPosition(Rect2HB1_Q3, P[2].x+P[2].dataHBox[0]  -camPosX, P[2].y+P[2].dataHBox[3]-8);
			SPR_setPosition(Rect2HB1_Q4, P[2].x+P[2].dataHBox[2]-8-camPosX, P[2].y+P[2].dataHBox[3]-8);
		}

		//hitboxes das magias para o P1
		if (P[1].fball.active == 1) {
			SPR_setPosition(Rect1HB1_Q1, P[1].fball.x + P[1].fball.dataHBox[0]   -camPosX, P[1].fball.y + P[1].fball.dataHBox[1]);
			SPR_setPosition(Rect1HB1_Q2, P[1].fball.x + P[1].fball.dataHBox[2] -8-camPosX, P[1].fball.y + P[1].fball.dataHBox[1]);
			SPR_setPosition(Rect1HB1_Q3, P[1].fball.x + P[1].fball.dataHBox[0]   -camPosX, P[1].fball.y + P[1].fball.dataHBox[3] -8);
			SPR_setPosition(Rect1HB1_Q4, P[1].fball.x + P[1].fball.dataHBox[2] -8-camPosX, P[1].fball.y + P[1].fball.dataHBox[3] -8);
		}
		//hitboxes das magias para o P2
		if (P[2].fball.active == 1) {
			SPR_setPosition(Rect1HB1_Q1, P[2].fball.x + P[2].fball.dataHBox[0]   -camPosX, P[2].fball.y + P[2].fball.dataHBox[1]);
			SPR_setPosition(Rect1HB1_Q2, P[2].fball.x + P[2].fball.dataHBox[2] -8-camPosX, P[2].fball.y + P[2].fball.dataHBox[1]);
			SPR_setPosition(Rect1HB1_Q3, P[2].fball.x + P[2].fball.dataHBox[0]   -camPosX, P[2].fball.y + P[2].fball.dataHBox[3] -8);
			SPR_setPosition(Rect1HB1_Q4, P[2].fball.x + P[2].fball.dataHBox[2] -8-camPosX, P[2].fball.y + P[2].fball.dataHBox[3] -8);
		}
		
		//metodo de display HBoxes Info, (piscando) = reduz os tiles simultaneos em tela (DESATIVADO)
		//para facilitar a vida de outros desenvolvedores, decidi manter a exibicao das caixas o tempo todo
		if(gPing2==0)
		{
			/*
			SPR_setVisibility(Rect1HB1_Q1, VISIBLE); SPR_setVisibility(Rect1HB1_Q2, VISIBLE);
			SPR_setVisibility(Rect1HB1_Q3, VISIBLE); SPR_setVisibility(Rect1HB1_Q4, VISIBLE);
			SPR_setVisibility(Rect1BB1_Q1, VISIBLE); SPR_setVisibility(Rect1BB1_Q2, VISIBLE);
			SPR_setVisibility(Rect1BB1_Q3, VISIBLE); SPR_setVisibility(Rect1BB1_Q4, VISIBLE);
			
			SPR_setVisibility(Rect2HB1_Q1, HIDDEN); SPR_setVisibility(Rect2HB1_Q2, HIDDEN);
			SPR_setVisibility(Rect2HB1_Q3, HIDDEN); SPR_setVisibility(Rect2HB1_Q4, HIDDEN);
			SPR_setVisibility(Rect2BB1_Q1, HIDDEN); SPR_setVisibility(Rect2BB1_Q2, HIDDEN);
			SPR_setVisibility(Rect2BB1_Q3, HIDDEN); SPR_setVisibility(Rect2BB1_Q4, HIDDEN);
		}else{
			SPR_setVisibility(Rect1HB1_Q1, HIDDEN); SPR_setVisibility(Rect1HB1_Q2, HIDDEN);
			SPR_setVisibility(Rect1HB1_Q3, HIDDEN); SPR_setVisibility(Rect1HB1_Q4, HIDDEN);
			SPR_setVisibility(Rect1BB1_Q1, HIDDEN); SPR_setVisibility(Rect1BB1_Q2, HIDDEN);
			SPR_setVisibility(Rect1BB1_Q3, HIDDEN); SPR_setVisibility(Rect1BB1_Q4, HIDDEN);
			
			SPR_setVisibility(Rect2HB1_Q1, VISIBLE); SPR_setVisibility(Rect2HB1_Q2, VISIBLE);
			SPR_setVisibility(Rect2HB1_Q3, VISIBLE); SPR_setVisibility(Rect2HB1_Q4, VISIBLE);
			SPR_setVisibility(Rect2BB1_Q1, VISIBLE); SPR_setVisibility(Rect2BB1_Q2, VISIBLE);
			SPR_setVisibility(Rect2BB1_Q3, VISIBLE); SPR_setVisibility(Rect2BB1_Q4, VISIBLE);
			*/
		}
	}
}
