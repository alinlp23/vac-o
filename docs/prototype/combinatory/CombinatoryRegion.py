"""
"""
import random
class CombinatoryRegion(object):

    def __init__(self, start, end):
        super(CombinatoryRegion, self).__init__()

        self.start = start
        self.end = end
        
    def set_base_sequence(self, sequence):
        self.base_sequence = sequence
        
    def reset(self):
        raise NotImplemented
        
    def empty(self):
        raise NotImplemented        
    
    def current(self):
        raise NotImplemented
        
    def next(self):
        raise NotImplemented
        
    def evaluate(self, seq):
        return random.random()                
    
