#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <stdexcept>
#include <string>
#define endl '\n'


using namespace std;

const double eps = 0.01;             //точность решения - наш эпсилон

double newton(auto f, auto df, auto ddf, double a,double b, int n){
                                    //выбираем такую границу отрезка что функция и вторая производная в этой точке одно знака
  if(f(a)*ddf(a)>0)                 // выбираем левую границу
    a=a;
  else if(f(b)*ddf(b)>0)            // выбираем правую
    a=b;
  else                              // такой границы нет , поэтому не начинаем итерационный процесс
    throw invalid_argument("f(a)*ddf(a)<=0 and f(b)*ddf(b)<=0 ");
    
  double ai;                           // следующая точка в приближении к ответу
  int width = 12;                      // ширина таблицы
  cout<<setprecision(width-4)<<fixed;       //количество знаков после запятой
  string line(width, '-');                  //нижняя линия ячейки таблицы
  
  //печать заголовка таблицы
  cout<<"---+"<<line<<'+'<<line<<'+'<<line<<'+'<<line<<'+'<<line<<'+'<<endl;
  cout<<setw(3)<<"i"<<'|'
  <<setw(width)<<"a_i"<<'|'<<setw(width)<<"f(a)"<<'|'<<setw(width)<<"f\'(a)"<<'|'<<setw(width)<<"f\'\'(a)"<<'|'<<setw(width)<<"a_{i+1}"<<'|'<<endl;
  cout<<"---+"<<line<<'+'<<line<<'+'<<line<<'+'<<line<<'+'<<line<<'+'<<endl;

  for(int i=0; i<n; ++i){ //начала итерационного процесса
    ai=a-f(a)/df(a);      // нахождение следующей точки, точки пересечения ох и касательной в текущей точке

    //печать очередной строки таблицы
    cout<<setw(3)<<i+1<<'|'
      <<setw(width)<<a<<'|'<<setw(width)<<f(a)<<'|'<<setw(width)<<df(a)<<'|'<<setw(width)<<ddf(a)<<'|'<<setw(width)<<((f(a)*ddf(a)>0)? to_string(ai) : "-")<<'|'<<endl;
    cout<<"---+"<<line<<'+'<<line<<'+'<<line<<'+'<<line<<'+'<<line<<'+'<<endl;
    
    if(f(a)*ddf(a)<=0) //проверка, что функция и вторая производная всё ещё одного знака
      break;
    a=ai; //запоминание текущей точки
  }

  
  return ai;
}

int main(){
  auto f= [](double x) -> double{ return 0.5*x*x*x  + 11.0*x  -24.75; };     //функция исходная
  auto df= [](double x) -> double{ return 1.5*x*x  + 11.0; };                // первая производная
  auto ddf= [](double x) -> double{ return 3.0*x ; };                        //вторая производная
  
  try{
    double ans = newton(f, df, ddf, 1, 2, 20);                               // передача функции с её производными, ищем ответ на отрезке [1, 2], делая не более 20ти итераций
    cout<<"ans    = "<<ans<<endl
        <<"f(ans) = "<<f(ans)<<endl
        <<"epsilon= "<<eps  <<endl;
  }
  catch(const logic_error& e){
    cout<<"Error : "<<e.what()<<endl;
  }
  return 0;
}