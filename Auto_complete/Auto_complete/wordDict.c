#include "dictionary.h"

#define INCREMENT_SIZE 5

// wordDict에서 이전 단어 탐색 후 connect_count 갱신
void searchWD(wordDict* wd, char* value)
{
    if (wd->count != 0 && wd->count % wd->size == 0) {
        wd->size += INCREMENT_SIZE;
        wd->voc = (Vocab*)realloc(wd->voc, sizeof(Vocab) * wd->size);
    }

    // 이전 단어 목록을 탐색
    for (int i = 0; i < wd->count; i++) {
        // 현재 단어가 wordDict에 존재하는 경우
        if (!(strcmp(wd->voc[i].string, value))) {
            wd->voc[i].connect++;    // connect_count 갱신
            return true;
        }
    }

	// 현재 단어가 wordDict에 없는 경우 추가
    wd->voc[wd->count].string = value;
    wd->voc[wd->count].connect = 1;
    wd->count++;

    return true;
}
