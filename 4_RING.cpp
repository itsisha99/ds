#include <iostream>
#include <vector>
using namespace std;

void ringAlgorithm(vector<int> &processes, int initiator) {
    int n = processes.size();
    int leaderID = processes[initiator];
    int currentID = leaderID;

    cout << "Initiator process: P" << initiator << " with ID " << leaderID << "\n";

    // Election process
    cout << "Starting election...\n";
    for (int i = (initiator + 1) % n; i != initiator; i = (i + 1) % n) {
        cout << "P" << i << " receives ID " << currentID << "\n";
        if (processes[i] > currentID) {
            currentID = processes[i];
            cout << "P" << i << " forwards new ID " << currentID << "\n";
        } else {
            cout << "P" << i << " forwards current ID " << currentID << "\n";
        }
    }

    // Leader announcement
    leaderID = currentID;
    cout << "\nLeader is P" << initiator << " with ID " << leaderID << "\n";
    cout << "Announcing leader to all processes...\n";

    for (int i = (initiator + 1) % n; i != initiator; i = (i + 1) % n) {
        cout << "P" << i << " acknowledges leader ID " << leaderID << "\n";
    }
    cout << "Election completed. Leader: " << leaderID << "\n";
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<int> processes(n);
    cout << "Enter the unique IDs of the processes:\n";
    for (int i = 0; i < n; i++) {
        cout << "ID for process P" << i << ": ";
        cin >> processes[i];
    }

    int initiator;
    cout << "Enter the index of the initiator process (0 to " << n - 1 << "): ";
    cin >> initiator;

    if (initiator < 0 || initiator >= n) {
        cout << "Invalid initiator index. Exiting...\n";
        return 1;
    }

    ringAlgorithm(processes, initiator);

    return 0;
}

/*
This code implements the **Ring Algorithm** for leader election in a distributed system. Below is a concise explanation of each part of the program:

---

### **Key Components of the Program**

1. **Process Representation:**
   - The processes in the system are represented by a vector `processes`, where each process has a unique ID.

2. **Input:**
   - The user provides:
     - Number of processes (`n`).
     - Unique IDs for each process.
     - The index of the initiator process that starts the election.

3. **The Ring Algorithm:**
   - The algorithm works in a circular manner, treating the processes as if they are connected in a logical ring.

---

### **Steps in the Algorithm**

1. **Initialization:**
   - The `initiator` process starts the election by passing its own ID as the initial leader candidate (`leaderID`).

2. **Election Process:**
   - The ID (`leaderID`) is passed around the ring. Each process:
     - Compares the received ID with its own.
     - Updates the `leaderID` if its own ID is higher.
     - Forwards the ID (updated or not) to the next process in the ring.

3. **Leader Announcement:**
   - Once the ID completes a full round back to the initiator:
     - The initiator determines the highest ID as the leader.
     - The leader ID is then sent around the ring again, and all processes acknowledge it.

4. **Output:**
   - The algorithm prints the steps of the election process and the final elected leader.

---

### **Example Input/Output Walkthrough**
- **Input:**
  ```
  Enter the number of processes: 5
  Enter the unique IDs of the processes:
  ID for process P0: 12
  ID for process P1: 9
  ID for process P2: 20
  ID for process P3: 15
  ID for process P4: 18
  Enter the index of the initiator process (0 to 4): 2
  ```

- **Output:**
  ```
  Initiator process: P2 with ID 20
  Starting election...
  P3 receives ID 20
  P3 forwards current ID 20
  P4 receives ID 20
  P4 forwards current ID 20
  P0 receives ID 20
  P0 forwards current ID 20
  P1 receives ID 20
  P1 forwards current ID 20

  Leader is P2 with ID 20
  Announcing leader to all processes...
  P3 acknowledges leader ID 20
  P4 acknowledges leader ID 20
  P0 acknowledges leader ID 20
  P1 acknowledges leader ID 20
  Election completed. Leader: 20
  ```

---

### **Key Features**
- The algorithm guarantees a unique leader by propagating and comparing IDs.
- The ring structure ensures fairness and participation of all processes.

---

### **Possible Enhancements**
- Add termination conditions to stop the loop if a process fails.
- Include timestamps or priorities to handle processes with identical IDs.

3. Ring Algorithm
A distributed leader election algorithm in ring topology.

Applications:
Token Ring Networks: Ensuring fault tolerance by electing a leader when a node fails.
Distributed Systems: Selecting a coordinator among distributed nodes for tasks like resource allocation or scheduling.
Sensor Networks: Leader election in circular communication architectures.

*/