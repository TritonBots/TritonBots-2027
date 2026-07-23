/**
   @file musical_player.c

   @brief defines helper functions to play musical notes.

   @see musical_notes.h

*/

#include "musical_player.h"

void play_song(TIM_TypeDef* TIMX, uint32_t song_size, note_t *song) {
  TIMX->CCR1 = 50; // start playing
  for (uint16_t note = 0; note < song_size; note++) {
    if (0 == song[note].psc) {
      TIMX->CCR1 = 0; // stop playing
    } else {
      TIMX->CCR1 = 50; // keep playing
      TIMX->PSC = song[note].psc;
    }
    HAL_Delay(song[note].duration);

    // articulate the end of the note so repeated notes have separation
    TIMX->CCR1 = 0;
    HAL_Delay(5);
  }
  TIMX->CCR1 = 0; // stop playing
}