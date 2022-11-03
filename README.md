# low level 3d wireframe graphics

I recently took a C programming course. To practice, I will try in this project to implement basic wireframe 3d graphics. The goal is to stay as low-level as possible, by only using the basic standard library.

## Bibliography and interesting links

The graphical part is handled by writing directly to Linux's framebuffer file. I followed this tutorial : [http://betteros.org/tut/graphics1.php](http://betteros.org/tut/graphics1.php)

This web page introduces the basic of perspective projection in computer graphics [http://learnwebgl.brown37.net/08_projections/projections_perspective.html](http://learnwebgl.brown37.net/08_projections/projections_perspective.html)


## how to run

- compile with `make main`
- run `./3d_wireframe.out`

Compiling requires superuser privileges, as the executable produced needs to be in the video group to be able 
to write in the framebuffer.

Be aware. The graphics are handled directly at the linux kernel level, i.e. deeper than your windows manager level.
I'm not sure, how all of this works, but my code will produce nothing if you have a graphics manager, like X or wayland
running.

What I do :

- go to an empty tty by typing `Ctrl+Alt+F3` for example
- if you never did this, be aware, from now on, you'll have to work only through the terminal, 
and you should go back to your session if you type `Ctrl+Alt+F1`
