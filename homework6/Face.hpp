#include <vector>

using namespace std;

class Face {
private:
    vector<vector<char>> face;
public:
    explicit Face(char color) {
        vector<char> row;
        row.reserve(3);
        for (int i = 0; i < 3; i++)
            row.emplace_back(color);
        for (int j = 0; j < 3; j++) {
            face.push_back(row);
        }
    }

    vector<char> &operator[](int i) {
        return face[i];
    }
};

