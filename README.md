# AVL Tree — Self-Balancing Binary Search Tree
### Data Structures & Algorithms Project | Language: C

---

## 1. Project Overview

This project implements an **AVL Tree** (Adelson-Velsky and Landis Tree) in the C programming language.

An AVL Tree is a self-balancing Binary Search Tree (BST) where the difference in heights between the left and right subtrees of any node — known as the **Balance Factor** — is always maintained within the range of **-1 to +1**.

Whenever an insertion or deletion operation violates this property, the tree automatically performs **rotation operations** to restore balance. This guarantees that all major operations run in **O(log n)** time in every case, unlike a standard BST which can degrade to **O(n)** in the worst case with sorted input.

---

## 2. DSA Topics Covered

### 2.1 Binary Search Tree (BST) Property
The AVL Tree is built on top of a Binary Search Tree. Every node satisfies:
- All values in the **left subtree** are **less than** the node's value
- All values in the **right subtree** are **greater than** the node's value
- No duplicate values are stored

### 2.2 Tree Node Structure
Each node stores four fields:

| Field   | Type            | Purpose                                          |
|---------|-----------------|--------------------------------------------------|
| data    | int             | The integer value stored in the node             |
| left    | struct Node *   | Pointer to the left child node                   |
| right   | struct Node *   | Pointer to the right child node                  |
| height  | int             | Height of the node used to compute balance factor|

### 2.3 Height & Balance Factor
- **Height** of a node = number of edges on the longest path to a leaf
- **Balance Factor (BF)** = Height(Left Subtree) - Height(Right Subtree)
- A node is balanced when BF is **-1, 0, or +1**
- If BF goes beyond this range after an operation, rotations are triggered

```
Balance Factor = Height(Left Subtree) - Height(Right Subtree)
```

### 2.4 Rotations (Core of AVL Balancing)
There are four rotation cases:

| Case               | Condition                                      | Fix                                          |
|--------------------|------------------------------------------------|----------------------------------------------|
| Left-Left (LL)     | BF > 1 and new key < left child's key          | Single Right Rotation                        |
| Right-Right (RR)   | BF < -1 and new key > right child's key        | Single Left Rotation                         |
| Left-Right (LR)    | BF > 1 and new key > left child's key          | Left Rotate left child, then Right Rotate    |
| Right-Left (RL)    | BF < -1 and new key < right child's key        | Right Rotate right child, then Left Rotate   |

### 2.5 Tree Traversals
Three standard depth-first traversal methods are implemented:

| Traversal  | Order               | Use Case                              |
|------------|---------------------|---------------------------------------|
| Inorder    | Left → Root → Right | Produces sorted ascending output      |
| Preorder   | Root → Left → Right | Used to copy or serialize the tree    |
| Postorder  | Left → Right → Root | Used to safely delete/free the tree   |

### 2.6 Recursive Algorithms
All major operations use recursion to traverse the tree. Recursive calls unwind back up the tree after insertion or deletion, updating heights and triggering rotations at each ancestor node that becomes unbalanced.

### 2.7 Dynamic Memory Allocation
- Every new node is allocated on the heap using `malloc()`
- On exit (Option 8), `freeTree()` uses postorder traversal to `free()` every node
- This ensures there are no memory leaks

---

## 3. Functions Reference

| Function              | Description                                              | Time Complexity |
|-----------------------|----------------------------------------------------------|-----------------|
| `newNode(data)`       | Creates and returns a new AVL node with height 1         | O(1)            |
| `height(node)`        | Returns height of a node; 0 if NULL                      | O(1)            |
| `getBalance(node)`    | Returns balance factor of a node                         | O(1)            |
| `rightRotate(y)`      | Performs a right rotation around node y                  | O(1)            |
| `leftRotate(x)`       | Performs a left rotation around node x                   | O(1)            |
| `insert(root, data)`  | Inserts a value and rebalances the tree                  | O(log n)        |
| `deleteNode(root, data)` | Deletes a value and rebalances the tree               | O(log n)        |
| `minValueNode(node)`  | Returns the node with the minimum value in a subtree     | O(log n)        |
| `search(root, data)`  | Searches for a value; returns 1 if found, 0 if not       | O(log n)        |
| `inorder(root)`       | Prints values in ascending sorted order                  | O(n)            |
| `preorder(root)`      | Prints values in preorder sequence                       | O(n)            |
| `postorder(root)`     | Prints values in postorder sequence                      | O(n)            |
| `printTree(root, space)` | Displays tree visually with heights and balance factors| O(n)           |
| `freeTree(root)`      | Frees all allocated memory using postorder traversal     | O(n)            |
| `displayMenu()`       | Prints the interactive operations menu                   | O(1)            |

---

## 4. Complexity Analysis

| Operation  | AVL Tree (Worst Case) | Simple BST (Worst Case) |
|------------|-----------------------|--------------------------|
| Insert     | O(log n)              | O(n)                     |
| Delete     | O(log n)              | O(n)                     |
| Search     | O(log n)              | O(n)                     |
| Traversal  | O(n)                  | O(n)                     |
| Space      | O(n)                  | O(n)                     |

The guaranteed **O(log n)** performance makes AVL Trees far superior to unbalanced BSTs, especially when dealing with sorted or nearly-sorted input which causes a plain BST to degenerate into a linked list.

---

## 5. How to Compile & Run

### Requirements
- GCC Compiler installed on your system
- Any terminal or command prompt (Linux, macOS, or Windows with MinGW)

### Compile
```bash
gcc avl_tree.c -o avl_tree
```

### Run
```bash
./avl_tree        # Linux / macOS
avl_tree.exe      # Windows
```

---

## 6. Menu Options

| Option | Operation             | Description                                           |
|--------|-----------------------|-------------------------------------------------------|
| 1      | Insert a node         | Enter an integer to insert into the AVL tree          |
| 2      | Delete a node         | Enter a value to remove from the tree                 |
| 3      | Search a value        | Check if a value exists in the tree                   |
| 4      | Inorder Traversal     | Print all values in sorted ascending order            |
| 5      | Preorder Traversal    | Print values in Root-Left-Right order                 |
| 6      | Postorder Traversal   | Print values in Left-Right-Root order                 |
| 7      | Display Tree Structure| Visual sideways tree with height and balance factor   |
| 8      | Exit                  | Free all memory and terminate the program             |

---

## 7. Sample Output

After inserting values **30, 20, 40, 10, 25**:

```
Inorder Traversal:   10 20 25 30 40
Preorder Traversal:  30 20 10 25 40
Postorder Traversal: 10 25 20 40 30
```

Tree Structure display (Option 7) — rotated 90 degrees:
```
          40 (h=1, bf=0)
     30 (h=3, bf=1)
          25 (h=1, bf=0)
     20 (h=2, bf=0)
          10 (h=1, bf=0)
```

---

## 8. Key Concepts Summary

| Concept        | Definition                                                                 |
|----------------|----------------------------------------------------------------------------|
| BST Property   | Left child < Parent < Right child for all nodes                            |
| Balance Factor | Height(Left) - Height(Right), must always be -1, 0, or +1                 |
| LL Rotation    | Right rotate when left-left insertion causes imbalance                     |
| RR Rotation    | Left rotate when right-right insertion causes imbalance                    |
| LR Rotation    | Left rotate left child + right rotate root for left-right imbalance        |
| RL Rotation    | Right rotate right child + left rotate root for right-left imbalance       |
| Inorder        | Traversal that always yields sorted output for a BST                       |
| Recursion      | All tree operations use recursive calls to traverse and update nodes       |
| malloc/free    | C dynamic memory functions used to create and destroy nodes                |
| O(log n)       | Guaranteed worst-case complexity for all operations due to AVL balancing   |

---

## 9. File Structure

```
avl-tree-project/
│
├── avl_tree.c       # Main C source file with all AVL Tree logic
└── README.md        # Project documentation (this file)
```

---

*AVL Tree Project — C Programming | Data Structures & Algorithms*
