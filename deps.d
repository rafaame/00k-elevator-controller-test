obj/Floor.o: src/Floor.cpp include/Floor.h include/common.h include/Person.h
obj/Person.o: src/Person.cpp include/Person.h include/common.h \
 include/Floor.h
obj/Building.o: src/Building.cpp include/Building.h include/common.h \
 include/Floor.h include/Elevator.h include/Floor.h include/Person.h
obj/Elevator.o: src/Elevator.cpp include/Elevator.h include/common.h \
 include/Floor.h include/Person.h
obj/main.o: src/main.cpp include/Building.h include/common.h
