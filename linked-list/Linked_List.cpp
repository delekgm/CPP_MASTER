#include <iostream>
#include "Linked_List.h"

Linked_List::Linked_List(std::vector<int> node_values) {
    if (node_values.empty()) {  // Handle empty list case
        head = nullptr;
        std::cout << "Empty list of values" << std::endl;
        return;
    }
    this->head = std::make_shared<Node>(node_values[0]);

    std::shared_ptr<Node> current = this->head;
    std::shared_ptr<Node> previous = nullptr;


    if(node_values.size() > 1) {
        for(auto i = 1; i < node_values.size(); ++i) {
            current->next = std::make_shared<Node>(node_values[i]);
            previous = current;
            current = current->next;
            current->previous = previous;
        }
    }
}

void Linked_List::iterate(const std::function<void(std::shared_ptr<Node>)>& func) const {
    for (auto it = this->begin(); it != this->end(); ++it) {
        func(*it);  // Apply function to each node
    }
}

void Linked_List::visualize() const {
    for (auto it = this->begin(); it != this->end(); ++it) {
        std::cout << (*it)->get_data() << "->";
    }

    std::cout << "null" << std::endl;
}

void Linked_List::add_first(std::shared_ptr<Node> node) {
    if (!node) return;  // Prevent adding a null node

    node->next = this->head;
    if (this->head) {
        this->head->previous = node;  // Update old head's `previous` pointer
    }

    this->head = node;
}

void Linked_List::add_last(std::shared_ptr<Node> node) {
    if(!node) return;

    if(!this->head) {
        this->head = node;
        node->previous.reset();  // Reset weak_ptr instead of assigning nullptr
        return;
    }

    std::shared_ptr<Node> current_node = this->head;

    while(current_node->next) {
        current_node = current_node->next;
    }

    current_node->next = node;
    node->previous = current_node; 
}

void Linked_List::add_after(int target_node_data, std::shared_ptr<Node> new_node) {
    if(!new_node) return;

    if(!this->head) throw std::runtime_error("List is empty!");

    bool found = false;
    this->iterate([&](std::shared_ptr<Node> node) {
        if (node->get_data() == target_node_data) {
            if(node->next) node->next->previous = new_node;
            new_node->next = node->next;
            new_node->previous = node;
            node->next = new_node;
            found = true;
        }
    });
    if(!found) throw std::runtime_error("Target node not found!");
}

void Linked_List::add_before(int target_node_data, std::shared_ptr<Node> new_node) {
    if(!new_node) return;

    if(!this->head) {
        this->head = new_node;
        std::cout << "List is empty added node as head" << std::endl;
        return;
    }

    if(this->head->get_data() == target_node_data) {
        this->add_first(new_node);
        return;
    }

    bool found = false;
    std::shared_ptr<Node> current_node = this->head;
    std::shared_ptr<Node> prev_node = nullptr;

    while(current_node) {
        if(current_node->get_data() == target_node_data) {
            found = true;
            prev_node->next = new_node;
            new_node->previous = prev_node;
            new_node->next = current_node;
            current_node->previous = new_node;
            return;
        }
        prev_node = current_node;
        current_node = current_node->next;
    }

    if(!found) throw std::runtime_error("Target node not found!");
}

void Linked_List::remove_node(int target_node_data) {
    if(!this->head) throw std::runtime_error("List is empty!");

    if(this->head->get_data() == target_node_data) {
        this->head = this->head->next;
        if (this->head) this->head->previous.reset();
        return;
    }

    bool found = false;
    std::shared_ptr<Node> current_node = this->head;
    std::shared_ptr<Node> prev_node = nullptr;

    while(current_node) {
        if(current_node->get_data() == target_node_data) {
            found = true;
            if(prev_node) {
                prev_node->next = current_node->next;
            }
            
            if (current_node->next) {
                current_node->next->previous = prev_node;
            }
            return;
        }
        prev_node = current_node;
        current_node = current_node->next;
    }

    if(!found) throw std::runtime_error("Target node not found!");
}

std::shared_ptr<Node> Linked_List::get(const int target_node_data) const {
    if(!this->head) throw std::runtime_error("List is empty!");

    std::shared_ptr<Node> current_node = this->head;
    while(current_node) {
        if(current_node->get_data() == target_node_data) {
            return current_node;
        }
        current_node = current_node->next;
    }
    return nullptr;
}

void Linked_List::reverse() {
    if (!this->head || !this->head->next) return;  // Empty list or single node = nothing to reverse

    std::shared_ptr<Node> current = this->head;
    std::shared_ptr<Node> prev = nullptr;

    while (current) {
        std::shared_ptr<Node> next_node = current->next; // Save next node

        // Swap `next` and `previous`
        current->next = prev;
        current->previous = next_node;

        // Move `prev` and `current` forward
        prev = current;
        current = next_node;
    }

    // Update `head` to be the last node (previously the tail)
    this->head = prev;
}

void Linked_List::iter_reverse(const std::function<void(std::shared_ptr<Node>)>& func) const {
    if (!this->head) return;  // Handle empty list case

    // Move to the last node
    std::shared_ptr<Node> current = this->head;
    while (current->next) {
        current = current->next;
    }

    // Iterate backwards
    while (current) {
        func(current);  // Apply function to current node
        current = current->previous.lock();  // Use `lock()` to convert `weak_ptr` to `shared_ptr`
    }
}

// Now, let's move on to implementing Linked_List.cpp in a step-by-step manner.