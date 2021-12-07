CC=g++

CFLAGS=-c

FLAGS=-lopencv_core -lopencv_highgui \
-lopencv_imgproc -lopencv_imgcodecs

# The following libraries are ignored for now:
# -lopencv_alphamat -lopencv_barcode -lopencv_cvv \
-lopencv_intensity_transform -lopencv_mcc -lopencv_rapid \
-lopencv_wechat_qrcode -lopencv_xfeatures2d \
-lopencv_gapi -lopencv_stitching \
-lopencv_aruco -lopencv_bgsegm -lopencv_bioinspired -lopencv_ccalib \
-lopencv_dnn_objdetect -lopencv_dnn_superres -lopencv_dpm -lopencv_face \
-lopencv_freetype -lopencv_fuzzy -lopencv_hdf -lopencv_hfs -lopencv_img_hash \
-lopencv_line_descriptor -lopencv_quality -lopencv_reg -lopencv_rgbd \
-lopencv_saliency -lopencv_stereo -lopencv_structured_light \
-lopencv_phase_unwrapping -lopencv_superres -lopencv_optflow \
-lopencv_surface_matching -lopencv_tracking -lopencv_highgui \
-lopencv_datasets -lopencv_text -lopencv_plot -lopencv_videostab \
-lopencv_videoio -lopencv_viz -lopencv_shape -lopencv_ml -lopencv_ximgproc \
-lopencv_video -lopencv_xobjdetect -lopencv_objdetect -lopencv_calib3d \
-lopencv_imgcodecs -lopencv_features2d -lopencv_dnn -lopencv_flann \
-lopencv_xphoto -lopencv_photo -lopencv_imgproc -lopencv_core

INCDIR = -I/usr/include/opencv4
CST11=-std=c++11

SHORTHAND=`pkg-config --cflags --libs opencv4`

all: P1

P1: P1.o 
	$(CC) $(CST11) P1.o $(INCDIR) $(LIBDIR) $(FLAGS) -o P1

P1.o: P1.cpp utility.hpp
	$(CC) $(CST11) $(CFLAGS) $(INCDIR) P1.cpp

clean:
	rm -f *o P1