/*
 COZIR CO2 Sensor Test Code
 Reads analog pin A0, converts it to voltage, and prints to the serial monitor.
 Adam J Burns
 adam@aburns.us
 Nov 12 2013
 
 -TODO...(1) set up github page
         (2) add timestamp
         (3) write to file
         (4) set up webpage to display data
 */
 
// =============================== Declarations ===============================
#define aref_voltage 3.3         // we tie 3.3V to ARef 

#define NUMSAMPLES 50       // number of samples taken to average over
#define analogpin A0
//-------------------- end declarations -----------------------------

#define NUMSAMPLES 5       // number of samples taken to average over
#define analogpin A0	// CO2 sensor analog pin to A0
//--------------------------- end declarations --------------------------------


// ================================== Setup ===================================
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  delay(100); // not needed but helps prevent errors during reset
    
  //-----------------------------DON'T CHANGE THIS-----------------------------
  analogReference(EXTERNAL); // *DON'T CHANGE THIS LINE*
  //-----------------------------DON'T CHANGE THIS-----------------------------
  
  delay(200);
  analogRead(analogpin); // dummy read to make sure aref=external
  Serial.println("Sensor power up");
  delay(3000); //let sensor warm up for 3 seconds
}
// ------------------------ end setup -------------------------

// ========================== Loop Routine ======================
void loop() {

  uint8_t i;
  int samples[NUMSAMPLES];
  float average = 0;
  float sample_co2_conc;
  
  // take 5 samples at 2 second increments
  for (i=0; i< NUMSAMPLES; i++) {

    samples[i] = analogRead(analogpin);
    sample_co2_conc = convertVoltage(aref_voltage, samples[i]);
  //  Serial.print(i+1);
  //  Serial.print(": ");
  //  Serial.print(sample_co2_conc);
      delay(10); // dont go below 7

    samples[i] = analogRead(analogpin); // this returns an int between 0-1023
    sample_co2_conc = convertVoltage(aref_voltage, samples[i]); 
    Serial.print(i+1);
    Serial.print(": ");
    Serial.print(sample_co2_conc);
    Serial.print("ppm, ");
    delay(2000); // delay between reads must be > 7;

  }
  // average all the samples out
  average = 0;
  for (i=0; i< NUMSAMPLES; i++) {
    average += samples[i];
  }
  average /= NUMSAMPLES;
  Serial.println("screw off man!");
  Serial.print("Average raw analog reading "); 
  Serial.println(average);
  
  float co2_conc = convertVoltage(aref_voltage, average);
  Serial.print("CO2 Conc: ");
  Serial.print(co2_conc); 
  Serial.println(" ppm");
  Serial.println("");
  delay(2000); //wait 2 seconds before next reading
}
// -------------------- end loop routine ---------------------------

float convertVoltage(float v_ref, float v_avg){
  int MAXPPM = 10000;
  float v_measured = v_ref*v_avg;
  v_measured /= 1024.0;
  float co2_conc = MAXPPM*v_measured/v_ref;
  return co2_conc;
}
  



