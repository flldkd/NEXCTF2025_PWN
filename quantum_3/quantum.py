from qiskit import QuantumCircuit, QuantumRegister
from qiskit.quantum_info import Statevector
from qiskit_aer import Aer
from math import acos, sqrt, pi
import matplotlib.pyplot as plt
import numpy as np 
def solve(n: int) -> QuantumCircuit:
    x, y = QuantumRegister(n), QuantumRegister(1)
    qc = QuantumCircuit(x, y)
    for i in range(n):
        qc.cx(x[i],y[0])

    return qc

def int_to_binary_array(n):
    # 使用内置的bin()函数获取二进制字符串，然后去掉前缀'0b'
    binary_str = bin(n)[2:]
    # 将字符串转为数组形式
    binary_array = [int(bit) for bit in binary_str]  # 转换每个字符为整数
    return binary_array

# 示例用法
number = 10  # 例子中的整数
binary_array = int_to_binary_array(number)
print(binary_array)  # 输出: [1, 0, 1, 0]

qc= solve(2)
qc.draw('mpl')
plt.show()
sv=Statevector.from_instruction(qc)
amps = sv.data

# 3 个量子比特 → 8 维向量
n = 3
for i, a in enumerate(amps):
    # 只打印明显不为 0 的项
    if abs(a) > 1e-10:
        print(f"|{i:>0{n}b}⟩  {a:.4f}   |amp|²={abs(a)**2:.4f}")