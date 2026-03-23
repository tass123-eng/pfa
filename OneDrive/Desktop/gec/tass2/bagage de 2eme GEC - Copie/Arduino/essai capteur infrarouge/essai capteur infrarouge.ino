int datapin=8;
int b=0;
int c=0;
bool T=true;
void setup() {
  // put your setup code here, to run once:
  pinMode (datapin,INPUT);
  pinMode(7,OUTPUT);
  pinMode(4,OUTPUT);


  digitalWrite(7,LOW) ;
  Serial.begin(9600);

}

void loop() {

  // put your main code here, to run repeatedly:
int a = digitalRead(datapin);
      Serial.print(a);

      if ((a!=b) && (a==1))
      { b=a;
        c++;
     
      }
      if (c == 3)
      {
      digitalWrite(7,HIGH) ;

      
      }
      if (c == 4)
      {
      digitalWrite(7,LOW) ;

      c=0;
      }
      Serial.print("   ");
      Serial.println(c);
      b=a;
      
}
