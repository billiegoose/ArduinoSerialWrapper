/*
ArduinoSerialWrapper.cpp

A pseudo-implementation of Arduino's SoftwareSerial using wjwwood's serial library for PCs.
*/

#include "ArduinoSerialWrapper.h"

//
// Constructor
//
SoftwareSerial::SoftwareSerial(uint8_t receivePin, uint8_t transmitPin, bool inverse_logic /* = false */) : 
  _inverse_logic(inverse_logic)
{
  _peek_ongoing = 0;
  //&_serial = new serial::Serial();
  setTX(transmitPin);
  setRX(receivePin);
}

//
// Destructor
//
SoftwareSerial::~SoftwareSerial()
{
  end();
}

//
// Public methods
//

void SoftwareSerial::setTX(uint8_t tx)
{
  _TX = tx;
}

void SoftwareSerial::setRX(uint8_t rx)
{
  _RX = rx;
}

void SoftwareSerial::setCOM(char* com)
{
  // Set port
  std::string str_com(com);
  _serial.setPort(str_com);
}

void SoftwareSerial::getCOM(char* com)
{
  // Get port
  std::string str_com;
  str_com = _serial.getPort();
  strcpy(com, str_com.c_str());
}

void SoftwareSerial::begin(long speed)
{
  _serial.setBaudrate(speed);
  _serial.open();
}

void SoftwareSerial::end()
{
  _serial.close();
}

// Read a byte from the buffer
int SoftwareSerial::read()
{
  _peek_ongoing = 0;
  uint8_t buffer[1];
  size_t bytes_read = 0;
  try {
    bytes_read = _serial.read(buffer, 1);
    if (bytes_read != 1) throw bytes_read;
  } catch (...) {
    return -1;
  }
  return buffer[0];
}

int SoftwareSerial::available()
{
  return _serial.available() + _peek_ongoing;
}

size_t SoftwareSerial::write(const uint8_t *buffer, size_t size)
{
  return _serial.write(buffer, size);
}

void SoftwareSerial::flush()
{
  _serial.flush();
}

int SoftwareSerial::peek()
{
  if (!_peek_ongoing) {
    _peek_char = read();
    _peek_ongoing = 1;
  }
  return _peek_char;
}
