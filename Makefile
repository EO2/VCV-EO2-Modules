SLUG = EO2

VERSION = 0.6.0dev

#FLAGS +=
#CFLAGS +=
#CXXFLAGS +=

#LDFLAGS +=

SOURCES += $(wildcard src/*.cpp)

DISTRIBUTABLES += $(wildcard LICENSE*) res

RACK_DIR ?= ../..

include $(RACK_DIR)/plugin.mk
