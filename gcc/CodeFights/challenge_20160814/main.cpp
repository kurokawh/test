
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <map>
#include <assert.h>

int pairwise(std::vector< int > arr, int N) {
  std::map<int, int> indices;
  for (int i = 0;  i < arr.size(); i++) {
    for (int j = i + 1 ; j < arr.size(); j++) {
      if (arr[i] + arr[j] == N) {
//        	sum_of_indices += i + j;
			printf("array[%d]: %d, array[%d]: %d\n", i, arr[i], j, arr[j]);
			int min = arr[i] < arr[j] ? arr[i]: arr[j];
			if (indices[min] <= 0 || indices[min] > (i + j)) {
				indices[min] = (i + j);
			}
			break;
      }
    }
  }
  int sum_of_indices = 0;
  for (std::map<int,int>::iterator it=indices.begin(); it!=indices.end(); ++it) {
	  sum_of_indices += it->second;
  }
  return sum_of_indices;
}

int main(int argc, char** argv)
{
//	int iarr1[] = {1, 3, 2, 4};
	int iarr1[] = {1, 4, 2, 3, 0, 5, 2};
	std::vector<int> arr1(iarr1, iarr1 + (sizeof(iarr1)/sizeof(int)));
//	int ret = pairwise(arr1, 4);
	int ret = pairwise(arr1, 7);
	printf("ret: %d\n", ret);
	return 0;
}
