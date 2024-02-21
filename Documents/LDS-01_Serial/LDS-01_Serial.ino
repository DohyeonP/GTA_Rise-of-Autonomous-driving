int Ready = 0;
void setup() {
  Serial.begin(230400);
  Serial1.begin(230400);
  Serial1.write('b');//begin /  serial monitor: 'e' will stop the motor
}
void loop() {
  byte Frame [2520];
  byte Sync[2];
  if (Serial.available()) {
    Serial1.write(Serial.read());
  }

  //First capture the start byte of a frame:
  if (Serial1.available()) {
    Sync[0] = Serial1.read();
    if (Sync[0] == 0xFA) {
      while (!Serial1.available()) {
        Serial1.write(Serial.read());
      }
      Sync[1] = Serial1.read();
    }
  }
  //Once start byte captured, read remaining frame into array:
  if (Sync[0] == 0xFA && Sync [1] == 0xA0) {
    Frame[0] = 0xFA;
    Frame[1] = 0xA0;
    for (int v = 2; v < 2520; v++) {
      while (!Serial1.available()) {
        Serial1.write(Serial.read());
      }
      Frame[v] = Serial1.read();
    }
    Ready = 1;
  }
  //Once frame captured, extract range/angle and convert to x/y:
  //
  if (Ready == 1) {
    for (int i = 0; i < 2520; i = i + 42) {
      if (Frame[i] == 0xFA && Frame[i + 1] == 0xA0 + (i / 42)) {
        for (int j = i + 4; j < i + 40; j = j + 6) {
          int rangeA = Frame[j + 2];
          int rangeB = Frame[j + 3];
          int Degrees = 6 * (i / 42) + (j - 4 - i) / 6;
          int range = (rangeB << 8) + rangeA;

          if (Degrees != 0 && range != 0) {
            // Calculate distance based on angle and output
            float distance = abs(range * cos(Degrees * PI / 180));
            if(distance < 300)
            {
              Serial.print(Degrees);
              Serial.print(",");
              Serial.println(distance);  
            }
          }
        }
      }
    }
/*
    for (int i = 0; i < 2520; i = i + 42) {
      if (Frame[i] == 0xFA && Frame[i + 1] == 0xA0 + (i / 42))//sync를 위한 FA바이트거나, 0~60도 사이의 angle index라면
      {// 그 뒤 데이터들을 데이터로 보고 해석을 시작하겠다.
        for (int j = i + 4; j < i + 40; j = j + 6) //RPM 정보는  필요없으니 버리고 Angle만 체크하겠다는거임.
        {
          int rangeA = Frame[j + 2];
          int rangeB = Frame[j + 3];
          int Degrees = 6 * (i / 42) + (j - 4 - i) / 6;
          int range = (rangeB << 8) + rangeA;
          if (Degrees != 0 && range != 0) {
            float Radians = (Degrees * PI) / 180;
            float x = range * cos(Radians);
            float y = range * sin(Radians);
            Serial.print(x);
            Serial.print(",");
            Serial.println(y);
          }
        }
      }
    }
  */
    Ready = 0;
  }
  else {
    Sync[0] = 0;
    Sync[1] = 0;
  }
}