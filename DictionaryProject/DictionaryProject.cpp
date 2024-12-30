#include "Functions.h"
#include "Graphics.h"

int main() {
	Trie Dictionary;

	createTrieFromFile(Dictionary, "words_alpha.txt");

	// Khởi tạo điểm mốc để vẽ giao diện 
	const Point initial = { 16,15 };

	// Khởi tạo điểm để lưu vị trí hiện tại của con trỏ màn hình khi vẽ giao diện
	Point current = { initial.x, initial.y };

	AppStartUI(initial);

	Display display;
	proccessStartMenu(current, initial, Dictionary, display);

	return 0;
}
