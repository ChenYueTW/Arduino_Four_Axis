#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Arduino.h>

RF24 radio(7, 8);                // 指定 Arduino Nano 腳位對應 nRF24L01 之 (CE, CSN)
const byte address[6] = "1Node"; // 節點位址為 5 bytes + \0=6 bytes

void setup() {
    Serial.begin(9600);
    radio.begin();        // 初始化 nRF24L01 模組
    radio.setChannel(83); // 設定頻道編號
    radio.setDataRate(RF24_2MBPS);
    radio.openWritingPipe(address); // 開啟寫入管線
    radio.setPALevel(RF24_PA_MAX);  // 設為低功率, 預設為 RF24_PA_MAX
    radio.stopListening();          // 傳送端不需接收, 停止傾聽
}

void loop() {
    char text[32]; // 宣告用來儲存欲傳送之字串
    int x = analogRead(0); // X
    int y = analogRead(1); // Y
    int r = analogRead(2); // Rotation
    int t = analogRead(3); // throttle 

    sprintf(text, "%d|%d%|%d|%d", x, y, r, t); // 將整數嵌入字串中
    Serial.println(text);
    radio.write(&text, sizeof(text)); // 將字串寫入傳送緩衝器
    delay(20);
}
