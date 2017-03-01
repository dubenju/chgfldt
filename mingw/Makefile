APP=chgfldt

# -ansi -pedantic -D_FILE_OFFSET_BITS=64
CC = C:/MinGW/bin/gcc.exe -std=gnu99 -D_DEBUGx -D_MINGW
CC1 = c:/mingw/libexec/gcc/mingw32/5.3.0/cc1.exe -quiet -v -iprefix c:/mingw/lib/gcc/mingw32/5.3.0/ -D_REENTRANT $(APP).c -quiet -dumpbase $(APP).c -mtune=generic -march=i586 -auxbase $(APP)  -version -std=c99
# AS  = C:/MinGW/bin/as.exe
AS  = c:/mingw/mingw32/bin/as.exe

LINK_APL = C:\MinGW\bin\ld.exe -v \
        -plugin c:/mingw/libexec/gcc/mingw32/5.3.0/liblto_plugin-0.dll \
        -plugin-opt=c:/mingw/libexec/gcc/mingw32/5.3.0/lto-wrapper.exe \
        -plugin-opt=-fresolution=C:\Users\DBJ\AppData\Local\Temp\cceCE83a.res \
        -plugin-opt=-pass-through=-lmingw32 \
        -plugin-opt=-pass-through=-lgcc \
        -plugin-opt=-pass-through=-lgcc_eh \
        -plugin-opt=-pass-through=-lmoldname \
        -plugin-opt=-pass-through=-lmingwex \
        -plugin-opt=-pass-through=-lmsvcrt \
        -plugin-opt=-pass-through=-lpthread \
        -plugin-opt=-pass-through=-ladvapi32 \
        -plugin-opt=-pass-through=-lshell32 \
        -plugin-opt=-pass-through=-luser32 \
        -plugin-opt=-pass-through=-lkernel32 \
        -plugin-opt=-pass-through=-lmingw32 \
        -plugin-opt=-pass-through=-lgcc \
        -plugin-opt=-pass-through=-lgcc_eh \
        -plugin-opt=-pass-through=-lmoldname \
        -plugin-opt=-pass-through=-lmingwex \
        -plugin-opt=-pass-through=-lmsvcrt \
        -Bdynamic \
        -o $(APP).exe \
        c:/mingw/mingw32/lib/crt2.o \
        c:/mingw/lib/gcc/mingw32/5.3.0/crtbegin.o \
        -Lc:/mingw/lib/gcc/mingw32/5.3.0 \
        -Lc:/mingw/lib/gcc \
        -Lc:/mingw/mingw32/lib \
        -Lc:/mingw/lib \
        .\$(APP).obj \
        -lmingw32 -lgcc -lgcc_eh -lmoldname -lmingwex -lmsvcrt \
        -lpthread -ladvapi32 -lshell32 -luser32 -lkernel32 \
        -lmingw32 -lgcc -lgcc_eh -lmoldname -lmingwex -lmsvcrt \
        c:/mingw/lib/gcc/mingw32/5.3.0/crtend.o

LIBS = -lmingw32 -lgcc -lgcc_eh -lmoldname -lmingwex -lmsvcrt -ladvapi32 -lshell32 -luser32 -lkernel32 -lmingw32 -lgcc -lgcc_eh -lmoldname -lmingwex -lmsvcrt c:/mingw/lib/gcc/mingw32/4.8.1/crtend.o
DELE = rm -f 

default :
	$(CC) -B -std=c99 -v -o $(APP).exe ..\$(APP).cpp
#	$(CC) -B -include ../readfat.h -std=c99 -v -o $(APP).exe $(APP).c
#	$(CC1) -H -include ./readfat.h -std=c99 -v -o readfat.exe readfat.c

asm : clean
	$(CC1) -o $(APP).gas
obj : asm 
	$(AS) -v -o $(APP).obj $(APP).gas
exe : clean obj 
	$(LINK_APL)
#	$(CLL) $(APP).obj -o $(APP).exe $(LIBS)

clean :
	$(DELE) $(APP).gas $(APP).obj $(APP).exe
