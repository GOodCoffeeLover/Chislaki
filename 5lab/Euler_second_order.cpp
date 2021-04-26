#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <functional>
#include <string>
#include <exception>

using namespace std;

const double eps =0.000000000001;

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
  if(x0<(pnts[0].first-eps)){
    throw logic_error("x0<l");
  }
  if(x0>(pnts.back().first+eps)){
    throw logic_error("x0>r");
  }

  for(int i=0; i<pnts.size()-1; ++i)
    if(pnts[i].first <=x0+eps && pnts[i+1].first >=x0-eps)
      return pnts[i].second + (x0 - pnts[i].first)/(pnts[i+1].first - pnts[i].first)*(pnts[i+1].second - pnts[i].second);
}

double det(const vector<vector<double>>& matrix){
  double res=0, one = 1; 
  if(matrix.size()==1)
    return matrix[0][0];
  for(int i=0; i<matrix.size(); ++i){
    vector<vector<double>>  mini_matrix(matrix.size()-1,vector<double>{});
    for(int j=1; j<matrix.size(); ++j)
      for(int k=0; k<matrix.size(); ++k)
        if(k!=i)
          mini_matrix[j-1].push_back(matrix[j][k]);

    res+=one*matrix[0][i]*det(mini_matrix);
    one*=-1;
  }
  return res;
}


double Runge(vector<pair<double, double>> res, int p){
  vector<vector<double>> M1(res.size(), vector<double>(res.size(), 1.0)),
                         M2(res.size(), vector<double>(res.size(), 1.0));
  for(int i=0; i<res.size(); ++i){
    M1[i][0]=res[i].first;
    for(int j=1; j<res.size(); ++j){
      M1[i][j]=pow(res[i].second, double(p+j-1));
      M2[i][j]=pow(res[i].second, double(p+j-1));
    }
  }
  double D1=det(M1), D2=det(M2); 
  cout<<"D1 = "<<D1<<" D2 = "<<D2<<endl;
  return D1/D2;

}

int main(){
  auto f = [](double x, double y, double z){return  z-2*y + 3*x -6;};
  double l=-3.0, r=-1.0, y0=-2.0, z0=-6.0, x0=r;
  vector<double> h{0.50, 0.250, 0.200}; 
  vector<pair<double, double>> reses{};
  double yn;
  
  for(int i=0; i<h.size(); ++i ){
    
    vector<pair<double, double>> pnts = euler(f, l, r, y0, z0, (r-l)/h[i]);
    cout<<"h"<<i+1<<" = "<<h[i] <<", y( "<<x0<<" )= "<<(yn=compute_at(pnts, x0))<<endl<<endl;
    reses.push_back({yn, h[i]});
  }
  yn = Runge(reses, 1); 
  cout<<"R y( "<<x0<<" )= "<<yn<<endl;
  
  return 0;
}