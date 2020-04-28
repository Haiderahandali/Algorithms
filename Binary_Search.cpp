#include <iostream>

void Binary_Search (int value, int left, int right,int array[]);


int main()
{
  int array[100];

  //initialising array of size 100;
  for (int i = 0;i<100;i++)
    array[i] = i-50;

  //testing the whole array to ensure no single value fails
  for (auto x: array)
    Binary_Search(x, 0, 100,array);
}


void Binary_Search (int value, int left, int right,int array[])
{
  //finding the middle index 
  int mid = (left + right)/2;

  //checking if we got the right element
  if(array[mid]==value)
  {
    std::cout<<"found at index " <<mid<<"\n";
    return;
  }

  // checking if the we reached one of the boundraies
  if (left >= right)
    {
      std::cout<<"not found \n";
      return;
    }

  //if the value is lower then go left
  if (value < array[mid])
      Binary_Search(value, left, mid -1  ,array);   
  
  else // go right 
      Binary_Search(value, mid + 1 , right,array);

}