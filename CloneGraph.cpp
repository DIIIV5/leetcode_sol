/*
Given a reference of a node in a connected undirected graph.

Return a deep copy (clone) of the graph.

Each node in the graph contains a value (int) and a list (List[Node]) of its neighbors.

// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
*/
#include <unordered_map>

class Solution {
public:
    std::unordered_map<Node*, Node*> nodesMap;
    Node* cloneGraph(Node* node) 
    {
        if(!node)
        {
            return NULL;
        }

        Node* head = new Node {node->val, vector<Node*>{}};
        nodesMap.insert({node, head});
        for(auto n: node->neighbors)
        {
            if(nodesMap.count(n))
            {
                head->neighbors.push_back(nodesMap[n]);
            }
            else
            {
                head->neighbors.push_back(cloneGraph(n));
            }
        }

        return head;
    }
};