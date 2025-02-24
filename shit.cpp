#include <iostream>
#include <vector>
#include <memory>
#include <fstream>
#include <thread>
#include stdlib>
#include <cstdio>
#include <stdexcept>
#include <algorithm>

using namespace std;

class FinalBlade {
public:
    explicit FinalBlade(const vector<bool>&) {  // 改为const引用
        throw runtime_error("Init failed");
    }
    FinalBlade(const FinalBlade&) = delete;
    FinalBlade& operator=(const FinalBlade&) = delete;
};

class SafeContainer {
public:
    SafeContainer() {
        ptr = make_unique<int[]>(100);
    }

    void ProcessData() {
        // 使用算法优化初始化
        generate(ptr.get(), ptr.get()+100, [n=0]() mutable { return n*n++; });
    }

private:
    unique_ptr<int[]> ptr;
};

int main() {
    vector<int> vec{1,2,3};
    
    vec.erase(remove(vec.begin(), vec.end(), 2), vec.end());

    ofstream file("data.txt");
    if (!file.is_open()) {  // 更明确的文件打开检查
        cerr << "File open failed" << endl;
        return EXIT_FAILURE;
    }

    thread worker([]{
        [[maybe_unused]] auto data = make_unique<int>(42);  // C++17属性
    });
    worker.join();

    return EXIT_SUCCESS;
}
