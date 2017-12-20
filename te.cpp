#include<iostream>
#include"graph.h"
using namespace std;
#include"algorithm"
#define num 10


int flow[100][100] = { 0 };
int f;
float result[num] = { 0 };
float result1[num] = { 0 };
float result2[num] = { 0 };
float result3[num] = { 0 };

float resultf[num] = { 0 };
float resultf1[num] = { 0 };
float resultf2[num] = { 0 };
float resultf3[num] = { 0 };

void input(int fnum,int lnum)
{
	int d, s;
	for (int i = 0; i < fnum; i++)
	{
		d = rand() % lnum;
		s = rand() % lnum;
		while (d == s)
		{
			d = rand() % lnum;
			s = rand() % lnum;
		}

		flow[s][d]++;
	}


}

void printflow(int lnum)
{
	for (int i = 0; i < lnum; i++)
	{
		for (int j = 0; j < lnum; j++)
		{
			cout << flow[i][j] << " ";
		}
		cout << endl;
	}
}

void print_index(int lnum,int f[100][100])
{

	int ff[100][100];
	for (int i = 0; i < lnum; i++)
	{
		for (int j = 0; j < lnum; j++)
		{
			ff[i][j] = f[i][j];
		}
	}

	for (int i = 0; i < lnum; i++)
	{
		for (int j = 0; j < lnum; j++)
		{
			 while(ff[i][j] != 0)
			{
				cout << "s:" << i << "d:" << j << endl;
				ff[i][j]--;

			}
		}
	}
}

float average(float a[]) {
	int l = sizeof(a);
	float sum = 0;
	for (int i = 0; i < l; i++) {
		sum = sum + a[i];
	}
	float ave = sum / l;
	return ave;

}

float stdd(float a[]) {
	int l = sizeof(a);
	float ave = average(a);
	float sum = 0;
	for (int i = 0; i < l; i++) {
		sum = sum + (ave-a[i]) * (ave - a[i]);
	}

	sum = sqrt(sum);
	float stdd = sum / l;
	return stdd;
}

int main()
{
	while (1)
	{
		int l = 4;
		int s = 8;
	//	cout << "Input the number of spine nodes" << endl;

	//	cin >> s;

	//	cout << "Input the number of leaf nodes" << endl;

	//	cin >> l;
		
		cout << "Input the number of flows" << endl;

		cin >> f;

	//	printflow(l);

		for (int k = 0; k < num; k++) {
			for (int ii = 0; ii < 100; ii++)
				for (int jj = 0; jj < 100; jj++)
					flow[ii][jj] = { 0 };

			input(f, l);

			graph g1 = graph(s, l);
			graph g2 = graph(s, l);
			graph g3 = graph(s, l);
			graph g4 = graph(s, l);

			g1.random(s, l, flow);
			g2.round(s, l, flow);
			g3.rslb(s, l, flow);
			g4.llf(s, l, flow);

			//	g3.print();
			//	cout << endl;
			//	g4.print();
			//	cout << endl;
				
				//print_index(l, flow);
				//	g1.printindex(f);

			result[k] = g1.throughput(s, l, flow);
			result1[k] = g2.throughput(s, l, flow);       //These three is calculate the throughput of the case uniform capacity
			result2[k] = g3.throughput(s, l, flow);
			result3[k] = g4.throughput(s, l, flow);

			  resultf[k] = g1.throughputfail(s, l, flow);
			  resultf1[k] = g2.throughputfail(s, l, flow);    //These three is calculate the throughput of the case random 25% links fail
			  resultf2[k] = g3.throughputfail(s, l, flow);
			  resultf3[k] = g4.throughputfail(s, l, flow);
		}

		float rav1 = average(result);
		float rstd1 = stdd(result);
		float up1 = rav1 + 1.96* rstd1;
		float down1 = rav1 - 1.96* rstd1;

		float rav2 = average(result1);
		float rstd2 = stdd(result1);
		float up2 = rav2 + 1.96* rstd2;
		float down2 = rav2 - 1.96* rstd2;

		float rav3 = average(result2);
		float rstd3 = stdd(result2);
		float up3 = rav3 + 1.96* rstd3;
		float down3 = rav3 - 1.96* rstd3;

		float rav4 = average(result3);
		float rstd4 = stdd(result3);
		float up4 = rav4 + 1.96* rstd4;
		float down4 = rav4 - 1.96* rstd4;

		float rav5 = average(resultf);
		float rstd5 = stdd(resultf);
		float up5 = rav5 + 1.96* rstd5;
		float down5 = rav5 - 1.96* rstd5;

		float rav6 = average(resultf1);
		float rstd6 = stdd(resultf1);
		float up6 = rav6 + 1.96* rstd6;
		float down6 = rav6 - 1.96* rstd6;

		float rav7 = average(resultf2);
		float rstd7 = stdd(resultf2);
		float up7 = rav7 + 1.96* rstd7;
		float down7 = rav7 - 1.96* rstd7;

		float rav8 = average(resultf3);
		float rstd8 = stdd(resultf3);
		float up8 = rav8 + 1.96* rstd8;
		float down8 = rav8 - 1.96* rstd8;

	/*	sort(result, result + 10);
		sort(result1, result1 + 10);
		sort(result2, result2 + 10);
		sort(result3, result3 + 10);

		sort(resultf, resultf + 10);
		sort(resultf1, resultf1 + 10);
		sort(resultf2, resultf2 + 10);
		sort(resultf3, resultf3 + 10);*/

	//	for (int i = 0; i < 10; i++) {
	//		cout << result3[i] << endl;
	//	}

		cout << "The total throughput is Random: " <<rav1<<" ["<<down1<<","<<up1<<"] " <<" Round:" << rav2 << " [" << down2 << "," << up2 << "] " << " RSLB:" << rav3 << " [" << down3 << "," << up3 << "] " << " LLF:" << rav4 << " [" << down4 << "," << up4 << "] " << endl;
		cout << endl;
		cout << "The total throughput in 25% random fail is Random: " << rav5 << " [" << down5 << "," << up5 << "] " << " Round:" << rav6 << " [" << down6 << "," << up6 << "] " << " RSLB:" << rav7 << " [" << down7 << "," << up7 << "] " << " LLF:" << rav8 << " [" << down8 << "," << up8 << "] " << endl;
	}
	return 0;
}