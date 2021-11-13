#include <bits/stdc++.h>

using namespace std;

const int LITTLE = 10;
const int BIG    = 1e4;

vector<int> get_random(int num) {
    vector<int> res(num);
    for (int i = 0; i < num; ++i) {
        res[i] = i;
    }
     default_random_engine e;
    uniform_int_distribution<unsigned> u(0, num - 1);

    for (int i = 0; i < num; ++i) {
        swap(res[u(e)], res[u(e)]);
    }

    return res;
}

void test_func(string name, void (*sort_func)(vector<int> &)) {
    cout << "Begin test : " << name << endl;

    cout << "Test LITTLE :";

    auto arr1 = get_random(LITTLE);
    sort_func(arr1);

    if (!is_sorted(arr1.begin(), arr1.end())) {
    	for (int i = 0; i < arr1.size(); ++i) {
    		cout << arr1[i] << ",";
		}
		cout << endl;
        cout << "Failed\n";
    }
    else {
        cout << "Success\n";
    }

    cout << "Test BIG : ";
    arr1 = get_random(BIG);
    clock_t start = clock();
    sort_func(arr1);
    clock_t end = clock();

    if (!is_sorted(arr1.begin(), arr1.end())) {
        cout << "Failed";
    }
    else {
        cout << "Success";
    }

    cout << "\t\t //Use Time : " << ((double)end - start) / CLOCKS_PER_SEC << endl;
    
    reverse(arr1.begin(), arr1.end());
    
    cout << "Test reverse: ";
    
    start = clock();
    sort_func(arr1);
    end = clock();
    
    cout << "Use Time : " << ((double)end - start) / CLOCKS_PER_SEC << endl << endl;
}

void bubble_sort(vector<int> & nums) {
	int n = nums.size();
	
	for (int i = 0; i < n; ++i) {
		int flag = false;
		for (int j = 0; j < n - i - 1; ++j) {
			if (nums[j] > nums[j + 1]) {
				swap(nums[j], nums[j + 1]);
				flag = true;
			}
		}
		if (!flag) {
			break;
		}
	}
}

void select_sort(vector<int> & nums) {
	int n = nums.size();
	
	for (int i = 0; i < n - 1; ++i) {
		
		int s = i;
		for (int j = i + 1; j < n; ++j) {
			if (nums[j] < nums[s]) {
				s = j;
			}
		}
		
		swap(nums[i], nums[s]);
	}
}

void insert_sort(vector<int> &nums) {
	int n = nums.size();
	
	for (int i = 1; i < n; ++i) {
		
		for (int j = i; j >= 1; --j) {
			if (nums[j] >= nums[j - 1]) {
				break;
			}
			
			swap(nums[j], nums[j - 1]);
		}
	}
}

void quick_sort_(vector<int> &nums, int l, int r) {
	if (l >= r) {
		return ;
	}
	
	int i = l + 1, j = r;

	while (true) {
		while (i < r && nums[i] <= nums[l]) {
			++i;
		}
		while (j > l && nums[j] >= nums[l]) {
			--j;
		}
		if (i >= j) {
			break;
		}

		swap(nums[i], nums[j]);
	}

	swap(nums[l], nums[j]);

	quick_sort_(nums, l, j - 1);
	quick_sort_(nums, j + 1, r);
}


void quick_sort(vector<int> & nums) {
	quick_sort_(nums, 0, nums.size() - 1);
}

vector<int> help;

// merge [l,mid], [mid + 1, r];
void merge(vector<int> &nums, int l, int mid, int r) {
	
	for (int i = l; i <= r; ++i) {
		help[i] = nums[i];
	}
	
	int i = l, j = mid + 1, len = l;
	
	while (i <= mid && j <= r) {
		if (help[i] < help[j]) {
			nums[len++] = help[i++];
		}
		else {
			nums[len++] = help[j++];
		}
	}
	
	while (i <= mid) {
		nums[len++] = help[i++];
	}
	while (j <= r) {
		nums[len++] = help[j++];
	}
}

void merge_sort_(vector<int> & nums, int l, int r) {
	
	if (l >= r) {
		return ;
	}
	
	int mid = l + r >> 1;
	
	merge_sort_(nums, l, mid);
	merge_sort_(nums, mid + 1, r);
	
	merge(nums, l, mid, r);
}

void merge_sort(vector<int> & nums) {
	help.resize(nums.size());
	merge_sort_(nums, 0, nums.size() - 1);
}

void shell_sort(vector<int> & nums) {
	
	
	
	for (int dis = nums.size() / 2; dis >= 1; dis >>= 1) {
		for (int i = dis; i < nums.size(); ++i) {
			for (int j = i; j - dis >= 0 && nums[j] < nums[j - dis]; j -= dis) {
				swap(nums[j], nums[j - dis]);
			}
		}
	}
}

void max_heapify(vector<int> & nums, int index, int rightmost) {
	int leftchild = 2 * index + 1;
	int rightchild = 2 * index + 2;
	
	//cout << index << " " << leftchild << " " << rightchild << endl;
	
	int max_id = index;
	if (leftchild < rightmost && nums[leftchild] > nums[max_id]) {
		max_id = leftchild;
	}
	if (rightchild < rightmost && nums[rightchild] > nums[max_id]) {
		max_id = rightchild;
	}
	
	if (max_id != index) {
		swap(nums[index], nums[max_id]);
		max_heapify(nums, max_id, rightmost);
	}
}

void heap_sort(vector<int> &nums) {
	for (int i = nums.size() / 2 - 1; i >= 0; --i) {
		max_heapify(nums, i, nums.size());
	}
	
	for (int i = nums.size() - 1; i >= 1; --i) {
		swap(nums[0], nums[i]);
		max_heapify(nums, 0, i);
	}
}


int main() {

    vector<pair<string, void(*)(vector<int> &)>> hash =
	{
		{"bubble_sort", bubble_sort},
		{"select_sort", select_sort},
		{"insert_sort", insert_sort},
		{"quick_sort" , quick_sort },
		{"merge_sort" , merge_sort },
		{"shell_sort" , shell_sort },
		{"heap_sort"  , heap_sort  },
	};
    

    for (auto & p : hash) {
        test_func(p.first, p.second);
    }
}
