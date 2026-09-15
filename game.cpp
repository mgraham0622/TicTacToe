# include <iostream>
# include <cctype>
# include <cstring>

using namespace std;

void printGrid(char board[3][3]){
}
bool checkWin (char board[3][3]){
  return false;
}
// function to strip a string of whitespace and make it lowercase (copied from Palindrome)
int strip(char (& input)[81]){
  // sets up variables used within the function
  char temp[11] = "";
  int length;
  char ch1;
  unsigned char ch2;

  // gets string length
  length = strlen(input);

  // goes through each character of the string, strips it, and adds it to the temp string
  for (int i = 0; i < length; i++){
    // gets individual character
    ch1 = input[i];
    // changes it to an ascII value for operations
    ch2 = static_cast<unsigned char>(ch1);
    // makes it lowercase if it is a letter or number
    if (isalnum(ch2)){
	// makes it lowercase
	ch2 = tolower(ch2);
	// transforms it back into a character
	ch1 = static_cast<char>(ch2);
	// adds character to the temp string
	strncat(temp,&ch1,1);
      }
  }
  // assigns the temp string to the original variable that was input
  // works because a refrence to the main function variable was read in
  strcpy(input,temp);
  return 0;
}
void getInput(int (& move)[2]){
  unsigned char single;
  char buffer[81] = "";
  int length;
  bool hasMove = false;
  move[0] = 0;
  move[1] = 1;
  while (hasMove == false){
    cout << "Enter your move (letter and number, no spaces. Ex: a1):";
    cin.get(buffer,11);
    cin.ignore(9999999,'\n');
    strip(buffer);
    
    for (int i = 0; i <= 1; i++){
      single = buffer[i];
      switch(single){
      case '1':
	move[1] = 1;
	break;
      case '2':
	move[1] = 2;
	break;
      case '3':
	move[1] = 3;
	break;
      case 'a':
	move[0] = 1;
	break;
      case 'b':
	move[0] = 2;
	break;
      case 'c':
	move[0] = 3;
	break;
      default:
	cout << "Enter a valid move (1 letter a-c and 1 number 1-3)" << endl;
      }
    }
    if (move[0] == 0 or move[1] == 0){
      cout << "Please enter a letter and a number as your move" << endl;
    }else{
      hasMove = true;
    }
  }
}
    
    

bool checkInput(char move[3], char board[3][3]){
  return false;
}

int main(){
  char board[3][3] = {
    {' ',' ',' '},
    {' ',' ',' '},
    {' ',' ',' '}
  };
  int move[2] = {0,0};
  
  cout << move[0] << move[1] << endl;
  getInput(move);
  cout << move[0] << move[1] << endl;
    
}
