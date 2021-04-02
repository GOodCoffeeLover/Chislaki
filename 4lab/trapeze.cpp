#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <stdexcept>
#include <functional>
#include <algorithm>
#define endl '\n'

using namespace std;       

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

double int_trapeze(auto f, double l, double r, int n){
  double h = (r-l)/double(n), res=0;
  int width = 12;                           //ширина столбца таблицы
  cout<<setprecision(width-4)<<fixed;       //количество знаков после запятой
  string line(width, '-');                  //нижняя линия ячейки таблицы

  cout<<line<<'+'<<line<<'+'<<endl;
  cout<<setw(width)<<'X'<<'|'<<setw(width)<<'Y'<<'|'<<endl;
  cout<<line<<'+'<<line<<'+'<<endl;
  for(int i=0; i<=n; ++i){
    if(i==0 || i==n)
      res+=h/2.0*f(l+double(i)*h);
    else
      res+=h*f(l+double(i)*h);
    cout<<setw(width)<<l+double(i)*h<<'|'<<setw(width)<<f(l+double(i)*h)<<'|'<<endl;
  }
  cout<<line<<'+'<<line<<'+'<<endl;
  cout<<"h = "<<h<<endl;
  return res;
}

double Runge_Romberg(vector<pair<double, double>> res, int p){
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
  //auto f= [](double x){ return sin(x);};
  auto f= [](double x){ return (-2*x+1)/(x*x+9);};
  //double l=0, r=M_PI/2, h=1.0;
  double l=-4, r=0, h1, h2, h3;
  double res1, res2, res3,res4;
  h1=1.0;
  res1 = int_trapeze(f, l, r,(r-l)/h1);
  cout<<"ans = "<<res1<<endl;
  h2=0.5;
  res2 = int_trapeze(f, l, r,(r-l)/h2);
  cout<<"ans = "<<res2<<endl;
  h3=0.25;
  res3 = int_trapeze(f, l, r,(r-l)/h3);
  cout<<"ans = "<<res3<<endl;
  res4=Runge_Romberg({{res1, h1}, {res2, h2}, {res3, h3}}, 2);
  cout<<"R-R ans = "<<res4<<endl;
  return 0;
}