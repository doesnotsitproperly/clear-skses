CXXFLAGS := -Wall -O2

default:
ifeq ($(OS), Windows_NT)
	$(CXX) main.cpp $(CXXFLAGS) -o ClearSKSEs.exe
	7z a ClearSKSEs-$(VERSION).7z ClearSKSEs.exe
	7z a ClearSKSEs-$(VERSION).zip ClearSKSEs.exe
else
	$(CXX) main.cpp $(CXXFLAGS) -o ClearSKSEs
	7z a ClearSKSEs-$(VERSION).7z ClearSKSEs
	7z a ClearSKSEs-$(VERSION).zip ClearSKSEs
endif

run:
ifeq ($(OS), Windows_NT)
	$(CXX) main.cpp $(CXXFLAGS) -o ClearSKSEs.exe
	.\ClearSKSEs.exe -no-wait
else
	$(CXX) main.cpp $(CXXFLAGS) -o ClearSKSEs
	./ClearSKSEs
endif
