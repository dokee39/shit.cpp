#include <iostream>
#include <vector>
#include <memory>
#include <fstream>
#include <thread>
#include <cstdlib>
#include <cstdio>
#include <stdexcept>

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
    if (!file.is_open()) {
        perror("File error");
        return EXIT_FAILURE;
    }

    thread worker([]{
        [[maybe_unused]] auto data = make_unique<int>(42);
    });
    worker.join();

    return EXIT_SUCCESS;
}
