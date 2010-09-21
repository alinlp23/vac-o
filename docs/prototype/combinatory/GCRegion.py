
from itertools import product
from CombinatoryRegion import CombinatoryRegion
from SequenceMutator import SequenceMutator
from Vienna import *

class GCRegion(CombinatoryRegion):
    
    def __init__(self, start, end, target_aminoacids):
        super(GCRegion, self).__init__(start, end)
        
        self.wildtype_aminoacids = target_aminoacids
        
        self.__triplets = list(product(*[triplets(amino) for amino in self.wildtype_aminoacids]))
        self.reset()
        
    def reset(self):
        self.__index = 0                

    def empty(self):
        return self.__triplets == []
    
    def current(self):
        seq = self.base_sequence[:self.start]+''.join(self.__triplets[self.__index])+self.base_sequence[self.end:]
        return seq, self.evaluate(''.join(self.__triplets[self.__index]))
        
    def next(self):
        self.__index += 1
        return self.__index == len(self.__triplets)
