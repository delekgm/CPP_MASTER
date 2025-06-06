#include <iostream>
#include "Linked_List.h"

int main() {
    Linked_List list({1, 2, 3, 4});

    // Visualize
    list.visualize();

    // Add first
    std::shared_ptr<Node> new_first_node = std::make_shared<Node>(8);
    list.add_first(new_first_node);

    // Add last
    std::shared_ptr<Node> new_last_node = std::make_shared<Node>(9);
    list.add_last(new_last_node);

    list.visualize();

    // Add after
    std::shared_ptr<Node> new_node_after = std::make_shared<Node>(76);
    list.add_after(2, new_node_after);

     list.visualize();

    // Add before
    std::shared_ptr<Node> new_node_before = std::make_shared<Node>(11);
    list.add_before(4, new_node_before);

    list.visualize();

    // Remove node
    list.remove_node(76);

    list.visualize();

    list.reverse();

    list.visualize();

    // Iter reverse
    int sum = 0;

    list.iter_reverse([&sum](std::shared_ptr<Node> node) { sum += node->get_data(); });

    std::cout << sum << std::endl;

    // Search
    int target = 3;
    bool found = false;

    list.iterate([&](std::shared_ptr<Node> node) {
        if (node->get_data() == target) {
            found = true;
        }
    });

    if (found) std::cout << "Found " << target << " in the list!" << std::endl;

    std::cout << std::endl;
    return 0;
}