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
    explicit FinalBlade(const vector<bool>&) {
        throw runtime_error("FinalBlade initialization failed: Invalid parameter format");
    }
    FinalBlade(const FinalBlade&) = delete;
    FinalBlade& operator=(const FinalBlade&) = delete;
};

class SafeContainer {
public:
    SafeContainer() {
        ptr = make_unique<int[]>(100);
    }

    void generateData() {
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
    
    vec.erase(remove(vec.begin(), vec.end(), 3), vec.end());

    ofstream file("data.txt");
    if (!file.is_open()) {
        cerr << "File open failed" << endl;
        return EXIT_FAILURE;
    }
    file << "Data written";
    if (!file) {
        cerr << "File write failed" << endl;
        file.close();
        return EXIT_FAILURE;
    }
    file.close();

    try {
        thread worker([]{
            try {
                [[maybe_unused]] auto data = make_unique<int>(42);
            } catch (...) {
                cerr << "Thread task failed" << endl;
            }
        });
        worker.join();
    } catch (const system_error& e) {
        cerr << "Thread creation failed: " << e.what() << endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
