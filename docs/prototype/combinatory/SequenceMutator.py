"""
"""
import itertools
BASES = ['A','U','C','G']

class SingleMutator(object):
    def __init__(self, sequence, index):
        super(SingleMutator, self).__init__()
        
        self.sequence = sequence        
        self.index = index
        
        self.reset()

    def reset(self):
        self.__mutated = [self.sequence[self.index]]
        self.current_base = filter(lambda x: x not in self.__mutated, BASES)[0]
        
    def next(self):
        self.__mutated.append(self.current_base)
        bases = filter(lambda x: x not in self.__mutated, BASES)
        if bases:
            self.current_base = bases[0]
            return False
        else:
            self.reset()
            return True
        
    def current(self):
        mutation = self.sequence[:self.index]+self.current_base+self.sequence[self.index+1:]
        return mutation
        
class NestedMutator(SingleMutator):
    def __init__(self, sequence, index, nested_indexes):
        super(NestedMutator, self).__init__(sequence, index)
        
        if len(nested_indexes) == 1:
            self.nested = SingleMutator(sequence, nested_indexes[0])
        else:
            self.nested = NestedMutator(sequence, nested_indexes[0], nested_indexes[1:])
        
    def next(self):
        done = self.nested.next()
        if done:
            done = super(NestedMutator, self).next()
            
        return done
            
    def current(self):
        sequence = self.nested.current()
        mutation = sequence[:self.index]+self.current_base+sequence[self.index+1:]
        return mutation
        
class SequenceMutator(object):
    def __init__(self, sequence, max_mutations):
        super(SequenceMutator, self).__init__()
        
        self.sequence = sequence
        self.max_mutations = max_mutations
        
        self.__mutations = 1
        self.reset_indexes()
        self.reset_mutator()             
        
    def next(self):
        done = self.__mutator.next()
        if done:
            done = False
            self.__index = self.__index + 1
            if self.__index == len(self.__indexes):
                self.__mutations = self.__mutations + 1
                if self.__mutations > self.max_mutations:
                    self.__mutations = 1
                    done = True
                    
                self.reset_indexes()
                
            self.reset_mutator()
            
        return done 
        
    def current(self):
        return self.__mutator.current()

    def reset_indexes(self):
        self.__index = 0
        self.__indexes = [list(i) 
                          for i in itertools.combinations(range(len(self.sequence)), self.__mutations)]
        
    def reset_mutator(self):
        if self.__mutations == 1:
            self.__mutator = SingleMutator(self.sequence, self.__indexes[self.__index][0])
        else:    
            indexes = self.__indexes[self.__index]
            self.__mutator = NestedMutator(self.sequence, indexes[0], indexes[1:])
            
