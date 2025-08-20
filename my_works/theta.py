class BinarySearchTree:
    def __init__(self ,data):
        self.data = data
        self.left = None
        self.right = None

    def add_child(self , data):
        if data == self.data:
            return
        if data < self.data:
            if self.left:
                self.left.add_child(data)
            else:
                self.left = BinarySearchTree(data)
        else:
            if self.right:
                self.right.add_child(data)
            else:
                self.right = BinarySearchTree(data)

    def in_order_traversal(self):
        elements = []

        if self.left:
            elements += self.left.in_order_traversal()

        elements.append(self.data)

        if self.right:
            elements += self.right.in_order_traversal()
       


        return elements

def build_tree(elements):
    if not elements:
        return None  # or raise ValueError("Elements list is empty")
    root = BinarySearchTree(elements[0])
    for i in range(1 , len(elements)):
        root.add_child(elements[i])
    return root


if __name__ == "__main__":
    numbers = []

    n = int(input("Enter the number of element you wanna add: "))
    for i in range(n):
       ins = int(input(f"No [{i+1}]. =  "))
       numbers.append(ins)
    if len(numbers) > 0:
        number_tree = build_tree(numbers)
        print(number_tree.in_order_traversal())
    else:
        print("No elements to add to the tree.")
  


