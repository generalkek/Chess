#include "Board.h"

char board[ROWS][COLUMNS] =
{
	' ',' ',' ',' ',' ',' ','A',' ',' ',' ',' ','B',' ',' ',' ',' ','C',' ',' ',' ',' ','D',' ',' ',' ',' ','E',' ',' ',' ',' ','F',' ',' ',' ',' ','G',' ',' ',' ',' ','H',' ',' ',
	' ',' ',' ',hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,
	' ','1',' ',ver,' ',' ',' ',' ',ver,' ',' ',' ',' ',ver,' ',' ',' ',' ',ver,' ',' ',' ',' ',ver,' ',' ',' ',' ',ver,' ',' ',' ',' ',ver,' ',' ',' ',' ',ver,' ',' ',' ',' ',ver,
	' ',' ',' ',hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,
	' ','2',' ',ver,' ',' ',' ',' ',ver,' ',' ',' ',' ',ver,' ',' ',' ',' ',ver,' ',' ',' ',' ',ver,' ',' ',' ',' ',ver,' ',' ',' ',' ',ver,' ',' ',' ',' ',ver,' ',' ',' ',' ',ver,
	' ',' ',' ',hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,
	' ','3',' ',ver,' ',' ',' ',' ',ver,' ',' ',' ',' ',ver,' ',' ',' ',' ',ver,' ',' ',' ',' ',ver,' ',' ',' ',' ',ver,' ',' ',' ',' ',ver,' ',' ',' ',' ',ver,' ',' ',' ',' ',ver,
	' ',' ',' ',hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,
	' ','4',' ',ver,' ',' ',' ',' ',ver,' ',' ',' ',' ',ver,' ',' ',' ',' ',ver,' ',' ',' ',' ',ver,' ',' ',' ',' ',ver,' ',' ',' ',' ',ver,' ',' ',' ',' ',ver,' ',' ',' ',' ',ver,
	' ',' ',' ',hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,
	' ','5',' ',ver,' ',' ',' ',' ',ver,' ',' ',' ',' ',ver,' ',' ',' ',' ',ver,' ',' ',' ',' ',ver,' ',' ',' ',' ',ver,' ',' ',' ',' ',ver,' ',' ',' ',' ',ver,' ',' ',' ',' ',ver,
	' ',' ',' ',hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,
	' ','6',' ',ver,' ',' ',' ',' ',ver,' ',' ',' ',' ',ver,' ',' ',' ',' ',ver,' ',' ',' ',' ',ver,' ',' ',' ',' ',ver,' ',' ',' ',' ',ver,' ',' ',' ',' ',ver,' ',' ',' ',' ',ver,
	' ',' ',' ',hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,
	' ','7',' ',ver,' ',' ',' ',' ',ver,' ',' ',' ',' ',ver,' ',' ',' ',' ',ver,' ',' ',' ',' ',ver,' ',' ',' ',' ',ver,' ',' ',' ',' ',ver,' ',' ',' ',' ',ver,' ',' ',' ',' ',ver,
	' ',' ',' ',hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,
	' ','8',' ',ver,' ',' ',' ',' ',ver,' ',' ',' ',' ',ver,' ',' ',' ',' ',ver,' ',' ',' ',' ',ver,' ',' ',' ',' ',ver,' ',' ',' ',' ',ver,' ',' ',' ',' ',ver,' ',' ',' ',' ',ver,
	' ',' ',' ',hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,

};

char* convert(int x, int y)
{
	/*
	function return position in "low-level" array of char, by using x and y
	position is used to write and read a character type 
	that create an illusion of moving pieces on board
	   	*/
	if (x <= 0)
	{
		std::cout << "Inccorect coordinates [" << x << "] <= 0\n";
		return nullptr;
	}
	if (x > 8)
	{
		std::cout << "Inccorect coordinates [" << x << "] > 8\n";
		return nullptr;
	}
	if (y <= 0)
	{
		std::cout << "Inccorect coordinates [" << y << "] <= 0\n";
		return nullptr;
	}
	if (y > 8)
	{
		std::cout << "Inccorect coordinates [" << y << "] > 8\n";
		return nullptr;
	}
	return &board[ver_step * y][1 + hor_step * x];
}

bool in_box(int x, int y)
{
	/*
	checks whether or not coordinates are pointing to the position on the board
	*/
	if (x < 1 || x>8 || y < 1 || y>8) return false;
	return true;
}

void draw()
{	//draw board from Board.cpp
	cout << "\t\t   " << white << endl;

	for (int i = 0; i < ROWS; ++i)
	{
		for (int j = 0; j < COLUMNS; ++j)
		{
			if (board[i][j])
				cout << board[i][j];
		}
		cout << '\n';
	}
	cout << "\t\t   " << black << endl;
}

void mark(int xx, int yy)
{
	char* temp = convert(xx, yy);
	*(temp-1) = '*';
}

