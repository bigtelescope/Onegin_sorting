#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Sentence
{
	char * begin;
	char * end;
	long int size;
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

//Prints arrays of symbols or pointers
int Printing(struct StructBuff structbuff);

//Compares strings
int Compare(const void * str1, const void * str2);

//Compares strings in reverse order
int ReverseCompare(const void * str1, const void * str2);

//Cleans dynamic memory
void CleanMem(char * mainbuffer, char ** pointsbuffer);////////////

//----------------------------------------------------------------

int Printing(struct StructBuff structbuff)
{
	
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

int ReverseCompare(const void * str1, const void * str2)
{
	///Warning!!!
	struct Sentence * struct1 = (struct Sentence *)str1;
	struct Sentence * struct2 = (struct Sentence *)str2;
	int i = 0, j = 0;
	if(strcmp(struct1->begin, struct2->begin) == 0)
		return 0;
	while(struct1->end[0 - i] != '\0')
	{
		if(isalpha(struct1->end[0 - i]) == 0)
			i++;
		if(isalpha(struct2->end[0 - j]) == 0)
			j++;

		if(struct2->end[0 - j] == '\0')
			return 1;
		else if(struct1->end[0 - i] < struct2->end[0 - j])
			return -1;
		else if(struct1->end[0 - i] > struct2->end[0 - j])
			return 1;
		i++;
		j++;
	}
}

int main(int argc, char * argv[])
{
	struct StructBuff structbuff = Prepare(argv[1]);
	int i = 0;
/*	for(i = 0; i < structbuff.strings; i++)
	{
		//printf("%p\n", structbuff.structpoint[i].begin);
		//printf("%p\n", structbuff.structpoint[i].end);
		printf("%s\n", structbuff.structpoint[i].begin);
		//printf("%s\n", structbuff.structpoint[i].end);
		printf("\n");
	}
*/
	//qsort(structbuff.structpoint, structbuff.strings, sizeof(struct Sentence), Compare);
	qsort(structbuff.structpoint, structbuff.strings, sizeof(struct Sentence), ReverseCompare);

	printf("--------------------------------------------------\n");

	for(i = 0; i < structbuff.strings; i++)
	{
		structbuff.structpoint[i].size = (structbuff.structpoint[i].end - structbuff.structpoint[i].begin);
	}

	for(i = 0; i < structbuff.strings; i++)
	{
		//printf("poiner to beggining = %p\n", structbuff.structpoint[i].begin);
		//printf("pointer to end = %p\n", structbuff.structpoint[i].end);
		//printf("%s\n", structbuff.structpoint[i].begin + structbuff.structpoint[i].size);
		printf("%s\n", structbuff.structpoint[i].begin);
		//printf("%s\n", structbuff.structpoint[i].end);
		//printf("size = %ld\n", structbuff.structpoint[i].size);
		printf("\n");
	}

	//Printing(pointsbuffer, strings);

	//CleanMem(mainbuff, pointsbuffer);
	return 0;
}








