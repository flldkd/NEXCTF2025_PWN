from qiskit import QuantumCircuit
from qiskit_aer import Aer
from math import pi


def solve() -> QuantumCircuit:
    qc = QuantumCircuit(1)
    # Write your code here:
    qc.global_phase += pi
    return qc
