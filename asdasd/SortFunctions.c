//#include "ProjectHeader.h"
//
//void DeleteDuplication(char** InstrumentsArr, int* size)
//{
//    int i, j = 1, k = 1;
//    int OldSize = *size;
//    for (i = 0; i < *size; i++)
//    {
//        for (j = i + 1, k = j; j < *size; j++)
//        {
//            /* If strings don't match... */
//            if (strcmp(InstrumentsArr[i], InstrumentsArr[j]))
//            {
//                strcpy(InstrumentsArr[k] , InstrumentsArr[j]);
//                k++;
//            }
//        }
//        (*size) -= j - k;
//    }
//    InstrumentsArr = DynamicAllocation2(InstrumentsArr, *size, REALLOC);
//  
//}
//void swapStrings(char** stringA, char** stringB) //Swaps stringA & stringB.
//{
//    char* temp = NULL;
//    temp = DynamicAllocation1(temp, strlen(*stringA)+1, MALLOC);
//    strcpy(temp, *stringA);
//    strcpy(*stringA, *stringB);
//    strcpy(*stringB, temp);
//    free(temp);
//}
//
//void maxHeapify(MaxHeap* maxHeap, int index)
//{
//    int largest = index;
//    int left = 2 * index + 1;
//    int right = (index + 1) * 2;
//
//    if (left < maxHeap->size && strcmp(maxHeap->arr[left], maxHeap->arr[largest]) > 0)
//        largest = left;
//
//    if (right < maxHeap->size && strcmp(maxHeap->arr[right], maxHeap->arr[largest]) > 0)
//        largest = right;
//
//    if (largest != index)
//    {
//        swapStrings(&(maxHeap->arr[largest]), &(maxHeap->arr[index]));
//        maxHeapify(maxHeap, largest);
//    }
//}
//
//MaxHeap* createAndBuildHeap(char** arr, int size)
//{
//    int i;
//    MaxHeap* maxHeap = (MaxHeap*)malloc(sizeof(maxHeap));
//    CheckMem(maxHeap);
//
//    maxHeap->arr = arr;
//    maxHeap->size = size;
//
//    for (i = (maxHeap->size - 2) / 2; i >= 0; --i)
//        maxHeapify(maxHeap, i);
//
//    return maxHeap;
//}
//
//void heapSort(char*** arr, int size)
//{
//    MaxHeap* maxHeap = createAndBuildHeap(*arr, size);
//
//    while (maxHeap->size > 1)
//    {
//        swapStrings(&maxHeap->arr[0], &maxHeap->arr[maxHeap->size - 1]);
//        --(maxHeap->size);
//
//        maxHeapify(maxHeap, 0);
//    }
//}