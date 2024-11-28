#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
using namespace std;

#define N 5                  // Number of philosophers
#define THINKING 2
#define HUNGRY 1
#define EATING 0
#define LEFT (phnum + 4) % N // Index of the left philosopher
#define RIGHT (phnum + 1) % N // Index of the right philosopher

int state[N];                // State of each philosopher
int phil[N] = { 0, 1, 2, 3, 4 }; // Philosopher IDs
sem_t mutex;                 // Semaphore for critical section
sem_t S[N];                  // Semaphore for individual philosophers

// Function to test if a philosopher can eat
void test(int phnum) {
    if (state[phnum] == HUNGRY &&
        state[LEFT] != EATING &&
        state[RIGHT] != EATING) {
        
        state[phnum] = EATING;
        sleep(2); // Simulate eating process
        
        cout << "Philosopher " << phnum + 1 << " takes fork " 
             << LEFT + 1 << " and " << phnum + 1 << endl;
        cout << "Philosopher " << phnum + 1 << " is Eating" << endl;
        
        sem_post(&S[phnum]); // Signal philosopher to start eating
    }
}

// Function for a philosopher to take forks
void take_fork(int phnum) {
    sem_wait(&mutex); // Enter critical section
    
    state[phnum] = HUNGRY;
    cout << "Philosopher " << phnum + 1 << " is Hungry" << endl;
    
    test(phnum); // Try to take forks
    
    sem_post(&mutex); // Exit critical section
    sem_wait(&S[phnum]); // Wait until allowed to eat
    sleep(1);
}

// Function for a philosopher to put down forks
void put_fork(int phnum) {
    sem_wait(&mutex); // Enter critical section
    
    state[phnum] = THINKING;
    cout << "Philosopher " << phnum + 1 << " putting fork " 
         << LEFT + 1 << " and " << phnum + 1 << " down" << endl;
    cout << "Philosopher " << phnum + 1 << " is thinking" << endl;
    
    // Test left and right neighbors
    test(LEFT);
    test(RIGHT);
    
    sem_post(&mutex); // Exit critical section
}

// Function executed by each philosopher thread
void* philosopher(void* num) {
    int* i = (int*)num;

    while (true) {
        sleep(1); // Thinking
        take_fork(*i); // Try to pick up forks
        sleep(0); // Eating
        put_fork(*i); // Put down forks
    }
}

int main() {
    pthread_t thread_id[N]; // Thread IDs for philosophers

    // Initialize the semaphores
    sem_init(&mutex, 0, 1);
    for (int i = 0; i < N; i++) {
        sem_init(&S[i], 0, 0);
    }

    // Create philosopher threads
    for (int i = 0; i < N; i++) {
        pthread_create(&thread_id[i], NULL, philosopher, &phil[i]);
        cout << "Philosopher " << i + 1 << " is thinking" << endl;
    }

    // Join philosopher threads
    for (int i = 0; i < N; i++) {
        pthread_join(thread_id[i], NULL);
    }

    return 0;
}


/*
This code implements the **Dining Philosophers Problem** using semaphores to handle synchronization and avoid deadlocks. The problem models a scenario where five philosophers sit around a circular table, alternating between **thinking** and **eating**, with one fork placed between each pair of adjacent philosophers. A philosopher must acquire both the left and right forks to eat.

---

### **Key Concepts**
1. **Philosophical States**:
   - **Thinking (2)**: Philosopher is not hungry or eating.
   - **Hungry (1)**: Philosopher is trying to acquire forks.
   - **Eating (0)**: Philosopher has acquired both forks and is eating.

2. **Synchronization Mechanisms**:
   - **Semaphores**:
     - **`mutex`**: Ensures mutual exclusion in the critical section where states are modified.
     - **`S[N]`**: Individual semaphores for each philosopher, signaling when they can eat.
   - **Critical Section**: Protects shared resources (forks and philosopher states) to avoid race conditions.

3. **Fork Allocation**:
   - Each philosopher tries to pick up the fork on their left and right.
   - If the adjacent philosophers are not eating, the philosopher can proceed.

---

### **Code Breakdown**

#### **1. Definitions and Initialization**
- **State Array**: Tracks each philosopher's state (`THINKING`, `HUNGRY`, `EATING`).
  ```cpp
  int state[N];
  ```
- **Philosopher IDs**: Stored in an array for easy referencing.
  ```cpp
  int phil[N] = { 0, 1, 2, 3, 4 };
  ```
- **Semaphores**:
  - `mutex`: Guards the critical section.
  - `S[N]`: Handles individual philosopher permissions to eat.
  ```cpp
  sem_t mutex;
  sem_t S[N];
  ```

---

#### **2. `test(int phnum)`**
This function checks if a philosopher can eat:
- A philosopher can eat if they are **hungry** and both adjacent philosophers are **not eating**.
- If conditions are met, the philosopher transitions to the `EATING` state, and their semaphore is signaled.

---

#### **3. `take_fork(int phnum)`**
This function simulates a philosopher trying to pick up forks:
1. Acquires the mutex to enter the critical section.
2. Sets the philosopher’s state to `HUNGRY`.
3. Calls `test(phnum)` to check if the philosopher can eat.
4. Releases the mutex and waits on the semaphore (`S[phnum]`) until allowed to eat.

---

#### **4. `put_fork(int phnum)`**
This function simulates a philosopher putting down forks:
1. Acquires the mutex to enter the critical section.
2. Sets the philosopher’s state back to `THINKING`.
3. Calls `test(LEFT)` and `test(RIGHT)` to check if adjacent philosophers can now eat.
4. Releases the mutex.

---

#### **5. `philosopher` Thread Function**
Each philosopher thread alternates between:
1. **Thinking**: Sleeps for 1 second.
2. **Picking up forks**: Calls `take_fork`.
3. **Eating**: Simulated by sleeping for a short duration.
4. **Putting down forks**: Calls `put_fork`.

This loop continues indefinitely, simulating the philosopher's behavior.

---

#### **6. `main()` Function**
1. **Initialize Semaphores**:
   - `mutex` is initialized with a value of 1 (binary semaphore).
   - `S[i]` are initialized with 0, indicating philosophers must wait for permission to eat.
   ```cpp
   sem_init(&mutex, 0, 1);
   for (int i = 0; i < N; i++) {
       sem_init(&S[i], 0, 0);
   }
   ```

2. **Create Threads**:
   - One thread is created for each philosopher.
   ```cpp
   pthread_create(&thread_id[i], NULL, philosopher, &phil[i]);
   ```

3. **Join Threads**:
   - Threads are joined to ensure the program doesn’t terminate early.
   ```cpp
   pthread_join(thread_id[i], NULL);
   ```

---

### **Program Execution**

1. **Initial State**:
   All philosophers start in the `THINKING` state.
   ```
   Philosopher 1 is thinking
   Philosopher 2 is thinking
   Philosopher 3 is thinking
   Philosopher 4 is thinking
   Philosopher 5 is thinking
   ```

2. **Message Flow**:
   - Philosopher 1 becomes **hungry** and tries to acquire forks:
     ```
     Philosopher 1 is Hungry
     Philosopher 1 takes fork 5 and 1
     Philosopher 1 is Eating
     ```

   - After eating, Philosopher 1 puts down forks:
     ```
     Philosopher 1 putting fork 5 and 1 down
     Philosopher 1 is thinking
     ```

   - The process continues for other philosophers in a round-robin manner.

---

### **Key Features**
- **Deadlock Prevention**: By ensuring a philosopher eats only if both adjacent philosophers are not eating, deadlock is avoided.
- **Concurrency**: The mutex ensures only one philosopher modifies shared resources at a time.
- **Fairness**: Adjacent philosophers are tested (`test(LEFT)` and `test(RIGHT)`) after a philosopher finishes eating, ensuring fair access to forks.

---

### **Output Example**
```
Philosopher 1 is thinking
Philosopher 2 is thinking
Philosopher 3 is thinking
Philosopher 4 is thinking
Philosopher 5 is thinking
Philosopher 1 is Hungry
Philosopher 1 takes fork 5 and 1
Philosopher 1 is Eating
Philosopher 1 putting fork 5 and 1 down
Philosopher 1 is thinking
Philosopher 2 is Hungry
Philosopher 2 takes fork 1 and 2
Philosopher 2 is Eating
...
```

This continues indefinitely, simulating the philosophers' behavior.


The program runs infinitely because the philosopher threads are in a **while(true)** loop, continuously alternating between thinking, trying to pick up forks, eating, and putting down forks. There is no condition to stop or terminate the threads.

### **How to Terminate It:**
1. **Add a Global Flag**: Introduce a `bool` flag (e.g., `terminate`) that threads check in their loop. If `terminate` becomes `true`, threads break out of the loop.
2. **Limit Iterations**: Use a counter in each philosopher's loop to allow only a fixed number of iterations (e.g., 10 eating cycles).
3. **Join Threads Gracefully**: Signal threads to exit, then `pthread_join` to clean up. 

This would make the program stop after completing a defined number of cycles or when externally signaled.

5. Dining Philosophers Problem
A synchronization problem used to study resource sharing among concurrent processes.

Applications:
Concurrency Control: Resolving deadlocks and resource contention in multithreaded systems.
Operating Systems: Managing processes that share resources like CPU, memory, or I/O devices.
Database Systems: Handling deadlocks in transaction processing systems.
Networking: Resource allocation in systems where multiple entities compete for a limited set of resources.
*/

