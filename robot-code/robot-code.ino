#define lineSensor1 A0
#define lineSensor2 A1

int lineSensor1Value = 0;
int lineSensor2Value = 0;

int trigger = 6;
int eco = 7;
float robotDistance;

float distance(int trigger, int eco);

void setup() 
{
  // put your setup code here, to run once:

  Serial.begin(9600);
 
  pinMode(lineSensor1, INPUT);
  pinMode(lineSensor2, INPUT);
  pinMode(trigger, OUTPUT);

}

void loop() 
{
  // put your main code here, to run repeatedly:

  lineSensor1Value = analogRead(lineSensor1);
  lineSensor2Value = analogRead(lineSensor2);

  // Se estiver dentro da pista o valor é maior que 800, na linha menor que 600
//  Serial.print("Valor do sensor 1: ");
//  Serial.println(lineSensor1Value);
//
//  Serial.print("Valor do sensor 2: ");
//  Serial.println(lineSensor2Value);

  robotDistance = distance(trigger, eco);

  //robotDistance = sensor.getCM();
  
  Serial.println(robotDistance);
  delay(2000);
}

float distance(int trigger, int eco) 
{
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(20);
  digitalWrite(trigger, LOW);
  pinMode(eco, INPUT);
  
  return (pulseIn(eco, HIGH)*0.01723);
}
