
-- CUDA PARALLEL COMPUTING
-COMPLIE
nvcc AprioriRule.cu FileReader.cpp OutputWritter.cpp main.cpp -o main
-RUN
time ./main.exe input1.txt 10 20 1000 8

-- G++ CODE SEQUENTLY
-COMPLIE
nvcc AprioriRule.cpp FileReader.cpp OutputWritter.cpp main.cpp -o main1
-RUN
time ./main1.exe input1.txt 10 20 1 1

