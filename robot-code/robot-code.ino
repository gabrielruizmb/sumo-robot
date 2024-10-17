#define lineSensor1 A0
#define lineSensor2 A1

int lineSensor1Value = 0;
int lineSensor2Value = 0;


void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
 
  pinMode(lineSensor1, INPUT);
  pinMode(lineSensor2, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:

  lineSensor1Value = analogRead(lineSensor1);
  lineSensor2Value = analogRead(lineSensor2);
  
  Serial.println("Valor do sensor 1: ");
  Serial.println(lineSensor1Value);

  Serial.println("Valor do sensor 2: ");
  Serial.println(lineSensor2Value);
  delay(1000);

}
