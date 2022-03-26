# PriorityQuereWithCsvFile
V.1 2021-10-24

Generates a simple program to push by priority, pop by priority , load data from csv

and save with Priorty Queue.

Node.h declares few elements that a node need.

Node.ccp defines the functions that have been declared in Node.have

LinkedList.h declares few elements that a queue need.

LinkedList.cpp defines the functions that have been declared in Node.have

main function is at Main.cpp.

Once the program runs, it will loop until the user hits 0 until then the user can

dequeue, enqueue, peek, load "patient.csv", save to "patient.csv" as many times as they want.




Terminal will show the following introduction

=============================================
Welcome to Fanshawe's College Medical Center
=============================================
Please make a selection then press Enter:
1. Add a patient
2. Process Next Patient In Queue
3. Display Queue
4. View Processed Patients History
5. Load Queue From External 'csv' File
6. Save Queue To An External 'csv' File
0. Exit


press 1 to save patient by 5 parameters and save them to csv File.

Press 2 to pop the highest priority patient and remove them from the queue.

press 3 to display the current queue status

press 4 to display the previous patients which contains in history queue.

press 5 to load queue according to the implemented csv File

press 6 to save the queue to the implemented csv file again to prevent data loss

press 0 to Exit the Terminal

press other key will continue the loop
