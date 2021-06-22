# Self-Stabilizing Algorithm

Given n processes we would like to build a self-stabilizing algorithm which at any given moment allows writing to only one process on screen.

First we will arrange the processes in a circle:




Then we choose a leader (main process) and perform the following algorithm :

o For a leader process:
1. Read the value of the process before you (the last in the circle).
2. If the value of the process is the same as your value then :

      A. The leader's value must be updated to  ( (value + 1) mod n ) .

      B. The value of the leader must be printed on the screen .


o For a non-leader process:
1. Read the value of the process before you .
2. If the value is different from yours then :

      A. Update the value of the process to the value of the previous process .

      B. The value of the process must be printed on the screen .

The program will take from the user a positive integer, will create a circle of n processes.
For each of the processes an arbitrary initial value will be drawn and the following menu will be given to the user:

  o View values of the processes .

  o Take a step (each process performs exactly one step "synchronous system" ) .

  o Exit
  
  
  To run the code :
  
  
  
  
  Example : 
  
  
  
