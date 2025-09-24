// cross_sensor_fusion.c  (works on PC) / .ino for Arduino (same code)
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>

#ifdef ARDUINO
  #include <Arduino.h>
  #include <LiquidCrystal.h>
  // LCD pins: RS, E, D4, D5, D6, D7  -- adjust wiring as needed
  LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
#else
  // on PC simulate delay and lcd
  #include <time.h>
  static void delay(unsigned long ms) { struct timespec ts={ms/1000, (ms%1000)*1000000}; nanosleep(&ts, NULL); }
#endif

// --- Cross-platform printing helpers ---
static void CrossPrintf(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
#ifdef ARDUINO
    // Use a small buffer and Serial.print (Arduino UNO doesn't have Serial.printf by default)
    static char buf[256];
    vsnprintf(buf, sizeof(buf), fmt, ap);
    Serial.print(buf);
#else
    vprintf(fmt, ap);
#endif
    va_end(ap);
}

// LCD print wrapper: on PC prints simulated [LCD], on Arduino writes to actual LCD
static void CrossLCDClearAndPrint(const char *line1, const char *line2) {
#ifdef ARDUINO
    lcd.clear();
    lcd.setCursor(0,0); lcd.print(line1);
    lcd.setCursor(0,1); lcd.print(line2);
#else
    printf("[LCD] %s\n", line1);
    if (line2) printf("[LCD] %s\n", line2);
#endif
}

// --- Config & thresholds ---
#define ROWS 3
#define COLS 2
#define ALPHA 0.98f            // complementary filter weight (float literal uses f)
#define TILT_THRESHOLD 15.0f   // example thresholds (units are demo-sensor units)
#define MOTION_THRESHOLD 5.0f

// --- Simulated sensor reads (PC) or actual driver should replace these ---
static void readAccelerometer(float out[ROWS][COLS], int iter) {
    // simulated pattern; in real firmware replace with driver read
    for (int i=0;i<ROWS;i++)
        for (int j=0;j<COLS;j++)
            out[i][j] = (float)( (i+1) * (j+1) * 1.0f + iter ); // simple varying values
}
static void readGyroscope(float out[ROWS][COLS], int iter) {
    for (int i=0;i<ROWS;i++)
        for (int j=0;j<COLS;j++)
            out[i][j] = (float)( (i+2) * (j+2) * 1.5f + iter*0.5f );
}

// --- Matrix operations ---
static void matrixAdd(float a[ROWS][COLS], float b[ROWS][COLS], float out[ROWS][COLS]) {
    for (int i=0;i<ROWS;i++) for (int j=0;j<COLS;j++) out[i][j] = a[i][j] + b[i][j];
}
static void axisAverage(float mat[ROWS][COLS], float avg[ROWS]) {
    for (int i=0;i<ROWS;i++) {
        float s=0.0f;
        for (int j=0;j<COLS;j++) s += mat[i][j];
        avg[i] = s / (float)COLS;
    }
}
static void complementaryFilter(float accel_avg[ROWS], float gyro_est[ROWS], float fused_out[ROWS]) {
    for (int i=0;i<ROWS;i++){
        fused_out[i] = ALPHA * accel_avg[i] + (1.0f - ALPHA) * gyro_est[i];
        gyro_est[i] = fused_out[i]; // update filter state (very simplified)
    }
}

// Decision logic -> returns a short message (max ~16 chars recommended for 16x2 LCD)
static void decideActionAndDisplay(float fused_axis[ROWS]) {
    float tilt = sqrtf(fused_axis[0]*fused_axis[0] + fused_axis[1]*fused_axis[1]);
    float maxAxis = fabsf(fused_axis[0]);
    for (int i=1;i<ROWS;i++) {
        float a = fabsf(fused_axis[i]);
        if (a > maxAxis) maxAxis = a;
    }

    char lcd_line1[17] = {0};
    char lcd_line2[17] = {0};

    if (tilt > TILT_THRESHOLD || maxAxis > (TILT_THRESHOLD * 1.2f)) {
        CrossPrintf("Decision: STOP motors (tilt=%.2f, max=%.2f)\n", tilt, maxAxis);
        snprintf(lcd_line1, sizeof(lcd_line1), "STOP MOTORS");
        snprintf(lcd_line2, sizeof(lcd_line2), "Tilt:%d",(int)tilt);
        CrossLCDClearAndPrint(lcd_line1, lcd_line2);
        // here, in real firmware call motor-stop API
    } else if (tilt > MOTION_THRESHOLD) {
        CrossPrintf("Decision: SLOW DOWN (tilt=%.2f)\n", tilt);
        snprintf(lcd_line1, sizeof(lcd_line1), "SLOW DOWN");
        snprintf(lcd_line2, sizeof(lcd_line2), "Tilt:%d",(int)tilt);
        CrossLCDClearAndPrint(lcd_line1, lcd_line2);
        // real firmware: reduce PWM
    } else {
        CrossPrintf("Decision: CONTINUE (tilt=%.2f)\n", tilt);
        snprintf(lcd_line1, sizeof(lcd_line1), "CONTINUE");
        snprintf(lcd_line2, sizeof(lcd_line2), "Tilt:%d",(int)tilt);
        CrossLCDClearAndPrint(lcd_line1, lcd_line2);
        // real firmware: normal operation
    }
}

// --- Platform entry points ---

#ifdef ARDUINO
void setup() {
    Serial.begin(115200);
    lcd.begin(16,2);
    lcd.clear();
    CrossPrintf("Sensor fusion starting...\n");
}
void loop() {
    static float accel[ROWS][COLS], gyro[ROWS][COLS], fusedMat[ROWS][COLS];
    static float accel_avg[ROWS], gyro_avg[ROWS], fused_axis[ROWS];
    static float gyro_est[ROWS] = {0.0f, 0.0f, 0.0f};
    static int iter = 0;

    readAccelerometer(accel, iter);
    readGyroscope(gyro, iter);
    matrixAdd(accel, gyro, fusedMat);

    axisAverage(accel, accel_avg);
    axisAverage(gyro, gyro_avg);

    complementaryFilter(accel_avg, gyro_est, fused_axis);

    // print debug to Serial
    CrossPrintf("Accel avg: ");
    for (int i=0;i<ROWS;i++) CrossPrintf("%.1f ", accel_avg[i]);
    CrossPrintf("\nGyro avg: ");
    for (int i=0;i<ROWS;i++) CrossPrintf("%.1f ", gyro_avg[i]);
    CrossPrintf("\nFused axis: ");
    for (int i=0;i<ROWS;i++) CrossPrintf("%.1f ", fused_axis[i]);
    CrossPrintf("\n");

    decideActionAndDisplay(fused_axis);

    iter++;
    delay(1000); // 1s loop
}
#else
int main(void) {
    float accel[ROWS][COLS], gyro[ROWS][COLS], fusedMat[ROWS][COLS];
    float accel_avg[ROWS], gyro_avg[ROWS], fused_axis[ROWS];
    float gyro_est[ROWS] = {0.0f, 0.0f, 0.0f};

    printf("Sensor fusion simulation (PC)\n\n");
    for (int iter=0; iter<5; ++iter) {
        readAccelerometer(accel, iter);
        readGyroscope(gyro, iter);
        matrixAdd(accel, gyro, fusedMat);

        axisAverage(accel, accel_avg);
        axisAverage(gyro, gyro_avg);

        complementaryFilter(accel_avg, gyro_est, fused_axis);

        printf("Accel avg: ");
        for (int i=0;i<ROWS;i++) printf("%.1f ", accel_avg[i]);
        printf("\nGyro avg:  ");
        for (int i=0;i<ROWS;i++) printf("%.1f ", gyro_avg[i]);
        printf("\nFused axis:");
        for (int i=0;i<ROWS;i++) printf("%.1f ", fused_axis[i]);
        printf("\n");

        decideActionAndDisplay(fused_axis);

        printf("\n--------------------------------\n\n");
        delay(1000);
    }
    return 0;
}
#endif
