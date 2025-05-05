#include "maze_solver.h"
#include <stack>
using namespace std;

bool MazeSolver::dfs(Maze& maze, int r, int c, vector<vector<bool>>& visited) {
    // Guard: Check for out of bounds, wall, or already visited
    if (r < 0 || r >= maze.grid.size() || c < 0 || c >= maze.grid[0].size() ||
        maze.grid[r][c] == '#' || visited[r][c]) {
        return false;
    }

    // Goal: Check if the current position is the finish
    if (maze.grid[r][c] == 'F') {
        maze.path.push_back({r, c}); // Add finish to path
        return true;
    }

    // Mark the current cell as visited
    visited[r][c] = true;

    // Explore in all four directions: North, East, South, West
    if (dfs(maze, r - 1, c, visited) || // North
        dfs(maze, r, c + 1, visited) || // East
        dfs(maze, r + 1, c, visited) || // South
        dfs(maze, r, c - 1, visited)) { // West
        maze.path.push_back({r, c}); // Add current cell to path only if a path is found
        return true;
    }

    // Fail: If no path is found, return false
    return false;
}

bool MazeSolver::solveDFS(Maze& maze) {
    // Clear any existing path
    maze.path.clear();
    
    // Create visited matrix
    vector<vector<bool>> visited(maze.grid.size(), 
                               vector<bool>(maze.grid[0].size(), false));
    
    // Start DFS from the start position
    bool found = dfs(maze, maze.start.row, maze.start.col, visited);
    
    // If path found, add the start position to the path
    if (found) {
        maze.path.push_back(maze.start);
    }
    
    return found;
}
