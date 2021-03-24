#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <stdexcept>


using namespace std;

const double eps = 0.01;

double iterations(auto f, auto g, auto dg, double a,double b, int n){
  if(f(a)*f(b)>0)
    throw invalid_argument("f(a)*f(b)<0");
    
  if(abs(dg(a))<1){
    a=a;
  }else if(abs(dg(b))<1){
    a=b;
  }else //throw exeption;
    throw invalid_argument("|g\'(a)|>1 and |g\'(b)|>1");
    
  double ai=0.0, aii=0.0;
  int width = 12;
  char line[width] = "------------";

  cout<<setw(3)<<"i"<<'|'
  <<setw(width)<<"a_i"<<'|'<<setw(width)<<"f(a)"<<'|'<<setw(width)<<"g(a)"<<'|'<<setw(width)<<"g\'(a)"<<'|'<<endl;
  
  cout<<"---+"<<line<<'+'<<line<<'+'<<line<<'+'<<line<<'+'<<endl;

  for(int i=0; i<n; ++i){
    aii=ai;
    ai=a;
    a=g(a);

    cout<<setw(3)<<i+1<<'|'
      <<setw(width)<<a<<'|'<<setw(width)<<f(a)<<'|'<<setw(width)<<g(a)<<'|'<<setw(width)<<dg(a)<<'|'<<endl;
    cout<<"---+"<<line<<'+'<<line<<'+'<<line<<'+'<<line<<'+'<<endl;
    if(i>=1 
        && ((a-ai)*(a-ai)/abs(2*ai-a-aii) < eps)
        && abs(f(a))<eps )
      break;

  }

  
  return a;
}

int main(){
  auto f= [](double x) -> double{ return 3.0*x*x*x  + 6.0*x  + 20.0; }; //3*x^3 + 6*x +20
  auto g= [](double x) -> double{ return -pow((double)((6.0*x + 20.0)/3.0), 1.0/3.0); };                            //x = -((6*x + 20)/3)^(1/3)
  auto dg= [](double x) -> double{ return -(double)2.0/3.0*(pow((double)((6.0*x + 20.0)/3.0), -2.0/3.0)); };                    // -2/3*((2*x + 20/3)^(-2/3))
  
  try{
    double ans = iterations(f, g, dg, -2, -1, 30);
    cout<<"ans    = "<<ans<<endl<<"f(ans) = "<<f(ans)<<endl<<"epsilon= "<<eps  <<endl;
  }
  catch(const logic_error& e){
    cout<<"Error : "<<e.what()<<endl;
  }
  return 0;
}