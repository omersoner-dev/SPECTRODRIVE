## 🔧 Hardware Design – SpectroDrive

This section contains the complete hardware design of the SpectroDrive smart robot, including schematic design, PCB layout, and bill of materials.

---

### 🧠 System Overview

The hardware system is built around a microcontroller-based architecture and integrates multiple sensing and control modules:

* Light tracking sensors (LDR)
* Ultrasonic distance sensor (HC-SR04)
* Motor driver (L298N)
* Bluetooth module (HC-05)
* LCD display
* Tilt sensor and buzzer for safety alerts

---

### 📐 Schematic

![Schematic](hardware/schematic)

The schematic includes all sensor interfaces, power distribution, and control logic connections.

---

### 🧩 PCB Layout

![PCB](Images/PCB.png)

Custom PCB was designed in KiCad, including routing, footprint selection, and optimized layout for embedded system integration.

---

### 🧱 3D View

![3D](Images/3D.png)

3D visualization of the PCB showing component placement and physical structure.

---

### 📦 Bill of Materials (BOM)

The complete list of components can be found in:

* `BOM/bom.xlsx`
* `BOM/bom.csv`

---

### 🛠️ Design Tools

* KiCad (Schematic & PCB Design)
* Custom libraries for specific modules

---

### 🎯 Notes

This hardware was developed as part of a Teknofest-oriented embedded systems project, focusing on modularity, expandability, and real-world testing.

