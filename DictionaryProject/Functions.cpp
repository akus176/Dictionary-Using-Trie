#include "Functions.h"
#include "Graphics.h"

int convertCharToIndex(char c) {
	return c - 'a';
}

char convertIndexToChar(int i) {
	return 'a' + i;
}

void insertWord(Trie& Dictionary, string word) {
	Node* current = Dictionary.root;

	for (char c : word) {
		int index = convertCharToIndex(c);

		if (current->childNode[index] == NULL) {
			current->childNode[index] = new Node();
		}

		current = current->childNode[index];
	}
	current->isEndOfWord = true;
	Dictionary.size++;
}

bool isLeafNode(Node*& node) {
	if (node == NULL) return false;

	for (int i = 0; i < SIZE_OF_ALPHABET; i++) {
		if (node->childNode[i] != NULL) return false;
	}

	return true;
}

void solveRemoveWord(Node*& root, string& word, int index) {
	if (root == NULL) return;

	if (index == word.size()) {
		if (!root->isEndOfWord) return;

		root->isEndOfWord = false;

		if (!isLeafNode(root)) return;

		delete root;
		root = NULL;

		return;
	}

	int i = convertCharToIndex(word[index]);

	solveRemoveWord(root->childNode[i], word, index + 1);

	if (!isLeafNode(root)) return;

	if (!root->isEndOfWord) {
		delete root;
		root = NULL;
	}
}

void removeWord(Trie& Dictionary, string& word) {
	if (word.empty()) return;

	solveRemoveWord(Dictionary.root, word, 0);
	Dictionary.size--;
}

void createTrieFromFile(Trie& dictionary, string fileName) {
	fstream input;
	input.open(fileName, ios::in);

	if (!input.is_open()) {
		cout << "Failed to open " << fileName << endl;
		return;
	}

	string word;

	while (getline(input, word)) {
		if (word.empty()) continue;
		insertWord(dictionary, word);
	}

	input.close();
}


bool isWordExist(Trie& Dictionary, string word) {
	Node* current = Dictionary.root;

	for (char c : word) {
		int index = convertCharToIndex(c);

		if (current->childNode[index] == NULL)
			return false;

		current = current->childNode[index];
	}

	return current->isEndOfWord;
}

void collectWordsFromNode(Trie& Dictionary, Node* node, string word, vector<string>& suggestedWord) {

	++Dictionary.numComparisons;
	if (node == NULL) return;

	++Dictionary.numComparisons;
	if (node->isEndOfWord) {
		suggestedWord.push_back(word);

		++Dictionary.numComparisons;
		if (suggestedWord.size() >= Dictionary.numSuggestedWords) {
			return;
		}
	}

	for (int i = 0; i < SIZE_OF_ALPHABET; i++) {
		++Dictionary.numComparisons;

		++Dictionary.numComparisons;
		if (node->childNode[i] != NULL) {
			char c = convertIndexToChar(i);

			collectWordsFromNode(Dictionary, node->childNode[i], word + c, suggestedWord);

			++Dictionary.numComparisons;
			if (suggestedWord.size() >= Dictionary.numSuggestedWords) return;
		}

	}
	++Dictionary.numComparisons;
}

vector<string> createSuggestedWordList(Trie& Dictionary, string& prefix) {
	Node* current = Dictionary.root;
	vector<string> suggestedWords;
	int index;

	for (char c : prefix) {
		++Dictionary.numComparisons;

		index = convertCharToIndex(c);

		++Dictionary.numComparisons;
		if (current->childNode[index] == NULL) return suggestedWords;

		current = current->childNode[index];
	}
	++Dictionary.numComparisons;

	collectWordsFromNode(Dictionary, current, prefix, suggestedWords);

	return suggestedWords;
}

void printWordsFromPrefix(Trie& Dictionary, string prefix, Display& display, bool f) {
	Dictionary.numComparisons = 0;

	vector<string> suggestedWords;
	string word = prefix;

	auto start = chrono::high_resolution_clock::now();
	suggestedWords = createSuggestedWordList(Dictionary,  prefix);
	auto end = chrono::high_resolution_clock::now();

	chrono::duration<double, std::milli> duration = end - start;

	Dictionary.suggestionTime = duration.count();

	drawTable(display);

	int idx = 0;

	for (int i = 0; i < display.rows; i++) {
		for (int j = 0; j < display.cols; j++) {
			gotoxy(display.start.x + j * WIDTH_CELL + 1, display.start.y + i * HEIGHT_CELL + 1);

			if(idx < suggestedWords.size()) 
				cout << suggestedWords[idx++];
 		}
	}
}

void generateSearchSuggestions(Trie& Dictionary, Display& display) {
	vector<string> suggestedWords;
	string input;
	char c;

	bool f = 0;

	system("cls");
	searchSuggestionUI(Dictionary, display);

	int startX = display.start.x + 13;
	int startY = display.start.y + 1;

	gotoxy(startX, startY);

	while (true) {

		f = 0;

		try {
			c = _getch();

			if (static_cast<unsigned char>(c) < 128) {
				if (isalpha(c) && input.size() <= MAX_WORD_LENGTH) {
					input.push_back(c);
				}
				else if (c == BACK) {
					system("cls");
					AnnouncementUI();
					break;
				}
				else if (c == BACKSPACE) {
					if (input.empty()) continue;
					input.pop_back();
				}
				else if (c == ENTER) {
					f = 1;
				}
			}
			else {
				gotoxy(startX - 6, startY + 3);
				setColor(BLACK, RED);
				cout << "The character you entered is invalid";
				resetColor();
				input.clear();
				gotoxy(startX- 6, startY + 4);
				system("PAUSE");
			}

			if (input.size() > MAX_WORD_LENGTH) {
				gotoxy(startX - 1, startY + 3);
				setColor(BLACK, RED);
				cout << "The word size is invalid";
				resetColor();
				gotoxy(startX, startY);
				cout << input;
				continue;
			}

			system("cls");
			searchSuggestionUI(Dictionary, display);

			if (!input.empty()) {
				printWordsFromPrefix(Dictionary, input, display, f);

				gotoxy(startX - 21, startY + 6);
				cout << Dictionary.suggestionTime << " ms";
				gotoxy(startX + 57, startY + 6);
				cout << Dictionary.numComparisons;
			}

			gotoxy(startX, startY);
			cout << input;
		}
		catch (const exception& e) {
			cout << "An error :" << e.what() << endl;
			break;
		}
	}
}

string findContent(Point current, const Point initial) {
	if (current.x == initial.x) {
		if (current.y == initial.y) {
			return "WORD SUGGESTIONS";
		}
		else {
			return "ABOUT";
		}
	}
	else if (current.x == initial.x + WIDTH + 15) {
		if (current.y == initial.y) {
			return "REMOVE WORD";
		}
		else {
			return "SETTINGS";
		}
	}
	else {
		if (current.y == initial.y) {
			return "INSERT WORD";
		}
		else {
			return "EXIT";
		}
	}
}

int findTextColor(Point current, const Point initial) {
	if (current.x == initial.x) {
		if (current.y == initial.y) {
			return BLUE;
		}
		else {
			return YELLOW;
		}
	}
	else if (current.x == initial.x + WIDTH + 15) {
		if (current.y == initial.y) {
			return GREEN;
		}
		else {
			return RED;
		}
	}
	else {
		if (current.y == initial.y) {
			return PINK;
		}
		else {
			return ORANGE;
		}
	}
}

void processMoveUp(Point& current, const Point initial) {
	if (current.y != initial.y) {

		string content = findContent(current, initial);
		int text_color = findTextColor(current, initial);
		drawBox(current, BLACK, text_color, content, WIDTH, HEIGHT);

		current.y = initial.y;
		content = findContent(current, initial);
		text_color = findTextColor(current, initial);
		drawBox(current, WHITE, text_color, content, WIDTH, HEIGHT);
	}
}

void processMoveDown(Point& current, const Point initial) {
	if (current.y == initial.y) {

		string content = findContent(current, initial);
		int text_color = findTextColor(current, initial);
		drawBox(current, BLACK, text_color, content, WIDTH, HEIGHT);

		current.y += 10;
		content = findContent(current, initial);
		text_color = findTextColor(current, initial);
		drawBox(current, WHITE, text_color, content, WIDTH, HEIGHT);
	}
}

void processMoveLeft(Point& current, const Point initial) {
	if (current.x != initial.x) {

		string content = findContent(current, initial);
		int text_color = findTextColor(current, initial);
		drawBox(current, BLACK, text_color, content, WIDTH, HEIGHT);

		current.x = current.x - WIDTH - 15;
		content = findContent(current, initial);
		text_color = findTextColor(current, initial);
		drawBox(current, WHITE, text_color, content, WIDTH, HEIGHT);
	}
}

void processMoveRight(Point& current, const Point initial) {
	if (current.x != initial.x + (WIDTH + 15) * 2) {

		string content = findContent(current, initial);
		int text_color = findTextColor(current, initial);
		drawBox(current, BLACK, text_color, content, WIDTH, HEIGHT);

		current.x = current.x + WIDTH + 15;
		text_color = findTextColor(current, initial);
		content = findContent(current, initial);
		drawBox(current, WHITE, text_color, content, WIDTH, HEIGHT);
	}
}

void processAbout() {
	AboutUI();
}

void processSettings(Trie& Dictionary, Display& display, char& choice) {
	int startX, startY;

	SettingsUI(Dictionary, startX, startY);

	if (choice == '1') {
		Dictionary.numSuggestedWords = 1;
		display.rows = 1;
		display.cols = 1;
	}
	else if (choice == '2') {
		Dictionary.numSuggestedWords = 5;
		display.rows = 1;
		display.cols = 5;
	}
	else if (choice == '3') {
		Dictionary.numSuggestedWords = 10;
		display.rows = 2;
		display.cols = 5;
	}
	else if (choice == '4') {
		Dictionary.numSuggestedWords = 15;
		display.rows = 3;
		display.cols = 5;
	}
	else if (choice == '5') {
		Dictionary.numSuggestedWords = 20;
		display.rows = 4;
		display.cols = 5;
	}

	gotoxy(startX, startY - 10);

	if (Dictionary.numSuggestedWords == 1)
		cout << "Number of suggested words that program will provide: " << Dictionary.numSuggestedWords << " word  ";
	else 
		cout << "Number of suggested words that program will provide: " << Dictionary.numSuggestedWords << " words ";
}

void processInsertWord(Trie& Dictionary, Display& display) {
	string word;
	int length;
	bool flag = true; // kiểm tra xem có sự thay đổi nào trên màn hình không

	while (true) {
		if (flag) {
			system("cls");
			InsertWordUI(display);
			gotoxy(display.start.x + 13, display.start.y + 1);
			cout << word;
			flag = false;
		}

		try {
			char c = _getch();

			if (static_cast<unsigned char>(c) < 128) {
				if (isalpha(c) && islower(c) && word.size() <= MAX_WORD_LENGTH) {
					word.push_back(c);
					flag = true;
				}
				else if (c == BACK) {
					system("cls");
					AnnouncementUI();
					break;
				}
				else if (c == BACKSPACE) {
					if (!word.empty()) {
						word.pop_back();
						flag = true; 
					}
				}
				else if (c == ENTER) {

					length = word.size();

					if (isWordExist(Dictionary, word)) {
						gotoxy(display.start.x + 5 - word.size() / 2, display.start.y + 6);
						setColor(BLACK, RED);
						cout << "The word \"" << word << "\" was existed in the dictionary";
						resetColor();
						gotoxy(display.start.x + 10, display.start.y + 8);
						system("PAUSE");
					}
					else if (length < MIN_WORD_LENGTH || length > MAX_WORD_LENGTH) {
						gotoxy(display.start.x + 13, display.start.y + 6);
						setColor(BLACK, RED);
						cout << "The word size is invalid";
						resetColor();
						gotoxy(display.start.x + 10, display.start.y + 8);
						system("PAUSE");
					}
					else {
						insertWord(Dictionary, word);
						gotoxy(display.start.x + 3 - word.size()/2, display.start.y + 6);
						setColor(BLACK, GREEN);
						cout << "The word \"" << word << "\" has been added to the dictionary";
						resetColor();
						gotoxy(display.start.x + 8, display.start.y + 8);
						system("PAUSE");
					}
					word.clear();
					flag = true;
				}
			}
			else {
				word.clear();
				gotoxy(display.start.x + 6, display.start.y + 6);
				setColor(BLACK, RED);
				cout << "The character you entered is invalid";
				resetColor();
				gotoxy(display.start.x + 8, display.start.y + 8);
				system("PAUSE");
				flag = true;
			}
		}
		catch (const exception& e) {
			cout << "An error :" << e.what() << endl;
			break;
		}
	}
}

void processRemoveWord(Trie& Dictionary, Display& display) {
	string word;
	int length;
	bool flag = true; // kiểm tra xem có sự thay đổi nào trên màn hình không

	while (true) {
		if (flag) {
			system("cls");
			RemoveWordUI(display);
			gotoxy(display.start.x + 13, display.start.y + 1);
			cout << word;
			flag = false;
		}

		try {
			char c = _getch();

			if (static_cast<unsigned char>(c) < 128) {
				if (isalpha(c) && islower(c) && word.size() <= MAX_WORD_LENGTH) {
					word.push_back(c);
					flag = true;
				}
				else if (c == BACK) {
					system("cls");
					AnnouncementUI();
					break;
				}
				else if (c == BACKSPACE) {
					if (!word.empty()) {
						word.pop_back();
						flag = true;
					}
				}
				else if (c == ENTER) {

					length = word.size();

					if (!isWordExist(Dictionary, word)) {
						gotoxy(display.start.x + 3 - word.size() / 2, display.start.y + 6);
						setColor(BLACK, RED);
						cout << "The word \"" << word << "\" wasn't existed in the dictionary";
						resetColor();
						gotoxy(display.start.x + 10, display.start.y + 8);
						system("PAUSE");
					}
					else if (length < MIN_WORD_LENGTH || length > MAX_WORD_LENGTH) {
						gotoxy(display.start.x + 13, display.start.y + 6);
						setColor(BLACK, RED);
						cout << "The word size is invalid";
						resetColor();
						gotoxy(display.start.x + 10, display.start.y + 8);
						system("PAUSE");
					}
					else {
						removeWord(Dictionary, word);
						gotoxy(display.start.x + 2 - word.size() / 2, display.start.y + 6);
						setColor(BLACK, GREEN);
						cout << "The word \"" << word << "\" has been removed to the dictionary";
						resetColor();
						gotoxy(display.start.x + 8, display.start.y + 8);
						system("PAUSE");
					}
					word.clear();
					flag = true;
				}
			}
			else {
				word.clear();
				gotoxy(display.start.x + 6, display.start.y + 6);
				setColor(BLACK, RED);
				cout << "The character you entered is invalid";
				resetColor();
				gotoxy(display.start.x + 8, display.start.y + 8);
				system("PAUSE");
				flag = true;
			}
		}
		catch (const exception& e) {
			cout << "An error :" << e.what() << endl;
			break;
		}
	}
}

void processExit(Trie& Dictionary) {
	system("cls");
	ExitUI();
	Sleep(2000);
	system("cls");
	Dictionary.~Trie();
	exit(0);
}

void processEnter(Point current, const Point initial, Trie& Dictionary, Display& display, int& flag, char& choice) {
	if (current.x == initial.x) {
		if (current.y == initial.y) {
			generateSearchSuggestions(Dictionary, display);
		}
		else {
			processAbout();
		}
	}
	else if (current.x == initial.x + WIDTH + 15) {
		if (current.y == initial.y) {
			processRemoveWord(Dictionary, display);
		}
		else {
			flag = 2;
			processSettings(Dictionary, display, choice);
		}
	}
	else {
		if (current.y == initial.y) {
			processInsertWord(Dictionary, display);
		}
		else {
			processExit(Dictionary);
		}
	}
}

void proccessStartMenu(Point& current, const Point initial, Trie& Dictionary, Display& display) {
	// Set flags to avoid conflicts between keys when executing functions
	int flag = 0;

	// flag = 0: ở màn hình bắt đầu
	// flag = 1: đã ấn vào phím Enter
	// flag = 2:  đã ấn vào phần Settings

	while (true) {
		char choice = _getch();

		switch (int(choice)) {
		case UP: {
			if (flag == 0) {
				processMoveUp(current, initial);
			}
			break;
		}
		case DOWN: {
			if (flag == 0) {
				processMoveDown(current, initial);
			}
			break;
		}
		case LEFT: {
			if (flag == 0) {
				processMoveLeft(current, initial);
			}
			break;
		}
		case RIGHT: {
			if (flag == 0) {
				processMoveRight(current, initial);
			}
			break;
		}
		case ENTER: {
			if (flag == 0) {
				flag = 1;
				processEnter(current, initial, Dictionary, display, flag, choice);
			}
			break;
		}
		case BACK: {
			if (flag != 0) {
				flag = 0;
				AppStartUI(initial);
				current = initial;
			}
			break;
		}
		case '1': {
			if (flag == 2) {
				processSettings(Dictionary,display, choice);
			}
			break;
		}
		case '2':
			if (flag == 2) {
				processSettings(Dictionary,display, choice);
			}
			break;
		case '3':
			if (flag == 2) {
				processSettings(Dictionary, display, choice);
			}
			break;
		case '4':
			if (flag == 2) {
				processSettings(Dictionary,display, choice);
			}
			break;
		case '5':
			if (flag == 2) {
				processSettings(Dictionary, display, choice);
			}
			break;
		default:
			break;
		}
	}
}