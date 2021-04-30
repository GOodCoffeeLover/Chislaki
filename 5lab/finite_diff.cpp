#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <functional>
#include <string>
#include <exception>



using namespace std;

const int width = 14;
const string line(width, '-');
// краевое условие третьего рода, вида А*y'(a)+B*y(a)=C
struct condintion{
  double A, B, C;
  
};

//просто метод прогонки
vector<double> progonka(const vector<vector<double>>& mtrix){
  vector<double> P(mtrix.size()+1, 0.0), 
                 Q(mtrix.size()+1, 0.0), 
                 ans(mtrix.size(), 0.0);
  
  for(int i=1; i<P.size(); ++i)
    //Pi = -ci/(bi + ai * P(i-1))
    cout<<"P["<<i+1<<"] = "<<(P[i]=-mtrix[i-1][2]/(mtrix[i-1][1] + mtrix[i-1][0]*P[i-1]))<<endl; 
  cout<<endl;

  for(int i=1; i<Q.size(); ++i)
    //Qi = (di - ai*Q(i-1)) / (bi + ai * P(i-1))
    cout<<"Q["<<i+1<<"] = "<<(Q[i] = (mtrix[i-1][3] - mtrix[i-1][0]*Q[i-1])/(mtrix[i-1][1] + mtrix[i-1][0]*P[i-1]))<<endl;
  
  //xn = qn
  ans[ans.size()-1] = Q[Q.size()-1];
  for(int i=ans.size()-1; i>0; --i)
    //xi = Qi + Pi * X(i+1)
    ans[i-1]=Q[i] + P[i]*ans[i];
  return ans;
}

//сам метод конечных разностей
vector<pair<double, double>> Finite_diff(auto F, auto K, auto L, auto M, pair<double, double> seg, condintion c0, condintion cn, int n){
  vector<pair<double, double>> res(n+1, {0, 0}); // создание вектора значений
  double h =(seg.second - seg.first)/n; //определение длины шага
 
  //сохранение "иксов" точек в результирующий вектор и формирование 3х-диагональной матрицы 
  vector<vector<double>> matrix {};
  res[0].first = seg.first;
  matrix.push_back({0, -c0.A/h+c0.B, c0.A/h, c0.C});// первоя строка матрицы 
  for(int i=1; i<n; ++i){
    double x = res[0].first+i*h;
    res[i].first = x; 
    matrix.push_back({K(x)/(h*h)-L(x)/(2*h),  -2.0*K(x)/(h*h)+M(x), K(x)/(h*h)+L(x)/(2*h), F(x)});//строка матрицы со второй до предпоследней
  }
  res[n].first = seg.second; 
  matrix.push_back({cn.A/h, -cn.A/h-c0.B, 0, -cn.C});//последняя строка матрицы
  //печать полученной "матрицы"
  cout<<"matrix:\n";
  cout<<setw(width)<<'a'<<'|'<<setw(width)<<'b'<<'|'<<setw(width)<<'c'<<'|'<<setw(width)<<'d'<<'|'<<endl;
  for(const auto& l: matrix){
    for(const double& d: l)
      cout<<setw(width)<<d<<'|';
    cout<<endl;
  }
  cout<<endl;
  //сохранение "игриков"
  vector<double> ans = progonka(matrix);
  for(int i=0; i<=n; ++i)
    res[i].second = ans[i];
  return res;//ответ

}


int main(){
  //начальные условия
  // auto F = [](double x){return -5*x*x -5*x -1;};
  // auto K = [](double x){return 2;};
  // auto L = [](double x){return -1;};
  // auto M = [](double x){return -4;};
  // double l=1.0, r=2.0, y0=3.0, yn = 5.0, h =0.20;
  // condintion c0{0, 5, y0}, cn{0, 5, yn};
  
  auto F = [](double x){return -4*x*x +1*x -2;};
  auto K = [](double x){return 2;};
  auto L = [](double x){return -2;};
  auto M = [](double x){return 3;};
  double l=-1.0, r=0.0, y0=4.0, yn = 1.0, h =0.20;
  condintion c0{2, 4, y0}, cn{-3, 3, yn};
  


  cout<<setprecision(width-6)<<fixed;       //количество знаков после запятой
  vector<pair<double, double>> pnts = Finite_diff(F, K, L, M, {l, r}, c0, cn, (r-l)/h); //решение уравнения
  
  //пеачать таблицы и шага, при котором решалось уравнение
  cout<<"---+"<<setw(width)<<line<<'+'<<setw(width)<<line<<'+'<<endl;
  cout<<setw(3)<<'i'<<'|'<<setw(width)<<'x'<<'|'<<setw(width)<<'y'<<'|'<<endl;
  cout<<"---+"<<setw(width)<<line<<'+'<<setw(width)<<line<<'+'<<endl;
  for(int i=0; i<pnts.size(); ++i){
    cout<<setw(3)<<i<<'|'<<setw(width)<<pnts[i].first<<'|'<<setw(width)<<pnts[i].second<<'|'<<endl;
    cout<<"---+"<<setw(width)<<line<<'+'<<setw(width)<<line<<'+'<<endl;
  }
  cout<<"h = "<<h<<endl;
  
  return 0;
}