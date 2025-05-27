#include <bits/stdc++.h>
using namespace std;

// #pragma GCC optimize("O2,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt")

using ll = long long int;
using ull = unsigned long long int;
using vi = vector<ll>;
using ii = pair<ll,ll>;
using vii = vector<ii>;
using ld = long double;
using Ti = array<int, 3>;

#define eb emplace_back
#define fi first
#define se second


mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

template<class T, class V> 
ostream& operator << (ostream &s, pair<T, V> a){
	s << a.fi << ' ' << a.se; return s;
}

template<class T, class V> 
istream& operator >> (istream &s, pair<T, V> &a){
	s >> a.fi >> a.se; return s;
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

template<class T> 
void input(T a[], int l, int r, istream &s = cin){
	while(l <= r)s >> a[l++];
}

template<class T> 
void output(T a[], int l, int r, bool en = true, ostream &s = cout){
	while(l <= r){ s << a[l++];
		if(l <= r) s << ' ';
	} if(en)s << "\n";
}

const double PI = acos(-1);



//====================================================================//
template<class T>
T getRandInt(T l, T r){
	std::uniform_int_distribution<T> distrib(l, r);
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


void print(const tuple<int, vector<ii>> &t){
	auto [n, e] = t;
	cout << n << " " << e.size() << "\n";
	for(int i = 0; i < (int)e.size(); i++){
		cout << e[i].first << ' ' << e[i].second << "\n";
	}
	
}

const int BATCH_COUNT = 14;
const ii Nrange[BATCH_COUNT] = {
	ii(4, 4),
	ii(6, 6),
	ii(2, 2),
	ii(3, 3),
	ii(2, 20),
	ii(20, 20),
	ii(2, 50),
	ii(50, 50),
	ii(2, 100),
	ii(100, 100),
	ii(2, 200),
	ii(200, 200),
	ii(2, 1000),
	ii(1000, 1000),
};

int main(int argc, char* argv[]){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	// cout << argc << endl;
	int batch = atoi(argv[1]);
	int test = atoi(argv[2]);
	int seed = batch * 786786 + test;
	batch--;
	rng.seed(seed); 
	int nlo = Nrange[batch].first;
	int nhi = Nrange[batch].second;
	if(batch == 3){
		cout << 3 << "\n";
		cout << 2 << " " << 2 << "\n";
		cout << 1 << " " << 3 << "\n";
		return 0;
	}
	int n = getRandInt(nlo, nhi);
	cout << n << "\n";
	cout << getPair(1, n) << "\n";
	cout << getPair(1, n) << "\n";
	
	return 0;
}

