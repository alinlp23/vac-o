
from itertools import product
from CombinatoryRegion import CombinatoryRegion
from SequenceMutator import SequenceMutator
from Vienna import *

class GCRegion(CombinatoryRegion):
    
    def __init__(self, vaccine, wildtype, start, end):
        super(GCRegion, self).__init__(vaccine, wildtype, start, end)
        
        #Que deberia pasar cuando hay un Codon de 'Stop' en entre 'start' y 'end'
        #o cuando end-start no es multiplo de 3
        self.wildtype_aminoacids = aminoacids(self.wildtype[start:end])
        
        self.__triplets = list(product(*[triplets(amino) for amino in self.wildtype_aminoacids]))
        self.reset()
        
    def reset(self):
        self.__index = 0                

    def empty(self):
        return self.__triplets == []
    
    def current(self):
        return ''.join(self.__triplets[self.__index])
        
    def next(self):
        self.__index += 1
        return self.__index == len(self.__triplets)
