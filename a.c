#include <stdio.h>

void swap(int *x,int *y);
void quick_sort_recursive(int arr[], int start, int end);
void quick_sort(int arr[], int len);

int main()
{
    int a[10000];
    int count = 0;
    int temp;
    scanf("%d",&temp);
    while(temp!=10)
    {
        a[count++] = temp;
        printf("Yes\n");
        scanf("%d",&temp);
    }
    quick_sort(a,count);
    int i = 0;
    for(;i<count-1;i++)
    {
        printf("%d ",a[i]);
    }
    printf("%d\n",a[i]);
}
//test

void swap(int *x, int *y)
{
    int t = *x;
    *x = *y;
    *y = t;
}

void quick_sort_recursive(int arr[], int start, int end)
{
    if (start >= end)
        return;
    int mid = arr[end];
    int left = start, right = end - 1;
    while (left < right) {
        while (arr[left] < mid && left < right)
            left++;
        while (arr[right] >= mid && left < right)
            right--;
        swap(&arr[left], &arr[right]);
    }
    if (arr[left] >= arr[end])
        swap(&arr[left], &arr[end]);
    else
        left++;
    if (left)
        quick_sort_recursive(arr, start, left - 1);
    quick_sort_recursive(arr, left + 1, end);
}

void quick_sort(int arr[], int len) 
{
    quick_sort_recursive(arr, 0, len - 1);
}