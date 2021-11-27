#define _CRT_SECURE_NO_WARNINGS

#include "dictionary.h"

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
    Dictionary* dic = DicCreate();
    wordList* wl = WLCreate();

    int start = 0;    // 첫 Dictionary 요소 구분
    char* string;
    int pre_idx = -1;    // 이전 단어 index
    int idx = 0;    // 입력한 단어의 index

    if (dic == NULL)
        return 0;

    do {
        // 단어 최대 길이 99
        string = (char*)malloc(sizeof(char) * 100);
        scanf("%s", string);

        // "_exit" 입력 시 입력 종료
        if (!strcmp(string, "_exit"))
            break;

        idx = InputToWL(wl, string);    // 입력한 단어를 wordList에 추가
        DicAdd(dic, string, idx, pre_idx, start);    // 입력한 단어에 대해 Dictionary 추가 및 connect_count 갱신

        if (idx == -1)
            return 0;

        // 이전 단어 index 갱신
        pre_idx = idx;
        
        start += 1;
    } while (true);

    printf("입력 종료\n\n\n\n");

    printf("WordList\n\n");
    for (int idx = 0; idx < wl->count; idx++) {
        printf("%s\n", wl->stringList[idx]);
    }

    printf("\n\n\n\n");

    printf("Dictionary\n\n");
    for (int i = 0; i < dic->count; i++) {
        printf("Dic word : %s\n", wl->stringList[i]);
        for (int j = 0; j < dic->wdic[i].count; j++) {
            printf("connect_string : %s\n", dic->wdic[i].voc[j].string);
            printf("connect_count : %d\n", dic->wdic[i].voc[j].connect);
            printf("\n\n");
        }
    }

    return 1;
}
