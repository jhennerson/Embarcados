int val1 = 0;
int val2 = 0;
int val3 = 0;
int val4 = 0;
int val5 = 0;

int valMed = 0;

void setup()
{
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop()
{
  val1 = analogRead(A0);
  val2 = analogRead(A0);
  val3 = analogRead(A0);
  val4 = analogRead(A0);
  val5 = analogRead(A0);
  valMed = ((val1 + val2 + val3 + val4 + val5) / 5);
  float voltage = valMed * (5.0 / 1023.0);
  Serial.println(voltage);
}
