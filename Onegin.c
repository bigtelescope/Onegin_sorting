#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct SentenceStruct
{
	char * begin;
	char * end;
	long int size;
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
int Printing(struct TextStruct TextStruct);

//Compares strings
int Compare(const void * str1, const void * str2);

//Compares strings in reverse order
int ReverseCompare(const void * str1, const void * str2);

//Cleans dynamic memory
void CleanMem(char * mainbuffer, char ** pointsbuffer);////////////

//----------------------------------------------------------------

int Printing(struct TextStruct TextStruct)
{
	
}

void CleanMem(char * mainbuffer, char ** pointsbuffer)
{
	free(mainbuffer);
	free(pointsbuffer);
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
	
	struct SentenceStruct * TextStructer = (struct SentenceStruct *)calloc(strings, sizeof(struct SentenceStruct));

	TextStructer[0].begin = mainbuffer;
	TextStructer[strings - 1].end = mainbuffer + size - 1;
	for(i = 1, j = 1; i < size - 1; i++)
	{
		if(mainbuffer[i] == '\0')
		{
			TextStructer[j].begin = mainbuffer + i + 1;
			TextStructer[j - 1].end = mainbuffer + i - 1;
			j++;			
		}
	}

	struct TextStruct TextStruct = {strings, TextStructer};

	return TextStruct;
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
	struct TextStruct TextStruct = Prepare(argv[1]);
	int i = 0;
	qsort(TextStruct.sentencepoint, TextStruct.strings, sizeof(struct SentenceStruct), Compare);
	qsort(TextStruct.sentencepoint, TextStruct.strings, sizeof(struct SentenceStruct), ReverseCompare);

	printf("--------------------------------------------------\n");

	for(i = 0; i < TextStruct.strings; i++)
	{
		TextStruct.sentencepoint[i].size = (TextStruct.sentencepoint[i].end - TextStruct.sentencepoint[i].begin);
	}

	for(i = 0; i < TextStruct.strings; i++)
	{
		//printf("poiner to beggining = %p\n", TextStruct.sentencepoint[i].begin);
		//printf("pointer to end = %p\n", TextStruct.sentencepoint[i].end);
		//printf("%s\n", TextStruct.sentencepoint[i].begin + TextStruct.sentencepoint[i].size);
		printf("%s\n", TextStruct.sentencepoint[i].begin);
		//printf("%s\n", TextStruct.sentencepoint[i].end);
		//printf("size = %ld\n", TextStruct.sentencepoint[i].size);
		printf("\n");
	}

	//Printing(pointsbuffer, strings);

	//CleanMem(mainbuff, pointsbuffer);
	return 0;
}








