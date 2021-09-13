void FWT(LL *x,int inv) {
    for(int i=1;i<lim;i<<=1){
        for(int j=0;j<lim;j+=(i<<1))/* xor */
            for(int k=0;k<i;++k) {
                LL y=x[j+k],z=x[j+k+i];
                x[j+k]=inv ? (y+z)*(mod+1)/2%mod : y+z;
                x[j+k+i]=inv ? (y-z)*(mod+1)/2%mod : y-z;
                x[j+k]=(x[j+k]%mod+mod)%mod;
                x[j+k+i]=(x[j+k+i]%mod+mod)%mod;
            }
    }
}
