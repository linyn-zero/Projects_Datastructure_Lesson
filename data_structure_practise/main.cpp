//#include "test.h"
#include <bits/stdc++.h>
using namespace std;
int check(int mid, vector<int>& p, int m){ // 检查目前间距是否能提供足够数量的间隔数
	int cnt = 0;
	int target = p[0] + mid;
	for(int i = 1; i < p.size(); i++){
		if(p[i] > target){
			cnt++;
			target = p[i] + mid;
		}
	}
	return cnt >= m - 1;
}
int maxDistance(vector<int>& p, int m) {
	sort(p.begin(), p.end());
	int diff = p.back() - p[0];
	if(m == 2) return diff;
	int mn = INT_MAX;
	for(int i=1; i < p.size(); i++){
		mn = min(mn, p[i] - p[i-1]);
	}
	// 最小间隔距离，平均最大间隔距离。我们要使用在两个距离直接二分找到答案
	int l = mn, r = diff / (m - 1);
	while(l <= r) { // [l,r] 闭区间
		int mid = l + (r-l) / 2;
		if(check(mid,p,m)){ // 检查mid是否可行，不可行则减一…
			l = mid + 1;
		} else {
			r = mid - 1;
		}
	}
	return l - 1;
}
int main() {
	vector<int> nums{1,2,3,4,7};
	cout << maxDistance(nums,3);
	return 0;
}
