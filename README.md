# Description
This project implements a hash table data structure using both Python and C programming languages. The hash table is implemented with linear probing collision resolution. Additionally, a simple dictionary application is created, allowing users to search for word meanings efficiently.

# Requirements/Commands
**Python:**
Requires Python interpreter.
python HashTable_Python.py

**C:**
Requires C compiler.
gcc HashTable_C.c -o hash_table
./hash_table

# Explanation/Comparison
**Scoping: Static vs. Dynamic:**
Python: Operates with dynamic scoping where variables' contexts are resolved at runtime, allowing for flexible but less predictable behavior, especially in complex environments.
C: Uses static scoping, with variables' contexts fixed at compile time, enhancing predictability, and reducing runtime overhead.\
**Garbage Collection:**
Python: Features an automatic garbage collector that manages memory by disposing of unused objects, simplifying development but potentially adding overhead.
C: Requires manual memory management, providing more control and efficiency in memory use, crucial for resource-constrained environments.
**Programming Paradigms:**
Python: The implementation utilizes the procedural paradigm, where functions operate on data directly, but also supports object-oriented programming. This flexibility allows Python to adapt easily to various problem domains by using the most appropriate programming style.
C: Strictly adheres to procedural programming. This focus enhances the efficiency of functions that are directly related to data manipulation and control structures but limits the versatility compared to Python.
**Performance:**
Python: The provided implementation highlights Python's ease of use and rapid development capabilities. However, the performance tests (measuring insertion and retrieval times) reveal that Python's hash table operations tend to be slower compared to C. This is largely due to its interpreted nature and the overhead associated with dynamic typing and automatic memory management.
C: The C implementation demonstrates significantly faster performance in both insertion and retrieval tasks. This superior speed stems from C's compiled nature and the ability to optimize data structures closely aligned with the hardware. Manual memory management in C allows for leaner, more efficient control over system resources, contributing to its faster operation in performance-critical tasks.

# Implementation Details
Python Implementation (HashTable_Python.py)
The Python implementation utilizes a linear probing hash table. It reads word definitions from a file, stores them in the hash table, and allows users to search for word meanings interactively.

C Implementation (HashTable_C.c)
The C implementation also uses linear probing for collision resolution. It reads word definitions from a file, stores them in the hash table, and enables users to search for word meanings interactively.

# Programming Languages and Compilers Used
Python:
Interpreter: Python 3.x
C:
Compiler: GCC (GNU Compiler Collection)

**Output**
Python Output:
Time taken to read the file and store 1115 items in Hashtable: 4.995584487915039 ms
Total Collisions: 580
Average Probe Length: 24.39641255605381 

Enter the word to find its meaning (enter 0 to exit): vex
vex means: to make (someone) feel annoyed, frustrated, or worried, especially with trivial matters
...

C Output:
Time taken to read the file and store 1115 items in Hashtable: 2.21 ms
Total Collisions: 575
Average Probe Length: 21.67

Enter the word to find its meaning (enter 0 to exit): vex
vex means: to make (someone) feel annoyed, frustrated, or worried, especially with trivial matters
...

Both implementations provide a seamless experience for searching word meanings while highlighting the differences between Python and C in terms of syntax, memory management, and performance.
