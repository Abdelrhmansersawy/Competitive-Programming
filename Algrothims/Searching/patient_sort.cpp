void LIS(vector<int> &v , vector<int> &ans){
  vector<int> lis(v.size());
  int cnt = 0;
  for (int i = 0; i < v.size(); ++i) {
    int pos = lower_bound(lis.begin() , lis.begin() + cnt , v[i]) - lis.begin();
    lis[pos] = v[i];
    if(pos == cnt) cnt++;
    ans[i] = pos + 1;
  }
}
