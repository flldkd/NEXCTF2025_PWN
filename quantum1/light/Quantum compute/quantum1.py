from qiskit import QuantumCircuit
from qiskit_aer import Aer

def solve(n: int) -> QuantumCircuit:
    qc = QuantumCircuit(n)
    # 在第 0 个量子比特上施加 H 门：|0> -> |+>
    qc.h(0)
    return qc
