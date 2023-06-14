all:	
	make -C OscProbCalcer
	make -C Oscillator
	make -C Apps

clean:
	make clean -C OscProbCalcer
	make clean -C Oscillator
	make clean -C Apps
	rm -rf ./Lib/*
	rm -rf ./Bin/*

vclean: clean
	rm -rf ProbGPU
	rm -rf CUDAProb3
	rm -rf CUDAProb3Linear
	rm -rf Prob3plusplus
	rm -rf ./Lib
	rm -rf ./Bin

deps:
	sh BuildPreReqs.sh
