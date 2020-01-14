.include "hdr.asm"

.section ".rodata1" superfree



tiles:
.incbin "board.pic"
tiles_end:

map:
.incbin "board.map"
map_end:

pal:
.incbin "board.pal"
pal_end:



.ends
