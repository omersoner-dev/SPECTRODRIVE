## 📱 Mobile Application – SpectroDrive Control

The SpectroDrive mobile application enables wireless control of the robot via Bluetooth (HC-05).
It provides both autonomous and interactive operation modes, along with a built-in security mechanism.

---

## 🎮 Control Modes

### 🔆 Following Mode

* The robot automatically tracks and follows a light source.
* Uses LDR-based sensing system.
* Fully autonomous behavior.

---

### 👋 Greeting Mode

* The robot performs a greeting animation using LEDs.
* Designed as a visual interaction feature.
* Can be triggered via the mobile application.

---

## 🔐 Security System

The system includes a **2-stage password protection mechanism** triggered when external interference or movement (tilt) is detected.

### 🚨 Trigger Condition

* Physical disturbance or tilt detected
* System enters security mode

---

### 🔑 Password Structure

**Password:** `6161`

#### 1️⃣ First Stage

* Stops the buzzer alarm
* Silences the warning system

#### 2️⃣ Second Stage

* Reactivates control buttons
* Restores full system functionality
* Allows the robot to receive commands again

---

## 📡 Bluetooth Communication

* Module: **HC-05**
* Communication: UART-based
* Pairing required before usage

---

## 🎯 Features Summary

* Autonomous light tracking
* Interactive greeting mode
* Bluetooth-based manual control
* Security system with dual authentication
* Real-time command execution

---

## 📥 Download

* APK File: `apk/Spectrodrive.apk`
* Alternative Download: (https://drive.google.com/file/d/1vwe7fVLtKn9J5ua9AbtXDbvv2uSjtZib/view?usp=sharing)

---

## ⚠️ Usage Notes

* Ensure Bluetooth is enabled
* Pair with HC-05 before launching the app
* In case of security lock, enter the password twice (`6161`) to regain control

---

## 🚀 Purpose

This application was developed as part of the SpectroDrive embedded robotics project to demonstrate real-time control, human interaction, and system security in a compact robotic platform.
