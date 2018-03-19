
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#define MAX_SIZE 30
#define ARR_SIZE 92

void check(int c, FILE *file, FILE *output_file);
void removeSubstr(char *string, char *sub, long length);
void inScript(FILE *file);
void win();

void win() {
    puts("You have obtained code execution.");
}

// onclick=' '
void removeSubstr(char *string, char *sub, long length) {
    char *match;
    long len = strnlen(sub, MAX_SIZE);
    while ((match = strstr(string, sub))) {
        *match = '\0';
        char* leftover = match+len;
        char apos = leftover[0];
        char *ret;
        ret = memchr(leftover+1, apos, strnlen(leftover, length-len)-1);
        long offset = strnlen(leftover, length-len) - strnlen(ret, length-len) + 1;
        strncat(string, match+len+offset, length);
    }   
}

int main(int argc, char** argv) {
	int i;
	char ch_arr[ARR_SIZE][25] = { "onclick=", "onmouseup=", "oncontextmenu=", "ondblclick=", "onmousedown=", "onmouseenter=", "onmouseleave=", "onmousemove=", "onmouseover=", "onmouseout=", "onmouseup=", "onkeydown=", "onkeypress=", "onkeyup=", "onabort=", "onbeforeunload=", "onerror=", "onhashchange=", "onload=", "onpageshow=", "onpagehide=", "onresize=", "onscroll=", "onunload=", "onblur=", "onchange=", "onfocus=", "onfocusin=", "onfocusout=", "oninput=", "oninvalid=", "onreset=", "onsearch=", "onselect=", "onsubmit=", "ondrag=", "ondragend=", "ondragenter=", "ondragleave=", "ondragover=", "ondragstart=", "ondrop=", "oncopy=", "oncut=", "onpaste=", "onafterprint=", "onbeforeprint=", "onabort=", "oncanplay=", "oncanplaythrough=", "ondurationchange=", "onemptied=", "onended=", "onerror=", "onloadeddata=", "onloadedmetadata=", "onloadstart=", "onpause=", "onplay=", "onplaying=", "onprogress=", "onratechange=", "onseeked=", "onseeking=", "onstalled=", "onsuspend=", "ontimeupdate=", "onvolumechange=", "onwaiting=", "animationend=", "animationiteration=", "animationstart=", "transitionend=", "onerror=", "onmessage=", "onopen=", "onmessage=", "onmousewheel=", "ononline=", "onoffline=", "onpopstate=", "onshow=", "onstorage=", "ontoggle=", "onwheel=", "ontouchcancel=", "ontouchend=", "ontouchmove=", "ontouchstart=", "CAPTURING_PHASE=", "AT_TARGET=", "BUBBLING_PHASE="};

    FILE *file;
    FILE *output;
    FILE *new_input;
    FILE *new_output;
    char cont;
    long length;
    char * buffer = 0;

    int iflag = 0;
    int oflag = 0;
    char c;
    char *ivalue = NULL;
    char *ovalue = NULL;

    // Parse the command line
    while ((c = getopt(argc, argv, "i:o:")) != -1)
    {
        switch (c)
        {
        case 'i':                   // Prints help message
        iflag = 1;
        ivalue = optarg;
        break;
        case 'o':                   // Emits additional diagnostic info
        oflag = 1;
        ovalue = optarg;
        break;
        default:
        break;
        }
    }

    //Must handle flag usage
    // -i [inputfile] -o [outputfile]
    if (!iflag) {
        file = fopen(argv[1], "rb");
        ivalue = argv[1];
    } else {
        file = fopen(ivalue, "rb");        
    }

    if (!oflag) {
        output = fopen(argv[2], "wb+");
        ovalue = argv[2];
    } else {
        output = fopen(ovalue, "wb+");        
    }

    if (file == NULL) {
        puts("Can't open file");
        exit(0);
    }

    if (output == NULL) {
        puts("Can't open file");
        exit(0);
    }

    while (cont != EOF) {
        cont = fgetc(file);
        if (cont == EOF) break;
        check(cont, file, output);
    }
    fclose(file);
    fclose(output);

    new_input = fopen(ovalue, "rb");
    fseek(new_input, 0, SEEK_END);
    length = ftell(new_input);
    fseek(new_input, 0, SEEK_SET);
    buffer = malloc(length+1);
    if (buffer) {
        fread(buffer, 1, length, new_input);
    }
    fclose(new_input);
    buffer[length] = 0;

    new_output = fopen(ovalue, "wb");
    if (buffer) {
        for (i=0; i < ARR_SIZE; i++) {
            removeSubstr(buffer, *(ch_arr+i), length);
        }
        fputs(buffer, new_output);
    }
    fclose(new_output);
    free(buffer);
    return 0;
}


//Check function looks for "<script" beginning tag
//Will print to screen if at any time "<script" is broken
//Then calls inScript to look for ending tag /script> removing all
//The text in between <script and /script> if beginning tag passed
void check(int c, FILE *file, FILE *output_file) {
	int one, two, three, four, five, six;
	if (c == '<')
	{
		one = fgetc(file);
		if (one == 's') { 
			two = fgetc(file);
			if (two == 'c') {
				three = fgetc(file);
				if (three == 'r') {
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

void inScript(FILE *file) {

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
