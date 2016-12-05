#include <iostream>
#include <stack>
#include <unordered_map>
using namespace std;



int constructSTUtil(int arr[], int ss, int se, int* & st, int si){
    //only one element
    if(ss==se){
        st[si]=ss;
        return st[si];
    }

    int mid=(ss+se)/2;
    int t1=constructSTUtil(arr, ss, mid, st, si*2+1);
    int t2=constructSTUtil(arr, mid+1, se, st, si*2+2);

    st[si] = arr[t1]>arr[t2]? t2 : t1;
    return st[si];
}
//segment tree implementation
int* constructST(int arr[], int n){
    int max_size=2*n-1;

    int* st = new int[max_size*2];
    constructSTUtil(arr, 0, n-1, st, 0);
    return st;
}
int RMQ(int arr[], int st[], int ss, int se, int qs, int qe, int idx){
    //if[ss,se] is in [qs, qe]
    if(qs<=ss and qe>=se)
        return st[idx];
    //if segment of this node is outside the given range
    if(se<qs or qe<ss)
        return INT16_MAX;

    //two intervals overlapped
    int mid=(ss+se)/2;
    int t1=RMQ(arr,st, ss, mid, qs, qe, 2*idx+1);
    int t2=RMQ(arr,st, mid+1, se, qs, qe, 2*idx+2);
    if(t1==INT16_MAX) return t2;
    if(t2==INT16_MAX) return t1;
    return arr[t1]<arr[t2]? t1:t2;


}

int getMaxAreaRec(int hist[], int *st, int n, int l, int r)
{
    // Base cases
    if (l > r)  return INT16_MIN;
    if (l == r)  return hist[l];

    // Find index of the minimum value in given range
    // This takes O(Logn)time
    int m = RMQ(hist, st, 0, n-1, l, r, 0);

    /* Return maximum of following three possible cases
       a) Maximum area in Left of min value (not including the min)
       a) Maximum area in right of min value (not including the min)
       c) Maximum area including min */
    return max(max(getMaxAreaRec(hist, st, n, l, m-1),
               getMaxAreaRec(hist, st, n, m+1, r)),
               (r-l+1)*(hist[m]) );
}

// The main function to find max area
int getMaxArea(int hist[], int n)
{
    // Build segment tree from given array. This takes
    // O(n) time
    int *st = constructST(hist, n);

    // Use recursive utility function to find the
    // maximum area
    return getMaxAreaRec(hist, st, n, 0, n-1);
}
int main(){
    int arr[]={6,1,5,4,5,2,6};
    int n=7;


    int ans = getMaxArea(arr, n);
    cout<<ans;
    return 0;

}
