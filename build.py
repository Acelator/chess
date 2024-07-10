import os

os.system("cmake . -B ./bin/ && cd bin && make && echo " " && echo ' ======= OUTPUT ======= ' && ./main")
