mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
ll rnd(){return rng() % N;} // N -> Range of number
