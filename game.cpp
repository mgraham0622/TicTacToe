/*
This game uses a 2d array to allow 2 players to play tic-tac-toe in the command line, 
they input their moves as a 2 character letter-number sequence, and if it is valid, 
the program translates that into a mark on the board and checks if the given player
has won. The program keeps track of how many wins, losses, and ties each player has.

created by: Matthew Graham

Last worked on: 9/22/26
*/
// import libraries/headers
# include <iostream>
# include <cctype>
# include <cstring>
using namespace std;

// function to print out the current board
void printGrid(char board[3][3]) {
	// text for row and column and spacers
	char top[8] = "X A B C";
	char row1 = '1';
	char row2 = '2';
	char row3 = '3';
	char spacer = ' ';
	cout << top << endl;
	// goes through row by row and prints it out
	for (int i = 0; i <= 2; i++) {
		// prints a different row header depending on what row the loop is at
		switch(i) {
		case 0:
			cout << row1;
			break;
		case 1:
			cout << row2;
			break;
		case 2:
			cout << row3;
			break;
		}
		// prints out a row with spacers in between
		for (int k = 0; k <= 2; k++) {
			cout << spacer << board[i][k];
		}
		// prints a return so the next row can be printed
		cout << endl;
	}
}
// function to check if the given player has win
bool checkWin (char board[3][3], char player) {
	// records how many are in a specific row, column, or diagonal
	int inrow = 0;
	int incol = 0;
	int pdiag = 0;
	int ndiag = 0;
	// goes through each row/column
	for (int i = 0; i<3; i++) {
		// resets totals for each row/column
		inrow = 0;
		incol = 0;
		// checks if the diagonal fron top left to bottom right is filled as the loop runs
		if (board[i][i] == player) {
			pdiag += 1;
			if (pdiag == 3) {
				return true;
			}
		}
		// checks if the diagonal from top right to bottom left is filled as the loop runs
		if (board[i][2-i] == player) {
			ndiag += 1;
			if (ndiag == 3) {
				return true;
			}
		}
		// goes through each square in the column/row
		for (int k = 0; k<3; k++) {
			// checks if the row has 3 in a row
			if (board[i][k] == player) {
				inrow += 1;
				if (inrow == 3) {
					return true;
				}
			}
			// checks if the column has 3 in a row
			if (board[k][i] == player) {
				incol += 1;
				if (incol == 3) {
					return true;
				}
			}
		}
	}
	// if there are no winning sequences returns false
	return false;
}
// function to strip a string of whitespace and make it lowercase (copied and modified from my Palindrome repo)
int strip(char (& input)[81]) {
	// sets up variables used within the function
	char temp[11] = "";
	int length;
	char ch1;
	unsigned char ch2;

	// gets string length
	length = strlen(input);

	// goes through each character of the string, strips it, and adds it to the temp string
	for (int i = 0; i < length; i++) {
		// gets individual character
		ch1 = input[i];
		// makes it lowercase if it is a letter or number
		if (isalnum(ch1)) {
			// makes it lowercase
			ch1 = tolower(ch1);
			// adds character to the temp string
			strncat(temp,&ch1,1);
		}
	}
	// assigns the temp string to the original variable that was input
	// works because a reference to the main function variable was read in
	strcpy(input,temp);
	return 0;
}
// gets the player input, validates/verifies it, and makes the move
void getInput(int (& move)[2], char (& board)[3][3],char player) {
	// sets up variables, input buffers, and dialogue
	unsigned char single;
	char buffer[81] = "";
	int length;
	bool hasMove = false;
	char noMove[3] = "zz";
	char dialogue1[56] = "Enter your move (letter and number, no spaces. Ex: a1):";
	char dialogue2[58] = "Please enter a valid move (1 letter a-c and 1 number 1-3)";
	char dialogue3[18] = "Move is Not valid" ;
	// gets the move from the player
	while (hasMove == false) {
		move[0] = -1;
		move[1] = -1;
		// asks for a move and gets the input
		cout << dialogue1;
		cin.getline(buffer,80);
		// checks if the move is at least 2 characters
		strip(buffer);
		if (strlen(buffer) < 2) {
			strncat(buffer,noMove,2);
		}
		// checks if the move is the right letters
		for (int i = 0; i <= 1; i++) {
			single = buffer[i];
			switch(single) {
			case '1':
				move[0] = 0;
				break;
			case '2':
				move[0] = 1;
				break;
			case '3':
				move[0] = 2;
				break;
			case 'a':
				move[1] = 0;
				break;
			case 'b':
				move[1] = 1;
				break;
			case 'c':
				move[1] = 2;
				break;
			}
		}
		// if move is not valid, asks for inout again
		if (move[0] == -1 or move[1] == -1) {
			cout << dialogue2 << endl;
		// if move is valid, checks if it is legal
		} else {
			// makes move if it is valid and legal
			if (board[move[0]][move[1]] == '_') {
				board[move[0]][move[1]] = player;
				hasMove = true;
			// if move is not legal, asks for a legal move
			} else {
				cout << dialogue3 << endl;
			}
		}
	}
}

// main game function
int main() {
	// sets up board, dialogue, and variables
	char board[3][3] = {
		{'_','_','_'},
		{'_','_','_'},
		{'_','_','_'}
	};
	char dialogue1[17] = "Current Player: ";
	char dialogue2[8] = "player ";
	char dialogue3[25] = " wins! Play again?(y/n):";
	char dialogue4[21] = "enter a valid input:";
	char dialogue5[28] = "Tie Game! Play again?(y/n):";
	char dialogue6[16] = "Player 1 Wins: ";
	char dialogue7[16] = "Player 2 Wins: ";
	char dialogue8[7] = "Ties: ";
	char player = '_';
	char input = ' ';
	int move[2] = {-1,-1};
	int playerNum = 0;
	int turns  = 0;
	int p1Wins = 0;
	int p2Wins = 0;
	int ties = 0;
	bool won = false;
	bool tie = false;
	bool hasInput = false;
	bool playing = true;

	// keeps running games over and over again
	while (playing) {
		// loops turns until a game is won or tied
		while (!won) {
			// increments turn counter
			turns++;
			// switches player or sets starting player
			if (player == 'O') {
				player = 'X';
				playerNum = 1;
			} else if (player == 'X') {
				player = 'O';
				playerNum = 2;
			} else {
				player = 'X';
				playerNum = 1;
			}
			// prints current player and board
			cout << dialogue1 << player << endl;
			printGrid(board);
			// gets player input
			getInput(move,board,player);
			// checks for a win
			won = checkWin(board,player);
			// checks for a tie. increments tie counter, flags it, and ends loop if there is one.
			if (turns == 9 and !won) {
				tie = true;
				ties++;
				won = true;
			}
		}
		// checks if the last game was a win or tie and outputs appropriate dialogue
		if (tie) {
			cout << dialogue5;
			tie = false;
		} else {
			cout << dialogue2 << playerNum << dialogue3;
			// increments win counter for winning player
			if (playerNum == 1) {
				p1Wins++;
			}
			if (playerNum == 2) {
				p2Wins++;
			}
		}
		// asks if the player wants to play again
		hasInput = false;
		while (!hasInput) {
			cin >> input;
			cin.ignore(99999,'\n');
			if (tolower(input) == 'y') {
				// resets game states if playing again
				hasInput = true;
				for (int i = 0; i <= 2; i++) {
					for (int k = 0; k <= 2; k++) {
						board[i][k] = '_';
					}
				}
				turns = 0;
				player = '_';
				won = false;
				// ends game if not playing again
			} else if (tolower(input) == 'n') {
				hasInput = true;
				playing = false;
				// asks for input again if input is invalid
			} else {
				cout << dialogue4;
			}
		}
		// prints the wins for each player and the number of ties
		cout << dialogue6 << p1Wins << endl;
		cout << dialogue7 << p2Wins << endl;
		cout << dialogue8 << ties << endl;
	}
}
