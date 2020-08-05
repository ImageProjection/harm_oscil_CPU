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

	FILE *out_traj;
	out_traj=fopen("out_traj.txt","w");

	double traj[N_spots];
	double x0=0.0;
	init_traj(traj,N_spots,x0);
	print_traj(out_traj,traj,N_spots);

    printf("av_sq_x=%.3lf",av_sq_x(traj,N_spots));
	fclose(out_traj);
    end=clock();
	printf("TIME: %.2lf ms\n",(double)(end-start)/CLOCKS_PER_SEC*1000);
}