from typing import TypeVar, Generic

T = TypeVar('T')


class BinaryTree(Generic[T]):
    class _Node:
        def __init__(self, value: T):
            self.value = value
            self.left = None
            self.right = None

    def __init__(self):
        self._root = None

    def add(self, value: T):
        self._root = self._add(self._root, value)

    def _add(self, node: _Node, value: T) -> 'BinaryTree._Node':
        if node is None:
            return self._Node(value)
        elif value < node.value:
            node.left = self._add(node.left, value)
        else:
            node.right = self._add(node.right, value)
        return node

    def inorder(self):
        return self._inorder(self._root)

    def _inorder(self, node: _Node) -> list[T]:
        if node is None:
            return []
        return [*self._inorder(node.left), node.value, *self._inorder(node.right)]

    def __contains__(self, value: T) -> bool:
        return self._contains(self._root, value)

    def _contains(self, node: _Node, value: T) -> bool:
        if node is None:
            return False
        elif value < node.value:
            return self._contains(node.left, value)
        elif value > node.value:
            return self._contains(node.right, value)
        else:
            return True
