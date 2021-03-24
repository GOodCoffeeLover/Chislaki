#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <stdexcept>


using namespace std;

const double eps = 0.01;

double chord(auto f, double a,double b, int n){
  if(f(a)*f(b)>=0) //throw exeption;
    throw invalid_argument("f(a)*f(b)>=0");

  double c, cn=a;
  int width = 12;
  char line[width] = "------------";

  cout<<setw(3)<<"i"<<'|'
  <<setw(width)<<"a"<<'|'<<setw(width)<<"c"<<'|'<<setw(width)<<"b"<<'|'
  <<setw(width)<<"f(a)"<<'|'<<setw(width)<<"f(c)"<<'|'<<setw(width)<<"f(b)"<<'|'<<endl;
  
  cout<<"---+"
      <<line<<'+'<<line<<'+'<<line<<'+'
      <<line<<'+'<<line<<'+'<<line<<'+'<<endl;

  for(int i=0; i<n; ++i){
  
    c=(a*f(b)-b*f(a))/(f(b)-f(a));
    

    cout<<setw(3)<<i+1<<'|'
      <<setw(width)<<a<<'|'<<setw(width)<<c<<'|'<<setw(width)<<b<<'|'
      <<setw(width)<<f(a)<<'|'<<setw(width)<<f(c)<<'|'<<setw(width)<<f(b)<<'|'<<endl;
    cout<<"---+"
      <<line<<'+'<<line<<'+'<<line<<'+'
      <<line<<'+'<<line<<'+'<<line<<'+'<<endl;
    
    if(abs(c-cn)<eps && abs(f(c))<eps ){
      break;
    }  

    if(f(a)*f(c)<0)
      b=c;
    else if(f(b)*f(c)<0)
      a=c;
    else 
      break;
    
    
    cn=c;
  }

  
  return c;
}

int main(){
  auto f=[](double x) -> double{ return 0.5*x*x*x  + 5*x  + 16; } ;
  try{
    double ans = chord(f, -3, -2, 20);
    cout<<"ans    = "<<ans<<endl<<"f(ans) = "<<f(ans)<<endl<<"epsilon= "<<eps  <<endl;
  }
  catch(const logic_error& e){
    cout<<"Error : "<<e.what()<<endl;
  }
  return 0;
}