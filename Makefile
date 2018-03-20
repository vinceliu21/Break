remove_scripts: remove_scripts.c malloc-2.7.2.c
	gcc -g -O0 -m32 -fno-stack-protector -o remove_scripts remove_scripts.c malloc-2.7.2.c
	execstack -s remove_scripts 

