*This project has been created as part of the 42 curriculum by skarayil.*

# Philosophers

## Description
The **Philosophers** project is a classic synchronization problem (the Dining Philosophers problem) implemented as part of the 42 school curriculum. The goal of this project is to learn the basics of threading a process, and how to work on the same memory space. You will learn about mutexes, semaphores, and shared memory. 

The project consists of two parts:
- **Mandatory (philo):** Implemented using threads and mutexes. Each philosopher is a thread, and forks are protected by mutexes.
- **Bonus (philo_bonus):** Implemented using processes and semaphores. Each philosopher is a process, and the forks are represented by a global semaphore.

## Instructions
### Compilation
To compile the project, navigate to either the `philo` or `philo_bonus` directory and run `make`:
```bash
cd philo # or cd philo_bonus
make
```

### Execution
Run the compiled executable with the following arguments:
```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```
- `number_of_philosophers`: The number of philosophers and also the number of forks.
- `time_to_die` (in milliseconds): If a philosopher didn't start eating `time_to_die` milliseconds since the beginning of their last meal or the beginning of the simulation, they die.
- `time_to_eat` (in milliseconds): The time it takes for a philosopher to eat. During that time, they will need to hold two forks.
- `time_to_sleep` (in milliseconds): The time a philosopher will spend sleeping.
- `number_of_times_each_philosopher_must_eat` (optional argument): If all philosophers have eaten at least `number_of_times_each_philosopher_must_eat` times, the simulation stops. If not specified, the simulation stops when a philosopher dies.

## Resources
- [Wikipedia - Dining philosophers problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
- Unix manuals (`man`) for: `pthread_create`, `pthread_join`, `pthread_mutex_init`, `fork`, `sem_open`, `sem_wait`, `sem_post`.

### AI Usage Summary
AI tools were used during the development of this project for:
- Understanding the theoretical concepts of process scheduling, threads, mutexes, and semaphores.
- Reviewing error-handling edge cases in system calls and memory management.
