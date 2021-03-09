#include <Arduino.h>
#pragma once
void gpio_on(uint8_t pin)
{
  digitalWrite(pin,HIGH);
}

void gpio_off(uint8_t pin)
{
  digitalWrite(pin,LOW);
}

void gpio_output(uint8_t pin)
{
  pinMode(pin,OUTPUT);
}

void gpio_input(uint8_t pin)
{
  pinMode(pin,INPUT);
}
