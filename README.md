# 💼 Employee Payroll System (C Mini Project)

## 📌 Project Overview

The **Employee Payroll System** is a mini project developed in the C programming language.
It is designed to manage employee salary details, compute payroll, and generate payslips.

This project demonstrates the use of:

* Structures
* File handling
* Functions
* Menu-driven programming

---

## 🎯 Objectives

* To store and manage employee data efficiently
* To calculate salary components like gross pay, tax, and net pay
* To generate a payslip for individual employees
* To implement file operations (save and load data)

---

## ⚙️ Features

✔ Add Employee (ID, Name, Basic Pay, OT Hours)
✔ Calculate Gross Salary
✔ Apply Tax Deduction (based on salary slabs)
✔ Calculate Net Salary
✔ Display All Employees
✔ Generate Payslip for a given Employee ID
✔ Save Records to File
✔ Load Records from File

---

## 🧮 Salary Calculation Logic

* **Gross Pay** = Basic Pay + (OT Hours × OT Rate)
* **Tax Rules**:

  * If Gross > 50000 → 20% tax
  * If Gross > 30000 → 10% tax
  * Otherwise → No tax
* **Net Pay** = Gross Pay − Tax

---

## 🛠️ Technologies Used

* C Programming Language
* Emscripten (for WebAssembly compilation)
* HTML & JavaScript (auto-generated for browser execution)

---

## ▶️ How to Run the Project

### 🔹 Method 1: Run as Normal C Program

1. Compile using GCC:

   ```
   gcc main.c -o payroll
   ```
2. Run:

   ```
   ./payroll
   ```

---

### 🔹 Method 2: Run in Browser (WebAssembly)

1. Compile using Emscripten:

   ```
   emcc main.c -o index.html -sASYNCIFY -sALLOW_MEMORY_GROWTH
   ```
2. Start server:

   ```
   python -m http.server 8000
   ```
3. Open browser:

   ```
   http://localhost:8000/index.html
   ```

---

## 📂 Project Structure

```
Employee-Payroll-System/
│
├── main.c
├── index.html
├── index.js
├── index.wasm
└── README.md
```

---

## ⚠️ Limitations

* File handling may not fully work in browser environment
* Uses basic console-based input/output
* Limited to fixed number of employees (array-based storage)

---

## 🚀 Future Enhancements

* Convert to graphical/web-based interface
* Use database instead of file storage
* Add search, update, and delete features
* Improve UI/UX

---

## 👨‍💻 Author

**Yogesh S**

---

## 📜 Conclusion

This project provides a clear understanding of payroll processing using C programming.
It demonstrates core programming concepts and real-world application logic.

---
