# Algorithms

## What are Algorithms?

An **algorithm** is a step-by-step procedure or formula for solving a problem. It's a finite sequence of well-defined instructions that, given an input, produces an output and terminates after a finite number of steps.

There are three main characeristics to an algorithm:
- Generality: it should work for a set of inputs, not just a specific case
- Predictability: it should produce the same output for the same input every time
- Result-oriented: it should solve the problem it's designed to solve

Here is a simple example of an algorithm that finds the perimeter of a rectangle:

```text
1. Input: length (l) and width (w) of the rectangle;
2. Calculate perimeter (p) using the formula: p = 2 * (l + w);
3. Output: perimeter (p);
```
Here we will always have a result because the operations multiplication and addition are well-defined for any real numbers provided as length and width.

Here is a simple example of an algorithm that finds the value of `x` in `a * x = b`:
```text
1. Input: a and b;
2. find x by dividing b by a. -> x = b / a
3. Output: x;
```
However, this algorithm does not work for all inputs. If `a` is `0`, then the algorithm will fail because division by zero is undefined. We also have the case where both `a` and `b` are `0`, which leads to infinite solutions for `x`. Therefore we need to modify the algorithm to handle these special cases:

```text
1. Input: a and b;
2. If a = 0, check b:
   - If b = 0, output: "Infinite solutions for x";
   - Else, output: "No solution for x";
3. If a ≠ 0, find x by dividing b by a. -> x = b / a and output: x;
```

## How to describe an algorithm

- **Pseudocode**: A high-level description of the algorithm using plain language mixed with programming constructs. It is not tied to any specific programming language.
- **Block diagrams**: Visual representation of the algorithm using shapes and arrows to illustrate the flow of control.
- **Programming languages**: Here are some examples of the algorithms we used earlier, implemented in Pascal and C/C++.

```pascal
program per;
var a,b,p: real;
begin
    read(a,b);
    p := 2 * (a + b);
    writeln(p);
end.
```
```c
int main() {
    float a, b, p;
    cin >> a >> b;
    p = 2 * (a + b);
    cout << p << endl;
    return 0;
}
```

## How the computer executes an algorithm

For the computer to execute an algorithm it firs needs to be translated to a language it understands. This translation end up being a bunch of instruction/commands that the CPU needs to execute. The CPU communicates with the RAM where all the instructions and needed variables live. Reads the next command and the variables it relies on and executes.

### The Recipe Analogy
Think of an algorithm like a cooking recipe:
- **Input**: Ingredients (your data - like an unsorted list of numbers)
- **Process**: Step-by-step instructions (the operations you perform - like comparing and swapping)
- **Output**: The finished dish (your result - like a sorted list)

Just as a recipe tells you "first mix the flour and eggs, then add milk, then bake for 30 minutes," an algorithm tells you exactly what steps to perform and in what order.

### Why Do Algorithms Matter?

Imagine you have 1 million customer records to sort by name. You could:
- Use a simple algorithm that takes 3 days to complete
- Use an efficient algorithm that takes 3 seconds to complete

Both give the same result, but one is vastly better. Understanding algorithms helps you choose the right tool for the job

---

## Types of Algorithms

### 1. Sorting Algorithms
**Purpose**: Arrange data in a particular order (ascending/descending)

#### Bubble Sort
**The Concept**: Like bubbles rising to the surface of water

**How it works step-by-step**:
1. Start at the beginning of the list
2. Compare the first two elements
3. If the first is larger than the second, swap them
4. Move to the next pair and repeat
5. Continue until you reach the end - the largest element is now at the end
6. Repeat the entire process for the remaining elements
7. Keep doing this until no more swaps are needed

**Visual Example**: Sorting [5, 2, 8, 1]
```
Pass 1:
[5, 2, 8, 1] → Compare 5 and 2 → Swap → [2, 5, 8, 1]
[2, 5, 8, 1] → Compare 5 and 8 → No swap → [2, 5, 8, 1]
[2, 5, 8, 1] → Compare 8 and 1 → Swap → [2, 5, 1, 8]
Result: Largest element (8) is now at the end

**The Concept**: Divide and conquer - break the problem into smaller pieces

**How it works step-by-step**:
1. Pick an element from the array (called the "pivot")
2. Partition: rearrange the array so that:
   - All elements smaller than the pivot go to its left
   - All elements larger than the pivot go to its right
3. The pivot is now in its final sorted position
4. Recursively apply the same process to the left and right subarrays
5. When subarrays have 0 or 1 elements, you're done (they're sorted)

**Visual Example**: Sorting [7, 2, 1, 6, 8, 5, 3]
```
Step 1: Choose pivot (let's pick the last element: 3)
[7, 2, 1, 6, 8, 5, 3]
                    ↑ pivot

Step 2: Partition around 3
- Elements ≤ 3: [2, 1]
- Pivot: [3]
- Elements > 3: [7, 6, 8, 5]
Result: [2, 1] [3] [7, 6, 8, 5]

Step 3: Recursively sort [2, 1]
Pivot = 1
Result: [1] [2]

Step 4: Recursively sort [7, 6, 8, 5]
Pivot = 5
- Elements ≤ 5: []
- Pivot: [5]
- Elements > 5: [7, 6, 8]
Result: [5] [7, 6, 8]

Step 5: Continue until all sorted
**The Concept**: Divide the problem until it's trivial, then combine the solutions

**How it works step-by-step**:
1. **Divide**: Split the array into two halves
2. Keep splitting each half until you have arrays of size 1
3. **Conquer**: Merge pairs of small arrays back together in sorted order
4. Keep merging until you have one sorted array

**Visual Example**: Sorting [38, 27, 43, 3]
```
DIVIDING PHASE:
[38, 27, 43, 3]
      ↓ split
[38, 27]    [43, 3]
  ↓ split    ↓ split
[38] [27]  [43] [3]
(Now we have arrays of size 1 - they're sorted by definition!)

MERGING PHASE:
[38] and [27] → Compare: 27 < 38 → [27, 38]
[43] and [3]  → Compare: 3 < 43  → [3, 43]

Now merge [27, 38] and [3, 43]:
- Compare 27 and 3  → Take 3   → [3]
- Compare 27 and 43 → Take 27  → [3, 27]
- Compare 38 and 43 → Take 38  → [3, 27, 38]
- Only 43 left      → Take 43  → [3, 27, 38, 43]

Result: [3, 27, 38, 43] ✓
```

**The Merging Process in Detail**:
When merging two sorted arrays [27, 38] and [3, 43]:
1. Use two pointers, one for each array
2. Compare the elements at both pointers
3. Take the smaller one and move that pointer forward
4. Repeat until one array is exhausted
5. Add remaining elements from the other array
**The Concept**: Check every item one by one until you find what you're looking for

**How it works step-by-step**:
1. Start at the first element
2. Check if it matches what you're searching for
3. If yes: You found it! Return the position
4. If no: Move to the next element
5. Repeat until you find it or reach the end
6. If you reach the end without finding it: It's not there

**Real-World Example**: Finding your keys
Imagine your keys are somewhere in your house. Linear search is like checking:
- The kitchen table? No
- The bedroom dresser? No  
- The coat pocket? No
**The Concept**: Like finding a word in a dictionary - you don't start from page 1!

**The Requirement**: The data MUST be sorted first (ascending or descending)

**How it works step-by-step**:
1. Look at the middle element
2. Is it what you're searching for? If yes, done!
3. Is your target smaller? Then it must be in the left half - ignore the right half
4. Is your target larger? Then it must be in the right half - ignore the left half
5. Repeat with the remaining half
6. Keep halving until you find it or run out of elements

**Real-World Example**: Guessing a number from 1-100
```
You're told: "I'm thinking of a number between 1 and 100"

Your strategy:
Guess 50? "Higher"
Guess 75? "Lower"
Guess 62? "Higher"  
Guess 68? "Lower"
Guess 65? "Correct!"

You found it in 5 guesses instead of potentially 100!
```

**Visual Example**: Finding 7 in sorted array [1, 2, 3, 7, 8, 9, 14]
```
Array: [1, 2, 3, 7, 8, 9, 14]
        ↑        ↑        ↑
       left     mid     right

Step 1: Check middle (7) → Is 7 = 7? YES! Found it!

If we were searching for 8:
Step 1: Check middle (7) → Is 7 = 8? No. Is 7 < 8? Yes → Go RIGHT
Step 2: Search [8, 9, 14] → Check middle (9) → Is 9 = 8? No. Is 9 > 8? Yes → Go LEFT
Step 3: Search [8] → Check middle (8) → Is 8 = 8? YES! Found it!
```

**The Power of Halving**: 
- 1,000 elements → Max 10 checks
- 1,000,000 elements → Max 20 checks
- 1,000,000,000 elements → Max 30 checks

Each guess eliminates HALF of the remaining possibilities!

**Pros**: Extremely fast on large sorted datasets
**Cons**: Requires sorted data, more complex than linear search
**When to use**: Large sorted datasets, frequent searches, data doesn't change often (or you can sort it once) 
    return merge(left, right);
}

function merge(left, right) {
    const result = []networks of connected data (like social networks, maps, websites)

**What is a Graph?**: A collection of nodes (vertices) connected by edges
- Think: Cities (nodes) connected by roads (edges)
- Or: People (nodes) connected by friendships (edges)
- Or: Web pages (nodes) connected by links (edges)

#### Breadth-First Search (BFS)
**The Concept**: Explore level by level, like ripples spreading in water

**Real-World Analogy**: LinkedIn connections
- Level 1: Your direct connections (1st-degree)
- Level 2: Friends of your friends (2nd-degree)
- Level 3: Friends of friends of friends (3rd-degree)

BFS explores ALL of level 1, then ALL of level 2, then ALL of level 3, etc.

**How it works step-by-step**:
1. Start at a node and mark it as visited
2. Look at all its immediate neighbors
3. Add those neighbors to a queue (waiting list)
4. Move to the first item in the queue
5. Repeat: visit it, add ITS neighbors to the queue
6. Continue until the queue is empty

**Visual Example**: Social network starting from person A
```
Network:
    A --- B --- D
**The Concept**: Go as deep as possible before backtracking - like exploring a maze

**Real-World Analogy**: Exploring a cave system
- You go down one tunnel as far as you can
- When you hit a dead end, you backtrack to the last intersection
- Then try the next unexplored tunnel
- Repeat until you've explored everything

**How it works step-by-step**:
1. Start at a node and mark it as visited
2. Pick ONE unvisited neighbor
3. Go to that neighbor and mark it visited
4. Repeat: pick ONE of its unvisited neighbors
5. When you reach a dead end (no unvisited neighbors), backtrack
6. Try the next unvisited neighbor from the previous node
7. Continue until all nodes are visited

**Visual Example**: Same network, different strategy
```
Network:
    A --- B --- D
**The Concept**: Find the shortest path when edges have different costs/distances

**Real-World Analogy**: GPS navigation
- You're in City A and want to reach City E
- Roads have different lengths/travel times
- Dijkstra finds the fastest route

**The Problem BFS Can't Solve**:
BFS finds shortest path by NUMBER of edges, but what if edges have different weights?
```
    A --5-- B --1-- C
    |               |
    2               3
    |               |
    D -----10------ E

BFS says: A → D → E (2 steps)
But that's 2+10=12 distance!

Better: A → B → C → E (3 steps, but only 5+1+3=9 distance!)
```(DP)
**Purpose**: Solve complex problems by breaking them into simpler subproblems and remembering the answers

**The Core Idea**: Don't solve the same problem twice - remember your answers!

#### The Fibonacci Problem
**The Sequence**: 0, 1, 1, 2, 3, 5, 8, 13, 21...
- Each number is the sum of the previous two
- fib(5) = fib(4) + fib(3)

**The Naive Approach** (Without DP):
```
To calculate fib(5):
                    fib(5)
                   /      \
              fib(4)      fib(3)
              /    \      /    \
         fib(3)  fib(2) fib(2) fib(1)
         /   \    /  \   /  \
    fib(2) fib(1) ...  ...  ...
**Real-World Problem**: You're a burglar with a backpack (knapsack) that holds 10 kg

Items available:
- Laptop: 3 kg, value $2000
- Camera: 2 kg, value $1000
- Jewelry: 1 kg, value $1500
- Books: 5 kg, value $300

**Question**: What combination gives you the maximum value without exceeding 10 kg?

**The Challenge**: You can't just take everything or take the highest value items - you have a weight limit!

**How Dynamic Programming Solves It**:

The key insight: For each item, you have TWO choices:
1. Take it (if it fits) + best solution for remaining capacity
2. Don't take it + best solution with same capacity

**Step-by-Step Thinking**:
```
Build a table: rows = items, columns = weight capacity

            Weight Capacity
Items       0  1  2  3  4  5  6  7  8  9  10
None        0  0  0  0  0  0  0  0  0  0  0

Jewelry     0  1500  1500  1500  1500  1500  1500  1500  1500  1500  1500
(1kg, $1500)
"Can I fit it? If yes, is it better than not taking it?"

Camera      0  1500  1500  2500  2500  2500  2500  2500  2500  2500  2500
(2kg, $1000)  
"At 3kg: Jewelry+Camera = $2500 > Jewelry alone"

Laptop      0  1500  1500  2500  2500  3500  3500  4500  4500  4500  4500
(3kg, $2000)
"At 6kg: Jewelry+Camera+Laptop = $4500!"

Books       0  1500  1500  2500  2500  3500  3500  4500  4500  4500  4500
(5kg, $300)
"Books are heavy and low value - never improves solution"
```

**The Process for Each Cell**:
```
For each item at each capacity:
- Can the item fit? (weight ≤ capacity)
  - YES: max(
           take it: item value + best value with remaining capacity,
  The Concept**: Make the best choice RIGHT NOW without worrying about future consequences

**Key Idea**: At each step, pick the option that looks best at that moment

#### Coin Change Problem (Greedy Approach)
**Problem**: Make change for $0.63 using the fewest coins

Coins available: quarters ($0.25), dimes ($0.10), nickels ($0.05), pennies ($0.01)

**Greedy Strategy**: Always pick the largest coin that fits

**How it works step-by-step**:
```
Need to make: $0.63

Step 1: What's the largest coin ≤ $0.63? → Quarter ($0.25)
Take it! Remaining: $0.63 - $0.25 = $0.38
Coins used: [Quarter]

Step 2: What's the largest coin ≤ $0.38? → Quarter ($0.25)
Take it! Remaining: $0.38 - $0.25 = $0.13
Coins used: [Quarter, Quarter]

Step 3: What's the largest coin ≤ $0.13? → Dime ($0.10)
Take it! Remaining: $0.13 - $0.10 = $0.03
Coins used: [Quarter, Quarter, Dime]

Step 4: What's the largest coin ≤ $0.03? → Penny ($0.01)
Take it! Remaining: $0.03 - $0.01 = $0.02
Coins used: [Quarter, Quarter, Dime, Penny]
Strategy
**The Concept**: Break a big problem into smaller pieces, solve each piece, combine the solutions

**The Three Steps**:
1. **Divide**: Break the problem into smaller subproblems
2. **Conquer**: Solve each subproblem (recursively if needed)
3. **Combine**: Merge the solutions into the final answer

**Real-World Analogy**: Organizing a large party
- **Divide**: Split guests into groups (food team, decoration team, music team)
- **Conquer**: Each team handles their part independently
- **Combine**: Bring everything together for the party

**Examples We've Already Seen**:
- **Merge Sort**: Divide array in half, sort each half, merge sorted halves
- **Quick Sort**: Pick pivot, partition around it, sort each partition
- **Binary Search**: Check middle, search appropriate half

**Why It Works**: Smaller problems are easier to solve. And solving many small problems can be faster than solving one massive problem.

**Key Insight**: The subproblems should be INDEPENDENT - solving one doesn't depend on solving another first.

**Classic Example - Finding Maximum**:
```
Array: [3, 7, 2, 9, 1, 5, 8, 4]

Naive: Check all 8 elements → 7 comparisons

Divide and Conquer:
1. Divide: [3,7,2,9] and [1,5,8,4]
2. Conquer left: [3,7] max=7, [2,9] max=9 → left_max=9
3. Conquer right: [1,5] max=5, [8,4] max=8 → right_max=8  
4. Combine: max(9, 8) = 9

Still makes comparisons, but structure makes it parallelizable and systematic.
```

**When to use**: When problem can be broken into independent, similar subproblems that can be combinedenny, Penny, Penny]

Done! 6 coins total.
```
**The Concept**: Try possibilities, and when you hit a dead end, back up and try something else

**Real-World Analogy**: Solving a maze
- Try a path
- Hit a wall? Back up to the last intersection
- Try a different path
- Repeat until you find the exit

**Key Difference from Brute Force**: You abandon paths as soon as you know they won't work (don't waste time exploring dead ends)

#### Sudoku Solver Example
**The Problem**: Fill a 9x9 grid with numbers 1-9 following these rules:
- Each row must have all digits 1-9
- Each column must have all digits 1-9
- Each 3x3 box must have all digits 1-9

**How Backtracking Works**:
```
Start with partially filled grid:

5 3 . | . 7 . | . . .
6 . . | 1 9 5 | . . .
. 9 8 | . . . | . 6 .
------+-------+------
8 . . | . 6 . | . . 3
4 . . | 8 . 3 | . . 1
7 . . | . 2 . | . . 6
------+-------+------
. 6 . | . . . | 2 8 .
. . . | 4 1 9 | . . 5
. . . | . 8 . | . 7 9

Process:
Step 1: Find first empty cell (row 0, col 2)
Step 2: Try 1 → Check if valid → Valid? Place it
Step 3: Move to next empty cell
Step 4: Try 1 → Invalid (already in row)
Step 5: Try 2 → Invalid (already in box)
Step 6: Try 3 → Invalid (already in row)
Step 7: Try 4 → Valid! Place it
...
Step N: Reached a point where NO number works
Step N+1: BACKTRACK! Remove last placed number
Step N+2: Try the next number at that position
...
Continue until completely filled or proven impossible
```

**The Process**:
1. Find an empty cell
2. Try numbers 1-9 in that cell
3. For each number, check if it's valid (follows rules)
4. If valid, place it and move to the next empty cell (recursive call)
5. If you fill all cells → SUCCESS!
6. If no valid number works → BACKTRACK (undo last placement, try next number)

**Visual Concept**:
```
Decision Tree for small example:

Try 1 at position A
│
├─ Try 2 at position B
│  │
│  ├─ Try 3 at position C → DEAD END
│  └─ Try 4 at position C → DEAD END
│  └─ BACKTRACK to B
│
├─ Try 3 at position B
│  │
│  ├─ Try 2 at position C → SUCCESS! ✓
│
Solution found!
```

#### N-Queens Problem
**The Problem**: Place N chess queens on an N×N board so no two queens attack each other

Rules: Queens can attack any piece on the same row, column, or diagonal

**For 4 Queens on 4×4 Board**:
```
Try placing queens row by row:

Row 0: Try column 0
. Q . .    Place queen at (0,0)
. . . .
. . . .
. . . .

Row 1: Try column 0 → Can't (same column)
       Try column 1 → Can't (same diagonal)
       Try column 2 → Can't (vertical attack from (0,0))
       Try column 3 → OK!
       
. Q . .
. . . Q
. . . .
. . . .

Row 2: Try columns... All fail!
       BACKTRACK to row 1

Row 1: Try next position (we tried 0,1,2,3 - all failed from 0)
       BACKTRACK to row 0
       
Row 0: Try column 1
. . Q .
. . . .
. . . .
. . . .

...continue trying...

Eventually find:
. . Q .
Q . . .
. . . Q
. Q . .

Or:
. Q . .
. . . Q
Q . . .
. . Q .
```

**Why Backtracking**: 
- Brute force would try ALL 4^4 = 256 possibilities
- Backtracking abandons invalid paths early
- Much faster in practice!

**When to use**: Puzzles (Sudoku, crosswords), constraint problems, generating permutations/combinations, maze solving, scheduling with conflicts0 ✓
B: 4
C: 1 ✓ (visited)
D: 4 (1+3 through C)
E: ∞

Step 4: Visit B (smallest unvisited = 4), check neighbors D and E
A: 0 ✓
B: 4 ✓ (visited)
C: 1 ✓
D: 4 (9 through B is worse, keep 4)
E: 6 (4+2 through B)

Step 5: Visit D (smallest unvisited = 4), check neighbor E
A: 0 ✓
B: 4 ✓
C: 1 ✓
D: 4 ✓ (visited)
E: 6 (9 through D is worse, keep 6)

Step 6: Visit E
A: 0 ✓
B: 4 ✓
C: 1 ✓
D: 4 ✓
E: 6 ✓ (visited)

Shortest path to E: A → B → E (distance 6)
```

**The Greedy Insight**: Always pick the closest unvisited node. Once you've found the shortest path to a node, you'll never find a shorter one.

**Pros**: Finds true shortest path in weighted graphs, efficient
**Cons**: Doesn't work with negative weights, more complex than BFS
**When to use**: GPS/map routing, network packet routing, game AI pathfinding, flight route optimization

Step 1: Visit A, pick first neighbor B
Path: [A]
At: A → Choose B

Step 2: Visit B, pick first neighbor D
Path: [A, B]
At: B → Choose D

Step 3: Visit D, no unvisited neighbors → BACKTRACK
Path: [A, B, D]
At: D → Dead end, go back to B

Step 4: At B, pick next neighbor E
Path: [A, B, D]
At: B → Choose E

Step 5: Visit E, pick neighbor C
Path: [A, B, D, E]
At: E → Choose C

Step 6: Visit C, no unvisited neighbors → DONE
Path: [A, B, D, E, C]

Order: A → B → D → E → C
(Compare to BFS: A → B → C → D → E)
```

**BFS vs DFS - The Key Difference**:
- **BFS**: Explore all neighbors, then all neighbors' neighbors (layer by layer)
- **DFS**: Pick one neighbor and go as deep as possible (tunnel all the way down)

```
BFS (Breadth): Go WIDE first     DFS (Depth): Go DEEP first
       A                               A
      / \                             /
     B   C                           B
    / \   \                         /
   D   E   F                       D
                                  /
                                 E
```

**Pros**: Uses less memory than BFS, good for exploring all possibilities, detects cycles
**Cons**: Doesn't guarantee shortest path, can get stuck going very deep
**When to use**: Maze solving, detecting cycles (like circular dependencies), puzzle solving, generating all possibilities, topological sortingited: [A, B, C, D]
Queue: [E]

Step 5: Visit E
Visited: [A, B, C, D, E]
Queue: []

Done! Order: A → B → C → D → E
```

**Key Insight**: BFS finds the SHORTEST PATH in an unweighted graph because it explores all nodes at distance 1, then distance 2, then distance 3, etc.

**Pros**: Finds shortest path, visits nodes in distance order, good for finding "closest" things
**Cons**: Requires more memory (must store all nodes at current level)
**When to use**: Finding shortest path, checking if two nodes are connected, recommendation systems ("friends in common"), web crawlingjavascript
function linearSearch(arr, target) {
    for (let i = 0; i < arr.length; i++) {
        if (arr[i] === target) return i;
    }
    return -1;
}
```

#### Binary Search
- **How it works**: Repeatedly divides sorted array in half to find target
- **Time Complexity**: O(log n)
- **Best for**: Sorted datasets
- **When to use**: Data is sorted, frequent searches needed

```javascript
function binarySearch(arr, target) {
    let left = 0;
    let right = arr.length - 1;
    
    while (left <= right) {
        const mid = Math.floor((left + right) / 2);
        
        if (arr[mid] === target) return mid;
        if (arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    
    return -1;
}
```

---

### 3. Graph Algorithms
**Purpose**: Process graph/tree data structures

#### Breadth-First Search (BFS)
- **How it works**: Explores all neighbors at current depth before moving to next level
- **Time Complexity**: O(V + E) where V = vertices, E = edges
- **Best for**: Shortest path in unweighted graphs, level-order traversal
- **When to use**: Find shortest path, check connectivity, web crawling

```javascript
function bfs(graph, start) {
    const visited = new Set();
    const queue = [start];
    const result = [];
    
    while (queue.length > 0) {
        const node = queue.shift();
        
        if (!visited.has(node)) {
            visited.add(node);
            result.push(node);
            queue.push(...(graph[node] || []));
        }
    }
    
    return result;
}
```

#### Depth-First Search (DFS)
- **How it works**: Explores as far as possible along each branch before backtracking
- **Time Complexity**: O(V + E)
- **Best for**: Detecting cycles, topological sorting, pathfinding
- **When to use**: Maze solving, detecting cycles, topological sort

```javascript
function dfs(graph, start, visited = new Set()) {
    if (visited.has(start)) return [];
    
    visited.add(start);
    const result = [start];
    
    for (const neighbor of (graph[start] || [])) {
        result.push(...dfs(graph, neighbor, visited));
    }
    
    return result;
}
```

#### Dijkstra's Algorithm
- **How it works**: Finds shortest path in weighted graph
- **Time Complexity**: O((V + E) log V) with min-heap
- **Best for**: Shortest path with positive weights
- **When to use**: GPS navigation, network routing, game pathfinding

---

### 4. Dynamic Programming Algorithms
**Purpose**: Solve complex problems by breaking them into simpler subproblems

#### Fibonacci with Memoization
- **How it works**: Stores previously calculated results to avoid redundant work
- **Time Complexity**: O(n) with memoization vs O(2^n) without
- **Best for**: Overlapping subproblems
- **When to use**: Optimization problems, sequence generation

```javascript
function fibonacci(n, memo = {}) {
    if (n <= 1) return n;
    if (memo[n]) return memo[n];
    
    memo[n] = fibonacci(n - 1, memo) + fibonacci(n - 2, memo);
    return memo[n];
}
```

#### Knapsack Problem
- **How it works**: Maximizes value within weight constraint
- **Time Complexity**: O(n * W) where n = items, W = capacity
- **Best for**: Resource allocation problems
- **When to use**: Budget optimization, cargo loading

```javascript
function knapsack(weights, values, capacity) {
    const n = weights.length;
    const dp = Array(n + 1).fill(null).map(() => Array(capacity + 1).fill(0));
    
    for (let i = 1; i <= n; i++) {
        for (let w = 1; w <= capacity; w++) {
            if (weights[i - 1] <= w) {
                dp[i][w] = Math.max(
                    values[i - 1] + dp[i - 1][w - weights[i - 1]],
                    dp[i - 1][w]
                );
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }
    
    return dp[n][capacity];
}
```

---

### 5. Greedy Algorithms
**Purpose**: Make locally optimal choices at each step

#### Coin Change Problem (Greedy)
- **How it works**: Always picks the largest denomination possible
- **Time Complexity**: O(n)
- **Best for**: Making change with standard coin systems
- **When to use**: Optimization where greedy choice is optimal

```javascript
function coinChange(amount, coins) {
    coins.sort((a, b) => b - a);
    const result = [];
    
    for (const coin of coins) {
        while (amount >= coin) {
            result.push(coin);
            amount -= coin;
        }
    }
    
    return amount === 0 ? result : null;
}
```

#### Huffman Coding
- **Best for**: Data compression
- **When to use**: File compression, encoding optimization

---

### 6. Divide and Conquer Algorithms
**Purpose**: Break problem into smaller subproblems, solve recursively, combine results

Examples:
- **Merge Sort** (already covered)
- **Quick Sort** (already covered)
- **Binary Search** (already covered)
- **Strassen's Matrix Multiplication**

---

### 7. Backtracking Algorithms
**Purpose**: Build solution incrementally, abandoning solutions that fail

#### N-Queens Problem
- **How it works**: Places queens on chessboard without conflicts
- **Best for**: Constraint satisfaction problems
- **When to use**: Puzzles, sudoku solvers, scheduling

```javascript
function solveNQueens(n) {
    const board = Array(n).fill(null).map(() => Array(n).fill('.'));
    const solutions = [];
    
    function isValid(row, col) {
        // Check column
        for (let i = 0; i < row; i++) {
            if (board[i][col] === 'Q') return false;
        }
        
        // Check diagonals
        for (let i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
            if (board[i][j] === 'Q') return false;
        }
        
        for (let i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++) {
            if (board[i][j] === 'Q') return false;
        }
        
        return true;
    }
    
    function backtrack(row) {
        if (row === n) {
            solutions.push(board.map(r => r.join('')));
            return;
        }
        
        for (let col = 0; col < n; col++) {
            if (isValid(row, col)) {
                board[row][col] = 'Q';
                backtrack(row + 1);
                board[row][col] = '.';
            }
        }
    }
    
    backtrack(0);
    return solutions;
}
```

---

## How to Choose the Right Algorithm

### Decision Framework

#### 1. **Data Characteristics**
| Data State | Best Algorithm |
|------------|----------------|
| Unsorted | Linear Search, Quick Sort |
| Sorted | Binary Search, Merge |
| Nearly Sorted | Insertion Sort, Bubble Sort |
| Many Duplicates | Merge Sort (stable) |

#### 2. **Dataset Size**
| Size | Recommendation |
|------|----------------|
| Small (< 100) | Simple algorithms (Bubble, Linear) |
| Medium (100-10,000) | O(n log n) algorithms (Quick, Merge) |
| Large (> 10,000) | Optimized O(n log n) or better |

#### 3. **Problem Type**
| Problem | Algorithm Type |
|---------|----------------|
| Find element | Search (Binary, Linear) |
| Order data | Sorting (Quick, Merge, Heap) |
| Shortest path | Graph (Dijkstra, BFS) |
| Optimization | Dynamic Programming, Greedy |
| Constraint satisfaction | Backtracking |
| Pattern matching | String algorithms (KMP, Rabin-Karp) |

#### 4. **Performance Requirements**
```
Time vs Space Trade-off:
- Need fast execution → Accept higher space complexity
- Limited memory → Choose space-efficient algorithm
- Need consistency → Choose algorithms with good worst-case (Merge Sort)
- Average performance matters → Quick Sort usually best
```

---

## Practical Examples by Use Case

### Use Case 1: E-commerce Product Search
**Scenario**: Search through thousands of products

**Solution**: 
1. **Initial load**: Quick Sort to organize by relevance
2. **Filter/Search**: Binary Search if sorted by price
3. **Autocomplete**: Trie data structure with prefix search

```javascript
// Autocomplete with Trie
class TrieNode {
    constructor() {
        this.children = {};
        this.isEndOfWord = false;
    }
}

class AutoComplete {
    constructor() {
        this.root = new TrieNode();
    }
    
    insert(word) {
        let node = this.root;
        for (const char of word) {
            if (!node.children[char]) {
                node.children[char] = new TrieNode();
            }
            node = node.children[char];
        }
        node.isEndOfWord = true;
    }
    
    search(prefix) {
        let node = this.root;
        for (const char of prefix) {
            if (!node.children[char]) return [];
            node = node.children[char];
        }
        return this.getAllWords(node, prefix);
    }
    
    getAllWords(node, prefix) {
        const words = [];
        if (node.isEndOfWord) words.push(prefix);
        
        for (const char in node.children) {
            words.push(...this.getAllWords(node.children[char], prefix + char));
        }
        
        return words;
    }
}
```

### Use Case 2: Social Network Friend Suggestions
**Scenario**: Find mutual friends and suggest connections

**Solution**: BFS for finding friends at distance 2

```javascript
function suggestFriends(graph, user) {
    const friends = new Set(graph[user]);
    const suggestions = new Set();
    
    // Find friends of friends
    for (const friend of friends) {
        for (const potentialFriend of graph[friend]) {
            if (potentialFriend !== user && !friends.has(potentialFriend)) {
                suggestions.add(potentialFriend);
            }
        }
    }
    
    return Array.from(suggestions);
}
```

### Use Case 3: Task Scheduler
**Scenario**: Schedule tasks with dependencies

**Solution**: Topological Sort using DFS

```javascript
function taskScheduler(tasks, dependencies) {
    const graph = {};
    const inDegree = {};
    
    // Build graph
    for (const task of tasks) {
        graph[task] = [];
        inDegree[task] = 0;
    }
    
    for (const [from, to] of dependencies) {
        graph[from].push(to);
        inDegree[to]++;
    }
    
    // Find tasks with no dependencies
    const queue = tasks.filter(task => inDegree[task] === 0);
    const result = [];
    
    while (queue.length > 0) {
        const task = queue.shift();
        result.push(task);
        
        for (const dependent of graph[task]) {
            inDegree[dependent]--;
            if (inDegree[dependent] === 0) {
                queue.push(dependent);
            }
        }
    }
    
    return result.length === tasks.length ? result : null;
}
```

---

## Algorithm Complexity Cheat Sheet

### Time Complexity Rankings (Best to Worst)
1. **O(1)** - Constant: Array access, hash table lookup
2. **O(log n)** - Logarithmic: Binary search, balanced tree operations
3. **O(n)** - Linear: Linear search, array traversal
4. **O(n log n)** - Linearithmic: Merge sort, heap sort, quick sort (average)
5. **O(n²)** - Quadratic: Bubble sort, selection sort, insertion sort
6. **O(2^n)** - Exponential: Recursive fibonacci, subset generation
7. **O(n!)** - Factorial: Permutation generation, traveling salesman (brute force)

### Quick Reference Table

| Algorithm | Best | Average | Worst | Space | Stable? |
|-----------|------|---------|-------|-------|---------|
| Bubble Sort | O(n) | O(n²) | O(n²) | O(1) | Yes |
| Insertion Sort | O(n) | O(n²) | O(n²) | O(1) | Yes |
| Selection Sort | O(n²) | O(n²) | O(n²) | O(1) | No |
| Merge Sort | O(n log n) | O(n log n) | O(n log n) | O(n) | Yes |
| Quick Sort | O(n log n) | O(n log n) | O(n²) | O(log n) | No |
| Heap Sort | O(n log n) | O(n log n) | O(n log n) | O(1) | No |
| Binary Search | O(1) | O(log n) | O(log n) | O(1) | N/A |
| Linear Search | O(1) | O(n) | O(n) | O(1) | N/A |
| BFS | O(V+E) | O(V+E) | O(V+E) | O(V) | N/A |
| DFS | O(V+E) | O(V+E) | O(V+E) | O(V) | N/A |

---

## Best Practices

### 1. **Start Simple**
- Begin with brute force solution
- Understand the problem thoroughly
- Optimize only when needed

### 2. **Consider Trade-offs**
- Time vs Space complexity
- Simplicity vs Performance
- Development time vs Execution time

### 3. **Test Edge Cases**
```javascript
// Always test:
- Empty input: []
- Single element: [1]
- Duplicates: [1, 1, 1]
- Already sorted: [1, 2, 3]
- Reverse sorted: [3, 2, 1]
- Negative numbers: [-3, -1, 0, 2]
```

### 4. **Profile Before Optimizing**
- Measure actual performance
- Identify bottlenecks
- Consider readability and maintainability

### 5. **Use Built-in Methods When Appropriate**
```javascript
// Native methods are often optimized
arr.sort() // Usually implemented as Timsort (hybrid of merge & insertion)
arr.find() // Linear search
arr.includes() // Linear search
```

---

## Resources for Learning

### Practice Platforms
- **LeetCode**: Algorithm problems by difficulty
- **HackerRank**: Challenges with explanations
- **CodeWars**: Community-driven challenges
- **Project Euler**: Mathematical/algorithmic problems

### Visualization Tools
- **VisuAlgo**: Interactive algorithm visualizations
- **Algorithm Visualizer**: Step-by-step animations
- **Big-O Cheat Sheet**: Complexity reference

### Books
- "Introduction to Algorithms" (CLRS)
- "Algorithm Design Manual" by Skiena
- "Grokking Algorithms" by Bhargava (beginner-friendly)

---

## Summary

**Key Takeaways:**
1. Choose algorithms based on data characteristics, size, and requirements
2. Understand time/space complexity trade-offs
3. Start simple, optimize when necessary
4. Practice with real-world problems
5. Use the right tool for the job

**Quick Decision Guide:**
- **Sorting?** → Use Quick Sort (general) or Merge Sort (stability needed)
- **Searching?** → Binary Search (sorted) or Hash Table (unsorted)
- **Shortest Path?** → BFS (unweighted) or Dijkstra (weighted)
- **Optimization?** → Dynamic Programming or Greedy
- **Constraints?** → Backtracking

Remember: The best algorithm is the one that solves your specific problem efficiently while maintaining code readability and maintainability!
