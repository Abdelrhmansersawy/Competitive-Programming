/**
* Monotonic queue to keep track of the minimum and the maximum
* elements so far in the queue in amortized time of O(1).
*/
template<class T>
class monotonic_queue {
queue<T> qu;
deque<T> mx, mn;
public:
1void push(T v) {
qu.push(v);
while (mx.size() && mx.back() < v) mx.pop_back();
mx.push_back(v);
while (mn.size() && mn.back() > v) mn.pop_back();
mn.push_back(v);
}
void pop() {
if (mx.front() == qu.front()) mx.pop_front();
if (mn.front() == qu.front()) mn.pop_front();
qu.pop();
}
T front() const {
return qu.front();
}
T max() const {
return mx.front();
}
T min() const {
return mn.front();
}
size_t size() const {
return qu.size();
}
