/*
  Isabella Jorissen
  CS 162 Program 4 .cpp
  Karla Fant
  Program Description:
 */

 #include "warehouse_stockhouse.h"


 //intitialize our first warehouse with its startup cash and ititialize struct 

warehouse::warehouse(int starting_cash) {
	cash = starting_cash;
	item_count = 0;
	int wh_ptr_size = 20;
	wh_stock_ptr = new product [wh_ptr_size]; // allocate 20 slots to array, method to expand if needed

	for (int i = 0; i<wh_ptr_size; i++) {
		wh_stock_ptr[i].name = new char [101]; //can also be expanded
		wh_stock_ptr[i].quantity = 0;
		wh_stock_ptr[i].cost = 0;
		wh_stock_ptr[i].vendor = new char [101];  //can also be expanded
		wh_stock_ptr[i].price = 0;
	}
}

void warehouse::wh_expand(){
	wh_ptr_size = wh_ptr_size * 2; //reset new size
	product * temp_ptr = new product [wh_ptr_size];

	//intitialize new array
	for (int i = 0; i<wh_ptr_size; i++) {
		temp_ptr[i].name = new char [101]; //can also be expanded
		temp_ptr[i].quantity = 0;
		temp_ptr[i].cost = 0;
		temp_ptr[i].vendor = new char [101];  //can also be expanded
  		temp_ptr[i].price = 0;
	}

	//transfer the items into the temp array
	for (int i = 0; i<wh_ptr_size; i++){

		strcpy(temp_ptr[i].name, wh_stock_ptr[i].name);
		delete [] wh_stock_ptr[i].name; //deallocate

		temp_ptr[i].quantity = wh_stock_ptr[i].quantity;
		temp_ptr[i].cost = wh_stock_ptr[i].cost;

		strcpy(temp_ptr[i].vendor, wh_stock_ptr[i].vendor);
		delete [] wh_stock_ptr[i].vendor; //deallocate

		temp_ptr[i].price = wh_stock_ptr[i].price;
	}

	//replace temp_ptr with the wh_stock_ptr
	//deallocate old wh_stock_ptr memory

	delete [] wh_stock_ptr;
	wh_stock_ptr = temp_ptr;

	delete [] temp_ptr; //deallocate temp memory
	
}
//a function that allows a warehouse to purchase a product at cost from the stockhouse
 void warehouse::buy_product(product &stock){
 	int num; //holds number of the items to be purchased
 	int cost; //cost equal to  items purchase * cost
 	char response;

 	//Prompt user for purchase
 	cout << "You have $" << cash << ".";
 	cout << "How many of this would you like to purchase?" <<endl;
 	cin >> num; //read in quanitity
 	cin.ignore();		
 	cost = num * stock.cost; //compute total cost and print it
 	cout << "That will be $" << cost << ". Confirm (y/n)";
 	cout << "\n Response: ";

 	//confirm purchase and then add it to the warehouse 
 	if ((cin.get() =='y') && (cash >= cost)){
 		cin.ignore();
 		cash -= cost;

 		//copy over name and vendor info
 		strcpy(wh_stock_ptr[item_count].name, stock.name);
 		strcpy(wh_stock_ptr[item_count].vendor, stock.vendor);

 		//copy over price / quantity info 
 	    wh_stock_ptr[item_count].quantity = num;
 	    wh_stock_ptr[item_count].price = stock.price;
 	    wh_stock_ptr[item_count].cost = stock.cost;
 	    item_count ++; //increase item count of the warehouse 
 	    cout << "Remaining Cash: " << cash << "." << endl;
 	}
 	else if (cash < cost) cout << "Purchase cannot be completed, insufficient funds." <<endl;
 	else cout << "Purchase Canceled"<<endl;
 	cout << "Bringing you back to options menu"<<endl;
 	}
 
//Prints the stock of the warehouse
 void warehouse::take_stock(){
 	//iterate through the warehouse's product[] and print out products and quantity
 	if (item_count == 0) cout << "There is nothing in stock!" <<endl;
 	for (int i = 0; i<item_count; i++){
 		cout << "Product: ";
 		for (int j = 0; (wh_stock_ptr[i].name[j] != '\0'); j++) cout << wh_stock_ptr[i].name[j];
 		cout << "\n Quantity: " << wh_stock_ptr[i].quantity <<endl; 
 	}
 }

//prints out current cash
void warehouse::finance(){
 	cout << "Current cash: " << cash <<endl;
 }

//function determines whether or not a given char[] is a product in stock
//returns the item location if it is
 //returns 1000 if it is not
int warehouse::is_a_product(char * item_name){
 	for (int i = 0; i < item_count; i++){
 			if (strcmp (item_name, wh_stock_ptr[i].name) == 0) return i; //i is item location
 	}
 	return 1000;
 }

//function to sell a product from the warehouse
void warehouse::sell_product(){
 	int to_sell = 0;
 	product selling;
 	int i = 0; //item location
 	char response;

 	//prompt user 
 	cout << "Do you have a product in mind (Enter y/yes)" << endl;
 	cout << "Or do you want to see a list of what's in stock? (Enter p/print)" <<endl;
 	cin >> response;
 	cin.ignore();

 	if (response == 'y') {
 		//prompt user for product
 		cout << "Enter product name: ";
 		selling.name = new char [101];
 		cin >> selling.name;
 		cin.ignore();
 		cout<< "Product: " << selling.name <<endl;
 		i = is_a_product(selling.name); //set item location
 		//check to see if the item exists in stock
 		if ( i > item_count) cout << "That product doesn't exist."<<endl;
 		else {
 			cout << "You have " << wh_stock_ptr[i].quantity << " in stock."<<endl;
 			cout << "How many do you want to sell?"<< endl;
 			cin >> to_sell;
 			cin.ignore();
 			//check to see if there is enough in stock
 			if (to_sell < wh_stock_ptr[i].quantity) {
 				cout << "Selling!" <<endl;
 				//change item info and cash to reflect sale
 				cash += to_sell * wh_stock_ptr[i].price;
 				wh_stock_ptr[i].quantity -= to_sell;
 			}
 			else cout<< "You don't have that much in stock!" <<endl;
 		}
 	}
 	else if (response == 'p') take_stock();
 }


/*
*  STOCKHOUSE STOCKHOUSE STOCKHOUSE STOCKHOUSE STOCKHOUSE STOCKHOUSE
*  STOCKHOUSE STOCKHOUSE STOCKHOUSE STOCKHOUSE STOCKHOUSE STOCKHOUSE
*     These are all the functions associated with the stockhouse
*  STOCKHOUSE STOCKHOUSE STOCKHOUSE STOCKHOUSE STOCKHOUSE STOCKHOUSE
*  STOCKHOUSE STOCKHOUSE STOCKHOUSE STOCKHOUSE STOCKHOUSE STOCKHOUSE
*/

stockhouse::stockhouse(){
	item_count = 0;
	sh_ptr_size = 25;
	stockhouse_ptr = new product [sh_ptr_size]; //set stockhouse size to 20, method avail to expand 
	for (int i = 0; i<sh_ptr_size; i++) {
		stockhouse_ptr[i].name = new char [101]; 
		stockhouse_ptr[i].quantity = 0;
		stockhouse_ptr[i].cost = 0;
		stockhouse_ptr[i].vendor = new char [101]; 
		stockhouse_ptr[i].price = 0;
	}
}

void stockhouse::sh_expand(){
	sh_ptr_size = sh_ptr_size * 2; //reset new size
	product * temp_ptr = new product [sh_ptr_size];

	//intialize new temp array
	for (int i = 0; i<sh_ptr_size; i++) {
		temp_ptr[i].name = new char [101]; //can also be expanded
		temp_ptr[i].quantity = 0;
		temp_ptr[i].cost = 0;
		temp_ptr[i].vendor = new char [101];  //can also be expanded
		temp_ptr[i].price = 0;
	}

	//transfer the items into the temp array
	for (int i = 0; i<sh_ptr_size; i++){

		strcpy(temp_ptr[i].name, stockhouse_ptr[i].name);
		delete [] stockhouse_ptr[i].name; //deallocate

		temp_ptr[i].quantity = stockhouse_ptr[i].quantity;
		temp_ptr[i].cost = stockhouse_ptr[i].cost;

		strcpy(temp_ptr[i].name, stockhouse_ptr[i].vendor);
		delete [] stockhouse_ptr[i].vendor; //deallocate

		temp_ptr[i].price = stockhouse_ptr[i].price;
	}

	//deallocate old stockhouse memory
	delete [] stockhouse_ptr;

	//replace temp_ptr with the stockhouse_ptr
	stockhouse_ptr = temp_ptr;
	delete [] temp_ptr; //deallocate memory
}

 //this function allows the user to create a custom product
//writes it to the product file
// the user can then purchase it for their warehouse if they like
void stockhouse::custom_product(warehouse &my_warehouse){
	ofstream file_out;
	//open file for output: append mode.
	file_out.open("products.txt", ios::app);

	//prompt user for product name
	cout << "Create a custom product!" << "\n Enter product name: ";
	cin >> stockhouse_ptr[item_count].name;  //read in item name to stockhouse
	cin.ignore();

	//write product name to file
	for (int i = 0; (stockhouse_ptr[item_count].name[i]) != '\0'; i++) {
		file_out << '\n' << stockhouse_ptr[item_count].name[i];
	}
	//put item quantity in stockhouse
	stockhouse_ptr[item_count].quantity = 10000;
	file_out << " 10000 "; //write quantity to file

	cout <<"\n Cost: ";  //prompt for cost
	//read into stockhouse item cost
	cin >> stockhouse_ptr[item_count].cost;
	cin.ignore();

	//write cost to products.txt
	file_out << stockhouse_ptr[item_count].cost << " ";

	//prompt for vendor
	cout << "\n Vendor name: ";
	cin >> stockhouse_ptr[item_count].vendor;
	cin.ignore();
	//write vendor name to file
	for (int j = 0; (stockhouse_ptr[item_count].vendor[j]) != '\0'; j++) {
		file_out << stockhouse_ptr[item_count].vendor[j];
	}

	//prompt for price
	cout << "\n Price: ";
	cin >> stockhouse_ptr[item_count].price;
	cin.ignore();
	//write price to file
	file_out << " " << stockhouse_ptr[item_count].price;
}

//a void function that matches a requested product from the warehouse and checks to see
// if it exists in the stockhouse.  If it does, it prompts the user to buy it.
// if it does not exist, it prompts the user to enter the porduct on their own if they choose.
void stockhouse::which_product(char * item, warehouse &my_warehouse){
	cout << "Matching your Product ..." <<endl;
	for (int i = 0; i <item_count; i++) {
		cout << "comparing: " << item << " " << stockhouse_ptr[i].name <<endl;
		if (strcmp (item, stockhouse_ptr[i].name) == 0){
			cout << "We found a match! ";

			//ask user if they want to buy the product
			cout << "\n Are you sure you want to buy it? (y/n)"<< endl;
			if (cin.get() == 'y') {
				cin.ignore();
				//call helper function from warehouse.cpp
				my_warehouse.buy_product(stockhouse_ptr[i]);
				i = item_count;
			}
			else cout << "Back to the options!"<<endl;
		}
		//check next product in stockhouse if its not empty yet and there wasn't a match
		else if (i == item_count){
			cout << "I'm sorry we don't carry that product, ";
			cout << "would you like to enter it yourself? (y/n)"<< endl;
			if (cin.get() == 'y') {
				cin.ignore();
				custom_product(my_warehouse);
			}
			else cout << "Back to the options!" <<endl;
		}
	}
}

//a void function that  prints everything in the stockhouse
void stockhouse::sh_printproducts(){
	for (int i = 0; i<item_count; i++){
		cout << "\nProduct: ";
		for (int l = 0; (stockhouse_ptr[i].name[l]!= '\0'); l++) cout << stockhouse_ptr[i].name[l];
		cout << "\n Quantity: " << stockhouse_ptr[i].quantity <<endl;
		cout << "Cost: " << stockhouse_ptr[i].cost <<endl;
		cout << "Vendor: ";
		for (int k = 0; (stockhouse_ptr[i].vendor[k]!= '\0'); k++) cout << stockhouse_ptr[i].vendor[k];
		cout << "\nPrice: " << stockhouse_ptr[i].price <<endl;
	}
}

//a function that allows the user to stock thier warehosue with items from the 
//stockhouse.  calls helper functions such as printproducts and which_product
void stockhouse::sh_stock(warehouse &my_warehouse) {
	sh_printproducts(); //print what's in the stockhouse (avail products)
	char * response = new char [101];

	//Ask user if they want to buy a product from the stockhouse
	cout << "Would you like to stock your warehouse with any of these products? (y/n)"<< endl;
	if (cin.get() == 'y') {
		cin.ignore();

		//since they want to buy a product, ask which one
		cout<<"Enter the name of the first product you would like to buy: ";
		cin >> response;
		cin.ignore();

		//see if there is a product that matches that 
		which_product(response, my_warehouse);
	}
	else cout<<"\n Back to the options"<<endl;
} 

 void stockhouse::to_productStruct(){
 	ifstream file_in;
	file_in.open("products.txt");
	int i = 0;
	//push file into product structures 
	while (!file_in.eof()) {

		//read in name
		file_in >> stockhouse_ptr[i].name;
		file_in.ignore();

				//read in quantity
		file_in >> stockhouse_ptr[i].quantity;
		file_in.ignore();

		//read in cost
		file_in >> stockhouse_ptr[i].cost;
		file_in.ignore();

		//read in vendor
		file_in >> stockhouse_ptr[i].vendor;
		file_in.ignore();

		//read in price
		file_in >> stockhouse_ptr[i].price;	
			
		file_in.ignore();

	    //if we are getting close to the size of the array
	    if (i + 1 == sh_ptr_size) sh_expand();
	    i++;
	}

	item_count = i+1; //number of items in stockhouse
	file_in.close(); 
}





