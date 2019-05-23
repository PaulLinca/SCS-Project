# Draw Cutting Trajectory - Work in Progress

**Requirement**<br />
The subject of this project is developing a program that controls laser cutting machine.
The program reads a file that contains the cutting trajectory as a sequence of segments and arcs and generates commands for bi-directional movements (x,y) of the cutting edge. The movement of the cutting edge will be simulated on the computer screen.

**Chosen approach**<br />
I've chosen C/C++ language to develop the application along with the SDL 2.0 library to implement the graphic simulation.

**How it works**<br/>
The program will from a file point coordinates from which lines and circles will be drawn. <br/>
A window with a blue blackground (reminiscent of blueprints) will be created that will be our canvas.

<p align="center"> <img src="Images/window.png" /> </p>

The program will proceed to drawing the lines and the circles point by point, simulating a laser cutting machine that follows a given trajectory.

<p align="center"> <img src="Images/drawnInput.png" /> </p>

Lastly, the user can add additional lines or circles using the mouse as a pointer and the mouse buttons to getermine the size of the objects.

<p align="center"> <img src="Images/mouseInput.png" /> </p>

