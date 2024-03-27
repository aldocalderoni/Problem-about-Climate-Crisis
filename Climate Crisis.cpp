#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

bool isValidCoordinate(int x, int y, int rows, int cols) {
	return (x >= 0 && x < cols && y >= 0 && y < rows);
}

bool isVisited(std::vector<std::string>& visited, int x, int y) {
	return (visited[y][x] == '1');
}

bool isMeltingBorder(std::vector<std::vector<int>>& meltingBorders, int x, int y) {
	return (std::find(meltingBorders.begin(), meltingBorders.end(), std::vector<int>{x, y}) != meltingBorders.end());
}

void exploreCell(std::vector<std::string>& grid, std::vector<std::string>& visited, std::vector<std::vector<int>>& meltingBorders, int x, int y) {
	visited[y][x] = '1';

	int rows = grid.size();
	int cols = grid[0].length();

	std::vector<std::pair<int, int>> directions = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};

	for (const auto& dir : directions) {
		int newX = x + dir.first;
		int newY = y + dir.second;

		if (isValidCoordinate(newX, newY, rows, cols)) {
			if (grid[newY][newX] == '1') {
				meltingBorders.push_back({newX, newY});
			} else if (grid[newY][newX] == '0' && !isVisited(visited, newX, newY) && !isMeltingBorder(meltingBorders, newX, newY)) {
				exploreCell(grid, visited, meltingBorders, newX, newY);
			}
		}
	}
}

int main() {
	int rows, cols;
	std::cin >> rows >> cols;
	std::vector<std::string> grid;

	for (int i = 0; i < rows; ++i) {
		std::string row;
		std::cin >> row;
		grid.push_back(row);
	}

	std::vector<std::string> new_grid = grid;
	std::string zeros(cols, '0');
	std::vector<std::string> visited;
	std::vector<std::vector<int>> meltingBorders;
	
	for (int i = 0; i < rows; i++) visited.push_back(zeros);
	
	int counter = 0;

	bool flag = true;
	while (flag) {
		int initX = 0;
		int initY = 0;
		exploreCell(new_grid, visited, meltingBorders, initX, initY);
		int sizeMB = meltingBorders.size();

		for (int i = 0; i < sizeMB; i++) {
			int x = meltingBorders[i][0];
			int y = meltingBorders[i][1];
			new_grid[y][x] = '0';
		}
		meltingBorders.clear();
		for (int i = 0; i < rows; i++) visited[i] = zeros;

		flag = false;
		for (size_t i = 0; i < new_grid.size(); i++) {
			if (new_grid[i] != zeros) {
				flag = true;
				break;
			}
		}
		counter++;
	}

	std::cout << counter;

	return 0;
}