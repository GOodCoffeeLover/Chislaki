#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <cmath>
#include <functional>

using namespace std;
using f_RtoR = function<double(double)>; // сокращение названия типа по логике f : R -> R

struct spline
{
  f_RtoR f;
  double l, r;
};

const int width = 12;
const string line(width, '-');
void print_hYPQm(const  vector<double>& h, 
                 const  vector<double>& Y,
                 const  vector<double>& P,
                 const  vector<double>& Q,
                 const  vector<double>& m){
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
  vector<double> h(p.size(), 0.0), 
                 Y(p.size(), 0.0), 
                 P(p.size(), 0.0), 
                 Q(p.size(), 0.0),
                 m(p.size(), 0.0);
  for(int i=1; i<p.size(); ++i)
    h[i]=p[i][0]-p[i-1][0];

  for(int i=1; i<p.size()-1; ++i)
    Y[i]= (p[i+1][1]-p[i][1]) /h[i+1] - (p[i][1]-p[i-1][1])/h[i];
  
  for(int i=1; i<p.size()-1; ++i)
    P[i+1]=-h[i+1]/(2*(h[i]+h[i+1]) +P[i]*h[i]);
  
  for(int i=1; i<p.size()-1; ++i)
    Q[i+1]=(6*Y[i]-h[i]*Q[i])/(2*(h[i]+h[i+1])+P[i]*h[i]);
  
  for(int i=p.size()-1; i>0; --i)
    m[i-1]=P[i]*m[i]+Q[i];

  print_hYPQm(h,Y, P, Q, m);
  vector<spline> ans;
  for(int i=1; i<p.size(); ++i)
    ans.push_back({ [p, h, Y, P, Q, m, i](double x0){
    return m[i]*(x0-p[i-1][0])*(x0-p[i-1][0])*(x0-p[i-1][0])/(6.0*h[i]) 
      + m[i-1]*(p[i][0] - x0)*(p[i][0] - x0)*(p[i][0] - x0)/(6.0*h[i]) 
      + (p[i][1] - m[i]*h[i]*h[i]/6.0)*(x0-p[i-1][0])/h[i]
      + (p[i-1][1] - m[i-1]*h[i]*h[i]/6.0)*(p[i][0] - x0)/h[i]; }, p[i-1][0], p[i][0]});
  return ans;  
}


int main(){
  vector<vector<double>> points
 {{ 0.0, 2.0},
  { 1.0, 4.0},
  { 3.0, 6.0},
  { 6.0, 7.0},
  {10.0, 3.0}};
  double x0=2.0;
  vector<spline> vec = make_spline(points);
  cout<<endl;
  cout<<line<<'+'<<line<<'+'<<line<<'+'<<endl;
  cout<<setw(width)<<"i"<<'|'<<setw(width)<<"x"<<'|'<<setw(width)<<"S(x)"<<'|'<<endl;
  cout<<line<<'+'<<line<<'+'<<line<<'+'<<endl;
  
  for(int i=0; i<(vec.size()); ++i){
    cout<<setw(width)<<i<<'|'<<setw(width)<<vec[i].l<<'|'<<setw(width)<<vec[i].f(vec[i].l)<<'|'<<endl;
    if(vec[i].l<x0 && x0<vec[i].r)
          cout<<setw(width)<<' '<<'|'<<setw(width)<<x0<<'|'<<setw(width)<<vec[i].f(x0)<<'|'<<endl;
    cout<<setw(width)<<' '<<'|'<<setw(width)<<vec[i].r<<'|'<<setw(width)<<vec[i].f(vec[i].r)<<'|'<<endl;
    cout<<line<<'+'<<line<<'+'<<line<<'+'<<endl;
  }
  return 0;
}