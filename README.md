# Quadtree

The framework used for graphics is SFML. You must install SFML in your system's library path to run the
executable. To compile the project, run 'make' in the root directory. It will generate the exectuable
in the same directory called 'main'. Type './main' to launch the application.

The quadtree accepts the points on the screen and subdivides the larger areas into smaller ones that contain the points in inside it. The green rectangle shows the selected region.

## Key Controls

* Esc: Close window
* I: Print total points to Console
* P: Toggle enter/exit Insert Mode
* S: Toogle show/hide points

## Mouse Controls

* Left click to query a rectangular region with the top-left corner at the mouse cursor.
    * The boundary of this region is green.
    * The points inside the region turn red.
* Drag the cursor to add points.
    * The points are added automatically at the position of the mouse cursor.
    * Exit the Insert Mode to stop adding new points.

![](res/screenshot_01.png)
