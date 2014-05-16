//
//  main.c
//  minK
//
//  Created by Ysan on 14-4-22.
//  Copyright (c) 2014年 Ysan. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void swap(int a,int b)
{
    int tmp;
    tmp = a;
    a = b;
    b = tmp;
}
void MaxHeap(int *heap,int i,int len)
{
    int largeIndex = -1;
    int left = i*2;
    int right = i*2 + 1;
    
    if(left < len && heap[left]>heap[i])
        largeIndex = left;
    else
        largeIndex = i;
    if(right <= len && heap[right] > heap[largeIndex])
        largeIndex = right;
    
    if(largeIndex != i)
    {
        swap(heap[i],heap[largeIndex]);
        MaxHeap(heap, largeIndex, len);
    }
}
void BuildHeap(int *heap,int len)
{
    if(heap == NULL)
        return;
    int index = len / 2;
    for (int i=index; i>=1; i--) {
        MaxHeap(heap, i, len);
    }
}
int main(int argc, const char * argv[])
{
    int k;
    int i;
    scanf("%d",&k);
    
    int *heap = (int* )malloc(k+1);
    
    FILE *fp = fopen("data.txt", "r");
    
    for (i = 1; i<=k; i++) {
        fscanf(fp, "%d ",&heap[i]);
    }
    
    BuildHeap(heap, k);
    int data;
    while (fscanf(fp, "%d ",&data) != EOF) {
        if (data < heap[1]) {
            heap[1] = data;
            MaxHeap(heap, 1, k);
        }
    }
    for (i=1; i<=k; i++) {
        printf("%d ",heap[i]);
    }
    printf("\n");
    fclose(fp);
    free(heap);
    
    return 0;
}

