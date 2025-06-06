#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_
#include <memory>
#include <vector>
#include "Node.h"

class Linked_List {
    private:
        std::shared_ptr<Node> head;
    public:
        
        class Iterator {
            private:
                std::shared_ptr<Node> current;
            public:
                explicit Iterator(std::shared_ptr<Node> node) : current(node) {}

                std::shared_ptr<Node> operator*() const { return current; }

                Iterator& operator++() {  // Prefix increment
                    if (current) current = current->next;
                    return *this;
                }

                bool operator!=(const Iterator& other) const { return current != other.current; }
        };

        Iterator begin() const { return Iterator(head); }
        Iterator end() const { return Iterator(nullptr); }
        
        // Constructors
        Linked_List() : head(nullptr) {}
        explicit Linked_List(std::vector<int> node_values);

        // Destructor
        ~Linked_List() = default;
        
        // methods
        void iterate(const std::function<void(std::shared_ptr<Node>)>& func) const;

        void visualize() const;

        void add_first(std::shared_ptr<Node> node);

        void add_last(std::shared_ptr<Node> node);

        void add_after(int target_node_data, std::shared_ptr<Node> new_node);

        void add_before(int target_node_data, std::shared_ptr<Node> new_node);

        void remove_node(int target_node_data);
        
        std::shared_ptr<Node> get(const int target_node_data) const;

        void reverse();

        void iter_reverse(const std::function<void(std::shared_ptr<Node>)>& func) const;

};

#endif