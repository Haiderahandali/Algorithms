#include<iostream>

void Bubble_Sort(int arr[],int sz);
void swap(int&a , int &b);

int main()
{
    int array [10] = {1,-2,0,-20,16,35,100,200,-1,0};
    Bubble_Sort(array,10);

    for (auto x :array)
        std::cout<<x<<"\n";
}


void Bubble_Sort(int arr[],int sz) 
{
    for (int i = 0;i<sz;i++)
    {
        bool no_Change = true;
        for(int j =0;j<sz;j++)
            if(arr[j] < arr[i])
            {
                    swap(arr[j],arr[i]);
                    no_Change = false;
            }
        if (no_Change)
            return;
    }
}

void swap(int&a , int &b) 
{
    int tmp = a;
    a = b;
    b = tmp;
}