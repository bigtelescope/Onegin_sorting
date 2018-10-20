#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct SentenceStruct
{
	char * begin;
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

//Prints arrays of symbols or pointers
void Printing(struct TextStruct structtext);

//Compares strings
int Compare(const void * str1, const void * str2);

//Compares strings in reverse order
int ReverseCompare(const void * str1, const void * str2);

//Cleans dynamic memory
void CleanMem(struct TextStruct structtext);

//----------------------------------------------------------------

void Printing(struct TextStruct structtext)
{
	int i = 0;
	for(i = 0; i < structtext.strings; i++)
	{
		//printf("size = %ld\n", structtext.sentencepoint[i].end - structtext.sentencepoint[i].begin);
		//printf("poiner to beggining = %p\n", structtext.sentencepoint[i].begin);
		//printf("pointer to end = %p\n", structtext.sentencepoint[i].end);
		printf("%s\n\n", structtext.sentencepoint[i].begin);
		printf("-------------------------------------------------\n\n");
	}
}

void CleanMem(struct TextStruct structtext)
{
	free(structtext.sentencepoint);
}

struct TextStruct Prepare(char * argv)
{
	struct SentenceStruct sentense;
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
	
	struct SentenceStruct * structtexter = (struct SentenceStruct *)calloc(strings, sizeof(struct SentenceStruct));

	structtexter[0].begin = mainbuffer;
	structtexter[strings - 1].end = mainbuffer + size - 1;
	for(i = 1, j = 1; i < size - 1; i++)
	{
		if(mainbuffer[i] == '\0')
		{
			structtexter[j].begin = mainbuffer + i + 1;
			structtexter[j - 1].end = mainbuffer + i - 1;
			j++;			
		}
	}

	struct TextStruct structtext = {strings, structtexter};

	return structtext;
}

int Compare(const void * str1, const void * str2)
{
	if(str1 == NULL || str2 == NULL)
	{
		fprintf(stderr, "Incorrect reading of an array element\n"
							"Emeregency shutdown\n");
		///errno
	}
	struct SentenceStruct * struct1 = (struct SentenceStruct *)str1;
	struct SentenceStruct * struct2 = (struct SentenceStruct *)str2;
	return strcmp((struct1->begin), (struct2->begin));
}

int ReverseCompare(const void * str1, const void * str2)
{
	///Warning!!!
	struct SentenceStruct * struct1 = (struct SentenceStruct *)str1;
	struct SentenceStruct * struct2 = (struct SentenceStruct *)str2;
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
	struct TextStruct structtext = Prepare(argv[1]);
	qsort(structtext.sentencepoint, structtext.strings, sizeof(struct SentenceStruct), ReverseCompare);
	Printing(structtext);
	CleanMem(structtext);
	return 0;
}



