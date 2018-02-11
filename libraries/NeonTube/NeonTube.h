/*
 * NeonTube.h
 *
 * Neon Tube - V 0.1 (Proof of concept)
 * Toolkit for simulating a neon tube
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 * Neon Tube Copyright (C) 2018 Frank Reins (github@rein-zieh.de)
 *
 * This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
 * This is free software, and you are welcome to redistribute it
 * under certain conditions; type `show c' for details.
 */

#ifndef NeonTube_h
#define NeonTube_h

#include "Arduino.h"
#include "NTTimer.h"

enum NT_Pattern { NT_NOPATTERN, NT_DIGITALPATTERN, NT_ANALOGPATTERN }; 

class NeonTube
{
    public:

        NeonTube();

        void init(
            uint8_t    pin, 
            uint32_t   startDelay = 0, 
            uint32_t   failsInterval = 0, 
            uint8_t    failsVariation = 0,
            NT_Pattern pattern = NT_NOPATTERN, 
            uint8_t    patternRythm = 20,
            uint8_t    *patternCustom = NULL,
            uint8_t    patternSize = 0
        );
        void initFails(
            uint32_t   failsInterval = 0, 
            uint8_t    failsVariation = 0
        );
        void initPattern(
            NT_Pattern pattern = NT_NOPATTERN, 
            uint8_t    patternRythm = 20,
            uint8_t    *patternCustom = NULL,
            uint8_t    patternSize = 0
        );

        void on();
        void off();
        void run();

    private:
        enum NT_RunStates { NT_STOP, NT_START, NT_PATTERN, NT_GLOW }; 

        NT_RunStates runState;
        uint8_t ledState;

        uint8_t pin;
        uint32_t startDelay;

        NT_Pattern pattern; 
        uint8_t patternDigital[30] = {
            1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
            1, 1, 1, 0, 0, 0, 0, 0, 1, 1,
            1, 0, 0, 0, 0, 1, 1, 1, 0, 0,
        };

        // Waste of RAM (Digispark limit 512byte)
        uint8_t patternAnalog[]; /* = {
              0,   0,  10,  20,  30,  30,  40,  50,  60,  70,
             80,  70,  70,  60,  60,  50,  50,  50,  60,  70, 
             80,  90, 100, 120, 140, 160, 240, 250, 100, 150,
            250, 250, 140, 240, 230, 220, 100,  80,  70,  70,
             70,  80,  80, 140, 130, 120, 110, 200, 210, 220,
            220, 100,  90,  40,  30,  30,  30,  20,  10,  10 
        }; */

        uint8_t patternIndex;
        uint8_t patternSize;
        uint8_t *patternPointer;
        uint8_t patternRythm;

        uint32_t failsInterval;  // average fail interval in seconds, 0=no fails
        uint8_t failsVariation; // fail variation, 0=exact, 100= up to +100%

        void runStart();
        void runPattern();
        void runGlow();
        void runStop();

        NTTimer lightTimer;
};

#endif