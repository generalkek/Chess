#include "Pieces.h"

 std::vector<Entity*>  Board;
//---------------------------------------//
Entity* find_piece(int xx, int yy)
{
	/*
		finds and returns the piece by its coordinates
	*/
	for (int i = 0; i < Board.size(); ++i)
	{
		if (xx == Board[i]->x && yy == Board[i]->y) return Board[i];	
	}
	return nullptr;
}

Entity::Entity(int xx, int yy, char type, Player s)
	:x(xx), y(yy), piece_type(type), side(s)
{
	life = true;
	moved = false;
	char* temp = convert(xx, yy);
	*temp = type;
	if (s == Player::white)
		*(temp - 1) = 'W';
	else *(temp - 1) = 'B';
}

bool Entity::passability(int xx, int yy)
{
	/*
	checks whether or not there are any object on piece way
	*/
	if (this->piece_type == 'N') return true;
	//vertical
	if (xx==x&&yy>y) 
	{
		while (yy != y)
		{
			yy--;
			Entity* temp = find_piece(xx, yy);
			if (temp != nullptr &&  yy != y) return false;
		}
		return true;
	}
	else if (xx == x && yy < y)
	{
		while (yy != y)
		{
			yy++;
			Entity* temp = find_piece(xx, yy);
			if (temp != nullptr &&  yy != y) return false;
		}
		return true;
	}
	//horizontal
	else if (xx > x && yy == y)
	{
		while (xx != x)
		{
			xx--;
			Entity* temp = find_piece(xx, yy);
			if (temp != nullptr && xx != x ) return false;
		}
		return true;
	}
	else if (xx < x && yy == y)
	{
		while (xx != x)
		{
			xx++;
			Entity* temp = find_piece(xx, yy);
			if (temp != nullptr && xx != x ) return false;
		}
		return true;
	}
	//diagonal
	else if (xx < x && yy < y)
	{
		while (xx != x&&yy!=y)
		{
			xx++; yy++;
			Entity* temp = find_piece(xx, yy);
			if (temp != nullptr && (xx != x && yy != y)) return false;
		}
		return true;
	}
	else if (xx > x && yy > y)
	{
		while (xx != x && yy != y)
		{
			xx--; yy--;
			Entity* temp = find_piece(xx, yy);
			if (temp != nullptr && (xx != x && yy != y)) return false;
		}
		return true;
	}
	else if (xx < x && yy > y)
	{
		while (xx != x && yy != y)
		{
			xx++; yy--;
			Entity* temp = find_piece(xx, yy);
			if (temp != nullptr && (xx != x && yy != y)) return false;
		}
		return true;
	}
	else if (xx > x && yy < y)
	{
		while (xx != x && yy != y)
		{
			xx--; yy++;
			Entity* temp = find_piece(xx, yy);
			if (temp != nullptr&&(xx != x && yy != y)) return false;
		}
		return true;
	}
	
}

bool Entity::king_in_check(int xx, int yy)
{
	/*
		checks if there is a check for a king after step
	*/
	int tempx=this->x, tempy= this->y;
	Entity* temp = find_piece(xx, yy);

	step(xx, yy);
	if (check(this->side)) { 
		undo_step(tempx, tempy, temp);
		return true; }
	else {
		undo_step(tempx, tempy, temp);
		return false;
	}
}

void Entity::step(int xx, int yy)
{
	/*
		implemets piece moving
	*/
	char* current = convert(x, y);//clean current position
	*(current - 1) = *current = ' ';

	char* temp = convert(xx, yy);//get final position
	if (temp == nullptr) 
	{ 
		cout << "step()::[Inccorect coordinate, please try one more!]\n"; 
	return; }
	if (isalpha(*temp)) //if there is an object, kill the object(it can't be alies piece, 
		//cause we have done check before call this(step()) function)
	{ 
		Entity* target = find_piece(xx, yy);
		target->life = false;
		target->x = 0;
		target->y = 0;
	}
	*temp = piece_type;//fill final position 
	if (side == Player::white) *(temp - 1) = 'W';
	
	else *(temp - 1) = 'B';
	//update coordinate
	x = xx;
	y = yy;
}

void Entity::undo_step(int xx, int yy, Entity* trg)
{
	//vice versa to step() function
	/*
	we remember begin coordinate in (xx, yy)
	and killed object(if any was) in trg
	from this information we can restore positions on board
	*/
	/*
	this function is needed when we want to check if there is check for king after move,
	and after we done "verification" we call this function to restore
	*/
	if (trg == nullptr)
	{
		char* current = convert(this->x, this->y);
		*(current - 1) = *current = ' ';
		this->x = xx;
		this->y = yy;
		current = convert(this->x, this->y);
		*current = this->piece_type;
		if (side == Player::white) * (current - 1) = 'W';

		else *(current - 1) = 'B';
	}
	else {
		trg->life = true;
		char* current = convert(this->x, this->y);
		*current = trg->piece_type;
		if (trg->side == Player::white) * (current - 1) = 'W';

		else *(current - 1) = 'B';
		trg->x = this->x;
		trg->y = this->y;

		this->x = xx;
		this->y = yy;
		current = convert(this->x, this->y);
		*current = this->piece_type;
		if (side == Player::white) * (current - 1) = 'W';

		else *(current - 1) = 'B';
	}
	
}
void Entity::mark_cell()
{
	// mark all possible moves by star
	for (int x = 1; x < 9; x++)
		for (int y = 1; y < 9; y++)
		{
			if (correct_move(x, y)&&
				passability(x,y))
				mark(x, y);
		}
}
//---------------------------------------//
Pawn::Pawn(int xx, int yy, char type, Player s)
	: Entity(xx, yy, 'P', s)
{
}

bool Pawn::correct_move(int xx, int yy)
{
	/*
		checks correctness of moving for pawn
	*/
	char* temp = convert(xx, yy);
	if (temp == nullptr) {
		
			cout << "Pawn::correct_move()::[Inccorect coordinate, please try one more!]\n";
			return false;
		
	}
	if (isalpha(*temp))/*
					   if pawn is going to attack, it can move aside, 
					   in this scope, function checks that white pawn can move "down",
					   and black can move "up", after that it finds object that pawn wants attack to 					   
					   */
	{
		if (((xx==x+1||xx==x-1)&&yy==y+1)&&side==Player::white)
			for (int i = 0; i < Board.size(); ++i)
			{
				if (side != Board[i]->side)
				{
					if (xx == Board[i]->x && yy == Board[i]->y) return true;
				}
			}
		if (((xx == x + 1 || xx == x - 1) && yy == y - 1) && side == Player::black)
			for (int i = 0; i < Board.size(); ++i)
			{
				if (side != Board[i]->side)
				{
					if (xx == Board[i]->x && yy == Board[i]->y) return true;
				}
			}
		return false;
	}

	if (side == Player::white)
	{
		if (!moved)//if the pawn hasn't moved yet, it can move up to 2 cells
		{
			if (yy - y <= 2 && yy - y > 0 && xx == x) return true;
		}
		if (yy - y <= 1 && yy - y > 0 && xx == x) return true;
	}
	else
	{
		if (!moved)
		{
			if (y - yy <= 2 && y - yy > 0 && xx == x) return true;
		}
		if (y - yy <= 1 && y - yy > 0 && xx == x) return true;
	}

	return false;
}

bool Pawn::move(int xx, int yy)
{
	/*
	complex function for each type of piece
	that checks each aspect of moving and end up do its move, if the last one is correct
	*/
	if (!in_box(xx, yy)) {
		system("cls");
		draw();
		cout << "move()::out of board, please type correct coordinate for move.\n";
		return false;
	}

	if (!passability(xx, yy)) 
	{
		system("cls");
		draw();
		cout << "move()::inccorect move, please try on more!\n";
		return false;
	}

	if (king_in_check(xx,yy))
	{
		system("cls");
		draw();
		cout << "move()::This move results in check for your king!\n";
		return false;
	}

	if (correct_move(xx, yy))	step(xx, yy);

	else {
		system("cls");
		draw();
		cout << "move()::inccorect move, please try on more!\n";
		return false;
	}
	if (side == Entity::Player::white)
	{
		if (y == 8)
			transform();
	}
	else if (side == Entity::Player::black)
	{
		if (y == 1)
			transform();
	}
	if (!moved) moved = true;

	system("cls");
	draw();
	return true;
}

void Pawn::mark_cell()
{
	for (int x= 1;x<9;x++)
		for (int y = 1; y < 9; y++)
		{
			if (correct_move(x, y))
				mark(x, y);
		}
}

bool Pawn::transform()
{
	/*
	implements transforming when pawn reach enemy side
	*/
	cout << "your panw reach the enemy baseline,\nso you can"
		    " transform it to another piece\n";
	cout << "choose what piece you need from available list\n";
	cout << "list of piece:\nRook\nBishop\nKnight\nQueen\n";
	char temp;
	while (temp = cin.get())
	{
		if (isalpha(temp))
		{
			switch (temp)
			{
			case 'R': case 'r':
				exchange_piece(this, new Rook(x, y, 'R', side));
				return true;
			case 'N': case 'n':
				exchange_piece(this, new Knight(x, y, 'N', side));
				return true;
			case 'B': case 'b':
				exchange_piece(this, new Bishop(x, y, 'B', side));
				return true;
			case 'Q': case 'q':
				exchange_piece(this, new Queen(x, y, 'Q', side));
				return true;
			default :
				cout << "You typed wrong letter, please try one more\n";
			}
		}
		else cout << "You typed the wrong symbol, please enter the first symbol of type you have chosen\n";
	}
	
	return true;
}
//---------------------------------------//
Rook::Rook(int xx, int yy, char type, Player s)
	:Entity(xx,yy,'R',s)
{
	moved = false;
}

bool Rook::correct_move(int xx, int yy)
{
	/*
		checks correctness of moving for rook
	*/
	Entity* temp = find_piece(xx, yy);
	if (temp != nullptr)
	{
		if (temp->side == side) return false;
	}
	if ((xx == x && abs(yy - y) < 8) || (abs( xx - x < 8) && yy == y)) return true;
	return false;
}

bool Rook::move(int xx, int yy)
{
	if (!in_box(xx, yy)) {
		cout << "move()::out of board, please type correct coordinate for move.\n";
		return false;
	}
	if (!passability(xx, yy))
	{
		system("cls");
		draw();
		cout << "move()::inccorect move, please try on more!\n";
		return false;
	}

	if (king_in_check(xx, yy))
	{
		system("cls");
		draw();
		cout << "move()::This move results in check for your king!\n";
		return false;
	}

	if (correct_move(xx, yy))	step(xx, yy);

	else {
		system("cls");
		draw();
		cout << "move()::inccorect move, please try on more!\n";
		return false;
	}

	if (!moved) moved = true;

	system("cls");
	draw();
	return true;
}
//---------------------------------------//
Knight::Knight(int xx, int yy, char type, Player s)
	: Entity(xx,yy,'N',s)
{
}

bool Knight::correct_move(int xx, int yy)
{
	/*
		checks correctness of moving for knight
	*/
	Entity* temp = find_piece(xx, yy);
	if (temp != nullptr)
	{
		if (temp->side == side) return false;
	}
	if ((xx == x + 2 && yy == y + 1) ||
		(xx == x + 2 && yy == y - 1) ||
		(xx == x - 2 && yy == y + 1) ||
		(xx == x - 2 && yy == y - 1) ||

		(xx == x - 1 && yy == y + 2) ||
		(xx == x - 1 && yy == y - 2) ||
		(xx == x + 1 && yy == y + 2) ||
		(xx == x + 1 && yy == y - 2))	return true;
	return false;
}

bool Knight::move(int xx, int yy)
{
	if (!in_box(xx, yy)) {
		cout << "move()::out of board, please type correct coordinate for move.\n";
		return false;
	}
	if (king_in_check(xx, yy))
	{
		system("cls");
		draw();
		cout << "move()::This move results in check for your king!\n";
		return false;
	}

	if (correct_move(xx, yy))
		step(xx, yy);
	else {
		system("cls");
		draw();
		cout << "move()::inccorect move, please try on more!\n";
		return false;
	}

	system("cls");
	draw();
	return true;
}
//---------------------------------------//
Bishop::Bishop(int xx, int yy, char type, Player s)
	:Entity(xx, yy, 'B', s)
{
}

bool Bishop::correct_move(int xx, int yy)
{
	/*
		checks correctness of moving for bishop
	*/
	Entity* temp = find_piece(xx, yy);
	if (temp != nullptr)
	{
		if (temp->side == side) return false;
	}
	if (abs(xx - x) == abs(yy - y)) return true;
	return false;
}

bool Bishop::move(int xx, int yy)
{
	if (!in_box(xx, yy)) {
		cout << "move()::out of board, please type correct coordinate for move.\n";
		return false;
	}
	if (!passability(xx, yy))
	{
		system("cls");
		draw();
		cout << "move()::inccorect move, please try on more!\n";
		return false;
	}

	if (king_in_check(xx, yy))
	{
		system("cls");
		draw();
		cout << "move()::This move results in check for your king!\n";
		return false;
	}

	if (correct_move(xx, yy))
		step(xx, yy);

	else {
		system("cls");
		draw();
		cout << "move()::inccorect move, please try on more!\n";
		return false;
	}

	system("cls");
	draw();
	return true;
}
//---------------------------------------//
Queen::Queen(int xx, int yy, char type, Player s)
	:Entity(xx, yy, 'Q', s)
{
}

bool Queen::correct_move(int xx, int yy)
{
	/*
		checks correctness of moving for queen
	*/
	Entity* temp = find_piece(xx, yy);
	if (temp != nullptr)
	{
		if (temp->side == side) return false;
	}
	if ((abs(xx - x) == abs(yy - y))||
		(xx == x && abs(yy - y) < 8) || (abs(xx - x < 8) && yy == y)) return true;
	return false;
}

bool Queen::move(int xx, int yy)
{
	if (!in_box(xx, yy)) {
		cout << "move()::out of board, please type correct coordinate for move.\n";
		return false;
	}
	if (!passability(xx, yy))
	{
		system("cls");
		draw();
		cout << "move()::inccorect move, please try on more!\n";
		return false;
	}

	if (king_in_check(xx, yy))
	{
		system("cls");
		draw();
		cout << "move()::This move results in check for your king!\n";
		return false;
	}

	if (correct_move(xx, yy))
		step(xx, yy);

	else {
		system("cls");
		draw();
		cout << "move()::inccorect move, please try on more!\n";
		return false;
	}

	system("cls");
	draw();
	return true;
}
//---------------------------------------//
King::King(int xx, int yy, char type, Player s)
	:Entity(xx, yy, 'K', s)
{
	moved = false;
}

bool King::correct_move(int xx, int yy)
{
	/*
		checks correctness of moving for king
	*/
	Entity* temp = find_piece(xx, yy);
	if (temp != nullptr)
	{
		if (temp->side == side) return false;
	}
	if ((xx == x && abs(yy - y) < 2) || ((abs(xx - x) < 2) && yy == y)||
		(abs(xx - x) == abs(yy - y)&&(abs(xx - x)<2))) return true;
	return false;
}

bool King::move(int xx, int yy)
{
	if (!in_box(xx, yy)) {
		cout << "move()::out of board, please type correct coordinate for move.\n";
		return false;
	}
	if (!passability(xx, yy))
	{
		system("cls");
		draw();
		cout << "move()::inccorect move, please try on more!\n";
		return false;
	}

	if (king_in_check(xx, yy))
	{
		system("cls");
		draw();
		cout << "move()::This move results in check for your king!\n";
		return false;
	}

	if (abs(xx - x) > 1)
	{
		if (castling(xx, yy))
		{
			system("cls");
			draw();
			cout << "move()::castling made successfully!\n";
			if (!moved) moved = true;
			return true;
		}
		system("cls");
		draw();
		cout << "move()::castling cannot be done!\n";
		return false;
	}

	if (correct_move(xx, yy))
		step(xx, yy);

	else {
		system("cls");
		draw();
		cout << "move()::inccorect move, please try on more!\n";
		return false;
	}

	if (!moved) moved = true;

	system("cls");
	draw();
	return true;
}

bool King::castling(int xx, int yy)
{
	/*
	checks if available to do castling, and does it if ok
	*/
	if (moved) return false;

	if (side == Entity::Player::white)
	{
		if (xx > x)
		{
			if (!passability(8, 1)) return false;
			Entity* temp = find_piece(8, 1);
			if (temp == nullptr) return false;
			if (temp->piece_type == 'R' && !temp->moved)
				;
		}
		else if (xx < x) 
		{
			if (!passability(1, 1)) return false;
			Entity* temp = find_piece(1, 1);
			if (temp == nullptr) return false;
			if (temp->piece_type == 'R' && !temp->moved);
		}
	}
	else if (side == Entity::Player::black)
	{
		if (xx > x) {
			if (!passability(8, 8)) return false;
			Entity* temp = find_piece(8, 8);
			if (temp == nullptr) return false;
			if (temp->piece_type == 'R' && !temp->moved);
		}
		else if (xx < x) {
			if (!passability(1, 8)) return false;
			Entity* temp = find_piece(8, 1);
			if (temp == nullptr) return false;
			if (temp->piece_type == 'R' && !temp->moved);
		}
	}
	//castling allowed, make move
	if (side == Entity::Player::white) 
	{
		if (xx > x) {
			step(7, 1);
			Entity* temp = find_piece(8, 1);
			temp->step(6, 1);
		}
		if (xx < x) {
			step(3, 1);
			Entity* temp = find_piece(1, 1);
			temp->step(4, 1);
		}
	}
	else if (side == Entity::Player::black)
	{
		if (xx > x) {
			step(7, 8);
			Entity* temp = find_piece(8, 8);
			temp->step(6, 8);
		}
		if (xx < x) {
			step(3, 8);
			Entity* temp = find_piece(1, 8);
			temp->step(4, 8);
		}
	}

	return true;
}
//---------------------------------------//
void make_board()
{
	/*
	create pieces and put them into vector, for convenient use
	*/
	Board.push_back(new Rook(1, 1, 'R', Entity::Player::white));
	Board.push_back(new Rook(8, 1, 'R', Entity::Player::white));

	Board.push_back(new Knight(2, 1, 'N', Entity::Player::white));
	Board.push_back(new Knight(7, 1, 'N', Entity::Player::white));

	Board.push_back(new Bishop(3, 1, 'B', Entity::Player::white));
	Board.push_back(new Bishop(6, 1, 'B', Entity::Player::white));

	Board.push_back(new Queen(4, 1, 'Q', Entity::Player::white));
	Board.push_back(new King(5, 1, 'K', Entity::Player::white));

	for (int i = 1; i < 9; ++i)
	{
		Board.push_back(new Pawn(i, 2, 'P', Entity::Player::white));
	}
	for (int i = 1; i < 9; ++i)
	{
		Board.push_back(new Pawn(i, 7, 'P', Entity::Player::black));
	}

	Board.push_back(new Rook(1, 8, 'R', Entity::Player::black));
	Board.push_back(new Rook(8, 8, 'R', Entity::Player::black));

	Board.push_back(new Knight(2, 8, 'N', Entity::Player::black));
	Board.push_back(new Knight(7, 8, 'N', Entity::Player::black));

	Board.push_back(new Bishop(3, 8, 'B', Entity::Player::black));
	Board.push_back(new Bishop(6, 8, 'B', Entity::Player::black));

	Board.push_back(new Queen(4, 8, 'Q', Entity::Player::black));
	Board.push_back(new King(5, 8, 'K', Entity::Player::black));
}
//void make_board()
//{
//	Board.push_back(new King(7, 6, 'K', Entity::Player::white));
//	Board.push_back(new King(8, 8, 'K', Entity::Player::black));
//	Board.push_back(new Queen(6, 6, 'Q', Entity::Player::white));
//	//Board.push_back(new Rook(7, 1, 'R', Entity::Player::white));
//}//test case
void fill_board()
{
	/*
	fill "low-level" array with symbols(piece_type, and object side)
	*/
	for (auto vec : Board)
	{
		char* temp = convert(vec->x, vec->y);
		*temp = vec->piece_type;
		if (vec->side == Entity::Player::white) * (temp - 1) = 'W';
		else  *(temp - 1) = 'B';
	}
}
void clear_board()
{
	/*
	when game has end, invoke this function for correct deleting of objects
	*/
	for (auto& x : Board)
	{
		delete x;
	}
	Board.clear();
	for (int x =1;x<9;++x)
		for (int y = 1; y < 9; ++y)
		{
			char* temp = convert(x, y);
			*(temp - 1) = *temp = ' ';
		}
}

void exchange_piece(Entity* del, Entity* ins)
{
	/*
	when transform the pawn, invoke this for correct exchange of pawn-object and new object 
	*/
	ins->life = del->life;
	ins->moved = del->moved;
	Board.erase(find(Board.begin(), Board.end(), del));
	delete del;
	Board.push_back(ins);
}

bool check(bool trig)
{
	/*
	checks if there is check for a king
	*/
	for (int i = 0; i < Board.size(); ++i)
	{
		if (Board[i]->piece_type == 'K')
		{
			Entity* temp = Board[i];
			for (int j = 0; j < Board.size(); ++j)
			{
				if (temp->side != Board[j]->side)
					if (Board[j]->correct_move(temp->x, temp->y) &&
						Board[j]->passability(temp->x, temp->y) &&
						Board[j]->life == true)
					{
						if (trig)
						{
							if (temp->side == Entity::Player::white)
								cout << "Check()::Check for white King\n";
							else cout << "Check()::Check for black King\n";
						}
						return true;
					}

			}
		}
	}
	return false;
}
bool check(Entity::Player s, bool trig )
{
	/*
	checks if there is check for a concrete king
	*/
	for (int i = 0; i < Board.size(); ++i)
	{
		if (Board[i]->piece_type == 'K'&&
			Board[i]->side==s)//difference is here
		{
			Entity* temp = Board[i];
			for (int j = 0; j < Board.size(); ++j)
			{
				if (temp->side != Board[j]->side)
					if (Board[j]->correct_move(temp->x, temp->y) &&
						Board[j]->passability(temp->x, temp->y)&&
						Board[j]->life == true)
					{					
						if (trig)
						{
							if (temp->side == Entity::Player::white)
								cout << "Check()::Check for white King\n";
							else cout << "Check()::Check for black King\n";
						}
						return true;
					}

			}
			return false;
		}
	}
}

bool stalemate(bool player)
{
	/*
	checks if there is stalemate
	*/
	bool stalemate_for_white = true;
	bool stalemate_for_black = true;

	for (int i = 0; i < Board.size(); ++i)
	{
		for (int xx =1;xx<9;++xx)
			for (int yy = 1; yy < 9; ++yy)
			{
				/*
				for each piece, makes each available move, and checks if there is check for king
				if there is at least one move that doesn't invoke check for king, return false
				*/
				if (Board[i]->correct_move(xx,yy) &&
					Board[i]->passability(xx,yy)  &&
					Board[i]->life)
					if (!Board[i]->king_in_check(xx, yy)) 
					{ 
						if (Board[i]->side == Entity::Player::white)  stalemate_for_white = false; 
						else stalemate_for_black = false;
					}
			}
	}
	return (stalemate_for_black&&!player)||(stalemate_for_white&&player);
}

bool checkmate()
{
	/*
	it is said by itself
	*/
	bool checkmate_for_white = true;
	bool checkmate_for_black = true;

	for (int i = 0; i < Board.size(); ++i)
	{
		for (int xx = 1; xx < 9; ++xx)
			for (int yy = 1; yy < 9; ++yy)
			{
				/*
				for each piece, makes each available move, and checks if there is check for king
				if there is at least one move that doesn't invoke check for king, return false
				*/
				if (Board[i]->correct_move(xx, yy) &&
					Board[i]->passability(xx, yy) &&
					Board[i]->life)
					if (!Board[i]->king_in_check(xx, yy))
					{
						if (Board[i]->side == Entity::Player::white)  checkmate_for_white = false;
						else checkmate_for_black = false;
					}
			}
	}

	if (checkmate_for_white) {
		cout << "It is checkmate for white King\nBlack player win\n";
	}
	else if (checkmate_for_black) cout << "It is checkmate for black King\nWhite player win\n";

	return checkmate_for_black || checkmate_for_white;
}
