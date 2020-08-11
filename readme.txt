1 This will only find <x^2> for 1 omega
//2 Then from that this will be expanded to multiple omega
3 then paralelise it, by hand check for various omega's
4 switch to 2well potential

actually
1 This will only find <x^2> for 1 omega
4 switch to 2well potential
5 parallelise 2well potential, probably refactoring algo a bit

cpu version of 2 well potential
runs in 460 seconds (for 4000 N_spots)
    in 114 seconds for N=1024 a=0.08

later possibly make multiblock kernel for longer trajectories
