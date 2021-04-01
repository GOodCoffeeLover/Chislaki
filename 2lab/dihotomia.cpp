#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <stdexcept>
#define endl '\n'
using namespace std;

const double eps = 0.01;                            //точность решения - наш эпсилон

double dihotomy(auto f, double a,double b, int n){ //функция f(x) границы отрезка [а, b] и максимальное число итераций
  if(f(a)*f(b)>=0)                          //проверка, что зачение функции на концах отрезка разные
    throw invalid_argument("f(a)*f(b)>=0"); //чтобы быть точно уверенными, что решение есть
   
  double c;                                 //переменная середины отрзка
  int width = 12;                           //ширина колонки таблицы
  cout<<setprecision(width-4)<<fixed;       //количество знаков после запятой
  string line(width, '-');                  //нижняя линия ячейки таблицы
                                            //печать шапки таблицы
  cout<<"---+"
      <<line<<'+'<<line<<'+'<<line<<'+'
      <<line<<'+'<<line<<'+'<<line<<'+'<<endl;
  cout<<setw(3)<<"i"<<'|'
  <<setw(width)<<"a"<<'|'<<setw(width)<<"c"<<'|'<<setw(width)<<"b"<<'|'
  <<setw(width)<<"f(a)"<<'|'<<setw(width)<<"f(c)"<<'|'<<setw(width)<<"f(b)"<<'|'<<endl;
  
  cout<<"---+"
      <<line<<'+'<<line<<'+'<<line<<'+'
      <<line<<'+'<<line<<'+'<<line<<'+'<<endl;

  for(int i=0; i<n; ++i){
 
    c=(a+b)/2;                                                                          //середина отрезка
                                                                                        //печать новой строки таблицы
    cout<<setw(3)<<i+1<<'|'
      <<setw(width)<<a<<'|'<<setw(width)<<c<<'|'<<setw(width)<<b<<'|'
      <<setw(width)<<f(a)<<'|'<<setw(width)<<f(c)<<'|'<<setw(width)<<f(b)<<'|'<<endl;
    cout<<"---+"
      <<line<<'+'<<line<<'+'<<line<<'+'
      <<line<<'+'<<line<<'+'<<line<<'+'<<endl;
            
    if(abs((a-b)/2)<eps){             //проверка точности решения
      break;
    }
                                      //выбор отрезка, где есть пересечение с осью ох
    if(f(a)*f(c)<0)                   //выбираем левый отрезок [а, с]
      b=c;
    else if(f(b)*f(c)<0)              //выбираем правый [c, b]
      a=c;
    else 
      break;                          //попали в ноль, т.е. f(c) = 0
    
  }

  
  return c;
}

int main(){
  auto f= [](double x) -> double{ return 0.5 * x*x*x  + 6*x  + 1.25; } ;                  //задаём функцию 0.5x^3 + 6x + 1.25
  
  try{
    double ans = dihotomy(f, -1, 0, 20);                                                  //ищем решение уравнения f(x) = 0 на отрезке от -1 до 0, делая не больше 20ти шагов
    cout<<"ans    = "<<ans<<endl<<"f(ans) = "<<f(ans)<<endl<<"epsilon= "<<eps  <<endl;
  }
  catch(const logic_error& e){
    cout<<"Error : "<<e.what()<<endl;
  }
  return 0;
}