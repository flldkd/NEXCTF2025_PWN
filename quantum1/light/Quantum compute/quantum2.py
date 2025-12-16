from qiskit import QuantumCircuit
from qiskit_aer import Aer


def solve(n: int) -> QuantumCircuit:
    qc = QuantumCircuit(n)
    # Write your code here:
    # 对每个量子比特施加一个 Hadamard 门
    for i in range(n):
        qc.h(i)
    return qc
