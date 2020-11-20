#include "Command.h"

bool PLAYER = true;
bool GAME = false;
bool QUIT = false;



int read_letter(char command)
{
	//reading the letter and transform to int
	switch (command)
	{
	case 'a':case'A': return 1;
	case 'b':case'B': return 2;
	case 'c':case'C': return 3;
	case 'd':case'D': return 4;

	case 'e':case'E': return 5;
	case 'f':case'F': return 6;
	case 'g':case'G': return 7;
	case 'h':case'H': return 8;
	default: {
		cout << "read_letter::Wrong command!" << endl;
		return -1; }
	}
}

Entity* read_command(const string& command)
{
	//read the coordinate from string, and return object
	//if coordinates are correct
	int xx = 0;	//coordinates
	int yy = 0;	//coordinates

	if (isdigit(command[0]))
	{	
		if (isalpha(command[1])) 
		{ 
			yy = command[0] - '0';
			xx = read_letter(command[1]); 
		}

		else { 
		xx = command[0] - '0'; 
		yy = command[1] - '0';
		}
	}
	else { 
		xx = read_letter(command[0]); 
		if (isalpha(command[1])) yy = read_letter(command[1]);

		else yy = command[1] - '0';
	}
	return find_piece(xx, yy);
	
}

Entity* read_command(const string& command, int& xx, int& yy)
{
	//read the coordinate from string, and return the object
	//if coordinates are correct
	/*
	overwriting this function is due to that we need coordinates of final position.
	first variety of this function return object(if any exist) in cell, 
	or nullptr if cell is empty, 
	but we generaly move in empty cell 
	thus if nullptr is returned we cannot get the final position by using first variety, 
	so we need posibility to modify our cordinates that are defined out of the scope of this function.
	*/
	xx = 0;	//coordinates
	yy = 0;	//coordinates

	if (isdigit(command[0]))
	{
		if (isalpha(command[1]))
		{
			yy = command[0] - '0';
			xx = read_letter(command[1]);
		}

		else {
			xx = command[0] - '0';
			yy = command[1] - '0';
		}
	}
	else {
		xx = read_letter(command[0]);
		if (isalpha(command[1])) yy = read_letter(command[1]);

		else yy = command[1] - '0';
	}
	return find_piece(xx, yy);
}

bool get_cordinate(string& firstc, string& secondc)
{
	// reads coordinates from stream, and write in two strings, which later will be used 
	// for moving
	char current;
	while (cin.get(current))
	{
		if ((current < 1) || (current > 255))
		{
			system("cls");
			draw();
			cout << "You type wrong symbol, please use English letters for command\n";
			cin.ignore(10, '\n');
			return false;
		}
		if (isalnum(current))
			firstc += current;
		else if ((current == ',' || current == '.' || isspace(current)) && (!(firstc.size() < 2))) break;
	}
	while (cin.get(current))
	{
		if ((current < 1) || (current > 255))
		{
			system("cls");
			draw();
			cout << "You type wrong symbol, please use English letters for command\n";
			cin.ignore(10, '\n');
			return false;
		}
		if (isalnum(current))
			secondc += current;
		else if ((current == ',' || current == '.' || isspace(current)) && (!(secondc.size() < 2))) break;
	}
	return true;
}
bool get_cordinate(string& firstc)
{
	// reads coordinates from stream, and write in two strings, which later will be used 
	// for moving
	char current;
	while (cin.get(current))
	{
		if ((current < 1) || (current > 255))
		{
			system("cls");
			draw();
			cout << "You type wrong symbol, please use English letters for command\n";
			cin.ignore(10, '\n');
			return false;
		}
		if (isalnum(current))
			firstc += current;
		else if ((current == ',' || current == '.' || isspace(current)) && (!(firstc.size() < 2))) break;
	}
	return true;
}

void get_command(bool trig)
{
	// reads command from stream, and call interactive function, if command is correct
	if (trig)
	{
		cout << reg;
		if (PLAYER) cout << "White turn\n";
		else cout << "Black turn\n";
	}
	char symbol;
	string command_name;
	cout << "> ";
	cin >> symbol;
	if ((symbol < 1) || (symbol > 255))
	{
		system("cls");
		if (GAME) draw();

		if (!trig) {
			cout << "You can use few functions: \n1. Start\n2. Restart\n3. Move (for moving the pieces)"
				<< "\nif you want quit, just type quit!\n\n";
		}
		cout << "You type wrong symbol, please use English letters for command\n";
		cin.ignore(10,'\n');
		return;
	}
	while (!isalpha(symbol)) cin>>symbol;
	if (isalpha(symbol))
	{
		cin.unget();
		cin >> command_name;
	}
	for (int i = 0; i < command_name.length(); ++i)
	{
		if (isalpha(command_name[i]))
			if (isupper(command_name[i]))
				command_name[i] = tolower(command_name[i]);
	}

	if (command_name == start)// begin playing
	{
		if (GAME) cout << "game already started\n";
		else {
			GAME = true;
			system("cls");
			play();
		}
		return;
	}

	if (command_name == moving) //set move
	{
		if (!GAME) { cout << "game hasn't  been started\n"; return; }

		string firstc, secondc;
		if (!get_cordinate(firstc, secondc)) return;
		move_piece(firstc, secondc);
		return;
	}
	
	if (command_name == reset) //restart
	{
		if (!GAME) cout << "game hasn't  been started\n";
		else restart();
		return;
	}
	
	if (command_name == quit) //quit
	{
		if (!QUIT) QUIT = true;
		clear_board();
		return;
	}
	if (command_name == helpp) //quit
	{
		system("cls");
		help();
		return;
	}
	if (command_name == ssp) //quit
	{
		if (!GAME) {
			cout << "game hasn't  been started\n";
			return;
		}
		system("cls");
		possible_step();
		return;
	}
	if (command_name == show_board) //quit
	{
		system("cls");
		if (GAME) draw();
		else {
			cout << "game hasn't  been started\n";
			cout << "please type \"start\" to begin playing\n";
		}
		return;
	}
	
	else //message about incorrect name of command
	{
		system("cls");
	
		if (GAME) {
			draw();
			cout << "You type the wrong name of command!\n";
		}
		else {
			cout << "You type the wrong name of command!\n";
			cout << "You can use few functions: \n1. Start\n2. Restart\n3. Move (for moving the pieces)\n4. Help"
				"\n5. Show - shows the board if game is started\n"
				<< "\nif you want quit, just type quit!\n\n";
		}
		cin.ignore(10, '\n');
	}
}

void help()
{
	cout << first_info;
}

void turn()
{
	/*
		switch turn
	*/
	if (PLAYER) PLAYER = false;

	else PLAYER = true;
}

bool which_turn(Entity* player)
{
	/*
	determines which side goes

	*/
	if (PLAYER && player->side == Entity::Player::white) return true;
	 
	else if (!PLAYER && player->side == Entity::Player::black) return true;

	else if (PLAYER && player->side == Entity::Player::black) 
	{
		system("cls");
		draw();
		cout << "It is white turn to move!\n";
		
	}
	else {
		system("cls");
		draw();
		cout << "It is black turn to move!\n";
	}
	return false;
}

void possible_step()
{
	string cor;
	get_cordinate(cor);
	Entity* temp = read_command(cor);
	if (temp == nullptr)
	{
		system("cls");
		draw();
		cout << "There is no such piece, please choose accurately\n";
		return;
	}
	temp->mark_cell();
	draw();
}

void game()
{
	//entry in game
	cout << greeting;
	cout << first_info;
	while (!QUIT)
		get_command(false);
}

void play()
{
	//start the game, also there is the game loop
	fill_board();
	make_board();
	draw();
	while (GAME)
	{
		get_command(true);

		if (QUIT) return;

		if (check(true))
			if (checkmate())
			{
				GAME = false;
				clear_board();
				break;
			}
		if (stalemate(PLAYER))
		{
			cout << "It is stalemate!\n";
			GAME = false;
			clear_board();
		}
		
	}
	cout << "Game over\n";
}

void restart()
{
	clear_board();
	system("cls");
	PLAYER = true;
	play();
}

void move_piece(const string& choose, const string& move)
{
	/*
		reads from stream two strings, determine the coordinates,
		finds object to move, and position where it object will be moved
	*/
	Entity* piece_to_move = read_command(choose);
	int xx, yy;
	Entity* target = read_command(move,xx,yy);

	if (piece_to_move == nullptr)
	{
		system("cls");
		draw();
		cout << "move_piece()::There is no such pieces on the board!\n"
			 << "Please choose the piece accurately\n";
		return;
	}
	
	if (!which_turn(piece_to_move)) return;

	if (piece_to_move->move(xx, yy)) turn();	
}