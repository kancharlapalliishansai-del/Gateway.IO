#define TOLL_GATE_SYSTEM_H
#define TOLL_GATE_SYSTEM_H

#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <LedControl.h>

class TollGateSystem {
private:
    // Pin Allocations
    uint8_t rstPin, ssPin, servoPin;
    uint8_t irEntryPin, irExitPin;
    uint8_t greenLedPin, redLedPin, buzzerPin;

    // Peripheral Subsystems
    MFRC522 mfrc522;
    Servo tollGate;
    LiquidCrystal_I2C lcd;
    LedControl matrix;

    // State Flags & Security Database
    bool accessPermitted;
    byte authorizedUID[4];

    // System Matrices Arrays
    static const byte STOP_SIGN[8];
    static const byte GO_ARROW[8];

    // Internal Helper Methods
    bool checkAuthority(byte* scanned, byte size);
    void displayMatrixPattern(const byte pattern[8]);
    void showScanPrompt();
    void handleAccessGranted();
    void handleAccessDenied();

public:
    // Constructor
    TollGateSystem(uint8_t rst, uint8_t ss, uint8_t servo, 
                   uint8_t irEntry, uint8_t irExit, 
                   uint8_t gLed, uint8_t rLed, uint8_t buzzer,
                   uint8_t mDin, uint8_t mClk, uint8_t mCs);

    // Core Runtime Methods
    void begin();
    void update();
};

#endif

