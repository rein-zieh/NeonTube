# NeonTube
Ein einfaches Arduino-Bibliothek (Toolkit) zur Simulation von Neonröhren mittels Leuchtdioden im Modell.

## Version 1.0

Mittels der NeonTube-Bibliothek lässt sich das typische Verhalten von Neonröhren im Modellbau simulieren:
- Unterschiedliche Einschaltverzögerungen
- Flackern alter Neonröhren während des Starts
- unwirkürliche kurze Aussetzer während des Betriebs

Die Bibliothek wurde auf einem Digispark Mini mit ATtiny85 Mikrocontroller (z.B.: https://tinyurl.com/y6u2h2o6) 
entwickelt und getestet.

## Anleitung

### Variablen

Im Variablen-Bereich des Sketch können Instanzen der NeonTube-Klasse erzeugt werden:

```C++
NeonTube tube1;
```

### Initialisieren / Setup

Initialisiert und parametrisiert werden die LEDs in der `setup()`-Funktion des Sketch. Bei der Initialisierung 
muss zumindest der Anschluss-Pin zugeordnet werden.

#### Funktion `init`

Rückgabe: -
Parameter:
- `uint8_t pin`: Pin-Id
- `uint32_t startDelay`: Startverzögerung in Milli-Sekunden

**Beispiele:**

Neonröhre an Pin 1:

```C++
tube1.init(1);
```

Neonröhre an Pin 0, Einschaltverzögerung 1 Sekunde:

```C++
tube1.init(1, 1000);
```

Neonröhre an Pin 0, Einschaltverzögerung zufällig zwischen 0,5 und 2 Sekunden:

```C++
tube1.init(1, random(500,2000));
```


### Funktionen zur Laufzeit


## License
Please check the file LICENSE.md for the details.

I appreciate if you give credits when appropriate, and if you want to donate, please donate to the linked Children Hospice Charity: http://www.akhd-luenen.de

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

## Warranty
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

Regards, Frank
