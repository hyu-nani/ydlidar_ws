// ���ڴ� �޽�
#define encoderPinA 18      // ����  //20
#define encoderPinB 19      // ���� //21
#define encoderPinC 2       // ������ �Ķ���
#define encoderPinD 3       // ���� �����

#define ATrunEdgeCount  84*4*40 //6720
double edgeCount = 0;       //���Ϳ� �߻��� ���ͷ�Ʈ count  . ���� encoderPos ���� ����.

bool interrupt_flag = false;    //���ͷ�Ʈ ���� �߻��� ������ �����̸� ���� ���� �뵵

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