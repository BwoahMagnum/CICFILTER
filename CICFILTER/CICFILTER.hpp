//
//  CICFILTER.hpp
//  CICFILTER
//
//  Created by 李彦锋 on 2020/11/23.
//

#ifndef CICFILTER_hpp
#define CICFILTER_hpp
#define CIC_Interpolation   false
#define CIC_Decimation      true

#include <stdio.h>

class CIC_FILTER{
public:
    CIC_FILTER(bool U, int W=1, int R=1, int N=1, int M=1);
    ~CIC_FILTER();
    // void INIT();
private:
    int     ratio;
    int     stage;
    int     sample;
    int     channel;
    bool    util;
    double* Z_Stage_Comb;
    double* Z_Stage_Integrator;
};

#endif /* CICFILTER_hpp */
