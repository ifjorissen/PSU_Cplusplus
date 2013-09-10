/* 
Isabella Jorissen
Karla Fant
CS 162
Programming Assignment 1: Make 15

Program Description: This game alternates between taking a user input from 1-9 and a computer input (also of range 1-9).  
					 it then sums the user and computer inputs separately and continues accepting unique inputs until either
					 the computer or the user's sum reaches 15.  When that happens, the player with the sum to 15 wins.  
					 For a descripton of the algorithm involved  see below.  This program uses two helper functions, one to 
					 print the winner's numbers, and another to check to see if a player has won (print_winner and winner_loser,
					 respectively)
*/

/*
PROGRAM ALGORITHM:
Whenever we read in a player choice, be it the user or the computer, we have to check to see if the number
that they have chosen has already been used.  To do this, we have created a reference array that holds every number 
that has been chosen by both players.  When a player chooses, we take that choice and check to see if it matches 
ANY of the numbers that are already in the reference array. If so, then we prompt the player to enter another choice or 
to seed another random number.
HOWEVER, we can't just keep iterating through the array from where we left off, because this is a new number.  We have 
to check the whole reference array all over again to make sure that the new numebr isn't already in the array.  Once
we have verified that the number is unique we can store it in the players individual array and add it to the respective sum.
Then, we check to see if anyone made 15.
*/

#include <iostream>  //include the I/O library

using namespace std;

//checks to see if there is a winner or a loser after each turn
void print_winner(int arr [], int g)
{
	cout<< "The winning numbers: ";
	for (int i = 0; i < g; i++) 
	{
		cout<< arr[i] << " ";
	}
}

bool winner_loser(int x, int y, int arr_x [], int arr_y [], int g)
{

	if(y > 15)   //if the sum is 15- They win!  if the computer went over, they win!
	{
		cout << "You win, because the Computer went over."<<endl;
		print_winner(arr_x, g);
		return true;
	}

	else if (x > 15)  //check to see if the computer won or if the user went over, if so, end the game
	{
		cout<<"You lose, because you went over" <<endl;
		print_winner(arr_y, g);
		return true;
	}


	else if (y == 15)  // check to see if the computer or the user won by making 15 (not by default where the other player goes over)
	{
		cout<<"We had a winner today! It wasn't you!"<< endl; //indicates that either the user or the computer reached 15
		print_winner(arr_y, g);
		return true;
	}

	else if (x == 15)
	{
		cout<< "You've won!  Congrats!";
		print_winner(arr_x, g);
		return true;
	}

	else 
	{
		return false;
	}

}

int main() {

	char response = 'n';  //set user's default response to "Play again" to no

	//Welcome the user and explain the game

	cout << "Hello and Welcome to Make 15!"<<endl;
	cout << "Pick a number from 1-9 inclusive.  You are competing against the \n"
	     << "Computer and the player that reaches 15 first wins!" <<endl;

	do {     

		int nums [10]; //an integer array of size 10 that will hold the computer and user choices in the order that they choose them
		int user[6]; //an integer [] to hold the user's numbers
		int comp[6]; // an integer [] to hold the computer's numbers
		int Usum = 0; // an integer that holds the sum of the user's  choices
		int Csum = 0; // an integer that holds the sum of the computer's choices
		//int i, j, k, l;  //integers for the for loops

		for (int i = 0; i<10; i+=2) //outer for loop that will allow each player 5 guesses at most totaling to 10 guesses max 
		{
			//Tell the player what numbers have been chosen:

			cout<<"These numbers have already been used: "; 
			for (int l = 0; l<(i); l++) 
			{
				cout << nums[l] << " ";
			}

			cout << "\n Choose one: 1 	2	3	4	5	6	7	8	9" << endl; //prompt user to choose a number
			cin >> user[i/2]; //read in the number
			cin.ignore();

			for (int k = 0; k<i; k++) //this for loop checks to make sure the number is unique
			{
				if (user[i/2] == nums[k])  // if the number has been used, the user must pick another
				{
					cout<< "You have to pick all different numbers! " <<endl;
					cout<< "Enter a different number: ";
					cin>>user[i/2]; //read in the user's new number
					cin.ignore();
					k=0;  //make k=0 since we have to iterate through all the numbers in nums[] to make sure it is unique 
				}
			}

			Usum += user[i/2];  //now we know this is a unique number; add it to the user's total
			nums[i] = user[i/2]; // store the user's number in the nums array (the nums array acts as a reference)

			cout<<"Current Sum: " << Usum << endl;  //tell the user what their sum is

			srand(time(NULL));  //create a random seed
			comp[i/2] = rand()%10;
	
			for (int j = 0; j<=i; j++) //same deal as with the user- we are checking that the computer's guess is unique
			{
				if (comp[i/2] == nums[j] || comp[i/2] == 0)
				{
					comp[i/2] = rand()%10;  //if it is zero or not unique, generate a new number
					j=0; //we have to check the WHOLE array again since this is a new number
				}
			}

			Csum += comp[i/2]; //we know this is a unique number, so we add it to the total
			nums[i+1] = comp[i/2]; //add the computer's number to the reference array, nums

			cout<< "The computer chose: "<< comp[i/2] <<endl;  //let the user know what the computer did
			cout<< "The computer's sum " << Csum <<endl;

			// Now we check again to see if anyone has won! 
			if (winner_loser(Usum, Csum, user, comp, i)) 
			{
				i = 10; // this throws us out of the loop
			}
		}
		cout << "Play again? (y/n)" << endl; //ask the user if they want to play again
		cin >> response; // read in the response
		cin.ignore();
	} while ('y'== response);
	return 0;
}

