#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Sentence
{
	char * begin;
	char * end;
	long long size;
};

struct StructBuff
{
	long long strings;
	struct Sentence * structpoint;
};

//----------------------------------------------------------------

//Calculates a size, creates main buffer and buffer of pointers,\
 counts number of symbols and changed '\n' to '\0', distributes pointers of sentenses
struct StructBuff Prepare(char * argv);

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
int Printing(struct StructBuff structbuff);

//Compares strings
int Compare(const void * str1, const void * str2);

//Cleans dynamic memory
void CleanMem(char * mainbuffer, char ** pointsbuffer);////////////

//----------------------------------------------------------------

/*long long SizeofFile(FILE * ptrfile, long int offset, int origin)
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
*/

int Printing(struct StructBuff structbuff)
{
	
}

int Compare(const void * str1, const void * str2)
{
	if(str1 == NULL || str2 == NULL)
	{
		fprintf(stderr, "Incorrect reading of an array element\n"
							"Emeregency shutdown\n");
		///errno
	}
	struct Sentence * struct1 = (struct Sentence *)str1;
	struct Sentence * struct2 = (struct Sentence *)str2;
	return strcmp((struct1->begin), (struct2->begin));
}

void CleanMem(char * mainbuffer, char ** pointsbuffer)
{
	free(mainbuffer);
	free(pointsbuffer);
}

struct StructBuff Prepare(char * argv)
{
	struct Sentence sentense;
	int i = 0, j = 0, k = 0;
	long long strings = 0;
	
	FILE * ptrfile = fopen(argv, "r");

	fseek(ptrfile, 0, SEEK_END);
	long long size = ftell(ptrfile);
	rewind(ptrfile);	
	
	char * mainbuffer = (char *)calloc(size, sizeof(char));

	fread(mainbuffer, sizeof(char), size, ptrfile);	
	
	for(i = 0; i < size; i++)
	{
		if(mainbuffer[i] == '\n')
		{
			mainbuffer[i] = '\0';
			strings++;
		}
	}
	
	struct Sentence * structbuffer = (struct Sentence *)calloc(strings, sizeof(struct Sentence));

	structbuffer[0].begin = mainbuffer;
	structbuffer[strings - 1].end = mainbuffer + size - 1;
	for(i = 1, j = 1; i < size - 1; i++)
	{
		if(mainbuffer[i] == '\0')
		{
			structbuffer[j].begin = mainbuffer + i + 1;
			structbuffer[j - 1].end = mainbuffer + i - 1;
			j++;			
		}
	}

	struct StructBuff structbuff = {strings, structbuffer};

	return structbuff;
}

int main(int argc, char * argv[])
{
	struct StructBuff structbuff = Prepare(argv[1]);
	int i = 0;
	for(i = 0; i < structbuff.strings; i++)
	{
		printf("%p\n", structbuff.structpoint[i].begin);
		printf("%p\n", structbuff.structpoint[i].end);
		printf("%s\n", structbuff.structpoint[i].begin);
		//printf("%s\n", structbuff.structpoint[i].end);
		printf("\n");
	}

	qsort(structbuff.structpoint, structbuff.strings, sizeof(struct Sentence), Compare);

	printf("--------------------------------------------------\n");

	for(i = 0; i < structbuff.strings; i++)
	{
		printf("%p\n", structbuff.structpoint[i].begin);
		printf("%p\n", structbuff.structpoint[i].end);
		printf("%s\n", structbuff.structpoint[i].begin);
		//printf("%s\n", structbuff.structpoint[i].end);
		printf("\n");
	}

	//Printing(pointsbuffer, strings);

	//CleanMem(mainbuff, pointsbuffer);
	return 0;
}








