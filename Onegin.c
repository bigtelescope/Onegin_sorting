#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct SentenceStruct
{
	char * start;
	char * end;
};

struct TextStruct
{
	long long strings;
	struct SentenceStruct * sentencepoint;
};

//----------------------------------------------------------------

//Calculates a size, creates main buffer and buffer of pointers,\
 counts number of symbols and changed '\n' to '\0', distributes pointers of sentenses
struct TextStruct Prepare(char * argv);

//Prints strings of an array
void Printing(struct TextStruct structtext);

//Compares strings
int Compare(const void * str1, const void * str2);

//Compares strings in a reverse order
int ReverseCompare(const void * str1, const void * str2);

//Cleans dynamic memory
void CleanMem(struct TextStruct structtext);

//----------------------------------------------------------------

void Printing(struct TextStruct structtext)
{
	int i = 0;
	for(i = 0; i < structtext.strings; i++)
	{
		//printf("size = %ld\n", structtext.sentencepoint[i].end - structtext.sentencepoint[i].start);
		//printf("poiner to beggining = %p\n", structtext.sentencepoint[i].start);
		//printf("pointer to end = %p\n", structtext.sentencepoint[i].end);
		printf("%s\n\n", structtext.sentencepoint[i].start);
	}
	printf("-------------------------------------------------\n\n");
}

void CleanMem(struct TextStruct structtext)
{
	free(structtext.sentencepoint);
}

struct TextStruct Prepare(char * argv)
{
	int i = 0, j = 0;
	long long strings = 0;
	
	FILE * ptrfile = fopen(argv, "r");
	if(ptrfile == NULL)
		perror("Error of file reading: ");
	fseek(ptrfile, 0, SEEK_END);
	long long size = ftell(ptrfile);
	rewind(ptrfile);	
	
	char * mainbuffer = (char *)calloc(size, sizeof(char));
	if(mainbuffer == NULL)
		perror("Error of memory allocationn: ");

	fread(mainbuffer, sizeof(char), size, ptrfile);	
	
	for(i = 0; i < size; i++)
	{
		if(mainbuffer[i] == '\n')
		{
			mainbuffer[i] = '\0';
			strings++;
		}
	}
	
	struct SentenceStruct * structsentence = (struct SentenceStruct *)calloc(strings, sizeof(struct SentenceStruct));
	if(structsentence == NULL)
		perror("Error of memory allocationn: ");

	structsentence[0].start = mainbuffer;
	structsentence[strings - 1].end = mainbuffer + size - 1;
	for(i = 1, j = 1; i < size - 1; i++)
	{
		if(mainbuffer[i] == '\0')
		{
			structsentence[j].start = mainbuffer + i + 1;
			structsentence[j - 1].end = mainbuffer + i - 1;
			j++;			
		}
	}

	struct TextStruct structtext = {strings, structsentence};

	return structtext;
}

int Compare(const void * str1, const void * str2)
{
	if(str1 == NULL || str2 == NULL)
		perror("Error of strings comparing: ");
	struct SentenceStruct * struct1 = (struct SentenceStruct *)str1;
	struct SentenceStruct * struct2 = (struct SentenceStruct *)str2;
	return strcmp((struct1->start), (struct2->start));
}

int ReverseCompare(const void * str1, const void * str2)
{
	if(str1 == NULL || str2 == NULL)
		perror("Error of strings comparing: ");
	struct SentenceStruct * struct1 = (struct SentenceStruct *)str1;
	struct SentenceStruct * struct2 = (struct SentenceStruct *)str2;
	int i = 0, j = 0;
	if(strcmp(struct1->start, struct2->start) == 0)
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
	struct TextStruct structtext = Prepare(argv[1]);
	qsort(structtext.sentencepoint, structtext.strings, sizeof(struct SentenceStruct), ReverseCompare);
	Printing(structtext);
	CleanMem(structtext);
	return 0;
}



