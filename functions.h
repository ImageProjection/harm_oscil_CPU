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
