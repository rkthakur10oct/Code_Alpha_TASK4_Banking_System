# 🏦 Banking System – C++ Project

A console-based Banking System written in C++ that supports customer account management, deposit/withdrawal, fund transfers, and transaction history. It also ensures automatic creation and storage of data in a dedicated `data/` directory.

---

## 📌 Features

- ✅ Create and manage customers and bank accounts
- 💰 Deposit and Withdraw funds
- 🔁 Fund Transfer between accounts
- 📜 View detailed transaction history
- 📄 Display account balance and profile info
- 🗃️ Auto-creates and saves data in `data/` folder
- 🧾 Stores all customer and transaction data in `.txt` files

---

## 💻 Technologies Used

- **Language:** C++
- **Standard:** C++17 (for filesystem support)
- **Storage:** File-based storage using `.txt` files
- **Platform:** Cross-platform (Windows, Linux)

---

## 🔧 How to Compile

Make sure you have a C++17-compliant compiler.

```bash
g++ banking_system.cpp -o banking_system -std=c++17
