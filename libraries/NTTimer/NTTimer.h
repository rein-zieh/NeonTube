/*
 * NTTimer.h 
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

#ifndef NTTimer_h
#define NTTimer_h

#include "Arduino.h"

class NTTimer;
typedef void (*timerEventHandler)(NTTimer&);

class NTTimer
{
    public:
        NTTimer(uint32_t duration = 0, timerEventHandler handler = NULL);
        
        void set(uint32_t duration = 0, timerEventHandler handler = NULL);
        void setHandler(timerEventHandler handler = NULL);

        boolean check();
        boolean checkAndRepeat();
        boolean checkAndSet(uint32_t duration);
      
        void run();

    private:
        uint32_t duration;
        uint32_t last;

        timerEventHandler handler;
};

#endif