#include <iostream>
#include <vector>

void sortColors(std::vector<int>& colors) {
    int red = 0, white = 0, blue = colors.size() - 1;

    while (white <= blue) {
        if (colors[white] == 0) {  // Red
            std::swap(colors[red], colors[white]);
            red++;
            white++;
        } else if (colors[white] == 1) {  // White
            white++;
        } else {  // Blue
            std::swap(colors[white], colors[blue]);
            blue--;
        }
    }
}

int main() {
    std::vector<int> colors = {2, 0, 2, 0, 0, 1, 0, 2, 1};
    sortColors(colors);
    for (int color : colors) {
        std::cout << color << " ";
    }
    return 0;
}