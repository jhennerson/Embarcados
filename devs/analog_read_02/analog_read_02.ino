byte interruptPin = 13;
byte analogPin = A0;

int val1 = 0;
int val2 = 0;
int val3 = 0;
int val4 = 0;
int val5 = 0;

int valMed = 0;

int count = 0;

void setup()
{
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(
    Timer1.initialize(300000);
    Timer1.attachInterrupt(resetCount);
}

void resetCount();

void loop()
{
  val1 = analogRead(analogPin);
  val2 = analogRead(analogPin);
  val3 = analogRead(analogPin);
  val4 = analogRead(analogPin);
  val5 = analogRead(analogPin);
  valMed = ((val1 + val2 + val3 + val4 + val5) / 5);
  float voltage = valMed * (5.0 / 1023.0);
  if (voltage <= 3)
  {
    count ++
    Serial.println(voltage);
    Serial.println("counter: ");
    Serial.print(count);
  }

  if (count >= 10)
  {
    digitalWrite(interruptPin, HIGH);
    delay(50);
    digitalWrite(interruptPin, LOW);
  }
}

void resetCount()
{
  count = 0;
}
/*
  void addCount()
  {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval)
  {

  previousMillis = currentMillis;

  count ++;
  }
  }*/
