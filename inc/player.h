#ifndef PLAYER_H
#define PLAYER_H

#include "globals.h"

void PLAYER_STATE(u8 Player, u16 State);
void FUNCAO_PLAY_SND(u8 Player, u16 State);
void FUNCAO_DEPTH(u8 Player);
void FUNCAO_UPDATE_LIFESP(u8 Player, u8 EnergyType, s8 Value);

#endif // PLAYER_H
