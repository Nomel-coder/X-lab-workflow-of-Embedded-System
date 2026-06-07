#include <Arduino.h>

// 定义连接到 ULN2003 的 ESP32 引脚
const int IN1 = 13;
const int IN2 = 26;
const int IN3 = 14;
const int IN4 = 27;

// 四相八拍的电平状态表（1代表高电平，0代表低电平）
// 顺着读是正转，逆着读是反转
const int stepsSequence[8][4] = {
  {1, 0, 0, 0}, // 步 1
  {1, 1, 0, 0}, // 步 2
  {0, 1, 0, 0}, // 步 3
  {0, 1, 1, 0}, // 步 4
  {0, 0, 1, 0}, // 步 5
  {0, 0, 1, 1}, // 步 6
  {0, 0, 0, 1}, // 步 7
  {1, 0, 0, 1}  // 步 8
};

// 调节转速的关键：每一步之间的延时（单位：毫秒）
// ⚠️ 注意：28BYJ-48 带有高减速比，延时太小（如小于1ms）电机内部齿轮会因为卡死而只震动不转；太大（如大于10ms）转速会极慢。
int stepDelay = 4; // 4ms 的延时大约能让电机以 15-20 RPM 的速度转动，适合演示和一般应用。根据需要调整这个值来改变转速。

// 函数声明
void moveForward(int steps);
void moveBackward(int steps);
void setPins(int stepIndex);
void stopMotor();

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println("步进电机驱动系统初始化...");

  // 设置所有驱动引脚为输出模式
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // 初始状态关闭所有引脚
  stopMotor();
}

void loop() {
  Serial.println(">>> 开始正转一圈...");
  moveForward(2048); // 2048 步正好是一圈
  stopMotor();       // 停顿期间关闭引脚，防止电机发热
  
  Serial.println("暂停 2 秒...");
  delay(2000);

  Serial.println("<<< 开始反转一圈...");
  moveBackward(2048);
  stopMotor();
  
  Serial.println("暂停 2 秒...\n");
  delay(2000);
}

// 正转控制函数
void moveForward(int steps) {
  for (int i = 0; i < steps; i++) {
    // 正转：节拍按 0 -> 1 -> 2 ... -> 7 循环
    int stepIndex = i % 8;
    setPins(stepIndex);
    delay(stepDelay); // 控制转速
  }
}

// 反转控制函数
void moveBackward(int steps) {
  for (int i = 0; i < steps; i++) {
    // 反转：节拍反过来，按 7 -> 6 -> 5 ... -> 0 循环
    int stepIndex = 7 - (i % 8);
    setPins(stepIndex);
    delay(stepDelay);
  }
}

// 写入引脚电平的辅助函数
void setPins(int stepIndex) {
  digitalWrite(IN1, stepsSequence[stepIndex][0]);
  digitalWrite(IN2, stepsSequence[stepIndex][1]);
  digitalWrite(IN3, stepsSequence[stepIndex][2]);
  digitalWrite(IN4, stepsSequence[stepIndex][3]);
}

// 停止电机并释放引脚（防止 ULN2003 持续给内部线圈通电导致发热）
void stopMotor() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}