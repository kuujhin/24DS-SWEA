#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>

using namespace std;

void swap(int *n1, int *n2)
{
	int tmp = *n1;
	*n1 = *n2;
	*n2 = tmp;
}

// O(n^2)
void bubble_sort(int *a, int n)
{
	for (int i = n - 2; i >= 0; --i)
	{
		for (int j = 0; j <= i; ++j)
		{
			if (a[j] > a[j + 1])
			{
				swap(&a[j], &a[j + 1]);
			}
		}
	}
}

void bubble_sort_simple(int *a, int n)
{
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n - 1; ++j)
		{
			if (a[j] > a[j + 1])
			{
				swap(&a[j], &a[j + 1]);
			}
		}
	}
}

// O(n^2)
void selection_sort(int *a, int n)
{
	for (int i = 0; i < n - 1; ++i)
	{
		int _min = i;
		for (int j = i + 1; j < n; ++j)
		{
			if (a[_min] > a[j])
			{
				_min = j;
			}
		}
		swap(&a[_min], &a[i]);
	}
}

// O(kn)
void selection_algorithm(int *a, int n, int k)
{
	for (int i = 0; i < k; ++i)
	{
		int _min = i;
		for (int j = i + 1; j < n; ++j)
		{
			if (a[_min] > a[j])
			{
				_min = j;
			}
		}
		swap(&a[_min], &a[i]);
	}
}

// O(n^2), O(n^2) �߿��� ���� ������.
// �����Ͱ� ��� ���� ���ĵ� �����϶� ������ ������ �����Ѵ�.
void insertion_sort(int *a, int n)
{
	for (int i = 1; i < n; ++i)
	{
		int tmp = a[i];
		int j = i - 1;

		while (j >= 0 && a[j] >= tmp)
		{
			a[j + 1] = a[j];
			j--;
		}
		a[j + 1] = tmp;
	}
}

// O(n + k), M(K)
void counting_sort(int *a, int n)
{
	int K = 0;
	for (int i = 0; i < n; ++i)
	{
		if (K <= a[i])
		{
			K = a[i];
		}
	}

	// cnt[]
	int *cnt = new int[K + 1];
	for (int i = 0; i <= K; ++i)
	{
		cnt[i] = 0;
	}

	for (int i = 0; i < n; ++i)
	{
		cnt[a[i]]++;
	}

	// ���� ������ ����
	int idx = 0;
	for (int i = 0; i <= K; ++i)
	{
		while (cnt[i])
		{
			a[idx++] = i;
			cnt[i]--;
		}
	}

	// memory ����
	delete[] cnt;
}

int *result = new int[50];
void merge(int *a, int low, int mid, int high)
{
	int idx = low;
	int *t = result;

	int i = low;
	int j = mid + 1;

	// ���� �� ���� �ִ� ���
	while (i <= mid && j <= high)
	{
		if (a[i] < a[j])
			t[idx++] = a[i++];
		else
			t[idx++] = a[j++];
	}

	// ���ʸ� ���� �ִ� ���
	while (i <= mid)
	{
		t[idx++] = a[i++];
	}

	// �����ʸ� ���� �ִ� ���
	while (j <= high)
	{
		t[idx++] = a[j++];
	}

	// ���� ������ ����
	for (int k = low; k <= high; ++k)
	{
		a[k] = t[k];
	}
}

// O(nlogn), M(n)
void merge_sort(int *a, int low, int high)
{
	if (high - low <= 0)
		return;

	int mid = (low + high) / 2;

	merge_sort(a, low, mid);
	merge_sort(a, mid + 1, high);
	merge(a, low, mid, high);
}

void merge_sort_pro(int *a, int low, int high)
{
	if (high - low <= 0)
		return;

	int mid = (low + high) / 2;

	merge_sort(a, low, mid);
	merge_sort(a, mid + 1, high);
	if (a[mid] > a[mid + 1])
	{
		// merge(a, low, mid, high);
		int idx = low;
		int *t = result;

		int i = low;
		int j = mid + 1;

		// ���� �� ���� �ִ� ���
		while (i <= mid && j <= high)
		{
			if (a[i] < a[j])
				t[idx++] = a[i++];
			else
				t[idx++] = a[j++];
		}

		// ���ʸ� ���� �ִ� ���
		while (i <= mid)
		{
			t[idx++] = a[i++];
		}

		// �����ʸ� ���� �ִ� ���
		while (j <= high)
		{
			t[idx++] = a[j++];
		}

		// ���� ������ ����
		for (int k = low; k <= high; ++k)
		{
			a[k] = t[k];
		}
	}
}

int Hoare_partition(int *a, int low, int high)
{
	int p = a[low];
	int i = low;
	int j = high;

	while (i <= j)
	{
		while (i <= high && a[i] <= p)
			i++;
		while (j >= low && p < a[j])
			j--;

		if (i < j)
		{
			swap(&a[i], &a[j]);
		}
	}
	swap(&a[low], &a[j]);

	return j;
}

int lomuto_partition(int *a, int low, int high)
{
	int p = a[high];
	int i = low - 1;
	int j = low;

	for (; j < high; j++)
	{
		if (a[j] <= p)
		{
			i++;
			swap(&a[i], &a[j]);
		}
	}

	swap(&a[++i], &a[j]);

	return i;
}

// O(nlogn), M(logn)
void quick_sort(int *a, int low, int high)
{
	if (low <= high)
	{
		// int p = Hoare_partition(a, low, high);
		int p = lomuto_partition(a, low, high);
		quick_sort(a, low, p - 1);
		quick_sort(a, p + 1, high);
	}
}

void quick_sort_pro(int *a, int low, int high)
{
	if (low <= high)
	{
		// int p = Hoare_partition(a, low, high);
		int p = a[low];
		int i = low;
		int j = high;

		while (i <= j)
		{
			while (i <= high && a[i] <= p)
				i++;
			while (j >= low && p < a[j])
				j--;

			if (i < j)
			{
				swap(&a[i], &a[j]);
			}
		}
		swap(&a[low], &a[j]);

		quick_sort_pro(a, low, j - 1);
		quick_sort_pro(a, j + 1, high);
	}
}

void insertionSort(int *a, int low, int high)
{
	for (int i = low + 1; i <= high; ++i)
	{
		int tmp = a[i];
		int j = i - 1;

		while (j >= low && a[j] >= tmp)
		{
			a[j + 1] = a[j];
			j--;
		}
		a[j + 1] = tmp;
	}
}

void quick_sort_pro2(int *a, int low, int high)
{
	if (high - low <= 13)
	{
		return insertionSort(a, low, high);
	}

	if (low <= high)
	{
		// int p = Hoare_partition(a, low, high);
		int p = a[low];
		int i = low;
		int j = high;

		while (i <= j)
		{
			while (i <= high && a[i] <= p)
				i++;
			while (j >= low && p < a[j])
				j--;

			if (i < j)
			{
				swap(&a[i], &a[j]);
			}
		}
		swap(&a[low], &a[j]);

		quick_sort_pro2(a, low, j - 1);
		quick_sort_pro2(a, j + 1, high);
	}
}

// O(logn), �ݵ�� ���ĵ� ���¿��� �Ѵ�.
int binarysearch(int *a, int n, int key)
{
	int low = 0;
	int high = n - 1;

	while (low <= high)
	{
		int mid = low + ((high - low) >> 1);

		if (a[mid] > key)
			high = mid - 1;
		else if (a[mid] < key)
			low = mid + 1;
		else
			return mid;
	}
	return -1;
}

int lower_bound(int *a, int n, int key)
{
	int low = 0;
	int high = n - 1;

	while (low < high)
	{
		int mid = low + ((high - low) >> 1);

		if (a[mid] < key)
			low = mid + 1;
		else
			high = mid;
	}
	return high;
}

int upper_bound(int *a, int n, int key)
{
	int low = 0;
	int high = n;

	while (low < high)
	{
		int mid = low + ((high - low) >> 1);

		if (a[mid] <= key)
			low = mid + 1;
		else
			high = mid;
	}
	return high;
}

int main()
{
	srand((unsigned int)time(NULL));

	const int n = 25;
	int arr[n];

	for (int i = 0; i < n; i++)
	{
		arr[i] = rand() % 50;
		printf("%d ", arr[i]);
	}
	printf("\n");

	// bubble_sort(arr, n);
	// bubble_sort_simple(arr, n);
	// selection_sort(arr, n);
	// selection_algorithm(arr, n, 3);
	// insertion_sort(arr, n);
	// counting_sort(arr, n);
	// merge_sort(arr, 0, n - 1);
	//  merge_sort_pro(arr, 0, n - 1);
	// quick_sort(arr, 0, n - 1);
	// quick_sort_pro(arr, 0, n - 1);
	quick_sort_pro2(arr, 0, n - 1);

	for (int i : arr)
	{
		printf("%d ", i);
	}
	printf("\n");

	int key = 35;

	int idx = binarysearch(arr, n, key);
	if (idx >= 0)
		printf("%d를 %d위치에서 찾았습니다. \n", key, idx);
	else
		printf("%d를 찾지 못했습니다. \n", key);

	key = 28;
	idx = lower_bound(arr, n, key);
	printf("%d -> %d. \n", key, idx);

	idx = upper_bound(arr, n, key);
	printf("%d -> %d. \n", key, idx);

	return 0;
}