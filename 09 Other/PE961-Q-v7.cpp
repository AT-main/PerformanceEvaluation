//Amir Tajik
//PE961 - version 7 - Nov. 2017
//Khatam University - Performance Evaluation
// In this version I'm going to add the effect of MU variable as well as 
// working on better synchronization of the threads.
// I need to make sure that threads are executed almost the same number 
// of times and desirably in equal intervals.
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

int queueCheckExecuted =0;
int queueAddExecuted =0;

int turnCounter =  10;


//======================================================================
//----------------------------- Constants ------------------------------
//======================================================================
#define LAMBDA 0.1
#define THETA 2
#define MAX_CUSTOMERS 5000
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

//============================  Check Queue Function  ==================
void *testCheckQueue(void *test) {
	int order;
	srand(time(0));
	sizeQueue = customersQ.size();

	while (sizeAll>0) {
		//~ if (turnCounter <= 10){
			turnCounter ++;
			usleep(1);
			order=0;
			cout<<"Queue size is: "<<sizeQueue<<endl;
			queueCheckExecuted++;
			if(sizeQueue>0){
				if(sizeQueue>1)
					order = rand() % (sizeQueue);
				 
				customersQ.erase(remove(customersQ.begin(),customersQ.end(),customersQ[order]));
			};
				sizeQueue = customersQ.size();
		//~ }
	};
	pthread_exit(NULL);
}
//============ Add To Queue Function ===================================
void *testAddToQueue(void *test){
		int temp;
	
		int value;
		
		
		srand(time(0));
		
		while(sizeAll>0){
			//~ if (turnCounter >=10) {
				turnCounter--;
				queueAddExecuted++;
				int LAMBDA_10 = LAMBDA*10;
				for(int i=1; i<=LAMBDA_10; i++)
					if(!allCustomers.empty()){
						if(sizeAll >1) {
							temp=rand() % (sizeAll);
						}else temp =0; 
						value = allCustomers[temp];
						if(customersQ.size()<= QUEUE_SIZE)
							customersQ.push_back(value);
							else
								blockCounter++;
	
						allCustomers.erase(remove(allCustomers.begin(),allCustomers.end(),value));
						sizeAll = allCustomers.size();
						cout<<"Population size is: "<<sizeAll<<endl;
					} // if block
				
			//~ }					
			usleep(2);
		};
	pthread_exit(NULL);
}

//======================================================================
//----------------------------- Implementation -------------------------
//======================================================================
int main(){
	Store store1;
	void *status;

	store1.createPopulation();

	pthread_t thread1;
	pthread_t thread2;
	
	sizeAll = allCustomers.size();
	
	pthread_create(&thread2, NULL, testAddToQueue, NULL);
	pthread_create(&thread1, NULL, testCheckQueue, NULL);
	pthread_join(thread2, &status);
	pthread_join(thread1, &status);
	
	
	cout<<"Block Counter: "<<blockCounter<<"\n\n";
	cout<<"customersQ: ";
			copy( customersQ.cbegin(), customersQ.cend(), output );
	cout<<endl<<endl;
	
	cout<<"Add execution times = "<<queueAddExecuted<<endl;
	cout<<"Check execution times = "<<queueCheckExecuted<<endl;
	cout<<"Add to Check proportion = "<<(float) queueAddExecuted/queueCheckExecuted<<endl;

	pthread_exit(NULL);
	
}
//======================================================================
//----------------------------- Functions ------------------------------
//======================================================================


void Store::createPopulation(){
		cout<<"Population being created..."<<endl<<endl;
		for(int i =1;i<=MAX_CUSTOMERS;i++)
			allCustomers.push_back(i);
}

