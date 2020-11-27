//
// Created by 李彦锋 on 2020/11/25.
//

#ifndef CICFILTER_CICFILTER_H
#define CICFILTER_CICFILTER_H

#define CIC_Interpolation   false
#define CIC_Decimation      true
#define CIC_Front           0
#define CIC_Rear            1
#define CIC_Nuovo           0
#define CIC_Vecchio         1

class CIC_FILTER{
public:
    CIC_FILTER(bool U, int W, int R=1, int N=1, int M=1);
    ~CIC_FILTER();

    int put(double* dataInput);
    int get(double* dataOutput);

private:
    int     ratio;
    int     stage;
    int     sample;
    int     channel;
    bool    util;

    double* Z_Stage_Comb;
    double* Z_Stage_Integrator;
    double* Swing_Buffer;
    double* Mid_Buffer;

    double* SampleIndex[2];
    double* BufIndex[2];


    void Combs();
    void Intergrators();
    static void SwingIndex(double* Index[2]);
};

#endif //CICFILTER_CICFILTER_H
