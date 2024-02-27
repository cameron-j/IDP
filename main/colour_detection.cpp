#include "colour_detection.h"
#include "map.h"
#include <arduino.h>

#define IR_SENSOR_PIN 12
#define LED_DISP_PIN 13
#define RED_LED_PIN 6
#define GREEN_LED_PIN 11

void colour_detection_init() {
  pinMode(IR_SENSOR_PIN, INPUT);
  pinMode(LED_DISP_PIN, OUTPUT);
  digitalWrite(LED_DISP_PIN, LOW);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
}

int detect_colour() {
  if (digitalRead(IR_SENSOR_PIN) == BLACK) {
    return BLACK;
  }
  else {
    return RED;
  }
}

void blink_LED(int colour){
  if (colour == RED) {
    digitalWrite(GREEN_LED_PIN, LOW);
    digitalWrite(RED_LED_PIN, HIGH);
  }
  else {
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(GREEN_LED_PIN, HIGH);
  }
  delay(6000);

  digitalWrite(GREEN_LED_PIN, LOW);
  digitalWrite(RED_LED_PIN, LOW);
}
