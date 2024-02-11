ll lpf[N],mobius[N];
 
void least_prime_factor()
{
    for(int i=2;i<N;i++)
    {
        if(!lpf[i])
        {
            for(int j=i;j<N;j+=i)
            {
                if(!lpf[j]) lpf[j]=i;
            }
        }
    }
}
 
void Mobius()
{
    for(int i=1;i<N;i++) 
    {
        if(i==1) mobius[i]=1;
        else 
        {
            if(lpf[i/lpf[i]]==lpf[i]) mobius[i]=0;
            else mobius[i]=-1*mobius[i/lpf[i]];
        }
    }
