import sys, os
sys.path.append( os.path.dirname(__file__) )
import _PyULIS3
from Types          import *
import AbstractPixel

class FPixelValue( AbstractPixel._IAbstractPixel, _PyULIS3._PyULIS3Type_PixelValue ):
    def __init__( self ):
        super( FPixelValue, self ).__init__()