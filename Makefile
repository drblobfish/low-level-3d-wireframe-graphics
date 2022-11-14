main :
	gcc -g *.c -o 3d_wireframe.out -lm
	sudo chgrp video ./3d_wireframe.out
	sudo chmod g+s ./3d_wireframe.out

line :
	gcc -g line.c -o line.out
	sudo chgrp video ./line.out
	sudo chmod g+s ./line.out
