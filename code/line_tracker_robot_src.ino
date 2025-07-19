#define in1 8 // input 1 for motor "A"
#define in2 9 // input 2 for motor "A"
#define enA 10 // ENABLE A (control the motor "A" speed)

#define in3 6 // input 1 for motor "B"
#define in4 7 // input 2 for motor "B"
#define enB 5 // ENABLE B (control the motor "B" speed)

#define WHITE 1
#define BLACK 0

int direction = 0;

int MA_Speed = 90; // السرعة للمحرك الأول
int MB_Speed = 100; // السرعة للمحرك الثاني
int MA_Turn_Speed = 90; // السرعة للمحرك الأول
int MB_Turn_Speed = 100; // السرعة للمحرك الثاني

void setup() {
  Serial.begin(9600);

  // motor "A"
  pinMode(in1, OUTPUT); // input 1 for motor "A"
  pinMode(in2, OUTPUT); // input 2 for motor "A"
  pinMode(enA, OUTPUT); // ENABLE A (control the motor "A" speed)
  // motor "B"
  pinMode(in3, OUTPUT); // input 1 for motor "B"
  pinMode(in4, OUTPUT); // input 2 for motor "B"
  pinMode(enB, OUTPUT); // ENABLE B (control the motor "B" speed)

  pinMode(2, OUTPUT);
  
  // السناسر
  pinMode(11, INPUT); // left sensor
  pinMode(4, INPUT); // right sensor
  pinMode(13, INPUT); // center sensor
}

void loop() {
  if (Serial.available() > 0) {
    char value = Serial.read();
    Serial.println(value);
      if (value == 'F')
        forward();
      else if (value == 'B')
        back();
      else if (value == 'S')
        stop();
      else if (value == 'L')
        left();
      else if (value == 'R')
        right();
      else if (value == 'M') 
      {
        while(true){
            int LEFT_SENSOR = digitalRead(11);
            int RIGHT_SENSOR = digitalRead(4);
            int CENTER_SENSOR = digitalRead(13);
            if (LEFT_SENSOR == BLACK && RIGHT_SENSOR == BLACK && CENTER_SENSOR == BLACK)
              forward();
            else if (LEFT_SENSOR == BLACK && CENTER_SENSOR == BLACK && RIGHT_SENSOR == WHITE)
              left();
            else if (LEFT_SENSOR == BLACK && CENTER_SENSOR == WHITE && RIGHT_SENSOR == BLACK)
              stop();
            else if (LEFT_SENSOR == BLACK && CENTER_SENSOR == WHITE && RIGHT_SENSOR == WHITE)
              left();
            else if (LEFT_SENSOR == WHITE && CENTER_SENSOR == BLACK && RIGHT_SENSOR == BLACK)
              right();
            else if (LEFT_SENSOR == WHITE && CENTER_SENSOR == BLACK && RIGHT_SENSOR == WHITE)
              forward();
            else if (LEFT_SENSOR == WHITE && CENTER_SENSOR == WHITE && RIGHT_SENSOR == BLACK)
              right();
            else if (LEFT_SENSOR == WHITE && CENTER_SENSOR == WHITE && RIGHT_SENSOR == WHITE)
              stop();
            else
              stop();
            if (Serial.available() > 0) {
              char value2 = Serial.read();
              Serial.println(value2);
              if (value2 == 'm') {
                stop();
                break;
              }
            }
        }
      } 
      else if (value == 'N')
        buzz();
  }
}

void buzz() {
    digitalWrite(2, HIGH);
    delay(500);
    digitalWrite(2, LOW);
}

void forward() {
  // Motor "A" move forward
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enA, MA_Speed);
  // Motor "B" move forward
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enB, MB_Speed);
}

void back() {
  // Motor "A" move forward
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enA, MA_Speed);
  // Motor "B" move forward
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enB, MB_Speed);
}

void right() {
  // Motor "A"
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enA, MA_Turn_Speed);
  // Motor "B"
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enB, MB_Turn_Speed);
}

void left() {
  // Motor "A"
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enA, MA_Turn_Speed);
  // Motor "B"
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enB, MB_Turn_Speed);
}

void stop() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
