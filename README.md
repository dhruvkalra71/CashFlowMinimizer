# 💸 Lean Ledger - Cash Flow Minimizer

> **"What if splitting group expenses or settling dues was no longer a headache?"**

Introducing the **Lean Ledger** – a smart, algorithm-powered cash flow minimizer designed to reduce clutter in financial settlements by intelligently minimizing the number of transactions required.

![Lean Ledger Banner](https://i.imgur.com/SxHqhRv.png) <!-- Replace with actual image path -->

---

## 🧩 Problem

In group transactions (trips, clubs, societies, or shared expenses), it's common to track who owes whom. But when it comes time to settle, multiple overlapping debts lead to inefficient payment chains.

👎 *Manually managing debts leads to:*

* Multiple redundant transactions
* Confusing settlements
* Wasted time and effort

---

## 💡 Solution

The **Cash Flow Minimizer** is a smart ledger that simplifies group settlements by:

* 🔁 **Reducing total transactions** needed to settle all debts.
* 📊 **Tracking all participants, payment modes, and transaction histories**.
* ⚙️ **Applying graph theory** and the **Net Amount Algorithm** for optimal settlement.
* 💾 Fully implemented in **C++** using **file handling**, **classes**, and **graphs**.

---

## 💡 Key Features

| Feature                    | Description                                                    |
| -------------------------- | -------------------------------------------------------------- |
| 🔄 Cash Flow Minimization  | Reduces transactions using net-balancing logic                 |
| 👥 Participant Management  | Add, delete, view, and edit members and their payment methods  |
| 📄 Transaction Handling    | Record, edit, delete, and sort transaction logs                |
| 📈 Sorted Display          | Alphabetical sorting of users, descending sort of transactions |
| 💳 Custom Payment Modes    | Allows multiple payment types per participant                  |
| 💾 Persistent File Storage | Binary file handling for efficient record storage              |

* 👤 Add/Delete/Edit participants
* 💰 Record/Edit/Delete transactions
* 🧾 Display transaction histories (sorted/unsorted)
* 🔃 Minimize total transactions to settle all debts
* 💳 Manage multiple payment modes per user
* 🧠 Uses graph theory for **cash flow minimization**
* 🔐 Stored locally using efficient binary file handling

---

## 🏗️ System Architecture

### 📌 Class Diagram

![Class Diagram](https://i.imgur.com/2cNj9VV.png) <!-- Replace with actual image from PDF -->

### ⚙️ Data Structures & Algorithms

* **Participant Class**: Stores user info and allowed payment modes.
* **Transaction Class**: Stores individual debt relations.
* **Graph-based Adjacency Matrix**: Models debts between participants for optimization.
* **Set & Map**: For tracking payment types and indexing users.
* **Greedy Net Amount Minimization Algorithm**

```cpp
struct Participant {
    string name;
    string username;
    vector<string> paymentModes;
};

struct Transaction {
    string payee;
    string debtor;
    float amountPaid;
};
```

---

## ⚙️ Algorithms & Logic

### 🔍 Cash Flow Minimization Algorithm

1. Compute net balance for each participant.
2. Use a **graph** to represent debts.
3. Apply a **greedy strategy** to transfer maximum amount between debtors and creditors using **shared payment modes**.
4. Output the optimal list of settlements.

### 📈 Time & Space Complexity

| Operation              | Time Complexity | Space Complexity |
| ---------------------- | --------------- | ---------------- |
| Sorting Records        | O(n log n)      | O(n)             |
| Cash Flow Minimization | O(V²)           | O(V²)            |

---

## 📸 Output Screenshots

### 🧾 Recorded Transactions

![Transactions Output](https://i.imgur.com/qmIEgQ4.png) <!-- Replace with actual image -->

### 🔁 Minimized Cash Flow Summary

![Minimized Flow](https://i.imgur.com/l3dkT3N.png) <!-- Replace with actual image -->

---

## 🚀 Getting Started

### 🔧 Prerequisites

* C++ compiler (GCC/Visual Studio)
* Terminal (Linux/macOS/Windows)
* IDE: VS Code / Code::Blocks / DevC++

### ▶️ Compile and Run

```bash
g++ cash-flow-minimizer-main.cpp -o CashFlowMinimizer
./CashFlowMinimizer
```

---

## 🧪 Example Use Cases

* Splitting expenses during trips
* Managing shared society funds
* Peer-to-peer micro lending groups
* Expense tracking in small startups or events

---

## 📍 Future Scope

* 🌐 Web/GUI front-end (Qt or React)
* 🔌 API + Payment Gateway Support
* 🔐 Add authentication and role-based access
* ☁️ Cloud backup and multi-device sync
* 📱 Mobile App Port (Flutter/React Native)




> *Streamline Group Expenses with Intelligence & Automation*

![Banner](https://raw.githubusercontent.com/your-repo/banner.png) <!-- Optional banner if available -->

---

## 🛠️ System Overview

### 📊 UML Class Diagram

![Class Diagram](sandbox:/mnt/data/pdf_images/image_6_1.png)

---

## 📈 Screenshots & Outputs

### 💡 Interactive Terminal Menu

![Menu](sandbox:/mnt/data/pdf_images/image_1_1.png)

---

### 🧾 Adding a Participant

![Add Participant](sandbox:/mnt/data/pdf_images/image_8_1.png)

---

### 💸 Recording Transactions

![Record Transactions](sandbox:/mnt/data/pdf_images/image_9_1.png)

---

### 📄 Transaction History

![Transactions](sandbox:/mnt/data/pdf_images/image_9_2.png)

---

### 📉 Sorted Transactions

![Sorted Transactions](sandbox:/mnt/data/pdf_images/image_9_3.png)

---

### ⚖️ Optimized Cash Flow Output

![Minimized Transactions](sandbox:/mnt/data/pdf_images/image_10_5.png)

---

