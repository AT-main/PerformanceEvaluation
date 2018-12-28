// I hope this be the last version
//it's 3:04 in the morning



#include <stdlib.h>
#include <random>
#include <math.h>
#include <algorithm>


#include <iostream>


//======================================================================
//----------------------------- Constants ------------------------------
//======================================================================
#define LAMBDA 1
#define MU 4
#define THETA 2
#define POPULATION 10
#define QUEUE_SIZE 4 
#define TAB "\t"


//======================================================================
//----------------------------- Global Variables -----------------------
//======================================================================
double arrivals[POPULATION+1];
double absArrivals[POPULATION+1];
double serviceTimes[POPULATION+1];
double absServiceTimes[POPULATION+1];
double leaveTimes[POPULATION+1];
double absLeaveTimes[POPULATION+1];

using namespace std;

int main()
{
	int queueSize =0;
	int totalBlocked =0;
	int totalDeparted =0;
	int totalLeft = 0;
	double complTime=0;
	
	
	absArrivals[1] = 0;
	arrivals[1]=0;
	serviceTimes[1]=1.0/MU;
	complTime = complTime + serviceTimes[1];
	queueSize++;
	
	cout<<"Cust."<<TAB<<"Arrival"<<TAB<<"ComplTime"<<TAB
		<<"queueSize"<<TAB<<"Blocked"<<TAB<<"Departed"<<TAB
		<<"Left"<<endl;
	cout<<1<<TAB<<absArrivals[1]<<TAB<<complTime<<TAB
			<<queueSize<<TAB<<totalBlocked<<TAB<<totalDeparted<<TAB
			<<totalLeft<<endl;
			
	for (int i=2; i<= POPULATION; i++)
	{
			
		arrivals[i] = 1.0/LAMBDA;
		absArrivals[i] = absArrivals[i-1] + arrivals[i];
		
		serviceTimes[i] = 1.0/MU;
		leaveTimes[i] = 1.0/THETA;
		absLeaveTimes[i] = absArrivals[i] + leaveTimes[i];
		
		if (absArrivals[i] < complTime)
		{
			if (queueSize < 12)
			{
				if (complTime > absLeaveTimes[i])
					totalLeft++;
					else
					{
					queueSize++;
					complTime = complTime + serviceTimes[i];
					}
			}
			else totalBlocked++;
		}
		else 
		{
			complTime = absArrivals[i] + serviceTimes[i];
			queueSize =1;
		}
		
		cout<<i<<TAB<<absArrivals[i]<<TAB<<complTime<<TAB
			<<queueSize<<TAB<<totalBlocked<<TAB<<totalDeparted<<TAB
			<<totalLeft<<endl;
	}
	
	
	
	cout<<"Total Blocked: "<<totalBlocked<<endl;
	cout<<"Total Departed: "<<totalDeparted<<endl;
	cout<<"Total Left: "<<totalLeft<<endl;
	
	
}




