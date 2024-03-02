#define type double
#define MapIterator map<type, multiset<type> >::iterator
#define SetIterator multiset<type>::iterator

const int SIZE = 10000; //Maximum number of points 
type x[SIZE], y[SIZE]; //Coordinates of points
int N; //Number of points
double INF = INT_MAX;
double getClosestPair() {
	map<type, multiset<type> > points;
	for (int i = 0; i < N; i++)
		points[x[i]].insert(y[i]);
	double d = INF;
	for (MapIterator xitr1 = points.begin(); xitr1 != points.end(); xitr1++){
	for (SetIterator yitr1 = (*xitr1).second.begin(); yitr1!= (*xitr1).second.end(); yitr1++) {
	type x1 = (*xitr1).first, y1 = *yitr1;
	MapIterator xitr3 = points.upper_bound(x1 + d);
	for (MapIterator xitr2 = xitr1; xitr2 != xitr3; xitr2++) 
	{
		type x2 = (*xitr2).first;
		SetIterator yitr2 = (*xitr2).second.lower_bound(y1 - d);
		SetIterator yitr3 = (*xitr2).second.upper_bound(y1 + d);
		for (SetIterator yitr4 = yitr2; yitr4 != yitr3; yitr4++) {
			if (xitr1 == xitr2 && yitr1 == yitr4)
				continue; //same point		type y2 = *yitr4;
			d = min(d, hypot(x1 - x2, y1 - y2));
		}
	}
	}
	}
	return d;
}
