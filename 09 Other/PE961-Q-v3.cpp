//Amir Tajik
//PE961 - version 2 - Oct. 2017
//Khatam University - Performance Evaluation

//======================================================================
//----------------------------- Libraries ------------------------------
//======================================================================
#include <stdlib.h>
#include <vector>
#include <random>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <thread>
//#include <unistd.h>
//#include <cstdlib>
//#include <deque>

using namespace std;
//======================================================================
//----------------------------- Global Variables -----------------------
//======================================================================
vector<int> allCustomers;
vector<int> customersQ;
int blockCounter = 0;
int departCounter = 0;
ostream_iterator< int > output( cout, " " );

//======================================================================
//----------------------------- Constants ------------------------------
//======================================================================
#define LAMBDA 1
#define THETA 6
#define MAX_CUSTOMERS 20
#define QUEUE_SIZE 5 //no semicolons after constant variables
#define TAB "\t"
//======================================================================
//----------------------------- Classes --------------------------------
//======================================================================
class Store {
		public:
			void createPopulation();
			void addToQueue();
};

class Cashier {
		public:
			void checkQueue();
};
//======================================================================
//----------------------------- Implementation -------------------------
//======================================================================
int main(){
	Store store1;
	store1.createPopulation();
	store1.addToQueue();
	
	cout<<"Block Counter: "<<blockCounter;
	
	Cashier cashier1;
	cashier1.checkQueue();
	
	thread thread2(&Cashier::checkQueue,&cashier1);
	thread thread1(&Store::addToQueue,&store1);
	
	thread2.join();
	thread1.join();
	
};
//======================================================================
//----------------------------- Functions ------------------------------
//======================================================================



void Store::createPopulation(){
		cout<<"Population being created..."<<endl<<endl;
		for(int i =1;i<=MAX_CUSTOMERS;i++){
			allCustomers.push_back(i*2);
		};
		
		
}

void Store::addToQueue(){
		int temp;
		int sizeAll;
		int value;
		
		sizeAll = allCustomers.size();
		srand(time(0));
		//random_device seed ;
		//mt19937 engine(seed()) ;
		while(sizeAll>0){

			cout<<"allCustomers size is: "<<sizeAll<<endl;
			//uniform_int_distribution<int> choose(0,allCustomers.size()-1) ;
			cout<<"allCustomers: ";
			copy( allCustomers.cbegin(), allCustomers.cend(), output );
			cout<<endl<<endl;
			
			if(sizeAll >1) {
				temp=rand() % (sizeAll);
			}else temp =0; 
			value = allCustomers[temp];
			cout<<"allCustomers at "<<temp<<" is: "<<value<<endl;
			
			// check to see if there is room in the queue to add new members
			// if not, block counter would be increased by one
			if(customersQ.size()<12)
				customersQ.push_back(value);
				else
					blockCounter++;
			
			cout<<"customersQ: ";
			copy( customersQ.cbegin(), customersQ.cend(), output );
			cout<<endl<<endl;
			
			
			allCustomers.erase(remove(allCustomers.begin(),allCustomers.end(),value));
			cout<<"---------- Erase is done ------------"<<endl<<endl;
			
			sizeAll = allCustomers.size();

		};
};

void Cashier::checkQueue(){
		srand(time(0));
		int order = rand() % (customersQ.size());
		cout<<"\n\nindex "<<order<<" of customersQ with value "
			<<customersQ[order]<<" will be removed"<<endl;
			
		customersQ.erase(remove(customersQ.begin(),customersQ.end(),customersQ[order]));
		
		cout<<"customersQ: ";
			copy( customersQ.cbegin(), customersQ.cend(), output );
			cout<<endl<<endl;
};
