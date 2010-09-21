from combinatory.CombinatoryEngine import CombinatoryEngine
from combinatory.SSRegion import SSRegion
from combinatory.GCRegion import GCRegion
from combinatory.Vienna import *

if __name__ == "__main__":
    wildtype = random_sequence(20)
    vaccine = random_sequence(20)

    engine = CombinatoryEngine()
    
    max_muta = 2
    max_sim = 0.995
    start = 0
    end = 8
    ssregion = SSRegion(start, end, fold(vaccine), fold(wildtype), max_muta, max_sim)
    
    start = 10
    end = 13
    gcregion = GCRegion(start, end, aminoacids(vaccine[start:end]))

    engine.set_sequence(vaccine)
    engine.set_cutoff(0.5)
    

    if not ssregion.empty():  
        print "added r1"  
        engine.add_region(ssregion)
    else:
        #Probar:
        # -Aumentando el numero maximo de iteraciones 
        # -Bajando el numero maximo de mutaciones
        # -Aumentar el maximo de similitud
        # -Volver a correr y quizas el random juega a favor
        print "Nada para hacer con la region de estructura secundaria." 
    
    if not gcregion.empty():
        print "added r2"  
        engine.add_region(gcregion)
    print vaccine
    print "running..."
    engine.run()
        
