###########################################################################
## Makefile generated for MATLAB file/project 'main_pef'. 
## 
## Makefile     : main_pef_rtw.mk
## Generated on : Tue Dec 01 15:13:38 2020
## MATLAB Coder version: 4.3 (R2019b)
## 
## Build Info:
## 
## Final product: ./main_pef.lib
## Product type : static-library
## 
###########################################################################

###########################################################################
## MACROS
###########################################################################

# Macro Descriptions:
# PRODUCT_NAME            Name of the system to build
# MAKEFILE                Name of this makefile
# CMD_FILE                Command file
# MODELLIB                Static library target

PRODUCT_NAME              = main_pef
MAKEFILE                  = main_pef_rtw.mk
MATLAB_ROOT               = C:/PROGRA~1/POLYSP~1/R2019b
MATLAB_BIN                = C:/PROGRA~1/POLYSP~1/R2019b/bin
MATLAB_ARCH_BIN           = $(MATLAB_BIN)/win64
MASTER_ANCHOR_DIR         = 
START_DIR                 = C:/_source/matlab/basicTone/codegen/lib/main_pef
TGT_FCN_LIB               = None
SOLVER_OBJ                = 
CLASSIC_INTERFACE         = 0
MODEL_HAS_DYNAMICALLY_LOADED_SFCNS = 
RELATIVE_PATH_TO_ANCHOR   = .
CMD_FILE                  = main_pef_rtw.rsp
C_STANDARD_OPTS           = 
CPP_STANDARD_OPTS         = 
MODELLIB                  = main_pef.lib

###########################################################################
## TOOLCHAIN SPECIFICATIONS
###########################################################################

# Toolchain Name:          LCC-win64 v2.4.1 | gmake (64-bit Windows)
# Supported Version(s):    2.4.1
# ToolchainInfo Version:   2019b
# Specification Revision:  1.0
# 

#-----------
# MACROS
#-----------

SHELL              = cmd
LCC_ROOT           = $(MATLAB_ROOT)/sys/lcc64/lcc64
LCC_BUILDLIB       = $(LCC_ROOT)/bin/buildlib
LCC_LIB            = $(LCC_ROOT)/lib64
MW_EXTERNLIB_DIR   = $(MATLAB_ROOT)/extern/lib/win64/microsoft
MW_LIB_DIR         = $(MATLAB_ROOT)/lib/win64
TOOLCHAIN_INCLUDES = -I$(LCC_ROOT)/include64

TOOLCHAIN_SRCS = 
TOOLCHAIN_INCS = 
TOOLCHAIN_LIBS = 

#------------------------
# BUILD TOOL COMMANDS
#------------------------

# C Compiler: Lcc-win64 C Compiler
CC_PATH = $(LCC_ROOT)/bin
CC = "$(CC_PATH)/lcc64"

# Linker: Lcc-win64 Linker
LD_PATH = $(LCC_ROOT)/bin
LD = "$(LD_PATH)/lcclnk64"

# Archiver: Lcc-win64 Archiver
AR_PATH = $(LCC_ROOT)/bin
AR = "$(AR_PATH)/lcclib64"

# MEX Tool: MEX Tool
MEX_PATH = $(MATLAB_ARCH_BIN)
MEX = "$(MEX_PATH)/mex"

# Download: Download
DOWNLOAD =

# Execute: Execute
EXECUTE = $(PRODUCT)

# Builder: GMAKE Utility
MAKE_PATH = %MATLAB%\bin\win64
MAKE = "$(MAKE_PATH)/gmake"


#-------------------------
# Directives/Utilities
#-------------------------

CDEBUG              = -g
C_OUTPUT_FLAG       = -Fo
LDDEBUG             =
OUTPUT_FLAG         = -o
ARDEBUG             =
STATICLIB_OUTPUT_FLAG = /out:
MEX_DEBUG           = -g
RM                  = @del /F
ECHO                = @echo
MV                  = @move
RUN                 =

#----------------------------------------
# "Faster Builds" Build Configuration
#----------------------------------------

ARFLAGS              =
CFLAGS               = -c -w -noregistrylookup -nodeclspec -I$(LCC_ROOT)/include64
DOWNLOAD_FLAGS       =
EXECUTE_FLAGS        =
LDFLAGS              = -s -L$(LCC_LIB) $(LDFLAGS_ADDITIONAL)
MEX_CPPFLAGS         =
MEX_CPPLDFLAGS       =
MEX_CFLAGS           =
MEX_LDFLAGS          =
MAKE_FLAGS           = -f $(MAKEFILE)
SHAREDLIB_LDFLAGS    = -dll -entry LibMain -s -L$(LCC_LIB) $(LDFLAGS_ADDITIONAL) $(DEF_FILE)



###########################################################################
## OUTPUT INFO
###########################################################################

PRODUCT = ./main_pef.lib
PRODUCT_TYPE = "static-library"
BUILD_TYPE = "Static Library"

###########################################################################
## INCLUDE PATHS
###########################################################################

INCLUDES_BUILDINFO = -I$(START_DIR) -IC:/_source/matlab/BASICT~1 -I$(MATLAB_ROOT)/extern/include -I$(MATLAB_ROOT)/simulink/include -I$(MATLAB_ROOT)/rtw/c/src -I$(MATLAB_ROOT)/rtw/c/src/ext_mode/common -I$(MATLAB_ROOT)/rtw/c/ert

INCLUDES = $(INCLUDES_BUILDINFO)

###########################################################################
## DEFINES
###########################################################################

DEFINES_CUSTOM = 
DEFINES_STANDARD = -DMODEL=main_pef -DHAVESTDIO -DUSE_RTMODEL

DEFINES = $(DEFINES_CUSTOM) $(DEFINES_STANDARD)

###########################################################################
## SOURCE FILES
###########################################################################

SRCS = $(START_DIR)/rt_nonfinite.c $(START_DIR)/rtGetNaN.c $(START_DIR)/rtGetInf.c $(START_DIR)/main_pef_rtwutil.c $(START_DIR)/main_pef_data.c $(START_DIR)/main_pef_initialize.c $(START_DIR)/main_pef_terminate.c $(START_DIR)/main_pef.c $(START_DIR)/nextpow2.c $(START_DIR)/logspace.c $(START_DIR)/linspace.c $(START_DIR)/diff.c $(START_DIR)/sum.c $(START_DIR)/find.c $(START_DIR)/hamming.c $(START_DIR)/gencoswin.c $(START_DIR)/colon.c $(START_DIR)/repmat.c $(START_DIR)/fft.c $(START_DIR)/fft1.c $(START_DIR)/bluesteinSetup.c $(START_DIR)/interp1.c $(START_DIR)/ifft.c $(START_DIR)/main_pef_emxutil.c $(START_DIR)/main_pef_emxAPI.c

ALL_SRCS = $(SRCS)

###########################################################################
## OBJECTS
###########################################################################

OBJS = rt_nonfinite.obj rtGetNaN.obj rtGetInf.obj main_pef_rtwutil.obj main_pef_data.obj main_pef_initialize.obj main_pef_terminate.obj main_pef.obj nextpow2.obj logspace.obj linspace.obj diff.obj sum.obj find.obj hamming.obj gencoswin.obj colon.obj repmat.obj fft.obj fft1.obj bluesteinSetup.obj interp1.obj ifft.obj main_pef_emxutil.obj main_pef_emxAPI.obj

ALL_OBJS = $(OBJS)

###########################################################################
## PREBUILT OBJECT FILES
###########################################################################

PREBUILT_OBJS = 

###########################################################################
## LIBRARIES
###########################################################################

LIBS = 

###########################################################################
## SYSTEM LIBRARIES
###########################################################################

SYSTEM_LIBS = 

###########################################################################
## ADDITIONAL TOOLCHAIN FLAGS
###########################################################################

#---------------
# C Compiler
#---------------

CFLAGS_BASIC = $(DEFINES) $(INCLUDES)

CFLAGS += $(CFLAGS_BASIC)

###########################################################################
## INLINED COMMANDS
###########################################################################

###########################################################################
## PHONY TARGETS
###########################################################################

.PHONY : all build clean info prebuild download execute


all : build
	@echo "### Successfully generated all binary outputs."


build : prebuild $(PRODUCT)


prebuild : 


download : $(PRODUCT)


execute : download


###########################################################################
## FINAL TARGET
###########################################################################

#---------------------------------
# Create a static library         
#---------------------------------

$(PRODUCT) : $(OBJS) $(PREBUILT_OBJS)
	@echo "### Creating static library "$(PRODUCT)" ..."
	$(AR) $(ARFLAGS) /out:$(PRODUCT) @$(CMD_FILE)
	@echo "### Created: $(PRODUCT)"


###########################################################################
## INTERMEDIATE TARGETS
###########################################################################

#---------------------
# SOURCE-TO-OBJECT
#---------------------

%.obj : %.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


%.obj : $(RELATIVE_PATH_TO_ANCHOR)/%.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


%.obj : $(START_DIR)/%.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


%.obj : C:/_source/matlab/basicTone/%.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


%.obj : $(MATLAB_ROOT)/rtw/c/src/%.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


rt_nonfinite.obj : $(START_DIR)/rt_nonfinite.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


rtGetNaN.obj : $(START_DIR)/rtGetNaN.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


rtGetInf.obj : $(START_DIR)/rtGetInf.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


main_pef_rtwutil.obj : $(START_DIR)/main_pef_rtwutil.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


main_pef_data.obj : $(START_DIR)/main_pef_data.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


main_pef_initialize.obj : $(START_DIR)/main_pef_initialize.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


main_pef_terminate.obj : $(START_DIR)/main_pef_terminate.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


main_pef.obj : $(START_DIR)/main_pef.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


nextpow2.obj : $(START_DIR)/nextpow2.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


logspace.obj : $(START_DIR)/logspace.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


linspace.obj : $(START_DIR)/linspace.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


diff.obj : $(START_DIR)/diff.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


sum.obj : $(START_DIR)/sum.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


find.obj : $(START_DIR)/find.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


hamming.obj : $(START_DIR)/hamming.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


gencoswin.obj : $(START_DIR)/gencoswin.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


colon.obj : $(START_DIR)/colon.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


repmat.obj : $(START_DIR)/repmat.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


fft.obj : $(START_DIR)/fft.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


fft1.obj : $(START_DIR)/fft1.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


bluesteinSetup.obj : $(START_DIR)/bluesteinSetup.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


interp1.obj : $(START_DIR)/interp1.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


ifft.obj : $(START_DIR)/ifft.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


main_pef_emxutil.obj : $(START_DIR)/main_pef_emxutil.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


main_pef_emxAPI.obj : $(START_DIR)/main_pef_emxAPI.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


###########################################################################
## DEPENDENCIES
###########################################################################

$(ALL_OBJS) : rtw_proj.tmw $(MAKEFILE)


###########################################################################
## MISCELLANEOUS TARGETS
###########################################################################

info : 
	@echo "### PRODUCT = $(PRODUCT)"
	@echo "### PRODUCT_TYPE = $(PRODUCT_TYPE)"
	@echo "### BUILD_TYPE = $(BUILD_TYPE)"
	@echo "### INCLUDES = $(INCLUDES)"
	@echo "### DEFINES = $(DEFINES)"
	@echo "### ALL_SRCS = $(ALL_SRCS)"
	@echo "### ALL_OBJS = $(ALL_OBJS)"
	@echo "### LIBS = $(LIBS)"
	@echo "### MODELREF_LIBS = $(MODELREF_LIBS)"
	@echo "### SYSTEM_LIBS = $(SYSTEM_LIBS)"
	@echo "### TOOLCHAIN_LIBS = $(TOOLCHAIN_LIBS)"
	@echo "### CFLAGS = $(CFLAGS)"
	@echo "### LDFLAGS = $(LDFLAGS)"
	@echo "### SHAREDLIB_LDFLAGS = $(SHAREDLIB_LDFLAGS)"
	@echo "### ARFLAGS = $(ARFLAGS)"
	@echo "### MEX_CFLAGS = $(MEX_CFLAGS)"
	@echo "### MEX_CPPFLAGS = $(MEX_CPPFLAGS)"
	@echo "### MEX_LDFLAGS = $(MEX_LDFLAGS)"
	@echo "### MEX_CPPLDFLAGS = $(MEX_CPPLDFLAGS)"
	@echo "### DOWNLOAD_FLAGS = $(DOWNLOAD_FLAGS)"
	@echo "### EXECUTE_FLAGS = $(EXECUTE_FLAGS)"
	@echo "### MAKE_FLAGS = $(MAKE_FLAGS)"


clean : 
	$(ECHO) "### Deleting all derived files..."
	$(RM) $(subst /,\,$(PRODUCT))
	$(RM) $(subst /,\,$(ALL_OBJS))
	$(ECHO) "### Deleted all derived files."


