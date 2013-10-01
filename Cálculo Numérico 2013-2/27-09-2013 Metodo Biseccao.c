#include <stdio.h>
#include <math.h>
float absoluto(float x);
float funcao(float x);
float e=2.7182;
int main()
{
    float a = -100;
    float b = 49;
    float fa,fb;
    float eps = 0.001;
    float r, fr;
    int i = 0;
    r = (a+b)/2;
    fr = funcao(r);
    while (absoluto(fr) > eps)
    {
        //printf("A = %f, B = %f, FR = %f\n",a,b,absoluto(fr));
        if(fr * funcao(b) > 0)
            b = r;
        else
            a = r;
        r = (a+b)/2;
        fr = funcao(r);
        i++;
    }
    printf("R = %f",r);
    return 1;
}

float funcao(float x)
{
    return x*x;
}
float absoluto(float x)
{
    if(x < 0)
        return x*(-1);
    else
        return x;
}
