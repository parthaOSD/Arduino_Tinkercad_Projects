int n=0;
void setup()
{
pinMode(4,OUTPUT);
    pinMode(7, OUTPUT);
  pinMode(2,OUTPUT);
   
  for(n=4;n>=2;n--){
  pinMode(n,OUTPUT);
  
  }
  
}

void loop()
{
  for(n=4;n>=2;n--){
  
  digitalWrite(n,HIGH);
    delay(100);
    digitalWrite(n,LOW);
    delay(100);
  }
      delay(100);
      }