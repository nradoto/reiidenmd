;;;;;;;;;; Palette
	.globl _swimmer_pal
_swimmer_pal:
	dc.w	$000
	dc.w	$0c0
	dc.w	$cc0
	dc.w	$060
	dc.w	$08e
	dc.w	$04e
	dc.w	$0ce
	dc.w	$000
	dc.w	$000
	dc.w	$000
	dc.w	$000
	dc.w	$000
	dc.w	$000
	dc.w	$000
	dc.w	$000
	dc.w	$000

;;;;;;;;;; Tile 0

	.globl _swimmer0_HSize
_swimmer0_HSize:	dc.w	$2

	.globl _swimmer0_VSize
_swimmer0_VSize:	dc.w	$4

	.globl _swimmer0
_swimmer0:
; Uncompressed
	INCBIN "swimmer0.bin"

;;;;;;;;;; Tile 1
	
	.globl _swimmer1_HSize
_swimmer1_HSize:	dc.w	$2

	.globl _swimmer1_VSize
_swimmer1_VSize:	dc.w	$4

	.globl _swimmer1
_swimmer1:
; Uncompressed
	INCBIN "swimmer1.bin"
	