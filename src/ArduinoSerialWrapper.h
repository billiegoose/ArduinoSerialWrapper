/*
ArduinoSerialWrapper.h

This is based on SoftwareSerial.h. 
Obviously, some changes to .begin() had to be made since we're specifying a COM port not pins.
*/

/*
What we must implement to make the HerkuleX libraries happy.
extern SoftwareSerial SwSerial(0, 1);
SwSerial.setRX(rx);
SwSerial.setTX(tx);
SwSerial.begin(baud);
SwSerial.end();
SwSerial.write(buffer, lenght);
SwSerial.available()
byte inchar = (byte)SwSerial.read();
(byte)SwSerial.peek() == 0xFF
SwSerial.flush();
SwSerial.flush();

extern SoftwareSerial SoftSerial(0, 1);
SoftSerial.setRX(rx);
SoftSerial.setTX(tx);
SoftSerial.begin(baudrate);
SoftSerial.write(buf, size);
SoftSerial.available()
byte inchar = (byte)SoftSerial.read();
SoftSerial.flush();
*/

#ifndef ArduinoSerialWrapper_h
#define ArduinoSerialWrapper_h

//#include <inttypes.h>
#include <stdint.h>
/*#include <Stream.h>*/

// PC implementation using wjwwood's serial.
#include "serial/serial.h"
// Arduino implementation?
// #include <SoftwareSerial.h>

/******************************************************************************
* Definitions
******************************************************************************/

// We can get away with implementing a bare bones version of SoftwareSerial that 
// doesn't take advantage of the full Stream class.
class SoftwareSerial //: public Stream
{
private:
  int _TX, _RX;
  char _COM_port[128];
  int _peek_char;
  bool _peek_ongoing;
  bool _inverse_logic;
  serial::Serial _serial;
public:
  void setTX(uint8_t transmitPin);
  void setRX(uint8_t receivePin);
  void setCOM(char* com);
  void getCOM(char* com);
  // public methods
  SoftwareSerial(uint8_t receivePin = 0, uint8_t transmitPin = 1, bool inverse_logic = false);
  ~SoftwareSerial();
  void begin(long speed);
  void end(); 
  int peek(); // This might be tricky since it's not supported in wjwwood/serial

  /*virtual size_t write(uint8_t byte);*/
  size_t write(const uint8_t *b, size_t size);
  /*virtual*/ int read();
  /*virtual*/ int available();
  /*virtual*/ void flush();

  // Not used by Herkulex or HerkuleX
  /*
  bool listen(); // not used
  bool isListening() { return this == active_object; } // not used
  bool overflow() { bool ret = _buffer_overflow; _buffer_overflow = false; return ret; } // not used
  */

  /*using Print::write;*/
};

#endif
