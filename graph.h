#pragma once

#include<iostream>
using namespace std;
#include<algorithm>
#define row 100
#define column 100
class graph
{
private:

	int g[row][column];
	int vs;
	int vl;
	int choose[512];

public:
	void print();
	void printindex(int f);
	void random(int snum, int lnum, int f[100][100]);
	void round(int snum, int lnum, int f[100][100]);
	void llf(int snum, int lnum, int f[100][100]);
	void rslb(int snum, int lnum, int f[100][100]);
	float throughput(int snum, int lnum, int f[100][100]);
	float throughputfail(int snum, int lnum, int f[100][100]);

	graph(int m, int n)
	{
		vs = m;
		vl = n;
		for (int i = 0; i < vl; i++)
		{
			for (int j = 0; j < vs; j++)
				g[i][j] = 0;
		}

	}
};

void graph::print()
{
	for (int i = 0; i < vl; i++)
	{
		for (int j = 0; j < vs; j++)
		{
			cout << g[i][j] << " ";
		}
		cout << endl;
	}


}

void graph::printindex(int f)
{
	for (int i = 0; i < f; i++)
		cout << choose[i] << " ";

}

void graph::random(int snum, int lnum, int f[100][100])
{

	int ff[100][100];
	for (int i = 0; i < lnum; i++)
	{
		for (int j = 0; j < lnum; j++)
		{
			ff[i][j] = f[i][j];
		}
	}

	int s;
	int index = 0;
	for (int i = 0; i < lnum; i++)
	{
		for (int j = 0; j < lnum; j++)
		{
			while (ff[i][j] != 0)
			{
				s = rand() % snum;
				g[i][s]++;
				g[j][s]++;
				choose[index] = s;
				index++;
				ff[i][j]--;
			}
		}
	}


}

void graph::round(int snum, int lnum, int f[100][100])
{

	int ff[100][100];
	for (int i = 0; i < lnum; i++)
	{
		for (int j = 0; j < lnum; j++)
		{
			ff[i][j] = f[i][j];
		}
	}

	int s;
	int index = 0;
	int num;
	for (int i = 0; i < lnum; i++)
	{
		 num = 0;
		for (int j = 0; j < lnum; j++)
		{
			while (ff[i][j] != 0)
			{
				num++;
				s = num % snum;
				g[i][s]++;
				g[j][s]++;
				choose[index] = s;
				index++;
				ff[i][j]--;
			}
		}
	}
}

void graph::rslb(int snum, int lnum, int f[100][100])
{
	int nflow = 0;

	int ff[100][100];
	for (int i = 0; i < lnum; i++)
	{
		for (int j = 0; j < lnum; j++)
		{
			ff[i][j] = f[i][j];
			nflow = nflow + f[i][j];
		}
	}

	int s;
	int cost;
	int index = 0;
	int count = 0;
	for (int i = 0; i < lnum; i++)
	{

		for (int j = 0; j < lnum; j++)
		{
			while (ff[i][j] != 0)
			{
				s = 0;
				cost = min(g[i][0], g[j][0]);
				for (int k = 1; k < snum; k++) {
					int ncost = min(g[i][k], g[j][k]);
					if (ncost < cost) {
						cost = ncost;
						s = k;
					}
				}

		/*		for (int k = 0; k < snum; k++) {
					int ncost = min(g[i][k], g[j][k]);
					if (ncost == cost) {
						count++;
						break;
					}
				}*/
				g[i][s]++;
				g[j][s]++;
				choose[index] = s;
				index++;
				ff[i][j]--;
			}
		}
	}
}

void graph::llf(int snum, int lnum, int f[100][100])
{

	int ff[100][100];
	for (int i = 0; i < lnum; i++)
	{
		for (int j = 0; j < lnum; j++)
		{
			ff[i][j] = f[i][j];
		}
	}

	int s;
	int cost;
	int index = 0;
	for (int i = 0; i < lnum; i++)
	{
		
		for (int j = 0; j < lnum; j++)
		{
			while (ff[i][j] != 0)
			{
				s = 0;
				cost = max(g[i][0], g[j][0]);
				for (int k = 1; k < snum; k++) {
					int ncost = max(g[i][k], g[j][k]);
					if (ncost < cost) {
						cost = ncost;
						s = k;
					}
				}
				g[i][s]++;
				g[j][s]++;
				choose[index] = s;
				index++;
				ff[i][j]--;
			}
		}
	}
}

float graph::throughput(int snum, int lnum, int f[100][100])
{

	int ff[100][100];
	for (int i = 0; i < lnum; i++)
	{
		for (int j = 0; j < lnum; j++)
		{
			ff[i][j] = f[i][j];
		}
	}

	float throughput;
	float sum;
	sum = 0;
	
	int s;
	int index = 0;
	for (int i = 0; i < lnum; i++)
	{
		for (int j = 0; j < lnum; j++)
		{   
			while (ff[i][j] != 0)
			{
				s = choose[index];
				if (g[i][s]>=g[j][s])
				{
					throughput = 1.0 / g[i][s];
				}
				else
				{
					throughput = 1.0 / g[j][s];
				}
			//	cout << throughput << " " ;
				sum = sum + throughput;
			
				index++;
				ff[i][j]--;
			}
		}
	}
	return sum;

}

float graph::throughputfail(int snum, int lnum, int f[100][100])
{

	int ff[100][100];
	for (int i = 0; i < lnum; i++)
	{
		for (int j = 0; j < lnum; j++)
		{
			ff[i][j] = f[i][j];
		}
	}

	float throughput;
	float sum;
	sum = 0;
	float t1,t2;
	int r,r1;

	int s;
	int index = 0;
	for (int i = 0; i < lnum; i++)
	{
		for (int j = 0; j < lnum; j++)
		{
			while (ff[i][j] != 0)
			{
				s = choose[index];

				r = rand() % 4;
				if (r == 0)
				{
					t1 = 0.5 / g[i][s];
				}
				else 
				{
                    t1= 1.0 / g[i][s];
				}

				r1 = rand() % 4;
				if (r1 == 0)
				{
					t2 = 0.5 / g[j][s];
				}
				else
				{
					t2 = 1.0 / g[j][s];
				}


				if (t1 >= t2)
				{
					throughput =t2;
				}
				else
				{
					throughput = t1;
				}
				//	cout << throughput << " " ;
				sum = sum + throughput;

				index++;
				ff[i][j]--;
			}
		}
	}
	return sum;

}

