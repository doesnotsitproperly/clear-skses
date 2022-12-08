default:
	$(CXX) main.cpp -O2 -Wall -o ClearSKSEs
	7z a ClearSKSEs-$(VERSION).7z ClearSKSEs
	7z a ClearSKSEs-$(VERSION).zip ClearSKSEs

windows:
	$(CXX) main.cpp -O2 -Wall -o ClearSKSEs.exe
	7z a ClearSKSEs-$(VERSION).7z ClearSKSEs.exe
	7z a ClearSKSEs-$(VERSION).zip ClearSKSEs.exe
