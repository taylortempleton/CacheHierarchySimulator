CXX = g++
CXXFLAGS = -Wall -Wextra -g

# Source Files
SRC = main.cpp cacheClass.cpp

# Object files
OBJS = $(SRC:.cpp =.o)
 
cache_sim: $(OBJS)
	@echo "**** Building Dependencies & Executable *****"
	$(CXX) -o cache_sim $(CXXFLAGS) $(SRC)
	@echo "**** Build Complete *****"

clean:
	@echo "**** Removing executable and object files *****"
	rm -f *.o cache_sim

