all:
	(cd timerLib; make install)
	(cd ball_demo; make)

clean:
	(cd timerLib; make clean)
	(cd ball_demo; make clean)
	rm -rf lib h