TARGET = calc
BISON_SRC = $(TARGET).y
INCLUDE_BISON_C = variable.c 
INCLUDE_BISON_O = variable.o 
BISON_H   = $(TARGET).tab.h
BISON_C   = $(TARGET).tab.c
BISON_O   = $(TARGET).tab.o
BISON_OUT = $(BISON_C) $(BISON_H) $(TARGET).output
FLEX_SRC  = $(TARGET).l
FLEX_C    = lex.yy.c
FLEX_O    = lex.yy.o
C_FILES   = $(BISON_C) $(FLEX_C) $(INCLUDE_BISON_C)
OBJ       = $(FLEX_O) $(BISON_O) $(INCLUDE_BISON_O)

all : $(TARGET)

$(TARGET) : $(OBJ)
	gcc -o $@ $(OBJ)

$(FLEX_C) : $(FLEX_SRC) $(BISON_H)
	flex $(FLEX_SRC)

$(BISON_OUT) : $(BISON_SRC)
	bison -dv $(BISON_SRC)

.c.o :
	gcc -c $<


clean :
	rm -f *.exe
	rm -f *.yy.c
	rm -f *.tab.c
	rm -f *.tab.h
	rm -f *.output
	rm -f *.o
	rm -f $(TARGET)

lex.yy.o: lex.yy.c calc.tab.h
calc.tab.o: calc.tab.c calc.tab.h variable.h