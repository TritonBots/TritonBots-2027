/**
   @file musical_player.h

   @brief declares helper functions to play musical notes.

   @see musical_notes.h

*/

#ifndef MUSICAL_PLAYER_H
#define MUSICAL_PLAYER_H

#include "musical_notes.h"

void play_song(TIM_TypeDef* TIMX, uint32_t song_size, note_t *song);

#endif /* MUSICAL_PLAYER_H */