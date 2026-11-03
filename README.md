# 🌐 Network Connection Analyzer

### C++ | Qt5 | Advanced Data Structures

A desktop-based Network Connection Analyzer developed using **C++ and Qt5**. The application combines network connectivity testing with graph-based representation and traversal of connected devices.

## 🚀 Features

- **IP Address Detection:** Detects the current system's IP address.
- **MAC Address Detection:** Retrieves the MAC address of the active network interface.
- **Device Management:** Add devices manually.
- **Network Visualization:** Displays devices and their connections using a graphical interface.
- **Connection Management:** Create connections between devices.
- **DFS Traversal:** Performs Depth First Search on the network graph.
- **Path Checking:** Checks whether a path exists between two devices.
- **Connectivity Testing:** Checks whether an IP address is reachable using ping.
- **Latency Measurement:** Displays the response time in milliseconds.
- **Reset Function:** Clears the current network graph and device table.
- **Desktop Launcher:** Opens the GUI through a desktop shortcut with a custom globe icon.

## 🛠️ Technologies Used

- C++
- Qt5 Widgets
- Qt5 Network
- Linux / Ubuntu
- Nmap
- Git and GitHub

## 📚 Data Structures and Algorithms

| Concept | Application |
|---|---|
| Graph | Represents devices and connections |
| Adjacency List | Stores graph connections |
| Hash-based Sets | Stores neighbouring devices and visited nodes |
| Depth First Search | Traverses the network graph |
| Graph Traversal | Checks connectivity between nodes |

## 🖥️ Application Screenshots

The application provides a graphical interface containing:
- Device information table
- Network graph visualization
- Connectivity testing controls
- DFS and path-checking functionality

## ⚙️ Installation and Execution

### Requirements
- Ubuntu/Linux
- C++ compiler (g++)
- Qt5 development libraries
- Nmap

### Install dependencies

```bash
sudo apt update
sudo apt install g++ qtbase5-dev libqt5network5 nmap
```

### Clone the repository

```bash
git clone https://github.com/yuvikasaini30/Network-Connection-Analyzer.git
```

### Open the project folder

```bash
cd Network-Connection-Analyzer
```

### Compile the application

```bash
g++ gui.cpp -o NetworkGUI $(pkg-config --cflags --libs Qt5Widgets Qt5Network) -fPIC
```

### Run the application

```bash
./NetworkGUI
```

### Desktop launcher

On your configured Ubuntu desktop, the application can also be opened using the desktop shortcut. The `launch.sh` script launches the GUI.

## ⚠️ Project Scope

The scanner currently detects the local system's network interface. Additional devices and graph connections can be added manually. The graph represents configured connections and does not automatically discover the physical network topology

👩‍💻 Developer

Yuvika Saini

UID: 25BCS13336

Section: 705A

BE Computer Science and Engineering

Chandigarh University

🎓 Project Information

Subject: Advanced Data Structures

Project: Network Connection Analyzer

Academic Session: July–December 2026

Developed as an academic project to demonstrate graph data structures, traversal algorithms, network connectivity, and GUI development in C++.
