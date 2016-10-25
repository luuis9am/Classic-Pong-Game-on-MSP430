all:
	(cd timerLib; make install)
	(cd lcdLib; make install)
	(cd ball_demo; make)

clean:
	(cd timerLib; make clean)
	(cd lcdLib; make clean)
	(cd ball_demo; make clean)
	rm -rf lib h
