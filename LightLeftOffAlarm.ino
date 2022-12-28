// Buzzer
int buzzerPin = 2;

// Photorresistor
int photoPin = A0;
int lightVal;
int lightThreshold = 400;

// Ultrasonic sensor
int triggerPin = 12;
int echoPin = 11;
float pingTravelTime = 0; // microseconds
float distance = 0; // meters
float speedOfSound = 343.; // meters per seconds
float distanceThreshold = 0.9; // meters

void setup() {
  Serial.begin(9600);
  
  // Ultrasonic sensor pins
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Photoresistor pins
  pinMode(photoPin, INPUT);

  // Buzzer pins
  pinMode(buzzerPin, OUTPUT);
}

void loop() {

if(isLightOn()){
  if(isDoorClosed()){
    Serial.println("DOOR IS CLOSED!!!");
    soundAlarm(HIGH);
    }
    else{
      soundAlarm(LOW);
      }
  }
  else{
    soundAlarm(LOW);
  }

  delay(2000);
}


void soundAlarm(bool value)
{
   digitalWrite(buzzerPin, value);
}

int isLightOn()
{
  lightVal = analogRead(photoPin);
  Serial.print("Light is:");
  Serial.println(lightVal);
  
  return lightVal > lightThreshold;
}

bool isDoorClosed()
{
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(10);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  pingTravelTime = pulseIn(echoPin, HIGH);
  /*Serial.print("Ping Travel Time is:");
  Serial.println(pingTravelTime);*/
  
  distance = speedOfSound * (pingTravelTime / 2) / 1000000;
  Serial.print("Distance is:");
  Serial.println(distance);
  
  return distance <= distanceThreshold;
}
