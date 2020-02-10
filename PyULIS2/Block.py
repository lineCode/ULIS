import sys, os
sys.path.append( os.path.dirname(__file__) )
import _PyULIS2
from Types      import *

class FBlock:
    def __init__( self, width, height, format ): self._data = _PyULIS2._PyULIS2Type_Block( width, height, format )
    def Width               (self): return  self._data.Width()
    def Height              (self): return  self._data.Height()
    def Format              (self): return  self._data.Format()
    def BytesPerSample      (self): return  self._data.BytesPerSample()
    def BytesPerPixel       (self): return  self._data.BytesPerPixel()
    def BytesPerScanLine    (self): return  self._data.BytesPerScanLine()
    def BytesTotal          (self): return  self._data.BytesTotal()
    def Model               (self): return  self._data.Model()
    def Type                (self): return  self._data.Type()
    def HasAlpha            (self): return  self._data.HasAlpha()
    def Swapped             (self): return  self._data.Swapped()
    def Reversed            (self): return  self._data.Reversed()
    def SamplesPerPixel     (self): return  self._data.SamplesPerPixel()
    def NumColorChannels    (self): return  self._data.NumColorChannels()
    def AlphaIndex          (self): return  self._data.AlphaIndex()
    def CRC32               (self): return  self._data.CRC32()
    def MD5                 (self): return  self._data.MD5()
    def UUID                (self): return  self._data.UUID()
    def TypeStr             (self): return  kwType[ self.Type() ]
    def ModelStr            (self): return  kwColorModel[ self.Model() ]