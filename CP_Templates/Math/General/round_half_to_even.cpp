// Rounds x to `decimals` places using round-half-to-even
double round_to(double x, int decimals) {
    double scale = pow(10.0, decimals);
    // rint uses current rounding mode (default = FE_TONEAREST = half-to-even)
    return rint(x * scale) / scale;
}
