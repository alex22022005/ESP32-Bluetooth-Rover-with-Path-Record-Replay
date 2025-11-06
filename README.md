# ESP32 Bluetooth Rover with Path Record & Replay

A simple ESP32-based rover that can be controlled via any Bluetooth Serial app. This project features a "record and replay" function, allowing you to save a sequence of movements and have the rover autonomously retrace its path.

---

## ✨ Features

* **Wireless Control:** Uses Bluetooth Serial (Classic) to receive commands.
* **Manual Driving:** Full remote control (Forward, Backward, Left, Right).
* **Path Recording:** Save a sequence of manual movements.
* **Path Replay:** Autonomously replay the saved sequence on command.
* **Simple Hardware:** Built for a standard 2/4-wheel drive chassis using an L298N-style motor driver.

---

## 🔧 Hardware Requirements

* ESP32 Development Board
* L298N Motor Driver (or similar 4-pin H-bridge)
* Rover chassis with 2 or 4 motors
* Power source (e.g., 7.4V LiPo or 4xAA battery pack)

---

## 🔌 Wiring

Connect your ESP32 to the motor driver's input pins.

| ESP32 Pin | Motor Driver Pin | Motor Function |
| :--- | :--- | :--- |
| **GPIO 5** | `IN1` | Motor A (Right) |
| **GPIO 18** | `IN2` | Motor A (Right) |
| **GPIO 19** | `IN3` | Motor B (Left) |
| **GPIO 21** | `IN4` | Motor B (Left) |

**Important:** Remember to connect the **GND** pin of the ESP32 to the **GND** pin of the L298N motor driver to create a common ground.

---

## 💡 How to Use

1.  Upload the `.ino` sketch to your ESP32.
2.  Power on the rover.
3.  On your smartphone or PC, scan for Bluetooth devices.
4.  Pair with the device named **"Rover"**.
5.  Open a Bluetooth Serial terminal app (like 'Serial Bluetooth Terminal' on Android).
6.  Connect to the "Rover" device from within the app.
7.  Send the commands below to control the rover.

---

## 🎮 Command List

Send a single character to control the rover:

### Manual Control
* `F` - Move Forward
* `B` - Move Backward
* `L` - Turn Left
* `R` - Turn Right

### Recording
* `S` - **Start Recording**. The rover will reply: `Recording Started`.
    * While recording, any manual move (`F`, `B`, `L`, `R`) will be executed for a fixed duration (1 second in the code) and stored as one step in the path.
* `X` - **Stop Recording**. The rover will reply: `Recording Finished`.

### Autonomous
* `A` - **Autonomous Replay**. The rover will reply: `Autonomous Mode`.
    * The rover will now execute the saved path step-by-step.
