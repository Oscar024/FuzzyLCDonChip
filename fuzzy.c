/*
 * File:   fuzzy.c
 * Author: OSCAR
 *
 * Created on 2 de noviembre de 2016, 05:34 PM
 */


//#include <xc.h>
#include "fuzzy.h"

void linspace(double x[], double start, double end, int size)
{
   int i;
   for (i=0; i<size; i++)
      x[i] = ( i*end + (size-1-i)*start ) / (size-1);
      return;
}



double minimo(double x[])
{
  int i;
  double min;

  min = x[0];
  for (i = 1; i < SIZE; i++)
    if (x[i] < min)
	  min = x[i];
  return (min);
}

double maximo(double x[])
{
  int i;
  double max;
  max = x[0];
  for (i = 1; i < SIZE; i++)
    if (x[i] > max)
	  max = x[i];
  return (max);
}


double triangular(double a, double b, double c, double x)
{
 double ux=0;
 if(x<=a){
  ux=0;
 }
 if(x>a && x<b){
  ux=(x-a)/(b-a);
 }
 if(x==b){
  ux=1;
 }
 if(x>b && x<c){
  ux = (c-x)/(c-b);
 }
 return ux;
}

void tri_mf(double t_value[],double x[],double a, double b, double c)
{
    int i;
    double temp[SIZE];
    for(i=0; i<SIZE; i++)
        temp[i]= x[i];
    for(i=0; i<SIZE; i++)
        t_value[i]= triangular(a,b,c,x[i]);
    
}
double trapezoidal(double a, double b, double c, double d, double x)
{
     double ux=0;
     if(x<=a){
      ux=0;
     }
     if(x>a && x<b){
      ux=(x-a)/(b-a);
     }
     if(x>=b && x<=c){
      ux=1;
     }
     if(x>c && x<d){
      ux = (d-x)/(d-c);
     }
     if(x>d){
      ux=0;
     }
     return ux;
}



void trap_mf(double t_value[],double x[],double a, double b, double c, double d)
{
    int i;
    double temp[SIZE];
    for(i=0; i<SIZE; i++)
        temp[i]= x[i];
    for(i=0; i<SIZE; i++)
        t_value[i]= trapezoidal(a,b,c,d,x[i]);
    //printArray(t_value,SIZE);
}

void qualified(double y[],double x[], double w)
{
    double min;
    int i;
    min=w;
    for(i=0;i<SIZE;i++){
       if (x[i] < w)
            y[i] = x[i];
       else
            y[i] = w;
    }

    return;
}

void out_mf(double result[],double x[],double y[],double z[])
{
    int i;
    for(i=0; i<SIZE;i++){
        if(x[i] > y[i] && x[i] > z[i])
        {
            //printf("El numero mayor es %d",A);
            result[i]=x[i];
        }
        else
        {
            if( y[i] > x[i] && y[i] > z[i]){
                //printf("El numero mayor es %d",B);
                result[i]=y[i];
            }
            else
            {
                //printf("El numero mayor es %d",C);
                result[i]=z[i];
            }
        }
    }
}

double defuzzy(double x[],double mf[])
{
    double sum1=0, sum2=0,out=0;
    int i;
    for(i=0;i<SIZE; i++)
        sum1+=x[i]*mf[i];
    for(i=0;i<SIZE; i++)
        sum2+=mf[i];
    out=sum1/sum2;
    return out;
}

void fuzzy_system(void)
{
    double ante_mf1[SIZE],cons_mf1[SIZE];
    double ante_mf2[SIZE],cons_mf2[SIZE];
    double ante_mf3[SIZE],cons_mf3[SIZE];
    double x[SIZE],y[SIZE];
    double qualified_cons_mf1[SIZE],qualified_cons_mf2[SIZE],qualified_cons_mf3[SIZE];
    double overall_out_mf[SIZE];
    double w1,w2,w3;
    double output[SIZE];
    int i;
    linspace(x,-10,10,SIZE);
    linspace(y,0,10,SIZE);
    //printArray(x,SIZE);
    //Funciones de membrecia de antecedente
    trap_mf(ante_mf1,x,-20,-15,-6,-3);
    trap_mf(ante_mf2,x,-6,-3,3,6);
    trap_mf(ante_mf3,x,3,6,15,20);

    //Funciones de membrecia de consecuente
    trap_mf(cons_mf1,y,-2.46,-1.46,1.46,2.46);
    trap_mf(cons_mf2,y,1.46,2.46,5,7);
    trap_mf(cons_mf3,y,5,7,13,15);

    //Fuzzy inference system
    for(i=0;i<SIZE;i++){
        w1=trapezoidal(-20,-15,-6,-3,x[i]);
        w2=trapezoidal(-6,-3,3,6,x[i]);
        w3=trapezoidal(3,6,15,20,x[i]);
        qualified(qualified_cons_mf1,cons_mf1,w1);
        qualified(qualified_cons_mf2,cons_mf2,w2);
        qualified(qualified_cons_mf3,cons_mf3,w3);
        out_mf(overall_out_mf,qualified_cons_mf1,qualified_cons_mf2,qualified_cons_mf3);
        output[i]= defuzzy(y,overall_out_mf);
    }
}

double fuzzy_system_single(double input)
{
    double ante_mf1[SIZE],cons_mf1[SIZE];
    double ante_mf2[SIZE],cons_mf2[SIZE];
    double ante_mf3[SIZE],cons_mf3[SIZE];
    double x[SIZE],y[SIZE];
    double qualified_cons_mf1[SIZE],qualified_cons_mf2[SIZE],qualified_cons_mf3[SIZE];
    double overall_out_mf[SIZE];
    double w1,w2,w3;
    double output;
    int i;
    linspace(x,0,100,SIZE);
    linspace(y,0,100,SIZE);
    //printArray(x,SIZE);
    //Funciones de membrecia de antecedente
    trap_mf(ante_mf1,x,-36,-4,14.68,36);
    trap_mf(ante_mf2,x,15.6,33.47,60.7,87.6);
    trap_mf(ante_mf3,x,64,79.76,104,136);

    //Funciones de membrecia de consecuente
    trap_mf(cons_mf1,y,-36,-4,17.59,36);
    trap_mf(cons_mf2,y,14,46,54,86);
    trap_mf(cons_mf3,y,64,85.32,104,136);

    //Fuzzy inference system
    //for(i=0;i<SIZE;i++){
        w1=trapezoidal(-36,-4,14.68,36,input);
        w2=trapezoidal(15.6,33.47,60.7,87.6,input);
        w3=trapezoidal(64,79.76,104,136,input);
        qualified(qualified_cons_mf1,cons_mf1,w1);
        qualified(qualified_cons_mf2,cons_mf2,w2);
        qualified(qualified_cons_mf3,cons_mf3,w3);
        out_mf(overall_out_mf,qualified_cons_mf1,qualified_cons_mf2,qualified_cons_mf3);
        output= defuzzy(y,overall_out_mf);
        return output;
    //}
}

double fuzzy_system_single2(double input)
{
    double ante_mf1[SIZE],cons_mf1[SIZE];
    double ante_mf2[SIZE],cons_mf2[SIZE];
    double ante_mf3[SIZE],cons_mf3[SIZE];
    double x[SIZE],y[SIZE];
    double qualified_cons_mf1[SIZE],qualified_cons_mf2[SIZE],qualified_cons_mf3[SIZE];
    double overall_out_mf[SIZE];
    double w1,w2,w3;
    double output;
    int i;
    linspace(x,-2,2,SIZE);
    linspace(y,0,100,SIZE);
    //printArray(x,SIZE);
    //Funciones de membrecia de antecedente
    tri_mf(ante_mf1,x,-3.6, -2, -0.4);
    tri_mf(ante_mf2,x,-1.6, 0, 1.6);
    tri_mf(ante_mf3,x,0.4, 2, 3.6);

    //Funciones de membrecia de consecuente
    tri_mf(cons_mf1,y,-40, 0, 40);
    tri_mf(cons_mf2,y,10, 50, 90);
    tri_mf(cons_mf3,y,60, 100, 140);

    //Fuzzy inference system
    //for(i=0;i<SIZE;i++){
        w1=triangular(-3.6, -2, -0.4,input);
        w2=triangular(-1.6, 0, 1.6,input);
        w3=triangular(0.4, 2, 3.6,input);
        qualified(qualified_cons_mf1,cons_mf1,w1);
        qualified(qualified_cons_mf2,cons_mf3,w2);
        qualified(qualified_cons_mf3,cons_mf3,w3);
        out_mf(overall_out_mf,qualified_cons_mf1,qualified_cons_mf2,qualified_cons_mf3);
        output= defuzzy(y,overall_out_mf);
        return output;
    //}
}




double fuzzy_system_single1(double input)
{
    double ante_mf1[SIZE],cons_mf1[SIZE];
    double ante_mf2[SIZE],cons_mf2[SIZE];
    double ante_mf3[SIZE],cons_mf3[SIZE];
    double x[SIZE],y[SIZE];
    double qualified_cons_mf1[SIZE],qualified_cons_mf2[SIZE],qualified_cons_mf3[SIZE];
    double overall_out_mf[SIZE];
    double w1,w2,w3;
    double output;
    int i;
    linspace(x,-2,2,SIZE);
    linspace(y,0,100,SIZE);
    //printArray(x,SIZE);
    //Funciones de membrecia de antecedente
    tri_mf(ante_mf1,x,-3.6, -2, -0.4);
    tri_mf(ante_mf2,x,-1.6, 0, 1.6);
    tri_mf(ante_mf3,x,0.4, 2, 3.6);

    //Funciones de membrecia de consecuente
    tri_mf(cons_mf1,y,-40, 0, 40);
    tri_mf(cons_mf2,y,10, 50, 90);
    tri_mf(cons_mf3,y,60, 100, 140);

    //Fuzzy inference system
    //for(i=0;i<SIZE;i++){
        w1=triangular(-3.6, -2, -0.4,input);
        w2=triangular(-1.6, 0, 1.6,input);
        w3=triangular(0.4, 2, 3.6,input);
        qualified(qualified_cons_mf1,cons_mf3,w1);
        qualified(qualified_cons_mf2,cons_mf3,w2);
        qualified(qualified_cons_mf3,cons_mf1,w3);
        out_mf(overall_out_mf,qualified_cons_mf1,qualified_cons_mf2,qualified_cons_mf3);
        output= defuzzy(y,overall_out_mf);
        return output;
    //}
}
