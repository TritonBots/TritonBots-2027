/**
   @file musical_player.c

   @brief defines helper functions to play musical notes.

   @see musical_notes.h

*/

#include "musical_player.h"

/**
  @brief play a series of notes

  @param TIMX reference to a HAL timer
  @param song_size number of notes in the song
  @param song the set of notes to play

  @note to alter the player, set bpm and articulation delay in musical_config.h
*/
void play_song(TIM_TypeDef* TIMX, uint32_t song_size, note_t *song) {
  TIMX->CCR1 = 50; // start playing at 50% duty cycle
  for (uint16_t note = 0; note < song_size; note++) {
    if (REST == song[note].psc) {
      TIMX->CCR1 = 0; // stop playing
    } else {
      TIMX->CCR1 = 50; // keep playing
      TIMX->PSC = song[note].psc;
    }
    HAL_Delay(song[note].duration);

    // articulate the end of the note so repeated notes have separation
    TIMX->CCR1 = 0;
    HAL_Delay(ARTICULATION_DELAY);
  }
  TIMX->CCR1 = 0; // stop playing
}