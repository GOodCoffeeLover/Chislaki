#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

#define endl '\n'

using namespace std;
//материал взят с 
//http://www.machinelearning.ru/wiki/index.php?title=%D0%98%D0%BD%D1%82%D0%B5%D1%80%D0%BF%D0%BE%D0%BB%D1%8F%D1%86%D0%B8%D1%8F_%D0%BF%D0%BE%D0%BB%D0%B8%D0%BD%D0%BE%D0%BC%D0%B0%D0%BC%D0%B8_%D0%9B%D0%B0%D0%B3%D1%80%D0%B0%D0%BD%D0%B6%D0%B0_%D0%B8_%D0%9D%D1%8C%D1%8E%D1%82%D0%BE%D0%BD%D0%B0

//нерекурсивный метод Ньютона

//omega_{k,i} = prod_{j=0, j!=k}^i (x_k - x_j)
double omega(const vector<vector<double>>& p, int k, int i){
  double res=1;
  for(int j=0; j<=i; ++j)
    if(j!=k)
      res*=(p[k][0] - p[j][0]);
  return res;
}

//A_i = sum_0^i y_k/omega_{k,i}
double A(const vector<vector<double>>& p, int i){
  double res=0;
  for(int k=0; k<=i; ++k)
    res+=p[k][1]/omega(p, k, i);
  return res;
}



//N_n(x0) = sum_i^n A_i * prod_{k=0, i>0}^{i-1} (x0-x_k)
double newton(const vector<vector<double>>& p, double x0){
  double res=0, prod = 1, a;
  for(int i=0; i<p.size(); ++i){
    a=A(p, i); 
    res +=a*prod;
    prod*=(x0-p[i][0]);
  }
  return res;
}




int main(){
  //начальные условия
  vector<vector<double>> points{
    //{1, 4},
    {2, 7},
    {3, 4},
    {4, 7}
  };
  double x0=2.5;
 
  int width = 12;
  cout<<setprecision(width-4)<<fixed;       //количество знаков после запятой
  string line(width, '-');
 
  //печать коэффициентов
  cout<<"coeficients: ";
  for(int i=0; i<points.size(); ++i)
    cout<<A(points, i)<<' ';
  cout<<endl;
  
  //печать таблицы
  cout<<line<<'+'<<line<<'+'<<endl;
  cout<<setw(width)<<"x0"<<'|'<<setw(width)<<"N(x0)"<<'|'<<endl;
  cout<<line<<'+'<<line<<'+'<<endl;
  for(int i=0; i<points.size(); ++i){
    if(i==0 && x0 < points[i][0]){
      cout<<setw(width)<<x0<<'|'<<setw(width)<<newton(points, x0)<<'|'<<endl;
    }
    cout<<setw(width)<<points[i][0]<<'|'<<setw(width)<<newton(points, points[i][0])<<'|'<<endl;
    if( (i>=0 && i<(points.size()-1) 
          && (points[i][0] < x0) && (x0 <points[i+1][0])) 
        ||(i==(points.size()-1) && x0 > points[i][0])){
      cout<<setw(width)<<x0<<'|'<<setw(width)<<newton(points, x0)<<'|'<<endl;
     }
  }
  cout<<line<<'+'<<line<<'+'<<endl;
  return 0;
}