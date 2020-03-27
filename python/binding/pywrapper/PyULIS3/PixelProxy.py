import sys, os
sys.path.append( os.path.dirname(__file__) )
import _PyULIS3
from Types          import *
import AbstractPixel

class FPixelProxy( _PyULIS3._PyULIS3Type_PixelProxy, AbstractPixel._IAbstractPixel ):
    def __init__( self ): pass
