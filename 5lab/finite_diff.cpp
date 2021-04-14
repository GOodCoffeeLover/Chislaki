#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <functional>
#include <string>
#include <exception>



using namespace std;

struct condintion{
  double A, B, C;
  
};

const int width = 14;
const string line(width, '-');

vector<double> progonka(const vector<vector<double>>& mtrix){
  vector<double> P(mtrix.size()+1, 0.0), 
                 Q(mtrix.size()+1, 0.0), 
                 ans(mtrix.size(), 0.0);
  
  for(int i=1; i<P.size(); ++i)
    //Pi = -ci/(bi + ai * P(i-1))
    P[i]=-mtrix[i-1][2]/(mtrix[i-1][1] + mtrix[i-1][0]*P[i-1]); 
  
  for(int i=1; i<Q.size(); ++i)
    //Qi = (di - ai*Q(i-1)) / (bi + ai * P(i-1))
    Q[i] = (mtrix[i-1][3] - mtrix[i-1][0]*Q[i-1])/(mtrix[i-1][1] + mtrix[i-1][0]*P[i-1]);
  
  //xn = qn
  ans[ans.size()-1] = Q[Q.size()-1];
  for(int i=ans.size()-1; i>0; --i)
    //xi = Qi + Pi * X(i+1)
    ans[i-1]=Q[i] + P[i]*ans[i];
  return ans;
}

vector<pair<double, double>> Finite_diff(auto F, auto K, auto L, auto M, pair<double, double> seg, condintion c0, condintion cn, int n){
  vector<pair<double, double>> res(n+1, {0, 0});
  double h =(seg.second - seg.first)/n;
  vector<vector<double>> matrix {};
 
  res[0].first = seg.first;
  matrix.push_back({0, -c0.A/h+c0.B, c0.A/h, c0.C});
  for(int i=1; i<n; ++i){
    double x = res[0].first+i*h;
    res[i].first = x; 
    matrix.push_back({K(x)/(h*h)-L(x)/(2*h),  -2.0*K(x)/(h*h)+M(x), K(x)/(h*h)+L(x)/(2*h), F(x)});
  }
  res[n].first = seg.second; 
  matrix.push_back({cn.A/h, -cn.A/h-c0.B, 0, -cn.C});

  cout<<"matrix:\n";
  for(auto l: matrix){
    for(double d: l)
      cout<<setw(width)<<d<<' ';
    cout<<endl;
  }

  vector<double> ans = progonka(matrix);
  for(int i=0; i<=n; ++i)
    res[i].second = ans[i];
  return res;

}

int main(){
  auto F = [](double x){return 2*sqrt(x);};
  auto K = [](double x){return (2*x*x);};
  auto L = [](double x){return (x);};
  auto M = [](double x){return 1;};
  double l=1.0, r=10.0, y0=2.0, yn = 2.0*sqrt(10.0);
 
  cout<<setprecision(width-4)<<fixed;       //количество знаков после запятой
  
  vector<pair<double, double>> pnts = Finite_diff(F, K, L, M, {l, r}, {0, 1, y0}, {0, 1, yn}, 4);
  
  cout<<"---+"<<setw(width)<<line<<'+'<<setw(width)<<line<<'+'<<endl;
  cout<<setw(3)<<'i'<<'|'<<setw(width)<<'x'<<'|'<<setw(width)<<'y'<<'|'<<endl;
  cout<<"---+"<<setw(width)<<line<<'+'<<setw(width)<<line<<'+'<<endl;

  for(int i=0; i<pnts.size(); ++i){
    cout<<setw(3)<<i<<'|'<<setw(width)<<pnts[i].first<<'|'<<setw(width)<<pnts[i].second<<'|'<<endl;
    cout<<"---+"<<setw(width)<<line<<'+'<<setw(width)<<line<<'+'<<endl;
  }
  
  return 0;
}