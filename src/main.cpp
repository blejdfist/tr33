#include <Arduino.h>
#include <FastLED.h>
#include <Commands.h>
#include <Twang.h>
#include <Tr33.h>
#include <Dode.h>
#include <Keller.h>

#define SERIAL_HEADER 42
#define SERIAL_READY_TO_SEND 0xAA
#define SERIAL_CLEAR_TO_SEND 0xBB
#define SERIAL_REQUEST_RESYNC 0xCC

const uint16_t SERIAL_BUFFER_SIZE = 1024;
char serial_buffer[SERIAL_BUFFER_SIZE];
const uint8_t SERIAL_PACKET_SIZE = 2 + COMMAND_DATA_SIZE;
const uint8_t SERIAL_TIMEOUT = 100;

IPAddress artnet_ip(2, 23, 42, 24);

Commands commands;

// HardwareSerial CommandSerial(2);
HardwareSerial CommandSerial(0);

// Tr33 led_structure = Tr33();
// Dode led_structure = Dode();
Keller led_structure = Keller();

void flush_serial()
{
  while (CommandSerial.available())
  {
    // int byte = CommandSerial.read();
    // Serial.print("Flushing from serial: ");
    // Serial.println(byte);
  }
}

void setup()
{
  Serial.begin(921600);
  CommandSerial.begin(921600);
  while (!Serial || !CommandSerial)
  {
    // do nothing
  }

  CommandSerial.setTimeout(SERIAL_TIMEOUT);

  Serial.println("\n\tLED Controller\r\n");

  Serial.println("Starting up...");

  commands.init(&led_structure);

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  CommandSerial.write(SERIAL_REQUEST_RESYNC);

  // artnet.begin(artnet_ip);
  // artnet.setArtDmxCallback(led_structure.artnet_packet_callback);
  // artnet.setArtSyncCallback(commands.artnet_sync_callback);

  Serial.println("Startup complete");
}

void loop()
{
  int byte;
  int commandCount;
  int bytes_read;

  byte = CommandSerial.read();

  if (byte == SERIAL_READY_TO_SEND)
  {
    CommandSerial.write(SERIAL_CLEAR_TO_SEND);
    long cts_send_time = millis();

    while (byte != SERIAL_HEADER && millis() < cts_send_time + SERIAL_TIMEOUT)
    {
      byte = CommandSerial.read();
    }

    if (byte == SERIAL_HEADER)
    {
      commandCount = CommandSerial.read();

      for (int i = 0; i < commandCount; i++)
      {
        bytes_read = CommandSerial.readBytes(serial_buffer, SERIAL_PACKET_SIZE);
        if (bytes_read == SERIAL_PACKET_SIZE)
        {
          commands.process((char *)serial_buffer);
        }
        else
        {
          Serial.print("Incomplete message, bytes read: ");
          Serial.println(bytes_read);
        }
      }
    }
    else
    {
      // Serial.print("Expected header, got: ");
      // Serial.println(byte);
    }
  }
  else if (byte != -1)
  {
    // Serial.print("Expected RTS, got: ");
    // Serial.println(byte);
    flush_serial();
    CommandSerial.write(SERIAL_REQUEST_RESYNC);
  }

  commands.run();
}
