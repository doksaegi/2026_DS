#include "ds/ScoreTree.h"
#include <iostream>

ScoreTree::ScoreTree() : root(nullptr), count(0) {}
ScoreTree::~ScoreTree() { clear(); }

void ScoreTree::insert(const ScoreRecord& record) {
    root = insertRecursive(root, record);
}

ScoreTree::Node* ScoreTree::insertRecursive(Node* current, const ScoreRecord& record) {
    if (current == nullptr) {
        ++count;
        return new Node(record);
    }
    if (record.score < current->record.score)
        current->left  = insertRecursive(current->left,  record);
    else
        current->right = insertRecursive(current->right, record);
    return current;
}

bool ScoreTree::containsPlayer(const std::string& playerName) const {
    return containsRecursive(root, playerName);
}

// 이름 기준 탐색이라 양쪽 모두 탐색 (O(n))
bool ScoreTree::containsRecursive(Node* current, const std::string& playerName) const {
    if (current == nullptr) return false;
    if (current->record.playerName == playerName) return true;
    return containsRecursive(current->left,  playerName)
        || containsRecursive(current->right, playerName);
}

ScoreTree::Node* ScoreTree::removeByNameRecursive(Node* current, const std::string& name, bool& removed) {
    if (current == nullptr) return nullptr;
    if (current->record.playerName == name) {
        removed = true;
        --count;
        if (current->left == nullptr) {
            Node* right = current->right;
            delete current;
            return right;
        }
        if (current->right == nullptr) {
            Node* left = current->left;
            delete current;
            return left;
        }
        // 후계자(오른쪽 서브트리 최솟값)로 대체
        Node* successor = current->right;
        while (successor->left) successor = successor->left;
        current->record = successor->record;
        bool dummy = false;
        current->right = removeByNameRecursive(current->right, successor->record.playerName, dummy);
        if (dummy) ++count; // 내부 재귀에서 중복 감소 방지
        return current;
    }
    current->left  = removeByNameRecursive(current->left,  name, removed);
    current->right = removeByNameRecursive(current->right, name, removed);
    return current;
}

void ScoreTree::removeByName(const std::string& name) {
    bool removed = false;
    root = removeByNameRecursive(root, name, removed);
}

void ScoreTree::printDescending() const {
    if (root == nullptr) {
        std::cout << "기록된 점수가 없습니다.\n";
        return;
    }
    std::cout << "=== 점수 랭킹 (높은 순) ===\n";
    printDescendingRecursive(root);
}

// 역 중위 순회: right -> current -> left
void ScoreTree::printDescendingRecursive(Node* current) const {
    if (current == nullptr) return;
    printDescendingRecursive(current->right);
    std::cout << "  " << current->record.playerName
              << " - " << current->record.score << "원\n";
    printDescendingRecursive(current->left);
}

void ScoreTree::clearRecursive(Node* current) {
    if (current == nullptr) return;
    clearRecursive(current->left);
    clearRecursive(current->right);
    delete current;
}

int  ScoreTree::size()    const { return count; }
bool ScoreTree::isEmpty() const { return count == 0; }

void ScoreTree::clear() {
    clearRecursive(root);
    root  = nullptr;
    count = 0;
}
