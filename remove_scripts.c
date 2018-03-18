
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


#define MAX_SIZE 500


void win()
{
  printf("You have obtained code execution.");
}

// onclick=' '
void removeSubstr (char *string, char *sub) {
    char *match;
    int len = strnlen(sub, MAX_SIZE);
    while ((match = strstr(string, sub))) {
        *match = '\0';

        // match+len[0] == ' or "
        char* leftover = match+len;
        char apos = leftover[0];
        // printf("%c\n", apos);
            
        // find the next occurence of ' or "
        char *ret;
        ret = memchr(leftover+1, apos, strnlen(leftover, MAX_SIZE )-1);
        // ret + 1 the rest of the string we want
        // puts(ret+1);

        int offset = strnlen(leftover, MAX_SIZE) - strnlen(ret, MAX_SIZE) + 1;
        strncat(string, match+len+offset, len+offset);
    }   

}





int main(int argc, char** argv)
{

	int i;
	char ch_arr[92][25] = { "onclick=", "onmouseup=", "oncontextmenu=", "ondblclick=", "onmousedown=", "onmouseenter=", "onmouseleave=", "onmousemove=", "onmouseover=", "onmouseout=", "onmouseup=", "onkeydown=", "onkeypress=", "onkeyup=", "onabort=", "onbeforeunload=", "onerror=", "onhashchange=", "onload=", "onpageshow=", "onpagehide=", "onresize=", "onscroll=", "onunload=", "onblur=", "onchange=", "onfocus=", "onfocusin=", "onfocusout=", "oninput=", "oninvalid=", "onreset=", "onsearch=", "onselect=", "onsubmit=", "ondrag=", "ondragend=", "ondragenter=", "ondragleave=", "ondragover=", "ondragstart=", "ondrop=", "oncopy=", "oncut=", "onpaste=", "onafterprint=", "onbeforeprint=", "onabort=", "oncanplay=", "oncanplaythrough=", "ondurationchange=", "onemptied=", "onended=", "onerror=", "onloadeddata=", "onloadedmetadata=", "onloadstart=", "onpause=", "onplay=", "onplaying=", "onprogress=", "onratechange=", "onseeked=", "onseeking=", "onstalled=", "onsuspend=", "ontimeupdate=", "onvolumechange=", "onwaiting=", "animationend=", "animationiteration=", "animationstart=", "transitionend=", "onerror=", "onmessage=", "onopen=", "onmessage=", "onmousewheel=", "ononline=", "onoffline=", "onpopstate=", "onshow=", "onstorage=", "ontoggle=", "onwheel=", "ontouchcancel=", "ontouchend=", "ontouchmove=", "ontouchstart=", "CAPTURING_PHASE=", "AT_TARGET=", "BUBBLING_PHASE="};

  FILE *file;
	FILE *output;
	FILE *new_input;
	FILE *new_output;
  char inputfile[200], cont;
  char outputfile[200];	
	long length;
	char * buffer = 0;

  //Must handle flag usage
  // -i [inputfile] -o [outputfile]
  file = fopen(argv[1], "r");

	output = fopen(argv[2], "w+");


  if (file == NULL)
  {
    printf("Can't open file \n");
    exit(0);
  }


  while (cont != EOF)
  {
    cont = fgetc(file);
		if (cont == EOF) break;
		//Instead of printing each character, Call check
		check(cont, file, output);
  }
  fclose(file);
	fclose(output);

	//First handled for <script> tags
	//Now reopen file and handle for event listener tags	
	new_input = fopen(argv[2], "r");

	fseek(new_input, 0, SEEK_END);
	length = ftell(new_input);
	fseek(new_input, 0, SEEK_SET);
	buffer = malloc(length);
	if (buffer) {
		fread(buffer, 1, length, new_input);
	}
	fclose(new_input);
	new_output = fopen(argv[2], "w");

	if (buffer) {
		for (i=0; i < 3; i++)
		{
			removeSubstr(buffer, *(ch_arr+i));
		}
		fputs(buffer, new_output);
	}
	fclose(new_output);

  return 0;
}


//Check function looks for "<script" beginning tag
//Will print to screen if at any time "<script" is broken
//Then calls inScript to look for ending tag /script> removing all
//The text in between <script and /script> if beginning tag passed
void check(int c, FILE *file, FILE *output_file)
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
							else { fputc(c, output_file); fputc(one, output_file); fputc(two, output_file); fputc(three, output_file); fputc(four, output_file); fputc(five, output_file); fputc(six, output_file);  } 
						}
						else { fputc(c, output_file); fputc(one, output_file); fputc(two, output_file); fputc(three, output_file); fputc(four, output_file); fputc(five, output_file); } 
					}
					else { fputc(c, output_file); fputc(one, output_file); fputc(two, output_file); fputc(three, output_file); fputc(four, output_file);}
				}
				else { fputc(c, output_file); fputc(one, output_file); fputc(two, output_file); fputc(three, output_file);}
			}
			else { fputc(c, output_file); fputc(one, output_file); fputc(two, output_file);}
		}
		else { fputc(c, output_file); fputc(one, output_file);}
	}
	else { fputc(c, output_file);}
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

  

