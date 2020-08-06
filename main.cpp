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


int main()
{
    clock_t start,end;
	start=clock();
	srand(time(0));

	const int N_sweeps_waiting=28000;
	const int N_sweeps_storing=15000;
	const double a=0.02;
	const int N_spots=500;
	//double beta=a*N_spots;
	const double omega=2;

	const int sigma_local_updates_period=1000;
	const int sigma_sweeps_period=ceil((double)sigma_local_updates_period/N_spots);
	const double sigma_coef=1.2;
	const double acc_rate_up_border=0.3;
	const double acc_rate_low_border=0.2;

	FILE *out_traj;
	out_traj=fopen("out_traj.txt","w");

	double traj[N_spots];
	double x0=0.0;
	init_traj(traj,N_spots,x0);

	double out_x_sq;

	out_x_sq=perform_sweeps(traj, N_spots, a, omega, sigma_coef, sigma_sweeps_period,
			acc_rate_up_border, acc_rate_low_border, N_sweeps_waiting, N_sweeps_storing);

	print_traj(out_traj,traj,N_spots);

	fclose(out_traj);
    end=clock();
	printf("termolised <x^2> for omega=%.1lf is: %.4lf\n",omega,out_x_sq);
	printf("TIME: %.2lf ms\n",(double)(end-start)/CLOCKS_PER_SEC*1000);
}