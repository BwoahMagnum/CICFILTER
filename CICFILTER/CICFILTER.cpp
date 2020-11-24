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
    
    util    = U;
    ratio   = (R>0)?R:1;
    stage   = (N>0)?N:1;
    sample  = (M>2)?M:1;
    channel = (W>0)?W:1;
    
    Z_Stage_Comb        = new double[stage];
    Z_Stage_Integrator  = new double[stage];
    
    cout<<"sample actually is "<<sample<<endl;
    for (int i=0; i<stage; i++)
        cout<<Z_Stage_Comb[i]<<endl;
    cout<<"Class CIC_FILTER has been created successfully!"<<endl;
}
CIC_FILTER::~CIC_FILTER(void){
    delete [] Z_Stage_Comb;
    delete [] Z_Stage_Integrator;
    cout<<"Class CIC_FILTER has been eliminated successfully!"<<endl;
}
