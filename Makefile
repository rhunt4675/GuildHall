########################################
## SETUP MAKEFILE
##      Set the appropriate TARGET (our
## executable name) and any OBJECT files
## we need to compile for this program.
##
## Next set the path to our local
## include/, lib/, and bin/ folders.
## (If you we are compiling in the lab,
## then you can ignore these values.
## They are only for if you are
## compiling on your personal machine.)
##
## Set if we are compiling in the lab
## environment or not.  Set to:
##    1 - if compiling in the Lab
##    0 - if compiling at home
##
## Finally, set the flags for which
## libraries you are using and want to
## compile against.
########################################

TARGET = guild

OBJECTS = main.o utils/context.o heroes/Antikythera.o heroes/Diomedes.o utils/ControlPoint.o utils/Point.o utils/bezierCurve.o utils/Direction.o heroes/AntikytheraPet.o utils/Camera.o utils/InputReader.o heroes/Asterion.o

LOCAL_INC_PATH = /Users/jpaone/Desktop/include
LOCAL_LIB_PATH = /Users/jpaone/Desktop/lib
LOCAL_BIN_PATH = /Users/jpaone/Desktop/bin


BUILDING_IN_LAB = 1
USING_OPENAL = 1
USING_OPENGL = 1
USING_GLUI = 0

ifeq ($(USER), ryhunt)
LOCAL_INC_PATH = ./include
LOCAL_LIB_PATH = ./lib
endif

ifeq ($(USER), rybailey)
LOCAL_INC_PATH = /usr/include
LOCAL_LIB_PATH = /usr/lib
LOCAL_BIN_PATH = /usr/bin
BUILDING_IN_LAB = 0
endif
#########################################################################################
#########################################################################################
#########################################################################################
##
## !!!STOP!!!
## THERE IS NO NEED TO MODIFY ANYTHING BELOW THIS LINE
## IT WILL WORK FOR YOU.  TRUST ME




#############################
## COMPILING INFO
#############################

CXX    = g++
CFLAGS = -Wall -std=c++11 -g

INCPATH += -I./include
LIBPATH += -L./lib
LAB_INC_PATH = C:/sw/opengl/include
LAB_LIB_PATH = C:/sw/opengl/lib
LAB_BIN_PATH = C:/sw/opengl/bin

# if we are not building in the Lab
ifeq ($(BUILDING_IN_LAB), 0)
    # and we are running Windows
    ifeq ($(OS), Windows_NT)
        # then set our lab paths to our local paths
        # so the Makefile will still work seamlessly
        LAB_INC_PATH = $(LOCAL_INC_PATH)
        LAB_LIB_PATH = $(LOCAL_LIB_PATH)
        LAB_BIN_PATH = $(LOCAL_BIN_PATH)
    endif
endif

#############################
## SETUP OpenGL & GLUT 
#############################

# if we are using OpenGL & GLUT in this program
ifeq ($(USING_OPENGL), 1)
    # Windows builds
    ifeq ($(OS), Windows_NT)
        INCPATH += -I$(LAB_INC_PATH)
        LIBPATH += -L$(LAB_LIB_PATH)
        LIBS += -lglut -lopengl32 -lglu32

    # Mac builds
    else ifeq ($(shell uname), Darwin)
        LIBS += -framework GLUT -framework OpenGL

    # Linux and all other builds
    else
        LIBS += -lglut -lGL -lGLU
    endif
endif

#############################
## SETUP OpenAL & ALUT
#############################

# if we are using OpenAL & GLUT in this program
ifeq ($(USING_OPENAL), 1)
    # Windows builds
    ifeq ($(OS), Windows_NT)
        INCPATH += -I$(LAB_INC_PATH)
        LIBPATH += -L$(LAB_LIB_PATH)
        LIBS += -lalut.dll -lOpenAL32.dll

    # Mac builds
    else ifeq ($(shell uname), Darwin)
        INCPATH += -I$(LOCAL_INC_PATH)
        LIBPATH += -L$(LOCAL_LIB_PATH)
        LIBS += -framework OpenAL

    # Linux and all other builds
    else
        INCPATH += -I$(LOCAL_INC_PATH)
        LIBPATH += -L$(LOCAL_LIB_PATH)
        LIBS += -lalut -lopenal
    endif
endif

#############################
## SETUP GLUI
#############################

# if we are using OpenGL & GLUT in this program
ifeq ($(USING_GLUI), 1)
    # Windows builds
    ifeq ($(OS), Windows_NT)
        INCPATH += -I$(LAB_INC_PATH)
        LIBPATH += -L$(LAB_LIB_PATH)
    # Linux and all other builds
    else
        INCPATH += -I$(LOCAL_INC_PATH)
        LIBPATH += -L$(LOCAL_LIB_PATH)
    endif

	LIBS += -lglui

endif

#############################
## COMPILATION INSTRUCTIONS 
#############################

all: $(TARGET)

clean:
	rm -f $(OBJECTS) $(TARGET)

depend:
	rm -f Makefile.bak
	mv Makefile Makefile.bak
	sed '/^# DEPENDENCIES/,$$d' Makefile.bak > Makefile
	echo '# DEPENDENCIES' >> Makefile
	$(CXX) $(INCPATH) -MM *.cpp >> Makefile

.c.o: 	
	$(CXX) $(CFLAGS) $(INCPATH) -c -o $@ $<

.cc.o: 	
	$(CXX) $(CFLAGS) $(INCPATH) -c -o $@ $<

.cpp.o: 	
	$(CXX) $(CFLAGS) $(INCPATH) -c -o $@ $<

$(TARGET): $(OBJECTS) 
	$(CXX) $(CFLAGS) $(INCPATH) -o $@ $^ $(LIBPATH) $(LIBS)


# DEPENDENCIES
main.o: main.cpp include/Antikythera.h include/Point.h \
 include/Direction.h include/context.h include/AntikytheraPet.h \
 include/drawable.h include/bezierCurve.h include/ControlPoint.h \
 include/Direction.h include/bezierCurveReader.h
