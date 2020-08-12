#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <cstdio>
#include <curand.h>
#include <curand_kernel.h>
using namespace std;

void print_traj(FILE* out_traj,double* traj,int N_spots);
__global__ void perform_sweeps(double* d_traj, int N_spots, double a, double omega,
	double bot,double x0, double sigma_coef, double sigma_sweeps_period,
	double acc_rate_up_border, double acc_rate_low_border, int N_sweeps_waiting, curandState *rng_states);

int main()
{
    clock_t start,end;
	start=clock();

	const int N_sweeps_waiting=800000;
	const double a=0.08;
	const int N_spots=1024;
	//double beta=a*N_spots;
	const double omega=7.0;
	double bot=1.0;
	double x0=bot;

	const int sigma_local_updates_period=2000;
	const int sigma_sweeps_period=ceil((double)sigma_local_updates_period/N_spots);
	const double sigma_coef=1.2;
	const double acc_rate_up_border=0.3;
	const double acc_rate_low_border=0.2;

	FILE *out_traj;
	out_traj=fopen("out_traj.txt","w");

	double* h_traj;
	h_traj=(double*)malloc(N_spots*sizeof(double));
	double* d_traj;
	cudaMalloc((void**)&d_traj, (N_spots*sizeof(double));

	dim3 grid(1,1,1);
	dim3 block(N_spots,1,1);
	
	curandState *devStates;
    cudaMalloc((void**)&devStates, N_spots*sizeof(curandState));

	perform_sweeps(d_traj, N_spots, a, omega, bot, x0, sigma_coef, sigma_sweeps_period,
		acc_rate_up_border, acc_rate_low_border, N_sweeps_waiting, devStates);
	cudamMemcpy(h_traj,d_traj,N_spots*sizeof(double));

	print_traj(out_traj,h_traj,N_spots);

	fclose(out_traj);
    end=clock();
	printf("TIME: %.2lf ms\n",(double)(end-start)/CLOCKS_PER_SEC*1000);
}
