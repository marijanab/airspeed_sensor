int sensorPin=A0;
int sensorValue=0;
int zo;

void setup(){
  int sum=0;
  int i;
  Serial.begin(9600);
  for(i=0;i<100;i++){  //calculate zero offset on 100 readings
    sensorValue=analogRead(sensorPin)-512;
    sum+=sensorValue;
  }
  zo=sum/100.0;
}

void loop(){
  sensorValue=analogRead(sensorPin)-zo;
  float voltage=(sensorValue*5)/1024.0; //convert value from [0,1023]-> [0,5] volts
  float pressure=voltage-2.5; // transfer function from datasheet: Vout=Vs x (0.2 x P(kPa)+0.5) +- 6.25% x VFSS;
  float velocity=sqrt(2*abs(pressure)/(1.225)); // velocity   


  //Serial.print("Voltage:"); Serial.print(voltage); Serial.println(" volts");
  Serial.print("Pressure:"); Serial.print(pressure); Serial.println(" kPa");
  Serial.print("Velocity:"); Serial.print(velocity); Serial.println(" m/s");

  delay(200);
}
