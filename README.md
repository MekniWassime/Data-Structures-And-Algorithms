# Data structures and algoithms
creation and manipulation of AVL trees, B trees, and Heap data structure
-	AVL trees:
    these are self balancing binary search trees, these are [binary search](https://en.wikipedia.org/wiki/Binary_search_tree) trees with the special property of having the height difference between each node's left and right sub-nodes be at most one, if this condition is not met after an insertion or deletion, a rebalancing will take place
    it also inherits the time complexity insertion, deletion and lookup of binary search trees which is `O(h)` where h is the height of the tree, and since this tree is balanced we can say that the height of the tree is equal to `log(n)` where n is the number of nodes of the tree thus the time complexity of these operation being `O(log(n))` in both worst and best case which makes them ideal for lookup intensive applications
- B trees:
	they are a generalisation of binary self balanced search trees which allows nodes to contain at most m values. Insertion, deletion and lookup operations all take `O(log(n))`, this data structure is especially suited for use in databases and file storage systems that deal with large blocks of data
- Heap:
	the Heap is an implementation of the abstract data type priority queue, a Heap (generally represented as trees and implemented as arrays) is useful in cases where the element with the highest priority (or lowest) needs to be accessed and/or removed frequently
