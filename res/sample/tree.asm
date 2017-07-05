;;;;;;;;;; Palette
	.globl _tree_pal
_tree_pal:
	dc.w	$000
	dc.w	$06a
	dc.w	$048
	dc.w	$004
	dc.w	$4ae
	dc.w	$08a
	dc.w	$006
	dc.w	$000
	dc.w	$000
	dc.w	$000
	dc.w	$000
	dc.w	$000
	dc.w	$000
	dc.w	$000
	dc.w	$000
	dc.w	$000

;;;;;;;;;; Tiles

	.globl _tree_HSize
_tree_HSize:	dc.w	$B

	.globl _tree_VSize
_tree_VSize:	dc.w	$3

	.globl _tree
_tree:
; Compressed
	INCBIN "tree.cmp"
