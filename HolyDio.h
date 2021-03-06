/*
   Optimized digital functions for AVR microcontrollers
   by Watterott electronic (www.watterott.com)
   based on http://code.google.com/p/digitalwritefast
 */

#ifndef FASTDIO_H
#define FASTDIO_H

#define ERROR_SEQUENCE 0b10101010 //dioRead will return this value if pin number is not constant
// general macros/defines
#ifndef BIT_READ
# define BIT_READ(value, bit)                  ((value) &    (1U << (bit)))
#endif
#ifndef BIT_SET
# define BIT_SET(value, bit)                   ((value) |=   (1U << (bit)))
#endif
#ifndef BIT_CLEAR
# define BIT_CLEAR(value, bit)                ((value) &= ~(1U << (bit)))
#endif
#ifndef BIT_WRITE
# define BIT_WRITE(value, bit, bitvalue) (bitvalue ? BIT_SET(value, bit) : BIT_CLEAR(value, bit))
#endif


// digital functions
//#ifndef digitalPinToPortReg
#define SPI_SW_SS_PIN    (10) //SS on Uno (for software SPI)
#define SPI_SW_MOSI_PIN (11) //MOSI on Uno (for software SPI)
#define SPI_SW_MISO_PIN (12) //MISO on Uno (for software SPI)
#define SPI_SW_SCK_PIN   (13) //SCK on Uno (for software SPI)


// --- Arduino Due ---
#if (defined(ARDUINO_SAM_DUE) || defined(__SAM3X8E__))

   #define UART_RX_PIN       (0)
   #define UART_TX_PIN       (1)

   #define I2C_SDA_PIN       (20)
   #define I2C_SCL_PIN       (21)

   #define SPI_HW_SS_PIN    (78) //SS0:77, SS1:87, SS2:86, SS3:78
   #define SPI_HW_MOSI_PIN (75) //75
   #define SPI_HW_MISO_PIN (74) //74
   #define SPI_HW_SCK_PIN   (76) //76


// --- Arduino Zero ---
#elif (defined(ARDUINO_SAM_ZERO) || defined(__SAMD21G18A__))

   #define UART_RX_PIN       (0)
   #define UART_TX_PIN       (1)

   #define I2C_SDA_PIN       (16)
   #define I2C_SCL_PIN       (17)

   #define SPI_HW_SS_PIN    (14) //14
   #define SPI_HW_MOSI_PIN (21) //21
   #define SPI_HW_MISO_PIN (18) //18
   #define SPI_HW_SCK_PIN   (20) //20


// --- Arduino Mega ---
#elif (defined(ARDUINO_AVR_MEGA) || \
          defined(ARDUINO_AVR_MEGA1280) || \
          defined(ARDUINO_AVR_MEGA2560) || \
          defined(__AVR_ATmega1280__) || \
          defined(__AVR_ATmega1281__) || \
          defined(__AVR_ATmega2560__) || \
          defined(__AVR_ATmega2561__))

#define UART_RX_PIN       (0) //PE0
#define UART_TX_PIN       (1) //PE1

#define I2C_SDA_PIN       (20)
#define I2C_SCL_PIN       (21)

#define SPI_HW_SS_PIN    (53) //PB0
#define SPI_HW_MOSI_PIN (51) //PB2
   #define SPI_HW_MISO_PIN (50) //PB3
   #define SPI_HW_SCK_PIN   (52) //PB1

   template <typename T>
   constexpr volatile U8* __digitalPinToPortReg(const T P) {
      return (((P) >= 22 && (P) <= 29) ? &PORTA : \
            ((((P) >= 10 && (P) <= 13) || ((P) >= 50 && (P) <= 53)) ? &PORTB : \
            (((P) >= 30 && (P) <= 37) ? &PORTC : \
            ((((P) >= 18 && (P) <= 21) || (P) == 38) ? &PORTD : \
            (((/* (P) >= 0 && --[must be true]-- */ (P) <= 3) || (P) == 5) ? &PORTE : \
            (((P) >= 54 && (P) <= 61) ? &PORTF : \
            ((((P) >= 39 && (P) <= 41) || (P) == 4) ? &PORTG : \
            ((((P) >= 6 && (P) <= 9) || (P) == 16 || (P) == 17) ? &PORTH : \
            (((P) == 14 || (P) == 15) ? &PORTJ : \
            (((P) >= 62 && (P) <= 69) ? &PORTK : &PORTL))))))))));
   }

   constexpr volatile U8* __digitalPinToDDRReg(const U8 P) {
      return (((P) >= 22 && (P) <= 29) ? &DDRA : \
            ((((P) >= 10 && (P) <= 13) || ((P) >= 50 && (P) <= 53)) ? &DDRB : \
            (((P) >= 30 && (P) <= 37) ? &DDRC : \
            ((((P) >= 18 && (P) <= 21) || (P) == 38) ? &DDRD : \
            (((/* (P) >= 0 && --[must be true]-- */ (P) <= 3) || (P) == 5) ? &DDRE : \
            (((P) >= 54 && (P) <= 61) ? &DDRF : \
            ((((P) >= 39 && (P) <= 41) || (P) == 4) ? &DDRG : \
            ((((P) >= 6 && (P) <= 9) || (P) == 16 || (P) == 17) ? &DDRH : \
            (((P) == 14 || (P) == 15) ? &DDRJ : \
            (((P) >= 62 && (P) <= 69) ? &DDRK : &DDRL))))))))));
   }

   #define __digitalPinToPINReg(P) \
   (((P) >= 22 && (P) <= 29) ? &PINA : \
   ((((P) >= 10 && (P) <= 13) || ((P) >= 50 && (P) <= 53)) ? &PINB : \
   (((P) >= 30 && (P) <= 37) ? &PINC : \
   ((((P) >= 18 && (P) <= 21) || (P) == 38) ? &PIND : \
   ((((P) >= 0 && (P) <= 3) || (P) == 5) ? &PINE : \
   (((P) >= 54 && (P) <= 61) ? &PINF : \
   ((((P) >= 39 && (P) <= 41) || (P) == 4) ? &PING : \
   ((((P) >= 6 && (P) <= 9) || (P) == 16 || (P) == 17) ? &PINH : \
   (((P) == 14 || (P) == 15) ? &PINJ : \
   (((P) >= 62 && (P) <= 69) ? &PINK : &PINL))))))))))

   #define __digitalPinToBit(P) \
   (((P) >=   7 && (P) <=   9) ? (P) - 3 : \
   (((P) >= 10 && (P) <= 13) ? (P) - 6 : \
   (((P) >= 22 && (P) <= 29) ? (P) - 22 : \
   (((P) >= 30 && (P) <= 37) ? 37 - (P) : \
   (((P) >= 39 && (P) <= 41) ? 41 - (P) : \
   (((P) >= 42 && (P) <= 49) ? 49 - (P) : \
   (((P) >= 50 && (P) <= 53) ? 53 - (P) : \
   (((P) >= 54 && (P) <= 61) ? (P) - 54 : \
   (((P) >= 62 && (P) <= 69) ? (P) - 62 : \
   (((P) == 0 || (P) == 15 || (P) == 17 || (P) == 21) ? 0 : \
   (((P) == 1 || (P) == 14 || (P) == 16 || (P) == 20) ? 1 : \
   (((P) == 19) ? 2 : \
   (((P) == 5 || (P) == 6 || (P) == 18) ? 3 : \
   (((P) == 2) ? 4 : \
   (((P) == 3 || (P) == 4) ? 5 : 7)))))))))))))))


// --- Arduino 644 ---
#elif (defined(__AVR_ATmega644__) || \
          defined(__AVR_ATmega644P__))

   #define UART_RX_PIN       (8) //PD0
   #define UART_TX_PIN       (9) //PD1

   #define I2C_SDA_PIN       (17) //PC1
   #define I2C_SCL_PIN       (16) //PC0

   #define SPI_HW_SS_PIN    (4) //PB4
   #define SPI_HW_MOSI_PIN (5) //PB5
   #define SPI_HW_MISO_PIN (6) //PB6
   #define SPI_HW_SCK_PIN   (7) //PB7

   #define __digitalPinToPortReg(P) \
   (((P) >= 0 && (P) <= 7) ? &PORTB : (((P) >= 8 && (P) <= 15) ? &PORTD : (((P) >= 16 && (P) <= 23) ? &PORTC : &PORTA)))
   #define __digitalPinToDDRReg(P) \
   (((P) >= 0 && (P) <= 7) ? &DDRB : (((P) >= 8 && (P) <= 15) ? &DDRD : (((P) >= 8 && (P) <= 15) ? &DDRC : &DDRA)))
   #define __digitalPinToPINReg(P) \
   (((P) >= 0 && (P) <= 7) ? &PINB : (((P) >= 8 && (P) <= 15) ? &PIND : (((P) >= 8 && (P) <= 15) ? &PINC : &PINA)))
   #define __digitalPinToBit(P) \
   (((P) >= 0 && (P) <= 7) ? (P) : (((P) >= 8 && (P) <= 15) ? (P) - 8 : (((P) >= 16 && (P) <= 23) ? (P) - 16 : (P) - 24)))


// --- Arduino Leonardo ---
#elif (defined(ARDUINO_AVR_LEONARDO) || \
          defined(__AVR_ATmega16U4__) || \
          defined(__AVR_ATmega32U4__))

   #define UART_RX_PIN       (0) //PD2
   #define UART_TX_PIN       (1) //PD3

   #define I2C_SDA_PIN       (2) //PD1
   #define I2C_SCL_PIN       (3) //PD0

   #define SPI_HW_SS_PIN    (17) //PB0
   #define SPI_HW_MOSI_PIN (16) //PB2
   #define SPI_HW_MISO_PIN (14) //PB3
   #define SPI_HW_SCK_PIN   (15) //PB1

   #define __digitalPinToPortReg(P) \
   ((((P) >= 0 && (P) <= 4) || (P) == 6 || (P) == 12 || (P) == 24 || (P) == 25 || (P) == 29) ? &PORTD : (((P) == 5 || (P) == 13) ? &PORTC : (((P) >= 18 && (P) <= 23)) ? &PORTF : (((P) == 7) ? &PORTE : &PORTB)))
   #define __digitalPinToDDRReg(P) \
   ((((P) >= 0 && (P) <= 4) || (P) == 6 || (P) == 12 || (P) == 24 || (P) == 25 || (P) == 29) ? &DDRD : (((P) == 5 || (P) == 13) ? &DDRC : (((P) >= 18 && (P) <= 23)) ? &DDRF : (((P) == 7) ? &DDRE : &DDRB)))
   #define __digitalPinToPINReg(P) \
   ((((P) >= 0 && (P) <= 4) || (P) == 6 || (P) == 12 || (P) == 24 || (P) == 25 || (P) == 29) ? &PIND : (((P) == 5 || (P) == 13) ? &PINC : (((P) >= 18 && (P) <= 23)) ? &PINF : (((P) == 7) ? &PINE : &PINB)))
   #define __digitalPinToBit(P) \
   (((P) >= 8 && (P) <= 11) ? (P) - 4 : (((P) >= 18 && (P) <= 21) ? 25 - (P) : (((P) == 0) ? 2 : (((P) == 1) ? 3 : (((P) == 2) ? 1 : (((P) == 3) ? 0 : (((P) == 4) ? 4 : (((P) == 6) ? 7 : (((P) == 13) ? 7 : (((P) == 14) ? 3 : (((P) == 15) ? 1 : (((P) == 16) ? 2 : (((P) == 17) ? 0 : (((P) == 22) ? 1 : (((P) == 23) ? 0 : (((P) == 24) ? 4 : (((P) == 25) ? 7 : (((P) == 26) ? 4 : (((P) == 27) ? 5 : 6 )))))))))))))))))))


// --- Arduino Uno ---
#elif (defined(ARDUINO_AVR_UNO) || \
          defined(ARDUINO_AVR_DUEMILANOVE) || \
          defined(ARDUINO_ARCH_AVR) || \
          defined(__AVR_ATmega328__) || \
          defined(__AVR_ATmega328P__) || \
          defined(__AVR__))

   #define UART_RX_PIN       (0) //PD0
   #define UART_TX_PIN       (1) //PD1

   #define I2C_SDA_PIN       (18) //A4
   #define I2C_SCL_PIN       (19) //A5

   #define SPI_HW_SS_PIN    (10) //PB0
   #define SPI_HW_MOSI_PIN (11) //PB2
   #define SPI_HW_MISO_PIN (12) //PB3
   #define SPI_HW_SCK_PIN   (13) //PB1

   #define __digitalPinToPortReg(P) \
   (((P) >= 0 && (P) <= 7) ? &PORTD : (((P) >= 8 && (P) <= 13) ? &PORTB : &PORTC))
   #define __digitalPinToDDRReg(P) \
   (((P) >= 0 && (P) <= 7) ? &DDRD : (((P) >= 8 && (P) <= 13) ? &DDRB : &DDRC))
   #define __digitalPinToPINReg(P) \
   (((P) >= 0 && (P) <= 7) ? &PIND : (((P) >= 8 && (P) <= 13) ? &PINB : &PINC))
   #define __digitalPinToBit(P) \
   (((P) >= 0 && (P) <= 7) ? (P) : (((P) >= 8 && (P) <= 13) ? (P) - 8 : (P) - 14))


// --- Other ---
#else

   #define SPI_HW_SS_PIN    SS
   #define SPI_HW_MOSI_PIN MOSI
   #define SPI_HW_MISO_PIN MISO
   #define SPI_HW_SCK_PIN   SCK


#endif
//#endif   //#ifndef digitalPinToPortReg


//ref: http://forum.arduino.cc/index.php?topic=140409.msg1054868#msg1054868
//void OutputsErrorIfCalled( void ) __attribute__ (( error( "Line: "__line__ "Variable used for dioWrite") ));
void NonConstantUsed( void )   __attribute__ (( error("") ));


#if (defined(__AVR__) || defined(ARDUINO_ARCH_AVR))

   /* #define dioWrite(P, V) \ */
   /* if (true) { \ */
   /*    BIT_WRITE(*__digitalPinToPortReg(P), __digitalPinToBit(P), (V)); \ */
   /* } else { \ */
   /*    NonConstantUsed(); \ */
   /* } */

   // One pin write
   template <U8 P, typename T>
   inline fn dioWrite(T V) -> Void {
      BIT_WRITE(*__digitalPinToPortReg(P), __digitalPinToBit(P), (V)); \
   }

   template <typename T>
   constexpr fn pToBits(T P1) -> U8 {
      return 1UL << __digitalPinToBit(P1);
   }

   // 4 pin write, same value
   template <U8 P1, U8 P2, U8 P3, U8 P4, typename T>
   inline fn dioWrite(T V) -> Void {
      if (__digitalPinToPortReg(P1) == __digitalPinToPortReg(P2) &&
          __digitalPinToPortReg(P2) == __digitalPinToPortReg(P3) &&
          __digitalPinToPortReg(P3) == __digitalPinToPortReg(P4)
      ) {
         constexpr auto port = __digitalPinToPortReg(P1);
         constexpr auto pattern = pToBits(P1) | pToBits(P2) | pToBits(P3) | pToBits(P4);
         if (V) {
            *port |= pattern;
         } else {
            *port &= ~pattern;
         }
      } else {
         dioWrite<P1>(V);
         dioWrite<P2>(V);
         dioWrite<P3>(V);
         dioWrite<P4>(V);
      }
   }

   // 4 pin write, different values
   template <U8 P1, U8 P2, U8 P3, U8 P4, typename T>
   inline fn dioWrite(T v1, T v2, T v3, T v4) -> Void {
      if (__digitalPinToPortReg(P1) == __digitalPinToPortReg(P2) &&
          __digitalPinToPortReg(P2) == __digitalPinToPortReg(P3) &&
          __digitalPinToPortReg(P3) == __digitalPinToPortReg(P4)
      ) {
         constexpr auto port = __digitalPinToPortReg(P1);
         auto pattern_hi = ((v1 ? pToBits(P1) : 0) | (v2 ? pToBits(P2) : 0) | (v3 ? pToBits(P3) : 0) | (v4 ? pToBits(P4) : 0));
         auto pattern_lo = ~((!v1 ? pToBits(P1) : 0) | (!v2 ? pToBits(P2) : 0) | (!v3 ? pToBits(P3) : 0) | (!v4 ? pToBits(P4) : 0));
         *port = (*port | pattern_hi) & pattern_lo;

      } else {
         dioWrite<P1>(v1);
         dioWrite<P2>(v2);
         dioWrite<P3>(v3);
         dioWrite<P4>(v4);
      }
   }

   /*/ This overload of @fn takes pin as an argument instead of template
      parametrization. This means that it will be more lenient:
      - If it's called with pin being a constant expression, it will result in
      highly optimized code, but if it's called with a variable expression, it will
      do the conversion from pin to port+bits at runtime.
      - If you wish to ensure that your program has a true constexpr path then
      use the slightly uglier templated version.
   **/
   template <typename T1, typename T2>
   inline fn dioWrite(const T1 Pin, T2 V) -> Void {
      BIT_WRITE(*__digitalPinToPortReg(Pin), __digitalPinToBit(Pin), (V)); \
   }

#else
   //#define dioWrite digitalWrite
   #error Unsupported hardware.
#endif


#if (defined(__AVR__) || defined(ARDUINO_ARCH_AVR))
   template <PinNumber PIN, typename T>
   cxp fn dioPinMode(const T val) -> Void {
      BIT_WRITE(*__digitalPinToDDRReg(PIN), __digitalPinToBit(PIN), (val));
   }

#else
   //#define pinModeFast pinMode
   #error Unsupported hardware.
#endif


#if (defined(__AVR__) || defined(ARDUINO_ARCH_AVR))
   template <U8 PIN>
   inline fn dioRead() -> PinState {
      return PinState(BIT_READ(*__digitalPinToPINReg(PIN), __digitalPinToBit(PIN)));
   }

#else
   //#define dioRead digitalRead
   #error Unsupported hardware.
#endif

#endif //FASTDIO_H
