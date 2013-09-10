/*
Isabella Jorissen
Karla Fant
CS 162
Programming Assignment 2: Word Game

Program Description: A word guessing game with alternating players
Program Algorithm: See attached.
*/

#include <iostream> //include I/O library
#include <cstring>

using namespace std;

//print out the hint for player 
void hint_word (char word [21]) {
	cout<<"Your hint: ";
	for (int i = 0; i < 21; i++) {
		if ((word[i] != 'a') &&  (word[i] != 'e') && (word[i] != 'i') && (word[i] != 'o') && (word[i] != 'u')) {
			cout<< word[i]; 
		}
		else cout << " ";
	}
	cout << endl;
}

// a function to deal with players guessed / keep score within the round
void guess (bool &turn, int & score1, int & score2, char p_word [21]) {
	int j = 0;
	//int s_p1 = score1;
	//int s_p2 = score2;
	char p_guess [21];

	do {
		cout << "Player! Enter your guess!" <<endl;
		cin >> p_guess;
		cin.ignore();

		if (strcmp(p_guess, p_word) == 0) {
			cout<< "You were right!" <<endl;
			if (turn) score2++;
			else score1++;
		}
		else {
			cout << "Guess again!" <<endl;
			j++;
		}
	} while (strcmp(p_guess, p_word) != 0 && j<3);

	if (turn) {
		if (strcmp(p_guess, p_word) != 0) {
			score1++;
			cout << "You lose, Player 2! Score: " << score2 << endl;
			cout << "Player 1, You win this round! Score: " <<score1<<endl;
		}
		else {
			cout << "You lose, Player 1! Score: " << score1 << endl;
			cout << "Player 2, You win this round! Score: " <<score2 <<endl;
		}
	}
	else {
		if (strcmp(p_guess, p_word) != 0) {
			score2++;
			cout << "You lose, Player 1! Score: " << score1 << endl;
			cout << "Player 2, You win this round! Score: " <<score2<<endl;
		}
		else {
			cout << "You lose, Player 2! Score: " << score2 << endl;
			cout << "Player 1, You win this round! Score: " <<score1 <<endl;
		}
	}
}

//play a round of the game!
void play(bool &turn, int & score1, int & score2){
	//int sc_p1 = score1;
	//int sc_p2 = score2;
	char p_word [21]; 
	char p_guess [21];

	if (turn){
		cout << "Enter your word, Player One! (Less than or Equal to 20 characters)" <<endl;
		cout << "Your score: " << score1 <<endl;
	}
	else {
		cout << "Enter your word, Player Two! (Less than or Equal to 20 characters)" <<endl;
		cout << "Your score: " << score2 << endl;
    }
	cin >> p_word;
	cin.ignore();

	for (int i = 0; i <=100; i++) cout << '\n';
	//print the hint word
	hint_word(p_word);
	
	//start guessing
	guess(turn, score1, score2, p_word);

	//end this round
	cout << "Ready for another round?" <<endl;

	//clear arrays for next round
	for (int i = 0; i <21; i++){
		p_word[i] = ' ';
		p_guess[i] = ' ';
	}
}


int main() {
	//declare a 20 character array to hold player 1's word
	int score_p1 = 0; //initialize score
	int score_p2 = 0;

	bool whose_turn = true; //true if it is player1 entering word false if player 2

	//play a game, which is 5 rounds
	do {
	play(whose_turn, score_p1, score_p2); //play a round
	whose_turn = !whose_turn; //switch turns
	} while (score_p1 < 5 && score_p2 < 5);

	//print ending stats
	cout << "Game over!" << endl;
	cout<< "Player 1 score: " << score_p1 <<endl;
	cout<< "Player 2 score: " <<score_p2 <<endl;

}
