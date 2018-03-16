
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>




void win()
{
  printf("You win");
}



int main(int argc, char** argv)
{
  FILE *file;
  char inputfile[200], cont;
  char outputfile[200];

  //Must handle flag usage
  // -i [inputfile] -o [outputfile]
  file = fopen(argv[1], "r");

  if (file == NULL)
  {
    printf("Can't open file \n");
    exit(0);
  }

  cont = fgetc(file);

  while (cont != EOF)
  {
    cont = fgetc(file);
		//Instead of printing each character, Call check
		check(cont, file);
  }
  fclose(file);
  return 0;
}


//Check function looks for "<script" beginning tag
//Will print to screen if at any time "<script" is broken
//Then calls inScript to look for ending tag /script> removing all
//The text in between <script and /script> if beginning tag passed
void check(int c, FILE *file)
{
	int one, two, three, four, five, six;
	if (c == '<')
	{
		one = fgetc(file);
		if (one == 's') { 
			two = fgetc(file);
			if (two == 'c') {
				three = fgetc(file);
				if (three = 'r') {
					four = fgetc(file);
					if (four == 'i') {
						five = fgetc(file);
						if (five == 'p') {
							six = fgetc(file);
							if (six == 't') {
								inScript(file);
							}
							else { printf("%c", c); printf("%c", one); printf("%c", two); printf("%c", three); printf("%c", four); printf("%c", five); printf("%c", six); } 
						}
						else { printf("%c", c); printf("%c", one); printf("%c", two); printf("%c", three); printf("%c", four); printf("%c", five); } 
					}
					else { printf("%c", c); printf("%c", one); printf("%c", two); printf("%c", three); printf("%c", four);}
				}
				else { printf("%c", c); printf("%c", one); printf("%c", two); printf("%c", three);}
			}
			else { printf("%c", c); printf("%c", one); printf("%c", two);}
		}
		else { printf("%c", c); printf("%c", one);}
	}
	else {printf("%c", c);}
}

void inScript(FILE *file)
{

	int one, two, three, four, five, six, seven, eight;
	one = fgetc(file);
	two = fgetc(file);
	three = fgetc(file);
	four = fgetc(file);
	five = fgetc(file);
	six = fgetc(file);
	seven = fgetc(file);
	eight = fgetc(file);

	while(one != '/' || two != 's' || three != 'c' || four != 'r' || five != 'i' 
					|| six != 'p' || seven != 't' || eight != '>')
	{
		one = two;
		two = three;
		three = four;
		four = five;
		five = six;
		six = seven;
		seven = eight;
		eight = fgetc(file);

	}

}  

  

