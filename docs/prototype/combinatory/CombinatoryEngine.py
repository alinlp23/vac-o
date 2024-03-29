"""
"""
class _CombinatoryEngine(object):

    def __init__(self):        
        super(_CombinatoryEngine, self).__init__()        
        
        self.regions = []
        
    def run(self):
        self.__product(self.regions, self.sequence)

    def __product(self, regions, seq, score=1):
        """
        Producto cartesiano de regiones con score y cutoff.
        """
        if len(regions) == 0:
            #No hay mas regiones, se muestra el producto y el score
            #Aca se dispararia un evento para avisar que hay una nueva
            #secuencia candidata para ser sometida a QA y despues rankeada.
            print seq, score
        else:
            r = regions[0]
            r.set_base_sequence(seq)
            done = False
            while(not done):
                #Mientras la region tenga secuencias para analizar
                s, lscore = r.current()
                
                #Evaluacion local de la region multiplicado por el score acumulado
                partial_score = lscore*score
                
                if partial_score > self.cutoff:
                    #Se sigue calculando el producto cartesiano, con la secuencia
                    #'s' incluida y el score actualizado
                    self.__product(regions[1:], s, partial_score)
                    
                done = r.next()

            r.reset()
                    
    def set_sequence(self, sequence):
        self.sequence = sequence
        
    def set_cutoff(self, cutoff):
        self.cutoff = cutoff
    
    def add_region(self, region):
        self.regions.append(region)

_combinatoryengine = _CombinatoryEngine()

def CombinatoryEngine(): 
    return _combinatoryengine
