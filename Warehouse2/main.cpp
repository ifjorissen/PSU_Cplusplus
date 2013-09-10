/* 
  Isabella Jorissen
  Karla Fant
  CS 162
  Programming Assignment 4
  Program Description:
 */

  #include "warehouse_stockhouse.h"
  const int START = 10000; //10,000 dollar cash start

//prototype functions
void welcome(stockhouse &my_stockhouse);
void options(warehouse &my_warehouse, stockhouse &my_stockhouse); //prints actions


int main () {
  char response;
  stockhouse my_stockhouse;		// initialize a stockhouse
  warehouse my_warehouse(START); //initialize a warehouse with 10,000 in cash
  welcome(my_stockhouse);  // welcome user

  //do-while loop that operates the managing system
  do {
  	response = ' '; //reset response to avoid infinite loop
  	options(my_warehouse, my_stockhouse); //prints options
  	//check to see if user wants to continue doing things or not
  	cout<< "Would you like to see the options? (y/n)"<<endl;
  	cout<< "Response: ";
  	response = cin.get();
  	cin.ignore();
	} while (response == 'y');
}


//a function to welcome the user and set up the stockhouse[]
 void welcome(stockhouse &my_stockhouse){
 	cout <<"\t ~~~Welcome to your warehouse manager!~~~" <<endl;
 	cout <<"\t ~~~You can manage all of your Warehouse inventory needs via our stockhouse!~~~" <<endl;
 	cout <<"\t ~~~Think of the stockhouse as an endless inventory of 20 or so ready to go products available for purchase.~~~" <<endl;
 	cout <<"\t ~~~You can also add your own custom products to your inventory by first registering them with us!~~~"<<endl;
 	my_stockhouse.to_productStruct();

 }

 //options function displays the user's options and then calls the relevant method
 void options(warehouse &my_warehouse, stockhouse &my_stockhouse){
 	int response = 0;
 	//display options
 	cout <<"Okay, what would you like the do?" <<endl;
 	cout << "You can do any of these things: (Respond with 1-4)" <<endl;
 	cout << "1. Stock Your Warehouse"<<endl;
 	cout << "2. Sell Items from your Warehouse" <<endl;
 	cout << "3. View Your Warehouse's Current Inventory and Finances" <<endl;
 	cout << "4. Enter a Custom Product into your inventory" <<endl;
 	cout << "A response other than 1-4 will terminate your session." <<endl;
 	cout << "Response: ";

//read in response
 	cin >> response;
 	cin.ignore();

 //a switch case to deal with the user's response
 	switch (response) {
 		case 1:
 			cout << "Let's Stock Your Warehouse!"<<endl;
 			my_stockhouse.sh_stock(my_warehouse);
 			break;
 		case 2:
 			cout<< "Sell an Item from your inventory"<<endl;
 			my_warehouse.sell_product();	
 			break;
 	    case 3:
 	    	cout << "View Current Inventory and Finances" <<endl;
 	    	my_warehouse.take_stock();
 	    	my_warehouse.finance();
 	    	break;
 	    case 4: 
 	    	cout << "Add a custom product!" <<endl;
 	    	my_stockhouse.custom_product(my_warehouse);
 	    	break;
 	    default: 
 	    	cout <<"Goodbye."<<endl;
 	}
 }