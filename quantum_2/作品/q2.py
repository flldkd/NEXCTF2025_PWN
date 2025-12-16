from qiskit import QuantumCircuit
from qiskit_aer import Aer

def solve() -> QuantumCircuit:
    qc = QuantumCircuit(2)
    # Write your code here:
    qc.h(0)
    qc.cx(0, 1)
    return qc
