#ifndef _LINKED_NODE_H_
#define _LINKED_NODE_H_
#include <memory>

struct Node {
    int data;
    std::shared_ptr<Node> next;
    std::weak_ptr<Node> previous;  // Use weak_ptr to break circular reference

    explicit Node(int data_) : data{data_}, next{nullptr} {}
    
    [[nodiscard]] int get_data() const { return data; }

    [[nodiscard]] std::shared_ptr<Node> get_next() const { return next; }
    [[nodiscard]] std::shared_ptr<Node> get_previous() const { return previous.lock(); }  // Convert weak_ptr to shared_ptr safely
    // nodiscard makes tells the compiler to make sure the return is used
};

#endif