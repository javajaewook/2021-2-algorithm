#define _CRT_SECURE_NO_WARNINGS

#include "dictionary.h"

extern void generate_sent(Dictionary* dic, wordList* wl, char* start_word, int max_length);

/*
Dictionary : word dictionary�� ���� ���� ����ü �迭
wordDict : ����� Vocab���� ���� ���� ����ü �迭
wordList : �Էµ� �ܾ���� ���
*/

// wordList�� �ܾ� �Է�
int InputToWL(wordList* wl, char* string)
{
    int idx = 0;

    idx = WLAdd(wl, string);

    if (idx == -1) {
        printf("WordList �Է� ����\n");
        return idx;
    }
    return idx;    // �Էµ� �ܾ �Ҵ��� index ��ȯ
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

	int start = 0;    // ù Dictionary ��� ����
	bool firstWord = false;    // ���� ù ��� ����
	char* string;
	int pre_idx = -1;    // ���� �ܾ� index
	int idx = 0;    // �Է��� �ܾ��� index

	if (dic == NULL)
		return 0;

	do {
		// �ܾ� �ִ� ���� 99
		string = (char*)malloc(sizeof(char) * 100);

		fscanf(fp, "%s", string);
		// scanf("%s", string);

		// "_exit" �Է� �� �Է� ����
		if (!strcmp(string, "_exit"))
			break;

		idx = InputToWL(wl, string);    // �Է��� �ܾ wordList�� �߰�
		DicAdd(dic, string, idx, pre_idx, start);    // �Է��� �ܾ ���� Dictionary �߰� �� connect_count ����

		if (idx == -1)
			return 0;

		// ���� �ܾ� index ����
		pre_idx = idx;

		if (!strcmp(string, "<eos>"))
			pre_idx = -1;

		start += 1;
	} while (true);

	fclose(fp);

	printf("\n\n===�Է� ����===\n\n\n");
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
	generate_sent(dic, wl, "�ϳ�", 10);
    return 0;
}