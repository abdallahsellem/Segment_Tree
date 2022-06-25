#include <iostream>

using namespace std;
int seg_tree[(int) 4e6 + 5];
int arr[(int) 4e6 + 5];
int lazy[(int) 4e6];
int n;

//propagation to update nodes with value of lazy
int propagate(int node, int l, int r) {
    int left_child = node * 2;
    int right_child = node * 2 + 1;
    int mid = (l + r) >> 1;
    seg_tree[left_child] += (mid - l + 1) * lazy[node];
    seg_tree[right_child] += (r - mid) * lazy[node];
    lazy[left_child] += lazy[node];
    lazy[right_child] += lazy[node];
    lazy[node] = 0;
}

//updating only one point of leafs and what's up on the tree
void update_point(int i, int value) {
    int node = i + n - 1;
    arr[node] += value;
    seg_tree[node] += value;
    while (node > 1) {
        node /= 2;
        int left_child = node * 2;
        int right_child = node * 2 + 1;
        seg_tree[node] = seg_tree[left_child] + seg_tree[right_child];
    }
    return;
}

//constructing the tree
void Build(int node=1, int l=1, int r=n) {
    if (l == r) {
        seg_tree[node] = arr[l];
        return;
    }
    int mid = (l + r) >> 1;
    int left_child = 2 * node;
    int right_child = 2 * node + 1;
    Build(left_child, l, mid);
    Build(right_child, mid + 1, r);
    seg_tree[node] = seg_tree[left_child] + seg_tree[right_child];
}

//query range on the tree
int query(int x, int y,int node = 1,int l=1, int r=n){
    if (l >= x && r <= y) {
        return seg_tree[node];
    }
    if (x > r || y < l) {
        return 0;
    }
    propagate(node, l, r);
    int mid = (l + r) >> 1;
    int left_child = 2 * node;
    int right_child = 2 * node + 1;
    int Left_value = query(x, y,left_child,l,mid);
    int Right_value = query( x, y,right_child,mid + 1, r);
    return Left_value + Right_value;
}

void update_range(int x, int y, int value,int node = 1,int l=1, int r=n) {
    if (l >= x && r <= y) {
        lazy[node] += value;
        seg_tree[node] += (r - l + 1) * value;
        return;
    }
    if (x > r || y < l) {
        return;
    }
    propagate(node, l, r);
    int left_child = node * 2;
    int right_child = node * 2 + 1;
    int mid = (l + r) >> 1;
    update_range( x, y,value,left_child, l, mid);
    update_range(x, y, value,right_child, mid + 1, r);
    seg_tree[node] = seg_tree[left_child] + seg_tree[right_child];
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    Build();
}
