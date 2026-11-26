###############################################################################
#
#  The global Makefile to build all Hydra modules from scratch.
#
#  Examples and explanations can be found in the file README
#
###############################################################################

# no external dependencies for a total build
#export HADDIR   := $(shell pwd)
MYHADDIR        ?= $(shell pwd)
INSTALL_DIR      =$(MYHADDIR)/

export USES_RFIO       ?= no
export USES_GFORTRAN   ?= no
export USES_ORACLE     ?= yes

MODULES ?=	GPhotons

include $(HADDIR)/hades.def.mk
include $(HADDIR)/hades.rules.mk
