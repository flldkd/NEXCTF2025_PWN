from qiskit import QuantumCircuit
from qiskit_aer import Aer

def solve() -> QuantumCircuit:
    qc = QuantumCircuit(2)
    # 1. 对第一个量子比特做 Hadamard，得到 (|0> + |1>)/√2
    qc.h(0)
    # 2. 用第一个比特控制第二个比特，做 CNOT
    qc.cx(0, 1)  # control = 0, target = 1
    return qc
