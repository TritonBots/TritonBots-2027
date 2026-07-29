/**
   @file musical_player.c

   @brief defines helper functions to play musical notes.

   @see musical_notes.h

*/

#include "musical_player.h"

/**
  @brief play a series of notes

  @param song_size number of notes in the song
  @param song the set of notes to play

  @note to alter the player, set bpm and articulation delay in musical_config.h
*/
void play_song(uint32_t song_size, note_t *song) {
  TIMX->CCR1 = START_PLAYING;
  for (uint32_t note = 0; note < song_size; note++) {
    if (REST == song[note].psc) {
      TIMX->CCR1 = STOP_PLAYING;
    } else {
      TIMX->CCR1 = START_PLAYING; // keep playing
      TIMX->PSC = song[note].psc;
    }
    HAL_Delay(song[note].duration);

    #if ARTICULATION_DELAY != 0
    // articulate the end of the note so repeated notes have separation
    TIMX->CCR1 = STOP_PLAYING;
    HAL_Delay(ARTICULATION_DELAY);
    #endif
  }
  TIMX->CCR1 = 0; // stop playing
}

/**
  @brief play a chord of multiple notes at once

  @param chord the chord to be played for its duration

*/
void play_chord(chord_t *chord) {
  TIMX->CCR1 = 50;
  const uint32_t start = HAL_GetTick();
  while(HAL_GetTick() - start < chord->duration) {
    for (int i=0;i<chord->size;i++) {
      TIMX->PSC = chord->psc[i];
      HAL_Delay(CHORD_DELAY);
    }
  }
  TIMX->CCR1 = 0;
}