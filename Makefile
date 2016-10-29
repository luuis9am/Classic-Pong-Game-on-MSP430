all:
	(cd timerLib; make install)
	(cd lcdLib; make install)
	(cd shapeLib; make install)
	(cd p2swLib; make install)
	(cd ball-demo; make)
	(cd shape-motion-demo; make)

clean:
	(cd timerLib; make clean)
	(cd lcdLib; make clean)
	(cd shapeLib; make clean)
	(cd ball-demo; make clean)
	(cd shape-motion-demo; make clean)
	(cd p2swLib; make clean)
	rm -rf lib h
