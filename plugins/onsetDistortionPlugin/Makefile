#!/user/bin/make -f
# Makefile for DISTRHO Plugins #
# ---------------------------- #
# Created by falkTX
#

# --------------------------------------------------------------
# Project name, used for binaries

NAME = 	onsetdistortionplugin
# --------------------------------------------------------------
# Files to build

FILES_DSP  = onsetDistortionPlugin.cpp \
		onset_distortion/onsetDistortion.cpp \
		onset_distortion/aubio_module/src/aubio_module.cpp \
		onset_distortion/aubio_module/src/aubio_onset.cpp \
		onset_distortion/aubio_module/src/hopbuffer.cpp \
		onset_distortion/ADSR.cpp \
		onset_distortion/distortion/simpleDistortion.cpp


# --------------------------------------------------------------
# Do some magic

include ../../dpf/Makefile.plugins.mk

BUILD_CXX_FLAGS += -laubio

ifeq ($(WIN32),true)
LINK_OPTS += -static -static-libgcc -static-libstdc++
endif

# --------------------------------------------------------------
# Enable all possible plugin types

ifeq ($(HAVE_DGL),true)
ifeq ($(HAVE_JACK),true)
TARGETS += jack
endif
endif

ifeq ($(HAVE_DGL),true)
TARGETS += lv2_sep
else
TARGETS += lv2_dsp
endif

TARGETS += vst

all: $(TARGETS)

# --------------------------------------------------------------
