#include<iostream>
#include<vector>





void merge (std::vector<int> v1,std:: vector<int> v2) 
{
std::vector<int> MRG;
   
    int i,j;
    i = j = 0;
    int s1 = v1.size() ;
    int s2 = v2.size() ;
    
    //MRG.reserve(v1.size()+ v2.size() - 2);
   while (int n = s1+s2)
   {
    std::cout << n << std::endl;
        if (v1[i] > v2[j])
        {
            MRG.push_back(v2[j]);
            j++;
            n--;
        }
        else
        {
            MRG.push_back(v1[i]);
            i++;
            n--;
        }
        
   
    
    }
}

int main(){
std::vector<int> arr(6,0);
int a[6]{0};


}