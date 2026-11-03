# 🌐 Network Connection Analyzer

### 💻 Advanced Data Structures Project | C++ & Qt5

![C++](https://img.shields.io/badge/Language-C++-blue?style=for-the-badge&logo=cplusplus)
![Qt](https://img.shields.io/badge/GUI-Qt5-green?style=for-the-badge&logo=qt)
![Data Structure](https://img.shields.io/badge/Data_Structure-Graph-orange?style=for-the-badge)
![Algorithm](https://img.shields.io/badge/Algorithm-DFS-purple?style=for-the-badge)
![Platform](https://img.shields.io/badge/Platform-Linux-lightgrey?style=for-the-badge)

---

## 📌 About The Project

The **Network Connection Analyzer** is a C++ desktop application developed using **Qt5 Widgets**.

It simulates a computer network using a **Graph Data Structure**, where devices are represented as vertices and connections are represented as edges.

The application allows users to create and visualize network connections, perform Depth First Search (DFS), check connectivity between devices, and find possible routes.

It demonstrates how graph algorithms can be used to represent and analyze network structures.

---

## ✨ Features

| Feature | Description |
|---|---|
| ➕ Add Device | Add network devices such as routers, laptops and servers |
| 🔗 Connect Devices | Create connections between devices |
| 📊 Network Visualization | View the network topology graphically |
| 🔍 DFS Traversal | Explore connected devices using DFS |
| 🛣️ Path Detection | Check whether a route exists between two devices |
| 🟡 Path Highlighting | Highlight the discovered route visually |
| 🔄 Reset Network | Clear the existing network |

---

## 🧠 Data Structures & Algorithms Used

### 🌐 Graph Data Structure

A graph represents the network.

- **Vertices:** Network devices
- **Edges:** Connections between devices
- **Representation:** Adjacency structure using `QMap` and `QSet`
- **Graph Type:** Undirected Graph

Example network:

```text
       Router
       /    \
   Laptop   Server
      |        |
   Mobile   Printer
```

### 🔍 Depth First Search (DFS)

DFS is used to explore the network starting from a selected device.

It visits a device, marks it as visited and recursively explores its unvisited neighbours.

### 🛣️ Path Finding

The application uses recursive graph traversal with backtracking to find a route between a source and destination device.

A discovered route is displayed and highlighted in yellow.

---

## 🖥️ Project Screenshots

### Network Visualization
![Network Connection Analyzer](Screenshot%20from%202026-11-03%2013-38-12.png)

---

## ⚙️ Technologies Used

- C++
- Qt5 Widgets
- Graph Data Structure
- QMap and QSet
- Depth First Search
- Recursive Algorithms

---

## 🚀 How to Run

### Option 1: Download the Application

1. Open the Releases section.
2. Download `NetworkGUI`.
3. Open Terminal in the Downloads folder.
4. Execute:

```bash
chmod +x NetworkGUI
./NetworkGUI
```

### Option 2: Compile From Source

Install the Qt5 development packages, then run:

```bash
g++ gui.cpp -o NetworkGUI $(pkg-config --cflags --libs Qt5Widgets) -fPIC
```

Launch the application:

```bash
./NetworkGUI
```

---

## 📥 Download

**[⬇️ Download Network Connection Analyzer v1.0](https://github.com/yuvikasaini30/Network-Connection-Analyzer/releases/tag/v1.0)**

---

## 📂 Source Code

**[View Project Repository on GitHub](https://github.com/yuvikasaini30/Network-Connection-Analyzer)**

---

## 👩‍💻 Developer

**Yuvika Saini**

- UID: 25BCS13336
- Section: 705A
- Program: B.E. Computer Science and Engineering
- Semester: 3rd

---

⭐ *Developed as an academic project to demonstrate Graph Data Structures and DFS Traversal.*
