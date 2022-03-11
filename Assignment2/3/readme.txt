GENERAL INSTRUCTIONS:
1. Insert your input in input.txt
2. The input should be in appropriate format
3. The commands accepted by the programs are as follows:
 - mf hello.txt "This is hello" --this will make a file with filename hello.txt with the content "This is hello". It is mandatory to provide the content within "".
 - pf hello.txt -- this will print the contents of hello.txt
 - rf hello.txt random.txt -- this will rename the filename to random.txt
 - df random.txt -- this will delete the file named random.txt
 - ls -- this will list all the files present in the filesystem
 
 N.B. - This disk blocks that are created will not be deleted and cannot be accessed after the program's execution is over because the filesystem is maintained in runtime with the help of structure.
      - The disk blocks are present under root/ present in the folder named 3.
 

INPUT FORMAT:
1. Enter the commands in the console after running the applicaton.
2. The output will appear in the console itself.

FOR WINDOWS:
Build and run the .cpp file in an IDE of your choice

FOR UBUNTU:
Open the directory in terminal. Simply type ./3 to run the file
