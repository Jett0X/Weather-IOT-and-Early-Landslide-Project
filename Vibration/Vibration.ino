/*
  SW-18010P Vibration Monitoring System - ADJUSTED FOR MULTI-LEVEL DETECTION
  
  This code monitors the analog output (A0) of the SW-18010P module 
  and reports different alert levels based on the severity of the drop 
  in the analog signal (1023 = Quiet, 0 = Max Vibration).
*/

// --- CONFIGURATION ---
#define Dig_pin 7                             // Digital output pin (DO) - Not strictly used, but kept for reference
// --- THRESHOLDS ---
// We define the lower boundary for the three alert levels
#define HIGH_SENSITIVITY_LOWER_BOUND 900      // Analog reading drops below 1001 but stays above 900
#define WARNING_LOWER_BOUND 500               // Analog reading drops below 751 but stays above 500
// Note: ALARM level is below 500
// ---------------------
////////////////////////////////////////
///////Lights Signage
////////////////////////////////////
int LEDRED = 8;
int LEDBLUE = 9;
int LEDGREEN = 10;
int PIEZOWARN = 11;
/////////////////////////////////

int Ana_out = 0;                              // Variable to hold the analog reading (0-1023)
String currentStatus = "Quiet";               // String to hold the current status (e.g., "Quiet", "WARNING", "ALERT")
String lastStatus = "Quiet";                  // String to track previous status

void setup() {
  Serial.begin(9600);
  pinMode(Dig_pin, INPUT);
  Serial.println("--- Vibration Monitoring System Initialized ---");
  Serial.println("Monitoring Multi-Level Thresholds:");
  Serial.println("  HIGH SENSITIVITY ALERT: 900 to 1000");
  Serial.println("  WARNING: 500 to 750");
  Serial.println("  ALARM: 0 to 499");
  //////////////////////////////////////////////////////////////////
  pinMode(LEDRED, OUTPUT);
  pinMode(LEDBLUE, OUTPUT);
  pinMode(LEDGREEN, OUTPUT);
  pinMode(PIEZOWARN, OUTPUT);

}

void loop() {
  Ana_out = analogRead(A0);
  
  // 1. Determine the current state based on the analog reading
  if (Ana_out < WARNING_LOWER_BOUND) {
    // Value is 0 to 499 -> ALARM (Max Vibration)
    currentStatus = "ALARM";
  } else if (Ana_out < 751) { 
    // Value is 500 to 750 -> WARNING (Medium Vibration)
    currentStatus = "WARNING";
  } else if (Ana_out < HIGH_SENSITIVITY_LOWER_BOUND + 100 + 1) { // This line is for demonstration of requested range 900 to 1000
    // Value is 900 to 1000 -> HIGH SENSITIVITY ALERT (Smallest detectable drop)
    // To implement the logic for the HIGH SENSITIVITY ALERT (900-1000), 
    // we use a simplified range check: Ana_out < 1001. Since we check 
    // WARNING and ALARM first, this catches 900-1000.
    currentStatus = "HIGH SENSITIVITY ALERT";
  } else {
    // Value is 1001 to 1023 -> Quiet
    currentStatus = "Quiet";
  }
  
  // 2. Report and Check for State Change
  if (currentStatus != lastStatus) {
    // State has just changed! Print a special, noticeable alert.
    if (currentStatus == "HIGH SENSITIVITY ALERT") {
      Serial.println("*************************************************");
      Serial.print("* 🚨 ALERT: HIGH SENSITIVITY VIBRATION DETECTED! 🚨 | Analog: ");
      Serial.print(Ana_out);
      Serial.println(" *");
      Serial.println("*************************************************");
      digitalWrite(LEDRED, HIGH);
      digitalWrite(LEDGREEN, LOW);
      digitalWrite(LEDBLUE, LOW);
      tone(PIEZOWARN, 500.00);
    } else if (currentStatus == "WARNING") {
      Serial.println("-------------------------------------------------");
      Serial.print("⚠️ WARNING: Medium Vibration Detected! | Analog: ");
      Serial.print(Ana_out);
      Serial.println(" ⚠️");
      digitalWrite(LEDBLUE, HIGH);
      tone(PIEZOWARN, 700.00);
      digitalWrite(LEDRED, LOW);
      digitalWrite(LEDGREEN, LOW);
      Serial.println("-------------------------------------------------");
    } else if (currentStatus == "ALARM") {
      Serial.println("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
      Serial.print("🛑 ALARM: Critical Vibration Detected! | Analog: ");
      Serial.print(Ana_out);
      Serial.println(" 🛑");
      Serial.println("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
      digitalWrite(LEDRED, HIGH);
      digitalWrite(LEDGREEN, LOW);
      digitalWrite(LEDBLUE, LOW);
      tone(PIEZOWARN, 500.00);
    } else {
      Serial.println("--- System is now QUIET ---");
      digitalWrite(LEDGREEN, HIGH);
      noTone(PIEZOWARN);
      digitalWrite(LEDRED, LOW);
      digitalWrite(LEDBLUE, LOW);
    }
    // Update the last state
    lastStatus = currentStatus;
  }

  // 3. Continuous Monitoring Output
  // Print status every half-second, but only if the system is not Quiet
  if (currentStatus != "Quiet") {
    Serial.print("Status: ");
    Serial.print(currentStatus);
    Serial.print(" | Analog: ");
    Serial.println(Ana_out);
  }
  
  delay(300); // Wait for half a second before the next reading
}	