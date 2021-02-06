#include <iostream>
using namespace std;

int* partition(int arr[], int l, int r);
void quicksort(int arr[], int l, int r)
{
    if(l<r) //注意要判断
    {
        int* p = partition(arr,l, r);
        quicksort(arr,l,p[0]-1);
        quicksort(arr,p[1],r);
    }
}

void quick(int arr[], int length)
{
    if(arr == NULL || length < 2)
    {
        return;
    }
    quicksort(arr,0, length-1);
}

void swap(int arr[], int l, int r)
{
    /*
    arr[l] = arr[l] + arr[r];   //a = a+b;
    arr[r] = arr[l] - arr[r];   //b = a-b;
    arr[l] = arr[l] - arr[r];   //a = a-b;
    */
    
    int temp = arr[l];
    arr[l] = arr[r];
    arr[r] = temp;
}

int* partition(int arr[], int l, int r)
{
    int less = l-1, more = r+1;
    int cur = l;
    while(cur < more)
    {
        if(arr[cur] < arr[r])
        {
            swap(arr,++less,cur++);
        }
        else if(arr[cur] > arr[r])
        {
            swap(arr,cur,--more);
        }
        else{
            cur++;
        }
    }
    //swap(arr, more, r);

    int* p = new int[2];
    p[0] = less+1;
    p[1] = more-1;
    return p;
}

int main()
{
    int arr[] = {1,3,22,25,2,45,34,90,37};
    int length = 9;
    quick(arr,length);
    
    for(int i = 0; i < length; i++)
    {
        cout << arr[i] << endl;
    }
}