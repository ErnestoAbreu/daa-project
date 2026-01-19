# Degree-Constrained Minimum Spanning Tree (DCMST) for University of Havana Fiber Optic Network

Analysis and implementation of solutions for the well-known NP-hard **Degree-Constrained Minimum Spanning Tree (DCMST)** problem. This repository presents theoretical analysis, complexity proofs, and practical implementations of exact and heuristic approaches.

## 📝 Problem Description

The main problem is defined at [problem description](docs/problem.md).

### Problem Formalization

Let $G = (V, E)$ be a conected, weighted, and undirected graph. We define a cost function $w: E \to \mathbb{R}^+$ for each edge and a capacity function $k: V \to \mathbb{N}$ representing the maximum allowed degree (available ports) for each vertex $v \in V$.

The goal is to find a spanning tree $T = (V, E')$ that minimizes the total installation cost:

$$T^* = \arg\min_{T \in \mathcal{T}} \sum_{e \in E'} w(e)$$

Subject to the following constraints:

1. **Connectivity:** $T$ must be a spanning tree of $G$ (connecting all vertices in $V$ with $|V| - 1$ edges and no cycles).
2. **Degree Constraint:** For every vertex $v \in V$, its degree in $T$ must satisfy:
   $$\text{deg}_T(v) \leq k(v)$$

This problem is **NP-Hard**, which can be demonstrated via a polynomial-time reduction from the **Travelling Salesman Problem** (a special case of DCMST where $k(v) = 2$ for all $v$).

## 🚀 Implemented Solutions

This repository includes multiple approaches to solve the DCMST problem, ranging from exact algorithms for small instances to metaheuristics for larger problem sizes.

### Exact Algorithms

These algorithms guarantee optimal solutions but are limited to small instances due to their exponential time complexity.

#### 1. **Bitmask Enumeration** ([bitmask.cpp](src/solutions/bitmask.cpp))

- **Approach:** Exhaustive enumeration using bitmask representation
- **Complexity:** $O(2^m + \binom{m}{n-1} \cdot n)$ where $m = \frac{n(n-1)}{2}$
- **Best for:** Instances with $n \leq 6$.

#### 2. **Lexicographic Combination Enumeration** ([comb.cpp](src/solutions/comb.cpp))

- **Approach:** Generates all combinations of $n-1$ edges
- **Complexity:** $O(\binom{m}{n-1} \cdot n)$
- **Best for:** Instances with $n \leq 9$

#### 4. **Gray Code Recursive** ([gray_recursive.cpp](src/solutions/gray_recursive.cpp))

- **Approach:** Recursive enumeration using Gray code properties with pruning
- **Complexity:** Exponential with early pruning
- **Best for:** Instances with $n \leq 11$

#### 3. **Gosper's Hack** ([iterative.cpp](src/solutions/iterative.cpp))

- **Approach:** Efficient combination generation using Gosper's hack algorithm
- **Complexity:** $O(\binom{m}{n-1} \cdot (m+n))$
- **Best for:** Instances with $n \leq 9$

### Metaheuristics

These algorithms provide high-quality approximate solutions for larger instances in reasonable time.

#### 5. **Randomized Primal Method (RPM) with Genetic Algorithm** ([evolutionary.cpp](src/metaheuristics/evolutionary.cpp))

- **Approach:** Hybrid method combining Prim's algorithm with genetic algorithms
- **Complexity:** $O(\text{generations} \times \text{population\_size} \times n^2)$
- **Best for:** Instances with $n \leq 100$

#### 6. **Ant Colony System (ACS)** ([ant_colony.cpp](src/metaheuristics/ant_colony.cpp))

- **Approach:** Ant Colony Optimization with pheromone-based decision making
- **Complexity:** $O(\text{iterations} \times \text{ants} \times n^2)$
- **Best for:** Instances with $n \leq 100$

### Performance Summary

Based on experimental results on test instances:

| Algorithm | Max n | Points (Total: 30500) | Best Use Case |
| ----------- | ------- | -------------------- | --------------- |
| **bitmask** | 9 | 4500 | Very small instances ($n \leq 6$) |
| **comb/gosper** | 9 | 5500 | Small instances ($n \leq 9$) |
| **gray_recursive** | 11 | 5648 | Small-medium instances ($n \leq 11$) |
| **evolutionary** | 100+ | ~25000 | Medium-large instances |
| **ant_colony** | 100+ | ~27000 | All instance sizes (best overall) |

**Note:** The metaheuristics (evolutionary and ant_colony) provide near-optimal solutions for all test groups while maintaining execution times well below the 15-second limit, making them the preferred choice for practical applications.

## 📁 Repository Structure

- `/docs`: Formal LaTeX report including the NP-Hardness proof and algorithm analysis.
- `/src`: C++/Python source files.

## 🎓 Authors

- **Ernesto Abreu Peraza** - [GitHub](https://github.com/ErnestoAbreu)
- **Eduardo Brito Labrada** - [GitHub](https://github.com/eblabrada)
