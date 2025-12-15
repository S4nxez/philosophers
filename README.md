# Philosophers Project

A C implementation of the classic dining philosophers problem using pthreads and mutexes.

## Project Structure

```
.
├── Makefile
├── include/
│   └── philo.h           # Header file with structures and function declarations
├── src/
│   ├── main.c            # Main program logic and thread management
│   ├── philo_functions.c # Philosopher behavior functions (eat, think, sleep)
│   ├── utils.c           # Utility functions for printing and timing
│   ├── ft_atoi.c         # String to integer conversion
│   ├── starving.c        # Starving detection functions
│   └── is_number.c       # Input validation functions
└── obj/                  # Compiled object files
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

## Current Status

- ✅ Basic thread creation and management
- ✅ Command line argument parsing
- ✅ Basic philosopher actions (eat, think, sleep)
- ✅ Timestamped logging system
- ✅ Mutex implementation for forks
- 🔄 **Pending**: Death detection mechanism
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

1. Add death detection monitoring thread
2. Add proper memory cleanup
3. Optimize timing precision with `usleep()` instead of `sleep()`
