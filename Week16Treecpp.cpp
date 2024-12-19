#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Node structure representing a chapter, section, subsection, etc.
struct Node {
    string title;             // Title of the chapter, section, etc.
    int pageCount;            // Number of pages in this node
    vector<Node*> smallNode;   // smallNode nodes (e.g., subsections)

    Node(string t, int p) : title(t), pageCount(p) {}
};

// Function to count the total number of chapters (first-level smallNode)
int countChapters(Node* root) {
    if (!root) return 0;
    return root->smallNode.size();
}

// Function to find the longest chapter based on page count (including smallNode)
Node* findLongestChapter(Node* root) {
    if (!root) return nullptr;

    Node* longestChapter = nullptr;
    int maxPages = 0;

    for (Node* chapter : root->smallNode) {
        int totalPages = chapter->pageCount;

        // Add the page count of this chapter's smallNode
        vector<Node*> stack = chapter->smallNode; // Use a stack for traversal
        while (!stack.empty()) {
            Node* current = stack.back();
            stack.pop_back();
            totalPages += current->pageCount;

            // Add smallNode of the current node to the stack
            for (Node* child : current->smallNode) {
                stack.push_back(child);
            }
        }

        if (totalPages > maxPages) {
            maxPages = totalPages;
            longestChapter = chapter;
        }
    }

    return longestChapter;
}

// Function to find and delete a node by title, updates parent page count
bool deleteNode(Node* root, const string& title) {
    if (!root) return false;

    for (auto it = root->smallNode.begin(); it != root->smallNode.end(); ++it) {
        if ((*it)->title == title) {
            // Subtract the page count of the deleted node from the parent
            root->pageCount -= (*it)->pageCount;

            // Delete the node and remove it from the smallNode vector
            delete *it;
            root->smallNode.erase(it);
            return true;
        }
        // Recursively search in smallNode
        if (deleteNode(*it, title)) {
            root->pageCount -= (*it)->pageCount;
            return true;
        }
    }
    return false;
}

// Function to print the tree (for debugging purposes)
void printTree(Node* root, int depth = 0) {
    if (!root) return;
    cout << string(depth * 2, ' ') << root->title << " (" << root->pageCount << " pages)" << endl;
    for (Node* child : root->smallNode) {
        printTree(child, depth + 1);
    }
}

int main() {
    // Create root node (the book itself)
    Node* book = new Node("Book", 0);

    // Add chapters
    Node* chapter1 = new Node("Chapter 1: Introduction", 20);
    Node* chapter2 = new Node("Chapter 2: Advanced Topics", 30);
    Node* chapter3 = new Node("Chapter 3: Conclusion", 15);

    // Add sections to Chapter 1
    Node* section1_1 = new Node("Section 1.1: Basics", 10);
    Node* section1_2 = new Node("Section 1.2: Overview", 10);
    chapter1->smallNode.push_back(section1_1);
    chapter1->smallNode.push_back(section1_2);

    // Add subsections to Section 1.1
    Node* subsection1_1_1 = new Node("Subsection 1.1.1: Details", 5);
    section1_1->smallNode.push_back(subsection1_1_1);

    // Add chapters to the book
    book->smallNode.push_back(chapter1);
    book->smallNode.push_back(chapter2);
    book->smallNode.push_back(chapter3);

    // Update total page count of the book
    book->pageCount = chapter1->pageCount + chapter2->pageCount + chapter3->pageCount;

    // Print the tree
    cout << "Book structure:" << endl;
    printTree(book);

    // Count the number of chapters
    cout << "\nNumber of chapters: " << countChapters(book) << endl;

    // Find the longest chapter
    Node* longestChapter = findLongestChapter(book);
    if (longestChapter) {
        cout << "Longest chapter: " << longestChapter->title << endl;
    }

    // Delete a node (e.g., "Section 1.1: Basics")
    string titleToDelete = "Section 1.1: Basics";
    if (deleteNode(book, titleToDelete)) {
        cout << "\nDeleted: " << titleToDelete << endl;
    } else {
        cout << "\nCould not find: " << titleToDelete << endl;
    }

    // Print the updated tree
    cout << "\nUpdated book structure:" << endl;
    printTree(book);

    delete book;

    return 0;
}