//    8186783030213839

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <chrono>
#include <cmath>
#include "omp.h"
#define CHUNK
#define THREADS 8
#define COL 8 // no. of digits in each prime(ensured to be same for all by padding with zeroes for easy seeking in the file)
using namespace std;



typedef unsigned long long int ull;

int main()
{
	FILE *in=fopen("input.txt","r");
	FILE *primes;

	primes=fopen("primes.txt","r");


	/*int temp;

	fscanf(primes,"%d",&temp);
	cout<<temp<<endl;
	fseek(primes,(COL+2)*5,SEEK_CUR); // skips 5 primes and moves to the 6th one from the current pointer
	fscanf(primes,"%d",&temp);

	cout<<temp<<endl;*/


	ull public_key;
	ull private_key1=0,private_key2=0;
	ull limit;
	ull temp;
	int flag=0;
	int count=0;

	fscanf(in,"%llu",&public_key);
	limit=(unsigned long long)sqrt(public_key);

	cout<<public_key<<endl;

	cout<<limit<<endl;

	//sequential code
	auto start=chrono::high_resolution_clock::now();

	fscanf(primes,"%llu",&temp);

	FILE *out=fopen("output.txt","w");

	while(temp<=limit)
	{
		//cout<<temp<<endl;

		if(!(public_key%temp))
		{	cout<<temp<<endl;
			private_key1=temp;
			private_key2=public_key/temp;
			break;
		}
		//fprintf(out,"%llu\r\n",temp);
		fscanf(primes,"%llu",&temp);
	}

//	omp_set_nested(1);

	cout<<"The two private keys are:\t"<<private_key1<<"\t"<<private_key2<<endl;

	auto end=chrono::high_resolution_clock::now();
	auto sequential_time=chrono::duration_cast<chrono::nanoseconds>(end-start).count();

	cout<<"Execution time :\t"<<sequential_time<<endl;

	cout<<temp<<endl;

	rewind(primes);

	private_key1=0;
	private_key2=0;

	//parallel code

	start=chrono::high_resolution_clock::now();

	fscanf(primes,"%llu",&temp);

	while(temp<limit && !flag)
	{
		#pragma omp parallel num_threads(THREADS) private(primes)
		{
			int id=omp_get_thread_num();
			primes=fopen("primes.txt","r");

			fseek(primes,(COL+2)*4000*((count*THREADS)+id),SEEK_SET);

			#pragma omp parallel for num_threads(2) schedule(dynamic,2000) private(temp)
			for(int j=0;j<4000;j++)
			{
				fscanf(primes,"%llu",&temp);

				if(flag)
				continue;


				if(!(public_key%temp))
				{
					private_key1=temp;
					private_key2=public_key/temp;
					flag=1;
				}



			}
		fscanf(primes,"%llu",&temp);

		}


		count++;
	}

	cout<<"The two private keys are:\t"<<private_key1<<"\t"<<private_key2<<endl;

	end=chrono::high_resolution_clock::now();
	auto parallel_time=chrono::duration_cast<chrono::nanoseconds>(end-start).count();

	cout<<"Execution time :\t"<<parallel_time<<endl;
	fclose(out);

}