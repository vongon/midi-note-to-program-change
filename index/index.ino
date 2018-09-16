
// MIDI NOTE TO PROGRAM CHANGE CONVERTER
// Designed for 12step -> Digitakt compatbility, change patterns via 12step

byte PROGRAM_CHANGE_COMMAND = 0xCD; // sending to channel 14
byte noteOnCommands[] = {0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9A, 0x9B, 0x9C, 0x9D, 0x9E, 0x9F};
int noteOnCommandsLength = 16;
byte commandByte;
byte noteByte;
byte velocityByte;


void setup() {
  Serial.begin(31250);
}

bool isNoteOnCommand(byte commandInput) {
  bool result = false;
  for (int i=0; i < noteOnCommandsLength; i++) {
    if (commandInput == noteOnCommands[i]) {
      result = true;
    }
  }
  return result;
}

void loop() {
  if(Serial.available() > 2) { // at least 3 messages in buffer (note on, note, velocity) 
    commandByte = Serial.read();
    noteByte = Serial.read();
    velocityByte = Serial.read();
    if (isNoteOnCommand(commandByte)) {
      Serial.write(PROGRAM_CHANGE_COMMAND);
      Serial.write(noteByte);
    }
  }
}
