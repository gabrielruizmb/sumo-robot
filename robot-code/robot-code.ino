#define backLineSensor A0  //Porta analógica do sensor dianteiro
#define frontLineSensor A1  //Porta analógica do sensor traseiro
#define EN1 9           //Porta enable do motor esquerdo
#define EN2 4           //Porta enable do motor direito
#define IN1 10          //Porta 1 do motor esquerdo
#define IN2 11          //Porta 2 do motor esquerdo
#define IN3 5           //Porta 1 do motor direito
#define IN4 3           //Porta 2 do motor direito

int backLineSensorValue = 0;  //Armazena o valor lido pelo sensor de linha
int frontLineSensorValue = 0;  //Armazena o valor lido pelo sensor de linha

int trigger = 6;      //Porta do gatilho do sensor ultra-sônico
int eco = 7;          //Porta da escuta do sensor ultra-sônico
float robotDistance;  //Armazena a distância captada pelo sensor

float distance(int trigger, int eco);  //Função que retorna a distância media pelo sensor
void scan();
void attack();  //Faz o robô avançar quando o sensor identificar algo próximo.
void stop();
void retreat();

void setup() 
{
  // put your setup code here, to run once:

  Serial.begin(9600);  //Inícia o monitor serial

  pinMode(backLineSensor, INPUT);
  pinMode(frontLineSensor, INPUT);
  pinMode(trigger, OUTPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(EN1, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(EN2, OUTPUT);
}

void loop() 
{
  // put your main code here, to run repeatedly:

  //Lê os valores dos sensores de luz
  backLineSensorValue = analogRead(backLineSensor);  
  frontLineSensorValue = analogRead(frontLineSensor);
  
  Serial.print("Valor do sensor 1: ");
  Serial.println(backLineSensorValue);

  Serial.print("Valor do sensor 2: ");
  Serial.println(frontLineSensorValue);

  robotDistance = distance(trigger, eco);  //Lê a distância captada pelo sensor ultra-sônico
  Serial.print("Valor do sensor ultra-sônico: ");
  Serial.println(robotDistance);

  scan();

  if(backLineSensorValue < 700)
    attack();

  if(frontLineSensorValue < 700)
    retreat();
  
  delay(500);  //Pausa de 100 milísegundos
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

void scan()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(EN2, 50);
  
  //Sê o robô adversario estivar a menos de 50cm, então avançe
  if(robotDistance < 50)
  {
    attack();
  } else{stop();};  //Se não, pare
}

void attack()
{
if (robotDistance > 15) {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(EN1, 55);
  analogWrite(EN2, 100);
  //Serial.println("Baixo vapor!");
} 

if (robotDistance <= 15) {
  analogWrite(EN1, 130);
  analogWrite(EN2, 255);
  //Serial.println("Todo vapor!");
}
}

void stop()
{
  analogWrite(EN1, 0);
  analogWrite(EN2, 0);
}

void retreat()
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(EN2, 30);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(EN2, 50);
}
