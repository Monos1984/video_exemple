@echo off



echo ================================
echo = precompilation en Assembleur =
echo ================================
..\..\compilateur\bin\816-tcc -Wall -I ..\..\pvsneslib\include -c hello_world.c -o hello.ps
pause 
echo ================
echo = optimization =
echo ================
..\..\compilateur\bin\816-opt.py  hello.ps >hello.asp
..\..\compilateur\bin\constify hello_world.c hello.asp hello.asm

pause
echo ========================================
echo = Compilation des fichiers assembleurs =
echo ========================================
..\..\compilateur\bin\wla-65816 -io hello.asm hello.obj
..\..\compilateur\bin\wla-65816 -io data.asm data.obj
..\..\compilateur\bin\wla-65816 -io hdr.asm hdr.obj
pause

echo ===========
echo = linkage =
echo ===========

 ..\..\compilateur\bin\wlalink -dsnov data.obj hdr.obj crt0_snes.obj hello.obj libc.obj libm.obj libtcc.obj snes.sfc
pause

echo ================
echo = Finalisation =
echo ================

..\..\compilateur\tools\snestools -hi! -ht"snes" snes.sfc
pause

echo ============
echo = Netoyage =
echo ============

if exist "*.o" del *.o
if exist "*.sym" del *.sym


pause