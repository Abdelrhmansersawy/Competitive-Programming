# (Undo, Change, Do) Technique 


## تعالي نأخد بروبليم و نحاول نشوف أزاي ممكن نستخدم التكنيك ده.
## Problem:
given a binary string $s$ (consisting of only $0$ or $1$) of length $n$. define $F(i)$ as the number of all indices $j$ such that ($1 <= j <= i$) and $a[j] = a[i]$.
The beauty of the array is $$\left( Beauty = \sum_{i=1}^n F(i) \right)$$
You have to perform this operation at most 1 time.

Operation: choose any index $i$ such that ($1<= i <= n$) and flip $s_i$.

Your target is to find the maximum beauty of the array using this operation.
### Input:
The first line contains only an integer $n$, $1 <= n <= 10^6$.

The Second line contains a binary string $s$ only length $n$. 
### Output:
one line contains the maximum beauty of the array using this operation.
***
## الحل
من طرق حل المسألة ده أنك تجرب جميع الاحتمالات و في كل أحتمال تحاول تجيب ال current beauty و تعمل maximuize ل Maximum beauty
فعشان تجرب جميع الأحتمالات ده هتأخد $O(n)$ فأنت المطلوب منك الأن انك تجيب ال current beauty في $O(1)$  لكل $i , (1 <= i <= n)$ و عشان نعمل حاجه زي كدا نستخدم التكنيك ده.
### طب ازاي؟
ببساطة التكنيك فكرتة أنك في الاول تحسب ال beauty بتاع الاراي و تجزنة في متغير و ليكن $beauty$.
```c++
int n; cin >> n;
string s; cin >> s;
long long cnt[2] = {} , beauty = 0;
for(int i = 0; i < n; i++){
  cnt[s[i] - '0']++;
  beauty += cnt[s[i] - '0'];
}
```
و أنت دلوقتي عايز تحسب قيمة ال beauty لو عملت flip ل $s_i$ و تحسبها في $O(1)$
هنحسب القيمة ده علي 3 خطوات.
تعالي الأول نعرف 2 اراي هنستخدمها و احنا بنجرب جميع الاحتمالات

pre[2] =  number of $0 , 1$ before index $i$.

suff[2] =  number of $0 , 1$ after index $i$.
### 1 - تعمل undo 
يعني أية (تشوف القيمة ال $s_i$ في ال beauty و تطرحها من beauty.
في مسألة هنا هيكون بالشكل ده: المقدار ده هيساوي:

(Number of indices $j$ such that $i <= j <= n$ and $s[j] = s[i]$) $+$ (Number of indices $j$ such that $1<= j < i$ and $s[j] = s[i]$)

### 2 - تعمل change 
تعمل flip ل $s_i$.
### 3 - تعمل do 
تشوف بعد لما عملت flip ل $s_i$ تشوف ده هيغير مبقدار أد اية في قيمة ال beauty و تزود المقدار ده علي beauty.
في مسألة هنا هيكون بالشكل ده: المقدار ده هيساوي:


(Number of indices $j$ such that $i <= j <= n$ and $s[j] = s[i]$) $+$ (Number of indices $j$ such that $1<= j < i$ and $s[j] = s[i]$)

بالشكل ده تكون جبت ال current beauty في  $O(1)$ 
### الكود:
```c++
int n; cin >> n;
string s; cin >> s;
long long cnt[2] = {} , beauty = 0;
long long pre[2] = {} , suff[2] = {};
for(int i = 0; i < n; i++){
  cnt[s[i] - '0']++;
  beauty += cnt[s[i] - '0'];
  suff[s[i] - '0']++;
}
long long max_beauty = beauty; // do 0 operation
for(int i = 0; i < n; i++){
  long long cur_beauty = beauty;
  int ch = s[i] - '0';
  // undo
  cur_beauty -= pre[ch] + suff[ch];
  // change
  ch = 1 - ch; // flipping
  // Do
  cur_beauty += pre[ch] + suff[ch] + 1;
  // update prefix, suffix
  suff[s[i] - '0']--;
  pre[s[i] - '0']++;
  // maximize the maximum beauty
  max_beauty = max(max_beauty , cur_beauty);
}
cout << max_beauty;
```
***
## Exercises problems:
[Binary Inversions](https://codeforces.com/problemset/problem/1760/E) [My Solution](https://codeforces.com/contest/1760/submission/217262410)

[Stacked Pearls](https://codeforces.com/gym/104426/problem/E) [My Solution](https://ideone.com/o2ftwO)
