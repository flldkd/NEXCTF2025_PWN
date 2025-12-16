
import math

def prepare_plus_state_basic():

    amplitude_0 = 1 / math.sqrt(2)  
    amplitude_1 = 1 / math.sqrt(2)  
    
    return amplitude_0, amplitude_1

def verify_plus_state_basic():
 
    a0, a1 = prepare_plus_state_basic()
    print("|+⟩ 态的概率幅:")
    print(f"⟨0|+⟩ = {a0:.6f}")
    print(f"⟨1|+⟩ = {a1:.6f}")
    
    probability_0 = a0 * a0  
    probability_1 = a1 * a1  
    total_probability = probability_0 + probability_1
    
    print(f"验证归一化:")
    print(f"|⟨0|+⟩|² = {probability_0:.6f}")
    print(f"|⟨1|+⟩|² = {probability_1:.6f}")
    print(f"总概率 = {total_probability:.6f} ")
    
    return a0, a1

amplitude_0, amplitude_1 = verify_plus_state_basic()