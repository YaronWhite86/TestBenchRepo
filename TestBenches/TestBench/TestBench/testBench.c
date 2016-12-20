#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <crtdbg.h>
#include "list.h"

#define MAX_LINE_SIZE (256)

// A function to check the action type of our input 
Result Command(char* input) {
	if (((strcmp(input, "Create") == 0) || (strcmp(input, "Destroy") == 0) || (strcmp(input, "Add") == 0) ||
		(strcmp(input, "First") == 0) || (strcmp(input, "Next") == 0) ||
		(strcmp(input, "Remove") == 0) || (strcmp(input, "GetSize") == 0)) == 0) return FAIL;
	else return SUCCESS;
}
// A function to count the number of input arguments
int Number_of_Inputs(char input[])
{
	
	int count = 0, i, len;
	char lastC;
	len = strlen(input);
	
	if (len > 0)
	{
		lastC = input[0];
	}
	for (i = 0; i <= len; i++)
	{
		if ((input[i] == ' ' || input[i] == '\0') && lastC != ' ')
		{
			count++;
		}
		lastC = input[i];
	}
	
	return count;
}
int testFunction(int input)
{
	return input;
}

int main(char argc, char* argv[]) {
	char szLine[MAX_LINE_SIZE];
	char* delimiters = " \t\n";
	char* command;
	char* arg1;
	int inputCount;
	int address = 1000;
	//char* arg2;
	//char* arg3;
	PList TheList;
	FILE *fp;

	if (argc < 1)
	{
		printf("Usage: %s <stack size> <file name>\n", argv[0]);
		exit(1);
	}

	fp = fopen(argv[1], "r");
	if (fp == NULL)
	{
		printf("Error: Can't open %s\n", argv[1]);
		exit(1);
	}

	while (fgets(szLine, MAX_LINE_SIZE, fp)) {

		inputCount = Number_of_Inputs(szLine);
		if (inputCount < 1)
		{
			fprintf(stderr, "Failed: not enough parameters.\n");
			continue;
		}

		command = strtok(szLine, delimiters);
		if (command == NULL)
		{
			continue;
		}
		if (Command(command) == FAIL)
		{
			fprintf(stderr, "Command not found.\n");
			continue;
		}
		arg1 = strtok(NULL, delimiters);
		if (strcmp(command, "Create") == 0)
		{
			TheList = ListCreate(testFunction, testFunction);
			if (TheList == NULL)
			{
				fprintf(stderr, "Create execution Failed.\n");
				continue;
			}
			else continue;
			
		}
		if (strcmp(command, "Add") == 0)
		{
			int j = ListAdd(TheList, address++);
			if (j == FAIL)
			{
				fprintf(stderr, "Add execution Failed.\n");
				continue;
			}
			else continue;
		}
		if (strcmp(command, "Destroy") == 0)
		{
			ListDestroy(TheList);
			break;
		}
		if (strcmp(command, "First") == 0)
		{
			PElem j = ListGetFirst(TheList);
			if (j == NULL)
			{
				fprintf(stderr, "First execution Failed.\n");
				continue;
			}
			else continue;
		}
		if (strcmp(command, "Next") == 0)
		{
			PElem j = ListGetNext(TheList);
			if (j == NULL)
			{
				fprintf(stderr, "Next execution Failed.\n");
				continue;
			}
			else continue;
		}
		if (strcmp(command, "Remove") == 0)
		{
			Result j = ListRemove(TheList);
			if (j == FAIL)
			{
				fprintf(stderr, "Remove execution Failed.\n");
				continue;
			}
			else continue;
		}
		if (strcmp(command, "GetSize") == 0)
		{
			int j = ListGetSize(TheList);
			if (j == FAIL)
			{
				fprintf(stderr, "Get execution Failed.\n");
				continue;
			}
			else continue;
		}
	}
	free(TheList);
}