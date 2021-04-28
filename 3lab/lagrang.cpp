#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

#define endl '\n'

using namespace std;
//метод многочлена лагранжа - просто вычисление многочлена лагранжа
//по формуле L_{n-1}(x0) = sum_{i=1}^n y_i * prod_{k=1, k!=i}^n (x0-x_k)/(x_i - x_k)
double lagrange(const vector<vector<double>>& p, double x0, bool flag){
  //вычисление суммы
  double res=0;
  for(int i=0; i<p.size(); ++i){
    //вычисление произведения
    double prod = 1;
    for(int j=0; j<p.size(); ++j){
      if(i!=j)
        prod*=(x0-p[j][0])/(p[i][0]-p[j][0]);
    }
    //-----------------------------
  //===============================
    //печать многочлена, который мы высчитываем
    if(flag)
      cout<<(i>0? "+": "L("+to_string(x0)+") =")<<" ( "<<p[i][1] <<" ) * ( "<<prod<<" )"<<((i<p.size()-1)? ' ': '\n');
    res+=prod*p[i][1];
  }
  return res;
}

int main(){
  //начальные условия
  vector<vector<double>> points{
    {1, 4},
    {2, 7},
    {3, 4}//,{4, 7}
  };
  double x0=2.5;

  int width = 12;
  cout<<setprecision(width-4)<<fixed;       //количество знаков после запятой
  string line(width, '-');

  //печать многочлена в процессе посчёта значения в точке x0
  lagrange(points, x0, true);
  cout<<endl;
  //печать заголовка таблицы
  cout<<line<<'+'<<line<<'+'<<endl;
  cout<<setw(width)<<"x0"<<'|'<<setw(width)<<"L(x0)"<<'|'<<endl;
  cout<<line<<'+'<<line<<'+'<<endl;

  //печать таблицы значений
  for(int i=0; i<points.size(); ++i){
    if(i==0 && x0 < points[i][0]){
      cout<<setw(width)<<x0<<'|'<<setw(width)<<lagrange(points, x0, false)<<'|'<<endl;
    }
    cout<<setw(width)<<points[i][0]<<'|'<<setw(width)<<lagrange(points, points[i][0], false)<<'|'<<endl;
    if( (i>=0 && i<(points.size()-1) 
          && (points[i][0] <x0) && (x0 <points[i+1][0])) 
        ||(i==(points.size()-1) && x0 > points[i][0])){
      cout<<setw(width)<<x0<<'|'<<setw(width)<<lagrange(points, x0, false)<<'|'<<endl;
     }
  }
  cout<<line<<'+'<<line<<'+'<<endl;

  return 0;//конец.
}