# Philosophers Project (42 School)

## Table of Contents
- [Introduction](#introduction)
- [Understanding the Problem](#understanding-the-problem)
- [Mandatory Rules](#mandatory-rules)
- [Setup & Environment](#setup--environment)
- [Project Structure](#project-structure)
- [Implementation Steps](#implementation-steps)
- [Testing & Debugging](#testing--debugging)
- [Optimization Tips](#optimization-tips)
- [Common Errors & Fixes](#common-errors--fixes)
- [Resources](#resources)

---

## Introduction
The **Philosophers** project is part of the 42 curriculum and aims to deepen your understanding of multi-threading, concurrency, and synchronization using mutexes.

## Understanding the Problem
You need to simulate the famous **Dining Philosophers Problem**, where multiple philosophers sit around a table, sharing forks. The goal is to prevent deadlocks and race conditions while ensuring all philosophers eat.

### Key Concepts:
- **Threads:** Each philosopher is a thread.
- **Mutexes:** Used to manage access to shared resources (forks).
- **Race Conditions:** Occur when multiple threads access shared data simultaneously.
- **Deadlocks:** When philosophers hold one fork and wait indefinitely for another.
- **Starvation:** When a philosopher never gets to eat due to scheduling issues.

## Mandatory Rules
- You must use **only one thread per philosopher**.
- A philosopher takes two forks to eat.
- Philosophers think, eat, and sleep in a cycle.
- Program must avoid **race conditions**, **deadlocks**, and **starvation**.

## Setup & Environment
### Requirements
- Language: **C**
- Compiler: **gcc**
- Tools: **pthread library**

### Compilation Command
```sh
cc -Wall -Wextra -Werror -pthread -o philo philo.c
```

## Project Structure
```
philosophers/
│── Makefile
│── philo.c
│── philo.h
│── utils.c
│── utils.h
│── threads.c
│── simulation.c
│── mutex.c
└── README.md
```

## Implementation Steps
### 1. Parse Input Arguments
- Number of philosophers
- Time to die
- Time to eat
- Time to sleep
- (Optional) Number of times each philosopher must eat

### 2. Initialize Structures
- Create a `t_philosopher` structure containing:
  - ID
  - Left and right forks (mutexes)
  - Last meal timestamp
  - Number of meals eaten
  - Thread reference
- Create a `t_data` structure for shared data.

### 3. Create Threads
- Use `pthread_create` to launch each philosopher as a separate thread.

### 4. Implement the Simulation Logic
- **Thinking:** Wait for forks to be available.
- **Eating:** Lock forks, update meal count, unlock forks.
- **Sleeping:** Wait for the specified sleep time.

### 5. Manage Synchronization
- Use `pthread_mutex_lock` and `pthread_mutex_unlock` to handle fork access.
- Implement a **monitoring thread** to check if a philosopher has died.

### 6. Handle Exit Conditions
- Stop simulation if a philosopher dies.
- If a maximum meal count is set, terminate once all philosophers have eaten enough times.

## Testing & Debugging
### Basic Tests
```sh
./philo 5 800 200 200
./philo 4 410 200 200
```

### Debugging Tools
- **gdb**: Debug segmentation faults.
- **valgrind**: Detect memory leaks.
- **printf**: Print thread status.

## Optimization Tips
- **Avoid busy-waiting:** Use `usleep()` for better CPU performance.
- **Minimize locking:** Only lock when necessary.
- **Reduce contention:** Assign each philosopher a unique fork order.

## Common Errors & Fixes
| Error | Cause | Fix |
|-------|-------|-----|
| Deadlock | All philosophers grab one fork | Use an odd-even approach |
| Race condition | Multiple threads modify shared data | Use mutexes |
| Starvation | Some philosophers eat less frequently | Implement fairness checks |

## Resources
- [Dining Philosophers Wiki](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
- [42 Docs](https://42docs.com/en/)
- [Pthread Library](https://man7.org/linux/man-pages/man7/pthreads.7.html)

---
Good luck! 🚀


