**TASK. Favorite colour program**

***1. Read the following user story and requirement.***

***User story***

As a user I want to be able to convert text file with an information related to image 16x16 based on my favorite colour preferences: if we have a pixel of my favorite color then corresponding left and top pixel should be changed to that color. This will allow me to have more beatiful pictures.


***Requirement 1:***

User should be able to provide input file name, favorite color info and the name of the output file.

***Requirement 2:***

Program should be able to check each data point of the input 16x16 format and if it matches provided favorite colour then left and top data point should be set to that color as well.

***Requirement 3:***

Program should validate the input data format and report 

***Design notes***

We are plan to use input format like this. Each pixel is stored as 3 integers separated by comma, each integer should belong to the range from 0 to 255. Each line contains 16 pixels separated by space. File should contain 16 lines.


***2. Test cases***

Write 5 different test cases to cover different scenarios for the user story and requirements from above. Automate them.
### Test case -1
User inputs:
```
1.txt
1,7,3
1o.txt
```
Output:
```
Error opening file 1.txt
```
### Test case 1
User inputs:
```
1i.txt
1,7,3
1o.txt
```

1i.txt is in ./testing2.2
1o.txt should be as ./testing2.2/1t.txt

### Test case 2
User inputs:
```
2i.txt
255,34,153
2o.txt
```


2i.txt is in ./testing2.2
2o.txt should be as ./testing2.2/2t.txt

### Test case 3
User inputs:
```
3i.txt
1,2,3
3o.txt
```


3i.txt is in ./testing2.2
3o.txt should be as ./testing2.2/3t.txt

### Test case 4
User inputs:
```
4i.txt
128,128,128
4o.txt
```


4i.txt is in ./testing2.2
4o.txt should be as ./testing2.2/4t.txt

### Test case 5
User inputs:
```
5i.txt
1,2,3
5o.txt
```


5i.txt is in ./testing2.2
5o.txt should be as ./testing2.2/5t.txt

***3. Implementation***

Implement a C++ program based on the requirements from above. Use your automation to test it.

