"""
  >>> engine = CombinatoryEngine()
  >>> engine.regions
  []
"""
class _CombinatoryEngine(object):

    def __init__(self):        
        super(_CombinatoryEngine, self).__init__()        
        
        self.regions = []
        
    def run(self):
        self.__product(self.regions)

    def __product(self, regions, product=[], score=1):
        if len(regions) == 0:
            print product, score
        else:
            r = regions[0]
            done = False
            while(not done):
                s = r.current()                
                partial_score = r.evaluate(s)*score
                if partial_score > self.cutoff:
                    self.__product(regions[1:], product+[s], partial_score)
                    
                done = r.next()
                    
    def set_sequence(self, sequence):
        self.sequence = sequence
        
    def set_cutoff(self, cutoff):
        self.cutoff = cutoff
    
    def add_region(self, region):
        self.regions.append(region)

_combinatoryengine = _CombinatoryEngine()

def CombinatoryEngine(): 
    return _combinatoryengine               
