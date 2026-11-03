# 🌐 Network Connection Analyzer

<p align="center">
  <img src="globe.png" width="120" alt="Network Connection Analyzer Globe Icon">
</p>

<h3 align="center">A Graph-Based Network Monitoring Application Built with C++ and Qt5</h3>

<p align="center">
  <img src="https://img.shields.io/badge/Language-C%2B%2B-blue">
  <img src="https://img.shields.io/badge/GUI-Qt5-green">
  <img src="https://img.shields.io/badge/Platform-Linux-orange">
  <img src="https://img.shields.io/badge/Project-Advanced%20Data%20Structures-purple">
</p>

---

## ✨ Overview

**Network Connection Analyzer** is a desktop-based application developed using C++ and Qt5. It combines network connectivity testing with graph-based device representation and traversal algorithms.

The project demonstrates how graph data structures can represent network devices and their connections through an interactive graphical interface.

## 🚀 Key Features

| Feature | Description |
|---|---|
| 🌐 IP Detection | Detects the current system's IP address |
| 🔐 MAC Detection | Retrieves the active interface's MAC address |
| 💻 Device Management | Allows users to add devices manually |
| 🔗 Network Connections | Creates connections between devices |
| 📊 Graph Visualization | Displays devices and connections visually |
| 🔍 DFS Traversal | Performs Depth First Search |
| 🛣️ Path Checking | Checks whether a path exists between devices |
| 📡 Connectivity Testing | Checks IP reachability using ping |
| ⚡ Latency Measurement | Displays response time in milliseconds |
| 🔄 Reset | Clears the current graph and device table |
| 🖥️ Desktop Launcher | Supports one-click launching with a custom icon |

## 🛠️ Technologies Used

- **C++** — Core programming language
- **Qt5 Widgets** — Graphical user interface
- **Qt5 Network** — Network interface information
- **Nmap** — Local host discovery
- **Linux / Ubuntu** — Development environment
- **Git & GitHub** — Version control

## 🧠 Data Structures & Algorithms

| Concept | Implementation |
|---|---|
| Graph | Represents network devices |
| Adjacency List | Stores device connections |
| QMap | Stores graph nodes |
| QSet | Stores neighbouring and visited nodes |
| DFS | Traverses the graph |
| Graph Search | Checks connectivity and paths |

## 🖥️ Application Interface

The application includes:

- A device information table showing IP and MAC addresses.
- A graphical network area displaying nodes and connections.
- Controls for scanning, adding devices, and connecting nodes.
- Connectivity and latency results.

## ⚙️ Installation & Setup

### 1. Install dependencies

```bash
sudo apt update
sudo apt install g++ qtbase5-dev libqt5network5 nmap
```

### 2. Clone the repository

```bash
git clone https://github.com/yuvikasaini30/Network-Connection-Analyzer.git
```

### 3. Navigate to the project

```bash
cd Network-Connection-Analyzer
```

### 4. Compile

```bash
g++ gui.cpp -o NetworkGUI $(pkg-config --cflags --libs Qt5Widgets Qt5Network) -fPIC
```

### 5. Run

```bash
./NetworkGUI
```

### 🖱️ Desktop Launching

The project also includes a `launch.sh` script for launching the GUI through a configured Linux desktop shortcut.

## ⚠️ Project Scope

The scanner currently detects the local system's active network interface. Additional devices and graph connections can be added manually.

The graph represents configured connections; it does not automatically discover the physical network topology.

## 👩‍💻 Developer

**Yuvika Saini**

- UID: `25BCS13336`
- Section: `705A`
- BE Computer Science and Engineering
- Chandigarh University

## 🎓 Academic Project

**Subject:** Advanced Data Structures

**Project Title:** Network Connection Analyzer

**Academic Session:** July–December 2026

---

<p align="center">
  <b>Built with 💙 using C++ and Qt5</b>
</p>
