#include "dictionary.h"

#define INCREMENT_SIZE 5

// wordList �ʱ�ȭ
void initWD(wordDict* wd)
{
    Vocab* pvoc = (Vocab*)malloc(sizeof(Vocab) * INCREMENT_SIZE);

    wd->voc = pvoc;
    wd->count = 0;
    wd->size = INCREMENT_SIZE;
}

// Dictionary ����
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

// Dictionary�� �ܾ� �߰�
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

	// �ܾ �̹� Dictionary�� �ִ� ���
    if (start != 0 && idx <= dic->count - 1) {
		// ���� �ܾ �����ϴ� ���
        if (pre_idx != -1) {
            searchWD(&(dic->wdic[pre_idx]), value);
        }
        return true;
    }

	// �ܾ Dictionary�� �������� �ʴ� ���
    else {
        dic->count++;    // Dictionary�� �ܾ� �߰�
		// ���� �ܾ �����ϴ� ���
        if (pre_idx != -1) {
            searchWD(&(dic->wdic[pre_idx]), value);
        }
    }

}
