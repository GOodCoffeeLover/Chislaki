#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <functional>
#include <string>
#include <exception>

using namespace std;

vector<pair<double, double>> Rugne_Kutt(auto f, double l, double r, double y0, double z0, int n){
  vector<pair<double, double>> res(n+1, {0,0});
  vector<double> z(n+1, 0);
  double h=(r-l)/n, ky1, ky2, ky3, ky4, kz1, kz2, kz3, kz4;
  res[0]={l, y0};
  z[0]=z0;
  const int width = 14;
  const string line(width, '-');
  cout<<setprecision(width-8)<<fixed;       //количество знаков после запятой
  
  cout<<"---+"<<setw(width)<<line<<'+'<<setw(width)<<line<<'+'<<setw(width)<<line<<'+'<<setw(width)<<line<<'+'<<setw(width)<<line<<'+'<<setw(width)<<line<<'+'<<setw(width)<<line<<'+'<<setw(width)<<line<<'+'<<setw(width)<<line<<'+'<<setw(width)<<line<<'+'<<setw(width)<<line<<'+'<<endl;
  cout<<setw(3)<<'i'<<'|'<<setw(width)<<'x'<<'|'<<setw(width)<<'y'<<'|'<<setw(width)<<'z'<<'|'<<setw(width)<<"ky1"<<'|'<<setw(width)<<"kz1"<<'|'<<setw(width)<<"ky2"<<'|'<<setw(width)<<"kz2"<<'|'<<setw(width)<<"ky3"<<'|'<<setw(width)<<"kz3"<<'|'<<setw(width)<<"ky4"<<'|'<<setw(width)<<"kz4"<<'|'<<endl;
  cout<<"---+"<<setw(width)<<line<<'+'<<setw(width)<<line<<'+'<<setw(width)<<line<<'+'<<setw(width)<<line<<'+'<<setw(width)<<line<<'+'<<setw(width)<<line<<'+'<<setw(width)<<line<<'+'<<setw(width)<<line<<'+'<<setw(width)<<line<<'+'<<setw(width)<<line<<'+'<<setw(width)<<line<<'+'<<endl;
    
  for(int i=0; i<n; ++i){
    ky1 = z[i],         kz1 = f(res[i].first, res[i].second, z[i]);
    ky2 = z[i]+h/2.0*kz1, kz2 = f(res[i].first + h/2.0, res[i].second + h/2.0*ky1, z[i] + h/2.0*kz1);
    ky3 = z[i]+h/2.0*kz2, kz3 = f(res[i].first + h/2.0, res[i].second + h/2.0*ky2, z[i] + h/2.0*kz2);
    ky4 = z[i]+h*kz3,   kz4 = f(res[i].first + h, res[i].second + h*ky3, z[i] + h*kz3);
    
    cout<<setw(3)<<i<<'|'<<setw(width)<<res[i].first<<'|'<<setw(width)<<res[i].second<<'|'<<setw(width)<<z[i]<<'|'<<setw(width)<<ky1<<'|'<<setw(width)<<kz1<<'|'<<setw(width)<<ky2<<'|'<<setw(width)<<kz2<<'|'<<setw(width)<<ky3<<'|'<<setw(width)<<kz3<<'|'<<setw(width)<<ky4<<'|'<<setw(width)<<kz4<<'|'<<endl;
    cout<<"---+"<<setw(width)<<line<<'+'<<setw(width)<<line<<'+'<<setw(width)<<line<<'+'<<setw(width)<<line<<'+'<<setw(width)<<line<<'+'<<setw(width)<<line<<'+'<<setw(width)<<line<<'+'<<setw(width)<<line<<'+'<<setw(width)<<line<<'+'<<setw(width)<<line<<'+'<<setw(width)<<line<<'+'<<endl;
    
    res[i+1]={res[i].first + h, res[i].second + h/6*(ky1 + 2*ky2 + 2*ky3 + ky4)};
    z[i+1] =z[i] + h/6*(kz1 + 2*kz2 + 2*kz3 + kz4); 
  }

  cout<<setw(3)<<n<<'|'<<setw(width)<<res.back().first<<'|'<<setw(width)<<res.back().second<<'|'<<setw(width)<<z.back()<<'|'<<setw(width)<<' '<<'|'<<setw(width)<<' '<<'|'<<setw(width)<<' '<<'|'<<setw(width)<<' '<<'|'<<setw(width)<<' '<<'|'<<setw(width)<<' '<<'|'<<setw(width)<<' '<<'|'<<setw(width)<<' '<<'|'<<endl;
  cout<<"---+"<<setw(width)<<line<<'+'<<setw(width)<<line<<'+'<<setw(width)<<line<<'+'<<setw(width)<<line<<'+'<<setw(width)<<line<<'+'<<setw(width)<<line<<'+'<<setw(width)<<line<<'+'<<setw(width)<<line<<'+'<<setw(width)<<line<<'+'<<setw(width)<<line<<'+'<<setw(width)<<line<<'+'<<endl;
    


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

double Runge_Romberg(pair<double, double> r1, pair<double, double>r2, int p){
  return r1.first + (r1.first - r2.first)/(pow(r2.second/r1.second, double(p))-1);
}

int main(){
  auto f = [](double x, double y, double z){return z - 2*y + 3*x-6;};
  double l=-3.0, r=-1.0, y0=-2.0, z0=-6.0, x0=r;
  vector<double> h{0.5, 0.25}; 
  vector<pair<double, double>> reses{};
  vector<pair<double, double>> pnts;
  double yn;

  for(int i=0; i<h.size(); ++i ){
    //cout<<"h"<<i+1<<" = "<<h[i]<<endl;
   	pnts = Rugne_Kutt(f, l, r, y0, z0, (r-l)/h[i]);
    cout<<"h"<<i+1<<" = "<<h[i] <<", y( "<<x0<<" )= "<<(yn=compute_at(pnts, x0))<<endl<<endl;
    reses.push_back({yn, h[i]});
  }
  yn = Runge_Romberg(reses[0], reses[1], 4); 
  cout<<"R-R y( "<<x0<<" )= "<<yn<<endl;
  
 return 0;
}