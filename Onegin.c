#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//----------------------------------------------------------------

//Calculates a size 
long long SizeofFile(FILE * ptrfile, long int offset, int origin);

//Creates main buffer
char * CreateBuff(long long size);

//Counts number of symbols and changed '\n' to '\0'
long long CountChange(long long size, char * buffer);

//Creates small buffer of pointers
char ** CreateLittleBuff(long long strings);

//Distributes pointers of sentenses
int Allocate(char ** littlebuffer, char * mainbuff, long long size, long long strings);

//Prints arrays of symbols or pointers
void Printing();

//Compares strings
int Compare(const void * str1, const void * str2);

//----------------------------------------------------------------

long long SizeofFile(FILE * ptrfile, long int offset, int origin)
{
	if(ptrfile == NULL)
	{
		printf("Incorrect reading of file\nEmeregency shutdown\n");
		exit(1);
	}
	fseek(ptrfile, offset, origin);
	long long size = ftell(ptrfile);
	rewind(ptrfile);	
	return size;
}

char * CreateBuff(long long size)
{
	char * buffer = (char *)calloc(size, sizeof(char));
	if(buffer == NULL)
	{
		printf("Error assigning memory\nEmergency shutdown\n");
		exit(2);
	}
	return buffer;
}

char ** CreateLittleBuff(long long strings)
{
	char ** littlebuffer = (char **)calloc(strings, sizeof(char *));
	if(littlebuffer == NULL)
	{
		printf("Error assigning memory\nEmergency shutdown\n");
		exit(2);
	}
	return littlebuffer;
}

long long CountChange(long long size, char * buffer)
{
	int i = 0;
	long long counter = 0;
	for(i = 0; i < size; i++)
	{
		if(buffer[i] == '\n')
		{
			buffer[i] = '\0';
			counter++;
		}
	}
	return counter;
}

int Allocation(char ** littlebuffer, char * mainbuff, long long size, long long strings)
{
	int i = 1, j = 1, k = 0;
	littlebuffer[0] = mainbuff;
	for(i = 1, j = 1; i < size - 1; i++)
	{
		if(mainbuff[i] == '\0')
		{
			littlebuffer[j] = mainbuff + i + 1;
			j++;
		}
	}
	if(j != (int)strings)
		printf("There is a mistake with allocation of pointers to little buffer\n");
	else
		return j;
}

/*void Printing()
{
	int i = 0;
	
}*/

int Compare(const void * str1, const void * str2)
{
	if(str1 == NULL || str2 == NULL)
	{
		printf("Incorrect reading of an array element\nEmeregency shutdown\n");
		exit(3);
	}
	char* string1 = (char*)str1;
	char* string2 = (char*)str2;
	return strcmp(string1, string2);
}

int main(int argc, char * argv[])
{
	FILE * ptrfile = fopen(argv[1], "r");
	long long size = SizeofFile(ptrfile, 0, SEEK_END);
	char * mainbuff = CreateBuff(size);
	fread(mainbuff, sizeof(char), size, ptrfile);

	long long strings = CountChange(size, mainbuff);
	char ** littlebuff = CreateLittleBuff(strings);

	Allocation(littlebuff, mainbuff, size, strings);

	qsort(littlebuff, strings, sizeof(char *), Compare);

	int i = 0;
	for(i = 0; i < strings; i++)
		printf("%s\n\n", littlebuff[i]);
	
	fclose(ptrfile);
	return 0;
}
