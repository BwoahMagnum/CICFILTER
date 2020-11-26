#include <iostream>
#include "CICFILTER.hpp"

using namespace std;
int main(int argc, const char * argv[]) {
    // insert code here...
    int channel;
    double *y, *z;
    y=NULL;
    channel  =2;
    y = (double* )calloc(channel, sizeof(double));
    CIC_FILTER x(CIC_Interpolation, 1, 1, 3, 3);
    z = x.Output(y);
    cout << "Hello, World!\n";
    // CIC_FILTER(x, 1);
    // ~CIC_FILTER();
    if (NULL!=y)
    {
        free(y);
        y = NULL;
    }
    return 0;
}
