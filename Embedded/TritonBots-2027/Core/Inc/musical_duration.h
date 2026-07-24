/**
   @file musical_duration.h

   @brief contains the various musical note durations.

   @see musical_config.h
*/

#ifndef MUSICAL_DURATION_H
#define MUSICAL_DURATION_H

#include "musical_config.h"

#define BPS (BPM / 60.0f)
#define BPS_MS (1000.0f / BPS)

#define WHOLE_NOTE 4.0f * (BPS_MS)
#define HALF_NOTE (WHOLE_NOTE) / 2
#define QUARTER_NOTE (WHOLE_NOTE) / 4
#define EIGHTH_NOTE (WHOLE_NOTE) / 8
#define SIXTEENTH_NOTE (WHOLE_NOTE) / 16
#define THIRTY_SECOND_NOTE (WHOLE_NOTE) / 32

#define DOTTED_WHOTE_NOTE (WHOLE_NOTE) + (HALF_NOTE)
#define DOTTED_HALF_NOTE  (HALF_NOTE) + (QUARTER_NOTE)
#define DOTTED_QUARTER_NOTE (QUARTER_NOTE) + (EIGHTH_NOTE)
#define DOTTED_EIGHTH_NOTE (EIGHTH_NOTE) + (SIXTEENTH_NOTE)
#define DOTTED_SIXTEENTH_NOTE (SIXTEENTH_NOTE) + (THIRTY_SECOND_NOTE)


#endif /* MUSICAL_DURATION_H */