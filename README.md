# Banker's Algorithm with C++

This C++ program simulates the Banker's Algorithm to determine a safe sequence of processes in a system with limited resources. It reads data from a resource file (`resources.txt`) and identifies whether the system is in a safe state. If so, it outputs the safe sequence of process execution; otherwise, it indicates that the system is in an unsafe state.

## Prerequisites

Before running the program, ensure you have:
- A C++ compiler (like `g++`).
- A `resources.txt` file containing data for allocation, maximum resources, and available resources.

The `resources.txt` file should follow this structure:

- **allocationMatrix:** Lists the resources currently allocated to each process. 
- **maxMatrix:** Describes the maximum resources each process might request.
- **available:** Shows the total resources available in the system.

Here's an example of the expected format:

```plaintext
Allocation:
P0:0,1,0
P1:2,0,0
P2:3,0,2
P3:2,1,1
P4:0,0,2
Max:
P0:7,5,3
P1:3,2,2
P2:9,0,2
P3:2,2,2
P4:4,3,3
Available:
3,3,2
```
```plaintext
-You can always change the example provided. But make sure to keep the exact same structure.
-Plus, to add a process to the system, you need manually change the initialization of vectors in the code
-To add a resource, just add comma and add your resource next to the existing resources. 
```

## Program Structure

- The program has functions to read and parse the `resources.txt` file, generate the need matrix, and determine the safe sequence of processes.
- It uses vectors to store matrices and lists of resources, allowing flexibility and scalability.
- The `getSafeSequence` function computes the safe sequence by checking if processes can meet their resource needs with the available resources.

## How to Use

1. Compile the code using a C++ compiler, such as `g++`:

   ```bash
   g++ -o banker banker.cpp

2. Run the compiled program:

   ```bash
   ./banker

3. Check the console output for the following:
    If the system is in a safe state, it will output "System is in safe state!" along with the safe sequence of processes.
    If no safe sequence is found, the output will indicate that the system is in an unsafe state.
