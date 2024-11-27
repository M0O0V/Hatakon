#ifndef SORT_H
#define SORT_H

class Sort 
{
private:

    void swap(int& a, int& b);
    int part(int arr[], int low, int high);
    
public:

    Sort(); 
    ~Sort(); 

    void quickSort(int arr[], int low, int high);
};

#endif

