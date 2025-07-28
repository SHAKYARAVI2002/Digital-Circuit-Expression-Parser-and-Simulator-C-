# Digital Circuit Expression Parser and Simulator (C++)

This project simulates a digital logic circuit using boolean expressions as input. It supports expressions like `A AND (B OR C)` and evaluates them for all binary combinations of inputs (A, B, C), generating the corresponding truth table.

## 🔧 Features
- Parses logical expressions in **infix notation**
- Converts to **postfix (Reverse Polish Notation)** using a stack
- Evaluates logic using truth values of variables (A, B, C)
- Generates complete **truth table**
- Supports operators: `AND`, `OR`, `NOT`, and parentheses

## 🚀 Technologies
- **C++**
- **Stacks / Expression Parsing**
- **Digital Logic Simulation**
- Aligns with EDA concepts and Siemens’ job role focus on software for electronic design

## ▶️ How to Run
1. Compile using any C++ compiler:
   ```bash
   g++ circuit_simulator.cpp -o circuit_simulator
   ./circuit_simulator
