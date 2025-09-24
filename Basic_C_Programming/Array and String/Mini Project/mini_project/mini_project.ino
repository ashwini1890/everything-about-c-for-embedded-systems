/*
  sensor_fusion_arduino_fixed.ino
  Fixed: no use of Serial.printf / Serial.print with format.
  Uses snprintf into a buffer, then Serial.print(buffer).
*/

#include <Arduino.h>
#include <LiquidCrystal.h>
#include <math.h>

// LCD pins: RS, E, D4, D5, D6, D7  -- adjust wiring if needed
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Configuration
const int ROWS = 3;   // axes: X, Y, Z
const int COLS = 2;   // number of samples per axis
const float ALPHA = 0.98f;         // complementary filter weight
const float TILT_THRESHOLD = 150.0f; // tune for your sensor units
const float MOTION_THRESHOLD = 50.0f;

// Analog pin mapping for simulated inputs (replace when using real sensors)
const int ACCEL_PINS[ROWS][COLS] = {
  {A0, A1}, // accel X samples
  {A2, A3}, // accel Y samples
  {A4, A5}  // accel Z samples
};
const int GYRO_PINS[ROWS][COLS] = {
  {A0, A1}, // gyro X samples (for simulation, reuse or change)
  {A2, A3}, // gyro Y
  {A4, A5}  // gyro Z
};

// Buffers / states
float accel[ROWS][COLS];
float gyro[ROWS][COLS];
float fusedMat[ROWS][COLS];
float accel_avg[ROWS], gyro_avg[ROWS], fused_axis[ROWS];
float gyro_est[ROWS] = {0.0f, 0.0f, 0.0f};

// small helper to print formatted text over Serial (using snprintf)
void SerialPrintf(const char *fmt, ...) {
  char buf[128];
  va_list ap;
  va_start(ap, fmt);
  vsnprintf(buf, sizeof(buf), fmt, ap);
  va_end(ap);
  Serial.print(buf);
}

// Map ADC raw 0..1023 -> demo sensor value (centered around 0)
float mapRawToSensor(int raw) {
  // map 0..1023 to -512..+511 (demo units)
  return (float)(raw - 512);
}

// Read simulated accelerometer samples
void readAccelerometer() {
  for (int i = 0; i < ROWS; ++i) {
    for (int j = 0; j < COLS; ++j) {
      int raw = analogRead(ACCEL_PINS[i][j]); // 0..1023
      accel[i][j] = mapRawToSensor(raw);
    }
  }
}

// Read simulated gyroscope samples
void readGyroscope() {
  for (int i = 0; i < ROWS; ++i) {
    for (int j = 0; j < COLS; ++j) {
      int raw = analogRead(GYRO_PINS[i][j]);
      gyro[i][j] = mapRawToSensor(raw) * 1.0f; // scale if needed
    }
  }
}

// Matrix addition (element-wise)
void matrixAdd(float a[ROWS][COLS], float b[ROWS][COLS], float out[ROWS][COLS]) {
  for (int i = 0; i < ROWS; ++i)
    for (int j = 0; j < COLS; ++j)
      out[i][j] = a[i][j] + b[i][j];
}

// Average across columns -> axis average
void axisAverage(float mat[ROWS][COLS], float avg[ROWS]) {
  for (int i = 0; i < ROWS; ++i) {
    float s = 0.0f;
    for (int j = 0; j < COLS; ++j) s += mat[i][j];
    avg[i] = s / (float)COLS;
  }
}

// Complementary filter (very simple example)
void complementaryFilter(float accel_avg[ROWS], float gyro_est[ROWS], float fused_out[ROWS]) {
  for (int i = 0; i < ROWS; ++i) {
    fused_out[i] = ALPHA * accel_avg[i] + (1.0f - ALPHA) * gyro_est[i];
    gyro_est[i] = fused_out[i]; // update state (simplified)
  }
}

void printDebug(float accel_avg[ROWS], float gyro_avg[ROWS], float fused_axis[ROWS]) {
  Serial.print("Accel avg: ");
  for (int i = 0; i < ROWS; ++i) { Serial.print(accel_avg[i], 1); Serial.print(" "); }
  Serial.println();

  Serial.print("Gyro avg:  ");
  for (int i = 0; i < ROWS; ++i) { Serial.print(gyro_avg[i], 1); Serial.print(" "); }
  Serial.println();

  Serial.print("Fused axis: ");
  for (int i = 0; i < ROWS; ++i) { Serial.print(fused_axis[i], 1); Serial.print(" "); }
  Serial.println();
  Serial.println("-------------------------------");
}

// Decision logic and LCD display (uses SerialPrintf)
void decideActionAndDisplay(float fused_axis[ROWS]) {
  float tilt = sqrtf(fused_axis[0]*fused_axis[0] + fused_axis[1]*fused_axis[1]);
  float maxAxis = fabsf(fused_axis[0]);
  for (int i = 1; i < ROWS; ++i) {
    float a = fabsf(fused_axis[i]);
    if (a > maxAxis) maxAxis = a;
  }

  char line1[17] = {0};
  char line2[17] = {0};
  char buf[128];

  if (tilt > TILT_THRESHOLD || maxAxis > (TILT_THRESHOLD * 1.2f)) {
    // use SerialPrintf (snprintf -> Serial.print)
    SerialPrintf("Decision: STOP motors (tilt=%.2f, max=%.2f)\n", tilt, maxAxis);
    strncpy(line1, "STOP MOTORS", sizeof(line1)-1);
    snprintf(line2, sizeof(line2), "Tilt:%d", (int)tilt);
    // In real hardware: call motor stop function here
  } else if (tilt > MOTION_THRESHOLD) {
    SerialPrintf("Decision: SLOW DOWN (tilt=%.2f)\n", tilt);
    strncpy(line1, "SLOW DOWN", sizeof(line1)-1);
    snprintf(line2, sizeof(line2), "Tilt:%d", (int)tilt);
    // call slow motor
  } else {
    SerialPrintf("Decision: CONTINUE (tilt=%.2f)\n", tilt);
    strncpy(line1, "CONTINUE", sizeof(line1)-1);
    snprintf(line2, sizeof(line2), "Tilt:%d", (int)tilt);
    // normal operation
  }

  // Show on LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(line1);
  lcd.setCursor(0, 1);
  lcd.print(line2);
}

void setup() {
  Serial.begin(115200);
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Sensor Fusion");
  delay(1000);
  lcd.clear();

  Serial.println("Sensor fusion (Arduino) starting...");
  Serial.println("Simulated reads: analog A0..A5");
}

void loop() {
  readAccelerometer();
  readGyroscope();

  matrixAdd(accel, gyro, fusedMat);

  axisAverage(accel, accel_avg);
  axisAverage(gyro, gyro_avg);

  complementaryFilter(accel_avg, gyro_est, fused_axis);

  printDebug(accel_avg, gyro_avg, fused_axis);
  decideActionAndDisplay(fused_axis);

  delay(1000); // 1 second loop - tune for your use
}
