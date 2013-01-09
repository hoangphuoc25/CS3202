#include <cassert>
#include <utility>
#include "ResultsGraph.h"
#include "StringBuffer.h"

using std::string;
using std::pair;
using std::map;
using std::set;
using std::make_pair;

//////////////////////////////////////////////////////////////////////
// Prune Info
//////////////////////////////////////////////////////////////////////

PruneInfo::PruneInfo(): check(-1) {}
PruneInfo::PruneInfo(int check_): check(check_) {}

void PruneInfo::add_vertex(Vertex *v)
{
    this->vertices.insert(v);
}

bool PruneInfoCmp::operator()(const PruneInfo &a, const PruneInfo &b)
        const
{
    return a.check < b.check;
}

//////////////////////////////////////////////////////////////////////
// Vertex
//////////////////////////////////////////////////////////////////////

// private
Vertex::Vertex() {}

Vertex::Vertex(SuperVertex *r, int syn_, const string& valueStr_,
        int value_)
    : root(r), alive(true), syn(syn_), value(value_),
      valueStr(valueStr_), blessed(true) {}

void Vertex::add_neighbor(Vertex *v)
{
    if (!this->alive || !v->alive) {
        return;
    }
    int otherSyn = v->syn;
    if (this->adjList.find(v) == this->adjList.end()) {
        this->adjList.insert(v);
        if (this->synCount.find(otherSyn) == this->synCount.end()) {
            this->synCount[otherSyn] = 0;
        }
        this->synCount[otherSyn]++;
    }
    this->bless();
    v->bless();
}

const set<Vertex *>& Vertex::get_adjList() const
{
    return this->adjList;
}

void Vertex::remove_neighbor(Vertex *v)
{
    if (!this->alive) {
        return;
    }
    if (this->adjList.find(v) != this->adjList.end()) {
        this->adjList.erase(v);
        this->synCount[v->syn]--;
    }
}

bool Vertex::has_neighbor(int syn) const
{
    if (!this->alive) {
        return false;
    }
    map<int, int>::const_iterator it = this->synCount.find(syn);
    if (it == this->synCount.end()) {
        return false;
    } else {
        return (it->second > 0);
    }
}

set<Vertex *> Vertex::destroy()
{
    set<Vertex *> ret;
    if (!this->alive) {
        return ret;
    }
    for (set<Vertex *>::const_iterator it = this->adjList.begin();
            it != this->adjList.end(); it++) {
        (*it)->remove_neighbor(this);
        if (*it != this) {
            ret.insert(*it);
        }
    }
    this->alive = false;
    // destroy copy in superVertex
    this->root->remove_vertex(this->value);
    return ret;
}

int Vertex::get_syn() const
{
    return this->syn;
}

int Vertex::get_value() const
{
    return this->value;
}

string Vertex::get_valueStr() const
{
    return valueStr;
}

void Vertex::reset()
{
    this->blessed = false;
}

void Vertex::bless()
{
    this->blessed = true;
}

bool Vertex::is_blessed() const
{
    return this->blessed;
}

bool Vertex::is_alive() const
{
    return this->alive;
}

string Vertex::toString() const
{
    StringBuffer sb;
    Vertex *v;
    set<pair<int, int> > S;
    if (this->is_alive()) {
        for (set<Vertex *>::const_iterator it = this->adjList.begin();
                it != this->adjList.end(); it++) {
            v = *it;
            if (v->is_alive()) {
                S.insert(make_pair(v->syn, v->value));
            }
        }
    }
    if (this->is_alive()) {
        sb.sprintf("%d %d ->", this->syn, this->value);
        for (set<pair<int, int> >::const_iterator it = S.begin();
                it != S.end(); it++) {
            sb.sprintf(" [%d %d]", it->first, it->second);
        }
        sb.append('\n');
    }
    return sb.toString();
}

//////////////////////////////////////////////////////////////////////
// SuperVertex
//////////////////////////////////////////////////////////////////////

// private constructor
SuperVertex::SuperVertex() {}

SuperVertex::SuperVertex(DesignEnt synType_, int syn_):
        synType(synType_), syn(syn_) {}

int SuperVertex::get_syn() const
{
    return this->syn;
}

Vertex *SuperVertex::add_vertex(const string& value, int valueInt)
{
    Vertex *v;
    if (this->vertices.find(valueInt) == this->vertices.end()) {
        v = new Vertex(this, this->syn, value, valueInt);
        this->vertices[valueInt] = v;
    }
    v = this->vertices[valueInt];
    v->bless();
    return v;
}

Vertex *SuperVertex::get_vertex(int value)
{
    map<int, Vertex *>::const_iterator it = this->vertices.find(value);
    if (it == this->vertices.end()) {
        return NULL;
    }
    return it->second;
}

DesignEnt SuperVertex::get_synType() const
{
    return this->synType;
}

const map<int, Vertex *>& SuperVertex::get_vertices() const
{
    return this->vertices;
}

bool SuperVertex::reset()
{
    for (map<int, Vertex *>::const_iterator it = this->vertices.begin();
            it != this->vertices.end(); it++) {
        it->second->reset();
    }
    return (this->vertices.size() > 0);
}

set<Vertex *> SuperVertex::get_unblessed() const
{
    set<Vertex *> unblessed;
    Vertex *v;
    for (map<int, Vertex *>::const_iterator it = this->vertices.begin();
            it != this->vertices.end(); it++) {
        v = it->second;
        if (!v->is_blessed()) {
            unblessed.insert(v);
        }
    }
    return unblessed;
}

void SuperVertex::remove_vertex(int value)
{
    if (this->vertices.find(value) != this->vertices.end()) {
        this->vertices.erase(value);
    }
}

string SuperVertex::toString() const
{
    StringBuffer sb;
    map<int, string> M;
    for (map<int, Vertex *>::const_iterator it = this->vertices.begin();
            it != this->vertices.end(); it++) {
        Vertex *v = it->second;
        string s = v->toString();
        if (s.size() > 0) {
            M[v->get_value()] = s;
        }
    }
    for (map<int, string>::const_iterator it = M.begin();
            it != M.end(); it++) {
        sb.append(it->second);
    }
    return sb.toString();
}

set<pair<int, string> > SuperVertex::toSet() const
{
    set<pair<int, string> > ret;
    Vertex *v;
    for (map<int, Vertex *>::const_iterator it = this->vertices.begin();
            it != this->vertices.end(); it++) {
        v = it->second;
        ret.insert(make_pair(v->get_value(), v->get_valueStr()));
    }
    return ret;
}

//////////////////////////////////////////////////////////////////////
// ResultsGraph
//////////////////////////////////////////////////////////////////////

ResultsGraph::ResultsGraph()
    : alive(true), SYNLABEL(1), VALUELABEL(1) {}

ResultsGraph::~ResultsGraph()
{
    this->reset();
}

Vertex *ResultsGraph::add_vertex(DesignEnt synType, const string& syn,
        const string& value)
{
    int synLabel, valueLabel;
    synLabel = this->retrieve_superVertex_label(syn);
    valueLabel = this->retrieve_value_label(value);
    return this->add_vertex(synType, synLabel, value, valueLabel);
}

Vertex *ResultsGraph::add_vertex(DesignEnt synType,
        const string& syn, int value)
{
    int synLabel;
    synLabel = this->retrieve_superVertex_label(syn);
    return this->add_vertex(synType, synLabel, "", value);
}

void ResultsGraph::add_edge(DesignEnt syn1Type,
        const string& syn, int value,
        DesignEnt syn2Type, const string& syn2, int value2)
{
    Vertex *a = this->add_vertex(syn1Type, syn, value);
    Vertex *b = this->add_vertex(syn2Type, syn2, value2);
    a->add_neighbor(b);
    b->add_neighbor(a);
}

void ResultsGraph::add_edge(DesignEnt syn1Type,
        const string& syn, int value,
        DesignEnt syn2Type, const string& syn2, const string& value2)
{
    Vertex *a = this->add_vertex(syn1Type, syn, value);
    Vertex *b = this->add_vertex(syn2Type, syn2, value2);
    a->add_neighbor(b);
    b->add_neighbor(a);
}

void ResultsGraph::add_edge(DesignEnt syn1Type,
        const string& syn, const string& value,
        DesignEnt syn2Type, const string& syn2, int value2)
{
    Vertex *a = this->add_vertex(syn1Type, syn, value);
    Vertex *b = this->add_vertex(syn2Type, syn2, value2);
    a->add_neighbor(b);
    b->add_neighbor(a);
}

void ResultsGraph::add_edge(DesignEnt syn1Type,
        const string& syn, const string& value,
        DesignEnt syn2Type, const string& syn2, const string& value2)
{
    Vertex *a = this->add_vertex(syn1Type, syn, value);
    Vertex *b = this->add_vertex(syn2Type, syn2, value2);
    a->add_neighbor(b);
    b->add_neighbor(a);
}

Vertex *ResultsGraph::get_vertex(const pair<int, int>& ip)
{
    int syn = ip.first;
    int val = ip.second;
    map<int, SuperVertex *>::const_iterator it = this->vertices.find(syn);
    if (it == this->vertices.end()) {
        return NULL;
    }
    SuperVertex *superVertex = it->second;
    return superVertex->get_vertex(val);
}

set<pair<int, string> > ResultsGraph::get_synonym(const string& syn) const
{
    if (!this->has_syn(syn)) {
        return set<pair<int, string> > ();
    } else {
        map<string, int>::const_iterator it = synMap.find(syn);
        assert(it != this->synMap.end());
        map<int, SuperVertex *>::const_iterator kt =
                this->vertices.find(it->second);
        assert(kt != this->vertices.end());
        SuperVertex *superVertex = kt->second;
        return superVertex->toSet();
    }
}

bool ResultsGraph::has_syn(const string& syn) const
{
    map<string, int>::const_iterator it = this->synMap.find(syn);
    if (it == this->synMap.end()) {
        return false;
    }
    int synLabel = it->second;
    map<int, SuperVertex *>::const_iterator kt =
            this->vertices.find(synLabel);
    return (kt != this->vertices.end());
}

bool ResultsGraph::has_syn(int syn) const
{
    map<int, SuperVertex *>::const_iterator it =
            this->vertices.find(syn);
    return (it != this->vertices.end());
}

int ResultsGraph::syn_to_int(const string& syn) const
{
    map<string, int>::const_iterator it =
            this->synMap.find(syn);
    if (it == this->synMap.end()) {
        return -1;
    }
    int synLabel = it->second;
    map<int, SuperVertex *>::const_iterator kt =
            this->vertices.find(synLabel);
    if (kt == this->vertices.end()) {
        return -1;
    } else {
        SuperVertex *v = kt->second;
        return v->get_syn();
    }
}

int ResultsGraph::retrieve_superVertex_label(const string &syn)
{
    int synLabel;
    if (this->synMap.find(syn) == this->synMap.end()) {
        synLabel = this->SYNLABEL++;
        this->synMap[syn] = synLabel;
    }
    return this->synMap[syn];
}

int ResultsGraph::retrieve_value_label(const string& value)
{
    int valueLabel;
    if (this->valueMap.find(value) == this->valueMap.end()) {
        valueLabel = this->VALUELABEL++;
        this->valueMap[value] = valueLabel;
        this->intValueToString[valueLabel] = value;
    }
    return this->valueMap[value];
}

// private version
Vertex *ResultsGraph::add_vertex(DesignEnt synType,
        int syn, const string& value, int valueInt)
{
    SuperVertex *superVertex;
    Vertex *vertex;
    if (this->vertices.find(syn) == this->vertices.end()) {
        superVertex = new SuperVertex(synType, syn);
        this->vertices[syn] = superVertex;
    }
    superVertex = this->vertices[syn];
    assert(superVertex->get_synType() == synType);
    vertex = superVertex->add_vertex(value, valueInt);
    return vertex;
}

void ResultsGraph::reset()
{
    SuperVertex *v;
    for (map<int, SuperVertex *>::const_iterator it =
            this->vertices.begin(); it != this->vertices.end(); it++) {
        v = it->second;
        const map<int, Vertex *>& vertices = v->get_vertices();
        for (map<int, Vertex *>::const_iterator kt = vertices.begin();
                kt != vertices.end(); kt++) {
            delete kt->second;
        }
        delete v;
    }
}

string ResultsGraph::toString() const
{
    StringBuffer sb;
    for (map<int, SuperVertex *>::const_iterator it =
            this->vertices.begin(); it != this->vertices.end(); it++) {
        string s = it->second->toString();
        if (s.size() > 0) {
            sb.append(s);
        }
    }
    return sb.toString();
}

void ResultsGraph::prune_prelude(int syn,
        map<int, PruneInfo, PruneInfoCmp>& q,
        set<Vertex *>& garbage)
{
    set<Vertex *> pruneSet;
    if (this->vertices.find(syn) != this->vertices.end()) {
        SuperVertex *superVertex = this->vertices[syn];
        pruneSet = superVertex->get_unblessed();
        if (pruneSet.size() > 0 && q.find(syn) == q.end()) {
            q[syn] = PruneInfo(syn);
        }
        for (set<Vertex *>::const_iterator it = pruneSet.begin();
                it != pruneSet.end(); it++) {
            // kill off unblessed
            set<Vertex *> neighbors = (*it)->destroy();
            garbage.insert(*it);
            for (set<Vertex *>::const_iterator kt = neighbors.begin();
                    kt != neighbors.end(); kt++) {
                q[syn].add_vertex(*kt);
            }
        }
    }
}

void ResultsGraph::prune(const string& syn)
{
    if (this->has_syn(syn)) {
        this->prune(syn_to_int(syn));
    } else {
        // didnt add such synonym. graph is dead
        this->alive = false;
    }
}

void ResultsGraph::prune(int syn)
{
    map<int, PruneInfo, PruneInfoCmp> q;
    set<Vertex *> garbage;
    set<int> synToReset;
    synToReset.insert(syn);
    this->prune_prelude(syn, q, garbage);
    this->prune__(&q, garbage, synToReset);
}

void ResultsGraph::prune(const string& syn, const string& syn2)
{
    if (this->has_syn(syn) && this->has_syn(syn2)) {
        this->prune(this->syn_to_int(syn), this->syn_to_int(syn2));
    } else {
        this->alive = false;
    }
}

void ResultsGraph::prune(const string& syn, int syn2)
{
    if (this->has_syn(syn) && this->has_syn(syn2)) {
        this->prune(this->syn_to_int(syn), syn2);
    } else {
        this->alive = false;
    }
}

void ResultsGraph::prune(int syn, const string& syn2)
{
    if (this->has_syn(syn) && this->has_syn(syn2)) {
        this->prune(syn, this->syn_to_int(syn2));
    } else {
        this->alive = false;
    }
}

void ResultsGraph::prune(int syn1, int syn2)
{
    if (this->has_syn(syn1) && this->has_syn(syn2)) {
        map<int, PruneInfo, PruneInfoCmp> q;
        set<Vertex *> garbage;
        set<int> synToReset;
        synToReset.insert(syn1);
        synToReset.insert(syn2);
        if (syn1 == syn2) {
            this->prune_prelude(syn1, q, garbage);
        } else {
            this->prune_prelude(syn1, q, garbage);
            this->prune_prelude(syn2, q, garbage);
        }
        this->prune__(&q, garbage, synToReset);
    } else {
        this->alive = false;
    }
}

void ResultsGraph::prune__(map<int, PruneInfo, PruneInfoCmp> *q,
        set<Vertex *>& garbage, const set<int>& synToReset)
{
    map<int, PruneInfo, PruneInfoCmp> mm;
    map<int, PruneInfo, PruneInfoCmp> *curQ, *nextQ, *tmpQ;
    curQ = q;
    nextQ = &mm;
    int checkAgainst, tmpSyn;
    Vertex *v;

    while (!curQ->empty()) {
        nextQ->clear();
        for (map<int, PruneInfo, PruneInfoCmp>::const_iterator
                it = curQ->begin(); it != curQ->end(); it++) {
            checkAgainst = it->first;
            const PruneInfo &pinfo = it->second;
            for (set<Vertex *>::const_iterator kt = pinfo.vertices.begin();
                    kt != pinfo.vertices.end(); kt++) {
                v = *kt;
                // no relevant neighbor, destroy.
                if (v->is_alive() && !v->has_neighbor(checkAgainst)) {
                    garbage.insert(v);
                    tmpSyn = v->get_syn();
                    if (nextQ->find(tmpSyn) == nextQ->end()) {
                        (*nextQ)[tmpSyn] = PruneInfo(tmpSyn);
                    }
                    set<Vertex *> neighbors = v->destroy();
                    for (set<Vertex *>::const_iterator
                            toCheck = neighbors.begin();
                            toCheck != neighbors.end(); toCheck++) {
                        (*nextQ)[tmpSyn].add_vertex(*toCheck);
                    }
                }
            }
        }
        // swap queues
        tmpQ = curQ;
        curQ = nextQ;
        nextQ = tmpQ;
    }

    // cleanup
    for (set<Vertex *>::const_iterator it = garbage.begin();
            it != garbage.end(); it++) {
        delete (*it);
    }

    // reset graph
    map<int, SuperVertex *>::const_iterator superIt;
    bool aliveNext = true;
    for (set<int>::const_iterator it = synToReset.begin();
            it != synToReset.end(); it++) {
        superIt = this->vertices.find(*it);
        if (superIt != this->vertices.end()) {
            SuperVertex *superVertex = superIt->second;
            aliveNext = superVertex->reset() && aliveNext;
        } else {
            aliveNext = false;
        }
    }
    this->alive = aliveNext;
}

bool ResultsGraph::is_alive() const
{
    return this->alive;
}