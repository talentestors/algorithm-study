# 一致性哈希（Consistent Hashing）

一致性哈希是一种分布式哈希表（DHT）算法，主要用于在动态变化的分布式系统中实现高效的键值分布。

## 核心特性

**节点位置固定，新增节点仅插入一点，只影响它与前驱之间的数据。**

这是区别于传统等长分片的本质区别：等长分片需要整体移动边界，必然导致全局重映射；一致性哈希允许不等长分区，从而保留原有节点位置。

## 算法原理

### 哈希环

1. 将哈希值空间组织成一个环形结构
2. 每个节点映射到环上的一个位置
3. 每个键也映射到环上，顺时针找到的第一个节点即为所属节点

### 节点增删

- **新增节点**：在环上插入一个新位置，只接管该位置与前驱节点之间的数据
- **删除节点**：移除其在环上的位置，原有数据由前驱节点接管

### 虚拟节点

为每个物理节点创建多个虚拟节点，均匀分布在环上，可实现更均衡的负载分布。

## 核心特点

| 特点 | 说明 |
|------|------|
| 单调性 | 新增/删除节点时，只影响局部键的映射 |
| 负载均衡 | 通过虚拟节点实现更均匀的分布 |
| 分散性 | 相同的键总是映射到相同的节点 |
| 位置固定 | 原有节点在环上的位置始终不变 |

## C++ 实现

```cpp
#include <iostream>
#include <map>
#include <string>
#include <functional>

// MurmurHash2 实现
unsigned int MurmurHash2(const void *key, int len) {
    const unsigned int m = 0x5bd1e995;
    const int r = 24;
    unsigned int h = 0;
    const unsigned char *data = (const unsigned char *)key;

    while (len >= 4) {
        unsigned int k = *(unsigned int *)data;
        k *= m;
        k ^= k >> r;
        k *= m;
        h *= m;
        h ^= k;
        data += 4;
        len -= 4;
    }

    if (len == 3) h ^= data[2] << 16;
    if (len == 2) h ^= data[1] << 8;
    if (len == 1) h ^= data[0];
    h *= m;

    h ^= h >> 13;
    h *= m;
    h ^= h >> 15;

    return h;
}

class ConsistentHash {
private:
    std::map<unsigned int, std::string> ring;  // 哈希环: hash -> node
    std::map<std::string, int> node_vnodes;     // 节点虚拟节点数统计
    int virtual_nodes;                           // 每个物理节点的虚拟节点数
    std::function<unsigned int(const std::string&)> hash_func;

public:
    ConsistentHash(int vnodes = 150,
                   std::function<unsigned int(const std::string&)> hf = nullptr)
        : virtual_nodes(vnodes) {
        if (hf) {
            hash_func = hf;
        } else {
            hash_func = [](const std::string& s) {
                return MurmurHash2(s.c_str(), s.length());
            };
        }
    }

    // 添加物理节点
    void add_node(const std::string& node) {
        if (node_vnodes.find(node) != node_vnodes.end()) return;

        for (int i = 0; i < virtual_nodes; ++i) {
            std::string vnode = node + "#vn" + std::to_string(i);
            unsigned int hash = hash_func(vnode);
            ring[hash] = node;
        }
        node_vnodes[node] = virtual_nodes;
    }

    // 删除物理节点
    void remove_node(const std::string& node) {
        if (node_vnodes.find(node) == node_vnodes.end()) return;

        for (int i = 0; i < virtual_nodes; ++i) {
            std::string vnode = node + "#vn" + std::to_string(i);
            unsigned int hash = hash_func(vnode);
            ring.erase(hash);
        }
        node_vnodes.erase(node);
    }

    // 获取键所属的节点
    std::string get_node(const std::string& key) {
        if (ring.empty()) return "";

        unsigned int hash = hash_func(key);
        auto it = ring.lower_bound(hash);

        // 环的起点
        if (it == ring.end()) {
            it = ring.begin();
        }

        return it->second;
    }

    // 统计各节点负载
    void print_distribution(const std::vector<std::string>& keys) {
        std::map<std::string, int> dist;
        for (const auto& key : keys) {
            dist[get_node(key)]++;
        }
        for (const auto& p : dist) {
            std::cout << p.first << ": " << p.second << std::endl;
        }
    }
};

int main() {
    ConsistentHash ch(150);

    // 添加节点
    ch.add_node("192.168.1.1:6379");
    ch.add_node("192.168.1.2:6379");
    ch.add_node("192.168.1.3:6379");

    // 测试
    std::vector<std::string> keys = {"user:1000", "user:2000", "user:3000",
                                       "user:4000", "user:5000"};
    for (const auto& key : keys) {
        std::cout << key << " -> " << ch.get_node(key) << std::endl;
    }

    // 新增节点
    std::cout << "\n新增节点后:\n";
    ch.add_node("192.168.1.4:6379");
    for (const auto& key : keys) {
        std::cout << key << " -> " << ch.get_node(key) << std::endl;
    }

    return 0;
}
```

## 适用场景

- **分布式缓存系统**（Redis Cluster、Memcached）
- **负载均衡器**
- **CDN 内容分发**
- **分布式数据库分片**

## 参考资料

- Blog: [eli.thegreenplace.net - Consistent Hashing](https://eli.thegreenplace.net/2025/consistent-hashing)
- [Consistent Hashing - Wikipedia](https://en.wikipedia.org/wiki/Consistent_hashing)
