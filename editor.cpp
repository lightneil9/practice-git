#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <sstream>

using namespace std;

class GraphicalEditor {
private:
    vector<vector<char>> table;
    int M, N; // M columns, N rows
    bool initialized;

public:
    GraphicalEditor() : M(0), N(0), initialized(false) {}

    void createTable(int cols, int rows) {
        M = cols;
        N = rows;
        table = vector<vector<char>>(N, vector<char>(M, 'O'));
        initialized = true;
    }

    void clearTable() {
        if (!initialized) return;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                table[i][j] = 'O';
            }
        }
    }

    void colorPixel(int x, int y, char color) {
        if (!initialized || x < 1 || x > M || y < 1 || y > N) return;
        table[y-1][x-1] = color;
    }

    void drawVerticalLine(int x, int y1, int y2, char color) {
        if (!initialized || x < 1 || x > M) return;
        if (y1 > y2) swap(y1, y2);
        for (int y = max(1, y1); y <= min(N, y2); y++) {
            table[y-1][x-1] = color;
        }
    }

    void drawHorizontalLine(int x1, int x2, int y, char color) {
        if (!initialized || y < 1 || y > N) return;
        if (x1 > x2) swap(x1, x2);
        for (int x = max(1, x1); x <= min(M, x2); x++) {
            table[y-1][x-1] = color;
        }
    }

    void drawFilledRectangle(int x1, int y1, int x2, int y2, char color) {
        if (!initialized) return;
        if (x1 > x2) swap(x1, x2);
        if (y1 > y2) swap(y1, y2);
        
        for (int y = max(1, y1); y <= min(N, y2); y++) {
            for (int x = max(1, x1); x <= min(M, x2); x++) {
                table[y-1][x-1] = color;
            }
        }
    }

    void floodFill(int x, int y, char newColor) {
        if (!initialized || x < 1 || x > M || y < 1 || y > N) return;
        
        char originalColor = table[y-1][x-1];
        if (originalColor == newColor) return;
        
        queue<pair<int, int>> q;
        q.push({x, y});
        
        while (!q.empty()) {
            auto [cx, cy] = q.front();
            q.pop();
            
            if (cx < 1 || cx > M || cy < 1 || cy > N) continue;
            if (table[cy-1][cx-1] != originalColor) continue;
            
            table[cy-1][cx-1] = newColor;
            
            // Add adjacent pixels
            q.push({cx+1, cy});
            q.push({cx-1, cy});
            q.push({cx, cy+1});
            q.push({cx, cy-1});
        }
    }

    void saveTable(const string& filename) {
        if (!initialized) return;
        cout << filename << endl;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                cout << table[i][j];
            }
            cout << endl;
        }
    }
};

int main() {
    GraphicalEditor editor;
    string line;
    
    while (getline(cin, line)) {
        if (line.empty()) continue;
        
        istringstream iss(line);
        char command;
        iss >> command;
        
        switch (command) {
            case 'I': {
                int m, n;
                if (iss >> m >> n) {
                    editor.createTable(m, n);
                }
                break;
            }
            case 'C': {
                editor.clearTable();
                break;
            }
            case 'L': {
                int x, y;
                char color;
                if (iss >> x >> y >> color) {
                    editor.colorPixel(x, y, color);
                }
                break;
            }
            case 'V': {
                int x, y1, y2;
                char color;
                if (iss >> x >> y1 >> y2 >> color) {
                    editor.drawVerticalLine(x, y1, y2, color);
                }
                break;
            }
            case 'H': {
                int x1, x2, y;
                char color;
                if (iss >> x1 >> x2 >> y >> color) {
                    editor.drawHorizontalLine(x1, x2, y, color);
                }
                break;
            }
            case 'K': {
                int x1, y1, x2, y2;
                char color;
                if (iss >> x1 >> y1 >> x2 >> y2 >> color) {
                    editor.drawFilledRectangle(x1, y1, x2, y2, color);
                }
                break;
            }
            case 'F': {
                int x, y;
                char color;
                if (iss >> x >> y >> color) {
                    editor.floodFill(x, y, color);
                }
                break;
            }
            case 'S': {
                string filename;
                if (iss >> filename) {
                    editor.saveTable(filename);
                }
                break;
            }
            case 'X': {
                return 0;
            }
            default: {
                // Invalid command, ignore
                break;
            }
        }
    }
    
    return 0;
}