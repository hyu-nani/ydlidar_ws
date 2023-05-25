// pid����

#define driverPwmL 6
#define driverIn1 7
#define driverIn2 8
#define encoderPinA 18     // ����  //20
#define encoderPinB 19      // ���� //21

#define driverIn3 9
#define driverIn4 10
#define driverPwmR 11
#define encoderPinC 2       // ������ �Ķ���
#define encoderPinD 3       // ���� �����

#define PI 3.141592

int in1, in2, in3, in4;
int pwmR;

int leftPWMoutput, rightPWMoutput;
int data;
int PPR = 10;
int setha = 0;

float rad = PI /180;
float deg = 180 / PI;

float encoderPosLeft = 0, encoderPosRight = 0;
const float r = 11.5;
const float L = 29.2;

// pid ����
const float ratio = 360. / (84 * 10);

// PID ���
// kp = 0.83, ki = 0.235 ------------> controlR += delta_vA; (360���� �Ϻ��� ��� ������ 360�� �̻��� ���� �Ϻ��� ���� X)
double kp_R = 0.9; // 0.83 // 0.1   //0.8
double ki_R = 0; // 0.235 //0.8
double kd_R = 0;

double de_B = 0;
double di_B = 0;
double dt_sleep = 0.01;

double errorB = 0;
double error_prev_B = 0.;
double error_prev_prev_B = 0.;

double delta_vB;
double time_prev = 0;
double controlR = 0;

// ȸ������
float motorR_setha = 0;

// �̵��Ÿ�
float delta_s = 0;
float motor_s = 0;

// ������
long delta_deg = 0;

// ���ͷ�Ʈ
void doEncoderA() {
  encoderPosLeft  += (digitalRead(encoderPinA) == digitalRead(encoderPinD)) ? 1 : -1;
}
void doEncoderB() {
  encoderPosLeft  += (digitalRead(encoderPinA) == digitalRead(encoderPinD)) ? -1 : 1;
}
void doEncoderC() {
  encoderPosRight += (digitalRead(encoderPinC) == digitalRead(encoderPinD)) ? 1 : -1;
}
void doEncoderD() {
  encoderPosRight += (digitalRead(encoderPinC) == digitalRead(encoderPinD)) ? -1 : 1;
}

void interruptInit() {
  attachInterrupt(4, doEncoderA, CHANGE);   //mega pin 18
  attachInterrupt(5, doEncoderB, CHANGE);   //mega pin 19
  attachInterrupt(0, doEncoderC, CHANGE);   //mega pin 2
  attachInterrupt(1, doEncoderD, CHANGE);   //mega pin 3
}

void driverSet();
void Calculation();

void setup() {
  Serial.begin(115200);
  pinMode(driverPwmL, OUTPUT);
  pinMode(driverPwmR, OUTPUT);
  pinMode(driverIn1, OUTPUT);
  pinMode(driverIn2, OUTPUT);
  pinMode(driverIn3, OUTPUT);
  pinMode(driverIn4, OUTPUT);
  pinMode(encoderPinA, INPUT_PULLUP);
  pinMode(encoderPinB, INPUT_PULLUP);
  pinMode(encoderPinC, INPUT_PULLUP);
  pinMode(encoderPinD, INPUT_PULLUP);

  interruptInit();

  digitalWrite(driverIn1, LOW);
  digitalWrite(driverIn2, LOW);
  digitalWrite(driverIn3, LOW);
  digitalWrite(driverIn4, LOW);
  analogWrite(driverPwmL, 0);
  analogWrite(driverPwmR, 0);
}

void loop() {
  delay(100);
  Serial.print("data :");
  Serial.println(data);
  Serial.print(" / left:");
  Serial.println(encoderPosLeft);
  Serial.print(" / right:");
  Serial.print(encoderPosRight);
  Serial.print(" / motorR_setha:");
  Serial.println(motorR_setha * deg);
  Serial.print(" / motor_s:");
  Serial.println(motor_s);
  Serial.print(" / delta_deg:");
  Serial.println(delta_deg);
  Serial.print(" / controlR :");
  Serial.println(controlR);
  Serial.print(" / kp_R :");
  Serial.println(kp_R);
  Serial.print(" / ki_R :");
  Serial.print(ki_R);
  Serial.print(" / kd_R :");
  Serial.println(kd_R);

  Calculation();
  driverSet();
}

void Calculation() {

  // ����
  motorR_setha = (encoderPosRight / (PPR * 84)) * 360 * rad;
 
  // unsigned long start_time = millis();
  errorB = setha - motorR_setha;
 // di_B += errorB * dt;

  delta_vB = kp_R * (errorB - error_prev_B) + ki_R * errorB + kd_R * (errorB - 2 * error_prev_B + error_prev_prev_B);
  controlR += delta_vB;
  pwmR = min(abs(controlR), 150);
 
  error_prev_prev_B = error_prev_B;
  error_prev_B = errorB;
  // time_prev = start_time;

  // �̵��Ÿ�
  delta_s = r / 2 * (motorR_setha + motorR_setha);
  motor_s = delta_s * (PI / 180);

  // ������
  delta_deg = r / L * (motorR_setha - motorR_setha);
}

void driverSet() {
  if (Serial.available() > 0) {
    data = Serial.parseInt();
    setha = Serial.parseInt();
    // kp_R = Serial.parseInt();
    // ki_R = Serial.parseInt();
    // kd_R = Serial.parseInt();
  }
  if (data == 0) {
    // ����(�ʱ�ȭ)
    in1 = LOW; in2 = LOW; in3 = LOW, in4 = LOW;
    digitalWrite(driverIn1, LOW);
    digitalWrite(driverIn2, LOW);
    digitalWrite(driverIn3, LOW);
    digitalWrite(driverIn4, LOW);
    delay(20);
    digitalWrite(driverIn1, in1);
    digitalWrite(driverIn2, in2);
    analogWrite(driverPwmL, 0);
    digitalWrite(driverIn3, in3);
    digitalWrite(driverIn4, in4);
    analogWrite(driverPwmR, 0);

    encoderPosLeft = 0;
    encoderPosRight = 0;
    motorR_setha = 0;
    delta_s = 0;
    delta_deg = 0;
    controlR = 0;
  }

  else if (data == 1) {
    // ����
    in1 = LOW; in2 = HIGH; in3 = HIGH, in4 = LOW;
    digitalWrite(driverIn1, in1);
    digitalWrite(driverIn2, in2);
    analogWrite(driverPwmL, pwmR);
    digitalWrite(driverIn3, in3);
    digitalWrite(driverIn4, in4);
    analogWrite(driverPwmR, pwmR);

    if (motorR_setha >= setha* rad) { // �� ���� ȸ���ϴµ� ������ �޽� �� : 1360 -> 920
      in1 = LOW; in2 = LOW; in3 = LOW, in4 = LOW;
      digitalWrite(driverIn1, LOW);
      digitalWrite(driverIn2, LOW);
      digitalWrite(driverIn3, LOW);
      digitalWrite(driverIn4, LOW);
      delay(20);
      digitalWrite(driverIn1, in1);
      digitalWrite(driverIn2, in2);
      analogWrite(driverPwmL, 0);
      digitalWrite(driverIn3, in3);
      digitalWrite(driverIn4, in4);
      analogWrite(driverPwmR, 0);
    }
  }
    else if (data == 2) {
      // ����
      in1 = HIGH; in2 = LOW; in3 = LOW, in4 = HIGH;
      digitalWrite(driverIn1, in1);
      digitalWrite(driverIn2, in2);
      analogWrite(driverPwmL, 20);
      digitalWrite(driverIn3, in3);
      digitalWrite(driverIn4, in4);
      analogWrite(driverPwmR, 20);

      if (encoderPosRight >= 840) { // �� ���� ȸ���ϴµ� ������ �޽� �� : 1360
        in1 = LOW; in2 = LOW; in3 = LOW, in4 = LOW;

        digitalWrite(driverIn1, LOW);
        digitalWrite(driverIn2, LOW);
        digitalWrite(driverIn3, LOW);
        digitalWrite(driverIn4, LOW);
        delay(20);
        digitalWrite(driverIn1, in1);
        digitalWrite(driverIn2, in2);
        analogWrite(driverPwmL, 0);
        digitalWrite(driverIn3, in3);
        digitalWrite(driverIn4, in4);
        analogWrite(driverPwmR, 0);

      }
    }
}