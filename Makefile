main :
	gcc -g main.c iz-graphics.c -o 3d_wireframe.out
	sudo chgrp video ./3d_wireframe.out
	sudo chmod g+s ./3d_wireframe.out

line :
	gcc -g line.c -o line.out
	sudo chgrp video ./line.out
	sudo chmod g+s ./line.out
