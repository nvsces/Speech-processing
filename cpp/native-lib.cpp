#include <jni.h>
#include <string>
#include "iostream"
#include "complex"
#include "vector"
#include "algorithm"

typedef std::complex< double> cld;
const double PI=acos(-1.0);


std::vector<std::vector<double >> createMatrix(size_t num,size_t N){
    std::vector<std::vector<double >> y;
    for(size_t i = 0; i < num; ++i)
    {
        std::vector<double > temp(N,0.0);
        y.push_back(temp);
    }
    return y;
}

std::vector<cld > copyVector(std::vector<cld> src,int  a, int  n){
    std::vector<cld> ans(n);
    for (int  i=0;i<n;i++){
        ans[i]=src[i+a];
    }
    return ans;
}

std::vector<double > copyVector(std::vector<double> src, int  a, int  n){
    std::vector<double> ans(n);
    for (int  i=0;i<n;i++){
        ans[i]=src[i+a];
    }
    return ans;
}

std::vector<std::vector<double >>  multiplicationVector( std::vector<std::vector<double >> y, int b, int c, std::vector<double> temp ){
    for (int i=0;i<c; ++i) {
        y[b][i] = temp[i];
    }
    return y;
}

std::vector<int> linspace(int x1, int x2, int n){
    double step=(x2-x1)/(n-1);
    std::vector<int> ans(n);
    for(int i=0;i<n;i++){
        ans[i]=(int) (x1+step*i);
    }
    return ans;
}

std::vector<double> sumSizeVector(std::vector<double> a,std::vector<double> b){
    std::vector<double> ans;
    for (double i : a)
        ans.push_back(i);

    for (double j : b)
        ans.push_back(j);
    return ans;
}

std::vector<double > linspace(double x1, double x2, int n){
    double step=(x2-x1)/(n-1);
    std::vector<double > ans(n);
    for(int i=0;i<n;i++){
        ans[i]=(x1+step*i);
    }
    return ans;
}

int nextpow2(double x){
    return (int ) ceil(log2(x));
}

std::vector<double > logspace(double x1, double x2, int n){
    std::vector<double > helpmas=linspace(x1,x2,n);
    for (int i=0;i<n;++i){
        helpmas[i]=pow(10.0,helpmas[i]);
    }
    return helpmas;
}

std::vector<double> mapdiffAbs(std::vector<double> input,int range){
    std::vector<double> ans(input.size());
    for (size_t i=0; i<input.size();++i){
        ans[i]=abs(input[i]-range);
    }
    return ans;
}

int minIndex(std::vector<double> input){
    int IndexMin=0;
    double minValue=input[0];
    for ( int i=1 ;i<input.size();++i){
        if (input[i]<minValue){
            minValue=input[i];
            IndexMin=i;
        }
    }
    return IndexMin;
}

std::vector<double> diff(std::vector<double> x){
    std::vector<double> ans;
    for (int i=0;i<x.size()-1;++i){
        ans.push_back(x[i+1]-x[i]);
    }
    return ans;
}

int find_last_less(std::vector<double> x,double m){
    int temp=0;
    for (int i=0; i<x.size();++i){
        if (x[i]<m){
            temp=i;
        }
    }
    return temp;
}

std::vector<double> hamming(int sizeWin){
    std::vector<double> win(sizeWin);
    for (int i=0;i<sizeWin;++i){
        win[i]=(0.54-0.46*cos(2*PI*i/sizeWin));
    }
    return win;
}

std::vector<cld > createComplexVector(const std::vector<double >&a,int nfft) {
    std::vector<cld> ca(nfft, cld(0.0, 0.0));
    for (size_t i = 0; i < a.size(); ++i) {
        ca[i] = cld(a[i], 0.0);
    }
    return ca;
}

int max (int a,int b){
    if (a>b) return a;
    else return b;
}

std::vector<cld> mainFFT(const std::vector<cld> &x){
    size_t N=x.size();
    if (N==1)
        return x;
    std::vector<cld> even(N/2,cld(0.0,0.0));
  
    for (int k=0;k<N/2;k++)
        even[k]=x[2*k];
 
    std::vector<cld> q=mainFFT(even);

    std::vector<cld> odd = even;
    for(int k=0; k<N/2;k++)
        odd[k]=x[2*k+1];

    std::vector<cld> r=mainFFT(odd);

    std::vector<cld> y(N,cld(0.0,0.0));

    for(int k=0;k<N/2;k++){
       double kth=-2.0*k*PI/N;
        cld wk=cld(cos(kth),sin(kth));
        cld u = wk*r[k];

        y[k]=wk*r[k]+q[k];
        y[k+N/2]=-wk*r[k]+q[k];
    }
    return y;
}

std::vector<cld> mainIFFT(std::vector<cld> x){
    int N=x.size();
    std::vector<cld> y(N);

    for (int i=0;i<N;i++){
        y[i]=std::conj(x[i]);
    }

    y=mainFFT(y);

    for(int i=0 ; i<N;i++){
        y[i]=std::conj(y[i]);
    }

    for (int i=0; i<N;i++){
        y[i]=y[i]*cld(1.0/N,0);
    }

    return y;
}




std::vector<double> interp1(std::vector<double> linear,std::vector<double> Y,std::vector<double> logspace){
    std::vector<double> interpAns(logspace.size(),0.0);
    int m=0;

    for (int k=0 ; k<logspace.size();++k){
        while (linear[m]<logspace[k]){
            m=m+1;
        }
        interpAns[k]=(Y[m - 1]+(Y[m]-Y[m - 1])*(logspace[k]-linear[m - 1])/(linear[m]-linear[m - 1]));
    }
    return interpAns;
}

std::vector<double> maxIndexAndValue(std::vector<double> x){
    std::vector<double> rezult(2);
    double tempValue=x[0];
    int temIndex=0;
    for (int i=0;i<x.size();++i){
        if (x[i]>tempValue){
            tempValue=x[i];
            temIndex=i;
        }
    }
    rezult[0]=tempValue;
    rezult[1]=temIndex;
    return rezult;
}

int min (int a ,int b){
    if (a>b) return b;
    else return a;
}

std::vector<double>  pef_(const std::vector<double>& x,double fs){

    int windowLength=(int)round(fs*0.052);
    int overlapLength=(int)round(fs*(0.052-0.01));
    double Range[2]{50.0,400.0};
    int oneCast=1;
    int r=x.size();

    int hopLength=windowLength-overlapLength;
    int numHopsFinal=(int)ceil((r-windowLength)/hopLength)+oneCast+1;

    int  N=windowLength;
    int hopSize=hopLength;
    int numHops=(int)ceil(((r-N)/hopSize)+oneCast+1);

    std::vector<std::vector<double >> y = createMatrix(numHops,N);

    for (int hop=0;hop<numHops;hop++){
        int a=hopSize*hop;
        int b=N+hopSize*hop;
        int mbr=min(b,r)-a;
        y= multiplicationVector(y,hop,min(N,mbr),copyVector(x,a,mbr));
    }

    int NFFT=(int)pow(2.0,nextpow2(2*windowLength-1));
    int nCol=y.size();
    double logpred = log10( min(fs / 2 - 1, 4000));

    std::vector<double> logSpaceFrequency=logspace(1.0,logpred,NFFT);
    std::vector<double> linSpaceFrequency=linspace(0.0,fs/2,(int)round(NFFT/2)+1);

    int wBandEdges[2];
    wBandEdges[0]=0;
    wBandEdges[1]=0;

    for (int i=0;i<2;++i){
        wBandEdges[i]=minIndex(mapdiffAbs(logSpaceFrequency,Range[i]));
    }

    std::vector<double> bwTemp;
    bwTemp.reserve(logSpaceFrequency.size()-2);
    for ( int i=0; i<logSpaceFrequency.size()-2;++i){
        bwTemp.push_back((logSpaceFrequency[i+2]-logSpaceFrequency[i])*0.5);
    }

    std::vector<double> bw;
    bw.push_back(bwTemp[0]/NFFT);
    for (int i=0;i<bwTemp.size();++i){
        bw.push_back(bwTemp[i]/NFFT);
    }
    bw.push_back(bwTemp[bwTemp.size()-1]/NFFT);

    int K=10;
    double gamma=1.8;
    int num=round(logSpaceFrequency.size()/2);
    std::vector<double> q=logspace(log10(0.5),log10(K+0.5),num);
    std::vector<double> h(q.size());
    for (int i=0;i<q.size();++i){
        h[i]=1/(gamma-cos(2*PI*q[i]));
    }

    std::vector<double> dArray;
    dArray.push_back(q[0]);
    for (int i=0;i<q.size()-1;++i){
        dArray.push_back((q[i]+q[i+1])/2);
    }
    dArray.push_back(q[q.size()-1]);

    std::vector<double> delta=diff(dArray);

    std::vector<double> hdelta;
    for (size_t i=0;i<h.size();++i){
        hdelta.push_back(h[i]*delta[i]);
    }
    double sumhdelta=0.0;
    double sumdelta=0.0;

    for (size_t i=0;i<hdelta.size();i++){
        sumdelta=sumdelta+delta[i];
        sumhdelta=sumhdelta+hdelta[i];
    }

    double betta=sumhdelta/(sumdelta+delta[delta.size()-1]);

    std::vector<double> aFilt;
    aFilt.reserve(h.size());
    for (double i : h){
        aFilt.push_back(i-betta);
    }
    int numToPad=find_last_less(q,1.0);

    std::vector<double> win=hamming(y[0].size());

    std::vector<std::vector<double >> yw=createMatrix(y.size(),y[0].size());
    std::vector<std::vector<cld >> Ylist;

    for (int i=0; i<y.size();++i){
        for (int j=0;j<y[0].size();++j){
            yw[i][j]=y[i][j]*win[j];
        }
        std::vector<cld> complx=createComplexVector(yw[i],NFFT);
        Ylist.push_back(copyVector(mainFFT(complx),0,complx.size()/2+1));
    }

    std::vector<std::vector<double>> Ylog;

    for ( int i=0;i<Ylist.size();++i){
        std::vector<double > power;
        power.reserve(Ylist[i].size());
        for (int j=0;j<Ylist[i].size();++j){
            power.push_back((std::conj(Ylist[i][j])*Ylist[i][j]).real());
        }
        std::vector<double> tempYLog= interp1(linSpaceFrequency,power,logSpaceFrequency);
        for (int j=0;j<tempYLog.size();++j){
            tempYLog[j]=tempYLog[j]*bw[j];
        }
        Ylog.push_back(tempYLog);
    }
    
    std::vector<std::vector<double >> zer=createMatrix(Ylog.size(),numToPad);
    std::vector<std::vector<cld>> X;

    int mm=max(zer[0].size()+Ylog[0].size(),aFilt.size());
    int mx1= min (wBandEdges[1],mm-1);
    int m2= min(pow(2.0,nextpow2(2*mm-1)),NFFT*4);

    for (int i=0; i< zer.size();++i){
        X.push_back(mainFFT(createComplexVector(sumSizeVector(zer[i],Ylog[i]),m2)));
    }

    std::vector<cld> ylist=createComplexVector(aFilt,m2);
    ylist=mainFFT(ylist);

    std::vector<std::vector<cld>> raz;

    for (int i=0;i<X.size();++i){
        std::vector<cld> razVec;
        razVec.reserve(X[i].size());
        for (int j=0;j<X[i].size();++j){
           razVec.push_back(X[i][j]*std::conj(ylist[j]));
        }
        raz.push_back(razVec);
    }

    std::vector<std::vector<double>> cl;

    for (int i=0; i<raz.size();++i){
        std::vector<cld> ct =mainIFFT(raz[i]);
        std::vector<double> ctReal(ct.size());
        for (int icx=0;icx<ct.size();icx++){
            ctReal[icx]=ct[icx].real();
        }
        cl.push_back(ctReal);
    }

    std::vector<int> lintemp=linspace(1,mx1,mx1);
    std::vector<int> alin =linspace(1,mx1-1,mx1-1);

    std::vector<int> atemp(mx1-1);
    for (int i=0;i<atemp.size();++i){
        atemp[i]=(m2-mx1+alin[i]);
    }

    std::vector<std::vector<double >> rR;
    for (int i=0; i<cl.size();++i){
        std::vector<double> arrayA(atemp.size(),0.0);
        std::vector<double> arrayB(lintemp.size(),0.0);
        for (int j=0;j<lintemp.size();++j){
            if (j<atemp.size()){
                arrayA[j]=cl[i][atemp[j]];
                arrayB[j]=cl[i][lintemp[j]+1];
            } else{
                arrayB[j]=cl[i][lintemp[j]+1];
            }
        }
        rR.push_back(sumSizeVector(arrayA,arrayB));
    }

    std::vector<std::vector<double >> domain;

    for ( int i=0;i<rR.size();++i){
        int nsize=rR[i].size()-(wBandEdges[1]-1);
        std::vector<double> tempDomain(nsize);
        for (int j=0 ;j<nsize;++j){
            tempDomain[j]=rR[i][wBandEdges[1]+j-1];
        }
        domain.push_back(tempDomain);
    }

    int numCol=domain.size();

    std::vector<int> locs(numCol,0);
    std::vector<double> peaks(numCol,0.0);

    int lower=wBandEdges[0];
    int upper=wBandEdges[1];

    for (int c=0 ;c<numCol;++c){
        std::vector<double> tempDomainR(upper-lower);
        for (int j=0;j<tempDomainR.size();++j){
            tempDomainR[j]=domain[c][lower+j];
        }
        std::vector<double> rezMax=maxIndexAndValue(tempDomainR);
        locs[c]=(int)rezMax[1] +lower-1;
        peaks[c]=rezMax[0];
    }

    std::vector<double> f0(locs.size());

    for (int i=0; i<f0.size();++i){
        f0[i]=logSpaceFrequency[locs[i]];
    }


    return f0;
}

size_t findUpperDegreeOfTwo(size_t v){
    size_t n =1 ;
    while (n<v)
        n*=2;
    return n;
}

std::vector<double > jdoubleToVectorDouble(jdouble *pDouble, int n) {
    std::vector<double > ans(n,0.0);
    for( int i=0; i<n; ++i)
        ans[i]=pDouble[i];
    return ans;
}

std::vector<cld> makeVectorIsJdouble(jdouble *pDouble, int n) {
    int sn =1 ;
    while (sn<n)
        sn*=2;
    std::vector<cld> ans(sn,cld(0.0,0.0));
    for( int i=0; i<n; ++i)
        ans[i]=cld (pDouble[i],0.0);
    return ans;
}

extern "C"
JNIEXPORT jdoubleArray JNICALL
Java_com_nvsces_mynative_MainActivity_fftCpp(JNIEnv *env, jobject thiz, jdoubleArray a) {
    int n=env->GetArrayLength(a);

    jdouble * dbl = env->GetDoubleArrayElements(a,nullptr);

    std::vector<cld> av= makeVectorIsJdouble(dbl, n);
    std::vector<cld> rezult=mainFFT(av);
    std::vector<cld> irezult=mainIFFT(rezult);


    double ans[2*av.size()];
    for (int i=0; i<2*n;++i) {
        if (i>n-1)
            ans[i] = rezult[i-n].imag();
        else
            ans[i] = rezult[i].real();

    }
    jdoubleArray jReal;
    jReal = env -> NewDoubleArray(2*n);
    env->SetDoubleArrayRegion(jReal, 0, 2*n, ans);
    env->ReleaseDoubleArrayElements(a, dbl, 0);

    return jReal;
}extern "C"
JNIEXPORT jdoubleArray JNICALL
Java_com_nvsces_mynative_InfoBufferFragment_pefCpp(JNIEnv *env, jobject thiz, jdoubleArray a,
                                                   jdouble fs) {
    int n = env->GetArrayLength(a);

    jdouble *dbl = env->GetDoubleArrayElements(a, nullptr);

    std::vector<double> x = jdoubleToVectorDouble(dbl, n);

    std::vector<double> ans = pef_(x, fs);

    double rezult[ans.size()];
    for (int i=0;i<ans.size();i++){
        rezult[i]=ans[i];
    }

    jdoubleArray f0;
    f0 = env->NewDoubleArray(ans.size());


    env->SetDoubleArrayRegion(f0, 0, ans.size(), rezult);
    env->ReleaseDoubleArrayElements(a, dbl, 0);

    return f0;
}extern "C"
JNIEXPORT jdoubleArray JNICALL
Java_com_nvsces_mynative_InfoBufferFragment_fftCpp(JNIEnv *env, jobject thiz, jdoubleArray a) {
    int n = env->GetArrayLength(a);

    jdouble *dbl = env->GetDoubleArrayElements(a, nullptr);

    std::vector<cld> av = makeVectorIsJdouble(dbl, n);
    std::vector<cld> rezult = mainFFT(av);
    std::vector<cld> irezult = mainIFFT(rezult);


    double ans[2 * av.size()];
    for (int i = 0; i < 2 * n; ++i) {
        if (i > n - 1)
            ans[i] = rezult[i - n].imag();
        else
            ans[i] = rezult[i].real();

    }
    jdoubleArray jReal;
    jReal = env->NewDoubleArray(2 * n);
    env->SetDoubleArrayRegion(jReal, 0, 2 * n, ans);
    env->ReleaseDoubleArrayElements(a, dbl, 0);

    return jReal;
}