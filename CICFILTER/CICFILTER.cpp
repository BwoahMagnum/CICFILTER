//
//  CICFILTER.cpp
//  CICFILTER
//
//  Created by 李彦锋 on 2020/11/23.
//

#include "CICFILTER.hpp"
#include <iostream>
using namespace std;
CIC_FILTER::CIC_FILTER(bool U, int W, int R, int N, int M){
    
    if (M>2)
    util    = U;
    ratio   = R;
    stage   = N;
    sample  = M;
    channel = W;
    
    Z_Stage_Comb        = new double[stage];
    Z_Stage_Integrator  = new double[stage];
    for (int i=0; i<stage; i++)
        cout<<Z_Stage_Comb[i]<<endl;
    cout<<"Class CIC_FILTER has been created successfully!"<<endl;
}
CIC_FILTER::~CIC_FILTER(void){
    delete [] Z_Stage_Comb;
    delete [] Z_Stage_Integrator;
    cout<<"Class CIC_FILTER has been eliminated successfully!"<<endl;
}
