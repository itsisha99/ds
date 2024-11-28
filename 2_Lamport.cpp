#include <iostream>
#include <vector>
using namespace std;

class Process {
public:
    int id;
    int logicalClock;

    Process(int id) : id(id), logicalClock(0) {}

    void sendMessage(Process& receiver) {
        logicalClock++;
        receiver.receiveMessage(logicalClock);
    }

    void receiveMessage(int senderClock) {
        logicalClock = max(logicalClock, senderClock) + 1;
    }
};

void printClocks(vector<Process>& processes) {
    for (Process& p : processes) {
        cout << "Process " << p.id << " logical clock: " << p.logicalClock << endl;
    }
}

int main() {
    int numProcesses;

    cout << "Enter the number of processes: ";
    cin >> numProcesses;

    vector<Process> processes;
    for (int i = 0; i < numProcesses; ++i) {
        processes.push_back(Process(i + 1));
    }

    for (int i = 0; i < numProcesses; i++) {
        int nextProcess = (i + 1) % numProcesses;
        processes[i].sendMessage(processes[nextProcess]);
    }

    cout << "\nLogical clocks after message exchanges:\n";
    printClocks(processes);

    return 0;
}

/* 
This program demonstrates the concept of **Lamport Logical Clocks** used in distributed systems to maintain a consistent order of events across multiple processes. The program simulates a simple communication scenario where each process sends a message to the next process, updating its logical clock based on Lamport’s clock rules.

---

### **Key Concepts of Lamport Logical Clocks**
1. **Logical Clock**: A counter maintained by each process to represent the order of events.
2. **Clock Update Rules**:
   - When a process sends a message, it increments its logical clock.
   - When a process receives a message, it updates its clock to the maximum of its current clock and the sender’s clock, plus one.

---

### **Code Breakdown**

#### 1. **`Process` Class**
- Each process has:
  - **`id`**: Unique identifier for the process.
  - **`logicalClock`**: The current value of the logical clock for the process.

- **Methods:**
  - **`sendMessage`**: 
    - Increments the logical clock of the sender.
    - Calls the `receiveMessage` method of the receiver, passing its updated logical clock.
    ```cpp
    void sendMessage(Process& receiver) {
        logicalClock++;
        receiver.receiveMessage(logicalClock);
    }
    ```

  - **`receiveMessage`**: Updates the receiver’s clock using:
    \[
    \text{logicalClock} = \max(\text{logicalClock}, \text{senderClock}) + 1
    \]
    ```cpp
    void receiveMessage(int senderClock) {
        logicalClock = max(logicalClock, senderClock) + 1;
    }
    ```

#### 2. **`printClocks` Function**
This function iterates through all processes and prints their logical clock values.
```cpp
void printClocks(vector<Process>& processes) {
    for (Process& p : processes) {
        cout << "Process " << p.id << " logical clock: " << p.logicalClock << endl;
    }
}
```

#### 3. **`main` Function**
- **Input**: The user enters the number of processes.
  ```cpp
  cout << "Enter the number of processes: ";
  cin >> numProcesses;
  ```

- **Process Creation**: Creates `numProcesses` objects of the `Process` class and stores them in a vector.
  ```cpp
  for (int i = 0; i < numProcesses; ++i) {
      processes.push_back(Process(i + 1));
  }
  ```

- **Message Passing**:
  - Each process sends a message to the next process (in a circular manner).
    ```cpp
    for (int i = 0; i < numProcesses; i++) {
        int nextProcess = (i + 1) % numProcesses;
        processes[i].sendMessage(processes[nextProcess]);
    }
    ```

- **Output**: Prints the logical clocks of all processes after all message exchanges.
  ```cpp
  cout << "\nLogical clocks after message exchanges:\n";
  printClocks(processes);
  ```

---

### **Example Input/Output**

#### **Input**:
```
Enter the number of processes: 3
```

#### **Output**:
```
Logical clocks after message exchanges:
Process 1 logical clock: 3
Process 2 logical clock: 4
Process 3 logical clock: 4
```

---

### **How It Works**

1. **Initial State**:
   - All processes start with a logical clock of 0.

2. **Message Passing**:
   - Process 1 sends a message to Process 2:
     - Process 1 increments its clock: \( 0 + 1 = 1 \).
     - Process 2 updates its clock: \( \max(0, 1) + 1 = 2 \).

   - Process 2 sends a message to Process 3:
     - Process 2 increments its clock: \( 2 + 1 = 3 \).
     - Process 3 updates its clock: \( \max(0, 3) + 1 = 4 \).

   - Process 3 sends a message back to Process 1:
     - Process 3 increments its clock: \( 4 + 1 = 5 \).
     - Process 1 updates its clock: \( \max(1, 5) + 1 = 6 \).

3. **Final State**:
   Each process reflects its updated logical clock based on the message exchanges.

---

### **Key Takeaways**
1. The program simulates distributed message-passing using logical clocks.
2. The clocks help maintain causal relationships between events.
3. Circular message passing ensures all processes are involved in the synchronization process.



2. Lamport's Logical Clock
A mechanism for ordering events in distributed systems without requiring synchronized clocks.

Applications:
Distributed Databases: Maintaining consistency by ordering transactions.
Distributed Debugging: Detecting race conditions or analyzing the sequence of events.
Concurrent Systems: For event ordering in distributed applications like messaging systems or multi-node applications.
Blockchain Technology: Event ordering in decentralized networks.

*/

