CXX=clang++
CXXFLAGS=-std=c++14 -Werror -Wsign-conversion
VALGRIND_FLAGS=-v --leak-check=full --show-leak-kinds=all  --error-exitcode=99

BUILDING_SOURCES = Village.cpp Road.cpp
CARD_SOURCES = development_card.cpp
TILES_SOURCES = Plot.cpp Resource.cpp
CODE_SOURCES = $(BUILDING_SOURCES) $(TILES_SOURCES) Board.cpp Player.cpp Game.cpp $(CARD_SOURCES)
CODE_HEADERS = $(subst .cpp,.h,$(CODE_SOURCES))
CODE_OBJECTS = $(subst .cpp,.o,$(CODE_SOURCES))
TEST_SOURCES = Tests/testPlayer.cpp Tests/testBoard.cpp Tests/testGame.cpp
TEST_OBJECTS = $(subst .cpp,.o,$(TEST_SOURCES))

catan: demo
	./$^

all: demo testMake

demo: $(CODE_OBJECTS) main.cpp
	$(CXX) $(CXXFLAGS) $^ -o demo -lstdc++

test: testMake
	./test

testMake: Tests/TestCounter.o $(TEST_OBJECTS) $(CODE_OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o test -lstdc++ -lm $(DOCTEST_INCLUDE)

tidy:
	clang-tidy $(CODE_SOURCES) \
        -checks=bugprone-*,clang-analyzer-*,cppcoreguidelines-*,performance-*,portability-*,readability-*,-cppcoreguidelines-pro-bounds-pointer-arithmetic,-cppcoreguidelines-owning-memory \
        -warnings-as-errors=-* \
        -header-filter=".*" \
        -extra-arg=-Wno-shorten-64-to-32

valgrind: demo testMake
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./test 2>&1 | { egrep "lost| at " || true; }
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./testFull 2>&1 | { egrep "lost| at " || true; }

%.o: %.cpp
	$(CXX) $(CXXFLAGS) --compile $< -o $@

clean:
	rm -f *.o demo test testFull Cards/*.o Board/Buildings/*.o Board/Tiles/*.o Board/*.o Tests/*.o