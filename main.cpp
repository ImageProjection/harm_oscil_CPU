#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <string>
using namespace std;

int main()
{
    clock_t start,end;
	start=clock();
	srand(time(0));

	const int N_sweep_waiting=8000;
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
	out_traj=fopen("out_traj","w");
	fprintf(out_traj,"testttt\n");

	fclose(out_traj);
    end=clock();
	printf("TIME: %.2lf ms\n",(double)(end-start)/CLOCKS_PER_SEC*1000);
}