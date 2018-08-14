# HolyDio

Fastest and cleanest possible digital IO manipulation functions for
*duino SBCs.

The libray is implemented _header-only_. I find that desirable!

There are several benefits of HolyDio compared to "fastDigitalWrite" and
other similar libraries:

- HolyDio does _not_ use polluting and dangerous macros. Instead it uses
  lex- and type-safe _constexpr functions_ and _templating_ (C++11/14).
- HolyDio composes multiple writes into one single register write
  automatically _where possible_! If you connect, say a stepper motor,
  on pins that _reside on the same hardware port_.
   - This gives us _one_, _timing synced_, operation totalling about
     _200 ns_ — in contrast to doing four individual writes totalling
     around 24,000 ns (!) with the standard arduino slowmo-lib.
   - Yes! It would take _a hundred arduinos' combined processing power_
     to get the same performance using stdlib functions! Suck on that.

## Name
- Digital Input Output, and the rest obviously is a word play on the
  awesome 80's hit song / album.

## Usage
- Add the lib to you project with: `glue add HolyDio` - or some other
  way (see "Installation")
- Include the library in you source: `#include <HolyDio.h>`

## Performance

*TODO* profile for composite-set etc..

Stdlib `digitalWrite` on Arduino Uno 16MHz   => **6280 ns**
HolyDio `dioWrite`                           => **125 ns**.

## Why make things fast fast?

- Your application might require it to meet a sufficient update rate
- Less wasted cycles is less wasted watts.
   - For a battery appliance, for instance, putting the SBC into low
     power sleep mode as soon, long and often as possible is desirable.
- The less energy we waste on earth, the more sustainable our future is.
- Making something _absolutely fastest_ while being _absolutely super
  simple_ to use is _awesome coolest_ in my book (Yes, I do suffer
  iheavily from optimization syndrome — growing up with q <= 1MHz 8-bit
  machines).

## Supported Hardware
- Arduino Due
- Arduino Zero
- Arduino Mega
- Arduino with ATmega644 or Atmega644P chip
- Arduino Leonardo
- Arduino Uno

If your SBC is not in the list, it will fail with a compile time error.
Extending the library is very simple, so please take a stab at it and
PR - I've littered the source code with comments, so it's a good
exercise for the keen coder.

## Installation
- Use `glue` package manager in your proj dir: `glue add HolyDio`
- Or simply `git clone` the repo in to your projects deps dir (if using build scripts - you should ;-) )
- Or `git clone` into arduino central libraries dir, if you use that hideous coding environment!

## Reference
I've used arduino-stdlib/hardware/*/pins.h and Watterott's monolith bundle https://github.com/watterott/Arduino-Libs/tree/master/digitalWriteFast
as references for pin-numbering and address-mapping.

