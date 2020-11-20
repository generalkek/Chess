#pragma once
#include <iostream>
#include <string>

using namespace std;

const string white = "White"; //label
const string black = "Black"; //label

const int ROWS = 18;
const int COLUMNS = 44;
const int hor_step = 5;
const int ver_step = 2;

const char hor = '-';
const char ver = '|';

char board[][COLUMNS];

char* convert(int x, int y);
bool in_box(int x, int y);
void draw();
void mark(int x, int y);
