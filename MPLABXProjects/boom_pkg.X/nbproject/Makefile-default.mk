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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/boom_pkg.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/boom_pkg.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
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
SOURCEFILES_QUOTED_IF_SPACED=../SDPNewPotProgram.X/src/AD.c ../SDPNewPotProgram.X/src/Ascii.c ../SDPNewPotProgram.X/src/BOARD.c ../SDPNewPotProgram.X/src/I2C.c ../SDPNewPotProgram.X/src/Oled.c ../SDPNewPotProgram.X/src/OledDriver.c ../SDPNewPotProgram.X/src/gpsLib.c ../SDPNewPotProgram.X/src/serial.c ../SDPNewPotProgram.X/src/serialcomm.c ../SDPNewPotProgram.X/src/timers.c ../SDPNewPotProgram.X/SDPNewPotProgram.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1907701826/AD.o ${OBJECTDIR}/_ext/1907701826/Ascii.o ${OBJECTDIR}/_ext/1907701826/BOARD.o ${OBJECTDIR}/_ext/1907701826/I2C.o ${OBJECTDIR}/_ext/1907701826/Oled.o ${OBJECTDIR}/_ext/1907701826/OledDriver.o ${OBJECTDIR}/_ext/1907701826/gpsLib.o ${OBJECTDIR}/_ext/1907701826/serial.o ${OBJECTDIR}/_ext/1907701826/serialcomm.o ${OBJECTDIR}/_ext/1907701826/timers.o ${OBJECTDIR}/_ext/1933293335/SDPNewPotProgram.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1907701826/AD.o.d ${OBJECTDIR}/_ext/1907701826/Ascii.o.d ${OBJECTDIR}/_ext/1907701826/BOARD.o.d ${OBJECTDIR}/_ext/1907701826/I2C.o.d ${OBJECTDIR}/_ext/1907701826/Oled.o.d ${OBJECTDIR}/_ext/1907701826/OledDriver.o.d ${OBJECTDIR}/_ext/1907701826/gpsLib.o.d ${OBJECTDIR}/_ext/1907701826/serial.o.d ${OBJECTDIR}/_ext/1907701826/serialcomm.o.d ${OBJECTDIR}/_ext/1907701826/timers.o.d ${OBJECTDIR}/_ext/1933293335/SDPNewPotProgram.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1907701826/AD.o ${OBJECTDIR}/_ext/1907701826/Ascii.o ${OBJECTDIR}/_ext/1907701826/BOARD.o ${OBJECTDIR}/_ext/1907701826/I2C.o ${OBJECTDIR}/_ext/1907701826/Oled.o ${OBJECTDIR}/_ext/1907701826/OledDriver.o ${OBJECTDIR}/_ext/1907701826/gpsLib.o ${OBJECTDIR}/_ext/1907701826/serial.o ${OBJECTDIR}/_ext/1907701826/serialcomm.o ${OBJECTDIR}/_ext/1907701826/timers.o ${OBJECTDIR}/_ext/1933293335/SDPNewPotProgram.o

# Source Files
SOURCEFILES=../SDPNewPotProgram.X/src/AD.c ../SDPNewPotProgram.X/src/Ascii.c ../SDPNewPotProgram.X/src/BOARD.c ../SDPNewPotProgram.X/src/I2C.c ../SDPNewPotProgram.X/src/Oled.c ../SDPNewPotProgram.X/src/OledDriver.c ../SDPNewPotProgram.X/src/gpsLib.c ../SDPNewPotProgram.X/src/serial.c ../SDPNewPotProgram.X/src/serialcomm.c ../SDPNewPotProgram.X/src/timers.c ../SDPNewPotProgram.X/SDPNewPotProgram.c


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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/boom_pkg.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

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
${OBJECTDIR}/_ext/1907701826/AD.o: ../SDPNewPotProgram.X/src/AD.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1907701826" 
	@${RM} ${OBJECTDIR}/_ext/1907701826/AD.o.d 
	@${RM} ${OBJECTDIR}/_ext/1907701826/AD.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1907701826/AD.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"include" -I"src" -MMD -MF "${OBJECTDIR}/_ext/1907701826/AD.o.d" -o ${OBJECTDIR}/_ext/1907701826/AD.o ../SDPNewPotProgram.X/src/AD.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1907701826/Ascii.o: ../SDPNewPotProgram.X/src/Ascii.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1907701826" 
	@${RM} ${OBJECTDIR}/_ext/1907701826/Ascii.o.d 
	@${RM} ${OBJECTDIR}/_ext/1907701826/Ascii.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1907701826/Ascii.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"include" -I"src" -MMD -MF "${OBJECTDIR}/_ext/1907701826/Ascii.o.d" -o ${OBJECTDIR}/_ext/1907701826/Ascii.o ../SDPNewPotProgram.X/src/Ascii.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1907701826/BOARD.o: ../SDPNewPotProgram.X/src/BOARD.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1907701826" 
	@${RM} ${OBJECTDIR}/_ext/1907701826/BOARD.o.d 
	@${RM} ${OBJECTDIR}/_ext/1907701826/BOARD.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1907701826/BOARD.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"include" -I"src" -MMD -MF "${OBJECTDIR}/_ext/1907701826/BOARD.o.d" -o ${OBJECTDIR}/_ext/1907701826/BOARD.o ../SDPNewPotProgram.X/src/BOARD.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1907701826/I2C.o: ../SDPNewPotProgram.X/src/I2C.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1907701826" 
	@${RM} ${OBJECTDIR}/_ext/1907701826/I2C.o.d 
	@${RM} ${OBJECTDIR}/_ext/1907701826/I2C.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1907701826/I2C.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"include" -I"src" -MMD -MF "${OBJECTDIR}/_ext/1907701826/I2C.o.d" -o ${OBJECTDIR}/_ext/1907701826/I2C.o ../SDPNewPotProgram.X/src/I2C.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1907701826/Oled.o: ../SDPNewPotProgram.X/src/Oled.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1907701826" 
	@${RM} ${OBJECTDIR}/_ext/1907701826/Oled.o.d 
	@${RM} ${OBJECTDIR}/_ext/1907701826/Oled.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1907701826/Oled.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"include" -I"src" -MMD -MF "${OBJECTDIR}/_ext/1907701826/Oled.o.d" -o ${OBJECTDIR}/_ext/1907701826/Oled.o ../SDPNewPotProgram.X/src/Oled.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1907701826/OledDriver.o: ../SDPNewPotProgram.X/src/OledDriver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1907701826" 
	@${RM} ${OBJECTDIR}/_ext/1907701826/OledDriver.o.d 
	@${RM} ${OBJECTDIR}/_ext/1907701826/OledDriver.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1907701826/OledDriver.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"include" -I"src" -MMD -MF "${OBJECTDIR}/_ext/1907701826/OledDriver.o.d" -o ${OBJECTDIR}/_ext/1907701826/OledDriver.o ../SDPNewPotProgram.X/src/OledDriver.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1907701826/gpsLib.o: ../SDPNewPotProgram.X/src/gpsLib.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1907701826" 
	@${RM} ${OBJECTDIR}/_ext/1907701826/gpsLib.o.d 
	@${RM} ${OBJECTDIR}/_ext/1907701826/gpsLib.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1907701826/gpsLib.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"include" -I"src" -MMD -MF "${OBJECTDIR}/_ext/1907701826/gpsLib.o.d" -o ${OBJECTDIR}/_ext/1907701826/gpsLib.o ../SDPNewPotProgram.X/src/gpsLib.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1907701826/serial.o: ../SDPNewPotProgram.X/src/serial.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1907701826" 
	@${RM} ${OBJECTDIR}/_ext/1907701826/serial.o.d 
	@${RM} ${OBJECTDIR}/_ext/1907701826/serial.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1907701826/serial.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"include" -I"src" -MMD -MF "${OBJECTDIR}/_ext/1907701826/serial.o.d" -o ${OBJECTDIR}/_ext/1907701826/serial.o ../SDPNewPotProgram.X/src/serial.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1907701826/serialcomm.o: ../SDPNewPotProgram.X/src/serialcomm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1907701826" 
	@${RM} ${OBJECTDIR}/_ext/1907701826/serialcomm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1907701826/serialcomm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1907701826/serialcomm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"include" -I"src" -MMD -MF "${OBJECTDIR}/_ext/1907701826/serialcomm.o.d" -o ${OBJECTDIR}/_ext/1907701826/serialcomm.o ../SDPNewPotProgram.X/src/serialcomm.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1907701826/timers.o: ../SDPNewPotProgram.X/src/timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1907701826" 
	@${RM} ${OBJECTDIR}/_ext/1907701826/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1907701826/timers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1907701826/timers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"include" -I"src" -MMD -MF "${OBJECTDIR}/_ext/1907701826/timers.o.d" -o ${OBJECTDIR}/_ext/1907701826/timers.o ../SDPNewPotProgram.X/src/timers.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1933293335/SDPNewPotProgram.o: ../SDPNewPotProgram.X/SDPNewPotProgram.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1933293335" 
	@${RM} ${OBJECTDIR}/_ext/1933293335/SDPNewPotProgram.o.d 
	@${RM} ${OBJECTDIR}/_ext/1933293335/SDPNewPotProgram.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1933293335/SDPNewPotProgram.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"include" -I"src" -MMD -MF "${OBJECTDIR}/_ext/1933293335/SDPNewPotProgram.o.d" -o ${OBJECTDIR}/_ext/1933293335/SDPNewPotProgram.o ../SDPNewPotProgram.X/SDPNewPotProgram.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
else
${OBJECTDIR}/_ext/1907701826/AD.o: ../SDPNewPotProgram.X/src/AD.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1907701826" 
	@${RM} ${OBJECTDIR}/_ext/1907701826/AD.o.d 
	@${RM} ${OBJECTDIR}/_ext/1907701826/AD.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1907701826/AD.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"include" -I"src" -MMD -MF "${OBJECTDIR}/_ext/1907701826/AD.o.d" -o ${OBJECTDIR}/_ext/1907701826/AD.o ../SDPNewPotProgram.X/src/AD.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1907701826/Ascii.o: ../SDPNewPotProgram.X/src/Ascii.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1907701826" 
	@${RM} ${OBJECTDIR}/_ext/1907701826/Ascii.o.d 
	@${RM} ${OBJECTDIR}/_ext/1907701826/Ascii.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1907701826/Ascii.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"include" -I"src" -MMD -MF "${OBJECTDIR}/_ext/1907701826/Ascii.o.d" -o ${OBJECTDIR}/_ext/1907701826/Ascii.o ../SDPNewPotProgram.X/src/Ascii.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1907701826/BOARD.o: ../SDPNewPotProgram.X/src/BOARD.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1907701826" 
	@${RM} ${OBJECTDIR}/_ext/1907701826/BOARD.o.d 
	@${RM} ${OBJECTDIR}/_ext/1907701826/BOARD.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1907701826/BOARD.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"include" -I"src" -MMD -MF "${OBJECTDIR}/_ext/1907701826/BOARD.o.d" -o ${OBJECTDIR}/_ext/1907701826/BOARD.o ../SDPNewPotProgram.X/src/BOARD.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1907701826/I2C.o: ../SDPNewPotProgram.X/src/I2C.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1907701826" 
	@${RM} ${OBJECTDIR}/_ext/1907701826/I2C.o.d 
	@${RM} ${OBJECTDIR}/_ext/1907701826/I2C.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1907701826/I2C.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"include" -I"src" -MMD -MF "${OBJECTDIR}/_ext/1907701826/I2C.o.d" -o ${OBJECTDIR}/_ext/1907701826/I2C.o ../SDPNewPotProgram.X/src/I2C.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1907701826/Oled.o: ../SDPNewPotProgram.X/src/Oled.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1907701826" 
	@${RM} ${OBJECTDIR}/_ext/1907701826/Oled.o.d 
	@${RM} ${OBJECTDIR}/_ext/1907701826/Oled.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1907701826/Oled.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"include" -I"src" -MMD -MF "${OBJECTDIR}/_ext/1907701826/Oled.o.d" -o ${OBJECTDIR}/_ext/1907701826/Oled.o ../SDPNewPotProgram.X/src/Oled.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1907701826/OledDriver.o: ../SDPNewPotProgram.X/src/OledDriver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1907701826" 
	@${RM} ${OBJECTDIR}/_ext/1907701826/OledDriver.o.d 
	@${RM} ${OBJECTDIR}/_ext/1907701826/OledDriver.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1907701826/OledDriver.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"include" -I"src" -MMD -MF "${OBJECTDIR}/_ext/1907701826/OledDriver.o.d" -o ${OBJECTDIR}/_ext/1907701826/OledDriver.o ../SDPNewPotProgram.X/src/OledDriver.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1907701826/gpsLib.o: ../SDPNewPotProgram.X/src/gpsLib.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1907701826" 
	@${RM} ${OBJECTDIR}/_ext/1907701826/gpsLib.o.d 
	@${RM} ${OBJECTDIR}/_ext/1907701826/gpsLib.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1907701826/gpsLib.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"include" -I"src" -MMD -MF "${OBJECTDIR}/_ext/1907701826/gpsLib.o.d" -o ${OBJECTDIR}/_ext/1907701826/gpsLib.o ../SDPNewPotProgram.X/src/gpsLib.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1907701826/serial.o: ../SDPNewPotProgram.X/src/serial.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1907701826" 
	@${RM} ${OBJECTDIR}/_ext/1907701826/serial.o.d 
	@${RM} ${OBJECTDIR}/_ext/1907701826/serial.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1907701826/serial.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"include" -I"src" -MMD -MF "${OBJECTDIR}/_ext/1907701826/serial.o.d" -o ${OBJECTDIR}/_ext/1907701826/serial.o ../SDPNewPotProgram.X/src/serial.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1907701826/serialcomm.o: ../SDPNewPotProgram.X/src/serialcomm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1907701826" 
	@${RM} ${OBJECTDIR}/_ext/1907701826/serialcomm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1907701826/serialcomm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1907701826/serialcomm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"include" -I"src" -MMD -MF "${OBJECTDIR}/_ext/1907701826/serialcomm.o.d" -o ${OBJECTDIR}/_ext/1907701826/serialcomm.o ../SDPNewPotProgram.X/src/serialcomm.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1907701826/timers.o: ../SDPNewPotProgram.X/src/timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1907701826" 
	@${RM} ${OBJECTDIR}/_ext/1907701826/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1907701826/timers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1907701826/timers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"include" -I"src" -MMD -MF "${OBJECTDIR}/_ext/1907701826/timers.o.d" -o ${OBJECTDIR}/_ext/1907701826/timers.o ../SDPNewPotProgram.X/src/timers.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1933293335/SDPNewPotProgram.o: ../SDPNewPotProgram.X/SDPNewPotProgram.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1933293335" 
	@${RM} ${OBJECTDIR}/_ext/1933293335/SDPNewPotProgram.o.d 
	@${RM} ${OBJECTDIR}/_ext/1933293335/SDPNewPotProgram.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1933293335/SDPNewPotProgram.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"include" -I"src" -MMD -MF "${OBJECTDIR}/_ext/1933293335/SDPNewPotProgram.o.d" -o ${OBJECTDIR}/_ext/1933293335/SDPNewPotProgram.o ../SDPNewPotProgram.X/SDPNewPotProgram.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/boom_pkg.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g -mdebugger -D__MPLAB_DEBUGGER_PK3=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/boom_pkg.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -mreserve=data@0x0:0x1FC -mreserve=boot@0x1FC02000:0x1FC02FEF -mreserve=boot@0x1FC02000:0x1FC024FF  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=__MPLAB_DEBUGGER_PK3=1,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/boom_pkg.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/boom_pkg.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/boom_pkg.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
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
