#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <cmath>
#include <functional>

#define endl '\n'

using namespace std;
using f_RtoR = function<double(double)>; // сокращение названия типа по логике f : R -> R

struct spline{ //структура хранящая функцию сплайна и отрезок, для которог строился этот сплайн
  f_RtoR f;
  double l, r;
};

const int width = 8;
const string line(width, '-');
void print_hYPQm(const  vector<double>& h, 
                 const  vector<double>& Y,
                 const  vector<double>& P,
                 const  vector<double>& Q,
                 const  vector<double>& m){ //просто функция печати промежуточных вычислений

  cout<<setprecision(width-4)<<fixed;       //количество знаков после запятой
  cout<<setw(width)<<line<<'+';
  for(int i=0; i<h.size(); ++i)
    cout<<line<<'+';
  cout<<endl;
  
  cout<<setw(width)<<"h"<<'|';
  for(int i=0; i<h.size(); ++i)
    cout<<setw(width)<<h[i]<<'|';
  cout<<endl;
  
  cout<<setw(width)<<line<<'+';
  for(int i=0; i<h.size(); ++i)
    cout<<line<<'+';
  cout<<endl;

  cout<<setw(width)<<"Y"<<'|';
  for(int i=0; i<Y.size(); ++i)
    cout<<setw(width)<<Y[i]<<'|';
  cout<<endl;
  
  cout<<setw(width)<<line<<'+';
  for(int i=0; i<Y.size(); ++i)
    cout<<line<<'+';
  cout<<endl;

  cout<<setw(width)<<"P"<<'|';
  for(int i=0; i<P.size(); ++i)
    cout<<setw(width)<<P[i]<<'|';
  cout<<endl;
  
  cout<<setw(width)<<line<<'+';
  for(int i=0; i<P.size(); ++i)
    cout<<line<<'+';
  cout<<endl;

  cout<<setw(width)<<"Q"<<'|';
  for(int i=0; i<Q.size(); ++i)
    cout<<setw(width)<<Q[i]<<'|';
  cout<<endl;
  
  cout<<setw(width)<<line<<'+';
  for(int i=0; i<Q.size(); ++i)
    cout<<line<<'+';
  cout<<endl;

  cout<<setw(width)<<"m"<<'|';
  for(int i=0; i<m.size(); ++i)
    cout<<setw(width)<<m[i]<<'|';
  cout<<endl;
  
  cout<<setw(width)<<line<<'+';
  for(int i=0; i<m.size(); ++i)
    cout<<line<<'+';
  cout<<endl;


}


vector<spline> make_spline(const  vector<vector<double>>& p){
  vector<double> h(p.size(), 0.0), // вектор длин отрезков
                 Y(p.size(), 0.0), // вектор значений Y, которые являются правой частью решаемой 3х-диагональной матрицы 
                 P(p.size(), 0.0), // Вектора P и Q 
                 Q(p.size(), 0.0), // для прогонки
                 m(p.size(), 0.0); // mi - вторая производная во внутренней точке получаемая из решения трехдиагональной системы
  for(int i=1; i<p.size(); ++i) // подсчёт длин отрезков
    h[i]=p[i][0]-p[i-1][0];

  for(int i=1; i<p.size()-1; ++i) // подсчёт значений  Y
    Y[i]= (p[i+1][1]-p[i][1]) /h[i+1] - (p[i][1]-p[i-1][1])/h[i];
  
  //метод прогонки
  for(int i=1; i<p.size()-1; ++i) 
    P[i+1]=-h[i+1]/(2*(h[i]+h[i+1]) +P[i]*h[i]);
  
  for(int i=1; i<p.size()-1; ++i)
    Q[i+1]=(6*Y[i]-h[i]*Q[i])/(2*(h[i]+h[i+1])+P[i]*h[i]);
  
  for(int i=p.size()-1; i>0; --i)
    m[i-1]=P[i]*m[i]+Q[i];
  //====================================================

  print_hYPQm(h,Y, P, Q, m); //печать промежуточных значений

  //формирование итогового ответа из полученных сплайнов и их отрезков
  vector<spline> ans; 
  for(int i=1; i<p.size(); ++i)
    ans.push_back({ 
      //спалйн
      [p, h, Y, P, Q, m, i](double x0){
        return m[i]*(x0-p[i-1][0])*(x0-p[i-1][0])*(x0-p[i-1][0])/(6.0*h[i]) 
        + m[i-1]*(p[i][0] - x0)*(p[i][0] - x0)*(p[i][0] - x0)/(6.0*h[i]) 
        + (p[i][1] - m[i]*h[i]*h[i]/6.0)*(x0-p[i-1][0])/h[i]
        + (p[i-1][1] - m[i-1]*h[i]*h[i]/6.0)*(p[i][0] - x0)/h[i]; }, 
        p[i-1][0],//левая граница отрезка 
        p[i][0]});//правая грани
  return ans;  
}

//чисто канонический метод для получения коэффициентов сплайна
vector<double> operator - (vector<double> l, const vector<double>& r ){
  if(l.size()!=r.size())
    return{};
  for(int i=0; i<l.size(); ++i)
    l[i]-=r[i];
  return l;
}

vector<double> operator * (double l, vector<double> r ){
  for(int i=0; i<r.size(); ++i)
    r[i]*=l;
  return r;
}

vector<double> operator * (vector<double> l,const vector<double>& r ){
  for(int i=0; i<r.size(); ++i)
    l[i]*=r[i];
  return l;
}

double sum(vector<double> l){
  double res=0;
  for(double i:l )
    res+=i;
  return res;
}

vector<double> gaus(vector<vector<double>> syst){
  if(syst.size() != (syst[0].size()-1))
    return{};
  vector<double> ans(syst.size());
  for(int i=0; i<syst.size(); ++i){
    for(int j=i+1; j<syst.size(); ++j)
      syst[j]=syst[j]-(syst[j][i]/syst[i][i])*syst[i];
  }

  for(int i=syst.size()-1; i>=0; --i){
    double sum=0;
    for(int j=syst.size()-1; j>i; --j)
      sum+=ans[j]*syst[i][j];
    ans[i]=(syst[i].back()-sum)/syst[i][i];
  }
  return ans;
}

vector<double> kanon(vector<vector<double>> p){
  vector<vector<double>>syst(p.size(), vector<double>(p.size()+1));
  for(int i=0; i<p.size(); ++i ){
    syst[i][0]=1;
    for(int j=1; j<=p.size(); ++j)
      syst[i][j]=p[i][0]*syst[i][j-1];
    syst[i].back() = p[i][1];
  } 
  // cout<<"System"<<endl;
  // for(auto l: syst){
  //   for(double d: l)
  //     cout<<setw(width)<<d<<' ';
  //   cout<<endl;
  // }
  return gaus(syst);
}

void print_pol(vector<double> pol){
  for(int i=0; i<pol.size(); ++i)
    cout<<((i>0 && pol[i]>=0)? '+'+to_string(pol[i]): to_string(pol[i])) <<" * x^"<<i<<' ';
  
  return;
}
//========================================================================
int main(){
  vector<vector<double>> points
 {{ 2.0, -3.0},
  { 3.0, -7.0},
  { 4.0,-10.0},
  { 5.0,-13.0}};//начальные точки
  //double x0=2.0;
  vector<spline> vec = make_spline(points); //получение сплайнов
  cout<<endl;
  //печать заголовка таблицы
  cout<<line<<'+'<<line<<'+'<<line<<'+'<<endl;
  cout<<setw(width)<<"i"<<'|'<<setw(width)<<"x"<<'|'<<setw(width)<<"S(x)"<<'|'<<endl;
  cout<<line<<'+'<<line<<'+'<<line<<'+'<<endl;
  
  //печать таблицы значний сплайнов на границах и в середине отрезков
  for(int i=0; i<(vec.size()); ++i){
    cout<<setw(width)<<i<<'|'<<setw(width)<<vec[i].l<<'|'<<setw(width)<<vec[i].f(vec[i].l)<<'|'<<endl;
    //if(vec[i].l<x0 && x0<vec[i].r)
    cout<<setw(width)<<' '<<'|'<<setw(width)<<(vec[i].l+vec[i].r)/2.0<<'|'<<setw(width)<<vec[i].f((vec[i].l+vec[i].r)/2.0)<<'|'<<endl;
    cout<<setw(width)<<' '<<'|'<<setw(width)<<vec[i].r<<'|'<<setw(width)<<vec[i].f(vec[i].r)<<'|'<<endl;
    cout<<line<<'+'<<line<<'+'<<line<<'+'<<endl;
  }
  //печать самих сплайнов
  for(int i=0; i<(vec.size()); ++i){
    double x1 = vec[i].l,
           x2 = vec[i].l + (vec[i].r-vec[i].l)/3.0,
           x3 = vec[i].l+ 2.0*(vec[i].r-vec[i].l)/3.0,
           x4 = vec[i].r;
    vector<double> pol = kanon({{x1, vec[i].f(x1)},
                              {x2, vec[i].f(x2)}, 
                              {x3, vec[i].f(x3)},
                              {x4, vec[i].f(x4)}});
    cout<<"[ "<<vec[i].l<<", "<<vec[i].r<<" ] : S_{"<<i+1<<"}(x) = "; print_pol(pol); cout<<endl;
  }
  return 0;
}