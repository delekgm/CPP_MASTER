#include <iostream>
#include <memory>
#include <vector>

class Test {
// private:
//     int data;
public:
    int data;
    Test() : data{0} { std::cout << "\tTest constructor (" << data << ")" << std::endl; }
    Test(int data) : data {data} { std::cout << "\tTest constructor (" << data << ")" << std::endl; }
    int get_data() const {return data; }
    ~Test() {std::cout << "\tTest destructor (" << data << ")" << std::endl; }
};

// Function prototypes
std::unique_ptr<std::vector<std::shared_ptr<Test>>> make();
void fill(std::vector<std::shared_ptr<Test>> &vec, int num);
void display(const std::vector<std::shared_ptr<Test>>&vec);

std::unique_ptr<std::vector<std::shared_ptr<Test>>> make(){
    return std::make_unique<std::vector<std::shared_ptr<Test>>>();
}

void fill(std::vector<std::shared_ptr<Test>> &vec, int num){ 
    for(auto i = 1; i < num + 1; ++i){
        std::shared_ptr<Test> ptr = std::make_shared<Test>(i * 10);
        vec.push_back(ptr);
    }
}

void display(const std::vector<std::shared_ptr<Test>>&vec){
    for(const auto &test : vec){
        std::cout << test->get_data() << std::endl;
    }
}

int main() {
    std::unique_ptr<std::vector<std::shared_ptr<Test>>> vec_ptr;
    auto pt1 = std::make_unique<Test>(100);
    std::cout << pt1->data << std::endl;
    vec_ptr = make();
    std::cout << "How many data points do you want to enter: ";
    int num;
    std::cin >> num;
    fill(*vec_ptr, num);
    display(*vec_ptr);
    return 0;
}