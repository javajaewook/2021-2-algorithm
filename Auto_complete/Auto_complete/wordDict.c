#include "dictionary.h"

#define INCREMENT_SIZE 5

// wordDict���� ���� �ܾ� Ž�� �� connect_count ����
void searchWD(wordDict* wd, char* value)
{
    if (wd->count != 0 && wd->count % wd->size == 0) {
        wd->size += INCREMENT_SIZE;
        wd->voc = (Vocab*)realloc(wd->voc, sizeof(Vocab) * wd->size);
    }

    // ���� �ܾ� ����� Ž��
    for (int i = 0; i < wd->count; i++) {
        // ���� �ܾ wordDict�� �����ϴ� ���
        if (!(strcmp(wd->voc[i].string, value))) {
            wd->voc[i].connect++;    // connect_count ����
            return true;
        }
    }

	// ���� �ܾ wordDict�� ���� ��� �߰�
    wd->voc[wd->count].string = value;
    wd->voc[wd->count].connect = 1;
    wd->count++;

    return true;
}
