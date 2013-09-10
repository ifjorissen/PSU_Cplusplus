/*
  Isabella Jorissen
  CS 162 Program 4 
  Karla Fant
  Program Description: Warehouse and stockhouse classes that have functions and a struct for products they contain
 */

  #include <iostream>
  #include <cstring>
  #include <fstream>

  using namespace std;

// simple struct for a product 
struct product {
	char * name;
	int quantity;
	int cost;
	char * vendor;
	int price;
};


class warehouse {
	public:
		warehouse(int starting_cash);  //a warehouse with a specific amount of starting cash
		void take_stock();     // return what's in stock (prints stock)
		void finance();        //return cash

		int is_a_product(char * item_name); /* an int function that acts a little like a bool
												*it returns an inter >1000 where a bool would return false
												* and an integer from 1-item_count if it is true
												* this int returned is then the location in items[]
												*/ 

		void buy_product(product &stock);	  //buy a product from stockhouse using location as the location in items 
		void sell_product();   // sell a product from the warehouse
		void wh_expand(); //will expand the size of the dynamically allocated array
	private:
		int cash; //how much cash is inthe warehouse
		int item_count; //tells us how many items we have (aka length of items);
		int wh_ptr_size; //tell us how many slots the array currently has
		product * wh_stock_ptr;  //pointer to the warehouse's array of products
};

class stockhouse {
	public:
		stockhouse(); //stockhouse constuctor
		void which_product(char *item_name, warehouse &my_warehouse); //match item name with 
		void sh_printproducts(); //prints products in stockhouse
		void sh_stock(warehouse &my_warehouse); //stocks the warehouse with items from stockhouse
		void custom_product(warehouse &my_warehouse); //warehouse adds a custom product to the stockhouse they can then buy it
		void to_productStruct();
		void sh_expand(); //will expand the size of the dynamically allocated array

	private:
		int item_count; //how many items are in the product 
		int sh_ptr_size; //tell us how many slots the array currently has
		product * stockhouse_ptr; //pointer to the stockhouse's array of products

};
