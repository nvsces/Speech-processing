#include "complex";
#include "vector";

typedef std::complex<long double> cld;
const long double PI=acosl(-1.0);

std::vector<cld> FFTcpp(const std::vector<cld> &x){
    size_t N=x.size();
    if (N==1)
        return x;
    std::vector<cld> even(N/2,cld(0.0,0.0));

    for (int k=0;k<N/2;k++)
        even[k]=x[2*k];

    std::vector<cld> q=FFTcpp(even);

    std::vector<cld> odd = even;
    for(int k=0; k<N/2;k++)
        odd[k]=x[2*k+1];

    std::vector<cld> r=FFTcpp(odd);

    std::vector<cld> y(N,cld(0.0,0.0));

    for(int k=0;k<N/2;k++){
       long double kth=-2.0*k*PI/N;
        cld wk=cld(cosl(kth),sinl(kth));
        //cld u = wk*r[k];

        y[k]=wk*r[k]+q[k];
        y[k+N/2]=-wk*r[k]+q[k];
    }
    return y;
}