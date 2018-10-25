#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

/*! \brief Structure involving poiners to first and last symbols of a sentence */
struct String
{
	char * start;///< Pointer to a first symbol
	char * end;///< Pointer to a last symbol
};

/*! \brief Structure involving poiner to an array of stuctures and number of an array's members*/
struct Text
{
	long long amount;///< Number of members
	struct String * lines;///< Pointer to an array
};

//----------------------------------------------------------------

/*! \brief A function that makes all work

	Calculates a size, creates main buffer and buffer of pointers,
	counts number of symbols and changed '\n' to '\0', distributes pointers of sentenses*/
struct Text ConstructText(char * argv);

/*! Prints amount of an array*/
void Printing(struct Text structtext);

/*! Determines a size of a text*/
long long FSize(FILE * fpt);

/*! Changes all symbols of a new line in text to symbols '\0'*/
int RepChar(char * mainbuffer, long long size);

/*! Compares strings*/
int Compare(const void * str1, const void * str2);

/*! Compares amount in a reverse order*/
int ReverseCompare(const void * str1, const void * str2);

/*! Cleans dynamic memory*/
void DestructText(struct Text structtext);

//----------------------------------------------------------------

void Printing(struct Text structtext)
{
	int i = 0;
	for(i = 0; i < structtext.amount; i++)
	{
		printf("%s\n\n", structtext.lines[i].start);
	}
	printf("-------------------------------------------------\n\n");
}

void DestructText(struct Text structtext)
{
	free(structtext.lines);
}

long long FSize(FILE * ptrfile)
{
	if(ptrfile == NULL)
	{
		errno = EINVAL;
		perror("Error of file reading");
		return -1;
	}
	long long curroff = ftell(ptrfile);
	fseek(ptrfile, 0, SEEK_END);
	long long size = ftell(ptrfile);
	fseek(ptrfile, curroff, SEEK_SET);
	return size;
}

int RepChar(char * mainbuffer, long long size)
{
	if(mainbuffer == NULL) {
		errno = EINVAL;
		return -1;
	}

	int i = 0;
	int amount = 0;
	for(i = 0; i < size; i++)
	{
		if(mainbuffer[i] == '\n')
		{
			mainbuffer[i] = '\0';
			amount++;
		}
	}
	return amount;
}

struct Text ConstructText(char * argv)
{
	int i = 0, j = 0;
	long long amount = 0;	
	
	FILE * ptrfile = fopen(argv, "r");
	long long size = FSize(ptrfile);

	char * mainbuffer = (char *)calloc(size, sizeof(char));
	if(mainbuffer == NULL){
		perror("Error of memory allocation");
		return (struct Text){-1, NULL};
	}

	fread(mainbuffer, sizeof(char), size, ptrfile);	

	amount = RepChar(mainbuffer, size);

	
	struct String * structsentence = (struct String *)calloc(amount, sizeof(struct String));
	if(structsentence == NULL){
		perror("Error of memory allocation");
		return (struct Text){-1, NULL};
	}

	structsentence[0].start = mainbuffer;
	structsentence[amount - 1].end = mainbuffer + size - 1;
	for(i = 1, j = 1; i < size - 1; i++)
	{
		if(mainbuffer[i] == '\0')
		{
			structsentence[j].start = mainbuffer + i + 1;
			structsentence[j - 1].end = mainbuffer + i - 1;
			j++;			
		}
	}

	struct Text structtext = { 	.amount = amount, .lines = structsentence};

	return structtext;
}

int Compare(const void * str1, const void * str2)
{
	if(str1 == NULL || str2 == NULL)
	{
		errno = EINVAL;
		perror("Incorrect arguments");
		exit(EINVAL);
	}

	struct String * struct1 = (struct String *)str1;
	struct String * struct2 = (struct String *)str2;
	if(strcmp(struct1->start, struct2->start) == 0)
		return 0;

	int i = 0;
	int j = 0;
	while(struct1->start[i] != '\0')
	{
		if(isalpha(struct1->start[i]) == 0)
			i++;
		if(isalpha(struct2->start[j]) == 0)
			j++;

		if(struct2->start[j] == '\0')
			return 1;
		else if(struct1->start[i] < struct2->start[j])
			return -1;
		else if(struct1->start[i] > struct2->start[j])
			return 1;
		i++;
		j++;
	}
	return 0;
}

int ReverseCompare(const void * str1, const void * str2)
{
	if(str1 == NULL || str2 == NULL)
	{
		errno = EINVAL;
		perror("Incorrect arguments");
		exit(EINVAL);
	}

	struct String * struct1 = (struct String *)str1;
	struct String * struct2 = (struct String *)str2;
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
	return 0;
}

int main(int argc, char * argv[])
{
	struct Text structtext = ConstructText(argv[1]);
	if(structtext.amount == -1 || structtext.lines == NULL)
	{
		printf("Unfortunately something crashed:(\n");
		return errno;
	}
	qsort(structtext.lines, structtext.amount, sizeof(struct String), Compare);
	Printing(structtext);
	DestructText(structtext);
	return 0;
}

