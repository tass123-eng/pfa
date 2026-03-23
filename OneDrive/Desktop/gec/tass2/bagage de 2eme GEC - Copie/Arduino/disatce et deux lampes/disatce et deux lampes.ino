const int trigPin = 9;
const int echoPin = 10;
long duration;
int distance;
void setup() {
  // put your setup code here, to run once:
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  Serial.println(distance);
  if (distance < 10) {
    digitalWrite(7, HIGH);
    digitalWrite(8, HIGH);
  }
  if (distance < 15)
    digitalWrite(8, HIGH);

  else {
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
  }
  // put your main code here, to run repeatedly:
}