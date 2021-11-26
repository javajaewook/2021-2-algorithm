#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
	int connect;
	char* string;
} Vocab;

typedef struct {
	Vocab* voc;
	int size;
	int count;
} wordDict;

typedef struct {
	wordDict* wdic;
	int size;
	int count;
} Dictionary;

typedef struct {
	char** stringList;
	int size;
	int count;
} wordList;
