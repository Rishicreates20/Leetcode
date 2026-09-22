#include <stdlib.h>
#include <string.h>

#define MAXK 5

typedef struct {
    int prod;                 /* product of segment mod k            */
    int cnt[MAXK][MAXK];      /* cnt[a][b] as described above        */
} Node;

static Node *tree;
static int   segSize;         /* power of two >= n                   */
static int   K;

/* leaf at position pos gets value v */
static void setLeaf(int pos, int v)
{
    int i = segSize + pos;
    int p = v % K;
    Node *nd = &tree[i];
    nd->prod = p;
    memset(nd->cnt, 0, sizeof(nd->cnt));
    for (int a = 0; a < K; a++)
        nd->cnt[a][(a * p) % K] = 1;
}

/* recompute node i from its two children */
static void pull(int i)
{
    Node *nd = &tree[i];
    const Node *L = &tree[i << 1];
    const Node *R = &tree[(i << 1) | 1];
    int lp = L->prod;

    nd->prod = (lp * R->prod) % K;
    for (int a = 0; a < K; a++) {
        int la = (a * lp) % K;           /* residue entering the right child */
        for (int b = 0; b < K; b++)
            nd->cnt[a][b] = L->cnt[a][b] + R->cnt[la][b];
    }
}

int *resultArray(int *nums, int numsSize, int k, int **queries,
                 int queriesSize, int *queriesColSize, int *returnSize)
{
    K = k;
    segSize = 1;
    while (segSize < numsSize) segSize <<= 1;

    tree = (Node *)calloc((size_t)segSize * 2, sizeof(Node));

    /* padding leaves: identity (no prefixes, product 1 mod k) */
    for (int i = numsSize; i < segSize; i++)
        tree[segSize + i].prod = 1 % K;

    for (int i = 0; i < numsSize; i++)
        setLeaf(i, nums[i]);
    for (int i = segSize - 1; i >= 1; i--)
        pull(i);

    int *res = (int *)malloc(sizeof(int) * queriesSize);
    int *leftNodes  = (int *)malloc(sizeof(int) * 64);
    int *rightNodes = (int *)malloc(sizeof(int) * 64);

    for (int q = 0; q < queriesSize; q++) {
        int idx = queries[q][0], val = queries[q][1];
        int start = queries[q][2], x = queries[q][3];

        /* point update, persists across queries */
        setLeaf(idx, val);
        for (int i = (segSize + idx) >> 1; i >= 1; i >>= 1)
            pull(i);

        /* fold nodes covering [start, numsSize) strictly left to right */
        int lc = 0, rc = 0;
        int lo = start + segSize, hi = numsSize + segSize;
        while (lo < hi) {
            if (lo & 1) leftNodes[lc++] = lo++;
            if (hi & 1) rightNodes[rc++] = --hi;
            lo >>= 1;
            hi >>= 1;
        }

        int a = 1 % K, total = 0;
        for (int i = 0; i < lc; i++) {
            total += tree[leftNodes[i]].cnt[a][x];
            a = (a * tree[leftNodes[i]].prod) % K;
        }
        for (int i = rc - 1; i >= 0; i--) {
            total += tree[rightNodes[i]].cnt[a][x];
            a = (a * tree[rightNodes[i]].prod) % K;
        }
        res[q] = total;
    }

    free(leftNodes);
    free(rightNodes);
    free(tree);
    *returnSize = queriesSize;
    return res;
}