
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
    printf("%c", cont);
    cont = fgetc(file);
  }
  fclose(file);
  return 0;
}



  

  

