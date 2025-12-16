#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <string>
#include <vector>

using namespace std;

class Sudoku {
private:
    vector<vector<int>> board; // 数独棋盘
    vector<vector<int>> solution; // 完整解
    vector<vector<bool>> fixed; // 固定位置（题目给出的数字）

    // 检查在(row, col)位置填入num是否合法
    bool isValid(int row, int col, int num)
    {
        // 检查行
        for (int i = 0; i < 9; i++) {
            if (board[row][i] == num)
                return false;
        }

        // 检查列
        for (int i = 0; i < 9; i++) {
            if (board[i][col] == num)
                return false;
        }

        // 检查3x3宫格
        int startRow = row - row % 3;
        int startCol = col - col % 3;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[startRow + i][startCol + j] == num)
                    return false;
            }
        }

        return true;
    }

    // 回溯法求解数独
    bool solveSudoku()
    {
        for (int row = 0; row < 9; row++) {
            for (int col = 0; col < 9; col++) {
                if (board[row][col] == 0) {
                    // 尝试1-9的数字
                    for (int num = 1; num <= 9; num++) {
                        if (isValid(row, col, num)) {
                            board[row][col] = num;

                            if (solveSudoku()) {
                                return true;
                            }

                            board[row][col] = 0; // 回溯
                        }
                    }
                    return false; // 无解
                }
            }
        }
        return true; // 所有格子都填满
    }

    // 生成完整的数独
    void generateCompleteSudoku()
    {
        board = vector<vector<int>>(9, vector<int>(9, 0));

        // 先填充对角线上的3个3x3宫格（它们相互独立）
        for (int box = 0; box < 3; box++) {
            vector<int> nums = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
            unsigned seed = chrono::system_clock::now().time_since_epoch().count();
            shuffle(nums.begin(), nums.end(), default_random_engine(seed));

            int index = 0;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    int row = box * 3 + i;
                    int col = box * 3 + j;
                    board[row][col] = nums[index++];
                }
            }
        }

        // 解数独得到完整棋盘
        solveSudoku();
        solution = board; // 保存完整解
    }

    // 挖空生成题目
    void digHoles()
    {
        fixed = vector<vector<bool>>(9, vector<bool>(9, true));

        // 随机决定挖空数量（40-50之间）
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(40, 50);
        int holes = dis(gen);

        cout << "本次数独题目挖空数量: " << holes << " 个" << endl;

        // 随机挖空
        int holesCreated = 0;
        while (holesCreated < holes) {
            int row = gen() % 9;
            int col = gen() % 9;

            if (fixed[row][col]) { // 如果这个位置还没有被挖空
                // 保存当前值（用于恢复）
                int temp = board[row][col];
                board[row][col] = 0;
                fixed[row][col] = false;

                // 检查挖空后是否仍然有解
                vector<vector<int>> tempBoard = board;
                if (solveSudoku()) {
                    holesCreated++;
                    board = tempBoard; // 恢复挖空状态
                } else {
                    // 无解，恢复这个位置
                    board[row][col] = temp;
                    fixed[row][col] = true;
                }
            }
        }
    }

public:
    Sudoku()
    {
        generateCompleteSudoku();
        digHoles();
    }

    // 显示数独棋盘
    void display()
    {
        cout << "数独题目 (0表示空格):" << endl;
        cout << "┌───────┬───────┬───────┐" << endl;
        for (int i = 0; i < 9; i++) {
            if (i == 3 || i == 6) {
                cout << "├───────┼───────┼───────┤" << endl;
            }
            cout << "│ ";
            for (int j = 0; j < 9; j++) {
                if (board[i][j] == 0) {
                    cout << ". ";
                } else {
                    cout << board[i][j] << " ";
                }
                if (j == 2 || j == 5) {
                    cout << "│ ";
                }
            }
            cout << "│" << endl;
        }
        cout << "└───────┴───────┴───────┘" << endl;
    }

    // 从81个连续数字字符串创建用户棋盘
    vector<vector<int>> createUserBoardFromString(const string& input)
    {
        vector<vector<int>> userBoard(9, vector<int>(9));
        int index = 0;

        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (index < input.length()) {
                    userBoard[i][j] = input[index] - '0'; // 将字符转换为数字
                    index++;
                } else {
                    userBoard[i][j] = 0; // 如果输入不足81个字符，剩余位置填0
                }
            }
        }

        return userBoard;
    }

    // 验证用户输入
    bool validateUserInput(const vector<vector<int>>& userBoard)
    {
        // 检查固定位置是否正确
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (fixed[i][j] && userBoard[i][j] != solution[i][j]) {
                    cout << "错误：位置(" << i + 1 << "," << j + 1 << ")应该是"
                         << solution[i][j] << "，但您输入了" << userBoard[i][j] << endl;
                    return false;
                }
            }
        }

        // 检查行
        for (int i = 0; i < 9; i++) {
            vector<bool> used(10, false);
            for (int j = 0; j < 9; j++) {
                int num = userBoard[i][j];
                if (num < 0 || num > 9) {
                    cout << "错误：位置(" << i + 1 << "," << j + 1 << ")的数字" << num << "无效" << endl;
                    return false;
                }
                if (num != 0 && used[num]) {
                    cout << "错误：第" << i + 1 << "行数字" << num << "重复" << endl;
                    return false;
                }
                if (num != 0)
                    used[num] = true;
            }
        }

        // 检查列
        for (int j = 0; j < 9; j++) {
            vector<bool> used(10, false);
            for (int i = 0; i < 9; i++) {
                int num = userBoard[i][j];
                if (num != 0 && used[num]) {
                    cout << "错误：第" << j + 1 << "列数字" << num << "重复" << endl;
                    return false;
                }
                if (num != 0)
                    used[num] = true;
            }
        }

        // 检查3x3宫格
        for (int boxRow = 0; boxRow < 3; boxRow++) {
            for (int boxCol = 0; boxCol < 3; boxCol++) {
                vector<bool> used(10, false);
                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 3; j++) {
                        int row = boxRow * 3 + i;
                        int col = boxCol * 3 + j;
                        int num = userBoard[row][col];
                        if (num != 0 && used[num]) {
                            cout << "错误：第" << boxRow + 1 << "宫格数字" << num << "重复" << endl;
                            return false;
                        }
                        if (num != 0)
                            used[num] = true;
                    }
                }
            }
        }

        return true;
    }

    // 获取当前棋盘（用于显示题目）
    vector<vector<int>> getBoard() const
    {
        return board;
    }

    // 获取固定位置信息
    vector<vector<bool>> getFixedPositions() const
    {
        return fixed;
    }

    // 显示完整解（用于调试）
    void displaySolution()
    {
        cout << "完整解:" << endl;
        cout << "┌───────┬───────┬───────┐" << endl;
        for (int i = 0; i < 9; i++) {
            if (i == 3 || i == 6) {
                cout << "├───────┼───────┼───────┤" << endl;
            }
            cout << "│ ";
            for (int j = 0; j < 9; j++) {
                cout << solution[i][j] << " ";
                if (j == 2 || j == 5) {
                    cout << "│ ";
                }
            }
            cout << "│" << endl;
        }
        cout << "└───────┴───────┴───────┘" << endl;
    }
};

int main()
{
    cout << "=== 数独游戏 ===" << endl;

    // 生成数独题目
    Sudoku sudoku;
    sudoku.display();

    // 获取用户输入
    cout << "\n请一次性连续输入81个数字（不需要空格或换行分隔）:" << endl;
    // cout << "提示: 对于空格，请输入0" << endl;

    string userInput;
    cin >> userInput;

    // 检查输入长度
    if (userInput.length() != 81) {
        cout << "错误：请输入 exactly 81 个数字！您输入了 " << userInput.length() << " 个字符。" << endl;
        return 1;
    }

    // 检查输入是否都是数字
    for (char c : userInput) {
        if (c < '1' || c > '9') {
            cout << "错误：输入包含非数字字符！" << endl;
            return 1;
        }
    }

    // 创建用户棋盘
    vector<vector<int>> userBoard = sudoku.createUserBoardFromString(userInput);

    // 验证用户输入
    cout << "\n验证结果:" << endl;
    if (sudoku.validateUserInput(userBoard)) {
        cout << "恭喜！您的解答是正确的！" << endl;
        cout << "FLAG:" << endl;
        // 输出 flag，位于 /home/ctf/flag
        FILE* flag = fopen("./flag", "r");
        char buf[1024];
        while (fgets(buf, sizeof(buf), flag)) {
            cout << buf;
        }
        fclose(flag);
    } else {
        cout << "抱歉，您的解答有错误。" << endl;
        cout << "\n正确解如下:" << endl;
        sudoku.displaySolution();
    }

    return 0;
}