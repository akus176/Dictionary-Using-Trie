#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <chrono> // for chrono
#include <conio.h> // for _getch()
#include <Windows.h> // for Sleep()
#include <fstream>

using namespace std;

#define SIZE_OF_ALPHABET 26
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define BACKSPACE 8
#define ENTER 13
#define BACK 27
#define EXIT 48
#define YES 48
#define NO 49
#define TAB 9
#define WIDTH 20
#define HEIGHT 4
#define BLACK 232
#define BLUE 4
#define GREEN 2
#define YELLOW 3
#define RED 1
#define PURPLE 5
#define SKYBLUE 6 
#define WHITE 7
#define GREY 8
#define PINK 9
#define BRIGHT_GREEN 10
#define IVORY 11
#define AQUA 14
#define BRIGHT_BLUE 63
#define ORANGE 202
#define WIDTH_CELL 20
#define HEIGHT_CELL 2
#define MAX_WORD_LENGTH 20
#define MIN_WORD_LENGTH 1

struct Node {
	Node* childNode[SIZE_OF_ALPHABET];
	bool isEndOfWord;

	Node() {
		for (int i = 0; i < SIZE_OF_ALPHABET; i++) {
			childNode[i] = NULL;
		}

		isEndOfWord = false;
	}
};

struct Trie {
	Node* root;
	int size;
	int numSuggestedWords;
	int numComparisons;
	double suggestionTime;

	Trie() {
		root = new Node();
		size = 0;
		numSuggestedWords = 10;
		numComparisons = 0;
		suggestionTime = 0;
	}

	~Trie() {
		freeTrie(root);
	}

	void freeTrie(Node* root) {
		if (root == NULL) return;

		for (int i = 0; i < SIZE_OF_ALPHABET; i++) {
			freeTrie(root->childNode[i]);
		}

		delete root;
	}
};

struct Point {
	int x;
	int y;
};

struct Display {
	int size_height, size_width; // kích thước màn hình console
	int rows, cols; // số dòng và số cột của bảng (nếu có)
	Point start; // lưu giữ tọa độ bắt đầu để vẽ hay in một đối tượng nào đó

	Display() {
		size_height = 0;
		size_width = 0;

		rows = 2;
		cols = 5;

		start = { 0,0 };
	}
};
