/*
 * NTTimer.cpp
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
 * CAlso add information on how to contact you by electronic and paper mail.
 *
 * Neon Tube Copyright (C) 2018 Frank Reins (github@rein-zieh.de)
 *
 * This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
 * This is free software, and you are welcome to redistribute it
 * under certain conditions; type `show c' for details.
 */

#include "Arduino.h"
#include "NTTimer.h"

NTTimer::NTTimer(uint32_t duration, timerEventHandler handler)
{
  set(duration);
  setHandler(handler);
}

void NTTimer::set(uint32_t duration, timerEventHandler handler) {
  this->duration = duration;
  last = millis();
  if (handler) this->handler = handler;
}

void NTTimer::setHandler(timerEventHandler handler) {
  this->handler = handler;
}

boolean NTTimer::check() {
  return (millis() - last >= duration);
}

boolean NTTimer::checkAndRepeat() {
  if (millis() - last < duration) {
    return false;
  }
  last = millis();
  return true;  
}

boolean NTTimer::checkAndSet(uint32_t duration = 0) {
  if (millis() - last < this->duration) {
    return false;
  }
  last = millis();
  this->duration = duration;
  return true;  
}

void NTTimer::run() {
  if (handler && checkAndRepeat()) {
      handler(*this);
  }
}
