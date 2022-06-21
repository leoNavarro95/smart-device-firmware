void setGPIO(String id, bool state)
{
   Serial.print("Set GPIO ");
   Serial.print(id);
   Serial.print(": ");
   Serial.println(state);
   digitalWrite(LED_BUILTIN, state);
}

void setPWM(String id, int pwm)
{
   Serial.print("Set PWM ");
   Serial.print(id);
   Serial.print(": ");
   Serial.println(pwm);
}

void doAction(String actionId)
{
   Serial.print("Doing action: ");
   Serial.println(actionId);
}
