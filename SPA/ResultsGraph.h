#ifndef T11_RESULTS_GRAPH_H
#define T11_RESULTS_GRAPH_H

#include <string>
#include <map>
#include <set>
#include "PQL.h"

// A note to the reader
// DO NOT
// 1. Initialize instances of any of these classes other than
//    ResultsGraph
// 2. Dynamically allocate new copies of any of these classes
//
// What the above points amount to are:
// 1. You should only interact with these classes through pointers
// 2. You should only manipulate these classes using their
//    given API
//
// Yes, this is C code written in C++ but that's the whole point.

// forward declaration
class SuperVertex;

class Vertex {
public:
    Vertex(SuperVertex *r, int syn, const std::string& valueStr, int value);
    void add_neighbor(Vertex *v);
    const std::set<Vertex *>& get_adjList() const;
    void remove_neighbor(Vertex *v);
    bool has_neighbor(int syn) const;
    std::set<Vertex *> destroy();
    int get_syn() const;
    int get_value() const;
    std::string get_valueStr() const;
    void reset();
    void bless();
    bool is_blessed() const;
    bool is_alive() const;
    std::string toString() const;

private:
    Vertex();
    SuperVertex *root;
    bool alive;
    int syn;
    int value;
    std::string valueStr;
    bool blessed;
    std::set<Vertex *> adjList;
    std::map<int, int> synCount;
};

class SuperVertex {
public:
    SuperVertex(DesignEnt synType, int syn);
    int get_syn() const;
    Vertex *add_vertex(const std::string& value, int valueInt);
    Vertex *get_vertex(int value);
    DesignEnt get_synType() const;
    const std::map<int, Vertex *>& get_vertices() const;
    bool reset();
    std::set<Vertex *> get_unblessed() const;
    void remove_vertex(int value);
    std::string toString() const;
    std::set<std::pair<int, std::string> > toSet() const;

private:
    SuperVertex();
    DesignEnt synType;
    int syn;
    std::map<int, Vertex *> vertices;
};

class VertexCmp {
public:
    bool operator()(const Vertex &a, const Vertex &b) const;
};

struct PruneInfo {
    int check;
    std::set<Vertex *> vertices;

    PruneInfo();
    PruneInfo(int check_);
    void add_vertex(Vertex *v);
};

struct PruneInfoCmp {
    bool operator()(const PruneInfo &a, const PruneInfo &b) const;
};

class ResultsGraph {
public:
    ResultsGraph();
    ~ResultsGraph();
    Vertex *add_vertex(DesignEnt synType, const std::string& syn,
            const std::string& value);
    Vertex *add_vertex(DesignEnt synType, const std::string& syn,
            int value);
    void add_edge(DesignEnt syn1Type,
            const std::string& syn, int value,
            DesignEnt syn2Type, const std::string& syn2, int value2);
    void add_edge(DesignEnt syn1Type,
            const std::string& syn, int value,
            DesignEnt syn2Type, const std::string& syn2,
            const std::string& value2);
    void add_edge(DesignEnt syn1Type,
            const std::string& syn, const std::string& value,
            DesignEnt syn2Type, const std::string& syn2, int value2);
    void add_edge(DesignEnt syn1Type,
            const std::string& syn, const std::string& value,
            DesignEnt syn2Type, const std::string& syn2,
            const std::string& value2);
    Vertex *get_vertex(const std::pair<int, int>& ip);
    std::set<std::pair<int, std::string> >
            get_synonym(const std::string& syn) const;
    bool has_syn(const std::string &syn) const;
    bool has_syn(int syn) const;
    int syn_to_int(const std::string &syn) const;
    void prune(const std::string &syn);
    void prune(int syn);
    void prune(const std::string& syn, const std::string& syn2);
    void prune(const std::string& syn, int syn2);
    void prune(int syn1, const std::string& syn2);
    void prune(int syn1, int syn2);
    void reset();
    bool is_alive() const;
    std::string toString() const;

private:
    ResultsGraph(const ResultsGraph& o);
    ResultsGraph& operator=(const ResultsGraph& o);
    // adds super vertex if necessary
    int retrieve_superVertex_label(const std::string& syn);
    int retrieve_value_label(const std::string& syn);
    Vertex *add_vertex(DesignEnt synType, int syn,
            const std::string& value, int valueInt);
    void add_edge(DesignEnt syn1Type, int syn, int value,
            DesignEnt syn2Type, int syn2, int value2);
    void prune_prelude(int syn, std::map<int, PruneInfo, PruneInfoCmp>& q,
            std::set<Vertex *>& garbage);
    void prune__(std::map<int, PruneInfo, PruneInfoCmp> *q,
            std::set<Vertex *>& garbage,
            const std::set<int>& synToReset);

    bool alive;
    int SYNLABEL;
    int VALUELABEL;
    std::map<std::string, int> synMap;
    std::map<std::string, int> valueMap;
    std::map<int, std::string> intValueToString;
    std::map<int, SuperVertex *> vertices;
};

#endif