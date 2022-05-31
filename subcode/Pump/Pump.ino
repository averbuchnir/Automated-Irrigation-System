
const int relay_1 = 25;
const int relay_2 = 26;
const int relay_3 = 27;

void setup() {
  Serial.begin(9600);
  pinMode(relay_1, OUTPUT);
  pinMode(relay_2, OUTPUT);
  pinMode(relay_3, OUTPUT);
  
}

void loop() {
  // Normally Open configuration, send LOW signal to let current flow
  // (if you're usong Normally Closed configuration send HIGH signal)
  digitalWrite(relay_1, LOW);
  delay(100);
  digitalWrite(relay_2, LOW);
  delay(100);
  digitalWrite(relay_3, LOW);
  delay(100);
  Serial.println("Current Flowing");
  delay(5000); 
  
  // Normally Open configuration, send HIGH signal stop current flow
  // (if you're usong Normally Closed configuration send LOW signal)
  digitalWrite(relay_1, HIGH);
  delay(100);
  digitalWrite(relay_2, HIGH);
  delay(100);
  digitalWrite(relay_3, HIGH);
  delay(100);
  Serial.println("Current not Flowing");
  delay(10000);
}
