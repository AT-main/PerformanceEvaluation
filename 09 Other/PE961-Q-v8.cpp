// Created to take a new approach in writing the code for assignment1
//Amir Tajik
//Assignment PE961-Q - Performance Evaluation - Dr. Movaghar
// m/m/1/k queue simulation code

#include <stdlib.h>
#include <random>
#include <math.h>
#include <algorithm>


#include <iostream>


//======================================================================
//----------------------------- Constants ------------------------------
//======================================================================
#define LAMBDA 10
#define MU 1
#define THETA 2
#define POPULATION 100
#define QUEUE_SIZE 12 
#define TAB "\t"


//======================================================================
//----------------------------- Global Variables -----------------------
//======================================================================
double arrivals[POPULATION+1];
double absArrivals[POPULATION+1];
double serviceTimes[POPULATION+1];
double absServiceTimes[POPULATION+1];
double leaveTimes[POPULATION+1];
double absleaveTimes[POPULATION+1];

double nextArrival, nextDeparture, nextLeave, sysClock;



using namespace std;

int main()
{
	int queueSize =0;
	int totalBlocked =0;
	int totalDeparted =0;
	int totalLeft = 0;
	
	int in, out;
	
	absArrivals[0] = 0;
	sysClock =0;

	for (int i=1; i<= POPULATION; i++)
	{
		arrivals[i] = 1.0/LAMBDA;
		absArrivals[i] = absArrivals[i-1] + arrivals[i];
		
		serviceTimes[i] = 1.0/MU;
		leaveTimes[i] = 1.0/THETA;
	}
	
	nextLeave = absArrivals[POPULATION]+1;
	
	in=2;
	out=1;
	queueSize = 1;
	arrivals[0] = 0;
	sysClock = absArrivals[1];
	nextArrival = absArrivals[2];
	nextDeparture = absServiceTimes[1] = sysClock + serviceTimes[1];
	nextLeave = absArrivals[out+1] + leaveTimes[out+1];
	
	//~ cout<<"Arrival\t"<<"Departure\t"<<"Leave\n";
	//~ cout<<nextArrival<<TAB<<nextDeparture<<TAB<<nextLeave<<endl;
	double minTime;
	
	while (out <=  POPULATION)
	{
		if (in <= POPULATION)
		{
			cout<<"\n out: "<<out<<TAB<<"in: "<<in<<endl<<endl;
			minTime =  (min(min(nextArrival,nextDeparture),nextLeave));
			cout<<"minTime equals: "<<minTime<<endl;
			if (minTime == nextArrival)
			{
				sysClock = nextArrival;
				if (queueSize < QUEUE_SIZE)
				{
					cout<<"Arrival at: "<<sysClock<<endl;
					queueSize++;
					cout<<"New queue size is: "<<queueSize<<endl;
				}
				else
				{
					cout<<"Blocked at: "<<sysClock<<endl;
					totalBlocked++;
					serviceTimes[in] = 0;
				}
				nextArrival = absArrivals[in+1];
				in++;
			}
			
			if (minTime == nextDeparture)
			{
				//Service is complete, so first element of the queue should be removed
				queueSize--;
				sysClock = nextDeparture;
				cout<<"Departure at: "<<sysClock<<endl;
				out++;
				nextDeparture = sysClock + serviceTimes[out+1];
				totalDeparted++;
				
			}
			
			if (minTime == nextLeave)
			{
				//a customer in the queue reached their deadline and have to leave 
				sysClock = nextLeave;
				cout<<"Leave at: "<<sysClock<<endl<<endl<<endl;
				queueSize --;
				out++;
				//~ serviceTimes[in] = 0;
				nextLeave = absArrivals[out+1] + leaveTimes[out+1];
				totalLeft++;
				
				
			}
		}
		else
		{
			sysClock = nextDeparture;
			queueSize--;
			out++;
			nextDeparture = sysClock + serviceTimes[out+1];
		}	
		cout<<"Arrival\t"<<"Departure\t"<<"Leave\n";
		cout<<nextArrival<<TAB<<nextDeparture<<TAB<<nextLeave<<endl;
	}
	
	cout<<"Total Blocked: "<<totalBlocked<<endl;
	cout<<"Total Departed: "<<totalDeparted<<endl;
	cout<<"Total Left: "<<totalLeft<<endl;
	
	
}

