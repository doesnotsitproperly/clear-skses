import os, sys

output = "ClearSKSEs"
if os.name == "nt":
	output += ".exe"

os.system("g++ main.cpp -O2 -Wall -o " + output)
os.system("7z a ClearSKSEs-" + sys.argv[1] + ".7z " + output)
os.system("7z a ClearSKSEs-" + sys.argv[1] + ".zip " + output)
