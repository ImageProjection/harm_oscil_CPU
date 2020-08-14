void print_traj(FILE* out_traj,double* traj,int N_spots)
{
    for (int i = 0; i < N_spots; i++)
    {
        fprintf(out_traj,"%lf\n",traj[i]);
    }    
}

__global__ void perform_sweeps(double* d_traj, const int N_spots, double a, double omega,
	double bot,double x0, double sigma_coef, double sigma_sweeps_period,
	double acc_rate_up_border, double acc_rate_low_border, int N_sweeps_waiting, curandState *rng_states)
{
	int id=threadIdx.x;// all threads must be in 1 block
    __shared__ double traj[N_spots];
    __shared__ double traj_new[N_spots];
    __shared__ int accepted_tmp_storage[N_spots];
    __shared__ double sigma;
    __shared__ double acc_rate;
    __shared__ int accepted;//try register type or rely on L1 cache
    double A=1.0-a*a*omega*omega*0.25;//try defferent memory types
    double B;
    double C=a*a*omega*omega/(bot*bot)*0.125;
	double x_old,x_new,S_old,S_new,B,prob_acc,gamma;
    
	curand_init(id, id, 0, &rng_states[id]);
    //init trajectory
    traj[id]=x0;
    accepted_tmp_storage[id]=0;
    if (id==0)
    {
        sigma=0.01*sqrt(0.5/omega);
		accepted=(sigma_sweeps_period*N_spots)*0.5*(acc_rate_low_border+acc_rate_up_border);//to not update on first sweep, when no data to eval acc_rate yet		
    }
    __syncthreads();
    for (int sweeps_counter=0; sweeps_counter < N_sweeps_waiting; sweeps_counter++)
    {
        //update sigma
        if ((sweeps_counter % sigma_sweeps_period) == 0)
		{
			for(int ps=N_spots/2; ps>=1; ps/=2)
			{
				if(id<ps)
					accepted_tmp_st[id]+=accepted_tmp_st[id+ps];
				__syncthreads();
			}
			accepted=accepted_tmp_st[0];
			if (id==0)
			{
				acc_rate=(double)accepted/(sigma_sweeps_period*N_spots);
				if (acc_rate < acc_rate_low_border)
				{
					sigma=sigma/sigma_coef;
				}
				if (acc_rate > acc_rate_up_border)
				{
					sigma=sigma*sigma_coef;
				}
			}
			accepted_tmp_st[id]=0;
		}
		__syncthreads();
        //local update for each
        x_old=traj[id];
        x_new=x_old+sigma*curand_normal_double(&rng_states[id]);
        B=(traj[(id-1+N_spots)%N_spots]+traj[(id+1+N_spots)%N_spots]);
        S_old=(A*x_old*x_old-B*x_old+C*x_old*x_old*x_old*x_old)/a;
        S_new=(A*x_new*x_new-B*x_new+C*x_new*x_new*x_new*x_new)/a;
        if (S_new < S_old)
		{
			traj_new[id]=x_new;
			accepted_tmp_st[id]++;
		}
		else
		{
			prob_acc=1.0/exp(S_new-S_old);
			gamma=curand_uniform_double(&rng_states[id]);
			if (gamma < prob_acc)
			{
				traj_new[id]=x_new;
				accepted_tmp_st[id]++;
			}
		}
		//new -> old
		traj[id]=traj_new[id];
    }    
}
