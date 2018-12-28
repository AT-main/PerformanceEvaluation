// I hope this be the last version
//it's 10:18, Dec.1.2017



#include <stdlib.h>
#include <random>
#include <math.h>
#include <vector>
#include <algorithm>

#include <iostream>


//======================================================================
//----------------------------- Constants ------------------------------
//======================================================================
#define LAMBDA 1.2
#define MU 1
#define THETA 2
#define POPULATION 10
#define QUEUE_SIZE 2
#define TAB "\t"


//======================================================================
//----------------------------- Global Variables -----------------------
//======================================================================
double arrivals[POPULATION+1];
double absArrivals[POPULATION+1];
double serviceTimes[POPULATION+1];
double leaveTimes[POPULATION+1];
double absLeaveTimes[POPULATION+1];
//~ double LAMBDA = 1.4;

using namespace std;

int main()
{
	vector<double> absServiceTimes;
	
	int queueSize =0;
	int totalBlocked =0;
	int totalDeparted =0;
	int totalLeft = 0;
	double complTime=0;
	
	int out = 0;
	int in = 0;
	
	double net=0; //Next Event Time
	double nscet=0; //Next service completion event time
	double naet=0; //Next arrival event time
	
	
	absArrivals[1] = 0;
	arrivals[1]=0;
	serviceTimes[1]=1.0/MU;
	
	absServiceTimes.push_back(serviceTimes[1]);
	complTime = absServiceTimes.front();
	queueSize++;
	
	
	cout<<"Cust."<<TAB<<"Arrival"<<TAB<<"ComplTime"<<TAB
		<<"queueSize"<<TAB<<"Blocked"<<TAB<<"Departed"<<TAB
		<<"Left"<<endl;
	cout<<1<<TAB<<absArrivals[1]<<TAB<<complTime<<TAB
			<<queueSize<<TAB<<totalBlocked<<TAB<<totalDeparted<<TAB
			<<totalLeft<<endl;
			
	for (int i =2; i <= POPULATION; i++)
	{
			
		arrivals[i] = 1/LAMBDA;
		absArrivals[i] = absArrivals[i-1] + arrivals[i];
		
		serviceTimes[i] = 1.0/MU;
		leaveTimes[i] = 1.0/THETA;
		absLeaveTimes[i] = absArrivals[i] + leaveTimes[i];
	
	}
	in =2;
	out = 1;
	nscet = absServiceTimes.front();
	naet = absArrivals[2];
	
	while (out <= POPULATION)
	{
		if (in <= POPULATION)
		{
			net = min (nscet, naet);
			if (net == naet)
			{
				if (naet > complTime) // means queueSize = 0
				{
					complTime = absArrivals[in] + serviceTimes[in];
					absServiceTimes.push_back(complTime);

					naet = absArrivals[in+1];
					queueSize++;
					//~ in++;
				}
				else
				{
					if (queueSize < QUEUE_SIZE)
					{
						if (complTime > absLeaveTimes[in])
						{
							totalLeft++;
							out++;
							naet = absArrivals[in+1];
							//~ in++;
						}
						else
						{
						complTime = complTime + serviceTimes[in];
						absServiceTimes.push_back(complTime);

						naet = absArrivals[in+1];
						queueSize++; 
						//~ in++;
						}
					}
					else 
					{
						totalBlocked++;
						out++;
						naet = absArrivals[in+1];
					}
					
				}
				in++;
				
			}
			
			else if (net == nscet)
			{
				queueSize--;
				totalDeparted ++;
				absServiceTimes.erase(absServiceTimes.begin());
				nscet = absServiceTimes.front();
				out++;
			}
		}
		else
		{
			queueSize--;
			nscet = absServiceTimes[totalDeparted + 1];
			totalDeparted ++;
			out++;
			
		}
		
		cout<<in-1<<TAB<<absArrivals[in-1]<<TAB<<complTime<<TAB
			<<queueSize<<TAB<<totalBlocked<<TAB<<totalDeparted<<TAB
			<<totalLeft<<endl;
	}
	
	
	
	cout<<"Total Blocked: "<<totalBlocked<<endl;
	cout<<"Total Departed: "<<totalDeparted<<endl;
	cout<<"Total Left: "<<totalLeft<<endl;
	
	
}




