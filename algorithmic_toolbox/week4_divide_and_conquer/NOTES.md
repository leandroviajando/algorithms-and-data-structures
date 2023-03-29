# Divide and Conquer

The divide-and-conquer technique usually involves designing an algorithm that solves a problem by splitting it into several disjoint subproblems, solving them recursively, and then combining their results to get an answer for the initial problem.

## Polynomial Multiplication

- Naive Solution
- Naive Divide and Conquer Solution
- Karatsuba Algorithm

## The Master Theorem

Given some constants $a>0$, $b>1$, $d\geq0$, if $T(n) = a T(\lceil \frac{n}{b} \rceil) + O(n^d)$, then:

$$
T(n) = \begin{cases}
    O(n^d) & \text{if } d > \log_b a \iff \frac{a}{b^d} < 1 \\
    O(n^d \log n) & \text{if } d = \log_b a \iff \frac{a}{b^d} = 1 \\
    O(n^{\log_b a}) & \text{if } d < \log_b a \iff \frac{a}{b^d} > 1 \\
\end{cases}
$$

$$
\frac{a}{b^d} < 1 \iff \sum_{i=0}^{\log_b n}{O(n^d (\frac{a}{b^d})^i)} = O(n^d)
$$

$$
\frac{a}{b^d} = 1 \iff \sum_{i=0}^{\log_b n}{O(n^d (\frac{a}{b^d})^i)} = \sum_{i=0}^{\log_b n}{O(n^d)} = (1 + \log_b n) O(n^d)
$$

$$
\frac{a}{b^d} > 1 \iff \sum_{i=0}^{\log_b n}{O(n^d (\frac{a}{b^d})^i)} = O(O(n^d) (\frac{a}{b^d})^{\log_b n}) = O(O(n^d) (\frac{a^{\log_b n}}{b^{d \log_b n}})) = O(O(n^d) (\frac{n^{\log_b a}}{n^d})) = O(n^{\log_b a})
$$

## Majority Element

[Article](https://leetcode.com/problems/majority-element/editorial/)

## Sorting

Sorted data allow for more efficient search.

### Selection Sort

Selection sort runs in place, i.e. it requires a constant amount of extra memory.

Its running time is $O(n^2)$, $n$ comparisons and $n$ swaps:

```c++
#include <iostream>
#include <vector>

void selectionSort(std::vector<int>& arr) {
  int n = arr.size();

  for (int i = 0; i < n - 1; i++) {
    int minIdx = i;

    for (int j = i + 1; j < n; j++)
      if (arr[j] < arr[minIdx])
        minIdx = j;

    if (minIdx != i)
      std::swap(arr[i], arr[minIdx]);
  }
}

int main() {
  std::vector<int> arr = {5, 2, 7, 1, 9, 3};
  selectionSort(arr);

  for (int num : arr)
    std::cout << num << std::endl;

  return 0;
}
```

The number of iterations of the inner loop is actually an arithmetic series: $(n-1) + (n-2) + \cdots + 1 = \frac{n(n-1)}{2}$. Asymptotically, this is $O(n^2)$.

Other examples of quadratic sorting algorithms are insertion sort and bubble sort.

### Merge Sort

Merge sort is a divide-and-conquer algorithm. It divides the input array into two halves, calls itself recursively for the two halves, and then merges the two sorted halves.

Its running time is $O(n \log n)$.

```c++
#include <iostream>
#include <vector>

void merge(std::vector<int>& arr, int left, int mid, int right) {
  int n1 = mid - left + 1;
  int n2 = right - mid;

  std::vector<int> leftArr(n1);
  std::vector<int> rightArr(n2);

  for (int i = 0; i < n1; i++)
    leftArr[i] = arr[left + i];

  for (int j = 0; j < n2; j++)
    rightArr[j] = arr[mid + 1 + j];

  int i = 0;
  int j = 0;
  int k = left;

  while (i < n1 && j < n2) {
    if (leftArr[i] <= rightArr[j]) {
      arr[k] = leftArr[i];
      i++;
    } else {
      arr[k] = rightArr[j];
      j++;
    }
    k++;
  }

  while (i < n1) {
    arr[k] = leftArr[i];
    i++;
    k++;
  }

  while (j < n2) {
    arr[k] = rightArr[j];
    j++;
    k++;
  }
}

void mergeSort(std::vector<int>& arr, int left, int right) {
  if (left < right) {
    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
  }
}

int main() {
  std::vector<int> arr = {5, 2, 7, 1, 9, 3};
  mergeSort(arr, 0, arr.size() - 1);

  for (int num : arr)
    std::cout << num << std::endl;

  return 0;
}
```

The running time of merging two sorted arrays of size $n$ is $O(n)$. The number of recursive calls is $O(\log n)$, and the number of elements in each array is $O(n)$.

Hence the running time of merge sort satisfies a recurrence relation of the form $T(n) = 2T(\lceil \frac{n}{2} \rceil) + O(n)$, which is solved by the master theorem to be $O(n \log n)$.

### Comparison-Based Sorting

A comparison-based sorting algorithm, e.g. selection sort, bubble sort, merge sort, quick sort, etc., is an algorithm that sorts a list of elements by repeatedly comparing pairs of two elements and swapping them if they are in the wrong order.

The worst-case running time of any comparison-based sorting algorithm is at least $O(n \log n)$, i.e. at least $n \log n$ operations are needed to sort $n$ elements.

### Non-Comparison-Based Sorting

An example of a non-comparison-based sorting algorithm is counting sort, which runs in $O(n)$ time.

By a single scan of the array $A$, count the number of occurrences of each number $1 \leq k \leq M$ in $A$ and store it in `Count[k]`. Then, for each number $k$, output $Count[k]$ times.

```c++
#include <algorithm>
#include <iostream>
#include <vector>

void countingSort(std::vector<int>& arr) {
  int n = arr.size();
  int maxVal = *std::max_element(arr.begin(), arr.end());

  std::vector<int> count(maxVal + 1, 0);
  std::vector<int> sortedArr(n);

  for (int i = 0; i < n; i++)
    count[arr[i]]++;

  for (int i = 1; i <= maxVal; i++)
    count[i] += count[i - 1];

  for (int i = n - 1; i >= 0; i--) {
    sortedArr[count[arr[i]] - 1] = arr[i];
    count[arr[i]]--;
  }

  for (int i = 0; i < n; i++)
    arr[i] = sortedArr[i];
}

int main() {
  std::vector<int> arr = {5, 2, 7, 1, 9, 3};
  countingSort(arr);

  for (int num : arr)
    std::cout << num << std::endl;

  return 0;
}
```

Provided all elements of $A$ are integers in the range $1 \leq k \leq M$, the running time of counting sort is $O(n + M)$.

If $M = O(n)$, the running time is $O(n)$.

In summary,

- merge sort uses the divide-and-conquer strategy to sort an $n$-element array in $O(n \log n)$ time
- no comparison-based algorithm (asymptotically) can do better than that
- one can do better if something is known about the input array in advance, e.g. that it contains small integers in a given range

### Quick Sort

```c++
#include <iostream>
#include <vector>

void quickSort(std::vector<int>& arr, int left, int right) {
  int i = left, j = right;
  int pivot = arr[(left + right) / 2];

  while (i <= j) {
    while (arr[i] < pivot) i++;
    while (arr[j] > pivot) j--;

    if (i <= j) {
      std::swap(arr[i], arr[j]);
      i++;
      j--;
    }
  }

  if (left < j) quickSort(arr, left, j);
  if (i < right) quickSort(arr, i, right);
}

int main() {
  std::vector<int> arr = {5, 3, 2, 7, 6, 8, 1, 4};

  quickSort(arr, 0, arr.size() - 1);

  for (int i = 0; i < arr.size(); i++)
    std::cout << arr[i] << std::endl;

  return 0;
}
```

Running time is quadratic for unbalanced partitions, and linearithmic for balanced partitions. *To avoid unbalanced partitions, a random pivot is chosen.*

```c++
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

int partition(std::vector<int>& arr, int left, int right) {
  int pivot = arr[left + rand() % (right - left + 1)];  // select a random pivot
  int i = left - 1;

  for (int j = left; j <= right; j++)
    if (arr[j] < pivot) {
      i++;
      std::swap(arr[i], arr[j]);
    }

  std::swap(arr[i + 1], arr[right]);

  return i + 1;
}

void quickSort(std::vector<int>& arr, int left, int right) {
  if (left < right) {
    int pivotIndex = partition(arr, left, right);

    quickSort(arr, left, pivotIndex - 1);
    quickSort(arr, pivotIndex + 1, right);
  }
}

int main() {
  std::vector<int> arr = {5, 3, 2, 7, 6, 8, 1, 4};
  srand(time(NULL));  // seed the random number generator

  quickSort(arr, 0, arr.size() - 1);

  for (int i = 0; i < arr.size(); i++)
    std::cout << arr[i] << std::endl;

  return 0;
}
```

An additional performance improvment is a three-way partitioning so that only the part with the elements less than the pivot and the part with the elements greater than the pivot need to be recursively sorted, since the elements equal to the pivot are already in the right place.
