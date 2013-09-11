#include <iostream>
#include <cstdlib>

int main ()
{
  using namespace std;

  cout<< 1 <<" "<< 9999 <<" "<<std::endl;
  for(int j=10000; j<1000000; j+=10000)
  {  
    cout<< j <<" "<< (j+9999) <<" "<<std::endl;
  }
  for(int i=0; i<900; i++)
  {
    int n1 = rand() % 1000000;
    int n2 = rand() % 1000000;
    cout<< n1 << " "<< n2 <<" "<< std::endl;
  }
  return 0;
}
