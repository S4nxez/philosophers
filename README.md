# Philosophers Project

A C implementation of the classic dining philosophers problem using pthreads and mutexes.

## Project Structure

```
.
├── Makefile
├── include/
│   └── philo.h          # Header file with structures and function declarations
├── src/
│   ├── main.c           # Main program logic and thread management
│   ├── philo_functions.c # Philosopher behavior functions (eat, think, sleep)
│   ├── utils.c          # Utility functions for printing and timing
│   ├── ft_atoi.c        # String to integer conversion
│   └── is_number.c      # Input validation functions
└── obj/                 # Compiled object files
```

## Current Implementation

The project currently includes:

- **Main Program** (src/main.c): Handles argument parsing, philosopher thread creation and management
- **Philosopher Functions** (src/philo_functions.c): Core philosopher behaviors (eating, thinking, sleeping)
- **Utilities** (src/utils.c): Helper functions for timestamped output
- **Data Structures** (include/philo.h): Definitions for philosopher and program parameters

### Key Functions

- `launch_philo`: Creates and launches individual philosopher threads
- `philo_functions`: Main philosopher routine executed by each thread
- `philo_print`: Thread-safe printing with timestamps
- `parse_input`: Validates command line arguments

## Usage

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### Parameters:
- `number_of_philosophers`: Number of philosophers (max 200)
- `time_to_die`: Time in milliseconds before a philosopher dies of starvation
- `time_to_eat`: Time in milliseconds a philosopher takes to eat
- `time_to_sleep`: Time in milliseconds a philosopher sleeps
- `number_of_times_each_philosopher_must_eat`: Optional parameter for meal limit

## Planned Strategy

The solution will implement a **3-turn rotation system** to prevent deadlocks and ensure fair resource allocation:

### Turn-Based Eating Strategy

1. **Turn Division**: Philosophers are divided into 3 groups based on their index:
   - Turn 1: Philosophers 1, 4, 7, 10, ...
   - Turn 2: Philosophers 2, 5, 8, 11, ...
   - Turn 3: Philosophers 3, 6, 9, 12, ...

2. **Rotation Cycle**:
   - **Phase 1**: Turn 1 eats → Turn 2 & 3 sleep
   - **Phase 2**: Turn 1 thinks → Turn 2 eats → Turn 3 sleeps
   - **Phase 3**: Turn 1 sleeps → Turn 2 thinks → Turn 3 eats
   - **Phase 4**: Turn 1 eats → Turn 2 sleeps → Turn 3 thinks
   - **Repeat**: Go back to phase 2

3. **Benefits**:
   - Prevents circular wait conditions
   - Ensures all philosophers get equal eating opportunities
   - Maintains proper synchronization without complex locking mechanisms
   - Scalable to any number of philosophers

This approach guarantees that no philosopher will starve while maintaining the philosophical problem's constraints.

## Current Status

- ✅ Basic thread creation and management
- ✅ Command line argument parsing
- ✅ Basic philosopher actions (eat, think, sleep)
- ✅ Timestamped logging system
- 🔄 **In Progress**: Mutex implementation for forks
- ⏳ **Pending**: Death detection mechanism
- ⏳ **Pending**: Meal counting system

## Building

Use the provided Makefile to compile the project:

```bash
make
```

This will generate the `philo` executable in the project root directory.

## Testing

Example execution:

```bash
./philo 5 800 200 200 7
```

This runs 5 philosophers with:
- 800ms time to die
- 200ms eating time
- 200ms sleeping time
- Each philosopher must eat 7 times (optional)

## Known Issues

- Memory leaks in thread argument allocation (to be fixed)
- Race conditions in output printing (implementing mutex locks)
- No death detection mechanism yet implemented

## Next Steps

1. Implement mutex locks for fork synchronization
2. Add death detection monitoring thread
3. Implement the 3-turn rotation strategy
4. Add proper memory cleanup
5. Optimize timing precision with `usleep()` instead of `sleep()`
