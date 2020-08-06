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
    double traj_new[N_spots];
    int accepted=(sigma_sweeps_period * N_spots)*0.5*(acc_rate_up_border+acc_rate_low_border);//to not update on first
    double sigma=sqrt(0.5/omega);
    double acc_rate,x_old,x_new,gamma,prob_acc,S_new,S_old,sq_x_sum;
    double A=1.0+a*a*omega*omega*0.5;
    double B;
    //WAITING SWEEPS
    //STORING SWEEPS
    for (int sweeps_counter = 0; sweeps_counter < N_sweeps_storing; sweeps_counter++)
    {
        //update sigma
        if (sweeps_counter % sigma_sweeps_period == 0)
        {
            acc_rate=(double) accepted / (sigma_sweeps_period * N_spots);
            if (acc_rate < acc_rate_low_border)
            {
                sigma/=sigma_coef;
            }
            else if (acc_rate > acc_rate_up_border)
            {
                sigma*=sigma_coef;
            }
            accepted=0;            
        }        
        //local updates
        for (int i = 0; i < N_spots; i++)
        {
            x_old=traj[i];
            x_new=norm_dist(x_old,sigma);
			B=(traj[(i-1+N_spots)%N_spots]+traj[(i+1+N_spots)%N_spots]);
            S_old=(A*x_old*x_old-B*x_old)/a;				
			S_new=(A*x_new*x_new-B*x_new)/a;
            if (S_new < S_old)
            {
                traj_new[i]=x_new;
                accepted++;
            }
            else
            {
                prob_acc=1.0/exp(S_new-S_old);
                gamma=(long double) rand() / RAND_MAX;
                if (gamma < prob_acc)
                {
                    traj_new[i]=x_new;
                    accepted++;
                }
                else
                {
                    traj_new[i]=x_old;
                }                
            }            
        }        
        //finding <x^2> over sweep
        sq_x_sum+=av_sq_x(traj_new,N_spots);
        //new -> old
        for (int i = 0; i < N_spots; i++)
        {
            traj[i]=traj_new[i];
        }        
    }
    return (double) sq_x_sum/N_sweeps_storing;   
}
