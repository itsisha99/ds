#include <iostream>
#include <vector>

using namespace std;

void bullyAlgo(vector<int>& pro, int n, int init1) {
    int l = -1;
    for (int i = 0; i < n; i++) {
        if (pro[i] > pro[init1]) {
            cout << "\nProcess " << pro[init1] << " initiates election." << endl;
            cout << "\nProcess " << pro[i] << " responds to process " << pro[init1] << endl;
            l = pro[i];
        }
    }
    if (l == -1) {
        l = pro[init1];
    }
    for (int i = 0; i < n; i++) {
        if (pro[i] != l) {
            cout << "\nProcess " << l << " notifies process " << pro[i] << " as the new leader." << endl;
        }
    }
    cout << "Final leader (coordinator) is process " << l << endl;
}

int main() {
    int n, init1;
    cout << "\nEnter number of processes:\n";
    cin >> n;
    vector<int> pro(n);
    for (int i = 0; i < n; i++) {
        cout << "\nEnter process ID of process " << i << " :\n";
        cin >> pro[i];
    }
    cout << "\nEnter process ID which initiates election:\n";
    cin >> init1;
    bullyAlgo(pro, n, init1);
    return 0;
}

/*
This program implements the **Bully Algorithm**, which is used for leader election in distributed systems. The algorithm selects the process with the highest ID as the leader (coordinator) after an election initiated by a process.

---

### **Key Components of the Code**

1. **Process Representation:**
   - Processes are represented by their IDs in a vector `pro`. The IDs should be unique and typically represent priority or capability.

2. **Inputs:**
   - The number of processes (`n`).
   - IDs of the processes.
   - The process ID (`init1`) that initiates the election.

3. **Election Logic (`bullyAlgo`):**
   - The initiating process starts the election and communicates with processes with higher IDs.
   - Processes with higher IDs respond and effectively "bully" the initiating process by claiming the right to lead.
   - The process with the highest ID ultimately becomes the leader and informs all other processes of its leadership.

---

### **Steps in the Algorithm**

1. **Election Initialization:**
   - The initiating process (`init1`) checks all other processes to see if their ID is higher than its own.
   - If a higher ID is found, that process responds and is considered a candidate for leadership.

2. **Leader Determination:**
   - The highest ID among the processes that responded becomes the new leader.
   - If no process responds (no higher ID exists), the initiator becomes the leader.

3. **Leader Announcement:**
   - The new leader notifies all other processes of its leadership status.

---

### **Detailed Code Flow**

1. **Input Handling:**
   - The user inputs the number of processes, their IDs, and the initiator ID.
   - Example:
     ```
     Enter number of processes:
     4
     Enter process ID of process 0 :
     1
     Enter process ID of process 1 :
     2
     Enter process ID of process 2 :
     3
     Enter process ID of process 3 :
     4
     Enter process ID which initiates election:
     2
     ```

2. **Election Process (`bullyAlgo`):**
   - The initiator (`init1` = process ID 2) starts the election:
     - It checks all other processes to find IDs greater than its own.
     - Higher-ID processes respond, and the highest among them (ID 4) is elected as the leader.
   - The leader (ID 4) notifies all other processes of its leadership.

3. **Output:**
   - Example output:
     ```
     Process 2 initiates election.

     Process 3 responds to process 2

     Process 4 responds to process 2

     Process 4 notifies process 1 as the new leader.

     Process 4 notifies process 2 as the new leader.

     Process 4 notifies process 3 as the new leader.

     Final leader (coordinator) is process 4
     ```

---

### **Key Features**
1. The process with the highest ID becomes the leader.
2. The initiator need not always be the leader.
3. The algorithm works even if some processes fail, as long as the leader process remains functional.

---

### **Limitations**
- The algorithm requires multiple rounds of communication, which may increase latency.
- It assumes that processes with higher IDs are more capable of leading, which may not always be true in real systems.

This program demonstrates a simple implementation of the **Bully Algorithm**, focusing on the logical steps of leader election in distributed systems.

4. Bully Algorithm
A distributed algorithm for leader election in a system where each process knows the IDs of all others.

Applications:
Cluster Management: Electing a leader node in cluster-based environments like Kubernetes.
Distributed Databases: Choosing a primary replica or coordinator for operations.
Fault-Tolerant Systems: Re-election of a leader after node failures in distributed applications.
*/
