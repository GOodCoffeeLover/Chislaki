#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <functional>
#include <string>
#include <exception>

using namespace std;

vector<pair<double, double>> euler(auto f, double l, double r, double y0, double z0, int n){
  vector<pair<double, double>> res(n+1, {0,0});
  vector<double> z(n+1, 0);
  double h=(r-l)/n;
  res[0]={l, y0};
  z[0]=z0;
  for(int i=0; i<n; ++i){
    res[i+1]={res[i].first + h, res[i].second + h*z[i]};
    z[i+1] =z[i] + h*f(res[i].first, res[i].second, z[i]); 
  }

  const int width = 14;
  const string line(width, '-');
  cout<<setprecision(width-4)<<fixed;       //количество знаков после запятой
  
  cout<<"---+"<<setw(width)<<line<<'+'<<setw(width)<<line<<'+'<<setw(width)<<line<<'+'<<endl;
  cout<<setw(3)<<'i'<<'|'<<setw(width)<<'x'<<'|'<<setw(width)<<'y'<<'|'<<setw(width)<<'z'<<'|'<<endl;
  cout<<"---+"<<setw(width)<<line<<'+'<<setw(width)<<line<<'+'<<setw(width)<<line<<'+'<<endl;

  for(int i=0; i<res.size(); ++i){
    cout<<setw(3)<<i<<'|'<<setw(width)<<res[i].first<<'|'<<setw(width)<<res[i].second<<'|'<<setw(width)<<z[i]<<'|'<<endl;
    cout<<"---+"<<setw(width)<<line<<'+'<<setw(width)<<line<<'+'<<setw(width)<<line<<'+'<<endl;
  }


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
  auto f = [](double x, double y, double z){return -z/(2*x);};
  double l=1.0, r=10.0, y0=2.0, z0=1.0;
  vector<pair<double, double>> pnts = euler(f, l, r, y0, z0, 10);
  
 
  double x0=3.0;
  cout<<"y( "<<x0<<" )= "<<compute_at(pnts, x0)<<endl;
  return 0;
}