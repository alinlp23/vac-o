import unittest
import doctest
from combinatory import CombinatoryEngine, CombinatoryRegion, Vienna, SSRegion, SequenceMutator

suite = unittest.TestSuite()
for mod in CombinatoryEngine, CombinatoryRegion, Vienna, SSRegion, SequenceMutator:
    suite.addTest(doctest.DocTestSuite(mod))
    
runner = unittest.TextTestRunner()
runner.run(suite)

