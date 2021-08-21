Basics:

//  https://cses.fi/problemset/result/505224/
const int maxn = 1000+5;
vector<vector<int>>B(maxn,vector<int>(maxn));
int n;// n * n
void update(int x,int y,int val){
	while( x  <= n ){
		int _y = y;
		while( _y <= n ){
			B[x][_y]+=val;
			_y+=_y&-_y;
		}
		x+=x&-x;
	}
}
int query(int x,int y){
	int s=0;
	while( x > 0 ){
		int _y = y;
		while( _y > 0 ){
			s+=B[x][_y];
			_y-=_y&-_y;
		}
		x-=x&-x;
	}
	return s;
}





-----------------------------------------------------------------------------------------------------------------------------
Problem                   :   https://codeforces.com/contest/341/problem/D
Solution                  :   https://codeforces.com/contest/341/submission/4383473
-----------------------------------------------------------------------------------------------------------------------------

:::NOT YET COMPLETED & TESTED
class BIT{
	/**
	 * Function : add in submatix  : range updation
	            : add at point     : point updation
	            : sum in submatix  : range query
	 * O(logn * longm ) add
	 * O(logn * logm  ) sum
	 **/
	private :vector<vector<int>>B;
	         int N,M;
	public:
	BIT(int N=1e3,int M=1e3)
	{
		B=vector<vector<int>>(N+1,vector<int>(M+1));
		this->N=N;
		this->M=M;
	}
	private:
	int sum(int x,int y)
	{
		int s=0;
		for(int i=x;i>0;i-=i&-i)
		for(int j=y;j>0;j-=j&-j)
		s+=B[i][j];
		return s;
	}
        public : //for point updation
        void add(int x,int y,int val)
	{
		for(int i=x;i<=N;i+=i&-i)
		for(int j=y;j<=M;j+=j&-j)
		B[i][j]+=val;
	}
	public: //range updation
	void matix_add(int x1,int y1,int x2,int y2,int val)
	{
		add(x2,y2,+val);
		add(x1-1,y2,-val);
		add(x2,y1-1,-val);
		add(x1-1,y1-1,+val);
	}
	public: //range query
	int matix_sum(int x1,int y1,int x2,int y2)
	{
		int s=0;
		s+=sum(x2,y2);
		s-=sum(x2,y1-1);
		s-=sum(x1-1,y2);
		s+=sum(x1-1,y1-1);
		return s;
	}
};
