#include <stdio.h>
#include <math.h>
#include "types.h"

f32 sigmoid(f32 x)
{
    return 1.0f / (1.0f + expf(-x));
}

f32 dsigmoid(f32 y)
{
    return y * (1.0f - y);
}

int main()
{
    f32 input[4][2] = {
        {0,0},{0,1},{1,0},{1,1}
    };

    f32 target[4] = {0,1,1,0};

    /* weights */
    f32 w1=0.5,w2=-0.3,w3=0.8,w4=0.3;
    f32 w5=-0.6,w6=0.7;

    f32 b1=0.1,b2=0.1,b3=0.1;

    f32 lr = 0.5;
    int batch = 4;

    for(int epoch=0; epoch<10000; epoch++)
    {
        /* gradient accumulators */
        f32 gw1=0,gw2=0,gw3=0,gw4=0;
        f32 gw5=0,gw6=0;
        f32 gb1=0,gb2=0,gb3=0;

        for(int i=0;i<batch;i++)
        {
            f32 x1=input[i][0];
            f32 x2=input[i][1];

            /* forward */
            f32 h1=sigmoid(x1*w1+x2*w2+b1);
            f32 h2=sigmoid(x1*w3+x2*w4+b2);

            f32 out=sigmoid(h1*w5+h2*w6+b3);

            /* backprop */
            f32 error=target[i]-out;

            f32 d_out=error*dsigmoid(out);
            f32 d_h1=d_out*w5*dsigmoid(h1);
            f32 d_h2=d_out*w6*dsigmoid(h2);

            /* accumulate gradients */
            gw5 += d_out*h1;
            gw6 += d_out*h2;
            gb3 += d_out;

            gw1 += d_h1*x1;
            gw2 += d_h1*x2;
            gb1 += d_h1;

            gw3 += d_h2*x1;
            gw4 += d_h2*x2;
            gb2 += d_h2;
        }

        /* average & update */
        w5 += lr*(gw5/batch);
        w6 += lr*(gw6/batch);
        b3 += lr*(gb3/batch);

        w1 += lr*(gw1/batch);
        w2 += lr*(gw2/batch);
        b1 += lr*(gb1/batch);

        w3 += lr*(gw3/batch);
        w4 += lr*(gw4/batch);
        b2 += lr*(gb2/batch);
    }

    printf("Results:\n");

    for(int i=0;i<4;i++)
    {
        f32 x1=input[i][0];
        f32 x2=input[i][1];

        f32 h1=sigmoid(x1*w1+x2*w2+b1);
        f32 h2=sigmoid(x1*w3+x2*w4+b2);
        f32 out=sigmoid(h1*w5+h2*w6+b3);

        printf("%f XOR %f = %f\n",x1,x2,out);
    }
}
