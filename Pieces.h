#pragma once
#include "Board.h"
#include <vector>

//---------------------------------------//
struct Entity
{
	/*
	abstract structure that implement piece model
	*/
	int x, y;
	char piece_type;
	enum Player { white, black};
	Player side;
	bool life;
	bool moved;

	Entity(int xx, int yy, char type, Player s);

	bool step_on(int xx, int yy) { return xx == x && yy == y; }
	bool passability(int xx, int yy);
	bool king_in_check(int xx, int yy);

	void step(int xx, int yy);
	void undo_step(int xx, int yy, Entity* trg);

	virtual bool correct_move(int xx, int yy)=0;
	virtual bool move(int xx, int yy)=0;
	virtual void mark_cell();

};
//---------------------------------------//
struct Pawn : Entity
{
	//particular case of piece model, with general interface(set of function)
	Pawn(int xx, int yy, char type, Player s);
	bool correct_move(int xx, int yy);
	bool move(int xx, int yy);	
	void mark_cell();
	bool transform();
};
//---------------------------------------//
struct Rook : Entity
{
	//particular case of piece model, with general interface(set of function)
	Rook(int xx, int yy, char type, Player s);
	bool correct_move(int xx, int yy);
	bool move(int xx, int yy);

};
//---------------------------------------//
struct Knight : Entity
{
	//particular case of piece model, with general interface(set of function)
	Knight(int xx, int yy, char type, Player s);
	bool correct_move(int xx, int yy);
	bool move(int xx, int yy);
	
};
//---------------------------------------//
struct Bishop :Entity
{
	//particular case of piece model, with general interface(set of function)
	Bishop(int xx, int yy, char type, Player s);
	bool correct_move(int xx, int yy);
	bool move(int xx, int yy);

};
//---------------------------------------//
struct Queen :Entity
{
	//particular case of piece model, with general interface(set of function)
	Queen(int xx, int yy, char type, Player s);
	bool correct_move(int xx, int yy);
	bool move(int xx, int yy);
};
//---------------------------------------//
struct King :Entity
{
	//particular case of piece model, with general interface(set of function)
	King(int xx, int yy, char type, Player s);
	bool correct_move(int xx, int yy);
	bool move(int xx, int yy);
	bool castling(int xx, int yy);
};
//---------------------------------------//
void make_board();
void fill_board();
void clear_board();
void exchange_piece(Entity*, Entity*);

Entity* find_piece(int xx, int yy);

bool check(bool trig = false);
bool check(Entity::Player, bool trig = false);

bool stalemate(bool player);
bool checkmate();