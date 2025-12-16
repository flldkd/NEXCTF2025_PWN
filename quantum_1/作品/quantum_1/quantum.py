from qiskit import QuantumCircuit
from qiskit_aer import Aer
from math import pi  

def solve() -> QuantumCircuit:
    qc = QuantumCircuit(1)
    
    qc.p(pi, 0)   # 给量子态加全局相位 π → 得到 -|0>
    return qc
