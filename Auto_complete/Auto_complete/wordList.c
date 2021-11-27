#include "dictionary.h"

#define INCREMENT_SIZE 5

// wordList 생성
wordList* WLCreate()
{
	wordList* wl = (wordList*)malloc(sizeof(wordList));

	if (wl) {
		wl->stringList = (char**)malloc(sizeof(char*) * INCREMENT_SIZE);
		wl->size = INCREMENT_SIZE;
		wl->count = 0;
		return wl;
	}

	else
		free(wl);

	return NULL;
}

// wordList에 단어 추가
int WLAdd(wordList* wl, char* string)
{
	if (wl && wl->stringList) {
		if (wl->count > 0 && wl->count % INCREMENT_SIZE == 0) {
			wl->size += INCREMENT_SIZE;
			wl->stringList = (char*)realloc(wl->stringList, sizeof(char*) * wl->size);

			if (wl->stringList == NULL) {
				free(wl);
				return -1;
			}
		}

		// 이미 wordList에 존재하는 단어인지 중복 확인
		for (int idx = 0; idx < wl->count; idx++) {
			if (!strcmp(wl->stringList[idx], string))
				return idx;
		}

		// 현재 단어가 wordList에 없는 경우 추가
		wl->stringList[wl->count] = string;
		wl->count++;

		return wl->count - 1;
	}
	return -1;
}
