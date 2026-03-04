#ifndef OCTREE_H
#define OCTREE_H

class T_Node {
public:
    T_Node* children[2][2][2];
    // дописать методы
};

class Octree {
public:
    T_Node* base;
    int dim;
    // дописать
};

#endif // OCTREE_H
