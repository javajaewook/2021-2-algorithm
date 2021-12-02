#include "dictionary.h"

// 현재 문자열의 dictionary index 반환
int searchWL(wordList* wl, char* string)
{
	for (int idx = 0; idx < wl->count; idx++) {
		if (strcmp(wl->stringList[idx], string) == 0)
			return idx;
	}
	return -1;
}

// 지정한 문자열에 대한 입력한 문자열의 connection count 반환
int connectCount(Dictionary* dic, int dic_idx, char* string)
{
	for (int i = 0; i < dic->wdic[dic_idx].count; i++) {
		if (!(strcmp(dic->wdic[dic_idx].voc[i].string, string))) {
			return dic->wdic[dic_idx].voc[i].connect;
		}
		return -1;
	}
}

// 지정한 문자열에 대한 입력한 문자열의 connection string 반환
char* connectString(Dictionary* dic, int dic_idx, char* string)
{
	for (int i = 0; i < dic->wdic[dic_idx].count; i++) {
		if (!(strcmp(dic->wdic[dic_idx].voc[i].string, string))) {
			return dic->wdic[dic_idx].voc[i].string;
		}
	}
	return NULL;
}
