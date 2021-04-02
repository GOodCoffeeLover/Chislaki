#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

#define endl '\n'

using namespace std;
double lagrange(const vector<vector<double>>& p, double x0){
  double res=0;
  for(int i=0; i<p.size(); ++i){
    double prod = p[i][1];
    for(int j=0; j<p.size(); ++j){
      if(i!=j)
        prod*=(x0-p[j][0])/(p[i][0]-p[j][0]);
    }
    res+=prod;
  }
  return res;
}

int main(){
  vector<vector<double>> points{
    {1, 4},
    {2, 7},
    {3, 4}//,{4, 7}
  };
  double x0=2.5;
  int width = 12;
  cout<<setprecision(width-4)<<fixed;       //количество знаков после запятой
  string line(width, '-');
  
  cout<<line<<'+'<<line<<'+'<<endl;
  cout<<setw(width)<<"x0"<<'|'<<setw(width)<<"L(x0)"<<'|'<<endl;
  cout<<line<<'+'<<line<<'+'<<endl;

  for(int i=0; i<points.size(); ++i){
    if(i==0 && x0 < points[i][0]){
      cout<<setw(width)<<x0<<'|'<<setw(width)<<lagrange(points, x0)<<'|'<<endl;
    }
    cout<<setw(width)<<points[i][0]<<'|'<<setw(width)<<lagrange(points, points[i][0])<<'|'<<endl;
    if( (i>=0 && i<(points.size()-1) 
          && (points[i][0] <x0) && (x0 <points[i+1][0])) 
        ||(i==(points.size()-1) && x0 > points[i][0])){
      cout<<setw(width)<<x0<<'|'<<setw(width)<<lagrange(points, x0)<<'|'<<endl;
     }
  }
  cout<<line<<'+'<<line<<'+'<<endl;
  return 0;
}