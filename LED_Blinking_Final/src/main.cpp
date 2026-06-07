#include <Arduino.h>

<<<<<<< HEAD
// ==========================================
// 1. 配置区域
// ==========================================
// 定义连接 LED 的 GPIO 引脚数组
const int ledPins[] = {2, 4, 5, 18};

// 动态计算 LED 的数量
const int numLeds = sizeof(ledPins) / sizeof(ledPins[0]);

// 流水灯闪烁的延时时间（单位：毫秒）
const int delayTime = 500; 

// ==========================================
// 2. 初始化函数
// ==========================================
void setup() {
    // 循环初始化所有引脚为输出模式
    for (int i = 0; i < numLeds; i++) {
        pinMode(ledPins[i], OUTPUT);
        // 初始化时让所有 LED 处于熄灭状态（低电平）
        digitalWrite(ledPins[i], LOW);
    }
}

// ==========================================
// 3. 主循环函数
// ==========================================
void loop() {
    // ---- 阶段 1: 从左到右依次点亮 ----
    for (int i = 0; i < numLeds; i++) {
        digitalWrite(ledPins[i], HIGH); // 点亮当前 LED
        delay(delayTime);               // 等待一段时间
    }

    // ---- 阶段 2: 从左到右依次熄灭 ----
    for (int i = 0; i < numLeds; i++) {
        digitalWrite(ledPins[i], LOW);  // 熄灭当前 LED
        delay(delayTime);               // 等待一段时间
    }
=======
// ESP-WROOM-32 板载蓝色 LED 通常在 GPIO 2
const int LED1 = 2; 
// 任务要求控制两个灯，你可以把第二个灯接在 GPIO 4（或者其他可用 GPIO）
const int LED2 = 4; 

void setup() {
  // ESP32 的串口速度非常快，虽然这里配合你的要求用 9600，但它完全支持 115200
  Serial.begin(9600);
  
  // 给 ESP32 串口初始化留出一点点时间
  delay(500); 
  
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  
  // 默认关闭
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  
  Serial.println("ESP32 系统就绪。输入 '1' 翻转 LED1，输入 '2' 翻转 LED2。");
}

void loop() {
  // 检查串口是否有数据
  if (Serial.available() > 0) {
    // 读取数据直到换行符
    String inputString = Serial.readStringUntil('\n');
    
    // 必须 trim！去除 ESP32 串口中可能附带的 \r 结束符
    inputString.trim();
    
    if (inputString == "1") {
      int currentState = digitalRead(LED1);
      if (currentState == LOW) {
        digitalWrite(LED1, HIGH);
        Serial.println("LED1亮");
      } else {
        digitalWrite(LED1, LOW);
        Serial.println("LED1灭");
      }
    } 
    else if (inputString == "2") {
      int currentState = digitalRead(LED2);
      if (currentState == LOW) {
        digitalWrite(LED2, HIGH);
        Serial.println("LED2亮");
      } else {
        digitalWrite(LED2, LOW);
        Serial.println("LED2灭");
      }
    }
  }
>>>>>>> master
}