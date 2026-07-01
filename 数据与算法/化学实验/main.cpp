#include <cstdio>
#include <algorithm>
#if defined(_MSC_VER)
#include <intrin.h>
#endif
using namespace std;

static const int INF = 0x3f3f3f3f;
static const int MAXN = 25;
static const int CACHE_SIZE = 65536;

static int n;
static int cost[MAXN + 1][MAXN + 1];
static int bestAns;
static int fullMask;

static int dpSmall[(1 << 16) * 16];

static int cacheLast[CACHE_SIZE];
static int cacheRem[CACHE_SIZE];
static int cacheVal[CACHE_SIZE];
static unsigned char cacheUsed[CACHE_SIZE];

static inline int cheb(int ph1, int t1, int ph2, int t2) {
    return max(abs(ph1 - ph2), abs(t1 - t2));
}

static inline int popCount(unsigned x) {
#if defined(_MSC_VER)
    return (int)__popcnt(x);
#else
    return __builtin_popcount(x);
#endif
}

static inline int ctz(unsigned x) {
#if defined(_MSC_VER)
    unsigned long idx;
    _BitScanForward(&idx, x);
    return (int)idx;
#else
    return __builtin_ctz(x);
#endif
}

static inline int relax(int a, int b) {
    if (a >= INF || b >= INF)
        return INF;
    int s = a + b;
    return s >= INF ? INF : s;
}

static void cacheClear() {
    for (int i = 0; i < CACHE_SIZE; i++)
        cacheUsed[i] = 0;
}

static int cacheGet(int last, int rem) {
    unsigned h = (unsigned)(last * 1000003 + rem * 9176);
    for (int i = 0; i < 8; i++) {
        int slot = (h + i) & (CACHE_SIZE - 1);
        if (cacheUsed[slot] && cacheLast[slot] == last && cacheRem[slot] == rem)
            return cacheVal[slot];
    }
    return -1;
}

static void cachePut(int last, int rem, int val) {
    unsigned h = (unsigned)(last * 1000003 + rem * 9176);
    int slot = h & (CACHE_SIZE - 1);
    cacheLast[slot] = last;
    cacheRem[slot] = rem;
    cacheVal[slot] = val;
    cacheUsed[slot] = 1;
}

static int heldKarp() {
    for (int mask = 0; mask <= fullMask; mask++)
        for (int i = 0; i < n; i++)
            dpSmall[(size_t)mask * n + i] = INF;

    for (int i = 0; i < n; i++)
        dpSmall[(1 << i) * n + i] = cost[0][i + 1];

    for (int mask = 1; mask <= fullMask; mask++) {
        if ((mask & (mask - 1)) == 0)
            continue;
        for (int i = 0; i < n; i++) {
            if (!(mask & (1 << i)))
                continue;
            int prev = mask ^ (1 << i);
            int best = INF;
            for (int bits = (unsigned)prev; bits; bits &= bits - 1) {
                int j = ctz(bits);
                best = min(best, relax(dpSmall[(size_t)prev * n + j], cost[j + 1][i + 1]));
            }
            dpSmall[(size_t)mask * n + i] = best;
        }
    }

    int ans = INF;
    for (int i = 0; i < n; i++)
        ans = min(ans, relax(dpSmall[(size_t)fullMask * n + i], cost[i + 1][0]));
    return ans;
}

static int solveRemaining(int last, int rem) {
    if (rem == 0)
        return cost[last][0];

    int hit = cacheGet(last, rem);
    if (hit >= 0)
        return hit;

    int ids[MAXN];
    int k = 0;
    for (int i = 0; i < n; i++)
        if (rem & (1 << i))
            ids[k++] = i;

    const int full = (1 << k) - 1;
    for (int mask = 0; mask <= full; mask++)
        for (int i = 0; i < k; i++)
            dpSmall[(size_t)mask * k + i] = INF;

    for (int i = 0; i < k; i++)
        dpSmall[(1 << i) * k + i] = cost[last][ids[i] + 1];

    for (int mask = 1; mask <= full; mask++) {
        if ((mask & (mask - 1)) == 0)
            continue;
        for (int i = 0; i < k; i++) {
            if (!(mask & (1 << i)))
                continue;
            int prev = mask ^ (1 << i);
            int best = INF;
            for (int bits = (unsigned)prev; bits; bits &= bits - 1) {
                int j = ctz(bits);
                int u = ids[i] + 1, v = ids[j] + 1;
                best = min(best, relax(dpSmall[(size_t)prev * k + j], cost[v][u]));
            }
            dpSmall[(size_t)mask * k + i] = best;
        }
    }

    int ans = INF;
    for (int i = 0; i < k; i++)
        ans = min(ans, relax(dpSmall[(size_t)full * k + i], cost[ids[i] + 1][0]));

    cachePut(last, rem, ans);
    return ans;
}

static int greedyFrom(int start) {
    int cur = cost[0][start + 1];
    int last = start + 1;
    int vis = 1 << start;

    while (vis != fullMask) {
        int nxt = -1, w = INF;
        for (int u = 0; u < n; u++) {
            if (vis & (1 << u))
                continue;
            if (cost[last][u + 1] < w) {
                w = cost[last][u + 1];
                nxt = u;
            }
        }
        cur += w;
        last = nxt + 1;
        vis |= 1 << nxt;
    }
    return cur + cost[last][0];
}

static int cheapBound(int last, int rem) {
    if (rem == 0)
        return cost[last][0];
    int b = cost[last][0];
    for (int u = 0; u < n; u++) {
        if (rem & (1 << u))
            b = min(b, cost[last][u + 1]);
    }
    return b;
}

static void dfsPick(int last, int vis, int cur, int depth) {
    int rem = fullMask ^ vis;

    if (depth == 0 || popCount((unsigned)rem) <= 16) {
        int tail = solveRemaining(last, rem);
        if (cur + tail < bestAns)
            bestAns = cur + tail;
        return;
    }

    int order[MAXN], cnt = 0;
    for (int u = 0; u < n; u++) {
        if (!(vis & (1 << u)))
            order[cnt++] = u;
    }
    for (int i = 0; i < cnt; i++) {
        for (int j = i + 1; j < cnt; j++) {
            if (cost[last][order[j] + 1] < cost[last][order[i] + 1])
                swap(order[i], order[j]);
        }
    }

    for (int t = 0; t < cnt; t++) {
        int u = order[t];
        int w = cost[last][u + 1];
        if (cur + w >= bestAns)
            continue;
        int newRem = rem ^ (1 << u);
        if (cur + w + cheapBound(u + 1, newRem) >= bestAns)
            continue;
        dfsPick(u + 1, vis | (1 << u), cur + w, depth - 1);
    }
}

static int searchLarge() {
    bestAns = INF;
    for (int s = 0; s < n; s++)
        bestAns = min(bestAns, greedyFrom(s));

    int prefix = n - 16;
    if (prefix < 1)
        prefix = 1;
    dfsPick(0, 0, 0, prefix);
    return bestAns;
}

int main() {
    scanf("%d", &n);
    fullMask = (1 << n) - 1;

    const int PH0 = 7, T0 = 25;
    int req_ph[MAXN], res_ph[MAXN], req_t[MAXN], res_t[MAXN], dur[MAXN];
    int totalDur = 0;

    for (int i = 0; i < n; i++) {
        scanf("%d%d%d%d%d", &req_ph[i], &res_ph[i], &req_t[i], &res_t[i], &dur[i]);
        totalDur += dur[i];
    }

    for (int j = 0; j < n; j++)
        cost[0][j + 1] = cheb(PH0, T0, req_ph[j], req_t[j]);
    for (int i = 0; i < n; i++)
        cost[i + 1][0] = cheb(res_ph[i], res_t[i], PH0, T0);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (i != j)
                cost[i + 1][j + 1] = cheb(res_ph[i], res_t[i], req_ph[j], req_t[j]);

    cacheClear();
    int adj = (n <= 16) ? heldKarp() : searchLarge();
    printf("%d\n", adj + totalDur);
    return 0;
}
