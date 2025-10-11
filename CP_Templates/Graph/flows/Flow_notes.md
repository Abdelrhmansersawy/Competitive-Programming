# **Ford–Fulkerson Method**

When we move in a direction and take flow `f`,
we **remove** it from the forward edge and **add** a reverse edge with flow `f`.

In the future, if a new path is found,
it can **cancel** a previous flow (move in the reverse edge) to find a **better path**.

---

## **Residual Graph**

The residual graph lets the algorithm **move flow forward or backward**:

* **Forward:** add new flow
* **Backward:** undo previous flow

This allows finding the **most efficient flow arrangement**.

---

## **Augmenting Path**

An **augmenting path** is a path from the **source (`s`)** to the **sink (`t`)**
in the **residual graph**, where every edge has **positive residual capacity**.

---

## **Flow Cancellations**

Flow cancellation allows the algorithm to **undo part of a previous flow** —
by sending flow **backward** through **reverse edges** —
to achieve a **more optimal** flow configuration.

---

> ⚠️ **Note:**
> A **DAG** (Directed Acyclic Graph) is **not necessarily** a **bipartite graph**.

---

# **Applications & Variants**

### 1. Maximum Edge-Disjoint Paths

* Equivalent to **Maximum Flow**
* Assign `capacity = 1` on all **edges**

---

### 2. Maximum Vertex-Disjoint Paths

* Equivalent to **Maximum Flow**
* Assign `capacity = 1` on all **vertices**

---

### 3. Maximum Independent Paths (No Shared Vertices)

* Combine logic of **(1)** and **(2)**

---

### 4. Multi-Source & Multi-Sink Flow

Create a **super source** and **super sink**, then:

* Connect all **sources → super source**
* Connect all **sinks → super sink**

---

### 5. Knight Graph → Bipartite Graph

* **Left set:** white cells
* **Right set:** black cells
* Since knights move between opposite-colored cells, the graph is **bipartite**.

---

### 6. Minimum Vertex Cover Problem

**Definition:**
Smallest set of vertices such that every edge is incident to at least one chosen vertex.

For **bipartite graphs**, by **Kőnig’s Theorem**:

> **Minimum Vertex Cover = Maximum Matching**

---

# **Kőnig’s Theorem**

**Definition:**
Establishes a relationship between:

* The **Maximum Matching Problem**, and
* The **Minimum Vertex Cover Problem**.

---

## **1. Minimum Path Coverage in a DAG**

**Definition:**
Minimum number of paths required to cover all vertices.

**Solution:**

1. Duplicate each of the `N` nodes.
2. Build adjacency `adj[n][n]`.
3. Compute:

   ```
   min_path_cover = N - maximum_matching
   ```

**Why it works:**
Unmatched left-side nodes represent **path ends**,
so the total paths = `N - number_of_matches`.

---

## **2. Minimum Edge Coverage**

**Definition:**
Minimum number of edges so every vertex is incident to at least one.

**Solution:**

```
min_edge_cover = N - maximum_matching
```

**Reasoning:**
Each matching edge covers **2 vertices**,
and unmatched vertices each need one additional edge.

---

## **3. Maximum Independent Set**

**Definition:**
Largest set of vertices with **no edges** between them.

**Relation:**

```
max_independent_set + min_vertex_cover = N
```

For **bipartite graphs** (by Kőnig’s Theorem):

```
min_vertex_cover = maximum_matching
max_independent_set = N - maximum_matching
```
