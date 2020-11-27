//
//  CICFILTER.cpp
//  CICFILTER
//
//  Created by ME on 2020/11/23.
//

#include "CICFILTER.hpp"
#include <iostream>
#include <cmath>
#include "mkl.h"
#define ALIGN       64                  // 数据对齐，单位字节
using namespace std;

CIC_FILTER::CIC_FILTER(bool U, int W, int R, int N, int M) {

    util = U;
    ratio = (R > 0) ? R : 1;
    stage = (N > 0) ? N : 1;
    sample = (2 == M) ? 2 : 1;
    channel = (W > 0) ? W : 1;

    Z_Stage_Comb        = (double *) mkl_calloc( sample * stage * channel, sizeof(double), ALIGN );
    Z_Stage_Integrator  = (double *) mkl_calloc( stage * channel         , sizeof(double), ALIGN );
    Swing_Buffer        = (double *) mkl_calloc( 2 * channel             , sizeof(double), ALIGN );
    Mid_Buffer          = (double *) mkl_calloc( channel                 , sizeof(double), ALIGN );
    SampleIndex[CIC_Nuovo]      = Z_Stage_Comb;
    SampleIndex[CIC_Vecchio]    = Z_Stage_Comb + ((sample-1)?(stage * channel):0);

    BufIndex[CIC_Front] = Swing_Buffer;
    BufIndex[CIC_Rear]  = Swing_Buffer + channel;

    // temporarily using if-else,
    // but next version going to replace it with virtual function
}
int CIC_FILTER::put(double *dataInput) {

    cblas_dcopy(channel, dataInput, 1, Mid_Buffer, 1);
    if (CIC_Interpolation == util) Combs();
    else if (CIC_Decimation == util) Intergrators();
    return 0;
}
int CIC_FILTER::get(double* dataOutput){

    if (CIC_Interpolation == util) Intergrators();
    else if (CIC_Decimation == util) Combs();
    cblas_dcopy(channel, Mid_Buffer, 1, dataOutput, 1);
    // 不确定倍数，只记得与ratio stage sample有关
    cblas_dscal(channel, pow(ratio, stage),dataOutput, 1);
    return 0;
}
CIC_FILTER::~CIC_FILTER(){
    mkl_free(Z_Stage_Comb       );
    mkl_free(Z_Stage_Integrator );
    mkl_free(Swing_Buffer       );
    mkl_free(Mid_Buffer         );
    cout<<"Class CIC_FILTER has been eliminated successfully!"<<endl;
}

void CIC_FILTER::Combs() {
    cblas_dcopy(channel, Mid_Buffer, 1, BufIndex[CIC_Front], 1);
    for(int i=0; i< stage; i++){
        vdSub(channel, BufIndex[CIC_Front], SampleIndex[CIC_Vecchio] + i * channel, BufIndex[CIC_Rear]);
        cblas_dcopy(channel, BufIndex[CIC_Front], 1, SampleIndex[CIC_Vecchio] + i * channel, 1);
        SwingIndex(BufIndex);
    }
    SwingIndex(SampleIndex);
    cblas_dcopy(channel, BufIndex[CIC_Front], 1, Mid_Buffer, 1);
}

void CIC_FILTER::Intergrators() {
    cblas_dcopy(channel, Mid_Buffer, 1, BufIndex[CIC_Front], 1);
    for(int i=0; i< stage; i++){
        vdAdd(channel, BufIndex[CIC_Front], Z_Stage_Integrator + i * channel, BufIndex[CIC_Rear]);
        cblas_dcopy(channel, BufIndex[CIC_Rear], 1, Z_Stage_Integrator + i * channel, 1);
        SwingIndex(BufIndex);
    }
    cblas_dcopy(channel, BufIndex[CIC_Front], 1, Mid_Buffer, 1);
}

void CIC_FILTER::SwingIndex(double **Index) {
    double* temp;
    temp     = Index[0];
    Index[0] = Index[1];
    Index[1] = temp;
}



