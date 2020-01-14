/*---------------------------------------------------------------------------------


Mise en mémoire d'une image dans un buffer puis l'injecter en VRAM

---------------------------------------------------------------------------------*/
#include <snes.h>
#include "../../compilateur/include/stdlib.h"
#include "../../compilateur/include/string.h"
//---------------------------------------------------------------------------------


extern char tiles,tiles_end;
extern char pal,pal_end;
extern char map, map_end;


int main(void) {

  u16 buffer_map[2048];

  // Initialize SNES 
  consoleInit();

  // Chargement tiles
  bgInitTileSet(0, &tiles, &pal, 0, (&tiles_end - &tiles), (&pal_end - &pal), BG_16COLORS, 0x4000);

  // Now Put in 16 color mode and disable Bgs except current
  setMode(BG_MODE1,0);  bgSetDisable(1);  bgSetDisable(2);

  // Copier les données Rom => RAM
  memcpy(buffer_map,&map,(&map_end - &map));

  // 1er copie en VRAM pour l'exemple
  bgInitMapSet(0,(u8*)buffer_map, (&map_end - &map),SC_32x32, 0x0000);

  // Modification en RAM pour la future map
  buffer_map[0]=0b0000000000011111;
  buffer_map[1]=01;
  buffer_map[32]=01;
  buffer_map[33]=01;

  // Copier RAm => VRAM la map
  bgInitMapSet(0,(u8*)buffer_map, (&map_end - &map),SC_32x32, 0x0000);

	// Wait for nothing :P
	setScreenOn();  


  // Boucle
	while(1) {

		WaitForVBlank(); // Attendre le VBL

	}
	return 0;
}