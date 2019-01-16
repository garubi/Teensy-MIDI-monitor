/* Receive Incoming MIDI messages by reading data and print on the serial monitor
   Use the Arduino Serial Monitor to view the messages
   as Teensy receives them by USB MIDI

   You must select MIDI from the "Tools > USB Type" menu

   This example code is in the public domain.
*/

#include <MIDI.h>
// Create the Serial MIDI port
MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI1);

// A variable to know how long the LED has been turned on
elapsedMillis ledOnMillis;

void setup() {
  pinMode(13, OUTPUT); // LED pin
  digitalWrite(13, LOW);
  MIDI1.begin(MIDI_CHANNEL_OMNI);
  Serial.begin(115200);
}

void loop() {
  bool activity = false;

  if (MIDI1.read()) {
    // get a MIDI IN1 (Serial) message
    byte type = MIDI1.getType();
    byte channel = MIDI1.getChannel();
    byte data1 = MIDI1.getData1();
    byte data2 = MIDI1.getData2();

switch (type) {
    case midi::NoteOff: // 0x80
      Serial.print("Note Off // 0x80, ch=");
      Serial.print(channel, DEC);
      Serial.print(", note=");
      Serial.print(data1, DEC);
      Serial.print(", velocity=");
      Serial.println(data2, DEC);
      break;

    case midi::NoteOn: // 0x90
      Serial.print("Note On // 0x90, ch=");
      Serial.print(channel, DEC);
      Serial.print(", note=");
      Serial.print(data1, DEC);
      Serial.print(", velocity=");
      Serial.println(data2, DEC);
      break;

    case midi::AfterTouchPoly: // 0xA0
      Serial.print("AfterTouch Change // 0xA0, ch=");
      Serial.print(channel, DEC);
      Serial.print(", note=");
      Serial.print(data1, DEC);
      Serial.print(", velocity=");
      Serial.println(data2, DEC);
      break;

    case midi::ControlChange: // 0xB0
      Serial.print("Control Change // 0xB0, ch=");
      Serial.print(channel, DEC);
      Serial.print(", control=");
      Serial.print(data1, DEC);
      Serial.print(", value=");
      Serial.println(data2, DEC);
      break;

    case midi::ProgramChange: // 0xC0
      Serial.print("Program Change // 0xC0, ch=");
      Serial.print(channel, DEC);
      Serial.print(", program=");
      Serial.println(data1, DEC);
      break;

    case midi::AfterTouchChannel: // 0xD0
      Serial.print("After Touch // 0xD0, ch=");
      Serial.print(channel, DEC);
      Serial.print(", pressure=");
      Serial.println(data1, DEC);
      break;

    case midi::PitchBend: // 0xE0
      Serial.print("Pitch Change // 0xE0, ch=");
      Serial.print(channel, DEC);
      Serial.print(", pitch=");
      Serial.println(data1 + data2 * 128, DEC);
      break;

    case midi::SystemExclusive: // 0xF0
      // Messages larger than usbMIDI's internal buffer are truncated.
      // To receive large messages, you *must* use the 3-input function
      // handler.  See InputFunctionsComplete for details.
      Serial.print("SysEx Message // 0xF0: ");
      printBytes(MIDI1.getSysExArray(), data1 + data2 * 256);
      Serial.println();
      break;

    case midi::TimeCodeQuarterFrame: // 0xF1
      Serial.print("TimeCode // 0xF1, index=");
      Serial.print(data1 >> 4, DEC);
      Serial.print(", digit=");
      Serial.println(data1 & 15, DEC);
      break;

    case midi::SongPosition: // 0xF2
      Serial.print("Song Position // 0xF2, beat=");
      Serial.println(data1 + data2 * 128);
      break;

    case midi::SongSelect: // 0xF3
      Serial.print("Sond Select // 0xF3, song=");
      Serial.println(data1, DEC);
      break;

    case midi::TuneRequest: // 0xF6
      Serial.println("Tune Request // 0xF6");
      break;

    case midi::Clock: // 0xF8
      Serial.println("Clock // 0xF8");
      break;

    case midi::Start: // 0xFA
      Serial.println("Start // 0xFA");
      break;

    case midi::Continue: // 0xFB
      Serial.println("Continue // 0xFB");
      break;

    case midi::Stop: // 0xFC
      Serial.println("Stop // 0xFC");
      break;

    case midi::ActiveSensing: // 0xFE
      Serial.println("Actvice Sensing // 0xFE");
      break;

    case midi::SystemReset: // 0xFF
      Serial.println("System Reset // 0xFF");
      break;

    default:
      Serial.println("Opps, an unknown MIDI message type!");
  }
  
    activity = true;
  }


  // blink the LED when any activity has happened
  if (activity) {
    digitalWriteFast(13, HIGH); // LED on
    ledOnMillis = 0;
  }
  if (ledOnMillis > 15) {
    digitalWriteFast(13, LOW);  // LED off
  }

}


void printBytes(const byte *data, unsigned int size) {
  while (size > 0) {
    byte b = *data++;
    if (b < 16) Serial.print('0');
    Serial.print(b, HEX);
    if (size > 1) Serial.print(' ');
    size = size - 1;
  }
}
