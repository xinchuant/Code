#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define large_scale 100000
#define small_scale 100

void array_reset(int array[],int data[],int count);
void swap(int *a, int *b);
int partition(int array[], int low, int high);
void quickSort(int array[], int low, int high);
void merge(int array[], int low, int middle, int high);
void mergeSort(int array[], int low, int high);
double Time(int data[], int count,char mode);

int main()
{
    //初始化数据
    int data_large_ordered[large_scale];
    int data_large_reverse[large_scale];
    int data_large_random[large_scale];
    int data_small_ordered[small_scale];
    int data_small_reverse[small_scale];
    int data_small_random[small_scale];
    for (int i = 0; i < large_scale; i++)
    {
        data_large_ordered[i] = i;
        data_large_reverse[i] = large_scale - i - 1;
        data_large_random[i] = rand();
    }
    for (int i = 0; i < small_scale;i++)
    {
        data_small_ordered[i] = i;
        data_small_reverse[i] = small_scale - i - 1;
        data_small_random[i] = rand();
    }

    //运行并记录时间
    double time_quick_large_ordered = Time(data_large_ordered,large_scale, 'q');
    double time_quick_large_reverse = Time(data_large_reverse, large_scale, 'q');
    double time_quick_large_random = Time(data_large_random, large_scale, 'q');
    double time_quick_small_ordered = Time(data_small_ordered, small_scale, 'q');
    double time_quick_small_reverse = Time(data_small_reverse, small_scale, 'q');
    double time_quick_small_random = Time(data_small_random, small_scale, 'q');

    double time_merge_large_ordered = Time(data_large_ordered, large_scale, 'm');
    double time_merge_large_reverse = Time(data_large_reverse, large_scale, 'm');
    double time_merge_large_random = Time(data_large_random, large_scale, 'm');
    double time_merge_small_ordered = Time(data_small_ordered, small_scale, 'm');
    double time_merge_small_reverse = Time(data_small_reverse, small_scale, 'm');
    double time_merge_small_random = Time(data_small_random, small_scale, 'm');

    //输出结果
    printf("处理大型顺序数据时：\n归并算法用时%lfs,快排算法用时%lfs。\n", time_merge_large_ordered, time_quick_large_ordered);
    printf("处理大型逆序数据时：\n归并算法用时%lfs,快排算法用时%lfs。\n", time_merge_large_reverse, time_quick_large_reverse);
    printf("处理大型乱序数据时：\n归并算法用时%lfs,快排算法用时%lfs。\n", time_merge_large_random, time_quick_large_random);
    printf("处理小型顺序数据时：\n归并算法用时%lfs,快排算法用时%lfs。\n", time_merge_small_ordered, time_quick_small_ordered);
    printf("处理小型逆序数据时：\n归并算法用时%lfs,快排算法用时%lfs。\n", time_merge_small_reverse, time_quick_small_reverse);
    printf("处理小型乱序数据时：\n归并算法用时%lfs,快排算法用时%lfs。\n", time_merge_small_random, time_quick_small_random);
    return 0;
}

void array_reset(int array[],int data[],int count)//排序后重设数组，保证所用数据相同
{
    for (int i = 0; i < count;i++)
    {
        array[i] = data[i];
    }
}

void swap(int *a, int *b)//交换元素
{
    int t = *a;
    *a = *b;
    *b = t;
}
//选择一个基准元素，将数组分为两部分，一部分比基准小，一部分比基准大
int partition(int array[], int low, int high)
{
    int pivot = array[high];//取末端为基准
    int i = (low - 1);//下一个比基准小的元素要放置的位置

    //从low到high遍历数组
    for (int j = low; j <= high - 1; j++)
    {   
        //元素小于基准则移到左边
        if (array[j] <= pivot)
        {
            i++;//移动到下一位置
            swap(&array[i], &array[j]);//交换
        }
    }
    swap(&array[i + 1], &array[high]);//把基准元素放到正确的位置
    return (i + 1);//返回基准元素的位置
}

void quickSort(int array[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(array, low, high);//对数组进行划分，返回基准元素的位置
        quickSort(array, low, pi - 1);//对基准左边的数组进行排序
        quickSort(array, pi + 1, high);//对基准右边的数组进行排序
    }
}

void merge(int array[], int low, int middle, int high)
{
    int i, j, k;
    int left = middle - low + 1;//左子数组长度
    int right = high - middle;//右子数组长度

    int L[left], R[right];//创建子数组

    //复制
    for (i = 0; i < left; i++)
    {
        L[i] = array[low + i];
    }
    for (j = 0; j < right; j++)
    {
        R[j] = array[middle + 1 + j];
    }
    i = 0;//左子数组的索引
    j = 0;//右子树组的索引
    k = low;//合并的数组（在原数组上）的索引
    //合并两个子数组
    while (i < left && j < right)
    {
        if (L[i] <= R[j])
        {
            array[k] = L[i];
            i++;
        }
        else
        {
            array[k] = R[j];
            j++;
        }
        k++;
    }
    //复制左子数组的剩余元素到合并的数组
    while (i < left)
    {
        array[k] = L[i];
        i++;
        k++;
    }
    //复制右子数组的剩余元素到合并的数组
    while (j < right)
    {
        array[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int middle = low + (high - low) / 2;//找到中间的索引
        mergeSort(arr, low, middle);//对左子数组排序
        mergeSort(arr, middle + 1, high);//对右子数组排序
        merge(arr, low, middle, high);//合并两个已排序的子数组
    }
}

double Time(int data[], int count,char mode)//计时用函数
{
    int a[count];
    double time = 0;
    if(mode == 'q')
    {
        for (int i = 0; i < 3; i++)//排序三次，减小偶然误差
        {
            array_reset(a, data, count);
            clock_t time_start = clock();
            quickSort(a, 0, count - 1);
            clock_t time_end = clock();
            time += (double)(time_end - time_start) / CLOCKS_PER_SEC;
        }
    }
    else if(mode == 'm')
    {
        for (int i = 0; i < 3; i++)
        {
            array_reset(a, data, count);
            clock_t time_start = clock();
            mergeSort(a, 0, count - 1);
            clock_t time_end = clock();
            time += (double)(time_end - time_start) / CLOCKS_PER_SEC;
        }
    }
    else
    {
        printf("WRONG MODE!!!\n");
        return -1;
    }
    time = time / 3;
    return time;
}
//直接编译运行即可，无需数据处理。