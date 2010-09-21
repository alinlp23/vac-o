"""
"""
from CombinatoryRegion import CombinatoryRegion
from SequenceMutator import SequenceMutator
import random
from Vienna import *

class SSRegion(CombinatoryRegion):

    def __init__(self, start, end, vaccine_structure, wt_structure, max_mutations, max_similitude, \
                    wt_inverse_cache=0, min_distance=0):
                    
        super(SSRegion, self).__init__(start, end)
        
        self.vaccine_structure = vaccine_structure
        self.wildtype_structure = wt_structure
        
        self.inverse_fold = InverseFoldIterator(vaccine_structure)

        self.max_mutations = max_mutations        
        #se podria tomar como maxima similitud la que ya exista entre la
        #estructura de la cepa vacunal con la estructura de la wildtype.
        self.max_similitude = max_similitude
        self.wt_inverse_cache = wt_inverse_cache
        self.min_distance = min_distance
        
        self.reset()
        
    def reset(self):
        #Construye algun numero de secuencias que tienen la estructura
        #de la wildtype       
        self.wt_cache = []
        ifi = InverseFoldIterator(self.wildtype_structure)
        for i in range(self.wt_inverse_cache):
            self.wt_cache.append(ifi.next())
            
        self.__empty = self.next()        

    def empty(self):
        return self.__empty

    def current(self):
        seq = self.base_sequence[:self.start]+self.__current+self.base_sequence[self.end:]
        return seq, self.evaluate(self.__current)        
    
    def compare_with_cache(self, seq):
        #Debe comparar seq con todas las secuencias en self.wt_cache
        #y chequear que ninguna este a menor distancia que self.min_distance
        #for s in self.wt_cache:
        #    if hamming(seq, s) <= self.min_distance:
        #        return False
        # return True
        r = random.random()
        return r < 0.9
        
    def next(self):
        fail = True
        while(fail):            
            seq = self.inverse_fold.next()
            if self.compare_with_cache(seq):
                #Si pasa el filtro de comparacion con el cache
                            
                #Se inicializa un mutator para la secuencia que devolvio el folding inverso.
                mutator = SequenceMutator(seq, self.max_mutations)       
                done = False
                fail = False
                while(not done):
                    #Se hace el folding de una mutacion
                    mseq_structure = fold(mutator.current())
                    #Se compara la estructura secundaria de la mutacion con la estructurea del wildtype
                    similitude = compare_secondary_structure(self.wildtype_structure, mseq_structure)
                    
                    if similitude > self.max_similitude:
                        #Si se pasa el umbral permitido de similitud, no se buscan mas mutaciones
                        #y se busca otra secuencia haciendo otro folding inverso.
                        done = True
                        fail = True 
                    else:
                        done = mutator.next()                
        
        self.__current = seq[self.start:self.end]
        return False
