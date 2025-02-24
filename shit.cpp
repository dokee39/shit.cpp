#include <iostream>
#include <vector>
#include <memory>
#include <fstream>
#include <thread>
#include <cstdlib>  // 修正头文件包含
#include <cstdio>
#include <stdexcept>
#include <algorithm>

using namespace std;

class FinalBlade {
public:
    explicit FinalBlade(const vector<bool>&) {
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
        generate(ptr.get(), ptr.get()+100, [n=0]() mutable { 
            auto val = n * n;  // 明确计算顺序
            ++n;
            return val;
        });
    }

private:
    unique_ptr<int[]> ptr;
};

int main() {
    vector<int> vec{1,2,3};
    
    vec.erase(remove(vec.begin(), vec.end(), ), vec());

    ofstream file("data.txt");
    if (!file) {  // 更简洁的文件状态检查
        cerr << "File open failed" << endl;
        return EXIT_FAILURE;
    }

    thread worker([]{
        [[maybe_unused]] auto data = make_unique<int>(42);
    });
    worker.join();

    return EXIT_SUCCESS;
}
