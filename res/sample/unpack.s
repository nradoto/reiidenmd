;----------------------------------------------------------------------------
; unpack.inc
; VRAM data decompression routine
;
; by Charles MacDonald
; WWW: http://cgfm2.emuviews.com
; modified for SGCC by Kaneda
;----------------------------------------------------------------------------

; C call :
; 	unpack(ulong compressed_data_adr, ulong destination_adr, uint size_of_compressed_data)
; 
; Example :
;	unpack(myCmp, GFX_WRITE_ADDR(32*4), 45)
;	decompress myCmp (45 bytes) at tile 4
;
; Parameters:
;	8(a6) : ulong compressed_data_adr
;	12(a6): ulong destination_adr
;	16(a6): uint size_of_compressed_data
;
; Input parameters:
; d4 = Data size minus one (saved)
; a4 = Compressed data (not saved)
;
; Register use:
; d0 = Compressed bytes / data
; d1 = Run length counter
; d2 = Shift count
; d3 = Pixel buffer
; a0 = VDP data port
;
	.globl _unpack
_unpack:
			link	a6,#0
			movem.l  d0-d7/a0-a4,-(sp)
			move.l	8(a6),a4
			move.w  16(a6),d4

			move.l	#$C00004,a1
			move.l  12(a6),(a1)
                        move.l  #$C00000, a0
                        move.l  #28, d2
                        moveq   #0, d3
        unpack_next:    moveq   #0, d0
                        move.b  (a4)+, d0
                        move.l  d0, d1
                        lsr.b   #4, d1
                        andi.b  #$0F, d1
                        andi.b  #$0F, d0
        unpack_run:     lsl.l   d2, d0
                        or.l    d0, d3         
                        lsr.l   d2, d0
                        subq.b  #4, d2
                        bpl     unpack_skip
                        move.l  d3, (a0)
                        moveq   #0, d3
                        move.b  #28, d2
        unpack_skip:    dbra    d1, unpack_run
                        dbra    d4, unpack_next 
        		movem.l  (sp)+,d0-d7/a0-a4
                        unlk	a6   
			rts
