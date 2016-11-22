all:
	(cd timerLib; make install)
	(cd lcdLib; make install)
	(cd shapeLib; make install)
	(cd circleLib; make install)
	(cd p2swLib; make install)
	(cd p2sw-demo; make)
	(cd shape-motion-demo; make)

doc:
	rm -rf doxygen_docs
	doxygen Doxyfile
clean:
	(cd timerLib; make clean)
	(cd lcdLib; make clean)
	(cd shapeLib; make clean)
	(cd p2swLib; make clean)
	(cd p2sw-demo; make clean)
	(cd shape-motion-demo; make clean)
	(cd circleLib; make clean)
	rm -rf lib h
	rm -rf doxygen_docs/*
