//
//  CICFILTER.cpp
//  CICFILTER
//
//  Created by 李彦锋 on 2020/11/23.
//

#include "CICFILTER.hpp"
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

CIC_FILTER::CIC_FILTER(bool U, int W, int R, int N, int M){
    util    = U;
    ratio   = R;
    stage   = N;
    sample  = M;
    channel = W;
}
