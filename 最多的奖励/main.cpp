#include <iostream>
#include <cstdint>
#include <cstdio>
#include <climits>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

/*
 外存分层处理方案（适用于内存受限的评测）：
 - 将输入按层序写入临时二进制文件 (1 byte / node)。
 - 自底向上逐层读取孩子层的 "max_down"（int16_t）并计算父层的 "max_down"，
   每层结果写入临时文件供上层读取。整个过程内存使用极小。
 - 处理时同时维护全局最大路径和 `ans`。
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int h;
    if (!(cin >> h)) return 0;
    if (h <= 0) { cout << 0 << '\n'; return 0; }

    // 计算节点总数 n = 2^h - 1
    uint64_t n = ((uint64_t)1 << h) - 1ULL;

    // 临时原始节点文件（按层序，每个节点 1 字节）
    FILE* orig = tmpfile();
    if (!orig) { // 若 tmpfile 不可用，尝试用命名文件
        orig = fopen("nodes.tmp", "w+b");
        if (!orig) { cerr << "无法创建临时文件\n"; return 0; }
    }

    int x;
    int global_max_single = INT_MIN;
    for (uint64_t i = 0; i < n; ++i) {
        cin >> x;
        int8_t b = static_cast<int8_t>(x);
        fwrite(&b, 1, 1, orig);
        if (x != -99 && x > global_max_single) global_max_single = x;
    }

    long long ans = global_max_single; // 至少可以取单个节点

    // 辅助临时文件，用于保存每层的 max_down（int16_t）
    FILE* child = nullptr;

    // 自底向上处理每一层
    for (int L = h - 1; L >= 0; --L) {
        uint64_t nodes = (uint64_t)1 << L; // 当前层节点数
        uint64_t level_offset = ((uint64_t)1 << L) - 1ULL; // 前面节点数量（层序偏移）

        // 如果是叶子层，直接从 orig 读节点值并写入 child (int16_t)
        if (L == h - 1) {
            // 创建 child 临时文件
            child = tmpfile();
            if (!child) child = fopen("child.tmp", "w+b");
            if (!child) { cerr << "无法创建临时文件(child)\n"; return 0; }

            // 定位到该层在 orig 中的起始位置
            fseek(orig, (long)level_offset, SEEK_SET);
            for (uint64_t i = 0; i < nodes; ++i) {
                int8_t vb;
                if (fread(&vb, 1, 1, orig) != 1) { vb = (int8_t)-99; }
                int16_t down = (vb == (int8_t)-99) ? 0 : (int16_t)vb;
                fwrite(&down, sizeof(int16_t), 1, child);
                // 单节点值已在读取输入时纳入 global_max_single
            }
            rewind(child);
        } else {
            // parent 层节点数 = nodes
            // child 文件当前包含 level L+1 的 int16_t 值，共 2*nodes 项
            FILE* parent = tmpfile();
            if (!parent) parent = fopen("parent.tmp", "w+b");
            if (!parent) { cerr << "无法创建临时文件(parent)\n"; return 0; }

            // 定位父层在 orig 中的起点
            fseek(orig, (long)level_offset, SEEK_SET);
            // child 文件当前指针应在开始位置
            rewind(child);

            for (uint64_t p = 0; p < nodes; ++p) {
                int8_t pv;
                if (fread(&pv, 1, 1, orig) != 1) pv = (int8_t)-99;

                // 从 child 读取左右孩子的 down（int16_t）
                int16_t left = 0, right = 0;
                if (fread(&left, sizeof(int16_t), 1, child) != 1) left = 0;
                if (fread(&right, sizeof(int16_t), 1, child) != 1) right = 0;

                if (pv == (int8_t)-99) {
                    // 父不存在，向上不贡献
                    int16_t pd = 0;
                    fwrite(&pd, sizeof(int16_t), 1, parent);
                } else {
                    int left_gain = max(0, (int)left);
                    int right_gain = max(0, (int)right);
                    int curr = (int)pv + left_gain + right_gain;
                    if (curr > ans) ans = curr;
                    int pdint = (int)pv + max(left_gain, right_gain);
                    int16_t pd = (int16_t)pdint; // 值在范围内（h<=25 保证）
                    fwrite(&pd, sizeof(int16_t), 1, parent);
                }
            }

            // 释放旧 child 文件，使用 parent 作为新 child
            fclose(child);
            child = parent;
            rewind(child);
        }
    }

    // 清理临时文件
    if (child) fclose(child);
    if (orig) fclose(orig);

    cout << ans << '\n';
    return 0;
}