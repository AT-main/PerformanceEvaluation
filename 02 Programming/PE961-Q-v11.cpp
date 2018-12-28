// 
//


#include <stdlib.h>
#include <random>
#include <math.h>
#include <vector>
//~ #include <algorithm>

#include <iostream>
#include <iomanip>


//======================================================================
//----------------------------- Constants ------------------------------
//======================================================================
//~ #define LAMBDA 10
#define MU 1
#define THETA 2
#define POPULATION 1000
#define QUEUE_SIZE 12
#define TAB "\t"


//======================================================================
//----------------------------- Global Variables -----------------------
//======================================================================
double arrivals[POPULATION+1];
double absArrivals[POPULATION+1];
double serviceTimes[POPULATION+1];
double leaveTimes[POPULATION+1];
double absLeaveTimes[POPULATION+1];
double lambda = 0;
int queueSize =0;
double 	Pb_analytic, Pd_analytic, product[QUEUE_SIZE+1], 
		coef_sum, coef[QUEUE_SIZE+1], P0;

using namespace std;

//======================================================================
//----------------------------- Main------------------------------------
//======================================================================
int main()
{
	vector<double> absServiceTimes;
	vector<double> absLeaveTimesVector;
	
	cout<<left<<setw(10)<<"lambda"
			<<left<<setw(12)<<"Pb Sim"
			<<left<<setw(20)<<"Pb analytic"
			<<left<<setw(12)<<"Pd Sim"
			<<left<<setw(12)<<"Pd analytic"
			<<endl;
			
	for (lambda=0.1; lambda<=20.1; lambda+=0.1)
	{
		int totalBlocked =0;
		int totalDeparted =0;
		int totalLeft = 0;
		double complTime= 0;
		
		srand(time(0));
		int out = 1;
		int in = 2;
		
		double net=0; //Next Event Time
		double nscet=0; //Next service completion event time
		double naet=0; //Next arrival event time
		double nlet=0; //Next Leave event time
		
		absArrivals[1] = 0;
		arrivals[1]=0;
		double x = (double)rand()/RAND_MAX;
		serviceTimes[1]=(double)-log(1.0-x)/MU;
		
		absServiceTimes.push_back(serviceTimes[1]);
		complTime = absServiceTimes.front();
		queueSize++;
		
		for (int i =2; i <= POPULATION; i++)
		{
			x = (double)rand()/RAND_MAX;
			arrivals[i] = (double) -log(1.0 -x) / lambda;
			absArrivals[i] = absArrivals[i-1] + arrivals[i];
	
			x = (double)rand()/RAND_MAX;
			serviceTimes[i] = (double)-log(1.0 -x)/MU;
			
			x = (double)rand()/RAND_MAX;
			leaveTimes[i] = (double)-log(1.0 -x)/THETA;
			
			absLeaveTimes[i] = absArrivals[i] + leaveTimes[i];
		}

		nscet = absServiceTimes.front();
		naet = absArrivals[2];
		
		nlet = INFINITY;
		
		while (out <= POPULATION)
		{
			if (in <= POPULATION)
			{
				net = min (nscet, min( naet, nlet));
				if (net == naet)
				{
					if (naet > complTime) // means queueSize = 0
					{
						complTime = absArrivals[in] + serviceTimes[in];
						absServiceTimes.push_back(complTime);
						nscet = absServiceTimes.front();
						naet = absArrivals[in+1];
						queueSize++;
					}
					else
					{
						if (queueSize < QUEUE_SIZE)
						{
							if (complTime > absLeaveTimes[in])
							{
								absLeaveTimesVector.push_back(absLeaveTimes[in]);
								queueSize++;
								naet = absArrivals[in+1];
								if (absLeaveTimesVector.size() == 1)
									nlet = absLeaveTimesVector.front();
							}
							else
							{
								complTime = complTime + serviceTimes[in];
								absServiceTimes.push_back(complTime);
			
								naet = absArrivals[in+1];
								queueSize++; 
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
					absServiceTimes.erase(absServiceTimes.begin());
					if (queueSize == 0) 
					nscet =  INFINITY;
					else
						nscet = absServiceTimes.front();
					totalDeparted ++;
					out++;
				}
				else if (net == nlet)
				{
					queueSize--;
					totalLeft ++;
					absLeaveTimesVector.erase(absLeaveTimesVector.begin());
					if (absLeaveTimesVector.size() == 0) 
						nlet = INFINITY;
						else
							nlet = absLeaveTimesVector.front();
					out++;
				}
			}
			else
			{
				net = (double) min(nscet, nlet);
				if (net == nscet)
				{
					queueSize--;
					absServiceTimes.erase(absServiceTimes.begin());
					if (queueSize == 0) 
					nscet =  INFINITY;
					else
						nscet = absServiceTimes.front();
					totalDeparted ++;
					out++;
				}
				else if (net == nlet)
				{
					queueSize--;
					totalLeft ++;
					absLeaveTimesVector.erase(absLeaveTimesVector.begin());
					if (absLeaveTimesVector.size() == 0) 
						nlet = INFINITY;
						else
							nlet = absLeaveTimesVector.front();
					out++;
				}
			}
			
		}
		
		product[0] = MU;
		coef[0] = 1;
		coef[1] = lambda/MU;
		coef_sum = 0;
		for (int i=0; i<=QUEUE_SIZE; i++)
		{
			if (i>0)
				product[i] = (product[i-1])*(MU + (double) i/THETA);
			if(i>1)
				coef[i] =  pow(lambda,i)/product[i-1];
			coef_sum += coef[i];
		}
		P0 = 1/coef_sum;
		Pb_analytic = P0 * coef[12];
		Pd_analytic = 1 - MU/lambda *(1-P0) - Pb_analytic;
		
		
		cout<<left<<setw(10)<<lambda
			<<left<<setw(12)<<(double)totalBlocked/POPULATION
			<<left<<setw(20)<<Pb_analytic
			<<left<<setw(12)<<(double)totalLeft/POPULATION
			<<left<<setw(12)<<Pd_analytic
			<<endl;
		
	
	}
}




