#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//----------------------------------------------------------------

//Calculates a size 
long long SizeofFile(FILE * ptrfile, long int offset, int origin);//////////////////arguments

//Creates main buffer
char * CreateBuff(long long size);//////////////////////

//Counts number of symbols and changed '\n' to '\0'
long long CountChange(long long size, char * buffer);////////////

//Creates small buffer of pointers
char ** CreatePointersBuff(long long strings);///////////////

//Distributes pointers of sentenses
int Allocate(char ** pointsbuffer, char * mainbuff, long long size, long long strings);///////////

//Prints arrays of symbols or pointers
int Printing(char ** pointsbuffer, long long strings);

//Compares strings
int Compare(const void * str1, const void * str2);

//Cleans dynamic memory
void CleanMem(char * mainbuffer, char ** pointsbuffer);////////////

void Rotation(char * string, int n);

//----------------------------------------------------------------

long long SizeofFile(FILE * ptrfile, long int offset, int origin)
{
	if(ptrfile == NULL)
	{
		printf("Incorrect reading of file\nEmeregency shutdown\n");
		///errno
	}
	fseek(ptrfile, offset, origin);
	long long size = ftell(ptrfile);
	rewind(ptrfile);	
	return size;
}

char * CreateBuff(long long size)
{
	char * mainbuffer = (char *)calloc(size, sizeof(char));
	if(mainbuffer == NULL)
	{
		printf("Error assigning memory\nEmergency shutdown\n");
		///errno
	}
	return mainbuffer;
}

char ** CreatePointersBuff(long long strings)
{
	char ** pointsbuffer = (char **)calloc(strings, sizeof(char *));
	if(pointsbuffer == NULL)
	{
		printf("Error assigning memory\nEmergency shutdown\n");
		///errno
	}
	return pointsbuffer;
}

long long CountChange(long long size, char * mainbuffer)
{
	int i = 0;
	long long counter = 0;
	for(i = 0; i < size; i++)
	{
		if(mainbuffer[i] == '\n')
		{
			mainbuffer[i] = '\0';
			counter++;
		}
	}
	return counter;
}

int Allocation(char ** pointsbuffer, char * mainbuff, long long size, long long strings)
{
	int i = 1, j = 1, k = 0;
	pointsbuffer[0] = mainbuff;
	for(i = 1, j = 1; i < size - 1; i++)
	{
		if(mainbuff[i] == '\0')
		{
			pointsbuffer[j] = mainbuff + i + 1;
			j++;
		}
	}
	if(j != (int)strings)
		printf("There is a mistake with allocation of pointers to little buffer\n");
	else
		return j;
}

int Printing(char ** pointsbuff, long long strings)
{
	if(pointsbuff == NULL)
	{
		printf("Incorrect reading of file\nEmeregency shutdown\n");
		///errno
	}
	int i = 0;
	for(i = 0; i < strings; i++)
		printf("%s\n\n", pointsbuff[i]);
}

int Compare(const void * str1, const void * str2)
{
	if(str1 == NULL || str2 == NULL)
	{
		fprintf(stderr, "Incorrect reading of an array element\nEmeregency shutdown\n");
		///errno
	}
	char** string1 = (char**)str1;
	char** string2 = (char**)str2;
	return strcmp(*string1, *string2);
}

void CleanMem(char * mainbuffer, char ** pointsbuffer)
{
	free(mainbuffer);
	free(pointsbuffer);
}

void Rotation(char * string, int n)
{
	int i = 0;
	char * copystring = (char *)calloc(n, sizeof(char*));
	////
	for(i = 0; i < n; i++)
		copystring[i] = string[n - i];
	for(i = 0; i < n; i++)
		string[i] = copystring[i];
	free(copystring);
}

int main(int argc, char * argv[])
{
/////////////
	FILE * ptrfile = fopen(argv[1], "r");
	long long size = SizeofFile(ptrfile, 0, SEEK_END);
	char * mainbuff = CreateBuff(size);
	fread(mainbuff, sizeof(char), size, ptrfile);

	long long strings = CountChange(size, mainbuff);
	char ** pointsbuffer = CreatePointersBuff(strings);

	Allocation(pointsbuffer, mainbuff, size, strings);
/////////////
	qsort(pointsbuffer, strings, sizeof(char *), Compare);

	Printing(pointsbuffer, strings);

	CleanMem(mainbuff, pointsbuffer);
	fclose(ptrfile);
	return 0;
}








