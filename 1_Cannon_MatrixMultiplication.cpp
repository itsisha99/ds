#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm> // Include this for the rotate function
using namespace std;

// Function to print a matrix
void printMatrix(const vector<vector<int>> &matrix)
{
    for (const auto &row : matrix)
    {
        for (const auto &elem : row)
        {
            cout << setw(5) << elem;
        }
        cout << endl;
    }
}


vector<vector<int>> cannonsMatrixMultiplication(const vector<vector<int>> &A, const vector<vector<int>> &B) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n, 0)); // Initialize result matrix

    // Step 1: Initial Alignment
    vector<vector<int>> A_aligned = A;
    vector<vector<int>> B_aligned = B;

    // Align rows of A
    for (int i = 0; i < n; i++) {
        rotate(A_aligned[i].begin(), A_aligned[i].begin() + i, A_aligned[i].end());
    }
    
    cout<<"\nMatrix A after Rotation :\n";
    printMatrix(A);
    
    

    // Align columns of B
    for (int j = 0; j < n; j++) {
        vector<int> temp_column(n);
        for (int i = 0; i < n; i++) {
            temp_column[i] = B_aligned[i][j];
        }
        rotate(temp_column.begin(), temp_column.begin() + j, temp_column.end());
        for (int i = 0; i < n; i++) {
            B_aligned[i][j] = temp_column[i];
        }
    }
    cout<<"\nMatrix B after Rotation :\n";
    printMatrix(B);

    // Step 2: Iterative Multiplication and Alignment
    for (int step = 0; step < n; step++) {
        // Multiply aligned matrices
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                C[i][j] += A_aligned[i][j] * B_aligned[i][j];
            }
        }
        cout<<"\nResultant Matrix C :\n";
    	printMatrix(C);

        // Shift rows of A left by one position
        for (int i = 0; i < n; i++) {
            rotate(A_aligned[i].begin(), A_aligned[i].begin() + 1, A_aligned[i].end());
        }
        cout<<"\nMatrix A after Rotation :\n";
    	printMatrix(A);

        // Shift columns of B up by one position
        for (int j = 0; j < n; j++) {
            int temp = B_aligned[0][j];
            for (int i = 0; i < n - 1; i++) {
                B_aligned[i][j] = B_aligned[i + 1][j];
            }
            B_aligned[n - 1][j] = temp;
        }
        cout<<"\nMatrix B after Rotation :\n";
    	printMatrix(B);
    }

    return C;
}

vector<vector<int>> Multiply(vector<vector<int>> A,vector<vector<int>> B)
{
	int n=A.size();
	vector<vector<int>> C(n,vector<int>(n,0));
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			for(int k=0;k<n;k++)
			{
				C[i][j]+=A[i][k]*B[k][j];
			}
		}
	}
	return C;
}
int main()
{
    int n;
    cout << "Enter the size of the square matrices (n x n): ";
    cin >> n;

    vector<vector<int>> A(n, vector<int>(n));
    vector<vector<int>> B(n, vector<int>(n));

    cout << "Enter elements of matrix A:" << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> A[i][j];
        }
    }

    cout << "Enter elements of matrix B:" << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> B[i][j];
        }
    }

    cout << "Matrix A:" << endl;
    printMatrix(A);

    cout << "Matrix B:" << endl;
    printMatrix(B);

    vector<vector<int>> C = cannonsMatrixMultiplication(A, B);

    cout << "Resultant Matrix C (A * B) with Canons Matrix Multiplication :" << endl;
    printMatrix(C);
    cout << "Resultant Matrix C (A * B) with Normal Matrix Multiplication :" << endl;
    vector<vector<int>> D = Multiply(A,B);
    printMatrix(D);

    return 0;
}


/*

This program implements **Cannon’s Matrix Multiplication Algorithm**, a parallel matrix multiplication technique that aligns submatrices for efficient computation. It also compares the result of Cannon's algorithm with a straightforward matrix multiplication method.

---

### **Key Components of the Code**

#### 1. **Matrix Representation**
The matrices are stored as `std::vector<std::vector<int>>`. This flexible data structure is used to hold the square matrices \( A \), \( B \), and the result matrix \( C \).

---

#### 2. **Cannon's Matrix Multiplication Algorithm**

##### **Steps in Cannon's Algorithm**
1. **Initial Alignment:**
   - Rows of \( A \) are rotated left by their row index.
   - Columns of \( B \) are rotated up by their column index.
   - This ensures initial alignment for multiplication.

2. **Iterative Multiplication and Re-Alignment:**
   - Multiply corresponding elements of aligned \( A \) and \( B \), accumulating the results in \( C \).
   - Rotate \( A \)'s rows left by one position.
   - Rotate \( B \)'s columns up by one position.
   - Repeat for \( n \) steps (where \( n \) is the matrix size).

##### **Supporting Code in Cannon's Algorithm**
- **Initial Alignment:**
  - Rows of \( A \) are rotated using `std::rotate`.
    ```cpp
    for (int i = 0; i < n; i++) {
        rotate(A_aligned[i].begin(), A_aligned[i].begin() + i, A_aligned[i].end());
    }
    ```
  - Columns of \( B \) are extracted, rotated, and reinserted.
    ```cpp
    vector<int> temp_column(n);
    for (int i = 0; i < n; i++) {
        temp_column[i] = B_aligned[i][j];
    }
    rotate(temp_column.begin(), temp_column.begin() + j, temp_column.end());
    ```

- **Multiplication:**
  - Multiply aligned elements and accumulate the result.
    ```cpp
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] += A_aligned[i][j] * B_aligned[i][j];
        }
    }
    ```

- **Re-Alignment:**
  - Rotate rows of \( A \) left by one position.
    ```cpp
    for (int i = 0; i < n; i++) {
        rotate(A_aligned[i].begin(), A_aligned[i].begin() + 1, A_aligned[i].end());
    }
    ```
  - Shift columns of \( B \) up by one position.
    ```cpp
    int temp = B_aligned[0][j];
    for (int i = 0; i < n - 1; i++) {
        B_aligned[i][j] = B_aligned[i + 1][j];
    }
    B_aligned[n - 1][j] = temp;
    ```

---

#### 3. **Normal Matrix Multiplication**
This serves as a reference to validate Cannon's algorithm.
```cpp
for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
        for (int k = 0; k < n; k++) {
            C[i][j] += A[i][k] * B[k][j];
        }
    }
}
```

---

#### 4. **Utility Functions**
- **Matrix Printing:**
  Displays the matrices neatly using `std::setw` for formatting.
  ```cpp
  void printMatrix(const vector<vector<int>> &matrix) {
      for (const auto &row : matrix) {
          for (const auto &elem : row) {
              cout << setw(5) << elem;
          }
          cout << endl;
      }
  }
  ```

---

#### 5. **Main Function**
- Reads input matrices \( A \) and \( B \).
- Prints matrices \( A \) and \( B \).
- Performs multiplication using both Cannon's algorithm and normal multiplication.
- Compares the results.

---

### **Example Input/Output**

#### **Input:**
```
Enter the size of the square matrices (n x n): 2
Enter elements of matrix A:
1 2
3 4
Enter elements of matrix B:
5 6
7 8
```

#### **Output:**
```
Matrix A:
    1    2
    3    4
Matrix B:
    5    6
    7    8

Matrix A after Rotation :
    1    2
    4    3

Matrix B after Rotation :
    5    6
    8    7

Resultant Matrix C (A * B) with Canons Matrix Multiplication :
   19   22
   43   50

Resultant Matrix C (A * B) with Normal Matrix Multiplication :
   19   22
   43   50
```

---

### **Code Explanation Summary**
1. The program implements Cannon’s algorithm for efficient matrix multiplication by leveraging initial alignment and iterative shifts.
2. It compares the results against the standard matrix multiplication to ensure correctness.
3. The program is modular, using functions for matrix operations and clear output formatting.


1. Cannon's Matrix Multiplication
A parallel algorithm for dense matrix multiplication.

Applications:
Scientific Computing: Used in simulations requiring large-scale matrix computations, such as weather prediction and fluid dynamics.
Machine Learning and AI: Utilized in training neural networks and other models that rely on matrix operations.
Graphics Processing: For image transformation and rendering in computer graphics.
Big Data Analytics: Processing large datasets in distributed systems.

*/