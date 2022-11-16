# low level 3d wireframe graphics

I recently took a C programming course. To practice, I will try in this project to implement basic wireframe 3d graphics. The goal is to stay as low-level as possible, by only using the basic standard library.

## Bibliography and interesting links

The graphical part is handled by writing directly to Linux's framebuffer file. I followed this tutorial : [http://betteros.org/tut/graphics1.php](http://betteros.org/tut/graphics1.php)

This web page introduces the basic of perspective projection in computer graphics [http://learnwebgl.brown37.net/08_projections/projections_perspective.html](http://learnwebgl.brown37.net/08_projections/projections_perspective.html)


## how to run

- compile with `make main`
- run `./3d_wireframe.out my_polygon_file.pff`

❗ Compiling requires superuser privileges, as the executable produced needs to be in the video group to be able 
to write in the framebuffer.

Be aware. The graphics are handled directly at the linux kernel level, i.e. deeper than your window manager level.
I'm not sure how all of this works, but my code will produce nothing if you have a graphics manager,like X or wayland or any
window manager running.

What I do :

- go to an empty tty by typing `Ctrl+Alt+F3` for example
- if you never did this, be aware, from now on, you'll have to work only through the terminal, 
and you should go back to your session if you type `Ctrl+Alt+F1`

## Polygon file

`my_polygon.pff` is just an example of a polygon file, you can display arbitrary polygons by creating your own polygon file 
using the following syntax : 

```
integer : number of vertex V
integer : number of edges E

3 floats : x,y,z coordinate of point 0
3 floats : x,y,z coordinate of point 1
.
.
.
3 floats : x,y,z coordinate of point V-1

2 integers : a and b corresponding to the two points linked by edge 0
2 integers : a and b corresponding to the two points linked by edge 1
.
.
.
2 integers : a and b corresponding to the two points linked by edge E-1
```

The python script `obj_to_pff.py` allows to convert a 3d object in `.obj` format to a `.pff` readable by this program.

You have to modify the script to make it work, but I might make it a command line program at some point.

## Architecture

```
.
├── 3d_mesh.c
├── 3d_mesh.h # 3d points, polygons, vector/matrix operations and screen projection
├── iz-graphics.c
├── iz-graphics.h # access to framebuffer service, configuration and graphics primitives (lines)
├── line.c # test of iz-graphics that prints random lines
├── line.h
├── main.c # keyboard input + drawing frame
├── main.h
├── parse_polygon.c
├── parse_polygon.h # parse pff file and produce polygon object
├── obj_to_pff.py # python script to convert .obj to .pff
├── polygon.pff # cube 3d model
├── suzanne.pff # monkey 3d model
├── Makefile 
└── README.md
```

## Controls

Once the program is running, you can move the camera using the following keys :
- `z` `s` translate forward and backward
- `q` `d` translate right and left
- `a` `e` translate up and down

- `i` `k` rotate up and down
- `j` `l` rotate right and left
- `u` `o` rotate