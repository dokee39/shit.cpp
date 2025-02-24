#include <iostream>
#include <vector>
#include <memory>
#include <fstream>
#include <thread>
#include <cstdlib>
#include <cstdio>
#include <stdexcept>
#include <algorithm>  // 添加缺失的头文件

using namespace std;

class FinalBlade {
public:
    explicit FinalBlade(vector<bool>&) {
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
        for (int i = 0; i < 100; ++i) {
            ptr[i] = i * i;
        }
    }

private:
    unique_ptr<int[]> ptr;
};

int main() {
    vector<int> vec{1,2,3};
    
    vec.erase(remove(vec.begin(), vec.end(), 2), vec.end());

    ofstream file("data.txt");
    if (!file) {  // 更可靠的文件状态检查
        cerr << "File open failed" << endl;
        return EXIT_FAILURE;
    }

    thread worker([]{
        auto data = make_unique<int>(42);
        static_cast<void>(data);  // 显式忽略未使用变量
    });
    worker.join();

    return EXIT_SUCCESS;
}
