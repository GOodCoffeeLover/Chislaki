#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <stdexcept>

using namespace std;

const double eps = 0.01;

double dihotomy(auto f, double a,double b, int n){
  if(f(a)*f(b)>=0) throw invalid_argument("f(a)*f(b)>=0");
   
  double c;
  int width = 10;
 
 cout<<setw(3)<<"i"<<'|'
  <<setw(width)<<"a"<<'|'<<setw(width)<<"c"<<'|'<<setw(width)<<"b"<<'|'
  <<setw(width)<<"f(a)"<<'|'<<setw(width)<<"f(c)"<<'|'<<setw(width)<<"f(b)"<<'|'<<endl;
  
  cout<<"---+"
      <<"----------"<<'+'<<"----------"<<'+'<<"----------"<<'+'
      <<"----------"<<'+'<<"----------"<<'+'<<"----------"<<'+'<<endl;

  for(int i=0; i<n; ++i){
 
    c=(a+b)/2;
    cout<<setw(3)<<i+1<<'|'
      <<setw(width)<<a<<'|'<<setw(width)<<c<<'|'<<setw(width)<<b<<'|'
      <<setw(width)<<f(a)<<'|'<<setw(width)<<f(c)<<'|'<<setw(width)<<f(b)<<'|'<<endl;
    cout<<"---+"
      <<"----------"<<'+'<<"----------"<<'+'<<"----------"<<'+'
      <<"----------"<<'+'<<"----------"<<'+'<<"----------"<<'+'<<endl;
    
    if(abs((a-b)/2)<eps){
      break;
    }
    
    if(f(a)*f(c)<0)
      b=c;
    else if(f(b)*f(c)<0)
      a=c;
    else 
      break;
    
  }

  
  return c;
}

int main(){
  auto f= [](double x) -> double{ return 0.5 * x*x*x  + 6*x  + 1.25; } ;
  
  try{
    double ans = dihotomy(f, -1, 0, 20);
    cout<<"ans    = "<<ans<<endl<<"f(ans) = "<<f(ans)<<endl<<"epsilon= "<<eps  <<endl;
  }
  catch(const logic_error& e){
    cout<<"Error : "<<e.what()<<endl;
  }
  return 0;
}