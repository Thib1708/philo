# Project Philosophers

Philosophers is a project that simulates the classic dining philosophers problem in concurrent programming. The goal is to implement a solution that allows multiple philosophers to share a table with limited resources (forks) and avoid deadlock and starvation. This README provides instructions on installing, using, and understanding the project, as well as acknowledging the individuals who contributed to its development.

## Installation

To install and use Philosophers, follow these steps:

1. Clone the Philosophers repository from GitHub:
   ```
   git clone https://github.com/Thib1708/philo.git
   ```

2. Change into the project directory:
   ```
   cd philo
   ```

3. Compile the Philosophers program using the provided Makefile:
   ```
   make
   ```

4. The `philosophers` executable will be generated. You can now start using Philosophers.

Note: Philosophers requires a Unix-like operating system and a C compiler (e.g., GCC) to be installed on your system.

## Usage

To use Philosophers, follow the syntax:

```
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

- `number_of_philosophers`: The number of philosophers sitting at the table.
- `time_to_die`: The time in milliseconds after which a philosopher dies if they have not eaten.
- `time_to_eat`: The time in milliseconds it takes for a philosopher to eat.
- `time_to_sleep`: The time in milliseconds a philosopher spends sleeping.
- `number_of_times_each_philosopher_must_eat` (optional): The number of times each philosopher must eat before the simulation ends. If not specified, the simulation continues indefinitely.

Example usage:

```
./philo 5 800 200 200
```

This command will simulate a table with 5 philosophers, a time-to-die of 800 milliseconds, a time-to-eat of 200 milliseconds, and a time-to-sleep of 200 milliseconds. The simulation will continue until a philosopher dies or the program is manually interrupted.

## Documentation

Philosophers has the following key features and considerations:

- The project uses threads and mutexes to represent philosophers and forks and ensure mutual exclusion when accessing shared resources.
- Philosophers are represented as threads that perform actions (eat, sleep, think) based on a set of rules and constraints.
- The program handles different scenarios, including deadlock avoidance, starvation prevention, and synchronized resource access.
- Error handling and graceful termination of the simulation have been implemented to handle unexpected situations and ensure clean program exit.

For further details on the implementation, algorithms, and code structure, refer to the source code comments and documentation provided within the Philosophers repository.

## Credits

This project was completed by Thibault GIRAUDON (tgiraudo) as part of the curriculum at École 42.
