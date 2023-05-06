GG=g++ -std=c++14

all=Mem-Pages 

Mem-Pages:Mem-Pages.cpp
	$(GG) Mem-Pages.cpp -o Mem-Pages


run:
	make
	if [ ! -e 'PyPlot' ] ; then \
	pyinstaller -F -w PyPlot.py ;\
	mv dist/PyPlot	. ;\
	rm -rf build dist *.spec ;\
	fi	
	./Mem-Pages | ./PyPlot

clean:
	rm End.gif PyPlot Mem-Pages
