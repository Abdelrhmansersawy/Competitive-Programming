vector<int> prime, lpf;
void Sieve(int n) {
    prime.clear();
    lpf.assign(n + 1, 0);

    lpf[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (lpf[i] == 0) {
            lpf[i] = i;
            prime.push_back(i);
        }
        for (int j = 0; j < (int) prime.size() && i * prime[j] <= n; j++) {
            lpf[i * prime[j]] = prime[j];
            if (prime[j] == lpf[i]) break;
        }
    }
}
