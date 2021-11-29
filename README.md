 # 2021-2-algorithm
2021학년도 2학기 알고리즘 팀프로젝트

Dictionary : word dictionary를 담은 동적 구조체 배열
wordDict : 연결된 Vocab들을 담은 동적 구조체 배열
Vocab : 특정 단어의 뒤에 등장한 단어와 등장 횟수를 담은 구조체
wordList : 입력된 단어들의 목록

Dictionary의 특정 단어에 접근하는 법
1. wordList에서 특정 단어의 idx를 탐색한다.
2. dic->wdic[idx]로 접근한다.

Dictionary의 특정 단어의 Vocab에 접근하는 법
1. wordList에서 특정 단어의 idx를 탐색한다.
2. dic->wdic[idx].voc로 접근한다.

Dictionary의 특정 단어의 뒤에 등장하는 특정 단어와 등장 횟수에 접근하는 법
1. wordList에서 특정 단어의 idx를 탐색한다.
2. dic->wdic[idx].voc를 탐색해서 뒤에 등장하는 특정 단어의 vidx를 얻는다.
  (i에 대한 반복문을 통해 dic->wdic[idx].voc[i]를 순회하면서 strcmp(특정단어, dic->wdic[idx].voc[i])의 결과를 통해 i를 반환하면 된다)
4-1. dic->wdic[idx].voc[vidx].string : 등장 단어
4-2. dic->wdic[idx].voc[vidx].connect : 등장 횟수
