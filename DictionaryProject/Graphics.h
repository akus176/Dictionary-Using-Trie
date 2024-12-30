#pragma once
#include "Libary.h"

void setColor(int background_color, int text_color);

void resetColor();

void gotoxy(int x, int y);

void showCursorOnScr(bool boolean);

void getConsoleSize(int& width, int& height);

void drawBox(Point point, int b_color, int t_color, string content, int width, int height);

void drawLogo();

void AppStartUI(const Point initial);

void searchSuggestionUI(Trie& Dictionary, Display& display);

void drawTableCell(int x, int y);

void drawTable(Display& display);

void InsertWordUI(Display& display);

void RemoveWordUI(Display& display);

void AboutUI();

void SettingsUI(Trie& Dictionary, int& startX, int& startY);

void AnnouncementUI();

void ExitUI();

string findContent(Point current, const Point initial);

int findTextColor(Point current, const Point initial);

void processMoveUp(Point& current, const Point initial);

void processMoveDown(Point& current, const Point initial);

void processMoveLeft(Point& current, const Point initial);

void processMoveRight(Point& current, const Point initial);