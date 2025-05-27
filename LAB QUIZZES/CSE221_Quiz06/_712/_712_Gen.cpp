#include <bits/stdc++.h>
using namespace std;

// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt")

using ll = long long int;
using ull = unsigned long long int;
using vi = vector<ll>;
using ii = pair<ll,ll>;
using vii = vector<ii>;
using ld = long double;


mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

template<class T, class V> 
ostream& operator << (ostream &s, pair<T, V> a){
	s << a.first << ' ' << a.second; return s;
}

template<class T, class V> 
istream& operator >> (istream &s, pair<T, V> &a){
	s >> a.first >> a.second; return s;
}

template<class T> 
ostream& operator << (ostream &s, vector<T> a){
	for(int i = 0; i < (int)a.size(); i++){
		if(i > 0)s << ' ' ; 
		s << a[i];
	} return s;
}

template<class T> 
istream& operator >> (istream &s, vector<T> &a){
	for(T &x : a)s >> x; 
	return s;
}


//====================================================================//
template<class T>
T getRandInt(T l, T r){
	std::uniform_int_distribution<T> distrib(l, r);
	return distrib(rng);
}
ld getRandDouble(ld l, ld r){
	std::uniform_real_distribution<> distrib(l, r);
	return distrib(rng);
}
template<class T>
vector<T> getIntArray(int n, T l, T r){
	vector<T> v(n);
	for(int i = 0; i < n; i++){
		v[i] = getRandInt(l, r);
	}
	return v;
}
vector<ld> getDoubleArray(int n, ld l, ld r){
	vector<ld> v(n);
	for(int i = 0; i < n; i++){
		v[i] = getRandDouble(l, r);
	}
	return v;
}
template<class T>
pair<T, T> getPair(T l, T r){
	T L = getRandInt(l, r);
	T R = getRandInt(l, r);
	if(L > R)swap(L, R);
	return {L, R};
}
string getString(int n, int l = 'a', int r = 'z'){
	string ans;
	for(int i = 0; i < n; i++)ans += (char)(getRandInt(l, r));
	return ans;
}
vector<int> getPermutation(int n){
	vector<int> v(n);
	for(int i = 0; i < n; i++){
		v[i] = i + 1;
	}
	shuffle(v.begin(), v.end(), rng);
	return v;
}

//====================================================================//
const int maxN[11] = {0, 3, 10, 50, 100, 500, 1000, 5000, 10000, 10000, 10000}; 

int main(int argc, char* argv[]){
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	assert(argc >= 3);
	int batch = atoi(argv[1]);
	int test = atoi(argv[2]);

	int seed = batch * 100000000 + test;
	rng.seed(seed);
	int n = getRandInt(2, maxN[batch]);
	ll x = n;
	x = x * (n-1);
	x = x/2;
	if(x>10000) x = 10000;
	int lim = x;
	int m = getRandInt(1, lim);
	int s = getRandInt(1, n);
	int d = getRandInt(1, n);
	int k = getRandInt(1, n);
	cout << n << " " << m << " " << s << " " << d << " " <<  k << "\n";
	int sz = 0;
	map<pair <int, int>, int > mp;
	vector<int> e1, e2, w;
	while(sz < m)
	{
		int x = getRandInt(1, n);
		int y = getRandInt(1, n);
		if (x==y) continue;
		if(mp.find(make_pair(x, y))==mp.end() and mp.find(make_pair(y, x))==mp.end())
		{
			mp[make_pair(x,y)] = 1;
			int z = getRandInt(1,1000);
			sz++;
			e1.push_back(x);
			e2.push_back(y);
			w.push_back(z);
		}
	}
	cout << e1 << "\n";
	cout << e2 << "\n";
	cout << w << "\n";
	return 0;
}

