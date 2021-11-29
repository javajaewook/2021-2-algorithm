#define _CRT_SECURE_NO_WARNINGS

#include "dictionary.h"

extern void generate_sent(Dictionary* dic, wordList* wl, char* start_word, int max_length);

/*
Dictionary : word dictionary를 담은 동적 구조체 배열
wordDict : 연결된 Vocab들을 담은 동적 구조체 배열
wordList : 입력된 단어들의 목록
*/

// wordList에 단어 입력
int InputToWL(wordList* wl, char* string)
{
    int idx = 0;

    idx = WLAdd(wl, string);

    if (idx == -1) {
        printf("WordList 입력 실패\n");
        return idx;
    }
    return idx;    // 입력된 단어에 할당한 index 반환
}

int main(void)
{
	int txtSize;
	int count;
	char inputTXT[100];
	// char txtBuffer[100];

	FILE* fp = fopen("sentence.txt", "r");

	Dictionary* dic = DicCreate();
	wordList* wl = WLCreate();

	int start = 0;    // 첫 Dictionary 요소 구분
	bool firstWord = false;    // 문장 첫 요소 구분
	char* string;
	int pre_idx = -1;    // 이전 단어 index
	int idx = 0;    // 입력한 단어의 index

	if (dic == NULL)
		return 0;

	do {
		// 단어 최대 길이 99
		string = (char*)malloc(sizeof(char) * 100);

		fscanf(fp, "%s", string);
		// scanf("%s", string);

		// "_exit" 입력 시 입력 종료
		if (!strcmp(string, "_exit"))
			break;

		idx = InputToWL(wl, string);    // 입력한 단어를 wordList에 추가
		DicAdd(dic, string, idx, pre_idx, start);    // 입력한 단어에 대해 Dictionary 추가 및 connect_count 갱신

		if (idx == -1)
			return 0;

		// 이전 단어 index 갱신
		pre_idx = idx;

		if (!strcmp(string, "<eos>"))
			pre_idx = -1;

		start += 1;
	} while (true);

	fclose(fp);

	printf("\n\n===입력 종료===\n\n\n");
	printf("=======================================================================\n\n");

	printf("WordList\n\n");
	for (int idx = 0; idx < wl->count; idx++) {
		printf("[%d] : %s\n", idx, wl->stringList[idx]);
	}

	printf("\n\n==================================================================\n\n");

	printf("Dictionary\n\n");
	for (int i = 0; i < dic->count; i++) {
		printf("[%d] : %s - ", i, wl->stringList[i]);;

		if (dic->wdic[i].count == 0)
			printf("\n");

		for (int j = 0; j < dic->wdic[i].count; j++) {
			if (j == 0) {
				if (j == dic->wdic[i].count - 1)
					printf("(%s, %d)\n", dic->wdic[i].voc[j].string, dic->wdic[i].voc[j].connect);
				else
					printf("(%s, %d / ", dic->wdic[i].voc[j].string, dic->wdic[i].voc[j].connect);
			}

			else if (j == dic->wdic[i].count - 1)
				printf("%s, %d)\n", dic->wdic[i].voc[j].string, dic->wdic[i].voc[j].connect);

			else
				printf("%s, %d / ", dic->wdic[i].voc[j].string, dic->wdic[i].voc[j].connect);
		}
	}
	generate_sent(dic, wl, "하나", 10);
    return 0;
}