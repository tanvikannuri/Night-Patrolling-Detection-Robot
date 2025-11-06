#define trigPin1 13      // us1
#define echoPin1 12
#define trigPin2 11
#define echoPin2 10
#define trigPin3 9
#define echoPin3 8

#define motor1  A0
#define motor1a A1
#define motor2  A2
#define motor2a A3
#define inp A4
int rbyte = 0;

long duration, distance,sensor2,sensor1,sensor3;
int mode=LOW;

void setup() 
{
 pinMode(motor1, OUTPUT); 
 pinMode(motor1a, OUTPUT); 
 pinMode(motor2, OUTPUT); 
 pinMode(motor2a, OUTPUT);
 pinMode(trigPin1, OUTPUT);
 pinMode(echoPin1, INPUT);
 pinMode(trigPin2, OUTPUT);
 pinMode(echoPin2, INPUT); 
 pinMode(trigPin3, OUTPUT);
 pinMode(echoPin3, INPUT);
  pinMode(inp, INPUT_PULLUP);
 stopp();
}
void forward()
{   
 digitalWrite(motor1, HIGH); 
 digitalWrite(motor1a, LOW); 
 digitalWrite(motor2, HIGH); 
 digitalWrite(motor2a, LOW);
}
void backward()
{
 digitalWrite(motor1, LOW); 
 digitalWrite(motor1a, HIGH); 
 digitalWrite(motor2, LOW); 
 digitalWrite(motor2a, HIGH);
}
 void stopp()
 {
  digitalWrite(motor1, LOW); 
  digitalWrite(motor1a, LOW); 
  digitalWrite(motor2, LOW); 
  digitalWrite(motor2a, LOW);
 }
 void left()
 {
  digitalWrite(motor1, HIGH); 
  digitalWrite(motor1a, LOW); 
  digitalWrite(motor2, LOW); 
  digitalWrite(motor2a, HIGH);
 }
 void right()
 {
  digitalWrite(motor1, LOW); 
  digitalWrite(motor1a, HIGH); 
  digitalWrite(motor2, HIGH); 
  digitalWrite(motor2a, LOW);
 }
//-----------------------------------------------------------------------// 
void loop() 
{
 mode=digitalRead(inp);  
  if(mode==LOW)
  {
   ultrasensor(trigPin1, echoPin1);
   sensor1 = distance;
   delay(2); 
   ultrasensor(trigPin2, echoPin2);
   sensor2 = distance;
   delay(2);
   ultrasensor(trigPin3, echoPin3);
   sensor3 = distance;
   Serial.print("sensor1=");
   Serial.println(sensor1);
   Serial.print("sensor2=");
   Serial.println(sensor2);
   Serial.print("sensor3=");
   Serial.println(sensor3);
   delay(200); 
  }
  else
  {
   manual_mode();  
  }
 
  
 }
 
void straight()
{
 if(sensor1 <= 55 && sensor1 >= 2)
  {
   direction_change(); 
  }
  else
  {
   forward();
   direction_change();
   //delay(200);
//   stopp();
  }
 }
 void direction_change()
 {
  if(sensor2 <= 45 && sensor2 >= 2)
  { 
   right(); 
   delay(200);
   stopp();
  }
   else if(sensor3 <= 45 && sensor3 >= 2)
  {
    left();
    delay(200); 
    stopp();
   }  
   else if((sensor3 <= 20 && sensor3 >= 2)&&(sensor2 <= 20 && sensor2 >= 2))
   {
    stopp();
   } 
  }
void ultrasensor(int trigPin,int echoPin)
{  
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
 }


 void manual_mode()
 {
 if (Serial.available() > 0) 
{  
 rbyte = Serial.read();
 Serial.print(rbyte); 
}
switch(rbyte) 
{ 
  case 'F':                   // fwd
 forward();
 rbyte='*'; 
 break; 

 case 'B':                 // bwd
 backward();
 rbyte='*'; 
 break; 

 case 'R':                 // right
 right();
 rbyte='*'; 
 break; 

 case 'L':                       //left
 left();
 rbyte='*'; 
 break;  
  delay(50);
 case 'S': 
 stopp();
 rbyte='*'; 
  break; 
}
 } 
 }
