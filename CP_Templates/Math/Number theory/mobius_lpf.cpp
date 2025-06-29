const int N = 1e7;
int mobius[N + 1];
int lpf[N + 1]; 
vector<int> primes;
void gen_mobius_lpf() {
    fill(lpf, lpf + N + 1, 0);
    mobius[1] = 1;

    for (int i = 2; i <= N; ++i) {
        if (lpf[i] == 0) {
            lpf[i] = i; 
            mobius[i] = -1; 
            primes.push_back(i);
        }

        for (int p : primes) {
            if (p > lpf[i] || i * p > N) {
                break;
            }
            lpf[i * p] = p;
            if (p == lpf[i]) {
                mobius[i * p] = 0;
            } else {
                mobius[i * p] = -mobius[i];
            }
        }
    }
}
