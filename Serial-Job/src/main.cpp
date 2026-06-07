#include <Arduino.h>

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
}