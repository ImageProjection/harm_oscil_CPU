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
    end=clock();
	printf("TIME: %.2lf ms\n",(double)(end-start)/CLOCKS_PER_SEC*1000);
}