#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <stdexcept>
#include <string>


using namespace std;

const double eps = 0.01;

double newton(auto f, auto df, auto ddf, double a,double b, int n){
  if(f(a)*ddf(a)>0)
    a=a;
  else if(f(b)*ddf(b)>0)
    a=b;
  else //throw exeption;
    throw invalid_argument("f(a)*ddf(a)<=0 and f(b)*ddf(b)<=0 ");
    
  double ai;
  int width = 12;
  char line[width] = "------------";

  cout<<setw(3)<<"i"<<'|'
  <<setw(width)<<"a_i"<<'|'<<setw(width)<<"f(a)"<<'|'<<setw(width)<<"f\'(a)"<<'|'<<setw(width)<<"f\'\'(a)"<<'|'<<setw(width)<<"a_{i+1}"<<'|'<<endl;
  
  cout<<"---+"<<line<<'+'<<line<<'+'<<line<<'+'<<line<<'+'<<line<<'+'<<endl;

  for(int i=0; i<n; ++i){
    

    ai=a-f(a)/df(a);
    cout<<setw(3)<<i+1<<'|'
      <<setw(width)<<a<<'|'<<setw(width)<<f(a)<<'|'<<setw(width)<<df(a)<<'|'<<setw(width)<<ddf(a)<<'|'<<setw(width)<<((f(a)*ddf(a)>0)? to_string(ai) : "-")<<'|'<<endl;
    cout<<"---+"<<line<<'+'<<line<<'+'<<line<<'+'<<line<<'+'<<line<<'+'<<endl;
    
    if(f(a)*ddf(a)<=0)
      break;
    a=ai;
  }

  
  return ai;
}

int main(){
  auto f= [](double x) -> double{ return 0.5*x*x*x  + 11.0*x  -24.75; };
  auto df= [](double x) -> double{ return 1.5*x*x  + 11.0; };
  auto ddf= [](double x) -> double{ return 3.0*x ; };
  
  try{
    double ans = newton(f, df, ddf, 1, 2, 20);
    cout<<"ans    = "<<ans<<endl<<"f(ans) = "<<f(ans)<<endl<<"epsilon= "<<eps  <<endl;
  }
  catch(const logic_error& e){
    cout<<"Error : "<<e.what()<<endl;
  }
  return 0;
}