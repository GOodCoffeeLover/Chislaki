#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

vector<double> operator - (vector<double> l, const vector<double>& r ){
  if(l.size()!=r.size())
    return{};
  for(int i=0; i<l.size(); ++i)
    l[i]-=r[i];
  return l;
}

vector<double> operator * (double l, vector<double> r ){
  for(int i=0; i<r.size(); ++i)
    r[i]*=l;
  return r;
}

vector<double> gaus(vector<vector<double>> syst){
  if(syst.size() != (syst[0].size()-1))
    return{};
  vector<double> ans(syst.size());
  for(int i=0; i<syst.size(); ++i){
    for(int j=i+1; j<syst.size(); ++j)
      syst[j]=syst[j]-(syst[j][i]/syst[i][i])*syst[i];
  }

  for(int i=syst.size()-1; i>=0; --i){
    double sum=0;
    for(int j=syst.size()-1; j>i; --j)
      sum+=ans[j]*syst[i][j];
    ans[i]=(syst[i].back()-sum)/syst[i][i];
  }
  return ans;
}

vector<double> kanon(vector<vector<double>> p){
  vector<vector<double>>syst(p.size(), vector<double>(p.size()+1));
  for(int i=0; i<p.size(); ++i ){
    syst[i][0]=1;
    for(int j=1; j<=p.size(); ++j)
      syst[i][j]=p[i][0]*syst[i][j-1];
    syst[i].back() = p[i][1];
  } 
  return gaus(syst);
}

double polynom_at(vector<double> pol, double x0){
  double pow=1, res=0;
  for(int i=0; i<pol.size(); ++i){
    res+=pow*pol[i];
    pow*=x0;
  }
  return res;
}

int main(){
  vector<vector<double>> points{
    {-1,4},
    { 1,-2},
    { 5,10}};
  double x0=0.5;
  int width = 8;
  string line(width, '-');
  
  vector<double> pol = kanon(points);
  
  cout<<"P(x) = ";
  for(int i=0; i<pol.size(); ++i)
    cout<<((i>0 && pol[i]>=0)? '+'+to_string(pol[i]): to_string(pol[i])) <<" * x^"<<i<<' ';
  cout<<endl;
  
  cout<<line<<'+'<<line<<'+'<<endl;
  cout<<setw(width)<<"x0"<<'|'<<setw(width)<<"P(x0)"<<'|'<<endl;
  cout<<line<<'+'<<line<<'+'<<endl;

  for(int i=0; i<points.size(); ++i){
    if(i==0 && x0 < points[i][0]){
      cout<<setw(width)<<x0<<'|'<<setw(width)<<polynom_at(pol, x0)<<'|'<<endl;
    }
    cout<<setw(width)<<points[i][0]<<'|'<<setw(width)<<polynom_at(pol, points[i][0])<<'|'<<endl;
    if( (i>=0 && i<(points.size()-1) 
          && (points[i][0] < x0) && (x0 <points[i+1][0])) 
        ||(i==(points.size()-1) && x0 > points[i][0])){
      cout<<setw(width)<<x0<<'|'<<setw(width)<<polynom_at(pol, x0)<<'|'<<endl;
     }
  }
  return 0;
}