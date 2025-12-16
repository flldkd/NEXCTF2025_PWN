import re
from z3 import *
from pwn import *

def parse_sudoku_string(sudoku_str):
    """解析数独字符串，将点替换为0，返回9x9网格"""
    lines = sudoku_str.strip().split('\n')
    grid = []

    for line in lines:
        # 只处理包含数字或点的行（跳过边框行）
        if '│' in line:
            # 提取单元格内容（去除边框和空格）
            cells = re.findall(r'[.0-9]', line)
            if len(cells) == 9:  # 确保是数据行
                row = []
                for cell in cells:
                    if cell == '.':
                        row.append(0)
                    else:
                        row.append(int(cell))
                grid.append(row)

    return grid


def solve_sudoku(grid):
    """使用z3求解数独"""
    # 创建9x9整数变量矩阵
    X = [[Int(f"x_{i}_{j}") for j in range(9)] for i in range(9)]

    # 创建求解器
    s = Solver()

    # 添加约束：每个单元格的值在1-9之间
    cells_c = [And(1 <= X[i][j], X[i][j] <= 9) for i in range(9) for j in range(9)]
    s.add(cells_c)

    # 添加约束：每行数字不重复
    rows_c = [Distinct(X[i]) for i in range(9)]
    s.add(rows_c)

    # 添加约束：每列数字不重复
    cols_c = [Distinct([X[i][j] for i in range(9)]) for j in range(9)]
    s.add(cols_c)

    # 添加约束：每个3x3宫数字不重复
    for i in range(0, 9, 3):
        for j in range(0, 9, 3):
            square_c = Distinct(
                [X[i + di][j + dj] for di in range(3) for dj in range(3)]
            )
            s.add(square_c)

    # 添加已知数字的约束
    for i in range(9):
        for j in range(9):
            if grid[i][j] != 0:
                s.add(X[i][j] == grid[i][j])

    # 求解
    if s.check() == sat:
        m = s.model()
        solution = [[m.evaluate(X[i][j]).as_long() for j in range(9)] for i in range(9)]
        return solution
    else:
        return None

def grid_to_81_digits(grid):
    """将9x9网格转换为81个数字的字符串"""
    return ''.join(str(num) for row in grid for num in row)


if __name__ == '__main__':
    # p = process("./sudoku_1")
    p = remote('219.216.65.41', 38294)
    p.recvuntil('数独题目 (0表示空格):\n'.encode())
    sudoku_str = p.recvuntil('┘'.encode()).decode()
    print(sudoku_str)
    grid = parse_sudoku_string(sudoku_str)
    solution = solve_sudoku(grid)
    if not solution:
        print("未找到解")
        exit(1)
    digits = grid_to_81_digits(solution)
    print(f"81个数字的解: {digits}")
    p.sendlineafter(b':', digits)
    print(p.recvall().decode())
    p.interactive()


