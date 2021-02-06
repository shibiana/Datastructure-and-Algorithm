#include <iostream>
using namespace std;

void sortprocess(int arr[], int l, int r);
void mergesort(int arr[], int length)
{
    if(arr == NULL || length < 2)
    {
        return;
    }
    sortprocess(arr,0,length-1);
}

void merge(int arr[], int l, int mid, int r)
{
    int *arrnew = new int[r-l+1];
    int i = 0;      //指示新建数组的位置
    int p1 = l;     //第一个数组的起始位置
    int p2 = mid+1; //第二个数组的起始位置


    //开始利用新的数组来进行外排
    while(p1 <= mid && p2 <= r)
    {
        arrnew[i++] = (arr[p1] <= arr[p2]) ? arr[p1++] : arr[p2++]; 
    }
    while(p1 <= mid)
    {
        arrnew[i++] = arr[p1++];
    }
    while(p2 <= r)
    {
        arrnew[i++] = arr[p2++];
    }
    //将arrnew中的值重新填入arr
    for(int j = 0; j < r-l+1; j++)
    {
        arr[j+l] = arrnew[j];
    }

}

void sortprocess(int arr[], int l, int r)
{
    if(l == r)
    {
        return;
    }
    int mid = l+((r-l)>>1);
    sortprocess(arr,l,mid);
    sortprocess(arr,mid+1,r);
    merge(arr,l,mid,r);
}

//测试
int main()
{
    int arr[] = {1,5,11,15,9,3,27,80};
    int length = 8;
    mergesort(arr,length);
    for(int i = 0; i< length; i++)
    {
        cout << arr[i] << endl;
    }
}