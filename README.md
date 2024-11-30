## Banker Algorithm

This program is to implement the Banker’s Algorithm for deadlock avoidance. It checks whether the system is in a safe state and provides the safe sequence for executing processes.  A system with five processes P0 through P4 and three resources of type A, B, C.

<div align=center>
  <image src="1.png" alt="s">
</div>

## Step:

1. Input Parsing:
    - Reads the Allocation, Max, and Available (aka work) sections from the input file then stores in matrix and vectors.
2. Calculate the Need matrix for each process
    - For each process: eed = Max - Allocate
3. Safety check:
    - Iterative and checks if any process’s Need can be satisfied:
        if (Need <= Work) 
    - If satisfied, executes the process and updates the Available resources:
        Work += Allocation
4. Output the safety sequence

## Reference:  

[Banker's algorithm for deadlock avoidance][Banker Algorithm]

[Banker Algorithm]: https://www.youtube.com/watch?v=2V2FfP_olaA

## Instruction to run on your local machine
`g++ banker.cpp -o banker`

`./banker inputTest.csv`

## Output Result:
<div align=center>
  <image src="2.png" alt="cs">
</div>