"""
  >>> m = mutations(random_sequence(10))
"""

import random
BASES = "AUCG"
BRACK = "()."

def random_sequence(seq_len):
    return ''.join(random.choice(BASES) for i in range(seq_len))
    
def mutations(sequence):
    return [random_sequence(len(sequence)) for j in range(random.randint(1, 10))]
    
def compare_secondary_structure(seq1, seq2):
    return random.random()
    
def random_structure(seq_len):
    i = 0
    j = seq_len - 1
    structure = ''.join('.' for k in range(seq_len))
    while(i<j):
        c = random.random()
        if c<0.5:
            structure = structure[:i] + '(' + structure[i+1:j] + ')' + structure[j+1:]
        i = i+1
        j = j-1
            
    return structure
    
def inverse_fold(structure):
    return random_sequence(len(structure))
    
def fold(sequence):
    return random_structure(len(sequence))

