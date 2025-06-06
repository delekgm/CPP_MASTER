class LinkedList:
    def __init__(self, nodes=None):
        self.head = None

        if nodes is not None:
            # print(nodes)
            node = Node(data=nodes.pop(0))
            self.head = node
            node.previous = None
            # print(nodes)
            # print(node.data)
            for element in nodes:
                # print(node.data)
                node.next = Node(data=element)
                previous = node
                node = node.next
                node.previous = previous

    def __iter__(self):
        node = self.head
        while node is not None:
            yield node
            # print(node.data)
            node = node.next

    def __repr__(self):
        node = self.head
        nodes = []
        while node is not None:
            nodes.append(node.data)
            node = node.next
        nodes.append("None")
        return " -> ".join(nodes)

    def add_first(self, node):
        node.next = self.head
        self.head = node

    def add_last(self, node):
        if self.head is None:
            self.head = node
            return
        # if obj is a group of objects you can iterate them this way
        for current_node in self:
            pass
        current_node.next = node

    def add_after(self, target_node_data, new_node):
        if self.head is None:
            raise Exception("List is empty")

        for iter_node in self:
            if iter_node.data == target_node_data:
                new_node.next = iter_node.next
                iter_node.next = new_node
                return
        raise Exception("Node with data '%s' not found" % target_node_data)

    def add_before(self, target_node_data, new_node):
        if self.head is None:
            raise Exception("List is empty added node as head")

        if self.head.data == target_node_data:
            return self.add_first(new_node)

        prev_node = self.head
        for node in self:
            if node.data == target_node_data:
                prev_node.next = new_node
                new_node.next = node
                return
            prev_node = node
        raise Exception("Node with data '%s' not found" % target_node_data)

    def remove_node(self, target_node_data):
        if self.head is None:
            raise Exception("List is empty")

        if self.head.data == target_node_data:
            self.head = self.head.next
            return

        prev_node = self.head
        for node in self:
            if node.data == target_node_data:
                prev_node.next = node.next
                return
            prev_node = node
        raise Exception("Node with data '%s' not found" % target_node_data)

    def get(self, target_node_index: int):
        if self.head is None:
            raise Exception("List is empty")

        count = 0
        for node in self:
            if target_node_index == count:
                return node
            if node.next is None and target_node_index != count:
                raise Exception("Index out of range")
            count += 1

    def reverse(self):
        if self.head is None:
            raise Exception("List is empty")

        stack = []
        temp = self.head

        while temp:
            stack.append(temp)
            temp = temp.next

        head = temp = stack.pop()
        while len(stack) > 0:
            temp.next = stack.pop()
            temp = temp.next
        temp.next = None

        self.head = head
        return

    def iter_reverse(self):
        if self.head is None:
            raise Exception("List is empty")

        prev = None
        current = self.head
        while current is not None:
            next = current.next
            # next is b
            current.next = prev
            # current.next is none
            prev = current
            # prev is head
            current = next
        #    current is b
        self.head = prev
        return


class Node:
    def __init__(self, data):
        self.data = data
        self.next = None
        self.previous = None

    # def __repr__(self):
    #     return self.data


# llist = LinkedList()
#
# first_node = Node("a")
# llist.head = first_node
#
# second_node = Node("b")
# third_node = Node("c")
# first_node.next = second_node
# second_node.next = third_node
#
# print(llist.__repr__())
# print(first_node.__repr__())

llist = LinkedList(nodes=["a", "b", "c", "d", "e"])
# llist.add_last(Node("f"))
# llist.add_first(Node("0"))
# llist.add_before(target_node_data="b", new_node=Node("bc"))
# llist.add_after(target_node_data="d", new_node=Node("de"))
# print(llist)
# llist.remove_node(target_node_data="de")
print(llist)
# print(llist.get(4).data)
for val in llist.__iter__():
    print(val.data)
llist.iter_reverse()
print(llist)
