#pragma once
#include "dictionary.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

void quick_sort(int* idx, int* cnt, int start, int end) {
	int pivot = start;
	int i = pivot + 1;
	int j = end;
	int temp_cnt;
	int temp_idx;

	if (start >= end) return;

	while (i <= j) {
		while (i <= end && cnt[i] >= cnt[pivot]) {
			i++;
		}
		while (j > start && cnt[j] <= cnt[pivot]) {
			j--;
		}

		if (i > j) {
			temp_cnt = cnt[j];
			cnt[j] = cnt[pivot];
			cnt[pivot] = temp_cnt;
			temp_idx = idx[j];
			idx[j] = idx[pivot];
			idx[pivot] = temp_idx;
		}
		else {
			temp_cnt = cnt[i];
			cnt[i] = cnt[j];
			cnt[j] = temp_cnt;
			temp_idx = idx[i];
			idx[i] = idx[j];
			idx[j] = temp_idx;
		}
	}

	// 분할 계산
	quick_sort(idx, cnt, start, j - 1);
	quick_sort(idx, cnt, j + 1, end);
}

float* softmax(int* input, int len) { // softmax 계산
	int i;
	float m, sum;
	float* smax = (float*)malloc(sizeof(float) * len);
	m = input[0];
	for (i = 1; i < len; i++) {
		if (input[i] > m) {
			m = input[i];
		}
	}

	sum = 0;
	for (i = 0; i < len; i++) {
		sum += expf(input[i] - m);
	}

	for (i = 0; i < len; i++) {
		smax[i] = expf(input[i] - m - log(sum));
	}

	return smax;
}

int* temparature(int* cnt, int len) {
	int sum = 0;
	int i;
	int* cum_sum = (int*)malloc(sizeof(int) * len);

	for (i = 0; i <= len; i++) {
		sum += cnt[i];
	}
}

void generate_sent(Dictionary* dic, wordList* wl, char* start_word, int max_length) {
	int i;
	int cur_idx; 
	int* word_cnt; int* word_idx;
	char* temp_word;
	wordDict cur_WD;

	cur_idx = searchWL(wl, start_word); // 단어의 인덱스 찾기
	cur_WD = dic->wdic[cur_idx]; // 현재 단어의 word dictionary
	
	word_cnt = (int*)malloc(sizeof(int) * cur_WD.count);
	word_idx = (int*)malloc(sizeof(int) * cur_WD.count);

	for (i = 0; i < cur_WD.count; i++) {
		word_cnt[i] = cur_WD.voc[i].connect;
		temp_word = cur_WD.voc[i].string;
		word_idx[i] = searchWL(wl, temp_word);
	}

	quick_sort(word_idx, word_cnt, 0, cur_WD.count - 1);

}