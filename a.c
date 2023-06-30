#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define N 100001
void swap(int *a, int *b);

int partition(int array[], int low, int high);

void quickSort(int array[], int low, int high);

void merge(int arr[], int low, int middle, int high);

void mergeSort(int arr[], int low, int high);

int main()
{
    int data[N];
    for (int i = 0; i < N;i++)
    {
        data[i] = rand();
    }
    // quickSort(data, 0, N - 1);
    mergeSort(data, 0, N - 1);
    for (int i = 0; i < N - 1; i++)
    {
        printf("%d:%d\n",i, data[i]);
    }
    printf("%d\n",data[N-1]);
    return 0;

    clock();
}

void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int array[], int low, int high)
{
    int pivot = array[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {
        if (array[j] <= pivot)
        {
            i++;
            swap(&array[i], &array[j]);
        }
    }
    swap(&array[i + 1], &array[high]);
    return (i + 1);
}

void quickSort(int array[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(array, low, high);
        quickSort(array, low, pi - 1);
        quickSort(array, pi + 1, high);
    }
}

void merge(int arr[], int low, int middle, int high)
{
    int i, j, k;
    int left = middle - low + 1;
    int right = high - middle;

    int L[left], R[right];

    for (i = 0; i < left; i++)
        L[i] = arr[low + i];
    for (j = 0; j < right; j++)
        R[j] = arr[middle + 1 + j];

    i = 0;
    j = 0;
    k = low;
    while (i < left && j < right)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < left)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < right)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int middle = low + (high - low) / 2;
        mergeSort(arr, low, middle);
        mergeSort(arr, middle + 1, high);
        merge(arr, low, middle, high);
    }
}
