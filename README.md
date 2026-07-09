# Pharmacy Inventory Management System

A console-based Pharmacy Inventory Management System developed in **C** using structured programming and file handling (.dat files).

Built as a Software Development Project (SDP) at **Bangladesh University of Business and Technology (BUBT)**, Department of Computer Science and Engineering.

---


> **🚧 Project Status:** Proposal approved. Development starting — currently on Increment 1 (Login System + File Structure). The folder structure below is the planned architecture; source code is being added gradually.

## 👥 Team — Three Knights

| Student ID   | Name                | Role                          |
|--------------|---------------------|-------------------------------|
| 20254103279  | Makhzum Bin Harun   | Team Leader & Core Programmer |
| 20254103269  | Md. Rafiul Islam    | Core Programmer & SQA         |
| 20254103272  | Estiak Ahmed Turnab | Core Programmer               |

**Supervised by:** Mastura Sadaf, Lecturer, Dept. of CSE, BUBT

---

## 📋 Project Overview

This system helps small pharmacies manage their daily operations through a role-based console interface. It supports two user roles — **Admin** and **Staff** — each with different levels of access.

---

## ✅ Features

- **Login System** — Admin and Staff login with file-based authentication
- **Medicine Management** — Add, view, search, update, and delete medicine records
- **Inventory Tracking** — Real-time stock tracking with low stock alerts (below 10 units)
- **Sales Management** — Sell medicine with auto stock deduction and unique Transaction IDs
- **Reports** — Inventory report, sales history report, low stock report

---

## 🔐 Role-Based Access

| Feature              | Admin | Staff                      |
|----------------------|-------|----------------------------|
| Login                | ✅    | ✅                          |
| View medicines       | ✅    | ✅                          |
| Search medicines     | ✅    | ✅                          |
| Sell medicine        | ✅    | ✅                          |
| Update stock         | ✅    | ✅                          |
| Generate reports     | ✅    | ✅                          |
| Add medicine         | ✅    | ⚠️ Requires Admin password  |
| Update medicine      | ✅    | ⚠️ Requires Admin password  |
| Delete medicine      | ✅    | ⚠️ Requires Admin password  |

---

## 🛠️ Technology Stack

- **Language:** C (C11 standard)
- **Compiler:** GCC (MinGW-w64 on Windows / GCC via apt on Linux)
- **Editor:** Visual Studio Code
- **Storage:** Binary `.dat` files (no external database)
- **Version Control:** Git & GitHub
- **OS:** Windows 10+ / Linux (tested)

---

## 📁 Project Structure
pharmacy-inventory-system/

├── src/

│   ├── main.c

│   ├── auth.c

│   ├── medicine.c

│   ├── inventory.c

│   ├── sales.c

│   └── reports.c

├── include/

│   ├── auth.h

│   ├── medicine.h

│   ├── inventory.h

│   ├── sales.h

│   └── reports.h

├── data/

│   ├── users.dat

│   ├── medicines.dat

│   └── sales.dat

├── docs/

│   └── proposal.pdf

├── .gitignore

├── Makefile

└── README.md

---

## ⚙️ How to Compile and Run

### Windows (MinGW/GCC)
```bash
gcc src/*.c -o pharmacy -Iinclude
pharmacy.exe
```

### Linux
```bash
gcc src/*.c -o pharmacy -Iinclude
./pharmacy
```

### Using Makefile
```bash
make
./pharmacy
```

---

## 📌 Development Model

Incremental Development Model — built in 4 increments:

1. Login System + File Structure
2. Medicine Management
3. Inventory & Sales
4. Reports + Integration & Testing

---

## 📄 License

This project is licensed under the MIT License. See [LICENSE](LICENSE) for details.
