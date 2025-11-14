/*==========================
  BASIC BIT OPERATIONS
==========================*/

b.set(pos);        // set bit to 1                // O(1)
b.reset(pos);      // set bit to 0                // O(1)
b.flip(pos);       // toggle bit                  // O(1)

b.set();           // set all bits to 1           // O(N/64)
b.reset();         // clear all bits              // O(N/64)
b.flip();          // flip all bits               // O(N/64)

bool v  = b.test(pos);  // read bit (checked)     // O(1)
bool v2 = b[pos];       // read bit (faster)      // O(1)


/*==========================
  QUERIES
==========================*/

b.count();         // number of 1 bits            // O(N/64)
b.any();           // exists a 1 bit?             // O(N/64)
b.none();          // all bits are 0?             // O(N/64)
b.size();          // number of bits              // O(1)

/*==========================
  GCC BUILTINS (uint64_t)
==========================*/

__builtin_clz(x);          // leading zero count   // O(1)
__builtin_ctz(x);          // trailing zero count  // O(1)
__builtin_popcount(x);     // popcount             // O(1)

/*==========================
  LIBSTDC++ EXTENSIONS
==========================*/

b._Find_first();           // first 1 bit index    // O(N/64)
b._Find_next(i);           // next 1 after i       // O(N/64)



/*==========================
  CONVERSIONS
==========================*/

b.to_string();     // convert to string           // O(N)
b.to_ulong();      // to unsigned long            // O(1)
b.to_ullong();     // to unsigned long long       // O(1)


/*==========================
  MANUAL EXTENSIONS NEEDED
==========================*/

_Find_prev(i);     // previous 1 before i         // O(N/64)
_Find_last();      // last 1 bit                  // O(N/64)

template <size_t Nb>
struct Bitset : bitset<Nb> {
  template <typename... Args>
  Bitset(Args... args) : bitset<Nb>(args...) {}

  static constexpr int N = Nb;
  static constexpr int array_size = (Nb + 63) / 64;

  union raw_cast {
    array<uint64_t, array_size> a;
    Bitset b;
  };

  int _Find_prev(size_t i) const {
    if (i == 0) return -1;
    if ((*this)[--i] == true) return i;
    size_t M = i / 64;
    const auto& a = ((raw_cast*)(this))->a;
    uint64_t buf = a[M] & ((1ull << (i & 63)) - 1);
    if (buf != 0) return M * 64 + 63 - __builtin_clzll(buf);
    while (M--) {
      if (a[M] != 0) return M * 64 + 63 - __builtin_clzll(a[M]);
    }
    return -1;
  }

  inline int _Find_last() const { return _Find_prev(N); }
};
