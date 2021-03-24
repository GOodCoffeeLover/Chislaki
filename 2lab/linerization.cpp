#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <stdexcept>
#include <functional>
#include <algorithm>

using namespace std;                              
using f_RxRtoR = function<double(double, double)>; // сокращение названия типа по логике f : RxR -> R

const double eps = 0.0001;                         // точность решения - наш эпсилон

//операторы для арифметических операций с функциями

f_RxRtoR operator+(f_RxRtoR l, f_RxRtoR r){
  return [l, r](double x, double y){return (double)l(x,y)+(double)r(x,y); };
}

f_RxRtoR operator-(f_RxRtoR l, f_RxRtoR r){
  return [l, r](double x, double y){return (double)l(x,y)-(double)r(x,y); };
}

f_RxRtoR operator-(f_RxRtoR l){
  return [l](double x, double y){return -(double)l(x,y); };
}

f_RxRtoR operator/(f_RxRtoR l, f_RxRtoR r){
  return [l, r](double x, double y){return (double)l(x,y)/(double)r(x,y); };
}

f_RxRtoR operator*(f_RxRtoR l, f_RxRtoR r){
  return [l, r](double x, double y){return (double)l(x,y)*(double)r(x,y); };
}
//=====================================================



pair<double, double> linerization2x2( f_RxRtoR f[2], f_RxRtoR J[2][2], pair<double, double> x, int n){
  
  
  if((J[1][1]*J[0][0]-J[1][0]*J[0][1])(x.first, x.second)==0) //проверка, что у матрицы якоби в начальной точки есть обратная матрица
    cout<<"error : determinator is zero"<<endl;
  
  f_RxRtoR invJ[2][2] = //обратная матрица якоби в виде функций, чтобы можно было считать её значение в любой точке.
    {{ J[1][1]/(J[1][1]*J[0][0]-J[1][0]*J[0][1]), -J[0][1]/(J[1][1]*J[0][0]-J[1][0]*J[0][1])},     //a22/(a11*a22-a21*a12)     -a12/(a11*a22-a21*a12)
     {-J[1][0]/(J[1][1]*J[0][0]-J[1][0]*J[0][1]),  J[0][0]/(J[1][1]*J[0][0]-J[1][0]*J[0][1])} };   //-a21/(a11*a22-a21*a12)     a11/(a11*a22-a21*a12)
  
  int width = 12;                                 //ширина столбца таблицы
  char line[width] = "------------";              //горизонтальная линия ячейки
  pair<double, double> prev;                      // предыдущая точка

  //печать заголовка таблицы
  cout<<setw(3)<<"i"<<'|'
  <<setw(width)<<"x"<<'|'<<setw(width)<<"y"<<'|'<<setw(width)<<"f1(x,y)"<<'|'<<setw(width)<<"f2(x,y)"<<'|'<<endl;
    cout<<"---+"<<line<<'+'<<line<<'+'<<line<<'+'<<line<<'+'<<endl;
  
  for(int i=0; i<n; ++i){    //начало итерационного процесса 
    //печать очередной строки таблицы
    cout<<setw(3)<<i+1<<'|'
      <<setw(width)<<x.first<<'|'<<setw(width)<<x.second<<'|'<<setw(width)<<f[0](x.first, x.second)<<'|'<<setw(width)<<f[1](x.first, x.second)<<'|'<<endl;
    cout<<"---+"<<line<<'+'<<line<<'+'<<line<<'+'<<line<<'+'<<endl;


    if( i>0                                                                   // проверка окончания итерационного процесса
      &&(max(abs(x.first-prev.first), abs(x.second-prev.second)) <eps )       // что наибольший сдвиг по координате достаточно маленький
      && (sqrt((f[1]*f[1] + f[0]*f[0])(x.first, x.second)) < eps) )           // что функции достаточно близки к нулю  
      break;  
    prev=x;                           //запоминаем текущую точку
      
    x={prev.first  -(invJ[0][0]*f[0] + invJ[0][1]*f[1])(prev.first, prev.second), //считаем новую точку по принципу x_{i+1} = x_i - (J^{-1} * F) (x_i)
       prev.second -(invJ[1][0]*f[0] + invJ[1][1]*f[1])(prev.first, prev.second)};
  }

  return x;
}





int main(){
  f_RxRtoR f[2]={
    [](double x, double y) -> double{ return x*x*x  -2.0*y*y*y  +  19.0; }, // функции системы уравнений f1 и f2 
    [](double x, double y) -> double{ return 2.0* x*y -2.0* y -7.0; }
  }; 
  f_RxRtoR J[2][2] =   //матрица якоби, содержащая функции (производные df1/dx df1/dy df2/dx df2/dy)
  {{[](double x, double y) -> double{ return 3.0*x*x; }, [](double x, double y) -> double{ return -6.0*y*y; },},
   {[](double x, double y) -> double{ return 2.0*y; },   [](double x, double y) -> double{ return 2.0*x -2.0; }}};


  pair<double, double> ans;
  try{
  ans = linerization2x2(f, J, {2.0, 2.0}, 100);    //поиск решения из точки (2, 2) с ограничением в 100 идераций
   cout<<"ans    = ( "<<ans.first <<" , "<<ans.second<<" ) "<<endl
       <<"f(ans) = ( "<<f[0](ans.first, ans.second) <<" , "<< f[1](ans.first, ans.second)<<" ) "<<endl<<"epsilon= "<<eps  <<endl;
  ans = linerization2x2(f, J, {-2.0, 0.0}, 100);                      //поиск решения из точки (-2, 0) с ограничением в 100 идераций
    cout<<"ans    = ( "<<ans.first <<" , "<<ans.second<<" ) "<<endl
       <<"f(ans) = ( "<<f[0](ans.first, ans.second) <<" , "<< f[1](ans.first, ans.second)<<" ) "<<endl<<"epsilon= "<<eps  <<endl;

  }
  catch(const logic_error& e){
    cout<<"Error : "<<e.what()<<endl;
  }
  return 0;
}