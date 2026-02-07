_This project was created as part of the 42 curriculum by dansanc3_

# Philosophers (Dining Philosophers) — 42 Project

## Description

This repository contains a C implementation of the classic "dining philosophers"
problem using `pthread` and `mutex`. The goal is to coordinate concurrency among
multiple threads (philosophers) that share limited resources (forks), avoiding
race conditions and deadlocks while detecting starvation (deaths) according to
time parameters.

Quick overview:

- Each philosopher is a thread that repeats the cycle: take forks → eat →
  sleep → think.
- Forks are protected with `pthread_mutex_t`.
- There is a per-philosopher death detector that watches `time_to_die`.
- The program supports an optional parameter to limit the number of meals.

## Usage

Minimum requirements:

- `gcc` on a POSIX-compatible environment (WSL on Windows is recommended)
- `make` (optional, a `Makefile` is included)

Build (from the repository root):

```bash
make
```

If you don't have `make` you can compile manually:

```bash
gcc -Wall -Wextra -Werror -g3 -Iinclude/ src/*.c -lpthread -o philo
```

Run:

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [max_meals]
```

Arguments:

- `number_of_philosophers` — number of philosophers (max 200 by input validation)
- `time_to_die` — time in ms before a philosopher dies without eating
- `time_to_eat` — time in ms a philosopher spends eating
- `time_to_sleep` — time in ms a philosopher spends sleeping
- `max_meals` — (optional) number of times each philosopher must eat; if
  provided the simulation ends when every philosopher reaches this count

Windows recommendation: run under WSL for pthread compatibility and a POSIX
environment.

Examples:

```bash
./philo 4 410 200 200
./philo 4 410 200 200 7   # finishes when each philosopher has eaten 7 times
```

## Resources

Recommended reading on the problem and concurrency:

- Classic reference: Dijkstra, "Dining Philosophers Problem" (1971)
- Pthreads documentation: https://man7.org/linux/man-pages/man7/pthread.7.html
- Tutorials on concurrency in C and mutex usage
- Philosophers guide: https://medium.com/@ruinadd/philosophers-42-guide-the-dining-philosophers-problem-893a24bc0fe2

## Project structure

```text
. /
├── Makefile
├── README.md
├── include/
│   └── philo.h
├── src/
│   ├── ft_atoi.c
│   ├── is_number.c
│   ├── main.c
│   ├── main_helpers.c
│   ├── forks.c
│   ├── philo_functions.c
│   ├── starving.c
│   ├── utils.c
│   └── clean.c
└── obj/
```

## Current status

- ✅ Builds on WSL with `gcc` and `-lpthread`
- ✅ Death detection and optional meal counting implemented
- ✅ Manual tests for critical odd/even scenarios performed
- ✅ Code formatted and validated with Norminette

If you want additional documentation (debugging steps, sample logs, or how
to run with `valgrind`), tell me what to include and I'll add it.
_This project was created as part of the 42 curriculum by dansanc3, S4nxez._

# Philosophers (Dining Philosophers) — 42 Project

## Description

This repository contains a C implementation of the classic "dining philosophers"
problem using `pthread` and `mutex`. The goal is to coordinate concurrency among
multiple threads (philosophers) that share limited resources (forks), avoiding
race conditions and deadlocks while detecting starvation (deaths) according to
time parameters.

Quick overview:

- Each philosopher is a thread that repeats the cycle: take forks → eat →
  sleep → think.
- Forks are protected with `pthread_mutex_t`.
- There is a per-philosopher death detector that watches `time_to_die`.
- The program supports an optional parameter to limit the number of meals.

## Usage

Minimum requirements:

- `gcc` on a POSIX-compatible environment (WSL on Windows is recommended)
- `make` (optional, a `Makefile` is included)

Build (from the repository root):

```bash
make
```

If you don't have `make` you can compile manually:

```bash
gcc -Wall -Wextra -Werror -g3 -Iinclude/ src/*.c -lpthread -o philo
```

Run:

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [max_meals]
```

Arguments:

- `number_of_philosophers` — number of philosophers (max 200 by input validation)
- `time_to_die` — time in ms before a philosopher dies without eating
- `time_to_eat` — time in ms a philosopher spends eating
- `time_to_sleep` — time in ms a philosopher spends sleeping
- `max_meals` — (optional) number of times each philosopher must eat; if
  provided the simulation ends when every philosopher reaches this count

Windows recommendation: run under WSL for pthread compatibility and a POSIX
environment.

Examples:

```bash
./philo 4 410 200 200
./philo 4 410 200 200 7   # finishes when each philosopher has eaten 7 times
```

## Resources

Recommended reading on the problem and concurrency:

- Classic reference: Dijkstra, "Dining Philosophers Problem" (1971)
- Pthreads documentation: https://man7.org/linux/man-pages/man7/pthread.7.html
- Tutorials on concurrency in C and mutex usage

AI assistance used in this project:

- AI (ChatGPT) was used to assist with analysis, debugging and small
  refactorings aimed at fixing synchronization bugs and making the code
  compliant with the Norminette style rules. The AI helped review execution
  flow, propose fixes for race conditions, implement a more precise
  `ft_usleep`, and simplify initialization to reduce function parameters.
  No core algorithmic behavior (fork-taking/releasing logic or death detection)
  was conceptually changed; edits were minimal and documented in commit
  messages.

## Project structure

```text
. /
├── Makefile
├── README.md
├── include/
│   └── philo.h
├── src/
│   ├── ft_atoi.c
│   ├── is_number.c
│   ├── main.c
│   ├── main_helpers.c
│   ├── forks.c
│   ├── philo_functions.c
│   ├── starving.c
│   ├── utils.c
│   └── clean.c
└── obj/
```

## Current status

- ✅ Builds on WSL with `gcc` and `-lpthread`
- ✅ Death detection and optional meal counting implemented
- ✅ Manual tests for critical odd/even scenarios performed
- ✅ Code formatted and validated with Norminette

If you want additional documentation (debugging steps, sample logs, or how
to run with `valgrind`), tell me what to include and I'll add it.
