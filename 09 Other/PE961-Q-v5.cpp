//Amir Tajik
//PE961 - version 4 - Oct. 2017
//Khatam University - Performance Evaluation
// In this version I'm going to use pthread library to overcome the
// problem of running threads really synchronously.
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
#include <pthread.h>
#include <unistd.h>
#include <cstdlib>

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
int sizeAll;
int sizeQueue;

//======================================================================
//----------------------------- Constants ------------------------------
//======================================================================
#define LAMBDA 1
#define THETA 6
#define MAX_CUSTOMERS 200
#define QUEUE_SIZE 12 //no semicolons after constant variables
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

// prototype for function template printVector
template < typename T > void printVector( const vector< T > &integers2 );

void *testCheckQueue(void *test) {
	int order;
	srand(time(0));
	sizeQueue = customersQ.size();

	while (sizeAll>0) {
		order=0;
		cout<<"Queue size is: "<<sizeQueue<<endl;
		
		if(sizeQueue>0){
			if(sizeQueue>1)
				order = rand() % (sizeQueue);
			 
			//~ cout<<"\n\nindex "<<order<<" of customersQ with value "
				//~ <<customersQ[order]<<" will be removed"<<endl;
			
			customersQ.erase(remove(customersQ.begin(),customersQ.end(),customersQ[order]));
		};
		//~ cout<<"customersQ: ";
			//~ copy( customersQ.cbegin(), customersQ.cend(), output );
			//~ cout<<endl<<endl;
			sizeQueue = customersQ.size();
	};
	pthread_exit(NULL);
}

void *testAddToQueue(void *test){
		int temp;
	
		int value;
		
		sizeAll = allCustomers.size();
		srand(time(0));
		
		while(sizeAll>0){

			cout<<"allCustomers size is: "<<sizeAll<<endl;

			//~ cout<<"allCustomers: ";
			//~ copy( allCustomers.cbegin(), allCustomers.cend(), output );
			//~ cout<<endl<<endl;
			
			if(sizeAll >1) {
				temp=rand() % (sizeAll);
			}else temp =0; 
			value = allCustomers[temp];
			//~ cout<<"allCustomers at "<<temp<<" is: "<<value<<endl;
			
			// check to see if there is room in the queue to add new members
			// if not, block counter would be increased by one
			if(customersQ.size()<QUEUE_SIZE)
				customersQ.push_back(value);
				else
					blockCounter++;
			
			//printVector(customersQ);
			//~ cout<<"customersQ: ";
			//~ copy( customersQ.cbegin(), customersQ.cend(), output );
			//~ cout<<endl<<endl;
			
			usleep(0.01);
			allCustomers.erase(remove(allCustomers.begin(),allCustomers.end(),value));
			//cout<<"---------- Erase is done ------------"<<endl<<endl;
			
			sizeAll = allCustomers.size();

		};
	pthread_exit(NULL);
}

//======================================================================
//----------------------------- Implementation -------------------------
//======================================================================
int main(){
	Store store1;
	store1.createPopulation();
	//store1.addToQueue();
	
	
	//Cashier cashier1;
	//cashier1.checkQueue();
	
	pthread_t thread1;
	pthread_t thread2;
	
	pthread_create(&thread2, NULL, testAddToQueue, NULL);
	pthread_create(&thread1, NULL, testCheckQueue, NULL);
	void *status;
	pthread_join(thread2, &status);
	pthread_join(thread1, &status);
	
	
	cout<<"Block Counter: "<<blockCounter<<"\n\n";
	cout<<"customersQ: ";
			copy( customersQ.cbegin(), customersQ.cend(), output );
			cout<<endl<<endl;
	//~ printVector(customersQ);

	pthread_exit(NULL);
	
}
//======================================================================
//----------------------------- Functions ------------------------------
//======================================================================


void Store::createPopulation(){
		cout<<"Population being created..."<<endl<<endl;
		for(int i =1;i<=MAX_CUSTOMERS;i++){
			allCustomers.push_back(i);
		};
		
		
}

