from combinatory.CombinatoryEngine import CombinatoryEngine
from combinatory.SSRegion import SSRegion
from combinatory.Vienna import random_sequence

if __name__ == "__main__":
    wildtype = random_sequence(20)
    vaccine = random_sequence(20)
    engine = CombinatoryEngine()
    
    max_iter = 1000
    max_muta = 2
    max_sim = 0.98
    start = 0
    end = 8
    ssregion_1 = SSRegion(vaccine, wildtype, start, end, max_iter, max_muta, max_sim)
    if not ssregion_1.empty():
        engine.set_sequence(vaccine)
        engine.set_cutoff(0.3)
        engine.add_region(ssregion_1)

        print "running..."
        engine.run()

    else:
        #Probar:
        # -Aumentando el numero maximo de iteraciones 
        # -Bajando el numero maximo de mutaciones
        # -Aumentar el maximo de similitud
        # -Volver a correr y quizas el random juega a favor
        print "Nada para hacer." 
        
