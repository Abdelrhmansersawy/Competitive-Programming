/*
 mobius Function (m)
 if i has a squared factor : m(i) = 0 
 else m(i) = (-1)^r , r : number of distinct prime the i has 
*/
const int N = 1e5;
int mobius[N] , sieve[N];
void gen_mobius(){
  for(int i = 1; i < N; i++) {mobius[i] = sieve[i] = 1;}
  sieve[1] = 0;
  for(long long i = 2; i < N; i++){
    if(sieve[i]){
      for(long long j = i; j < N; j += i){
        sieve[j] = 0;
        mobius[j] = (j % (i * i) == 0) ? 0 : -mobius[j];
      }
    }
  }
}
