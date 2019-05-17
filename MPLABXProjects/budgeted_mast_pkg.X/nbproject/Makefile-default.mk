#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/budgeted_mast_pkg.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/budgeted_mast_pkg.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=src/AD.c src/BOARD.c src/gpsLib.c src/I2C.c src/INPUT_CAPTURE.c src/LSM9DS1_func.c src/MatrixMath.c src/serial.c src/serialcomm.c src/timers.c src/vars.c include/main_lsm.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/src/AD.o ${OBJECTDIR}/src/BOARD.o ${OBJECTDIR}/src/gpsLib.o ${OBJECTDIR}/src/I2C.o ${OBJECTDIR}/src/INPUT_CAPTURE.o ${OBJECTDIR}/src/LSM9DS1_func.o ${OBJECTDIR}/src/MatrixMath.o ${OBJECTDIR}/src/serial.o ${OBJECTDIR}/src/serialcomm.o ${OBJECTDIR}/src/timers.o ${OBJECTDIR}/src/vars.o ${OBJECTDIR}/include/main_lsm.o
POSSIBLE_DEPFILES=${OBJECTDIR}/src/AD.o.d ${OBJECTDIR}/src/BOARD.o.d ${OBJECTDIR}/src/gpsLib.o.d ${OBJECTDIR}/src/I2C.o.d ${OBJECTDIR}/src/INPUT_CAPTURE.o.d ${OBJECTDIR}/src/LSM9DS1_func.o.d ${OBJECTDIR}/src/MatrixMath.o.d ${OBJECTDIR}/src/serial.o.d ${OBJECTDIR}/src/serialcomm.o.d ${OBJECTDIR}/src/timers.o.d ${OBJECTDIR}/src/vars.o.d ${OBJECTDIR}/include/main_lsm.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/src/AD.o ${OBJECTDIR}/src/BOARD.o ${OBJECTDIR}/src/gpsLib.o ${OBJECTDIR}/src/I2C.o ${OBJECTDIR}/src/INPUT_CAPTURE.o ${OBJECTDIR}/src/LSM9DS1_func.o ${OBJECTDIR}/src/MatrixMath.o ${OBJECTDIR}/src/serial.o ${OBJECTDIR}/src/serialcomm.o ${OBJECTDIR}/src/timers.o ${OBJECTDIR}/src/vars.o ${OBJECTDIR}/include/main_lsm.o

# Source Files
SOURCEFILES=src/AD.c src/BOARD.c src/gpsLib.c src/I2C.c src/INPUT_CAPTURE.c src/LSM9DS1_func.c src/MatrixMath.c src/serial.c src/serialcomm.c src/timers.c src/vars.c include/main_lsm.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/budgeted_mast_pkg.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX340F512H
MP_LINKER_FILE_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/src/AD.o: src/AD.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/AD.o.d 
	@${RM} ${OBJECTDIR}/src/AD.o 
	@${FIXDEPS} "${OBJECTDIR}/src/AD.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"include" -I"src" -MMD -MF "${OBJECTDIR}/src/AD.o.d" -o ${OBJECTDIR}/src/AD.o src/AD.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/BOARD.o: src/BOARD.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/BOARD.o.d 
	@${RM} ${OBJECTDIR}/src/BOARD.o 
	@${FIXDEPS} "${OBJECTDIR}/src/BOARD.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"include" -I"src" -MMD -MF "${OBJECTDIR}/src/BOARD.o.d" -o ${OBJECTDIR}/src/BOARD.o src/BOARD.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/gpsLib.o: src/gpsLib.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/gpsLib.o.d 
	@${RM} ${OBJECTDIR}/src/gpsLib.o 
	@${FIXDEPS} "${OBJECTDIR}/src/gpsLib.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"include" -I"src" -MMD -MF "${OBJECTDIR}/src/gpsLib.o.d" -o ${OBJECTDIR}/src/gpsLib.o src/gpsLib.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/I2C.o: src/I2C.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/I2C.o.d 
	@${RM} ${OBJECTDIR}/src/I2C.o 
	@${FIXDEPS} "${OBJECTDIR}/src/I2C.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"include" -I"src" -MMD -MF "${OBJECTDIR}/src/I2C.o.d" -o ${OBJECTDIR}/src/I2C.o src/I2C.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/INPUT_CAPTURE.o: src/INPUT_CAPTURE.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/INPUT_CAPTURE.o.d 
	@${RM} ${OBJECTDIR}/src/INPUT_CAPTURE.o 
	@${FIXDEPS} "${OBJECTDIR}/src/INPUT_CAPTURE.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"include" -I"src" -MMD -MF "${OBJECTDIR}/src/INPUT_CAPTURE.o.d" -o ${OBJECTDIR}/src/INPUT_CAPTURE.o src/INPUT_CAPTURE.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/LSM9DS1_func.o: src/LSM9DS1_func.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/LSM9DS1_func.o.d 
	@${RM} ${OBJECTDIR}/src/LSM9DS1_func.o 
	@${FIXDEPS} "${OBJECTDIR}/src/LSM9DS1_func.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"include" -I"src" -MMD -MF "${OBJECTDIR}/src/LSM9DS1_func.o.d" -o ${OBJECTDIR}/src/LSM9DS1_func.o src/LSM9DS1_func.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/MatrixMath.o: src/MatrixMath.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/MatrixMath.o.d 
	@${RM} ${OBJECTDIR}/src/MatrixMath.o 
	@${FIXDEPS} "${OBJECTDIR}/src/MatrixMath.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"include" -I"src" -MMD -MF "${OBJECTDIR}/src/MatrixMath.o.d" -o ${OBJECTDIR}/src/MatrixMath.o src/MatrixMath.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/serial.o: src/serial.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/serial.o.d 
	@${RM} ${OBJECTDIR}/src/serial.o 
	@${FIXDEPS} "${OBJECTDIR}/src/serial.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"include" -I"src" -MMD -MF "${OBJECTDIR}/src/serial.o.d" -o ${OBJECTDIR}/src/serial.o src/serial.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/serialcomm.o: src/serialcomm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/serialcomm.o.d 
	@${RM} ${OBJECTDIR}/src/serialcomm.o 
	@${FIXDEPS} "${OBJECTDIR}/src/serialcomm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"include" -I"src" -MMD -MF "${OBJECTDIR}/src/serialcomm.o.d" -o ${OBJECTDIR}/src/serialcomm.o src/serialcomm.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/timers.o: src/timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/timers.o.d 
	@${RM} ${OBJECTDIR}/src/timers.o 
	@${FIXDEPS} "${OBJECTDIR}/src/timers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"include" -I"src" -MMD -MF "${OBJECTDIR}/src/timers.o.d" -o ${OBJECTDIR}/src/timers.o src/timers.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/vars.o: src/vars.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/vars.o.d 
	@${RM} ${OBJECTDIR}/src/vars.o 
	@${FIXDEPS} "${OBJECTDIR}/src/vars.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"include" -I"src" -MMD -MF "${OBJECTDIR}/src/vars.o.d" -o ${OBJECTDIR}/src/vars.o src/vars.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/include/main_lsm.o: include/main_lsm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/include" 
	@${RM} ${OBJECTDIR}/include/main_lsm.o.d 
	@${RM} ${OBJECTDIR}/include/main_lsm.o 
	@${FIXDEPS} "${OBJECTDIR}/include/main_lsm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"include" -I"src" -MMD -MF "${OBJECTDIR}/include/main_lsm.o.d" -o ${OBJECTDIR}/include/main_lsm.o include/main_lsm.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
else
${OBJECTDIR}/src/AD.o: src/AD.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/AD.o.d 
	@${RM} ${OBJECTDIR}/src/AD.o 
	@${FIXDEPS} "${OBJECTDIR}/src/AD.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"include" -I"src" -MMD -MF "${OBJECTDIR}/src/AD.o.d" -o ${OBJECTDIR}/src/AD.o src/AD.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/BOARD.o: src/BOARD.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/BOARD.o.d 
	@${RM} ${OBJECTDIR}/src/BOARD.o 
	@${FIXDEPS} "${OBJECTDIR}/src/BOARD.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"include" -I"src" -MMD -MF "${OBJECTDIR}/src/BOARD.o.d" -o ${OBJECTDIR}/src/BOARD.o src/BOARD.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/gpsLib.o: src/gpsLib.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/gpsLib.o.d 
	@${RM} ${OBJECTDIR}/src/gpsLib.o 
	@${FIXDEPS} "${OBJECTDIR}/src/gpsLib.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"include" -I"src" -MMD -MF "${OBJECTDIR}/src/gpsLib.o.d" -o ${OBJECTDIR}/src/gpsLib.o src/gpsLib.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/I2C.o: src/I2C.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/I2C.o.d 
	@${RM} ${OBJECTDIR}/src/I2C.o 
	@${FIXDEPS} "${OBJECTDIR}/src/I2C.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"include" -I"src" -MMD -MF "${OBJECTDIR}/src/I2C.o.d" -o ${OBJECTDIR}/src/I2C.o src/I2C.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/INPUT_CAPTURE.o: src/INPUT_CAPTURE.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/INPUT_CAPTURE.o.d 
	@${RM} ${OBJECTDIR}/src/INPUT_CAPTURE.o 
	@${FIXDEPS} "${OBJECTDIR}/src/INPUT_CAPTURE.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"include" -I"src" -MMD -MF "${OBJECTDIR}/src/INPUT_CAPTURE.o.d" -o ${OBJECTDIR}/src/INPUT_CAPTURE.o src/INPUT_CAPTURE.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/LSM9DS1_func.o: src/LSM9DS1_func.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/LSM9DS1_func.o.d 
	@${RM} ${OBJECTDIR}/src/LSM9DS1_func.o 
	@${FIXDEPS} "${OBJECTDIR}/src/LSM9DS1_func.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"include" -I"src" -MMD -MF "${OBJECTDIR}/src/LSM9DS1_func.o.d" -o ${OBJECTDIR}/src/LSM9DS1_func.o src/LSM9DS1_func.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/MatrixMath.o: src/MatrixMath.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/MatrixMath.o.d 
	@${RM} ${OBJECTDIR}/src/MatrixMath.o 
	@${FIXDEPS} "${OBJECTDIR}/src/MatrixMath.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"include" -I"src" -MMD -MF "${OBJECTDIR}/src/MatrixMath.o.d" -o ${OBJECTDIR}/src/MatrixMath.o src/MatrixMath.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/serial.o: src/serial.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/serial.o.d 
	@${RM} ${OBJECTDIR}/src/serial.o 
	@${FIXDEPS} "${OBJECTDIR}/src/serial.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"include" -I"src" -MMD -MF "${OBJECTDIR}/src/serial.o.d" -o ${OBJECTDIR}/src/serial.o src/serial.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/serialcomm.o: src/serialcomm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/serialcomm.o.d 
	@${RM} ${OBJECTDIR}/src/serialcomm.o 
	@${FIXDEPS} "${OBJECTDIR}/src/serialcomm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"include" -I"src" -MMD -MF "${OBJECTDIR}/src/serialcomm.o.d" -o ${OBJECTDIR}/src/serialcomm.o src/serialcomm.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/timers.o: src/timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/timers.o.d 
	@${RM} ${OBJECTDIR}/src/timers.o 
	@${FIXDEPS} "${OBJECTDIR}/src/timers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"include" -I"src" -MMD -MF "${OBJECTDIR}/src/timers.o.d" -o ${OBJECTDIR}/src/timers.o src/timers.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/vars.o: src/vars.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/vars.o.d 
	@${RM} ${OBJECTDIR}/src/vars.o 
	@${FIXDEPS} "${OBJECTDIR}/src/vars.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"include" -I"src" -MMD -MF "${OBJECTDIR}/src/vars.o.d" -o ${OBJECTDIR}/src/vars.o src/vars.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/include/main_lsm.o: include/main_lsm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/include" 
	@${RM} ${OBJECTDIR}/include/main_lsm.o.d 
	@${RM} ${OBJECTDIR}/include/main_lsm.o 
	@${FIXDEPS} "${OBJECTDIR}/include/main_lsm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"include" -I"src" -MMD -MF "${OBJECTDIR}/include/main_lsm.o.d" -o ${OBJECTDIR}/include/main_lsm.o include/main_lsm.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/budgeted_mast_pkg.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g -mdebugger -D__MPLAB_DEBUGGER_PK3=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/budgeted_mast_pkg.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -mreserve=data@0x0:0x1FC -mreserve=boot@0x1FC02000:0x1FC02FEF -mreserve=boot@0x1FC02000:0x1FC024FF  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=__MPLAB_DEBUGGER_PK3=1,--defsym=_min_heap_size=128,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/budgeted_mast_pkg.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/budgeted_mast_pkg.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=128,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/budgeted_mast_pkg.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
