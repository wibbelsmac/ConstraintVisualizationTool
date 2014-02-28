CXX      = $(shell fltk-config --cxx)
DEBUG    = -g
CXXFLAGS = $(shell fltk-config --use-gl --use-images --cxxflags ) -I.
LDFLAGS  = $(shell fltk-config --use-gl --use-images --ldflags )
LDSTATIC = $(shell fltk-config --use-gl --use-images --ldstaticflags )
LINK     = $(CXX)

TARGET = editor
OBJS = EditorMain.o EditorGui.o EditorBackEnd.o
SRCS = EditorMain.cxx  EditorGui.cxx EditorBackEnd.cxx

.SUFFIXES: .o .cxx
%.o: %.cxx
		$(CXX) $(CXXFLAGS) $(DEBUG) -c $<

all: $(TARGET)
		$(LINK) -o $(TARGET) $(OBJS) $(LDSTATIC)

$(TARGET): $(OBJS)
EditorMain.o: EditorMain.cxx EditorGui.h EditorBackEnd.cxx
EditorGui.o: EditorMain.cxx EditorBackEnd.cxx EditorGui.cxx
EditorBackEnd.o: EditorBackEnd.cxx

clean: $(TARGET) $(OBJS)
		rm -f *.o 2> /dev/null
		rm -f $(TARGET) 2> /dev/null