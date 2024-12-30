#include "Functions.h";
#include "Graphics.h";

using namespace std;

void setColor(int background_color, int text_color) {
    cout << "\033[48;5;" << background_color << "m";
    cout << "\033[38;5;" << text_color << "m";
}

void resetColor() {
    cout << "\033[0m";
}

void gotoxy(int x, int y) {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
	SetConsoleCursorPosition(h, c);
}

void showCursorOnScr(bool boolean) {
    CONSOLE_CURSOR_INFO Info;
    if (!boolean) 
        Info.bVisible = FALSE;
    else 
        Info.bVisible = TRUE;

    Info.dwSize = 20;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}

void getConsoleSize(int& width, int& height) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

void drawBox(Point point, int b_color, int t_color, string content, int width, int height) {
    setColor(b_color, t_color);

    // Draw color for the box
    for (int i = point.y + 1; i < point.y + height; i++) {
        for (int j = point.x + 1; j < point.x + width; j++) {
            gotoxy(j, i);
            cout << " ";
        }
    }

    // Find coordinates so that the content is centered inside the box
    int startX = point.x + ((width - content.size()) / 2);

    if (content.size() % 2 == 1) {
        startX += 1;
    }

    int srartY = point.y + height / 2;

    // Print content
    gotoxy(startX, srartY);
    cout << content;

    for (int ix = point.x; ix <= point.x + width; ix++) {

        // Draw the top line of the box
        gotoxy(ix, point.y);
        cout << char(205);

        // Draw the bottom line of the box
        gotoxy(ix, point.y + height);
        cout << char(205);
    }

    for (int iy = point.y; iy <= point.y + height; iy++) {

        // Draw the right line of the box
        gotoxy(point.x, iy);
        cout << char(186);

        // Draw the left line of the box
        gotoxy(point.x + width, iy);
        cout << char(186);
    }

    // Draw the square corners for the box

    gotoxy(point.x, point.y);
    cout << char(201);

    gotoxy(point.x + width, point.y);
    cout << char(187);

    gotoxy(point.x, point.y + height);
    cout << char(200);

    gotoxy(point.x + width, point.y + height);
    cout << char(188);

    resetColor();
}

void drawLogo() {
    gotoxy(6, 1);
    cout << "  __       __   ______   _______   _______   ______  ________  __      __          ______   _______   _______  ";
    gotoxy(6, 2);
    cout << " /  |  _  /  | /      \\ /       \\ /       \\ /      |/        |/  \\    /  |        /      \\ /       \\ /       \\ ";
    gotoxy(6, 3);
    cout << " WW | / \\ WW |/OOOOOO  |RRRRRRR  |DDDDDDD  |IIIIII/ FFFFFFFF/ YY  \\  /YY/        /AAAAAA  |PPPPPPP  |PPPPPPP  |";
    gotoxy(6, 4);
    cout << " WW |/W  \\WW |OO |  OO |RR |__RR |DD |  DD |  II |  FF |__     YY  \\/YY/        AA |__AA |PP |__PP |PP |__PP |";
    gotoxy(6, 5);
    cout << " WW /WWW  WW |OO |  OO |RR    RR< DD |  DD |  II |  FF    |     YY  YY/         AA    AA |PP    PP/ PP    PP/ ";
    gotoxy(6, 6);
    cout << " WW WW/WW WW |OO |  OO |RRRRRRR  |DD |  DD |  II |  FFFFF/       YYYY/          AAAAAAAA |PPPPPPP/  PPPPPPP/  ";
    gotoxy(6, 7);
    cout << " WWWW/  WWWW |OO \\__OO |RR |  RR |DD |__DD | _II |_ FF |          YY |          AA |  AA |PP |      PP |      ";
    gotoxy(6, 8);
    cout << " WWW/    WWW |OO    OO/ RR |  RR |DD    DD/ / II   |FF |          YY |          AA |  AA |PP |      PP |      ";
    gotoxy(6, 9);
    cout << " WW/      WW/  OOOOOO/  RR/   RR/ DDDDDDD/  IIIIII/ FF/           YY/           AA/   AA/ PP/       PP/       ";
}

void AppStartUI(const Point initial) {
    showCursorOnScr(false); // Ản vị trí con trỏ trên màn hình consolve
    system("cls");
    drawLogo();

    // The first box will be highlighted when drawn
    drawBox(initial, WHITE, BLUE, "WORD SUGGESTIONS", WIDTH, HEIGHT);
    drawBox({ initial.x + WIDTH + 15, initial.y }, BLACK, GREEN, "REMOVE WORD", WIDTH, HEIGHT);
    drawBox({ initial.x + (WIDTH + 15) * 2, initial.y }, BLACK, PINK, "INSERT WORD", WIDTH, HEIGHT);
    drawBox({ initial.x, initial.y + 10 }, BLACK, YELLOW, "ABOUT", WIDTH, HEIGHT);
    drawBox({ initial.x + WIDTH + 15, initial.y + 10 }, BLACK, RED, "SETTINGS", WIDTH, HEIGHT);
    drawBox({ initial.x + (WIDTH + 15) * 2, initial.y + 10 }, BLACK, ORANGE, "EXIT", WIDTH, HEIGHT);
}

void drawTableCell(int x, int y) {
    for (int i = x; i <= x + WIDTH_CELL; i++) {
        // Draw the top line of the cell
        gotoxy(i, y);
        cout << char(196);

        //  Draw the bottom line of the cell
        gotoxy(i, y + HEIGHT_CELL);
        cout << char(196);
    }

    for (int j = y; j <= y + HEIGHT_CELL; j++) {
        // Draw the left line of the cell
        gotoxy(x, j);
        cout << char(179);

        // Draw the right line of the cell
        gotoxy(x + WIDTH_CELL, j);
        cout << char(179);
    }

    // Draw the square corners for the cell

    gotoxy(x, y);
    cout << char(218);
    gotoxy(x + WIDTH_CELL, y);
    cout << char(191);
    gotoxy(x, y + HEIGHT_CELL);
    cout << char(192);
    gotoxy(x + WIDTH_CELL, y + HEIGHT_CELL);
    cout << char(217);
}

void drawTable(Display& display) {
    display.start.x = (display.size_height - WIDTH_CELL * display.cols) / 2;
    display.start.y += 9;

    // Vẽ các ô
    for (int i = 0; i < display.rows; i++) {
        for (int j = 0; j < display.cols; j++) {
            drawTableCell(display.start.x + j * WIDTH_CELL, display.start.y + i * HEIGHT_CELL);
        }
    }

    // Vẽ các giao điểm
    for (int i = 1; i < display.rows; i++) {
        for (int j = 1; j < display.cols; j++) {
            gotoxy(display.start.x + j * WIDTH_CELL, display.start.y + i * HEIGHT_CELL);
            cout << char(197); 
        }
    }

    // Vẽ các nút nối
    for (int i = 1; i < display.rows; i++) {
        // Nút nối bên trái
        gotoxy(display.start.x, display.start.y + i * HEIGHT_CELL);
        cout << char(195); 

        // Nút nối bên phải
        gotoxy(display.start.x + display.cols * WIDTH_CELL, display.start.y + i * HEIGHT_CELL);
        cout << char(180); 
    }

    for (int j = 1; j < display.cols; j++) {
        // Nút nối trên
        gotoxy(display.start.x + j * WIDTH_CELL, display.start.y);
        cout << char(194); 

        // Nút nối dưới
        gotoxy(display.start.x + j * WIDTH_CELL, display.start.y + display.rows * HEIGHT_CELL);
        cout << char(193); 
    }
}

void searchSuggestionUI(Trie& Dictionary, Display& display) {
    showCursorOnScr(true); // Hiện vị trí con trỏ trên màn hình console

    // Tạo ô để điền từ vào

    getConsoleSize(display.size_height, display.size_width);

    display.start.x = (display.size_height - 50) / 2;
    display.start.y = display.size_width / 2 - 16;

    gotoxy(display.start.x - 6, display.start.y + 1);
    cout << "  ____                      _      __        __            _  ";
    gotoxy(display.start.x - 6, display.start.y + 2);
    cout << " / ___|  ___  __ _ _ __ ___| |__   \\ \\      / /__  _ __ __| | ";
    gotoxy(display.start.x - 6, display.start.y + 3);
    cout << " \\___ \\ / _ \\/ _` | '__/ __| '_ \\   \\ \\ /\\ / / _ \\| '__/ _` | ";
    gotoxy(display.start.x - 6, display.start.y + 4);
    cout << "  ___) |  __/ (_| | | | (__| | | |   \\ V  V / (_) | | | (_| | ";
    gotoxy(display.start.x - 6, display.start.y + 5);
    cout << " |____/ \\___|\\__,_|_|  \\___|_| |_|    \\_/\\_/ \\___/|_|  \\__,_| ";

    display.start.y = display.size_width / 2 - 8;

    drawBox(display.start, BLACK, WHITE, "", 50, 2);

    gotoxy(display.start.x + 1, display.start.y + 1);
    cout << "Enter word: ";

    // In các thông số phụ trong việc tìm kiếm

    gotoxy(display.start.x - 25 , display.start.y + 7);
    cout << "Time for search: ";
    gotoxy(display.start.x + 13, display.start.y + 7);
    cout << "Size for search: " << Dictionary.numSuggestedWords;
    gotoxy(display.start.x + 47, display.start.y + 7);
    cout << "Number of comparisons: ";

    drawBox({ 5, 25 }, BLACK, GREY, "esc x 2: BACK", WIDTH / 2 + 4, HEIGHT / 2);
}

void AboutUI() {
    showCursorOnScr(false); // Ẩn con trỏ trên màn hình console
    system("cls");
    drawLogo();

    drawBox({ 17,12 }, BLACK, WHITE, "", WIDTH * 4 + 3, HEIGHT * 3 - 2);

    gotoxy(19, 13);
    cout << " Welcome to ";
    setColor(BLACK, YELLOW);
    cout << "WORDIFY APP! ";
    resetColor();
    cout << "This is project of ";
    setColor(BLACK, PINK);
    cout << "Tran Anh Khoa. ";
    resetColor();
    cout << "This assignment is my";
    gotoxy(19, 14);
    cout << "own work except where I have acknowledged the use of the works of other people.";

    gotoxy(19, 16);
    cout << "  This application is designed to make word management quick and effortless.";
    gotoxy(19, 17);
    cout << "With search suggestions and auto-complete, finding the words becomes much easier.";
    gotoxy(19, 18);
    cout << "It also includes features such as adding and removing words from the dictionary.";
    gotoxy(19, 19);
    cout << "This allows you to customize your word collection to better suit yourself.";

    gotoxy(19, 21);
    setColor(BLACK, BLUE);
    cout << "  Begin your journey now and discover how enjoyable word management can be!";
    resetColor();

    drawBox({ 5, 25 }, BLACK, GREY, "esc: BACK", WIDTH / 2, HEIGHT / 2);
}

void InsertWordUI(Display& display) {
    showCursorOnScr(true); // Hiện con trỏ trên màn hình console

    getConsoleSize(display.size_height, display.size_width);

    display.start.x = (display.size_height - 50) / 2;
    display.start.y = display.size_width / 2 - 12;

    // Draw title
    gotoxy(display.start.x - 4, display.start.y + 1);
    cout << "  ___                     _    __        __            _";
    gotoxy(display.start.x - 4, display.start.y + 2);
    cout << " |_ _|_ __  ___  ___ _ __| |_  \\ \\      / /__  _ __ __| |";
    gotoxy(display.start.x - 4, display.start.y + 3);
    cout << "  | || '_ \\/ __|/ _ \\ '__| __|  \\ \\ /\\ / / _ \\| '__/ _` |";
    gotoxy(display.start.x - 4, display.start.y + 4);
    cout << "  | || | | \\__ \\  __/ |  | |_    \\ V  V / (_) | | | (_| |";
    gotoxy(display.start.x - 4, display.start.y + 5);
    cout << " |___|_| |_|___/\\___|_|   \\__|    \\_/\\_/ \\___/|_|  \\__,_|";

    display.start.y = display.size_width / 2 - 3;

    drawBox(display.start, BLACK, WHITE, "", 50, 2);

    gotoxy(display.start.x + 1, display.start.y + 1);
    cout << "Enter word: ";

    gotoxy(display.start.x - 7, display.start.y + 4);
    setColor(BLACK, YELLOW);
    cout << "NOTICE";
    resetColor();
    cout << ": Words must be 1 - 20 characters, all lowercase letters only";

    drawBox({ 5, 25 }, BLACK, GREY, "esc x 2: BACK", WIDTH / 2 + 4, HEIGHT / 2);
}

void RemoveWordUI(Display& display) {
    showCursorOnScr(true); // Bật con trỏ trên màn hình console

    getConsoleSize(display.size_height, display.size_width);

    display.start.x = (display.size_height - 50) / 2;
    display.start.y = display.size_width / 2 - 12;

    // Draw title
    gotoxy(display.start.x - 8, display.start.y + 1);
    cout << "  ____                                __        __            _ ";
    gotoxy(display.start.x - 8, display.start.y + 2);
    cout << " |  _ \\ ___ _ __ ___   _____   _____  \\ \\      / /__  _ __ __| |";
    gotoxy(display.start.x - 8, display.start.y + 3);
    cout << " | |_) / _ \\ '_ ` _ \\ / _ \\ \\ / / _ \\  \\ \\ /\\ / / _ \\| '__/ _` |";
    gotoxy(display.start.x - 8, display.start.y + 4);
    cout << " |  _ <  __/ | | | | | (_) \\ V /  __/   \\ V  V / (_) | | | (_| |";
    gotoxy(display.start.x - 8, display.start.y + 5);
    cout << " |_| \\_\\___|_| |_| |_|\\___/ \\_/ \\___|    \\_/\\_/ \\___/|_|  \\__,_|";

    display.start.y = display.size_width / 2 - 3;

    drawBox(display.start, BLACK, WHITE, "", 50, 2);

    gotoxy(display.start.x + 1, display.start.y + 1);
    cout << "Enter word: ";
    gotoxy(display.start.x - 7, display.start.y + 4);
    setColor(BLACK, YELLOW);
    cout << "NOTICE";
    resetColor();
    cout << ": Words must be 1 - 20 characters, all lowercase letters only";

    drawBox({ 5, 25 }, BLACK, GREY, "esc x 2: BACK", WIDTH / 2 + 4, HEIGHT / 2);
}

void SettingsUI(Trie& Dictionary, int& startX, int& startY) {
    showCursorOnScr(false); // Ẩn vị trí con trỏ trên màn hình console
    system("cls");

    int width, height;
    getConsoleSize(width, height);

    startX = (width - 54) / 2;
    startY = height;

    gotoxy(startX + 5, startY - 28);
    cout << "  ____       _   _   _                 ";
    gotoxy(startX + 5, startY - 27);
    cout << " / ___|  ___| |_| |_(_)_ __   __ _ ___ ";
    gotoxy(startX + 5, startY - 26);
    cout << " \\___ \\ / _ \\ __| __| | '_ \\ / _` / __|";
    gotoxy(startX + 5, startY - 25);
    cout << "  ___) |  __/ |_| |_| | | | | (_| \\__ \\";
    gotoxy(startX + 5, startY - 24);
    cout << " |____/ \\___|\\__|\\__|_|_| |_|\\__, |___/";
    gotoxy(startX, startY - 23);
    cout << "                                   |___/     ";

    gotoxy(startX, startY - 20);
    cout << "Press";
    setColor(BLACK, BLUE);
    cout << " [1]";
    resetColor();
    cout << " to select the number of suggestion is";
    setColor(BLACK, BLUE);
    cout << " 1 word";
    resetColor();

    gotoxy(startX, startY - 18);
    cout << "Press";
    setColor(BLACK, ORANGE);
    cout << " [2]";
    resetColor();
    cout << " to select the number of suggestion is";
    setColor(BLACK, ORANGE);
    cout << " 5 word";
    resetColor();

    gotoxy(startX, startY - 16);
    cout << "Press";
    setColor(BLACK, GREEN);
    cout << " [3]";
    resetColor();
    cout << " to select the number of suggestion is";
    setColor(BLACK, GREEN);
    cout << " 10 word";
    resetColor();

    gotoxy(startX, startY - 14);
    cout << "Press";
    setColor(BLACK, IVORY);
    cout << " [4]";
    resetColor();
    cout << " to select the number of suggestion is";
    setColor(BLACK, IVORY);
    cout << " 15 word";
    resetColor();

    gotoxy(startX, startY - 12);
    cout << "Press";
    setColor(BLACK, PINK);
    cout << " [5]";
    resetColor();
    cout << " to select the number of suggestion is";
    setColor(BLACK, PINK);
    cout << " 20 word";
    resetColor();

    gotoxy(startX, startY - 10);
    setColor(BLACK, WHITE);;
    cout << "Number of suggested words that program will provide: " << Dictionary.numSuggestedWords << " words";

    drawBox({ 5, 25 }, BLACK, GREY, "esc: BACK", WIDTH / 2 + 2, HEIGHT / 2);
}

void AnnouncementUI() {
    showCursorOnScr(false); // Ẩn vị trí con trỏ trên màn hình console

    int startX, startY;

    getConsoleSize(startX, startY);

    startX = (startX - (WIDTH * 3 - 6)) / 2 ;
    startY = (startY - (HEIGHT * 2 - 2)) / 2;

    drawBox({ startX, startY }, BLACK, WHITE, "", WIDTH * 3 - 6, HEIGHT * 2 - 3);

    gotoxy(startX + 3, startY + 2);
    cout << "The program is currently paused. To return to the ";
    gotoxy(startX + 3, startY + 3);
    cout << "main screen, please press the ESC key once more!";
}

void ExitUI() {
    int startX, startY;

    getConsoleSize(startX, startY);

    startX = (startX - (WIDTH * 3 - 6)) / 2;
    startY = (startY - (HEIGHT * 2 - 2)) / 2;

    drawBox({ startX, startY }, BLACK, WHITE, "", WIDTH * 3 - 6, HEIGHT * 2 - 3);

    gotoxy(startX + 3, startY + 2);
    cout << "Your program is about to complete its execution ";
    gotoxy(startX + 3, startY + 3);
    cout << "process and will terminate in just a few seconds";
}
