# Gateway.IO
# GateWay.IO — Automated RFID Toll Gate System 🛣️🤖

An intelligent, state-driven automated toll booth system built using the Arduino ecosystem. This project integrates RFID vehicle identification, a dual-IR sensor state machine for dynamic physical entry/exit handling, and an I2C LCD human-machine interface.

---

## ⚙️ Key Features
- **Secure Authentication:** Utilizes the RC522 RFID module (SPI protocol) for reliable, non-contact vehicle verification.
- **Dynamic Queue Management:** Implements dual-IR sensors to track vehicle positioning, keeping the barrier open *only* while a vehicle is crossing.
- **I2C Reduced-Pin Display:** Displays contextual alerts ("Access Granted", "Drive Forward", countdowns) using a 16x2 LCD requiring just 2 data pins.
- **Audio-Visual Feedback:** Integrated active buzzers and distinct status LEDs for rapid debugging and real-world safety compliance.

---

## 🛠️ Components List
- **Microcontroller:** Arduino Uno R3
- **RFID Module:** MFRC522 (13.56 MHz)
- **Actuator:** SG90 / MG996R Servo Motor
- **Sensors:** 2x Active-Low Infrared (IR) Obstacle Avoidance Sensors
- **Display:** 16x2 Character LCD with I2C Backpack Module
- **Indicators:** High-brightness LEDs (Red/Green), 5V Active Buzzer

---

## 🔌 Circuit Topology & Pin Mapping

### 1. RFID MFRC522 Connection (SPI)
| MFRC522 Pin | Arduino Uno Pin | Description |
| :--- | :--- | :--- |
| **VCC** | 3.3V | Main Power (Strictly 3.3V) |
| **RST** | Pin 9 | System Reset |
| **GND** | GND | Common Ground |
| **MISO** | Pin 12 | Master In Slave Out |
| **MOSI** | Pin 11 | Master Out Slave In |
| **SCK** | Pin 13 | Serial Clock |
| **SDA (SS)**| Pin 10 | Slave Select |

### 2. Peripherals & Sensor Arrays
- **I2C LCD Display:** `SDA` ➔ Pin A4 | `SCL` ➔ Pin A5
- **IR Sensors:** `Entry Sensor` ➔ Pin 2 | `Exit Sensor` ➔ Pin 4
- **Servo Motor:** `Signal Pin` ➔ Pin 3 (PWM)
- **Alerts:** `Green LED` ➔ Pin 5 | `Red LED` ➔ Pin 6 | `Buzzer` ➔ Pin 7

---

## 💻 Logic Flow & State Diagram

The firmware operates on a simple state machine to prevent unauthorized tailgating or early gate closure:

1. **STANDBY State:** Red LED is active. The LCD prompts for an RFID scan.
2. **VERIFICATION State:** Card scanned. Matches stored Hex UID?
   - *No* ➔ Trigger alert frequency on Buzzer, flash Red LED, return to standby.
   - *Yes* ➔ Transition to Authorized State. Switch to Green LED.
3. **ENTRY TRIP State:** Wait until vehicle triggers `IR_ENTRY`. Swing servo barrier $90^\circ$.
4. **EXIT & CLEAR State:** Loop locks inside code while vehicle transitions to `IR_EXIT`. The gate remains fully open until the exit sensor reads `HIGH` again (vehicle completely cleared).
5. **RESET State:** Lower servo to $0^\circ$, clear memory flags, revert back to Standby.

---

## 🚀 Getting Started

### Prerequisites
Ensure the following libraries are installed in your Arduino IDE:
- `MFRC522` by Miguel Balboa
- `LiquidCrystal_I2C` by Frank de Brabander
- `Servo` (Built-in)

### Installation
1. Clone this repository:
   ```bash
   git clone [https://github.com/YOUR_USERNAME/GateWay.IO.git](https://github.com/YOUR_USERNAME/GateWay.IO.git)
   
