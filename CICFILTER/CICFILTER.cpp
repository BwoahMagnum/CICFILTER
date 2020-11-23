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
    ratio   = R;
    stage   = N;
    sample  = M;
    channel = W;
    cout<<"Class CIC_FILTER has been created successfully!"<<endl;
}
CIC_FILTER::~CIC_FILTER(void){
    
}
