#include <Arduino.h>

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
}