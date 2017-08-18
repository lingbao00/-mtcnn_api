CXX = g++

CXXFLAGS := -Wall -O2 -std=c++11 -fPIC

ARCH = ar rcs

TF_ROOT=../tf_install/

LIB_DIR = ./lib

OBJ_DIR = ./obj/

SRC_DIR = ./src/

LIB_S = $(LIB_DIR)/libmtcnnfacedec.a
LIB_D = $(LIB_DIR)/libmtcnnfacedec.so

EXE = main

EXE_SRC = main.cpp

SRCS = $(wildcard $(SRC_DIR)*.cpp)

EXE_OBJ = $(OBJ_DIR)main.o

OBJ = mt_dec.o mtcnn_detect.o tensorflow_mtcnn.o utils.o comm_lib.o

OBJS = $(addprefix $(OBJ_DIR),$(OBJ))


OPENCV_INC = -I $(OPENCV_INC_ROOT)

INCLUDES = -I./$(TF_ROOT)include -I./ -I./include

LDFLAGS = -L

LIBS = -lopencv_calib3d -lopencv_contrib -lopencv_core -lopencv_features2d -lopencv_flann -lopencv_gpu -lopencv_highgui -lopencv_imgproc -lopencv_legacy -lopencv_ml -lopencv_objdetect -lopencv_ocl -lopencv_photo -lopencv_stitching -lopencv_superres -lopencv_ts -lopencv_video -lopencv_videostab -lboost_system -lglog 

all: $(LIB_S) $(LIB_D) $(EXE)
		@echo '---------------- COMPILE $EXE DONE ------------------'

#to get the .a file
$(LIB_S): $(OBJS)
	$(ARCH) $(LIB_S) $(OBJS)

$(OBJ_DIR)%.o:$(SRC_DIR)%.cpp
	@echo '$(INCLUDES)-----------'
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(LIB_D): $(OBJS)
	$(CXX) $(CXXFLAGS) -shared -o $(LIB_D) $(OBJS)

$(EXE): $(EXE_OBJ)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $(EXE) $(EXE_OBJ)  $(LDFLAGS) $(LIBS) $(LIB_D) ./$(TF_ROOT)lib/libtensorflow.so

$(EXE_OBJ): $(EXE_SRC)
	$(CC) $(CXXFLAGS) $(INCLUDES) $(LDFLAGS) $(LIBS) -c $(EXE_SRC) -o $(EXE_OBJ) 

.PYTHON: clean

clean:
	rm -rf $(EXE) $(EXE_OBJ) $(OBJS) $(LIB_S) $(LIB_D)
