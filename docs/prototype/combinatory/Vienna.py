"""
"""

import random
BASES = "AUCG"
BRACK = "()."

GC = [
    ('UUU', 'F'),('UUC', 'F'),('UUA', 'L'), ('UUG', 'L'),
    ('CUU', 'L'), ('CUC', 'L'), ('CUA', 'L'), ('CUG', 'L'),
    ('AUU', 'I'), ('AUC', 'L'), ('AUA', 'L'), ('AUG', 'M'),
    ('GUU', 'V'), ('GUC', 'V'), ('GUA', 'V'), ('GUG', 'V'),
    ('UCU', 'S'), ('UCC', 'S'), ('UCA', 'S'), ('UCG', 'S'),    
    ('CCU', 'P'), ('CCC', 'P'), ('CCA', 'P'), ('CCG', 'P'),    
    ('ACU', 'T'), ('ACC', 'T'), ('ACA', 'T'), ('ACG', 'T'),
    ('GCU', 'A'), ('GCC', 'A'), ('GCA', 'A'), ('GCG', 'A'),
    ('UAU', 'Y'), ('UAC', 'Y'), ('UAA', 'Stop'), ('UAG', 'Stop'),    
    ('CAU', 'H'), ('CAC', 'H'), ('CAA', 'Q'), ('CAG', 'Q'),
    ('AAU', 'N'), ('AAC', 'N'), ('AAA', 'K'), ('AAG', 'K'),    
    ('GAU', 'D'), ('GAC', 'D'), ('GAA', 'E'), ('GAG', 'E'),    
    ('UGU', 'C'), ('UGC', 'C'), ('UGA', 'Stop'), ('UGG', 'W'),
    ('CGU', 'R'), ('CGC', 'R'), ('CGA', 'R'), ('CGG', 'R'),
    ('AGU', 'S'), ('AGC', 'S'), ('AGA', 'R'), ('AGG', 'R'),
    ('GGU', 'G'), ('GGC', 'G'), ('GGA', 'G'), ('GGG', 'G')
]

def random_sequence(seq_len):
    return ''.join(random.choice(BASES) for i in range(seq_len))

def triplets(aminoacid):
    return [t for t,a in GC if a==aminoacid]
    
def aminoacids(seq):
    search = [(t,a) for t,a in GC if t==seq[:3]]
    t = search[0][0]
    a = search[0][1]    
    if a != 'Stop':
        if seq[3:]:
            return a + aminoacids(seq[3:])
        else:
            return a
    else:
        return ''
    
def compare_secondary_structure(seq1, seq2):
    return random.random()
    
def random_structure(seq_len):
    i = 0
    j = seq_len - 1
    structure = ''.join('.' for k in range(seq_len))
    while(i<j):
        c = random.random()
        if c < 0.5:
            structure = structure[:i] + '(' + structure[i+1:j] + ')' + structure[j+1:]
        i = i+1
        j = j-1
            
    return structure
    
def inverse_fold(structure):
    return random_sequence(len(structure))
    
def fold(sequence):
    return random_structure(len(sequence))

