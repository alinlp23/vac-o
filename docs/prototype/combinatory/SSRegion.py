"""
"""

from CombinatoryRegion import CombinatoryRegion
from SequenceMutator import SequenceMutator
from Vienna import *

class SSRegion(CombinatoryRegion):

    def __init__(self, vaccine, wildtype, start, end, max_iterations, max_mutations, max_similitude):
        super(SSRegion, self).__init__(vaccine, wildtype, start, end)
        
        self.wildtype_structure = fold(self.wildtype[start:end])
        self.vaccine_structure = fold(self.vaccine[start:end])
        
        self.max_iterations = max_iterations
        self.max_mutations = max_mutations
        #se podria tomar como maxima similitud la que ya exista entre la
        #estructura de la cepa vacunal con la estructura de la wildtype.
        self.max_similitude = max_similitude
        
        self.__iter = 0
        self.__empty = self.next()

    def empty(self):
        return self.__empty

    def current(self):
        return self.__current
        
    def next(self):
        fail = True
        while(fail and self.__iter < self.max_iterations):
            self.__iter = self.__iter + 1
            seq = inverse_fold(self.vaccine_structure)
            mutator = SequenceMutator(seq, self.max_mutations)       
            done = False
            fail = False
            while(not done):
                mseq_structure = fold(mutator.current())
                similitude = compare_secondary_structure(self.wildtype_structure, mseq_structure)

                if similitude > self.max_similitude:
                    done = True
                    fail = True 
                else:    
                    done = mutator.next()                

        if self.__iter >= self.max_iterations:            
            done = True
        else:
            self.__current = seq
            done = False

        return done
