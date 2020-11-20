#pragma once
#include "Pieces.h"

//names of general command

const string start = "start";
const string moving = "move";
const string reset = "restart";
const string save = "save";
const string load = "load";
const string quit = "quit";
const string helpp = "help";
const string show_board = "show";
const string ssp = "sps";

extern bool PLAYER; // indicator which player turn
extern bool GAME; // indicator did the game start?
extern bool QUIT; // indicator did the quit typed?

int read_letter(char command);
Entity* read_command(const string& command);
Entity* read_command(const string& command, int& xx, int& yy);

bool get_cordinate(string& firstc, string& secondc);
void get_command(bool trig);

void move_piece(const string& choose, const string& move);

void help();
void turn();
void game();
void play();
void restart();
bool which_turn(Entity*);
void possible_step();

//----------------------------//

const string greeting = "Welcome to chess\n\n";
const string first_info = "For interacting with programm, you have few functions:\n\n"
"1. Start : it is used when you want to begin play\n\tTo use this function just type \"start\"\n\n"
"2. Restart : it is used when you are already playing, and want to begin new game\n"
"\tTo use this function just type \"restart\"\n\n"
"3. Move : it is used to manage pieces on board\n\t"
"To use this function type move and coordinates of position\n\tfrom where you want move, and destination position\n\t"
"for example: \"move d2,d3\" - move the piece which is at d2, to the d3.\n"
"\tit is not necessary to use a comma as a separator,\n\tyou can simply write the coordinates separately\n"
"\tfor example: \"move d2 d3\" - move the piece which is at d2, to the d3.\n\n"
"4. Help : it us used to inform player about how to interact with game\n\t"
"To use this function just type \"help\"\n\n"
"5. Show : shows the board if game has already started\n\t"
"To use this function just type \"show\"\n\n"
"6. Show Posible Steps : shows the steps that piece can make\n\t"
"To use this function just type \"sps\" and the coordinates of piece\n"
"\t for exp: \"sps d2\"\n\n"
"7. Quit : it us used to quit from game\n\t"
"To use this function just type \"quit\"\n\n";
const string  reg = "Choose the piece for a move, and set coordinates.(exp: move a2 a3)\n"
"If you want to see the all possible moves for concrete piece type: \"sps xy\"(x and y is coordinates of piece)\n";