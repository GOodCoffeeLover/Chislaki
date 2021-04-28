#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <functional>
#include <string>
#include <exception>

using namespace std;
//метод эйлера
vector<pair<double, double>> euler(auto f, double l, double r, double y0, int n){         // вычисление n значений значений функции, являющейся
  vector<pair<double, double>> res(n+1, {0,0});                                           // решением диффура y' = f(x,y),
  double h=(r-l)/n;                                                                       // по формуле
  res[0]={l, y0};                                                                         // x_{i+1} = x_i + h
  for(int i=1; i<=n; ++i)                                                                 // y_{i+1} = x_{i+1} + h*f(xi, yi)
    res[i]={res[i-1].first + h, res[i-1].second + h*f(res[i-1].first, res[i-1].second)};  //
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
// функции, относящиеся к уточнению с помощью формулы Рунге
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
  //начальные условия
  auto f = [](double x, double y){return -2 *y + x*x -2;};
  double l=8.0, r=12.0, y0=-1.0, x0=r;
  vector<double> h{1.0, 0.5, 0.4}; 
  //вектор, в который будем складывать результаты и шаги вычисления
  vector<pair<double, double>> reses{};
 

  const int width = 14;
  const string line(width, '-');
  cout<<setprecision(width-4)<<fixed;       //количество знаков после запятой
  

  double yn;
 
  for(int i=0; i<3; ++i){
    //вычисление точек значений решений ду
    vector<pair<double, double>> pnts = euler(f, l, r, y0, (r-l)/h[i]);
    //печать таблицы значений
    cout<<"---+"<<setw(width)<<line<<'+'<<setw(width)<<line<<'+'<<endl;
    cout<<setw(3)<<'i'<<'|'<<setw(width)<<'x'<<'|'<<setw(width)<<'y'<<'|'<<endl;
    cout<<"---+"<<setw(width)<<line<<'+'<<setw(width)<<line<<'+'<<endl;
    for(int i=0; i<pnts.size(); ++i){
      cout<<setw(3)<<i<<'|'<<setw(width)<<pnts[i].first<<'|'<<setw(width)<<pnts[i].second<<'|'<<endl;
      cout<<"---+"<<setw(width)<<line<<'+'<<setw(width)<<line<<'+'<<endl;
    }
    cout<<"h"<<i+1<<" = "<<h[i] <<", y( "<<x0<<" )= "<<(yn=compute_at(pnts, x0))<<endl<<endl; //вывод шага точности и значения в искомой точке

    reses.push_back({yn, h[i]}); //сохранение результата и шага
  }
  
  yn = Runge(reses, 1); //уточнение по формуле Рунге
  
  cout<<"R y( "<<x0<<" )= "<<yn<<endl;
  
  return 0;
}