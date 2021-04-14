#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <functional>
#include <string>
#include <exception>



using namespace std;

vector<pair<double, double>> Rugne_Kutt(auto f, double l, double r, double y0, int n){
  vector<pair<double, double>> res(n+1, {0,0});
  double h=(r-l)/n, k1, k2, k3, k4;
  res[0]={l, y0};
   const int width = 14;
  const string line(width, '-');
  cout<<setprecision(width-4)<<fixed;       //количество знаков после запятой
  
  cout<<"---+"<<setw(width)<<line<<'+'<<setw(width)<<line<<'+'<<setw(width)<<line<<'+'<<setw(width)<<line<<'+'<<setw(width)<<line<<'+'<<setw(width)<<line<<'+'<<endl;
  cout<<setw(3)<<'i'<<'|'<<setw(width)<<'x'<<'|'<<setw(width)<<'y'<<'|'<<setw(width)<<"k1"<<'|'<<setw(width)<<"k2"<<'|'<<setw(width)<<"k3"<<'|'<<setw(width)<<"k4"<<'|'<<endl;
  cout<<"---+"<<setw(width)<<line<<'+'<<setw(width)<<line<<'+'<<setw(width)<<line<<'+'<<setw(width)<<line<<'+'<<setw(width)<<line<<'+'<<setw(width)<<line<<'+'<<endl;

  for(int i=0; i<n; ++i){
    k1=f(res[i].first, res[i].second);
    k2=f(res[i].first +h/2.0, res[i].second + h/2.0*k1);
    k3=f(res[i].first +h/2.0, res[i].second + h/2.0*k2);
    k4=f(res[i].first +h, res[i].second + h*k3);

   cout<<setw(3)<<i<<'|'<<setw(width)<<res[i].first<<'|'<<setw(width)<<res[i].second<<'|'<<setw(width)<<k1<<'|'<<setw(width)<<k2<<'|'<<setw(width)<<k3<<'|'<<setw(width)<<k4<<'|'<<endl;
   cout<<"---+"<<setw(width)<<line<<'+'<<setw(width)<<line<<'+'<<setw(width)<<line<<'+'<<setw(width)<<line<<'+'<<setw(width)<<line<<'+'<<setw(width)<<line<<'+'<<endl;

    res[i+1]={res[i].first + h, res[i].second + h/6*(k1+2*k2+2*k3+k4)};
  }

   cout<<setw(3)<<n<<'|'<<setw(width)<<res.back().first<<'|'<<setw(width)<<res.back().second<<'|'<<setw(width)<<' '<<'|'<<setw(width)<<' '<<'|'<<setw(width)<<' '<<'|'<<setw(width)<<' '<<'|'<<endl;
   cout<<"---+"<<setw(width)<<line<<'+'<<setw(width)<<line<<'+'<<setw(width)<<line<<'+'<<setw(width)<<line<<'+'<<setw(width)<<line<<'+'<<setw(width)<<line<<'+'<<endl;
  return res;
}

double compute_at(const vector<pair<double, double>> & pnts, double x0){
  if(x0<pnts[0].first)
    throw logic_error("x0<l");
  if(x0>pnts.back().first)
    throw logic_error("x0>r");

  for(int i=0; i<pnts.size()-1; ++i)
    if(pnts[i].first <=x0 && pnts[i+1].first >=x0)
      return pnts[i].second + (x0 - pnts[i].first)/(pnts[i+1].first - pnts[i].first)*(pnts[i+1].second - pnts[i].second);
}

int main(){
  auto f = [](double x, double y){return y/(2*x);};
  double l=1.0, r=10.0, y0=2.0;
  vector<pair<double, double>> pnts = Rugne_Kutt(f, l, r, y0, 5);
  
  double x0=3.0;
  cout<<"y( "<<x0<<" )= "<<compute_at(pnts, x0)<<endl;
  return 0;
}