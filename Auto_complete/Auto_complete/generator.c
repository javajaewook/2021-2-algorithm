#pragma once
#include "dictionary.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>

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

int nucleus_sampling(int* cnt, int* idx, int len, float p_value) { // select word with nucleus sampling
	float* smax;
	int i, random_val;
	float* cum_sum = (float*)malloc(sizeof(float) * len);
	for (i = 0; i < len; i++) {
		cum_sum[i] = 0; // initialize
	}
	smax = softmax(cnt, len); // get softmax value
	cum_sum[len - 1] = smax[len - 1];
	for (i = len - 1; i > 0; i--) {
		cum_sum[i - 1] = cum_sum[i] + smax[i - 1];
	}
	for (i = 0; i < len;) {
		i++;
		if (cum_sum[i] < p_value) break;
	}
	srand((unsigned int)time(NULL)); // for complete random

	free(smax);
	free(cum_sum);
	return idx[rand() % i];
}

void generate_sent(Dictionary* dic, wordList* wl, char* start_word, int max_length) {
	int i, iter;
	int cur_idx, target_idx; 
	int* word_cnt; 
	int* word_idx;
	char* temp_word;
	wordDict cur_WD;

	iter = 1;
	printf("\ngenerated sentence: %s ", start_word);
	temp_word = start_word;

	// 생성 시작
	while (iter <= max_length) {
		cur_idx = searchWL(wl, temp_word); // 단어의 인덱스 찾기
		cur_WD = dic->wdic[cur_idx]; // 현재 단어의 word dictionary

		word_cnt = (int*)malloc(sizeof(int) * cur_WD.count);
		word_idx = (int*)malloc(sizeof(int) * cur_WD.count);

		for (i = 0; i < cur_WD.count; i++) {
			word_cnt[i] = cur_WD.voc[i].connect;
			temp_word = cur_WD.voc[i].string;
			word_idx[i] = searchWL(wl, temp_word);
		}

		// 단어 등장 횟수의 내림차순으로 정렬
		quick_sort(word_idx, word_cnt, 0, cur_WD.count - 1);

		// 누적 확률이 p_value 이상인 단어 중 랜덤으로 선택
		cur_idx = nucleus_sampling(word_cnt, word_idx, cur_WD.count, 0.2);
		cur_WD = dic->wdic[cur_idx];

		temp_word = wl->stringList[cur_idx];

		// 선택된 단어가 eos 토큰이면 생성 종료
		if (strcmp("<eos>", temp_word) == 0) {
			// 생성 종료
			break;
		}
		else printf("%s ", temp_word);
	}
}

void generate_sent_greedy(Dictionary* dic, wordList* wl, char* start_word, int max_length) {
	int i, iter;
	int cur_idx, target_idx;
	int* word_cnt;
	int* word_idx;
	char* temp_word;
	wordDict cur_WD;

	iter = 1;
	printf("\ngenerated sentence: %s ", start_word);
	temp_word = start_word;

	// 생성 시작
	while (iter <= max_length) {
		cur_idx = searchWL(wl, temp_word); // 단어의 인덱스 찾기
		cur_WD = dic->wdic[cur_idx]; // 현재 단어의 word dictionary

		word_cnt = (int*)malloc(sizeof(int) * cur_WD.count);
		word_idx = (int*)malloc(sizeof(int) * cur_WD.count);

		for (i = 0; i < cur_WD.count; i++) {
			word_cnt[i] = cur_WD.voc[i].connect;
			temp_word = cur_WD.voc[i].string;
			word_idx[i] = searchWL(wl, temp_word);
		}

		// 단어 등장 횟수의 내림차순으로 정렬
		quick_sort(word_idx, word_cnt, 0, cur_WD.count - 1);

		// 누적 확률이 p_value 이상인 단어 중 랜덤으로 선택
		cur_idx = word_idx[0];
		cur_WD = dic->wdic[cur_idx];

		temp_word = wl->stringList[cur_idx];

		// 선택된 단어가 eos 토큰이면 생성 종료
		if (strcmp("<eos>", temp_word) == 0) {
			// 생성 종료
			break;
		}
		else printf("%s ", temp_word);
	}
}