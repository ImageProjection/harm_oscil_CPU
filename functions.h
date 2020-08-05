void print_traj(FILE* out_traj,double* traj,int N_spots)
{
    for (int i = 0; i < N_spots; i++)
    {
        fprintf(out_traj,"%lf\n",traj[i]);
    }    
}

void init_traj(double* traj, int N_spots, double x0)
{
    for (int i = 0; i < N_spots; i++)
    {
        traj[i]=x0;
    }    
}

double av_sq_x(double* traj, int N_spots)
{
    double res=0;
    for (int i = 0; i < N_spots; i++)
    {
        res+=traj[i]*traj[i];
    }
    return res;    
}

double norm_dist(double x0,double sigma)
{

}


double perform_sweeps(double* traj,int N_spots,double a,double omega,double sigma_coef,
    int sigma_sweeps_period, double acc_rate_up_border,double acc_rate_low_border,int N_sweeps_waiting,int N_sweeps_storing)
{
    return 4;
}