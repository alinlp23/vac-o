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
        
        self.reset()
        
    def reset(self):
        #pensar que pasa con el inverse folding. En sucesivas
        #iteraciones sobre las secuencias de la region daria distintas secuencias.
        self.__iter = 0
        self.__empty = self.next()

    def empty(self):
        return self.__empty

    def current(self):
        return self.__current        
        
    def next(self):
        fail = True
        while(fail and self.__iter < self.max_iterations):
            self.__iter += 1
            
            #Se calcula el folding inverso. Aca tambien se le pasaria una
            #secuencia random. Ver que pasa con el reset y esto.
            seq = inverse_fold(self.vaccine_structure)
            
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
        
        if self.__iter >= self.max_iterations:
            #Si se alcanzo el maximo de iteraciones, no hay mas sequencias/
            done = True
        else:
            #Termino el while por fail=False. Es decir que se encontro una secuencia.
            self.__current = seq
            done = False

        return done
