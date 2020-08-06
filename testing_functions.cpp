#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <string>
#include "functions.h"
using namespace std;

void print_traj(FILE* out_traj,double* traj,int N_spots);
void init_traj(double* traj,double x0);
double perform_sweeps(double* traj,int N_spots,double a,double omega,double sigma_coef,
	int sigma_sweeps_period, double acc_rate_up_border,double acc_rate_low_border,
	int N_sweeps_waiting,int N_sweeps_storing);
double av_sq_x(double* traj, int N_spots);
double norm_dist(double x0,double sigma);

int main()
{
    clock_t start,end;
	start=clock();
	srand(time(0));

	const int N_sweeps_waiting=8000;
	const int N_sweeps_storing=15000;
	const double a=0.025;
	const int N_spots=200;
	int beta=a*N_spots;
	const double omega=2;

	const int sigma_local_updates_period=1000;
	const int sigma_sweeps_period=ceil((double)sigma_local_updates_period/N_spots);
	const double sigma_coef=1.2;
	const double acc_rate_up_border=0.3;
	const double acc_rate_low_border=0.2;

	FILE *out_norm_dis_test;
	out_norm_dis_test=fopen("out_norm_dis_test.txt","w");

	for (int i = 0; i < 1000000; i++)
	{
		fprintf(out_norm_dis_test,"%lf\n",norm_dist(2.5,0.8));
	}
	
	fclose(out_norm_dis_test);
    end=clock();
	printf("TIME: %.2lf ms\n",(double)(end-start)/CLOCKS_PER_SEC*1000);
}