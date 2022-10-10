#include <stdio.h>
#include <stdlib.h>
#include <math.h>
double Trapezium(double ary[],int, double, double);
double f(double, double ary[], int);
double Simpsons(double ary[],int, double, double);

int main()
{
    int Order;
    double ReadIn;
    double Answer;
    double LowLim;
    double UpLim;
    int Menu1Boo = 0;
    int Menu2Boo = 0;

    while(Menu1Boo != 1){
        printf("What is the order of the polynomial?\n");
        scanf("%i", &Order);
        if (Order > 0){
            Menu1Boo = 1;
        }
        else{
            //To catch if user inputs negative or 0 as the order.
            printf("Input Error - That was not a valid choice.\n");
            printf("\n");
        }
    }
    Order += 1;
    double Coefficients[Order];
    printf("Enter coefficients from highest power to lowest.\n");
    for(int i = 0; i < Order; ++i){
        printf("Please enter coefficient %i.\n", i+1);
        scanf("%lf", &ReadIn);
        Coefficients[i] = ReadIn;
    }
    printf("Enter lower limit of integration.\n");
    scanf("%lf", &LowLim);
    printf("Enter upper limit of integration.\n");
    scanf("%lf", &UpLim);

    printf("Input Complete.\n");

    int Method;
    while(Menu2Boo != 1){
        printf("Choose your method.\n 1: Trapezium Rule,\n 2: Simpson's Rule.\n");
        scanf("%i", &Method);
        switch(Method){
            case 1:
                printf("Trapezium Rule selected.\n");
                Answer = Trapezium(Coefficients, Order, LowLim, UpLim);
                printf("Answer = %lf. \n", Answer);
                Menu2Boo = 1;
                continue;
            case 2:
                printf("Simpson's Rule selected.\n");
                Answer = Simpsons(Coefficients, Order, LowLim, UpLim);
                printf("Answer = %lf. \n", Answer);
                Menu2Boo = 1;
                continue;
            default:
                printf("Input Error - That was not a valid choice.\n");
                printf("\n");
                continue;
        }
    }
    return 0;
}





double Trapezium(double Coefficients[], int Order, double LowLim, double UpLim){
    int n;
    double h;
    double Solution;

    printf("Enter the number of Trapezoids you wish to use.\n");
    scanf("%i", &n);
    printf("All required quantities obtained. Computing result.\n");

    h = (UpLim - LowLim)/n; // Width of each trapezoid.

    int i;
    double y;
    double yValues[n+1];
    double x;
    double xValues[n+1];
    double SummationTrap = 0;

    // Assemble yValues (list) using each x value.
    for (i = 0; i <= n; i++){
        x = LowLim + i*h;
        y = f(x, Coefficients, Order);
        yValues[i] = y;
    }
    for(i = 0; i<= n-1; i++){
        // Accounts for the double counting require in summation of y values in Trapezium Rule.
        //Limiting condition of loop ensures first and last y values are only counted once.
        SummationTrap += yValues[i];
        SummationTrap += yValues[i+1];
    }
    Solution = h/2 * SummationTrap;
    return Solution;
}
double f(double x, double Coefficients[], int Order){
    int i;
    double y = 0;
    for(i = 1; i <= Order; i++){
        // Assembles the polynomial term by term to obtain a value of y for a given x.
        double Term =  pow(x, Order - i);
        y += Coefficients[i-1]*Term;
        }
    return y;
}

double Simpsons(double Coefficients[], int Order, double LowLim, double UpLim){
    double yValues[2];
    double Midx;
    double Solution;

    printf("All required quantities obtained. Computing result.\n");
    // Computing the y vale at each third required for Simpsons rule.
    yValues[0] = f(LowLim, Coefficients, Order);
    Midx = (LowLim + UpLim)/2;
    yValues[1] = f(Midx, Coefficients, Order);
    yValues[2] = f(UpLim, Coefficients, Order);

    // Applying Simpsons rule to obtain answer
    Solution = ((UpLim - LowLim)/6) * (yValues[0] + 4*yValues[1] + yValues[2]);

    return Solution;

}
