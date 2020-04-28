#include <iostream>

void Insertion_Sort(int array[]);

int main()
{ 
  int array[10]{1,5,7,8,9,0,4,10,5,0};

  Insertion_Sort(array);

  //printing the array
  for (auto x:array)
    std::cout<<x<<std::endl;
}


void Insertion_Sort(int array[]) 
{
 // this loop travere the array
    for (int i = 1;i<10;i++)
    {
      int j = i-1;
      int key = array[i];

      //checking if the previous element is larger 
      //and if we haven't crossed the boundray
      while(array[j]> key && j >=0)
        {
          //move each element's index by one
          array[j+1] = array[j];
          --j;
        }
      //when the condiiton is out or we no longer have 
      //an element that is bigger than our key; swap.
      array[j+1] = key;
    }
}