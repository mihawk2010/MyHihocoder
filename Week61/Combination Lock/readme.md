## Combination Lock 解题过程##

因为我是个菜鸟，整个的解题思路是按照[http://hihocoder.com/discuss/question/2120](http://hihocoder.com/discuss/question/2120) , 这里我只是把我写代码的过程记录一下，以供以后回顾。 代码核心数据结构是线段树以解决区间更新的问题。 

1. 由于第一次写代码的时候模仿分析报告中的代码， 我想一次实现所有功能导致自己思路也很混乱。所以之后我决定一个功能一个功能的来实现， 即先写好cmd 1，然后调试成功，再加入cmd 2，测试直至成功，然后最后4个功能全部完成。

2. 线段树比较难理解的就是延迟标记的实现了， 我之前学习的时候也弄的不是很清楚。 这次里面的标记就是base这个变量了。 **注意**： 在分析报告中提到了base和same两个词， 而实际上我们把他理解为一个意思就好了， 即「 该区间字符是否一样， 一样base等于该字符， 否则base=-1 」

代码中最麻烦的，我觉得是这一段：
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

这里如果 'base != -1' 表示为标记不为0事， 则更新至子节点。 注意，这里的更新使用的是等号， 原因为如果标记不为0， 表明这段区间被**修改**过了， 所以之前的base, add, delta, inc的值都没有意义了。  如果'base == -1'，表明这段区间并没有被修改过， 所以我们使用+=传递信息。 传递完之后， 原来的节点的信息全部初始化即可。 

**注意**： 这里update()传递时， 我们不需要讲区间[left, right]分割， 因为我们在此之前处理过区间不相交的情况了， 这只是另外一种写法。

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

这里也不同与一般的query(), 我们省略了区间信息。 这里如果我们遇到了标记的区间， 我们就不用再次向下搜索了， 因为这个区间全是base字符，直接输出即可。 另一方面， 如果没有标记，则我们要向下搜索， 进行类似的pushDown操作即可， 这里注意可以不用将原节点信息清楚（。。我以为还要加）， 因为我们不会在回到该节点了。 

 

