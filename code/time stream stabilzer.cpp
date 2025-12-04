#include <iostream>
#include <string>
using namespace std;

/*
    ============================================
        CHRONOS CORPORATION: TIME-STREAM CORE
    ============================================
    Every historical event is stored inside a 
    TimeCapsule, forming a Binary Search Tree
    that keeps the entire universe stable.
*/

struct TimeCapsule {
    int year;              // Timeline Key
    string eventName;      // What happened?
    TimeCapsule* left;     // Past
    TimeCapsule* right;    // Future

    TimeCapsule(int y, string name) {
        year = y;
        eventName = name;
        left = right = nullptr;
    }
};

/*
    ============================================
           TIME-STREAM BST CLASS
    ============================================
    Handles injecting new events, removing 
    paradox years, searching the timeline, 
    and generating chronological reports.
*/

class TimeStream {
private:
    TimeCapsule* root;

    // ---- INSERT OPERATION ----
    TimeCapsule* insert(TimeCapsule* node, int year, string name) {
        if (!node) return new TimeCapsule(year, name);

        if (year < node->year)
            node->left = insert(node->left, year, name);
        else if (year > node->year)
            node->right = insert(node->right, year, name);

        // If equal, do nothing (duplicates not allowed)
        return node;
    }

    // ---- SEARCH OPERATION ----
    TimeCapsule* search(TimeCapsule* node, int year) {
        if (!node || node->year == year) return node;

        if (year < node->year)
            return search(node->left, year);
        else
            return search(node->right, year);
    }

    // ---- FIND MIN FOR DELETE ----
    TimeCapsule* findMin(TimeCapsule* node) {
        while (node && node->left)
            node = node->left;
        return node;
    }

    // ---- DELETE OPERATION (PARADOX) ----
    TimeCapsule* deleteNode(TimeCapsule* node, int year) {
        if (!node) return nullptr;

        if (year < node->year)
            node->left = deleteNode(node->left, year);

        else if (year > node->year)
            node->right = deleteNode(node->right, year);

        else {
            // Case 1: No children
            if (!node->left && !node->right)
                return nullptr;

            // Case 2: One child
            else if (!node->left)
                return node->right;
            else if (!node->right)
                return node->left;

            // Case 3: Two children -> use inorder successor
            TimeCapsule* successor = findMin(node->right);
            node->year = successor->year;
            node->eventName = successor->eventName;
            node->right = deleteNode(node->right, successor->year);
        }
        return node;
    }

    // ---- IN-ORDER TRAVERSAL ----
    void inorder(TimeCapsule* node) {
        if (!node) return;
        inorder(node->left);
        cout << node->year << ": " << node->eventName << endl;
        inorder(node->right);
    }

    // ---- FIND MINIMUM YEAR ----
    int findMinYear(TimeCapsule* node) {
        if (!node) return -1;
        while (node->left) node = node->left;
        return node->year;
    }

    // ---- FIND MAXIMUM YEAR ----
    int findMaxYear(TimeCapsule* node) {
        if (!node) return -1;
        while (node->right) node = node->right;
        return node->year;
    }

public:
    TimeStream() { root = nullptr; }

    // ---- PUBLIC INTERFACE ----

    void inject(int year, string name) {
        cout << "> System: Injecting " << year << "... Timeline stable." << endl;
        root = insert(root, year, name);
    }

    void paradox(int year) {
        cout << "\n> Alert: Paradox detected at " << year << "!" << endl;
        root = deleteNode(root, year);
        cout << "> System: Year " << year << " removed. Timeline stabilized.\n";
    }

    void searchYear(int year) {
        cout << "\n> Query: Searching for " << year << "..." << endl;
        TimeCapsule* result = search(root, year);

        if (result)
            cout << "> Result: Event Found! [" << result->year
                 << ": " << result->eventName << "]\n";
        else
            cout << "> Result: Year " << year 
                 << " not found in current timeline.\n";
    }

    void report() {
        cout << "\n> COMMAND: CHRONOLOGICAL REPORT\n";
        cout << "-------------------------------\n";
        inorder(root);
        cout << "-------------------------------\n";
    }

    // ---- BONUS FEATURE ----
    int CalculateTimeSpan() {
        if (!root) return 0;
        int minYear = findMinYear(root);
        int maxYear = findMaxYear(root);
        return maxYear - minYear;
    }
};

/*
    ============================================
                 MAIN SIMULATION
    ============================================
*/

int main() {
    TimeStream timeline;

    timeline.inject(2050, "Mars Colony Established");
    timeline.inject(1969, "Moon Landing");
    timeline.inject(2100, "Warp Drive Invented");
    timeline.inject(2000, "Y2K Bug");

    timeline.searchYear(1969);

    timeline.inject(1990, "World Wide Web");

    timeline.paradox(2000);

    timeline.report();

    timeline.searchYear(2000);

    cout << "\nTime Span (BONUS): " 
         << timeline.CalculateTimeSpan() 
         << " years\n";

    return 0;
}
