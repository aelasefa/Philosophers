
# 🧠 Philosophers - 42 Project

## 📌 Project Description

The **Dining Philosophers** problem is a classic concurrency exercise. The goal is to create a simulation where multiple philosophers sit at a table, alternating between **thinking**, **eating**, and **sleeping**, without causing deadlocks or starvation.

This project uses **POSIX threads (pthreads)** and **mutexes** to handle synchronization.

---

## 🧩 Program Arguments

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

- `number_of_philosophers`: Number of philosophers (and forks)
- `time_to_die`: Time (ms) a philosopher can live without eating
- `time_to_eat`: Time (ms) a philosopher takes to eat
- `time_to_sleep`: Time (ms) a philosopher takes to sleep
- `number_of_times_each_philosopher_must_eat` (optional): End the simulation once all philosophers have eaten at least this many times

---

## 📁 File Structure

- **main.c** — Parses arguments, initializes data, starts threads.
- **init.c** — Initializes mutexes and philosopher structures.
- **philo.c** — Thread routine: philosopher actions (think, eat, sleep).
- **monitor.c** — Background thread that checks if a philosopher dies.
- **utils.c** — Time and helper functions.
- **philo.h** — All shared structures and function declarations.

---

## 🔧 Key Structs

### `t_input`

Shared data between all philosophers:
```c
typedef struct s_input {
    int nbr_philo;
    int die_time;
    int eat_time;
    int sleep_time;
    int count_eat;
    int is_dead;
    long long start_time;
    pthread_mutex_t *forks;
    pthread_mutex_t print_lock;
    pthread_mutex_t death_lock;
    struct s_philo *philos;
} t_input;
```

### `t_philo`

Individual philosopher data:
```c
typedef struct s_philo {
    int id;
    int meals_eaten;
    long long last_meal_time;
    pthread_t thread;
    pthread_mutex_t *l_fork;
    pthread_mutex_t *r_fork;
    t_input *input;
} t_philo;
```

---

## 💡 Logic Summary

1. Initialize input data and mutexes.
2. Create a thread for each philosopher.
3. Philosophers follow this routine:
   - Think
   - Take forks
   - Eat
   - Release forks
   - Sleep
4. A monitor thread checks for dead philosophers.
5. Exit simulation on death or when all have eaten (optional case).

---

## ✅ Bonus Tips

- Use `gettimeofday` or `clock_gettime` for timing.
- Use `usleep` to prevent busy waiting.
- Protect shared data with mutexes (`is_dead`, `printf`, etc.)

---

## 🧪 Example Usage

```bash
./philo 5 800 200 200
```

Simulates 5 philosophers with:
- 800ms to live without eating
- 200ms to eat
- 200ms to sleep

---

Happy threading! 🚀
