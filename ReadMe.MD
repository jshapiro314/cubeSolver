#Computer Graphics Project Proposal#
Participants: Joshua Shapiro | 2016951067 Software Used: Tizen

I propose to create a mobile application that solves Rubik’s Cubes. This application will use openGLES to display a 3D Rubik’s cube on screen that the user can rotate and manipulate. Using either a 2D layout or physically tapping on the 3D cube, the user can input the colors of each square, setting the cube to a desired configuration. Once set, the user can press the “Solve” button and the cube will show step-by-step instructions on how to solve the cube by rotating into the correct position on screen.

This will use openGLES to display the Rubik’s Cube and allow the user to manipulate it. Additionally, openGLES will be used to rotate specific slices of the cube during the solving process. Texture mapping will also be used as colors will have to be attached to the squares on the cube.

The input method the user will use to “mix up” the cube has yet to be determined. It may be through a 2D “unfolded” version of the cube that they can easily tap on to choose square colors or it may be through tapping squares on the 3D cube. If possible, I would like to use the camera to take a picture of an actual Rubik’s Cube and map the colors automatically to the 3D cube face. I will add this feature only if I have time and I have completed the other requirements.

The app’s output will be the 3D cube solving itself. It will step through each instruction of the solution by rotating the slices of the 3D cube to give the user a visual representation of each instruction. The user would be able to follow along with their own Rubik's Cube to successfully solve their physical cube. If the user inputs an invalid starting state (invalid state is when the user puts the colors on the squares in a way that a physical Rubik's Cube could never appear), the program will notify the user that the input state has no solution.

There has been extensive research in algorithms to solve Rubik's Cubes. As this is a computer graphics course and not an algorithms course, I plan to use some of the publicly available solving algorithms instead of trying to create my own. This will allow me to spend more time focusing on the openGLES portion of this project.
