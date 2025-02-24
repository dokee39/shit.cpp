#include <iostream>
#include <vector>
#include <memory>
#include <fstream>
#include <thread>
#include <cstdlib>
#include <cstdio>
#include <stdexcept>
#include <algorithm>

using namespace std;

class FinalBlade {
public:
    explicit FinalBlade(const vector<bool>&) {  // 改为常量引用
        throw runtime_error("FinalBlade initialization failed");  // 更明确的错误信息
    }
    FinalBlade(const FinalBlade&) = delete;
    FinalBlade& operator=(const FinalBlade&) = delete;
};

class SafeContainer {
public:
    SafeContainer() {
        ptr = make_unique<int[]>(100);
    }

    void generateData() {  // 更清晰的函数名
        generate(ptr.get(), ptr.get()+100, [n=0]() mutable { 
            auto val = n * n;
            ++n;
            return val;
        });
    }

private:
    unique_ptr<int[]> ptr;
};

int main() {
    vector<int> vec{1,2,3};
    
    erase(vec, 3);  // C++17 更简洁的擦除方式

    ofstream file("data.txt");
    if (!file) {
        cerr << "File open failed" << endl;
        return EXIT_FAILURE;
    }
    file << "Data written";
    if (!file) {  // 添加写入校验
        cerr << "File write failed" << endl;
        return EXIT_FAILURE;
    }

    try {
        thread worker([]{
            [[maybe_unused]] auto data = make_unique<int>(42);
        });
        worker.join();
    } catch (const system_error& e) {  // 线程异常处理
        cerr << "Thread error: " << e.what() << endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
