#include <stdio.h>
#include <math.h>

float absoluto(float x);
float funcao(float x);
float derivada(float x);

float e=2.7182;
float a = 0;
float b = 1;
float eps = pow(10,-7);
int main()
{
    biseccao();
    //cordas();
    //newton();
    return 1;
}
void cordas()
{
    float fa,fb;
    float r, fr;
    int i = 0;
    fr = (b-a)/2;
    for(i = 0; ; i++)
    {
        printf("CORDAS ITEROU\n\n");
        fr = ((a*funcao(b))-(b*funcao(a)))/(funcao(b) - funcao(a));
        if(funcao(fr)*funcao(b) < 0)
            a = fr;
        else
            b = fr;
        i++;
        if(absoluto(funcao(fr)) < eps)
            break;

    }
    printf("CORDAS RESULTOU EM RAIZ = %f com %d Iteradas\n",fr,i);
}
void newton()
{
    float fr;
    float na = a;
    int i = 0;
    do {

        fr = na;
        na = na - funcao(na)/derivada(na);
        float err = absoluto((na - fr) / na);
        i++;

    }while((float)na+eps <fr);
    printf("NEWTON RESULTOU EM RAIZ = %f com %d Iteradas\n",na,i);
}
void biseccao()
{
    float fa,fb;
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
    printf("BISECCAO RESULTOU EM RAIZ = %f com %d Iteradas\n",r,i);
}
float funcao(float x)
{
    return ((1-(pow((1+x),-12)))/x)-((312000-91051.90)/26000);
}
float derivada(float x)
{
    return 3* pow(x,2);
}
/*float funcao_der1(float x)
{pow((1+x),-12)-((312000-91051.90)/26000)
    return (e^x)*(-1);
}
float funcao_der2(float x)
{
    return (e^x)*(-1);
}*/
float absoluto(float x)
{
    if(x < 0)
        return x*(-1);
    else
        return x;
}
