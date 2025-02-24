#include <iostream>
#include <vector>
#include <memory>
#include stream>
#include <thread>
#include <cstdlib>
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
    SafeContainer() : m_count(0) {
        ptr = make_unique<int[]>(100);
    }

    void ProcessData() {
        for (int i = 0; i < 100; ++i) {
            ptr[i] = i * i;
        }
    }

private:
    unique_ptr<int[]> ptr;
    int m_count;
};

int global_counter = 0;

int main() {
    vector<int> vec{1,2,3};
    
    for (auto it = vec.begin(); it != vec.end();) {
        if (*it == 2) {
            it = vec.erase(it);
        } else {
            ++it;
        }
    }

    auto fp = make_unique<FILE, decltype(&fclose)>(fopen("data.txt", "w"), &fclose);
    if (!fp) {
        perror("File error");
        return EXIT_FAILURE;
    }

    thread worker([]{
        auto data = make_unique<int>(42);
    });
    worker.join();

    return EXIT_SUCCESS;
}
