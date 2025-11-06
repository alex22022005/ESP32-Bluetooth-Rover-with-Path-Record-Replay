#include <BluetoothSerial.h>
BluetoothSerial SerialBT;

struct PathPoint {
  char direction;
  unsigned long duration;
};

PathPoint path[100];
int pathIndex = 0;
bool recording = false;
unsigned long moveStart = 0;
char lastDirection;

#define IN1 5
#define IN2 18
#define IN3 19
#define IN4 21

void setup() {
  Serial.begin(115200);
  SerialBT.begin("Rover");
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void loop() {
  if (SerialBT.available()) {
    char cmd = SerialBT.read();

    if (cmd == 'S') { // START
      pathIndex = 0;
      recording = true;
      SerialBT.println("Recording Started");
    } else if (cmd == 'X') { // FINISH
      recording = false;
      SerialBT.println("Recording Finished");
    } else if (cmd == 'F' || cmd == 'B' || cmd == 'L' || cmd == 'R') {
      move(cmd);
    } else if (cmd == 'A') { // AUTONOMOUS
      replayPath();
    }
  }

  // Stop recording after 1s (example)
  if (recording && millis() - moveStart > 1000 && lastDirection != '\0') {
    path[pathIndex++] = {lastDirection, 1000};
    stopMotors();
    lastDirection = '\0';
  }
}

void move(char dir) {
  if (recording) {
    moveStart = millis();
    lastDirection = dir;
  }

  switch (dir) {
    case 'F': forward(); break;
    case 'B': backward(); break;
    case 'L': left(); break;
    case 'R': right(); break;
  }
}

void forward() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
}

void backward() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
}

void left() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
}

void right() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
}

void stopMotors() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
}

void replayPath() {
  SerialBT.println("Autonomous Mode");
  for (int i = 0; i < pathIndex; i++) {
    move(path[i].direction);
    delay(path[i].duration);
    stopMotors();
    delay(300);
  }
}
