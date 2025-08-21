// Rounds x to `decimals` places using round-half-to-even
ld round_to(ld x, int decimals) {
    ld scale = powl(10.0L, decimals);
    // rint uses current rounding mode (default = FE_TONEAREST = half-to-even)
    return rintl(x * scale) / scale;
}
