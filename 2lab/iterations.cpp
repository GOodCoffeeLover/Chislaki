#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <stdexcept>


using namespace std;

const double eps = 0.01;                                               //точность решения - наш эпсилон

double iterations(auto f, auto g, auto dg, double a,double b, int n){  //функция, итерационная функция и её производная
  if(f(a)*f(b)>0)
    throw invalid_argument("f(a)*f(b)<0");  // проверка, что решение точно есть на отрезке [а, b]
    
  if(abs(dg(a))<1){                     //выборграницы отрезка, что в ней производная итерационной 
    a=a;                                //левая граница
  }else if(abs(dg(b))<1){
    a=b;                                //правая граница
  }else 
    throw invalid_argument("|g\'(a)|>1 and |g\'(b)|>1"); //ни одна граница не подходит или функция подобрана неправильно
    
  double ai=0.0, aii=0.0;              //предыдущие две точки
  int width = 12;                      //ширина столбца таблицы
  char line[width] = "------------";   //нижняя линия таблицы
  //печать заголовка таблица
  cout<<setw(3)<<"i"<<'|'
  <<setw(width)<<"a_i"<<'|'<<setw(width)<<"f(a)"<<'|'<<setw(width)<<"g(a)"<<'|'<<setw(width)<<"g\'(a)"<<'|'<<endl;
   cout<<"---+"<<line<<'+'<<line<<'+'<<line<<'+'<<line<<'+'<<endl;

  for(int i=0; i<n; ++i){
    aii=ai; //запоминание предыдущей точки
    ai=a;   //запоминание текущей точки
    a=g(a); //создание новой точки

    cout<<setw(3)<<i+1<<'|'
      <<setw(width)<<a<<'|'<<setw(width)<<f(a)<<'|'<<setw(width)<<g(a)<<'|'<<setw(width)<<dg(a)<<'|'<<endl;
    cout<<"---+"<<line<<'+'<<line<<'+'<<line<<'+'<<line<<'+'<<endl; печать линии таблицы
    
    if(i>=1 
        && ((a-ai)*(a-ai)/abs(2*ai-a-aii) < eps) //проверка окончания итерационного процеса начиная со второй итерации, т.к. с этого момента у нас есть a_i, a_{i-1} и a_{i-2}  
        && abs(f(a))<eps )
      break;
  }
  return a;
}

int main(){
  auto f= [](double x) -> double{ return 3.0*x*x*x  + 6.0*x  + 20.0; };                             //задание исходной функции f(x) = 3*x^3 + 6*x +20
  auto g= [](double x) -> double{ return -pow(((6.0*x + 20.0)/3.0), 1.0/3.0); };                    // нахождение равносильнго уравнения f(x)=0 <=> x=g(x) : x = -((6*x + 20)/3)^(1/3)
  auto dg= [](double x) -> double{ return -2.0/3.0*(pow(((6.0*x + 20.0)/3.0), -2.0/3.0)); };        // g'(x) = -2/3*((2*x + 20/3)^(-2/3))
  
  try{
    double ans = iterations(f, g, dg, -2, -1, 20);   //поиск решения на отрезке [-2, -1] делая не более 20ти итераций
    cout<<"ans    = "<<ans<<endl<<"f(ans) = "<<f(ans)<<endl<<"epsilon= "<<eps  <<endl;
  }
  catch(const logic_error& e){
    cout<<"Error : "<<e.what()<<endl;
  }
  return 0;
}