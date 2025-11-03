# philosophers_42
philosophers_42

A compact, POSIX-threaded C implementation of the classical "Dining Philosophers" exercise.  
This project models philosophers who alternately think, eat and sleep while competing for forks (mutexes). It focuses on thread-safety and graceful cleanup.

## Features
- Minimal, portable C (pthread) implementation.
- Per-philosopher mutexes and shared fork mutexes.
- Watcher thread (grim onlooker) to detect dead philosophers and stop the simulation.
- Safe startup/teardown with mutex cleanup and thread joins.

## Project layout
- Source: [philo/main.c](philo/main.c), [philo/routine.c](philo/routine.c), [philo/routine_helper.c](philo/routine_helper.c), [philo/routine_helper_two.c](philo/routine_helper_two.c)
- Manager & types: [philo/philosophers.h](philo/philosophers.h)
- Thread creation & lifecycle: [philo/create_threads.c](philo/create_threads.c)
- Time utilities: [philo/get_time_of_day.c](philo/get_time_of_day.c)
- Watcher: [`grim_onlooker`](philo/grim_onlooker.c) ([implementation](philo/grim_onlooker.c))
- Mutex init/cleanup: [philo/init_mutex.c](philo/init_mutex.c), [philo/clear_mutex.c](philo/clear_mutex.c)
- Helpers & utils: [philo/utils.c](philo/utils.c), [philo/printf_error.c](philo/printf_error.c)
- Build script: [philo/Makefile](philo/Makefile)
- Compiled objects: [philo/build/](philo/build/)

## Diagrams — philosopher/fork layout

Below are small ASCII diagrams showing typical layouts and the fork indexing convention used in many implementations of the problem.

1) Circular layout (example with 5 philosophers)

```
             (F4)
        P4 ------- P0
        /             \
    (F3)              (F0)
      |     Table       |
      P3               P1
        \             /
       (F2) ------- (F1)
              P2
```

Avoiding deadlock:
Even/Odd fork-taking strategy (deadlock avoidance)
- Strategy (zero-based indexing): philosophers with even index pick up their left fork first, then their right; philosophers with odd index pick up their right fork first, then their left.
- Why it helps: this breaks the circular-wait condition (not all philosophers wait in the same order). At least one philosopher will be able to take both forks and eat, which prevents the classic deadlock where every philosopher holds one fork and waits for the other.
- Example (N = 5, zero-based):
  - P0 (even): take left (F0) → then right (F4)
  - P1 (odd):  take right (F1) → then left (F0)
  - P2 (even): take left (F2) → then right (F1)
  - ...
  In the worst case, this ordering ensures a break in this cycle.
- Notes:
  - If your code uses one-based indexing (P1..PN), adapt the rule accordingly (e.g., even/odd flips).
  - This strategy prevents the circular wait condition but does not by itself guarantee the absence of starvation; additional logic may be added if needed.


Legend:
- Px = Philosopher x (1..N or 0..N-1 depending on implementation)
- (Fx) = Fork x placed between two neighboring philosophers

2) Linear mapping with indices (5 philosophers, zero-based)

```
Philosophers:  P0   P1   P2   P3   P4
Forks:         F0   F1   F2   F3   F4
Layout:       P0--F0--P1--F1--P2--F2--P3--F3--P4--F4--(wrap to P0)
```

Common fork ownership convention (zero-based):
- Fork i sits between philosopher i and philosopher (i + 1) % N.
- Typically:
  - Philosopher i's left fork = fork i
  - Philosopher i's right fork = fork (i + N - 1) % N 
  - Or vice versa — check the source to confirm which side your code uses.

3) Example for 5 philosophers showing left/right forks for P2:

```
... P1  -- F1 --  P2  -- F2 --  P3 ...
            ^           ^
         right?       left?
```

(Interpretation depends on the code; above conventions help reason about deadlock avoidance strategies.)

## Build

From the `philo/` directory:

```sh
make
```

## Usage

Run the program as:

```sh
./philo <nbr_philo> <time_to_die_ms> <time_to_eat_ms> <time_to_sleep_ms> [num_meals]
```

Example:

Not die:
```sh
./philo 5 800 200 200
./philo 4 410 200 200 3
./philo 3 700 200 100
./philo 103 800 200 200
./philo 200 800 200 200
```

Die:
```sh
./philo 3 300 130 150
./philo 4 800 200 99999999
./philo 1 800 200 200
./philo 4 310 200 100
./philo 4 200 205 200
```

Not correct:
```sh
./philo -5 600 200 200
./philo 4 -3 200 200
./philo 4 600 -5 200
./philo 4 600 200 200 -3
```


Behaviour:
- The program prints timestamped actions such as "has taken a fork", "is eating", "is sleeping", "is thinking", and "<time> <id> dead".
- The optional `num_meals` stops the simulation when every philosopher has eaten that many times.

## Testing & Observability
- The code uses timestamps from [get_time](philo/get_time_of_day.c).
- You can enable thread sanitiser in `Makefile` for race detection (see commented flags).
- Logs are synchronised via the `printf` mutex to keep output readable.

## Cleanup
Use the Makefile targets:
```sh
make clean   # remove object files
make fclean  # remove executable and object files
make re      # rebuild
```

## Contributing
Pull requests and issues are welcome. When contributing:
- Keep changes minimal and thread-safe.
- Run with sanitiser flags if changing synchronisation logic.

## License
Choose and add a license file if you plan to publish (e.g., MIT / Apache-2.0).

---
