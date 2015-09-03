#include <cstdio>
#include <string>
#include <iostream>
#include <fstream>

#define debug 0

using namespace std;

const int MAXN = 50001;

int n, m, sp;
string str;
ifstream fin("data.out");
ofstream fout("datamain.out");

struct sTreeNode{
    int left, right; //区间信息
    int lch, rch;    // 左右儿子
    int base, add;
    int delta, inc;
}tree[MAXN << 2];

void createTree(int rt, int left, int right){

    tree[rt].left = left; tree[rt].right = right;
    tree[rt].add = 0; tree[rt].delta = tree[rt].inc = 0;

    if (left == right){
        tree[rt].lch = tree[rt].rch = 0;
        tree[rt].base  = str[left] - 'A';
        return;
    }

    tree[rt].base = -1;
    tree[rt].lch = 2*rt; tree[rt].rch = 2*rt + 1;
    int mid = (left + right) >> 1;
    createTree(tree[rt].lch, left, mid);
    createTree(tree[rt].rch, mid+1, right);
}

void update(int rt, int left, int right, int key, int type){
    if (!rt) return;
    if (left > tree[rt].right || right < tree[rt].left) return;
    if (left<=tree[rt].left && tree[rt].right<=right){
        // 节点完全包含在区间内
        if (type == 1){
            tree[rt].base = key;
            tree[rt].add = 0;
            tree[rt].delta = tree[rt].inc = 0;
        } else if (type == 2){
            tree[rt].add += key;
        } else if (type == 4){
            tree[rt].delta += key + (tree[rt].left - left);
            tree[rt].inc ++;
        }

        return ;

    }else {

        int mid = (tree[rt].left + tree[rt].right) >> 1;

        if (tree[rt].base != -1){
            tree[tree[rt].lch].base = tree[tree[rt].rch].base = tree[rt].base;

            tree[tree[rt].lch].add = tree[rt].add;
            tree[tree[rt].rch].add = tree[rt].add;

            tree[tree[rt].lch].delta = tree[rt].delta;
            tree[tree[rt].rch].delta = tree[rt].delta + (mid - tree[rt].left + 1) * tree[rt].inc;

            tree[tree[rt].lch].inc = tree[rt].inc;
            tree[tree[rt].rch].inc = tree[rt].inc;

            tree[rt].base = -1;
        } else {

            tree[tree[rt].lch].add += tree[rt].add;
            tree[tree[rt].rch].add += tree[rt].add;

            tree[tree[rt].lch].delta += tree[rt].delta;
            tree[tree[rt].rch].delta += tree[rt].delta + (mid - tree[rt].left + 1) * tree[rt].inc;

            tree[tree[rt].lch].inc += tree[rt].inc;
            tree[tree[rt].rch].inc += tree[rt].inc;

        }

        tree[rt].add = 0;
        tree[rt].delta = tree[rt].inc = 0;

        update(tree[rt].lch, left, right, key, type);
        update(tree[rt].rch, left, right, key, type);
    }
}

int f[MAXN];

void getResult(int rt){
    if (tree[rt].base != -1){
        int delta = tree[rt].delta;
        for (int i=tree[rt].left; i<=tree[rt].right; i++){
            f[i] = tree[rt].base + tree[rt].add + delta;
            delta += tree[rt].inc;
        }
    } else {

        int mid = (tree[rt].left + tree[rt].right) >> 1;

        tree[tree[rt].lch].add += tree[rt].add;
        tree[tree[rt].rch].add += tree[rt].add;

        tree[tree[rt].lch].delta += tree[rt].delta;
        tree[tree[rt].rch].delta += tree[rt].delta + (mid - tree[rt].left + 1) * tree[rt].inc;

        tree[tree[rt].lch].inc += tree[rt].inc;
        tree[tree[rt].rch].inc += tree[rt].inc;

        tree[rt].add = 0;
        tree[rt].delta = tree[rt].inc = 0;

        getResult(tree[rt].lch);
        getResult(tree[rt].rch);
    }
    return ;
}

void typeAns(){
    for (int i=1; i<=n; i++){
        int k=i+sp;
        while (k > n)
            k -= n;
        cout<<char(f[k]%26 + 'A');
    }
    cout<<endl;
    return ;
}

int main(){

    char cmd[4];

    cin>>n>>m;
    cin>>str;

    str = "!" + str;
    sp = 0;

    createTree(1, 1, n);

    while (--m >= 0){
        //cout<<m<<endl;
        int type;
        scanf("%s %d", cmd, &type);
        if (type == 1){
            int i, j;
            char c;
            scanf("%d %d %c", &i, &j, &c);
            int new_i = sp + i;
            int new_j = sp + j;

            while (new_i >n)
                new_i -= n;
            while (new_j > n)
                new_j -= n;

            if (new_i > new_j){
                update(1, new_i, n, c-'A', 1);
                update(1, 1, new_j, c-'A', 1);
            }else{
                update(1, new_i, new_j, c - 'A', 1);
            }

        }else if (type == 2){
            int i, j, k;
            scanf("%d %d %d", &i, &j, &k);
            int new_i = (sp + i) % n;
            int new_j = (sp + j) % n;

            while (new_i >n)
                new_i -= n;
            while (new_j > n)
                new_j -= n;

            if (new_i > new_j){
                update(1, new_i, n, k, 2);
                update(1, 1, new_j, k, 2);
            }else{
                update(1, new_i, new_j, k, 2);
            }

        }else if (type == 3){
            int k;
            scanf("%d", &k);
            sp = sp + k;
            sp = sp % n;
        } else if (type == 4){
            int i, j;
            scanf("%d %d", &i, &j);

            int new_i = (sp + i) % n;
            int new_j = (sp + j) % n;

            while (new_i >n)
                new_i -= n;
            while (new_j > n)
                new_j -= n;

            if (new_i > new_j){
                update(1, new_i, n, 1, 4);
                update(1, 1, new_j, n+2-new_i, 4);
            }else{
                update(1, new_i, new_j, 1, 4);
            }
        }

         #if debug
        for (int i=1; i<=4*n; i++){
            cout<<i<<" Base="<<tree[i].base<<" Add= "<<tree[i].add<<endl;
        }
        #endif
    }
    getResult(1);
    typeAns();
    return 0;
}
