/*
 * NeonTube.h
 *
 * Neon Tube - V 0.2 (Proof of concept)
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


class NeonTube
{
    public:

        NeonTube();

        void reset();

        void init(
            uint8_t pin, 
            uint32_t startDelay = 0
        );
        void setFails(
            uint32_t failsInterval = 0, 
            uint8_t failsVariation = 0
        );
        void setDigitalPattern(
            const uint8_t *patternCustom,
            uint8_t patternSize = 0,
            uint8_t patternRythm = 20
        );
        void setAnalogPattern(
            const uint8_t *patternCustom,
            uint8_t patternSize = 0,
            uint8_t patternRythm = 20
        );

        void on();
        void off();
        void run();

    private:
        enum NT_RunStates { NT_STOP, NT_START, NT_PATTERN, NT_GLOW }; 
        enum NT_Pattern { NT_NOPATTERN, NT_DIGITALPATTERN, NT_ANALOGPATTERN }; 

        NT_RunStates runState;
        uint8_t ledState;

        uint8_t pin;
        uint32_t startDelay;

        NT_Pattern pattern; 

        uint8_t patternIndex;
        uint8_t patternSize;
        const uint8_t *patternPointer;
        uint8_t patternRythm;

        uint32_t failsInterval;  // average fail interval in seconds, 0=no fails
        uint8_t failsVariation; // fail variation, 0=exact, 100= up to +100%

        void runStart();
        void runPattern();
        void runGlow();
        void runStop();

        NTTimer lightTimer;

        static const uint8_t myDigital[];
};

#endif