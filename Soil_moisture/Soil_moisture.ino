/*  Soil Moisture Basic Example
    Orginally from  SparkFun Electronics
    Released under the MIT License(http://opensource.org/licenses/MIT)

    Modifications include:
    use with an arduino nano and "funduino"
    calcualte average over an hour period

    customized for my polkadot plant 
    
    Observations:
    day of water:
    1 day of watering: >400
    2 days of watering: ~370-300
    3 days after water: 240-285
    4 days after watering: 150-160
*/

int val = 0; //value for storing moisture value 
int soilPin = A0;//Declare a variable for the soil moisture sensor 
int soilPower = 6;//Variable for Soil moisture Power
const int numReadings = 60;

int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average

const int ledPin = 2; 
unsigned long previousMillis = 0;  
unsigned long myTime;

const long interval = 10000;   // milliseconds
void setup() 
{
  pinMode(ledPin, OUTPUT);

  Serial.begin(9600);   // open serial over USB

  pinMode(soilPower, OUTPUT);//Set D7 as an OUTPUT
  digitalWrite(soilPower, LOW);//Set to LOW so no power is flowing through the sensor


  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
}

void loop() 
{
  unsigned long currentMillis = millis();

  //use millis so only call the soil moisture every 10 seconds (interval)
  if (currentMillis - previousMillis >= interval) {
      int ledState = LOW; 
        if(readSoil() <= 175){
          ledState = HIGH;
          digitalWrite(ledPin, HIGH);   // turn the LED on (HIGH is the voltage level)
    //  Serial.println("water your plant"); 
       }
    else if(readSoil() >175){
      digitalWrite(ledPin,LOW); 
    }
      Serial.print("Soil Moisture = ");    
      ////get soil moisture value from the function below and print it
      Serial.println(readSoil());

  
    previousMillis = currentMillis;
  }
 

//use millis instead of delay() need to trigger calling funtion every 10 seconds 

//delay(10000);//take a reading every  seconds
//Serial.println("Average: ");
//Serial.println(calcAvg());
}


//This is a function used to get the soil moisture content
int readSoil(){
    digitalWrite(soilPower, HIGH);//turn D7 "On"
    delay(100);//wait 10 milliseconds 
    val = analogRead(soilPin);//Read the SIG value form sensor 
    digitalWrite(soilPower, LOW);//turn D7 "Off"
    return val;//send current moisture value

}

int calcAvg(){
 // subtract the last reading:
  total = total - readings[readIndex];
  // read from the sensor:
  readings[readIndex] = analogRead(soilPin);
  // add the reading to the total:
  total = total + readings[readIndex];
  // advance to the next position in the array:
  readIndex = readIndex + 1;

  // if we're at the end of the array...
  if (readIndex >= numReadings) {
    // ...wrap around to the beginning:
    readIndex = 0;
  }
  // calculate the average:
  average = total / numReadings;
  // send it to the computer as ASCII digits
  //Serial.println(average);
  delay(1);        // delay in between reads for stability
  return average; 
  
}
