dungeonGo: main.o roomManip.o stringManip.o
	gcc main.o roomManip.o stringManip.o -o dungeonGo

main.o: main.c roomManip.h stringManip.h
	gcc main.c -c

roomManip.o: roomManip.c roomManip.h
	gcc roomManip.c roomManip.h -c

stringManip.o: stringManip.c stringManip.h
	gcc stringManip.c stringManip.h -c

clean:
	rm *.o
	rm roomManip.h.gch 
	rm stringManip.h.gch
	rm dungeonGo
