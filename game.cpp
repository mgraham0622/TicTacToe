# include <iostream>
# include <cctype>
# include <cstring>

using namespace std;

void printGrid(char board[3][3]) {
	char top[8] = "X A B C";
	char row1 = '1';
	char row2 = '2';
	char row3 = '3';
	char spacer = ' ';
	cout << top << endl;
	for (int i = 0; i <= 2; i++) {
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
		for (int k = 0; k <= 2; k++) {
			cout << spacer << board[i][k];
		}
		cout << endl;
	}
}
bool checkWin (char board[3][3], char player) {
	int inrow = 0;
	int incol = 0;
	int pdiag = 0;
	int ndiag = 0;
	for (int i = 0; i<3; i++) {
		inrow = 0;
		incol = 0;
		if (board[i][i] == player) {
			pdiag += 1;
			if (pdiag == 3) {
				return true;
			}
		}
		if (board[i][2-i] == player) {
			ndiag += 1;
			if (ndiag == 3) {
				return true;
			}
		}
		for (int k = 0; k<3; k++) {
			if (board[i][k] == player) {
				inrow += 1;
				if (inrow == 3) {
					return true;
				}
			}
			if (board[k][i] == player) {
				incol += 1;
				if (incol == 3) {
					return true;
				}
			}
		}
	}
	return false;
}
// function to strip a string of whitespace and make it lowercase (copied from Palindrome)
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
	// works because a refrence to the main function variable was read in
	strcpy(input,temp);
	return 0;
}
void getInput(int (& move)[2], char (& board)[3][3],char player) {
	unsigned char single;
	char buffer[81] = "";
	int length;
	bool hasMove = false;
	char noMove[3] = "zz";

	while (hasMove == false) {
		move[0] = -1;
		move[1] = -1;
		cout << "Enter your move (letter and number, no spaces. Ex: a1):";
		cin.getline(buffer,80);
		strip(buffer);
		if (strlen(buffer) < 2) {
			strncat(buffer,noMove,2);
		}
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
		if (move[0] == -1 or move[1] == -1) {
			cout << "Please enter a valid move (1 letter a-c and 1 number 1-3)" << endl;
		} else {
			if (board[move[0]][move[1]] == '_') {
				board[move[0]][move[1]] = player;
				hasMove = true;
			} else {
				cout << "Move is Not valid" << endl;
			}
		}
	}
}

int main() {
	char board[3][3] = {
		{'_','_','_'},
		{'_','_','_'},
		{'_','_','_'}
	};
	char player = '_';
	char input = ' ';
	int move[2] = {-1,-1};
	int playerNum = 0;
	bool won = false;
	bool hasInput = false;
	bool playing = true;

	while (playing) {
		while (!won) {
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
			cout << "Current Player: " << player << endl;
			printGrid(board);
			getInput(move,board,player);
			won = checkWin(board,player);
		}
		cout << "player " << playerNum << " wins! Play again?(y/n):";
		hasInput = false;
		while (!hasInput) {
			cin >> input;
			cin.ignore(99999,'\n');
			if (tolower(input) == 'y') {
				hasInput = true;
				for (int i = 0; i <= 2; i++) {
					for (int k = 0; k <= 2; k++) {
						board[i][k] = '_';
					}
				}
				player = '_';
				won = false;
			} else if (tolower(input) == 'n') {
				hasInput = true;
				playing = false;
			} else {
				cout << "enter a valid input:";
			}
		}
	}
}
