/**
   @file musical_player.h

   @brief declares helper functions to play musical notes.

   @see musical_notes.h

*/

#ifndef MUSICAL_PLAYER_H
#define MUSICAL_PLAYER_H

#include "musical_notes.h"

#define STOP_PLAYING 0 // 0% Duty Cycle
#define START_PLAYING 50 // 50% Duty Cycle

void play_song(uint32_t song_size, note_t *song);
void play_chord(chord_t* chord);

#endif /* MUSICAL_PLAYER_H */