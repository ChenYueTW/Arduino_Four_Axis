#include <Arduino.h>
#include <Servo.h>
#include <RF24.h>
#include <nRF24L01.h>
#include <printf.h>
#include <MPU6050_light.h>
#include <Wire.h>

Servo FRONT_LEFT;
Servo FRONT_RIGHT;
Servo BACK_LEFT;
Servo BACK_RIGHT;

double frontLeftOutput;
double frontRightOutput;
double backLeftOutput;
double backRightOutput;

RF24 radio(8, 9);				 // 指定 Arduino Nano 腳位對應 nRF24L01 之 (CE, CSN)
const byte address[6] = "1Node"; // 節點位址為 5 bytes + \0=6 bytes

MPU6050 mpu(Wire);

int x; // x
int y; // y
int r; // rotation
int t; // throttle

void setup() {
	Serial.begin(9600);

	// Servo Init
	FRONT_LEFT.attach(6);
	FRONT_RIGHT.attach(3);
	BACK_LEFT.attach(10);
	BACK_RIGHT.attach(5);

	// RF24 Init
	radio.begin();					   // 初始化 nRF24L01 模組
	printf_begin();					   // 初始化 RF24 的列印輸出功能
	radio.setChannel(83);
	radio.setDataRate(RF24_2MBPS);
	radio.openReadingPipe(0, address); // 開啟 pipe 0 之讀取管線
	radio.setPALevel(RF24_PA_MAX);	   // 設為低功率, 預設為 RF24_PA_MAX
	radio.startListening();			   // 接收端開始接收
	radio.printDetails();			   // 印出 nRF24L01 詳細狀態
	Serial.println("NRF24L01 receiver");
	Serial.println("waiting...");

	// MPU6050 Init
	Wire.begin();
	byte status = mpu.begin();
	Serial.print(F("MPU6050 status: "));
	Serial.println(status);
	while (status != 0) {}

	Serial.println(F("Calculating offsets, do not move MPU6050"));
	delay(1000);
	mpu.calcOffsets(); 
	Serial.println("Done!\n");
}

void loop() {
	mpu.update();

	if (radio.available()) { // 偵測接收緩衝器是否有資料
		char text[32] = "";	// 用來儲存接收字元之陣列
		radio.read(&text, sizeof(text)); // 讀取接收字元
		String reciverText = String(text);
		reciverText.indexOf('|');
		x = reciverText[0];
		y = reciverText[1];
		r = reciverText[2];
		t = reciverText[3];

		Serial.println(text);
	}

	// PID

	FRONT_LEFT.writeMicroseconds(frontLeftOutput);
	FRONT_RIGHT.writeMicroseconds(frontRightOutput);
	BACK_LEFT.writeMicroseconds(backLeftOutput);
	BACK_RIGHT.writeMicroseconds(backRightOutput);
}