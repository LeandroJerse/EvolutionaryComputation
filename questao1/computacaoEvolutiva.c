#include <stdio.h>
#include <stdlib.h>
#include <math.h>


double pi = 3.1415;

double goal(double x){
   double function = x*sin(10*pi*x)+1;
   return function;
}

double ee(int MaxGeneraction, double father,double* avarage,double* deviation){
    int count = 0;
    double vector[MaxGeneraction+1];
    vector[0]= father;
    
    while (count<MaxGeneraction)
    {

    double noise = (double)rand() / (double)RAND_MAX * 3 - 1;
    while (father+noise<-1||father+noise>2)
    {
        noise = (double)rand() / (double)RAND_MAX * 3 - 1;
    }
    

    double child = father+noise;
    printf("Generation:%d\tX:%lf\tf(X):%lf\n",count+1,child,goal(child));
    *avarage+=child;
    vector[count+1]=child;
    
    if(goal(child)>goal(father)){
    father = child;
    printf("\tBest value(X:%lf,f(X):%lf)\n",father,goal(father));
    }
    count++;

    }
    *avarage/=MaxGeneraction;
    for (int i = 0; i < MaxGeneraction+1; i++)
    {
        *deviation += pow((vector[i]-*avarage),2);
    }
    *deviation= sqrt((*deviation/(MaxGeneraction+1)));
    
    return father;
    
}


int main(int argc, char const *argv[])
{
    int maxGeneration;
    double father=0,bestFather;
    double avarage=0;
    double deviation = 0;
    printf("Type the number of generations:\t");
    scanf("%d",&maxGeneration);
    printf("Type the initial number, between -1 and 2;\n");
    scanf("%lf",&father);
    while (father>2 || father <-1)
    {
        printf("Type again:\t");
        scanf("%lf",&father);
    }
    avarage+=father;
    bestFather=ee(maxGeneration,father, &avarage,&deviation);

    printf("--------------------------------\nMaxGen\tfather\tchild\tBest\t\tAvarage\n%d\t1\t%d\t%lf\t%lf+-%lf",(maxGeneration+1),maxGeneration,bestFather,avarage,deviation);
    
    return 0;
}
