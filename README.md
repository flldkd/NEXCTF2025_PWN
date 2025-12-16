# NEX Team CTF 2025 Challenges
README是我用ai生成的，内容是我出的pwn方向的题目和尝试的量子方向题目和对应的题解，用于25年校赛

Welcome to the official repository for the **NEX Team CTF 2025**. This repository contains the source code, deployment environments, and exploit scripts for the challenges authored by me for the competition.

The challenges primarily focus on **Binary Exploitation (Pwn)** and **Quantum Computing**.

## 📂 Repository Structure

```text
.
├── Pwn/
│   ├── Stack Overflow
│   │   ├── ret2text / ret2text2   # Basic stack overflow
│   │   └── ret2libc / ret2libc2   # ROP chains, libc address leaking
│   ├── Format String
│   │   ├── fmt1                   # Basic format string vulnerabilities
│   │   ├── fmt2                   # Advanced writes
│   │   └── fmt3                   # Complex exploitation
│   ├── Shellcode
│   │   ├── shellcode              # Shellcode injection techniques
│   │   └── shellcode2
│   ├── Logic & C++
│   │   └── sudoku_1               # C++ logic vulnerability (Sudoku game)
│   └── Tools & Debugging
│       ├── gdb_challenge          # GDB usage and anti-debugging skills
│       └── study_gdb
├── Quantum/
│   ├── quantum_1
│   ├── quantum_2
│   └── quantum_3
└── ...
```

## 🛡️ Pwn Challenges

The Pwn challenges are designed to cover a wide range of exploitation techniques, from basic buffer overflows to advanced heap or logic bugs.

### Deployment (Docker)

Most Pwn challenges in this repository come with a `docker-compose.yml` file. You can easily deploy them locally for testing.

**Prerequisites:**
- Docker
- Docker Compose

**How to run a challenge:**

1. Navigate to the challenge directory (e.g., `fmt1`):
   ```bash
   cd fmt1
   ```

2. Start the container:
   ```bash
   docker-compose up -d
   ```

3. Connect to the challenge:
   ```bash
   nc 127.0.0.1 <port>
   ```
   *(Check `docker-compose.yml` or `ctf.xinetd` to confirm the exposed port)*

### Challenge Descriptions

| Category | Challenge Name | Description |
| :--- | :--- | :--- |
| **Stack** | `ret2text` / `ret2text2` | Introduction to stack buffer overflows and control flow hijacking. |
| **Stack** | `ret2libc` / `ret2libc2` | Bypassing NX bit using Return Oriented Programming (ROP) and Ret2Libc attacks. |
| **Fmt Str** | `fmt1` - `fmt3` | Progressive difficulty challenges focusing on Format String vulnerabilities (Leaking memory, Arbitrary Write). |
| **Shellcode** | `shellcode1` / `shellcode2` | Challenges requiring the crafting and injection of custom shellcode into executable segments. |
| **Logic** | `sudoku_1` | A C++ based Pwn challenge involving game logic (Sudoku) vulnerabilities. |
| **Misc** | `gdb_challenge` | A challenge designed to test and improve your dynamic debugging skills with GDB. |

> **Note:** Exploit scripts (`exp.py`) are included in most directories for educational purposes.

## ⚛️ Quantum Challenges

A series of challenges exploring the fundamentals of Quantum Computing, likely involving Qiskit or similar frameworks.

- **quantum_1**: Introduction to quantum circuits and gates.
- **quantum_2**: Intermediate quantum algorithms.
- **quantum_3**: Advanced quantum logic or cryptography.

## ⚠️ Disclaimer

These challenges are for **educational purposes only**. The code and exploits contained in this repository should only be used in authorized Capture The Flag (CTF) environments or for personal research.

## ✍️ Author

**NEX Team**
*2025*

