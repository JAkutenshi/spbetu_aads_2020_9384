#include "MergeSort.h"


void Merge(int *A, int first, int last)
{
	int middle = 0, start = 0, final = 0;
	int n = last - first + 1;
	int *mas = new int[n];
	middle = (first + last) / 2;
	start = first;
	final = middle + 1;
	for (int j = first; j <= last; j++)
		if ((start <= middle) && ((final > last) || (A[start] < A[final])))
		{
			mas[j - first] = A[start];
			start++;
		}
		else
		{
			mas[j - first] = A[final];
			final++;
		}
	
	for (int j = first; j <= last; j++) A[j] = mas[j - first];
	delete[]mas;
}

void MergeSort(int *A, int first, int last)
{
	if (first < last)
	{
		MergeSort(A, first, (first + last) / 2); 
		MergeSort(A, (first + last) / 2 + 1, last);
		Merge(A, first, last);
	}
}