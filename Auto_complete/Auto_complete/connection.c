#include "dictionary.h"

// ���� ���ڿ��� dictionary index ��ȯ
int searchWL(wordList* wl, char* string)
{
	for (int idx = 0; idx < wl->count; idx++) {
		if (strcmp(wl->stringList[idx], string) == 0)
			return idx;
	}
	return -1;
}

// ������ ���ڿ��� ���� �Է��� ���ڿ��� connection count ��ȯ
int connectCount(Dictionary* dic, int dic_idx, char* string)
{
	for (int i = 0; i < dic->wdic[dic_idx].count; i++) {
		if (!(strcmp(dic->wdic[dic_idx].voc[i].string, string))) {
			return dic->wdic[dic_idx].voc[i].connect;
		}
		return -1;
	}
}

// ������ ���ڿ��� ���� �Է��� ���ڿ��� connection string ��ȯ
char* connectString(Dictionary* dic, int dic_idx, char* string)
{
	for (int i = 0; i < dic->wdic[dic_idx].count; i++) {
		if (!(strcmp(dic->wdic[dic_idx].voc[i].string, string))) {
			return dic->wdic[dic_idx].voc[i].string;
		}
	}
	return NULL;
}
