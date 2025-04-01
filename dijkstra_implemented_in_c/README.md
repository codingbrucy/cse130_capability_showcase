# CSE 101 - Programming Assignment 3

Author: Dingfei Ning

Feb 2, 2025
## Strongly Connected Components using Kosaraju’s Algorithm

### **Submitted Files**
This assignment includes the following files:
- **Makefile** – Builds `FindComponents` and `GraphTest`, compiles with `-Wall -Wextra -Wpedantic`, and provides a `clean` rule.
- **README.md** – This file, documenting the implementation details.
- **List.h / List.c** – Implements a doubly linked list, used for adjacency lists and DFS processing.
- **Graph.h / Graph.c** – Implements a directed graph with adjacency lists, DFS, graph transposition, and SCC extraction.
- **GraphTest.c** – Unit tests for the `Graph` module.
- **FindComponents.c** – Client program that reads an input file, constructs a graph, runs Kosaraju’s algorithm, and outputs the SCCs.

---

### **Implementation Details**
This project implements **Kosaraju’s Algorithm** to find the **strongly connected components (SCCs)** of a directed graph using **two depth-first searches (DFS)**.

1. **Graph Representation**
   - The graph is stored as an **adjacency list** in `Graph.c`.
   - Vertices are labeled from `1` to `n` (1-based indexing).
   - `Graph` contains:
     - `adj_list` (array of adjacency lists)
     - `colors` (W/G/B for DFS state tracking)
     - `parent_table` (stores DFS tree parent)
     - `discovery` (discovery times)
     - `finish` (finish times)
     - `num_vertices` (order), `num_edges` (size)
  
2. **Depth-First Search (DFS)**
   - Implements **DFS** with a helper function `visit()`, which updates `discovery` and `finish` times.
   - Uses a **List** to track vertices in decreasing **finish time** order for Kosaraju’s second DFS.
   - The `time` variable is passed **by reference** inside DFS to maintain its value across recursive calls.

3. **Graph Transposition**
   - `transpose()` creates a new graph with **reversed edges**.
   - This allows SCC detection using a second DFS.

4. **Finding SCCs (Kosaraju’s Algorithm)**
   - **First DFS:** Runs on `G`, storing vertices in **decreasing finish order**.
   - **Graph Transposition:** Constructs `G^T` with reversed edges.
   - **Second DFS:** Runs on `G^T`, processing vertices **in decreasing finish time order**.
   - Each DFS tree in `G^T` is an SCC.

---

### **Input and Output**
#### **Input Format (`infile`)**
- First line: `n` (number of vertices).
- Subsequent lines: `u v` (directed edge from `u` to `v`).
- Input ends with `0 0`.

#### **Output Format (`outfile`)**
- Prints adjacency list of `G`.
- Lists the number of SCCs.
- Prints SCCs in **topologically sorted order**.