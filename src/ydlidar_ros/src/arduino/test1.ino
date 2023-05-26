// 엔코더 펄스
#define encoderPinA 18      // 왼쪽  //20
#define encoderPinB 19      // 왼쪽 //21
#define encoderPinC 2       // 오른쪽 파란색
#define encoderPinD 3       // 왼쪽 보라색

#define ATrunEdgeCount  84*4*40 //6720
double edgeCount = 0;       //모터에 발생한 인터럽트 count  . 이전 encoderPos 값과 동일.

bool interrupt_flag = false;    //인터럽트 이중 발생시 한쪽의 딜레이를 막기 위한 용도

void doEncoderA() {
  interrupt_flag = true;
  edgeCount  += (digitalRead(encoderPinA) == digitalRead(encoderPinD)) ? 1 : -1;
}
void doEncoderB() {
  interrupt_flag = true;
  edgeCount  += (digitalRead(encoderPinA) == digitalRead(encoderPinD)) ? -1 : 1;
}

void interruptInit() {
  attachInterrupt(4, doEncoderA, CHANGE);   //mega pin 18
  attachInterrupt(5, doEncoderB, CHANGE);   //mega pin 19
}

void setup() {
  Serial.begin(115200);
  pinMode(encoderPinA, INPUT_PULLUP);
  pinMode(encoderPinB, INPUT_PULLUP);
  interruptInit();
}

void loop() {
    if (interrupt_flag != true)
    {
        float angle = (edgeCount/ATrunEdgeCount)*360.0;
        Serial.print("angle:");
        Serial.println(angle);
    }
    else
    {
        interrupt_flag = false;
    }
}