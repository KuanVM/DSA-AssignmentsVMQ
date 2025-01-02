#include <iostream>
using namespace std;

// Đồ thị sử dụng ma trận kề
class Graph {
private:
    int adj_matrix[100][100]; // Ma trận kề (giả định tối đa 100 đỉnh)
    int num_nodes;            // Số đỉnh

public:
    // Hàm khởi tạo đồ thị
    Graph(int n) {
        num_nodes = n;
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= n; j++) {
                adj_matrix[i][j] = 0; // Khởi tạo ma trận kề với giá trị 0
            }
        }
    }

    // Hàm thêm cạnh vào đồ thị
    void add_edge(int u, int v) {
        adj_matrix[u][v] = 1; // Đánh dấu các cạnh từ u đến v
        adj_matrix[v][u] = 1; // Đồ thị vô hướng
    }

    // Hàm duyệt BFS
    void bfs(int start) {
        int scanned[100] = { 0 }; // Mảng đánh dấu đỉnh đã quét qua
        int queue[100];         // Hàng đợi
        int front = 0, rear = 0;

        queue[rear++] = start;  // Đưa đỉnh bắt đầu vào hàng đợi
        scanned[start] = 1;     // Đánh dấu đã quét qua

        cout << "Thu tu duyet BFS: ";
        while (front < rear) {
            int current = queue[front++]; // Lấy đỉnh từ hàng đợi
            cout << current << " ";       // In đỉnh đang duyệt

            // Duyệt các đỉnh kề
            for (int i = 1; i <= num_nodes; i++) {
                if (adj_matrix[current][i] == 1 && scanned[i] == 0) {
                    queue[rear++] = i;    // Đưa đỉnh kề vào hàng đợi
                    scanned[i] = 1;       // Đánh dấu đã quét qua
                }
            }
        }
        cout << endl;
    }

    // Hàm duyệt DFS
    void dfs(int start) {
        int scanned[100] = { 0 }; // Mảng đánh dấu đỉnh đã quét qua
        int stack[100];         // Ngăn xếp
        int top = -1;

        stack[++top] = start;  // Đưa đỉnh bắt đầu vào ngăn xếp

        cout << "Thu tu duyet DFS: ";
        while (top >= 0) {
            int current = stack[top--]; // Lấy đỉnh từ ngăn xếp

            if (scanned[current] == 0) {
                scanned[current] = 1;   // Đánh dấu đã quét qua
                cout << current << " "; // In đỉnh đang duyệt

                // Thêm các đỉnh kề vào ngăn xếp
                for (int i = num_nodes; i >= 1; i--) {
                    if (adj_matrix[current][i] == 1 && scanned[i] == 0) {
                        stack[++top] = i;
                    }
                }
            }
        }
        cout << endl;
    }
};

int main() {
    int num_nodes, num_edges;

    // Nhập số đỉnh và số cạnh
    cout << "Nhap so dinh va so canh: ";
    cin >> num_nodes >> num_edges;

    Graph g(num_nodes);

    // Nhập các cạnh
    cout << "Nhap cac canh (u v):" << endl;
    for (int i = 0; i < num_edges; i++) {
        int u, v;
        cin >> u >> v;
        g.add_edge(u, v);
    }

    int start;
    // Nhập đỉnh bắt đầu duyệt
    cout << "Nhap dinh bat dau duyet: ";
    cin >> start;

    // Duyệt đồ thị
    g.bfs(start);
    g.dfs(start);

    return 0;
}