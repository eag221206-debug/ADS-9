// Copyright 2022 NNTU-CS
#include <iostream>
#include <fstream>
#include <locale>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include "tree.h"

PMTree::PMTree(std::vector<char> in) {
    std::sort(in.begin(), in.end());
    root = new Node('\0');
    root->children = buildTree(in);
}

PMTree::~PMTree() {
    delete root;
}

std::vector<Node*> PMTree::buildTree(std::vector<char> available) {
    std::vector<Node*> children;
    if (available.empty()) {
        return children;
    }

    for (size_t i = 0; i < available.size(); ++i) {
        Node* child = new Node(available[i]);
        std::vector<char> remaining = available;
        remaining.erase(remaining.begin() + i);
        child->children = buildTree(remaining);
        children.push_back(child);
    }
    return children;
}

void dfs(Node* node, std::vector<char>& current, std::vector<std::vector<char>>& result) {
    if (!node) return;
    
    if (node->value != '\0') {
        current.push_back(node->value);
    }

    if (node->children.empty()) {
        if (node->value != '\0') {
            result.push_back(current);
        }
    } else {
        for (Node* child : node->children) {
            dfs(child, current, result);
        }
    }

    if (node->value != '\0') {
        current.pop_back();
    }
}

std::vector<std::vector<char>> getAllPerms(PMTree& tree) {
    std::vector<std::vector<char>> result;
    std::vector<char> current;
    dfs(tree.root, current, result);
    return result;
}

std::vector<char> getPerm1(PMTree& tree, int num) {
    std::vector<std::vector<char>> all_perms = getAllPerms(tree);
    if (num > 0 && num <= all_perms.size()) {
        return all_perms[num - 1];
    }
    return {};
}

int getFactorial(int n) {
    int res = 1;
    for (int i = 2; i <= n; ++i) {
        res *= i;
    }
    return res;
}

std::vector<char> getPerm2(PMTree& tree, int num) {
    std::vector<char> result;
    if (!tree.root || tree.root->children.empty()) return result;

    int k = num - 1;
    Node* current = tree.root;
    int n = current->children.size();

    while (!current->children.empty()) {
        int fact = getFactorial(n - 1); 
        int idx = k / fact; 
        
        if (idx >= current->children.size()) return {}; 
        
        current = current->children[idx];
        result.push_back(current->value);
        
        k = k % fact; 
        n--;
    }
    
    return result;
}
