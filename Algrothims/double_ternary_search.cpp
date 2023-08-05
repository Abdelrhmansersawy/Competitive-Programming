long double l = 0 , r = 1e9 , mid;
int cnt = 400;
while(cnt--){
  double g = l + (r - l) / 3,
       h = r - (r - l) / 3;
  if(f(g) < f(h)) r = h; // get minumum value
  else l = g;
}
