#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <algorithm>

using namespace std;

std::vector<int> mergetwosortedarray(const vector<int>& a, const vector<int>& b){

    int i = 0;
    int j = 0;
    vector<int> ans(a.size() + b.size());
    int k = 0;
    while(i < a.size() && j < b.size()){
        if(a[i] <= b[j]){
            ans[k] = a[i];
            i++;
            k++;
        }
        else{
            ans[k] = b[j];
            j++;
            k++;
        }
    }
    while(i < a.size()){
        ans[k] = a[i];
        i++;
        k++;
    }
    while(j < b.size()){
        ans[k] = b[j];
        j++;
        k++;
    }
    return ans;
}
vector<int> mergesort(const vector<int> &A,int start, int end){
    if(start == end){
        vector<int> ba(1);
        ba[0] = A[start];
        return ba;
    }
    int mid = (start + end)/2;
    vector<int> fsh = mergesort(A, start, mid);
    vector<int> ssh = mergesort(A, mid+1, end);
    vector<int> sorted = mergetwosortedarray(fsh, ssh);
    return sorted;
}

int partition(vector<int>& A, int pivot, int lo, int hi){
    int i = lo;
    int j = lo;
    while(i <= hi){
        if(A[i] > pivot){
            i++;
        }
        else{
            int temp = A[i];
            A[i] = A[j];
            A[j] = temp;
            i++;
            j++;
        }
    }
    return j-1;
}
void quicksort(vector<int>& A, int lo, int hi){
    if(lo >= hi){
        return;
    }
    int pivot = A[hi];
    int pivotidx = partition(A, pivot, lo, hi);
    quicksort(A, lo, pivotidx-1);
    quicksort(A, pivotidx+1, hi);
}

int main(){
    int N = 15000;
    vector<int> A(N);

    std::srand(static_cast<unsigned>(std::time(0)));

    int lowerbound = -100;
    int upperbound = 10000;

    for(auto &ele : A){
        ele = rand() % (upperbound - lowerbound + 1) + lowerbound;
    }
    cout<< endl;

    auto mstart = std::chrono::high_resolution_clock::now();
    vector<int> mergesorted = mergesort(A, 0, N-1);
    auto mend = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> mtimeTaken = mend - mstart;
    cout << "Time taken for Merge sorting: " << mtimeTaken.count() << " milliseconds" << endl;
    // for(auto ele : mergesorted){
    //     cout <<ele <<" ";
    // }
    cout<< endl;
    cout<< endl;

    auto qstart = std::chrono::high_resolution_clock::now();
    quicksort(A, 0, N - 1);
    auto qend = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> qtimeTaken = qend - qstart;
    std::cout << "Time taken for Quick Sort: " << qtimeTaken.count() << " milliseconds" << std::endl;
    // for(auto ele : A){
    //     cout <<ele <<" ";
    // }

    return 0;
}