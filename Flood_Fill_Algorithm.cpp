#include <iostream>
#include <vector>
#include <queue>

/*
  BÀI TOÁN "FLOOD FILL ALGORITHM"

  Mô tả bài toán:
  ---------------
  - Bài toán Flood Fill được sử dụng để điền màu vào một vùng kết nối trong ma trận 2D.
  - Xuất phát từ một ô nhất định, thuật toán sẽ điền màu mới vào tất cả các ô kết nối với ô ban đầu bằng một quy tắc kết nối cụ thể (4 hoặc 8 hướng).
  - Mục tiêu: Điền màu vào toàn bộ vùng kết nối với ô ban đầu.

  Ý tưởng thuật toán:
  ------------------
  - Có hai cách tiếp cận phổ biến:
    1. Đệ quy: Gọi đệ quy đến các ô láng giềng để điền màu.
    2. Lặp: Sử dụng hàng đợi hoặc ngăn xếp để thực hiện thuật toán lặp.

  - Công thức giải quyết:
      Nếu ô hiện tại có màu giống màu gốc:
          - Điền màu mới.
          - Thêm các ô láng giềng vào hàng đợi (nếu là phương pháp lặp).

  - Độ phức tạp:
      + Thời gian: O(n * m), với n, m là kích thước ma trận.
      + Không gian: O(n * m) cho hàng đợi (phương pháp lặp) hoặc ngăn xếp đệ quy (phương pháp đệ quy).
*/

// Hàm kiểm tra tính hợp lệ của ô trong ma trận
bool isValid(int x, int y, int rows, int cols) {
    // Kiểm tra xem ô (x, y) có nằm trong phạm vi ma trận hay không
    return (x >= 0 && x < rows && y >= 0 && y < cols);
}

// Phương pháp đệ quy
void floodFillRecursive(std::vector<std::vector<int>> &grid, int x, int y, int newColor, int originalColor) {
    // Điều kiện dừng: Nếu ô (x, y) không hợp lệ hoặc không cùng màu gốc, dừng đệ quy
    if (!isValid(x, y, grid.size(), grid[0].size()) || grid[x][y] != originalColor) {
        return;
    }

    // Điền màu mới vào ô hiện tại
    grid[x][y] = newColor;

    // Gọi đệ quy cho 4 ô láng giềng (trên, dưới, trái, phải)
    floodFillRecursive(grid, x + 1, y, newColor, originalColor);
    floodFillRecursive(grid, x - 1, y, newColor, originalColor);
    floodFillRecursive(grid, x, y + 1, newColor, originalColor);
    floodFillRecursive(grid, x, y - 1, newColor, originalColor);
}

// Phương pháp lặp
void floodFillIterative(std::vector<std::vector<int>> &grid, int x, int y, int newColor) {
    int rows = grid.size();
    int cols = grid[0].size();
    int originalColor = grid[x][y];

    // Nếu màu mới trùng với màu gốc, không cần thực hiện
    if (originalColor == newColor) return; // Tránh vòng lặp vô tận

    // Khởi tạo hàng đợi để duyệt các ô cần xử lý
    std::queue<std::pair<int, int>> q;
    q.push({x, y});

    // Các hướng di chuyển (4 hướng: trên, dưới, trái, phải)
    int dx[] = {1, -1, 0, 0};
    int dy[] = {0, 0, 1, -1};

    while (!q.empty()) {
        // Lấy ô hiện tại từ hàng đợi
        auto [cx, cy] = q.front();
        q.pop();

        // Nếu ô không hợp lệ hoặc không cùng màu gốc, bỏ qua
        if (!isValid(cx, cy, rows, cols) || grid[cx][cy] != originalColor) {
            continue;
        }

        // Điền màu mới vào ô hiện tại
        grid[cx][cy] = newColor;

        // Thêm các ô láng giềng vào hàng đợi để xử lý tiếp
        for (int i = 0; i < 4; i++) {
            int nx = cx + dx[i];
            int ny = cy + dy[i];
            q.push({nx, ny});
        }
    }
}

// Hàm chính
int main() {
    // Nhập kích thước ma trận
    int rows, cols;
    std::cout << "Nhập số dòng và số cột của ma trận: ";
    std::cin >> rows >> cols;

    // Tạo ma trận với kích thước nhập vào
    std::vector<std::vector<int>> grid(rows, std::vector<int>(cols));

    // Nhập các phần tử của ma trận
    std::cout << "Nhập các phần tử của ma trận: \n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cin >> grid[i][j];
        }
    }

    // Nhập tọa độ bắt đầu và màu mới
    int x, y, newColor;
    std::cout << "Nhập tọa độ bắt đầu (x, y) và màu mới: ";
    std::cin >> x >> y >> newColor;

    // Gọi thuật toán Flood Fill (chọn đệ quy hoặc lặp)
    int originalColor = grid[x][y];

    // Sử dụng phương pháp lặp để tránh tràn stack
    floodFillIterative(grid, x, y, newColor);

    // In kết quả sau khi áp dụng thuật toán
    std::cout << "Ma trận sau khi áp dụng Flood Fill: \n";
    for (const auto &row : grid) {
        for (int cell : row) {
            std::cout << cell << " ";
        }
        std::cout << "\n";
    }

    return 0;
}
