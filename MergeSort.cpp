#include <iostream>

void Merge(int array[], int p, int left, int  right);// Merge Function
void Merge_Sort(int array[], int left, int  right); //actual merge sort

int main() {

  //input, unsorted array>
  int arr[9]{9,-5,-2,40,41,5,6,5,19};

  //merge sort the array of boundaries 0 ->8 inclusive
   Merge_Sort(arr, 0, 8);
  

  //printing the array
  for(auto x : arr)
    std::cout<<x<<std::endl;
}



void Merge_Sort(int array[], int left, int  right)
{
  //if the array is empty or of one element, we're done.
  if(left<right)
  {
    //speicify mid point p to separate left & right
    int p = (left+right)/2;

    //merge sort the left -> mid point
    Merge_Sort(array, left,p);

    //merge sort mid + 1  -> right
    Merge_Sort(array,p+1,right);

    //merge both the left and the right.
    Merge(array,p,left,right);

  }

}

void Merge(int array[], int p,int left, int  right)
{
  
  //init new arrays to have the left and right side
  // we add an extra sentile element to each array (infinity) at line 75 
  int L[p - left + 1 + 1]; 
  int R[right-p+1];

  //setting the boundaries for each new array (L and R)
  int n1 = p-left;
  int n2 = right - p;


  //getting elemetns from oringal array to each array
  for(int i =0;i<=n1;i++)
  {
    L[i] = array[left+i];
  }
  
  //same here.
  for(int j =0; j<n2 ;j++)
  {
    R[j]= array[p +1 + j];      
  }

  
  L[n1+1] = 1000000; //the extra sentile element at the end
  R[n2] = 1000000;

  //Merging the 2 arrays
  int i =0; int j = 0;
  for (int k = left;k<right+1;k++)
  {
    
    if (L[i]< R[j])
    {
      array[k] = L[i];
      ++i;
    }
    else 
    {
      array[k] = R[j];
      ++j;
    }
      
  // because we add an extra element at the end, we don't need to check if the L, R arrays are empty. 
  
  }
  
}