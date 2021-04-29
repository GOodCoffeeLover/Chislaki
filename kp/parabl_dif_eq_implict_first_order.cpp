#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <functional>
#include <string>
#include <exception>



using namespace std;
using f_RxRtoR = function<double(double, double)>; // сокращение названия типа по логике f : R -> R
using f_RtoR = function<double(double)>; // сокращение названия типа по логике f : R -> R


const int width = 14;
const string line(width, '-');

struct equasion{ // dy/dt = a1*d^2y/dx^2 + a2*dy/dx + a3*y + f(t,x) 
  double a1, a2, a3;
  f_RxRtoR f;  
};

struct edge_cond{ // fi1*dy/dx + fi2*y = f1(t)
  double fi1, fi2;
  f_RtoR f;
};

struct  region{
  double l, r, h;
};


//просто метод прогонки
vector<double> progonka(const vector<vector<double>>& mtrix){
  vector<double> P(mtrix.size()+1, 0.0), 
                 Q(mtrix.size()+1, 0.0), 
                 ans(mtrix.size(), 0.0);
  for(int i=1; i<P.size(); ++i){
    //Pi = -ci/(bi + ai * P(i-1))
    P[i]=-mtrix[i-1][2]/(mtrix[i-1][1] + mtrix[i-1][0]*P[i-1]);
    //cout<<"P["<<i+1<<"] = "<<(P[i])<<endl; 
  }
  //cout<<endl;

  for(int i=1; i<Q.size(); ++i){
    //Qi = (di - ai*Q(i-1)) / (bi + ai * P(i-1))
    Q[i] = (mtrix[i-1][3] - mtrix[i-1][0]*Q[i-1])/(mtrix[i-1][1] + mtrix[i-1][0]*P[i-1]);
    //cout<<"Q["<<i+1<<"] = "<<(Q[i])<<endl;
  }
  
  //xn = qn
  ans[ans.size()-1] = Q[Q.size()-1];
  for(int i=ans.size()-1; i>0; --i)
    //xi = Qi + Pi * X(i+1)
    ans[i-1]=Q[i] + P[i]*ans[i];
  return ans;
}
void implict_grid_method(const equasion& eq, const edge_cond& cl, const edge_cond& cr, const region& rx, const region& rt, f_RtoR cf, vector<vector<double>>& y){
  y.clear();
  y.push_back({});
  int nx = (rx.r - rx.l)/rx.h;
  int nt = (rt.r - rt.l)/rt.h; 
  for(int k=0; k<=nt; k+=1){
    vector<vector<double>> matrix{};
    for(int i=0; i<=nx; i+=1){
      if(k==0){
        y[k].push_back(cf(rx.l+i*rx.h));
        continue;
      }
      if(i==0)
        matrix.push_back({
          0, 
          (rx.h*cl.fi2 - cl.fi1), 
          cl.fi1, 
          cl.f(rt.l+rt.h*k)*rx.h});
      else if(i==nx)
        matrix.push_back({
          -cr.fi1, 
          (rx.h*cr.fi2 + cr.fi1), 
          0, 
          cr.f(rt.l+rt.h*k)*rx.h});
      else
        matrix.push_back({
          (2.0*eq.a1 - rx.h*eq.a2)*rt.h/(2*rx.h*rx.h), 
          (eq.a3*rt.h - 2.0*eq.a1*rt.h/(rx.h*rx.h) - 1.0),
          (2.0*eq.a1 + rx.h*eq.a2)*rt.h/(2*rx.h*rx.h),
          -y[k-1][i] - rt.h*eq.f(rt.l+rt.h*(k), rx.l+rx.h*i)});
    }
    if(k!=0)
    y.push_back(progonka(matrix));
    //y.push_back(vector<double>(nx+1, 0));
    
  }
}


int main(){
  //начальные условия
  equasion eq{2.4, 0, 6.3, [](double t, double x){return (x+3)/(t+5);}};
  region x{-4, 0, 0.8}, 
         t{0, 0.1, 0.025};
  edge_cond cl{5, 4, [](double t){return 78.83185307 + t/(-4.0);}},
            cr{4, 0, [](double t){return 50.26548246 + t*t/(-3.0) - 0.8*t;}};
  f_RtoR cf = [](double x){return 4.0 + 8.0 * sin( 1.57079633 * x );};
  
  //условия примера из методички, решением которого является y = exp(-t)*sin(x)
  // equasion eq{1, 0, 0, [](double t, double x){return 0;}};
  // region x{0, M_PI, M_PI/10.0}, t{0, 2, 0.1};
  // edge_cond cl{0, 1, [](double t){return 0;}},
  //           cr{0, 1, [](double t){return 0;}};
  // f_RtoR cf = [](double x){return sin( x );};
  
  vector<vector<double>> y{};
  
  implict_grid_method(eq, cl, cr, x,t, cf, y);

   
  //cout<<line<<'+'<<line<<'+'<<line<<'+'<<line<<'+'<<endl;
  // for(auto l : y){
  //  for(auto d: l)
  //    cout<<setw(width)<<d<<'|';
  //   cout<<endl;
  // }
  for(int i=0; i<=int((x.r-x.l)/x.h); i+=1)
    cout<<"( "<<x.l+i*x.h<<", "<<y.back()[i] <<((i!=int((x.r-x.l)/x.h))?"),":")\n");
  //cout<<endl;
  //cout<<line<<'+'<<line<<'+'<<line<<'+'<<line<<'+'<<endl;
  
  return 0;
}