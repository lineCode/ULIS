tp = [ "uint8", "uint16", "uint32", "float", "double" ]
cm = [ "G", "RGB", "HSL", "HSV", "CMYK", "YUV", "Lab", "XYZ" ]
ea = [ "hasAlpha", "noAlpha" ]
nm = [ "normalized", "typeLimits" ]

variants =	{
	( "G", "noAlpha"	) 	: [ "G" ],
	( "G", "hasAlpha"	) 	: [ "GA", "AG" ],
	( "RGB", "noAlpha" 	) 	: [ "RGB", "BGR" ],
	( "RGB", "hasAlpha" ) 	: [ "ARGB", "ABGR", "RGBA", "BGRA" ],
	( "HSL", "noAlpha" 	) 	: [ "HSL" ],
	( "HSL", "hasAlpha" ) 	: [ "HSLA", "AHSL" ],
	( "HSV", "noAlpha" 	) 	: [ "HSV" ],
	( "HSV", "hasAlpha" ) 	: [ "HSVA", "AHSV" ],
	( "CMYK", "noAlpha" ) 	: [ "CMYK", "KCMY" ],
	( "CMYK", "hasAlpha") 	: [ "CMYKA", "KCMYA", "ACMYK", "AKCMY" ],
	( "YUV", "noAlpha" 	) 	: [ "YUV" ],
	( "YUV", "hasAlpha" ) 	: [ "YUVA", "AYUV" ],
	( "Lab", "noAlpha" 	) 	: [ "Lab" ],
	( "Lab", "hasAlpha" ) 	: [ "LabA", "ALab" ],
	( "XYZ", "noAlpha" 	) 	: [ "XYZ" ],
	( "XYZ", "hasAlpha" ) 	: [ "XYZA", "AXYZ" ],
}

def is_decimal( iType ):
	return  iType == "float" or iType == "double"

for icm in cm:
	for itp in tp: 
		for iea in ea:
			for inm in nm:
				if( not is_decimal( itp ) and inm == "normalized" ):
					continue
					
				var = ( icm, iea )
				for ivar in variants[var]:
					print( "ULIS_DECLSPEC(" + itp + "," + icm + "," + iea + "," + ivar + "," + inm + ")" )