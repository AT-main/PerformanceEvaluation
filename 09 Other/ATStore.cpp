//Amir tajik

//---------- Libraries ----------

#include <iostream>
#include <queue>
#include <random>
#include <vector>
#include <algorithm>
#include <thread>
#include <stdlib.h>
#include <unistd.h>
#include <cstdlib>
#include <ctime>
#include <chrono>
//----------
using namespace std;
//===============================
//---------- Global Variables ---
//===============================
vector<int> population;
queue<int> customersQ;
int nextCustomerAddTime = 0;
int blockCounter = 0;

//--------- Constants -----------
#define maxCustomers 1000
#define tab "\t"
#define maxQueueSize 12

//===============================
//--------- Classes -------------
//===============================

class Customer{
		public:
			int id =0;
			
			long long waitingTime;  	//time since customer stood in the queue
			long long serviceTime; 	//time customer needs to be served
			long long deadline;		//maximum time customer can stand in the queue
};

class Store{
		public:
			void createPopulation();
			void addToQueue();
};

class Cashier{
		public:
			long long freeTime=0;
			void checkQueue();
};
//===============================
//--------- Implementation ------
//===============================

Customer cst[maxCustomers];

int main(){
	
	Store store1;
	store1.createPopulation();
	Cashier cashier1;
	
	srand(time(0));
	nextCustomerAddTime += 1+ rand() %10;
	
	for (int timeCounter=0; timeCounter<=60; timeCounter++){
		
		if (population.size()>0 && timeCounter >= nextCustomerAddTime)
			store1.addToQueue();
		
		cout<<"minute "<<timeCounter<<" : "<<tab<<nextCustomerAddTime<<
			tab<<"Queue size: "<<customersQ.size()<<endl;
		cashier1.checkQueue();
		
	}
	
	//~ thread thread1(&Store::addToQueue,&store1);
	//~ thread thread2(&Cashier::checkQueue,&cashier1);
	//~ thread1.join();
	//~ thread2.join();
	
	//thread thread1(store1.addToQueue());
	//thread thread2(cashier1.checkQueue()):
	
	cout<<"Queue size: "<<customersQ.size()<<endl;
	cout<<"Population size: "<<population.size()<<endl;
	cout<<"Cashier Free Time: "<<cashier1.freeTime<<endl;
	

};

//===============================
//--------- Functions -----------
//===============================

void Store::createPopulation(){
		for(int i=1; i<=maxCustomers; i++){
			cst[i].id = i;
			population.push_back(cst[i].id); //? why push_back? why not simply push?
		}

} //?semicolon causes a problem here?

void Store::addToQueue(){
		//~ for (int timeCounter=0; timeCounter<=60; timeCounter++){
		
			//if (population.size()>0 && timeCounter >= nextCustomerAddTime){
				int temp;
				
				random_device seed ;
				mt19937 engine(seed()) ;
				

				//default_random_engine engine(static_cast<int>(time(0)));
				uniform_int_distribution<int> randomId(0,population.size()-1);
				temp=population[randomId(engine)];
				
				//srand(static_cast<int>( time( 0 ) ));
				uniform_int_distribution<int> randomService(1,8);
				cst[temp].deadline = 11;
				cst[temp].serviceTime = randomService(engine);
				cst[temp].waitingTime = 0;
				
				//srand(static_cast<int>( time( 0 ) ));
				uniform_int_distribution<int> randomNext(1,10);
				nextCustomerAddTime += randomNext(engine);
				customersQ.push(cst[temp].id);
		//		cout<<"Customer id: "<<tab<<"deadline"<<tab<<"serviceTime"<<tab<<"waitingTime"<<endl;
		//		cout<<temp<<tab<<cst[temp].deadline<<tab<<cst[temp].serviceTime<<tab<<cst[temp].waitingTime<<endl;
		//		population.erase(temp);
				population.erase(remove(population.begin(),population.end(),temp));
	
		//}		
}

void Cashier::checkQueue(){
	
	//for (int timeCounter=0; timeCounter<=60; timeCounter++){
		if (customersQ.size()>0){
			if(cst[customersQ.front()].serviceTime <= 0)
				customersQ.pop();
				else {
					cst[customersQ.front()].serviceTime --;
					cout<<"First Customer service Time: "<< cst[customersQ.front()].serviceTime<<endl;
				}
			
			for (unsigned int i=1; i <= customersQ.size(); i++)
				cst[i].waitingTime ++;
		}
		else freeTime ++;
		
}
