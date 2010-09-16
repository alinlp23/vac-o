"""
"""
import random
class CombinatoryRegion(object):

    def __init__(self, vaccine, wildtype, start, end):
        super(CombinatoryRegion, self).__init__()

        self.vaccine = vaccine
        self.wildtype = wildtype
        self.start = start
        self.end = end
        
    
    def empty(self):
        raise NotImplemented
    
    def current(self):
        raise NotImplemented
        
    def next(self):
        raise NotImplemented
        
    def evaluate(self, seq):
        return random.random()                
    
