/*
	 1157	Online Majority Element In Subarray.
https://leetcode.com/problems/online-majority-element-in-subarray/

Design a data structure that efficiently finds the majority element of a given subarray.
The majority element of a subarray is an element that occurs threshold times or more in the subarray.
Implementing the MajorityChecker class:
MajorityChecker(int[] arr) Initializes the instance of the class with the given array arr.
int query(int left, int right, int threshold) returns the element in the subarray arr[left...right] 
that occurs at least threshold times, or -1 if no such element exists.
 */
class MajorityChecker {
	public:
		struct Node{
			int l, r;
			int val, cnt;
			Node operator + (const Node node) const {
				Node t;
				if(val == node.val)
				{
					t.val = val;
					t.cnt = cnt + node.cnt;
				}else if(cnt > node.cnt)
				{
					t.val = val;
					t.cnt = cnt - node.cnt;
				}
				else{
					t.val = node.val;
					t.cnt = node.cnt - cnt;
				}
				t.l = l, t.r = node.r;
				return t;
			}
		};
		static const int N = 2e4+10;
		Node tr[4*N];
		int a[N], n;
		vector<int> s[N];
		void pushup(int u){
			tr[u] = tr[u<<1] + tr[u<<1|1];
		}
		void build(int u,  int l, int r){
			if(l == r)
				tr[u] = {l, r, a[l], 1};
			else{
				int mid = l+r>>1;
				tr[u].l = l, tr[u].r = r;
				build(u<<1, l, mid), build(u<<1|1, mid+1, r);
				pushup(u);
			}
		}
		Node ask(int u, int l, int r){
			if(tr[u].l >= l&&tr[u].r <= r)
				return tr[u];
			else{
				int mid = tr[u].l + tr[u].r >> 1;
				if(l>mid)
					return ask(u<<1|1,l, r);
				else if(r<=mid)
					return ask(u<<1,l, r);
				else{
					auto left = ask(u<<1, l, r);
					auto right = ask(u<<1|1, l, r);
					return left + right;
				}

			}
		}
		MajorityChecker(vector<int>& arr) {
			n = arr.size();
			for(int i = 0;i<n;i++)
				s[a[i] = arr[i]].push_back(i);
			build(1, 0, n-1);
		}

		int query(int left, int right, int threshold) {
			int val = ask(1, left, right).val;
			if(upper_bound(s[val].begin(), s[val].end(), right) - lower_bound(s[val].begin(), s[val].end(), left) >= threshold)
				return val;
			else return -1;
		}
};

/**
 * Your MajorityChecker object will be instantiated and called as such:
 * MajorityChecker* obj = new MajorityChecker(arr);
 * int param_1 = obj->query(left,right,threshold);
 */
