#include <bits/stdc++.h>
using namespace std;

const int POPULATION_SIZE = 50; // GA Population
const int GENERATIONS = 1000;
const double MUTATION_RATE = 0.05;

int MAX_DEGREE = 3;       // The 'd' in d-MST

struct Edge {
    int u, v;
    int weight;
    
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

class Graph {
public:
    int n;
    vector<vector<Edge>> adj;

    Graph(int nodes) : n(nodes), adj(nodes) {}

    void addEdge(int u, int v, int w) {
        adj[u].push_back({u, v, w});
        adj[v].push_back({v, u, w});
    }

    void sortEdges() {
        for (auto& edges : adj) {
            sort(edges.begin(), edges.end());
        }
    }
};

// --- Randomised Primal Method (RPM) Logic ---

// The Chromosome represents the "Edge Choice Table"
using Chromosome = vector<vector<int>>;

struct Solution {
    vector<Edge> treeEdges;
    int totalCost;
    bool valid; // True if a spanning tree was successfully formed
};

class RPMSolver {
private:
    const Graph& graph;
    int degreeConstraint;

public:
    RPMSolver(const Graph& g, int d) : graph(g), degreeConstraint(d) {}

    Solution decode(const Chromosome& chrom) {
        int n = graph.n;
        Solution sol;
        sol.totalCost = 0.0;
        sol.valid = false;

        vector<int> currentDegree(n, 0);
        vector<bool> inTree(n, false);
        vector<Edge> treeEdges;
        treeEdges.reserve(n - 1);

        // Step 1: Place an arbitrary vertex in S (We choose vertex 0)
        inTree[0] = true;
        int verticesInTree = 1;

        // General Step: Loop until we have a spanning tree (n-1 edges)
        while (verticesInTree < n) {
            
            Edge bestEdge = {-1, -1, numeric_limits<int>::max()};
            bool foundCandidate = false;

            // 1. For each vertex i in S whose current degree < d
            for (int i = 0; i < n; ++i) {
                if (!inTree[i]) continue;
                if (currentDegree[i] >= degreeConstraint) continue;

                // Construct sorted list l_i of valid edges connecting to vertices NOT in S.
                // Since graph.adj is pre-sorted, we iterate to find valid ones.
                
                int validEdgesFound = 0;
                int desiredIndex = chrom[i][currentDegree[i]]; // The allele a(i, d_i)
                
                Edge candidateForNodeI = {-1, -1, -1};
                bool foundForNodeI = false;

                // Look through pre-sorted edges of node i
                for (const auto& edge : graph.adj[i]) {
                    if (!inTree[edge.v]) {
                        // This is a valid edge (connects Tree to Non-Tree)
                        // If we haven't reached the desired index yet, keep going
                        candidateForNodeI = edge;
                        if (validEdgesFound == desiredIndex) {
                            foundForNodeI = true;
                            break; 
                        }
                        validEdgesFound++;
                    }
                }

                // Note: The paper implies if the list is shorter than the allele index,
                // we take the last valid edge available (the highest weight considered).
                // The loop above naturally leaves candidateForNodeI as the last valid edge 
                // if we exhaust the list without hitting the exact index.
                if (candidateForNodeI.u != -1) {
                    foundForNodeI = true;
                }

                // 2. Place edge into low-cost set L (implied) and 3. Select lowest in L
                if (foundForNodeI) {
                    if (candidateForNodeI.weight < bestEdge.weight) {
                        bestEdge = candidateForNodeI;
                        foundCandidate = true;
                    }
                }
            }

            if (!foundCandidate) {
                // If we get here, the graph is disconnected or constraints make it impossible
                // (Dead end due to degree constraints).
                sol.valid = false; 
                return sol; 
            }

            // Add the best global candidate to the tree
            treeEdges.push_back(bestEdge);
            sol.totalCost += bestEdge.weight;
            
            // Update state
            inTree[bestEdge.v] = true; // u was already in tree, v is new
            currentDegree[bestEdge.u]++;
            currentDegree[bestEdge.v]++;
            verticesInTree++;
        }

        sol.treeEdges = treeEdges;
        sol.valid = true;
        return sol;
    }
};

// --- Genetic Algorithm ---

class GeneticAlgorithm {
private:
    const Graph& graph;
    int popSize;
    int degreeConstraint;
    vector<Chromosome> population;
    mt19937 rng;

public:
    GeneticAlgorithm(const Graph& g, int pSize, int d) 
        : graph(g), popSize(pSize), degreeConstraint(d), rng(random_device{}()) {}

    // Initialize with bias towards lower values (Negative Exponential / Geometric)
    void initializePopulation() {
        population.clear();
        // Probability p roughly mimics the bias described in paper. 
        // Higher p means higher probability of getting 0 (which maps to index 0, the best edge).
        geometric_distribution<int> dist(0.5); 

        for (int i = 0; i < popSize; ++i) {
            Chromosome chrom(graph.n, vector<int>(degreeConstraint, 0));
            for (int u = 0; u < graph.n; ++u) {
                for (int deg = 0; deg < degreeConstraint; ++deg) {
                    chrom[u][deg] = dist(rng);
                }
            }
            population.push_back(chrom);
        }
    }

    // Uniform Crossover [15]
    Chromosome crossover(const Chromosome& p1, const Chromosome& p2) {
        Chromosome child = p1;
        uniform_int_distribution<int> coin(0, 1);
        
        for (int u = 0; u < graph.n; ++u) {
            for (int deg = 0; deg < degreeConstraint; ++deg) {
                if (coin(rng)) {
                    child[u][deg] = p2[u][deg];
                }
            }
        }
        return child;
    }

    // Mutation: Small change operator
    void mutate(Chromosome& chrom) {
        geometric_distribution<int> valDist(0.5);
        uniform_real_distribution<double> rateDist(0.0, 1.0);

        for (int u = 0; u < graph.n; ++u) {
            for (int deg = 0; deg < degreeConstraint; ++deg) {
                if (rateDist(rng) < MUTATION_RATE) {
                    chrom[u][deg] = valDist(rng);
                }
            }
        }
    }

    void run(int generations) {
        RPMSolver solver(graph, degreeConstraint);
        
        // Track best
        int globalBestCost = numeric_limits<int>::max();
        Chromosome globalBestChrom;

        for (int gen = 0; gen < generations; ++gen) {
            vector<pair<int, int>> fitness;
            
            // 1. Evaluate
            for (int i = 0; i < popSize; ++i) {
                Solution s = solver.decode(population[i]);
                int cost = s.valid ? s.totalCost : numeric_limits<int>::max();
                fitness.push_back({cost, i});

                if (s.valid && cost < globalBestCost) {
                    globalBestCost = cost;
                    globalBestChrom = population[i];
                }
            }

            sort(begin(fitness), end(fitness));

            if (gen % 100 == 0) {
                cout << "Gen " << gen << ": Best Cost = " << globalBestCost << endl;
            }

            // 2. Selection (Tournament) & Crossover
            vector<Chromosome> nextGen;
            // Elitism: Keep best
            nextGen.push_back(population[fitness[0].second]);

            uniform_int_distribution<int> idxDist(0, popSize - 1);

            while (nextGen.size() < popSize) {
                // Tournament 1
                int r1 = idxDist(rng); int r2 = idxDist(rng);
                int p1_idx = (fitness[r1].first < fitness[r2].first) ? fitness[r1].second : fitness[r2].second;

                // Tournament 2
                int r3 = idxDist(rng); int r4 = idxDist(rng);
                int p2_idx = (fitness[r3].first < fitness[r4].first) ? fitness[r3].second : fitness[r4].second;

                Chromosome child = crossover(population[p1_idx], population[p2_idx]);
                mutate(child);
                nextGen.push_back(child);
            }
            population = nextGen;
        }

        // cerr << "\n--- Final Result ---" << endl;
        // cerr << "Best d-MST Cost Found: " << globalBestCost << endl;

        
        // Output degree check
        Solution finalSol = solver.decode(globalBestChrom);
        vector<int> degrees(graph.n, 0);
        for(auto& e : finalSol.treeEdges) {
            degrees[e.u]++;
            degrees[e.v]++;
        }
        
        cout << globalBestCost << "\n";
        for (auto &e: finalSol.treeEdges) {
            cout << e.u+1 << " " << e.v+1 << " " << e.weight << "\n";
        }

        // cerr << "Max Degree in Solution: ";
        // int maxD = 0;
        // for(int d : degrees) maxD = max(maxD, d);
        // cerr << maxD << " (Constraint: " << degreeConstraint << ")" << endl;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int V, K; cin >> V >> K;
   
    Graph G(V);
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            int val; cin >> val;

            if (i < j) G.addEdge(i, j, val);
        }
    }

    MAX_DEGREE = K;

    // cerr << "Running GA with RPM for degree constraint d=" << MAX_DEGREE << endl;
    GeneticAlgorithm ga(G, POPULATION_SIZE, MAX_DEGREE);
    
    ga.initializePopulation();
    ga.run(GENERATIONS);
}