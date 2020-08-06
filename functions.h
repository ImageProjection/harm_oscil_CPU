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
    return res/N_spots;    
}

double norm_dist(double x0,double sigma)//possible but highly unlikely ln(0)
{
    long double gamma1,gamma2;
    long double x,result;
    gamma1=(long double) rand() / RAND_MAX;
    gamma2=(long double) rand() / RAND_MAX;
    x=sqrt(-2.0*log(gamma2))*sin(2.0*M_PI*gamma1);
    result=x0+sigma*x;
    return result;
}


double perform_sweeps(double* traj,int N_spots,double a,double omega,double sigma_coef,
    int sigma_sweeps_period, double acc_rate_up_border,double acc_rate_low_border,int N_sweeps_waiting,int N_sweeps_storing)
{
    return 4;
}