;;;;;;;;;; Palette
	.globl _back_pal
_back_pal:
	dc.w	$004
	dc.w	$0a0
	dc.w	$060
	dc.w	$792
	dc.w	$0e0
	dc.w	$00e
	dc.w	$848
	dc.w	$400
	dc.w	$048
	dc.w	$cee
	dc.w	$08e
	dc.w	$0ce
	dc.w	$e80
	dc.w	$46a
	dc.w	$0ee
	dc.w	$006

;;;;;;;;;; Optimized Map
	.globl _back_omap_HSize
_back_omap_HSize:
	dc.w	$20

	.globl _back_omap_VSize
_back_omap_VSize:
	dc.w	$1C

	.globl _back_omap
_back_omap:
	INCBIN "back_omap.bin"

;;;;;;;;;; Tiles for optimized map
	.globl _back_Number
_back_Number:
	dc.w	$73

	.globl _back
_back:
; Uncompressed
	INCBIN "back.cmp"


