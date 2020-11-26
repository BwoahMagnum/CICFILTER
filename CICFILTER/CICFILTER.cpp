//
//  CICFILTER.cpp
//  CICFILTER
//
//  Created by ME on 2020/11/23.
//

#include "CICFILTER.hpp"
#include <iostream>
#include "mkl.h"
#define ALIGN       64                  // 数据对齐，单位字节
using namespace std;

CIC_FILTER::CIC_FILTER(bool U, int W, int R, int N, int M) {

    util = U;
    ratio = (R > 0) ? R : 1;
    stage = (N > 0) ? N : 1;
    sample = (2 == M) ? 2 : 1;
    channel = (W > 0) ? W : 1;

    Z_Stage_Comb        = (double *) mkl_calloc(sample * stage * channel, sizeof(double), ALIGN);
    Z_Stage_Integrator  = (double *) mkl_calloc(stage * channel         , sizeof(double), ALIGN);
    Swing_Buffer        = (double *) mkl_calloc(2 * channel             , sizeof(double), ALIGN);

    SampleIndex[CIC_Nuovo]      = Z_Stage_Comb;
    SampleIndex[CIC_Vecchio]    = Z_Stage_Comb + ((sample-1)?(stage * channel):0);

    BufIndex[CIC_Front] = Swing_Buffer;
    BufIndex[CIC_Rear]  = Swing_Buffer + channel;

}
double* CIC_FILTER::Output(double* data){
    // Interpolation
    // Comb Stages
    int i;
    cblas_dcopy(channel, data, 1, BufIndex[CIC_Front], 1);
    for(i=0; i< stage; i++){
        vdSub(channel, BufIndex[CIC_Front], SampleIndex[CIC_Vecchio] + i * channel, BufIndex[CIC_Rear]);
        cblas_dcopy(channel, BufIndex[CIC_Front], 1, SampleIndex[CIC_Vecchio] + i * channel, 1);
        SwingIndex(BufIndex);
    }
    SwingIndex(SampleIndex);
    // 有个升速率的过程，还是要将Comb和Integrator拆开
    // Integrator Stages
    for(i=0; i< stage; i++){
        vdAdd(channel, BufIndex[CIC_Front], Z_Stage_Integrator + i * channel, BufIndex[CIC_Rear]);
        cblas_dcopy(channel, BufIndex[CIC_Rear], 1, Z_Stage_Integrator + i * channel, 1);
        SwingIndex(BufIndex);
    }
    return BufIndex[CIC_Front];
}
CIC_FILTER::~CIC_FILTER(void){
    mkl_free(Z_Stage_Comb       );
    mkl_free(Z_Stage_Integrator );
    mkl_free(Swing_Buffer       );
    cout<<"Class CIC_FILTER has been eliminated successfully!"<<endl;
}

void CIC_FILTER::SwingIndex(double **Index) {
    double* temp;
    temp     = Index[0];
    Index[0] = Index[1];
    Index[1] = temp;
}
