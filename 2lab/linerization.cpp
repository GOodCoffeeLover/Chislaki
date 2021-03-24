#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <stdexcept>
#include <functional>
#include <algorithm>

using namespace std;

const double eps = 0.0001;

function<double(double, double)> operator+(function<double(double, double)> l, function<double(double, double)> r){
  return [l, r](double x, double y){return (double)l(x,y)+(double)r(x,y); };
}

function<double(double, double)> operator-(function<double(double, double)> l, function<double(double, double)> r){
  return [l, r](double x, double y){return (double)l(x,y)-(double)r(x,y); };
}

function<double(double, double)> operator-(function<double(double, double)> l){
  return [l](double x, double y){return -(double)l(x,y); };
}

function<double(double, double)> operator/(function<double(double, double)> l, function<double(double, double)> r){
  return [l, r](double x, double y){return (double)l(x,y)/(double)r(x,y); };
}

function<double(double, double)> operator*(function<double(double, double)> l, function<double(double, double)> r){
  return [l, r](double x, double y){return (double)l(x,y)*(double)r(x,y); };
}




pair<double, double> linerization2x2( function<double(double, double)> f[2], function<double(double, double)> J[2][2], pair<double, double> x, int n){
  
  pair<double, double> prev=x;
  
  if((J[1][1]*J[0][0]-J[1][0]*J[0][1])(prev.first, prev.second)==0)
    cout<<"error : determinator is zero"<<endl;
  
  function<double(double, double)> invJ[2][2] = 
    {{ J[1][1]/(J[1][1]*J[0][0]-J[1][0]*J[0][1]), -J[0][1]/(J[1][1]*J[0][0]-J[1][0]*J[0][1])},
     {-J[1][0]/(J[1][1]*J[0][0]-J[1][0]*J[0][1]),  J[0][0]/(J[1][1]*J[0][0]-J[1][0]*J[0][1])} };
  
  int width = 12;
  char line[width] = "------------";

  cout<<setw(3)<<"i"<<'|'
  <<setw(width)<<"x"<<'|'<<setw(width)<<"y"<<'|'<<setw(width)<<"f1(x,y)"<<'|'<<setw(width)<<"f2(x,y)"<<'|'<<endl;
  
  cout<<"---+"<<line<<'+'<<line<<'+'<<line<<'+'<<line<<'+'<<endl;
  for(int i=0; i<n; ++i){
    cout<<setw(3)<<i+1<<'|'
      <<setw(width)<<x.first<<'|'<<setw(width)<<x.second<<'|'<<setw(width)<<f[0](x.first, x.second)<<'|'<<setw(width)<<f[1](x.first, x.second)<<'|'<<endl;
    cout<<"---+"<<line<<'+'<<line<<'+'<<line<<'+'<<line<<'+'<<endl;


    if( (max(abs(x.first-prev.first), abs(x.second-prev.second)) <eps )
      && (sqrt((f[1]*f[1] + f[0]*f[0])(x.first, x.second)) < eps) )
      break;  
    prev=x;
      
    x={prev.first  -(invJ[0][0]*f[0] + invJ[0][1]*f[1])(prev.first, prev.second),
       prev.second -(invJ[1][0]*f[0] + invJ[1][1]*f[1])(prev.first, prev.second)};
  
  }

  return x;
}





int main(){
  function<double(double, double)> f[2]={
    [](double x, double y) -> double{ return x*x*x  -2.0*y*y*y  +  19.0; },
    [](double x, double y) -> double{ return 2.0* x*y -2.0* y -7.0; }
  }; 
  function<double(double, double)> J[2][2] =
  {{[](double x, double y) -> double{ return 3.0*x*x; }, [](double x, double y) -> double{ return -6.0*y*y; },},
   {[](double x, double y) -> double{ return 2.0*y; },   [](double x, double y) -> double{ return 2.0*x -2.0; }}};


  
  try{
  pair<double, double> ans = linerization2x2(f, J, {2.0, 2.0}, 100);
   cout<<"ans    = ( "<<ans.first <<" , "<<ans.second<<" ) "<<endl
       <<"f(ans) = "<<f[0](ans.first, ans.second) <<" , "<< f[1](ans.first, ans.second)<<endl<<"epsilon= "<<eps  <<endl;
    ans = linerization2x2(f, J, {-2.0, 0.0}, 100);
    cout<<"ans    = ( "<<ans.first <<" , "<<ans.second<<" ) "<<endl
       <<"f(ans) = "<<f[0](ans.first, ans.second) <<" , "<< f[1](ans.first, ans.second)<<endl<<"epsilon= "<<eps  <<endl;

  }
  catch(const logic_error& e){
    cout<<"Error : "<<e.what()<<endl;
  }
  return 0;
}