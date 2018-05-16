





#include <cstdio>
#include <vector>
#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;




struct instance {
    vector<double> attr;
    double tar;
};


class node {
private:
    int splitAttribute;
    double splitVal;
    
public:
    void addInstance(vector<instance> x){
        inst = x;
    }
    long long instanceCount(){
        return inst.size();
    }
    double ans;
    vector<instance> inst;
    int getAttr(){
        return splitAttribute;
    }
    double getVal(){
        return splitVal;
    }
};


class tree {
private:
    
    vector<node> Tree;
    double entropy(vector<instance> x, int attr){
        vector<double> prob = probability(x, attr);
        double entropy = 0;
        for (int i=0; i<prob.size(); i++) {
            entropy = entropy - prob[i]*log(prob[i]);
        }
        return entropy;
    }
    vector<double> probability(vector<instance>x, int attr);
    vector<int> attributeLeft;
    void train(long long x){
        int splitAttr = 0;
        double splitVal = 0.0;
        if (Tree[x].instanceCount() == 0) {
            Tree[x].ans = Tree[x/2].ans;
            return;
        }
        if (attributeLeft.size()==0) {
            Tree[x].ans = Tree[x/2].ans;
            return;
        }
        Tree.push_back(node());
        Tree.push_back(node());
        vector<instance> small;
        vector<instance> large;
        
        for (int i=0; i<attributeLeft.size(); i++) {
            if (Tree[x].inst[i].attr[splitAttr] < splitVal) {
                small.push_back(Tree[x].inst[i]);
            }
            else{
                large.push_back(Tree[x].inst[i]);
            }
        }
        Tree[Tree.size()-2].addInstance(small);
        Tree[Tree.size()-1].addInstance(large);
        
        train(Tree.size()-2);
        train(Tree.size()-1);
        
    }
    
public:

    void initialize(vector<instance> x){
        node dummy;
        Tree.push_back(dummy);
        
        node root;
        root.addInstance(x);
    }
    void train(){
        train(1);
    }
    double predict(instance a){
        long long ite = 1;
        while (ite < Tree.size()) {
            int splitAttributeIte = Tree[ite].getAttr();
            double splitVal = Tree[ite].getVal();
            if (a.attr[splitAttributeIte] < splitVal) {
                ite = ite*2;
            }
            else{
                ite = ite*2 + 1;
            }
        }
        return Tree[ite].ans;
    }
    
};


int main() {
   
    tree t;
    vector<instance> x;
    t.initialize(x);
    
    
    
    
    
    return 0;
}
