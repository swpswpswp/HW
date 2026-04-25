#include <iostream>
#include <stack>
#include <algorithm>
#include <vector>

using namespace std;

// 存储栈中每个元素及其辅助信息 将 long long 改为 int
struct Node {
    int val;
    int min_v; // 栈内到该位置为止的最小值
    int max_v; // 栈内到该位置为止的最大值
    int max_u; // 栈内该段序列对应的最大U值
    int max_d; // 栈内该段序列对应的最大D值
};

class DSQueue {

    stack<Node> s_in, s_out;

public:
    
    void push(int x) {
        if (s_in.empty()) {
            s_in.push({ x, x, x, 0, 0 });
        }
        else {
            Node prev = s_in.top();
            int cur_min = min(x, prev.min_v);
            int cur_max = max(x, prev.max_v);
            // U = Qj - Qi (j > i), 此时 x 是最新的 Qj, 减去之前的最小 Qi
            int cur_u = max(prev.max_u, x - prev.min_v);
            // D = Qi - Qj (j > i), 此时 x 是最新的 Qj, 之前的最大 Qi 减去它
            int cur_d = max(prev.max_d, prev.max_v - x);
            s_in.push({ x, cur_min, cur_max, cur_u, cur_d });
        }
    }

    void pop() {
        if (s_out.empty()) {
            while (!s_in.empty()) {
                int x = s_in.top().val;
                s_in.pop();
                if (s_out.empty()) {
                    s_out.push({ x, x, x, 0, 0 });
                }
                else {
                    Node prev = s_out.top();
                    int cur_min = min(x, prev.min_v);
                    int cur_max = max(x, prev.max_v);
                    // U = Qj - Qi (j > i), 之前栈内的 max_v 是 Qj, 当前 x 是 Qi
                    int cur_u = max(prev.max_u, prev.max_v - x);
                    // D = Qi - Qj (j > i), 当前 x 是 Qi, 之前栈内的 min_v 是 Qj
                    int cur_d = max(prev.max_d, x - prev.min_v);
                    s_out.push({ x, cur_min, cur_max, cur_u, cur_d });
                }
            }
        }
        if (!s_out.empty()) s_out.pop();
    }

    void query() {
        if (s_in.size() + s_out.size() < 2) {
            cout << "0 0\n";
            return;
        }

        int res_u = 0, res_d = 0;

        // 1. 获取两栈内部的最大值
        if (!s_in.empty()) {
            res_u = max(res_u, s_in.top().max_u);
            res_d = max(res_d, s_in.top().max_d);
        }
        if (!s_out.empty()) {
            res_u = max(res_u, s_out.top().max_u);
            res_d = max(res_d, s_out.top().max_d);
        }

        // 2. 考虑跨栈的情况：Qi 在 s_out (较早), Qj 在 s_in (较晚)
        if (!s_in.empty() && !s_out.empty()) {
            // U = s_in中的最大值 - s_out中的最小值
            res_u = max(res_u, s_in.top().max_v - s_out.top().min_v);
            // D = s_out中的最大值 - s_in中的最小值
            res_d = max(res_d, s_out.top().max_v - s_in.top().min_v);
        }

        cout << res_u << " " << res_d << "\n";
    }
};

int main() {
    // 快速IO
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int M;
    if (!(cin >> M)) return 0;

    DSQueue q;
    while (M--) {
        int type;
        cin >> type;
        if (type == 1) {
            int x;
            cin >> x;
            q.push(x);
        }
        else if (type == 2) {
            q.pop();
        }
        else if (type == 3) {
            q.query();
        }
    }

    return 0;
}