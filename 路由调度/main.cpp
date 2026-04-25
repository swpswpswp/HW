#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <utility>

using namespace std;

struct EdgeArr {
    int to;
    int w;
    int next;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M, K, Q, C;
    if (!(cin >> N >> M >> K >> Q >> C)) return 0;

    // 使用链式数组（类似 adjacency-list 的 CSR/链表实现）存反向图
    vector<int> head(N, -1);
    vector<EdgeArr> edges;
    edges.reserve((size_t)M);

    for (int i = 0; i < M; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        --u; --v; // 转为 0-based
        EdgeArr e; e.to = u; e.w = w; e.next = head[v];
        head[v] = (int)edges.size();
        edges.push_back(e); // 反向边：v -> u (原 u->v)
    }

    vector<int> servers;
    servers.reserve(K);
    for (int i = 0; i < K; ++i) {
        int s; cin >> s; --s;
        if (s >= 0 && s < N) servers.push_back(s);
    }

    vector<int> queries(Q);
    for (int i = 0; i < Q; ++i) {
        int s; cin >> s; --s;
        queries[i] = s;
    }

    const long long INF = numeric_limits<long long>::max() / 4;
    const int L = C + 1;
    // dist[layer * N + node]
    size_t totalNodes = (size_t)L * (size_t)N;
    vector<long long> dist;
    dist.assign(totalNodes, INF);

    using P = pair<long long,int>; // (dist, code)
    priority_queue<P, vector<P>, greater<P>> pq;

    // 多源初始化：所有服务器在 layer 0 距离 0
    for (int s : servers) {
        if (s < 0 || s >= N) continue;
        int code = s; // layer 0 -> code = 0 * N + s
        if (dist[code] > 0) {
            dist[code] = 0;
            pq.emplace(0LL, code);
        }
    }

    while (!pq.empty()) {
        auto cur = pq.top(); pq.pop();
        long long d = cur.first;
        int code = cur.second;
        if (d != dist[code]) continue;
        int layer = code / N;
        int u = code % N;

        // 遍历反向边列表（v = edges[idx].to）
        for (int idx = head[u]; idx != -1; idx = edges[idx].next) {
            const EdgeArr &e = edges[idx];
            int v = e.to;
            long long nd_same = d + (long long)e.w;
            int code_same = layer * N + v;
            if (nd_same < dist[code_same]) {
                dist[code_same] = nd_same;
                pq.emplace(nd_same, code_same);
            }
            // 使用一次直通隧道（转到下一层，权值为 0）
            if (layer + 1 < L) {
                int code_next = (layer + 1) * N + v;
                if (d < dist[code_next]) {
                    dist[code_next] = d;
                    pq.emplace(d, code_next);
                }
            }
        }
    }

    // 输出每个查询的答案（各层最小值）
    for (int i = 0; i < Q; ++i) {
        int s = queries[i];
        if (s < 0 || s >= N) {
            cout << -1 << '\n';
            continue;
        }
        long long ans = INF;
        for (int layer = 0; layer < L; ++layer) {
            long long d = dist[layer * N + s];
            if (d < ans) ans = d;
        }
        if (ans >= INF / 2) cout << -1 << '\n';
        else cout << ans << '\n';
    }

    return 0;
}