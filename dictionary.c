#include "dictionary.h"

#define INCREMENT_SIZE 5

// wordList 초기화
void initWD(wordDict* wd)
{
    Vocab* pvoc = (Vocab*)malloc(sizeof(Vocab) * INCREMENT_SIZE);

    wd->voc = pvoc;
    wd->count = 0;
    wd->size = INCREMENT_SIZE;
}

// Dictionary 생성
Dictionary* DicCreate()
{
    Dictionary* dic = (Dictionary*)malloc(sizeof(Dictionary));
    wordDict* wd = (wordDict*)malloc(sizeof(wordDict) * INCREMENT_SIZE);

    if (dic == NULL || dic->wdic == NULL)
        return NULL;

    dic->wdic = wd;
    dic->count = 0;
    dic->size = INCREMENT_SIZE;

    for (int i = 0; i < 5; i++)
        initWD(&(dic->wdic[i]));

    return dic;
}

// Dictionary에 단어 추가
bool DicAdd(Dictionary* dic, char* value, int idx, int pre_idx, int start)
{
    if (dic == NULL)
        return false;

    if (dic->count != 0 && dic->count % dic->size == 0) {
        dic->size += INCREMENT_SIZE;
        dic->wdic = (wordDict*)realloc(dic->wdic, sizeof(wordDict) * dic->size);

        for (int i = dic->count; i < dic->size; i++)
            initWD(&(dic->wdic[i]));
    }

    if (dic->wdic == NULL)
        return false;

    // 단어가 이미 Dictionary에 있는 경우
    if (start != 0 && idx <= dic->count - 1) {
        // 이전 단어가 존재하는 경우
        if (pre_idx != -1) {
            searchWD(&(dic->wdic[pre_idx]), value);
        }
        return true;
    }

    // 단어가 Dictionary에 존재하지 않는 경우
    else {
        dic->count++;    // Dictionary에 단어 추가
        // 이전 단어가 존재하는 경우
        if (pre_idx != -1) {
            searchWD(&(dic->wdic[pre_idx]), value);
        }
    }

}
