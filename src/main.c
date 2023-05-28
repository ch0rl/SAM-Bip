#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "reciter.h"
#include "sam.h"

#include <SDL.h>
#include <SDL_audio.h>


// Approximations of some Windows functions to ease portability
#if defined __GNU_LIBRARY__ || defined __GLIBC__
static void strcat_s(char * dest, int size, char * str) {
    unsigned int dlen = strlen(dest);
    if (dlen >= size-1) return;
    strncat(dest+dlen, str, size - dlen - 1);
}
void fopen_s(FILE ** f, const char * filename, const char * mode) {
    *f = fopen(filename,mode);
}
#endif

void WriteWav(char* filename, char* buffer, int bufferlength)
{
	unsigned int filesize;
	unsigned int fmtlength = 16;
	unsigned short int format=1; //PCM
	unsigned short int channels=1;
	unsigned int samplerate = 22050;
	unsigned short int blockalign = 1;
	unsigned short int bitspersample=8;

	FILE *file;
	fopen_s(&file, filename, "wb");
	if (file == NULL) return;
	//RIFF header
	fwrite("RIFF", 4, 1,file);
	filesize=bufferlength + 12 + 16 + 8 - 8;
	fwrite(&filesize, 4, 1, file);
	fwrite("WAVE", 4, 1, file);

	//format chunk
	fwrite("fmt ", 4, 1, file);
	fwrite(&fmtlength, 4, 1, file);
	fwrite(&format, 2, 1, file);
	fwrite(&channels, 2, 1, file);
	fwrite(&samplerate, 4, 1, file);
	fwrite(&samplerate, 4, 1, file); // bytes/second
	fwrite(&blockalign, 2, 1, file);
	fwrite(&bitspersample, 2, 1, file);

	//data chunk
	fwrite("data", 4, 1, file);
	fwrite(&bufferlength, 4, 1, file);
	fwrite(buffer, bufferlength, 1, file);

	fclose(file);
}

void PrintUsage()
{
	printf("usage: sam Word1 Word2 ....\n");	
}

int pos = 0;

int main(int argc, char **argv)
{
	int i;

	char* wavfilename = "sam-bip.wav";
	unsigned char input[256];
	
	memset(input, 0, 256);

	if (argc <= 1)
	{
		PrintUsage();
		return 1;
	}

	i = 1;
	while(i < argc)
	{
		strcat_s((char*)input, 256, argv[i]);
		strcat_s((char*)input, 256, " ");
		
		i++;
	} //while

	for(i=0; input[i] != 0; i++)
		input[i] = (unsigned char)toupper((int)input[i]);
	
	strcat_s((char*)input, 256, "[");
	if (!TextToPhonemes(input)) return 1;

	if ( SDL_Init(SDL_INIT_AUDIO) < 0 ) 
	{
		printf("Unable to init SDL: %s\n", SDL_GetError());
		exit(1);
	}
	atexit(SDL_Quit);

	SetInput(input);
	if (!SAMMain())
	{
		PrintUsage();
		return 1;
	}

	WriteWav(wavfilename, GetBuffer(), GetBufferLength() / 50);
	
	return 0;
}
