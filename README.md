# Projet Report Rubikscube
## Welcome
Welcome 🤗 in our github project ! <br>
You'll find the progression of the code in [commits](https://github.com/jeandtx/Projet-Rubikscube/commits/main).
<br><br>

## The code 👨‍💻
The full program is divided in only two files:
* The [main.c](https://github.com/jeandtx/Projet-Rubikscube/blob/main/main.c) which create the rubikscube and diplay the user interface
* The [pack.h](https://github.com/jeandtx/Projet-Rubikscube/blob/main/pack.h) which is a header file implement in main.c and who contain all our functions and structure definitions. <br><br>

the cube is represented as an array of faces, which are an array of lines, which are an array of colored squares.
This makes it a 3D array.<br>
In this configuration, turning the front face of the cube requires a different algorithm than turning the right or up faces of the cube. Making all these algorithms would require a lot of code.<br>
Instead, we decided to use functions already built : <br>
* turning the cube horizontally<br>
* turning the cube vertically<br>

Using these two functions, we can make any face become the front face. Then, we can use the "turn front face" function, and flip the cube back ✨<br><br>
Since any movement is a combination of turning the cube vertically, horizontally and turning the front face,
> We only need three movements to generate all other movements of the cube !<br>

## Algorithmics 🧠

### Turning a face :<br>
When turning a face, we have to rotate a square of nine blocks by a quarter of a turn in the clockwise direction.
To perform this action, we can first copy the values of these nine squares into a 2D array.<br>
Then, we manually map out where they should be placed in the new, rotated face.<br>
We paste the saved blocks into their new place in the selected face.<br> 
To make the code look prettier, we find patterns in the copying and pasting processes,<br> and emulate them using 'for loops'.
##### note that we couldn't achieve a similar result when turning the crown (blocks adjascent to the rotated face that circle around it).

### Horizontally turning the cube<br>

 
## Our product 📦

The rubiks cube appears as a colored patron
##### (the orange side will be represented in purple)

On the right side of the patron, a box appears and demands you make a wish 🧚🏽‍♀️<br> 
* Scramble
* Blank
* Fill             
* QuitReset
* pivot front face  
* turn cube horizontaly
* turn cube verticaly

###### *note that the three last functions can be considered as building blocks,<br>from which all other movements of the cube can be created*<br><br>

as shown in picture 👇
<img width="1060" alt="Capture de l'interface" src="https://user-images.githubusercontent.com/75331707/119239340-b4c85780-bb48-11eb-99fb-320da4c6bfe1.png">

## Encountered [difficulties](https://github.com/jeandtx/Projet-Rubikscube/issues)
Our first struggles were encountered when attempting to build the function that simply turns the front face.<br>

> ##### Figuring out the allocation of each unit of each face and placing them correctly, as well as determining an algorithm to make this process more efficient, was troublesome. However, our main difficulties were in communication.
<br>

Our disagreements, misunderstandings and imperfect communication sometimes lead to little to no progress in some coding sessions.
<br>
<br>

> ##### However, this prompted us to keep explaining our algorithms, giving us both a better understanding of why our code would or would not work.
<br>

We also tried to produce code to pivot any face, but it appeared that this feat would be much more tedious than expected.
<br>
<br>

> ##### we could not find an universal algorithm (each face turn would have its own function
<br>

A final issue that we encountered were coding together, in viso.. But we closed it quite fast because we knew tools like [Live Share](https://visualstudio.microsoft.com/fr/services/live-share/) on VS code or [github](https://github.com/home) a version control manager.
<br>
<br>

## lessons of this project

### In this project, we learned how to : 
* work as a team 🤝
  * ##### we extensively used the liveshare functions of VS code, as well as Discord's screenshares and audio calls.
* use git and github ! <img width="30" alt="Github" src="https://user-images.githubusercontent.com/75331707/119240715-d843d000-bb51-11eb-95ce-2ded55f55529.png">
  * ##### with numerous commits, pulls & pushes to the main git branch. 
* make algorithms before blindly coding 👨🏽‍🦯
  * ##### by making the mistake, a lot of times. Finally we mastered the use of VS code's whiteboard, allowing us to visualy represent our algorithms.

<br>
<br>

## prospect for improving your project
For the next project:
* We will focus more on algorithms
* make a project schedule and to-do list
* regularly review what we did in regards to our wider endeavor

<br>


## Contributors 🦾
* [Oscar Byrne](https://github.com/osbyrne)
* [Jean Doutriaux](https://github.com/jeandtx)
