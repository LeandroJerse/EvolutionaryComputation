#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double pi = 3.1415;

double goal(double x, double y){
   double function = pow((1-x),2)+100*pow((y-pow(x,2)),2);
   return function;
}

void ee(int MaxGeneraction, double *father, double *mother,double* avarageFather, double* avarageMother,double* menDeviation, double* womenDeviation){
    int count = 0;
    double vectorMen[MaxGeneraction+1],vectorWomen[MaxGeneraction+1];
    vectorMen[0]=*father;
    vectorWomen[0]=*mother;

    while (count<MaxGeneraction)
    {
        double noiseFather, noiseMother;
        do {
            noiseFather = (double)rand() / (double)RAND_MAX * 1.5 - 1.5;
        } while (*father+noiseFather<-1.5||*father+noiseFather>1.5);

        do {
            noiseMother = (double)rand() / (double)RAND_MAX * 2.5 - 0.5;
        } while (*mother+noiseMother< -0.5||*mother+noiseMother> 2.5);

     
        
    

        double son = *father+noiseFather;
        double daughter = *mother+noiseMother;

        while ((son + daughter-2)>0)
        {
            if (son>-1.5)
            {
                son-=((double)rand() / (double)RAND_MAX * son + 0.01);;
            }
             if (daughter>-0.5)
            {
                daughter-=((double)rand() / (double)RAND_MAX * daughter + 0.01);
            }
        }
        *avarageFather+=son;
        vectorMen[count+1]= son;
        *avarageMother+=daughter;
        vectorWomen[count+1] = daughter;
        
        printf("Generation:%d\tX:%lf\tY:%lf\tf(X,Y):%lf\n",count+1,son,daughter,goal(son,daughter));
    
        if(goal(son,*mother)<goal(*father,*mother)){
            printf("\tBest combination son: %lf\n",son);
            *father = son;
        }
        if (goal(*father, daughter)<goal(*father,*mother))
        {
            printf("\tBest combination daughter: %lf\n",daughter);
            *mother=daughter;
        }

        count++;
    }

    *avarageFather/=MaxGeneraction;
    *avarageMother/=MaxGeneraction;

    for (int i = 0; i <= MaxGeneraction; i++)
    {
        *menDeviation += pow((vectorMen[i]-*avarageFather),2);
        *womenDeviation +=pow((vectorWomen[i]-*avarageMother),2);
        
    }
    *womenDeviation= sqrt((*womenDeviation/(MaxGeneraction+1)));
    *menDeviation = sqrt((*menDeviation/(MaxGeneraction+1)));
    

}


int main(int argc, char const *argv[])
{
    int maxGeneration;
    double father=0,mother = 0,bestFather,avarageFather =0,avarageMother=0,menDeviation=0,womanDeviation=0;
    printf("Type the number of generations:\t");
    scanf("%d",&maxGeneration);
    do
    {
    printf("Type the X initial number, between -1.5 and 1.5;\n");
    scanf("%lf",&father);
    
            while (father>1.5 || father <-1.5)
    {
        printf("Type again:\t");
        scanf("%lf",&father);
    }
    printf("Type the Y initial number, between -0.5 and 2.5;\n");
    scanf("%lf",&mother);
    while (mother>2.5 || mother <-0.5)
    {
        printf("Type again:\t");
        scanf("%lf",&mother);
    }
    if (father + mother - 2>0)
    {
        printf("The sum of father and mother must be <= 0, type again:\n");
    }
    
    } while (father + mother - 2>0);
    avarageFather = father;
    avarageMother= mother;
    
    printf("Generation:0\tX:%lf\tY:%lf\tf(X,Y):%lf\n",father,mother,goal(father,mother));
    ee(maxGeneration,&father,&mother,&avarageFather,&avarageMother,&menDeviation,&womanDeviation);

    printf("\n\n------------------------------------------------------------------------------------------------\n-");
    printf("\nMaxGen\tfather\tmother\tson\tdaughter\tBest son\tBest Daughter\t\tAvarage Son\t\tAvarage Daughter\tBest f(x,y)\n%d\t1\t1\t%d\t%d\t\t%lf\t%lf\t\t%lf+-%lf\t%lf+-%lf\t%lf\n",(maxGeneration+1),(maxGeneration),maxGeneration,maxGeneration,father,mother,avarageFather,menDeviation,avarageMother,womanDeviation,goal(father, mother));
    return 0;
}
