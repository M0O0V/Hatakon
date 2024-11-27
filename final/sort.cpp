#include "sort.h"

Sort::Sort() {}

Sort::~Sort() {}

void Sort::swap(int& a, int& b) 
{
    int temp = a;
    a = b;
    b = temp;
}

int Sort::part(int arr[], int low, int high) 
{
    int pivot = arr[high];
    int i = low - 1;
    
    for (int j = low; j < high; j++) 
    {
        if (arr[j] <= pivot) 
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void Sort::quickSort(int arr[], int low, int high) 
{
    if (low < high) 
    {
        int pi = part(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
