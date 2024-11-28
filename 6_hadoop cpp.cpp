#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <sstream>
#include <iterator>

using namespace std;

// Map function that tokenizes the input text and returns a vector of key-value pairs
vector<pair<string, int> > mapFunction(const string &input) {
    vector<pair<string, int> > wordCounts;
    stringstream ss(input); 
    string word;

    // Tokenize the input string
    while (ss >> word) {
        wordCounts.push_back(make_pair(word, 1));  // Emit key-value pairs (word, 1)
    }
    return wordCounts;
}

// Shuffle and Sort function: groups the words and their counts
map<string, int> shuffleAndSort(const vector<pair<string, int> > &mappedData) {
    map<string, int> sortedData;

    // Aggregate word counts
    for (size_t i = 0; i < mappedData.size(); i++) {
        const pair<string, int>& entry = mappedData[i];
        sortedData[entry.first] += entry.second;
    }

    return sortedData;
}

// Reduce function: processes each word and its count, aggregating counts
void reduceFunction(const map<string, int> &sortedData) {
    cout << "\nWord Count Result: \n";

    // Traditional loop to iterate through the map (sortedData)
    for (map<string, int>::const_iterator it = sortedData.begin(); it != sortedData.end(); ++it) {
        cout << it->first << ": " << it->second << endl;  // Print word and its count
    }
}

int main() {
    string line;
    vector<pair<string, int> > mappedData;

    cout << "Enter text (type 'DONE' to finish input):\n";
    
    // Take multiple lines of input from the user
    while (true) {
        // Read a line of input
        getline(cin, line);
        
        // Stop reading when the user types 'DONE'
        if (line == "DONE") {
            break;
        }

        // 1. Map Phase: Tokenize the input text and generate key-value pairs
        vector<pair<string, int> > mappedLine = mapFunction(line);
        mappedData.insert(mappedData.end(), mappedLine.begin(), mappedLine.end());
    }

    // 2. Shuffle & Sort Phase: Group and sort the data based on keys (words)
    map<string, int> sortedData = shuffleAndSort(mappedData);

    // 3. Reduce Phase: Aggregate the counts for each word
    reduceFunction(sortedData);

    return 0;
}

/*
Enter text (type 'DONE' to finish input):
hello world hello map reduce hello world
this is a test hello test world
DONE

OUTPUT:
Word Count Result:
a: 1
hello: 4
is: 1
map: 1
reduce: 1
test: 2
this: 1
world: 3



This program demonstrates a **MapReduce framework** for counting the occurrences of words in a given input text. It implements three core phases of MapReduce: **Map, Shuffle & Sort,** and **Reduce.** The program reads text input, processes it through these phases, and outputs the word counts.

---

### **Detailed Explanation**

#### **1. Map Function (`mapFunction`)**

The **Map Phase** processes the input text line by line, tokenizing it into individual words and creating key-value pairs where:
- **Key** = Word.
- **Value** = 1 (indicating one occurrence of the word).

```cpp
vector<pair<string, int> > mapFunction(const string &input) {
    vector<pair<string, int> > wordCounts;
    stringstream ss(input);
    string word;
    while (ss >> word) {
        wordCounts.push_back(make_pair(word, 1));
    }
    return wordCounts;
}
```

**Key Points:**
- Input: A single line of text, e.g., `"hello world"`.
- Output: A vector of key-value pairs, e.g., `[("hello", 1), ("world", 1)]`.

---

#### **2. Shuffle & Sort Function (`shuffleAndSort`)**

The **Shuffle & Sort Phase** groups key-value pairs with the same key (word) and aggregates their counts.

```cpp
map<string, int> shuffleAndSort(const vector<pair<string, int> > &mappedData) {
    map<string, int> sortedData;
    for (size_t i = 0; i < mappedData.size(); i++) {
        const pair<string, int>& entry = mappedData[i];
        sortedData[entry.first] += entry.second;
    }
    return sortedData;
}
```

**Key Points:**
- Input: A vector of key-value pairs, e.g., `[("hello", 1), ("world", 1), ("hello", 1)]`.
- Processing:
  - It iterates through the vector and uses a `map` (dictionary) to group and sum counts for each word.
- Output: A `map` with aggregated counts, e.g., `{ "hello": 2, "world": 1 }`.

---

#### **3. Reduce Function (`reduceFunction`)**

The **Reduce Phase** processes the grouped data from the Shuffle & Sort Phase and outputs the final word counts.

```cpp
void reduceFunction(const map<string, int> &sortedData) {
    for (map<string, int>::const_iterator it = sortedData.begin(); it != sortedData.end(); ++it) {
        cout << it->first << ": " << it->second << endl;
    }
}
```

**Key Points:**
- Input: A map of grouped word counts, e.g., `{ "hello": 4, "world": 3 }`.
- Processing: Iterates over the map and prints the word and its final count.
- Output: The final word count result:
  ```
  hello: 4
  world: 3
  ```

---

### **Main Function**

1. **Input Handling:**
   - Continuously reads lines of input from the user until the word "DONE" is entered.
   - Example:
     ```
     hello world hello map reduce hello world
     this is a test hello test world
     DONE
     ```

2. **Processing:**
   - Calls `mapFunction` for each line to tokenize and generate key-value pairs.
   - Combines all mapped key-value pairs into a single vector.
   - Passes the combined data to `shuffleAndSort` to aggregate counts.
   - Calls `reduceFunction` to display the final word counts.

3. **Output:**
   - After processing all input lines, outputs the word counts.

---

### **Example Walkthrough**

Input:
```
hello world hello map reduce hello world
this is a test hello test world
DONE
```

#### **Map Phase Output:**
Key-value pairs from tokenizing each line:
```
[("hello", 1), ("world", 1), ("hello", 1), ("map", 1), ("reduce", 1), ("hello", 1), ("world", 1), 
 ("this", 1), ("is", 1), ("a", 1), ("test", 1), ("hello", 1), ("test", 1), ("world", 1)]
```

#### **Shuffle & Sort Phase Output:**
Aggregated counts:
```
{
    "a": 1,
    "hello": 4,
    "is": 1,
    "map": 1,
    "reduce": 1,
    "test": 2,
    "this": 1,
    "world": 3
}
```

#### **Reduce Phase Output:**
Final word counts:
```
a: 1
hello: 4
is: 1
map: 1
reduce: 1
test: 2
this: 1
world: 3
```

---

### **Key Features**
1. **Decoupled Phases:**
   - Each phase (Map, Shuffle & Sort, Reduce) is modular and handles a specific responsibility.

2. **Dynamic Input Handling:**
   - Reads multiple lines of input dynamically and processes them iteratively.

3. **MapReduce Concept:**
   - Demonstrates how distributed systems process large datasets using the MapReduce paradigm.

---

This program effectively implements a simple **MapReduce framework** for word count. It demonstrates the concepts of mapping, grouping, and reducing data in a distributed or parallel processing environment.

6. Word Count with MapReduce
A distributed computing paradigm for processing and generating large datasets.

Applications:
Search Engines: Counting the frequency of words in web pages to rank search results.
Big Data Analytics: Log analysis, sentiment analysis, and text mining on large-scale data.
E-commerce: Product review analysis by counting keyword occurrences.
Research: Analyzing large-scale datasets in fields like genomics, social media, or linguistics.
Content Recommendation Systems: Identifying popular topics or keywords in user data.

*/
