#include <iostream>
#include <vector>
#include <iomanip>
#define endl '\n'

using namespace std;

int main(){
  vector<vector<double>> mtrix{
    //a,   b,  c,  d      matrx format 
    { 0,  -8, 1,  19},   // b1 c1  0  0  0  0 | d1 
    {-3, -11, 4,  -7},   // a2 b2 c2  0  0  0 | d2
    { 5,   8, 2,  65},   //  0 a3 b3 c3  0  0 | d3  
    { 1,  -9, 5, -25},   //  0  0 a4 b4 c4  0 | d4
    {-3,   7, 5,  16},   //  0  0  0 a5 b5 c5 | d5
    { 5, -11, 5, -22},   //  0  0  0  0 a6 b6 | d6
    {-5,   8, 3, -43},
    { 2, -10, 1,  25},
    { 1,  11, 0,   8}
  };

  vector<double> P(mtrix.size()+1, 0.0), 
                 Q(mtrix.size()+1, 0.0), 
                 ans(mtrix.size(), 0.0);
  
  for(int i=1; i<P.size(); ++i)
    //Pi = -ci/(bi + ai * P(i-1))
    P[i]=-mtrix[i-1][2]/(mtrix[i-1][1] + mtrix[i-1][0]*P[i-1]); 
  
  for(int i=1; i<Q.size(); ++i)
    //Qi = (di - ai*Q(i-1)) / (bi + ai * P(i-1))
    Q[i] = (mtrix[i-1][3] - mtrix[i-1][0]*Q[i-1])/(mtrix[i-1][1] + mtrix[i-1][0]*P[i-1]);
  
  //xn = qn
  ans[ans.size()-1] = Q[Q.size()-1];
  for(int i=ans.size()-1; i>0; --i)
    //xi = Qi + Pi * X(i+1)
    ans[i-1]=Q[i] + P[i]*ans[i];
  
  //print supporting calculations
  int width = 12;
  cout<<setprecision(width-4)<<fixed;       //количество знаков после запятой
  for(int i = 0; i<ans.size(); ++i)
    cout<<"P["<<i+1<<"] = "<<setw(width)<<P[i+1]
      <<"  Q["<<i+1<<"] = "<<setw(width)<<Q[i+1]<<endl;
  //print answer
  cout<<"Answer:"<<endl;
  for(int i = 0; i<ans.size(); ++i){
    cout<<"x["<<i+1<<"] = "<<ans[i]<<endl;
  }

  //testing final answer
  cout<<"testing:"<<endl;
  cout<<"line 1  " << 
  mtrix[0][1]*ans[0] + 
  mtrix[0][2]*ans[1] - 
  mtrix[0][3] <<endl;
  for(int i=1; i<mtrix.size()-1; ++i){
    cout<<"line "<<i+1<<"  "<<
     mtrix[i][0]*ans[i-1] + 
     mtrix[i][1]*ans[i] + 
     mtrix[i][2]*ans[i+1] - 
     mtrix[i][3]<<endl;
  }
  cout<<"line "<<mtrix.size()<<"  "<< 
    mtrix[mtrix.size()-1][0]*ans[mtrix.size()-2] + 
    mtrix[mtrix.size()-1][1]*ans[mtrix.size()-1] - 
    mtrix[mtrix.size()-1][3]<<endl;
  return 0;
}