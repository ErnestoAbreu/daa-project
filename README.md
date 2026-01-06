# Degree-Constrained Minimum Spanning Tree (DCMST) for University of Havana Fiber Optic Network

Analysis and implementation of solutions for the well-known NP-hard **Degree-Constrained Minimum Spanning Tree (DCMST)** problem. This repository presents theoretical analysis, complexity proofs, and practical implementations of exact and heuristic approaches.

## 📝 Problem Description

The main problem is defined at [problem description](docs/problem.md).

### Problem Formalization

Let $G = (V, E)$ be a complete, weighted, and undirected graph. We define a cost function $w: E \to \mathbb{R}^+$ for each edge and a capacity function $k: V \to \mathbb{N}$ representing the maximum allowed degree (available ports) for each vertex $v \in V$.

The goal is to find a spanning tree $T = (V, E')$ that minimizes the total installation cost:

$$T^* = \arg\min_{T \in \mathcal{T}} \sum_{e \in E'} w(e)$$

Subject to the following constraints:

1. **Connectivity:** $T$ must be a spanning tree of $G$ (connecting all vertices in $V$ with $|V| - 1$ edges and no cycles).
2. **Degree Constraint:** For every vertex $v \in V$, its degree in $T$ must satisfy:
   $$\text{deg}_T(v) \leq k(v)$$

This problem is **NP-Hard**, which can be demonstrated via a polynomial-time reduction from the **Travelling Salesman Problem** (a special case of DCMST where $k(v) = 2$ for all $v$).

## 🚀 Implemented Solutions

Not implemented yet

## 📁 Repository Structure

* `/docs`: Formal LaTeX report including the NP-Hardness proof and algorithm analysis.
* `/src`: C++ source files.

## 🎓 Authors

* **Ernesto Abreu Peraza** - [GitHub](https://github.com/ErnestoAbreu)
* **Eduardo Brito Labrada** - [GitHub](https://github.com/eblabrada)
