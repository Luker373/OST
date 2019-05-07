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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/gpsAnVIMU_bTMaster.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/gpsAnVIMU_bTMaster.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
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
SOURCEFILES_QUOTED_IF_SPACED=C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/src/AD.c C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/src/BOARD.c C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/src/ClosedLoopIntegration.c C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/src/DCM.c C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/src/I2C.c C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/src/INPUT_CAPTURE.c C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/src/LSM9DS1_func.c C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/src/MatrixFunctions.c C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/src/OpenLoopIntegration.c C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/src/gpsLib.c C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/src/serialcomm.c C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/src/timers.c C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/main.c C:/Users/RARogers/sail-trim/MPLAB/bluetoothTest.X/serial.c C:/CMPE167/src/Ascii.c C:/Users/RARogers/MPLABXProjects/gpsAnVane_btMaster.X/src/Oled.c C:/Users/RARogers/MPLABXProjects/gpsAnVane_btMaster.X/src/OledDriver.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/655534661/AD.o ${OBJECTDIR}/_ext/655534661/BOARD.o ${OBJECTDIR}/_ext/655534661/ClosedLoopIntegration.o ${OBJECTDIR}/_ext/655534661/DCM.o ${OBJECTDIR}/_ext/655534661/I2C.o ${OBJECTDIR}/_ext/655534661/INPUT_CAPTURE.o ${OBJECTDIR}/_ext/655534661/LSM9DS1_func.o ${OBJECTDIR}/_ext/655534661/MatrixFunctions.o ${OBJECTDIR}/_ext/655534661/OpenLoopIntegration.o ${OBJECTDIR}/_ext/655534661/gpsLib.o ${OBJECTDIR}/_ext/655534661/serialcomm.o ${OBJECTDIR}/_ext/655534661/timers.o ${OBJECTDIR}/_ext/897091312/main.o ${OBJECTDIR}/_ext/523504707/serial.o ${OBJECTDIR}/_ext/474142844/Ascii.o ${OBJECTDIR}/_ext/41107281/Oled.o ${OBJECTDIR}/_ext/41107281/OledDriver.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/655534661/AD.o.d ${OBJECTDIR}/_ext/655534661/BOARD.o.d ${OBJECTDIR}/_ext/655534661/ClosedLoopIntegration.o.d ${OBJECTDIR}/_ext/655534661/DCM.o.d ${OBJECTDIR}/_ext/655534661/I2C.o.d ${OBJECTDIR}/_ext/655534661/INPUT_CAPTURE.o.d ${OBJECTDIR}/_ext/655534661/LSM9DS1_func.o.d ${OBJECTDIR}/_ext/655534661/MatrixFunctions.o.d ${OBJECTDIR}/_ext/655534661/OpenLoopIntegration.o.d ${OBJECTDIR}/_ext/655534661/gpsLib.o.d ${OBJECTDIR}/_ext/655534661/serialcomm.o.d ${OBJECTDIR}/_ext/655534661/timers.o.d ${OBJECTDIR}/_ext/897091312/main.o.d ${OBJECTDIR}/_ext/523504707/serial.o.d ${OBJECTDIR}/_ext/474142844/Ascii.o.d ${OBJECTDIR}/_ext/41107281/Oled.o.d ${OBJECTDIR}/_ext/41107281/OledDriver.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/655534661/AD.o ${OBJECTDIR}/_ext/655534661/BOARD.o ${OBJECTDIR}/_ext/655534661/ClosedLoopIntegration.o ${OBJECTDIR}/_ext/655534661/DCM.o ${OBJECTDIR}/_ext/655534661/I2C.o ${OBJECTDIR}/_ext/655534661/INPUT_CAPTURE.o ${OBJECTDIR}/_ext/655534661/LSM9DS1_func.o ${OBJECTDIR}/_ext/655534661/MatrixFunctions.o ${OBJECTDIR}/_ext/655534661/OpenLoopIntegration.o ${OBJECTDIR}/_ext/655534661/gpsLib.o ${OBJECTDIR}/_ext/655534661/serialcomm.o ${OBJECTDIR}/_ext/655534661/timers.o ${OBJECTDIR}/_ext/897091312/main.o ${OBJECTDIR}/_ext/523504707/serial.o ${OBJECTDIR}/_ext/474142844/Ascii.o ${OBJECTDIR}/_ext/41107281/Oled.o ${OBJECTDIR}/_ext/41107281/OledDriver.o

# Source Files
SOURCEFILES=C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/src/AD.c C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/src/BOARD.c C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/src/ClosedLoopIntegration.c C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/src/DCM.c C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/src/I2C.c C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/src/INPUT_CAPTURE.c C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/src/LSM9DS1_func.c C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/src/MatrixFunctions.c C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/src/OpenLoopIntegration.c C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/src/gpsLib.c C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/src/serialcomm.c C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/src/timers.c C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/main.c C:/Users/RARogers/sail-trim/MPLAB/bluetoothTest.X/serial.c C:/CMPE167/src/Ascii.c C:/Users/RARogers/MPLABXProjects/gpsAnVane_btMaster.X/src/Oled.c C:/Users/RARogers/MPLABXProjects/gpsAnVane_btMaster.X/src/OledDriver.c


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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/gpsAnVIMU_bTMaster.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX320F128H
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
${OBJECTDIR}/_ext/655534661/AD.o: C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/src/AD.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/655534661" 
	@${RM} ${OBJECTDIR}/_ext/655534661/AD.o.d 
	@${RM} ${OBJECTDIR}/_ext/655534661/AD.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/655534661/AD.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Users/RARogers/sail-trim/MPLAB/gpsAnVane_btMaster.X" -I"C:/CMPE167/include" -I"C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/include" -I"C:/Users/RARogers/sail-trim/MPLAB/bluetoothTest.X" -MMD -MF "${OBJECTDIR}/_ext/655534661/AD.o.d" -o ${OBJECTDIR}/_ext/655534661/AD.o C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/src/AD.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/655534661/BOARD.o: C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/src/BOARD.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/655534661" 
	@${RM} ${OBJECTDIR}/_ext/655534661/BOARD.o.d 
	@${RM} ${OBJECTDIR}/_ext/655534661/BOARD.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/655534661/BOARD.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Users/RARogers/sail-trim/MPLAB/gpsAnVane_btMaster.X" -I"C:/CMPE167/include" -I"C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/include" -I"C:/Users/RARogers/sail-trim/MPLAB/bluetoothTest.X" -MMD -MF "${OBJECTDIR}/_ext/655534661/BOARD.o.d" -o ${OBJECTDIR}/_ext/655534661/BOARD.o C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/src/BOARD.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/655534661/ClosedLoopIntegration.o: C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/src/ClosedLoopIntegration.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/655534661" 
	@${RM} ${OBJECTDIR}/_ext/655534661/ClosedLoopIntegration.o.d 
	@${RM} ${OBJECTDIR}/_ext/655534661/ClosedLoopIntegration.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/655534661/ClosedLoopIntegration.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Users/RARogers/sail-trim/MPLAB/gpsAnVane_btMaster.X" -I"C:/CMPE167/include" -I"C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/include" -I"C:/Users/RARogers/sail-trim/MPLAB/bluetoothTest.X" -MMD -MF "${OBJECTDIR}/_ext/655534661/ClosedLoopIntegration.o.d" -o ${OBJECTDIR}/_ext/655534661/ClosedLoopIntegration.o C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/src/ClosedLoopIntegration.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/655534661/DCM.o: C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/src/DCM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/655534661" 
	@${RM} ${OBJECTDIR}/_ext/655534661/DCM.o.d 
	@${RM} ${OBJECTDIR}/_ext/655534661/DCM.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/655534661/DCM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Users/RARogers/sail-trim/MPLAB/gpsAnVane_btMaster.X" -I"C:/CMPE167/include" -I"C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/include" -I"C:/Users/RARogers/sail-trim/MPLAB/bluetoothTest.X" -MMD -MF "${OBJECTDIR}/_ext/655534661/DCM.o.d" -o ${OBJECTDIR}/_ext/655534661/DCM.o C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/src/DCM.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/655534661/I2C.o: C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/src/I2C.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/655534661" 
	@${RM} ${OBJECTDIR}/_ext/655534661/I2C.o.d 
	@${RM} ${OBJECTDIR}/_ext/655534661/I2C.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/655534661/I2C.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Users/RARogers/sail-trim/MPLAB/gpsAnVane_btMaster.X" -I"C:/CMPE167/include" -I"C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/include" -I"C:/Users/RARogers/sail-trim/MPLAB/bluetoothTest.X" -MMD -MF "${OBJECTDIR}/_ext/655534661/I2C.o.d" -o ${OBJECTDIR}/_ext/655534661/I2C.o C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/src/I2C.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/655534661/INPUT_CAPTURE.o: C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/src/INPUT_CAPTURE.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/655534661" 
	@${RM} ${OBJECTDIR}/_ext/655534661/INPUT_CAPTURE.o.d 
	@${RM} ${OBJECTDIR}/_ext/655534661/INPUT_CAPTURE.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/655534661/INPUT_CAPTURE.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Users/RARogers/sail-trim/MPLAB/gpsAnVane_btMaster.X" -I"C:/CMPE167/include" -I"C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/include" -I"C:/Users/RARogers/sail-trim/MPLAB/bluetoothTest.X" -MMD -MF "${OBJECTDIR}/_ext/655534661/INPUT_CAPTURE.o.d" -o ${OBJECTDIR}/_ext/655534661/INPUT_CAPTURE.o C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/src/INPUT_CAPTURE.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/655534661/LSM9DS1_func.o: C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/src/LSM9DS1_func.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/655534661" 
	@${RM} ${OBJECTDIR}/_ext/655534661/LSM9DS1_func.o.d 
	@${RM} ${OBJECTDIR}/_ext/655534661/LSM9DS1_func.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/655534661/LSM9DS1_func.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Users/RARogers/sail-trim/MPLAB/gpsAnVane_btMaster.X" -I"C:/CMPE167/include" -I"C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/include" -I"C:/Users/RARogers/sail-trim/MPLAB/bluetoothTest.X" -MMD -MF "${OBJECTDIR}/_ext/655534661/LSM9DS1_func.o.d" -o ${OBJECTDIR}/_ext/655534661/LSM9DS1_func.o C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/src/LSM9DS1_func.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/655534661/MatrixFunctions.o: C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/src/MatrixFunctions.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/655534661" 
	@${RM} ${OBJECTDIR}/_ext/655534661/MatrixFunctions.o.d 
	@${RM} ${OBJECTDIR}/_ext/655534661/MatrixFunctions.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/655534661/MatrixFunctions.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Users/RARogers/sail-trim/MPLAB/gpsAnVane_btMaster.X" -I"C:/CMPE167/include" -I"C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/include" -I"C:/Users/RARogers/sail-trim/MPLAB/bluetoothTest.X" -MMD -MF "${OBJECTDIR}/_ext/655534661/MatrixFunctions.o.d" -o ${OBJECTDIR}/_ext/655534661/MatrixFunctions.o C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/src/MatrixFunctions.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/655534661/OpenLoopIntegration.o: C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/src/OpenLoopIntegration.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/655534661" 
	@${RM} ${OBJECTDIR}/_ext/655534661/OpenLoopIntegration.o.d 
	@${RM} ${OBJECTDIR}/_ext/655534661/OpenLoopIntegration.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/655534661/OpenLoopIntegration.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Users/RARogers/sail-trim/MPLAB/gpsAnVane_btMaster.X" -I"C:/CMPE167/include" -I"C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/include" -I"C:/Users/RARogers/sail-trim/MPLAB/bluetoothTest.X" -MMD -MF "${OBJECTDIR}/_ext/655534661/OpenLoopIntegration.o.d" -o ${OBJECTDIR}/_ext/655534661/OpenLoopIntegration.o C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/src/OpenLoopIntegration.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/655534661/gpsLib.o: C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/src/gpsLib.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/655534661" 
	@${RM} ${OBJECTDIR}/_ext/655534661/gpsLib.o.d 
	@${RM} ${OBJECTDIR}/_ext/655534661/gpsLib.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/655534661/gpsLib.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Users/RARogers/sail-trim/MPLAB/gpsAnVane_btMaster.X" -I"C:/CMPE167/include" -I"C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/include" -I"C:/Users/RARogers/sail-trim/MPLAB/bluetoothTest.X" -MMD -MF "${OBJECTDIR}/_ext/655534661/gpsLib.o.d" -o ${OBJECTDIR}/_ext/655534661/gpsLib.o C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/src/gpsLib.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/655534661/serialcomm.o: C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/src/serialcomm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/655534661" 
	@${RM} ${OBJECTDIR}/_ext/655534661/serialcomm.o.d 
	@${RM} ${OBJECTDIR}/_ext/655534661/serialcomm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/655534661/serialcomm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Users/RARogers/sail-trim/MPLAB/gpsAnVane_btMaster.X" -I"C:/CMPE167/include" -I"C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/include" -I"C:/Users/RARogers/sail-trim/MPLAB/bluetoothTest.X" -MMD -MF "${OBJECTDIR}/_ext/655534661/serialcomm.o.d" -o ${OBJECTDIR}/_ext/655534661/serialcomm.o C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/src/serialcomm.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/655534661/timers.o: C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/src/timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/655534661" 
	@${RM} ${OBJECTDIR}/_ext/655534661/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/655534661/timers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/655534661/timers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Users/RARogers/sail-trim/MPLAB/gpsAnVane_btMaster.X" -I"C:/CMPE167/include" -I"C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/include" -I"C:/Users/RARogers/sail-trim/MPLAB/bluetoothTest.X" -MMD -MF "${OBJECTDIR}/_ext/655534661/timers.o.d" -o ${OBJECTDIR}/_ext/655534661/timers.o C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/src/timers.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/897091312/main.o: C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/897091312" 
	@${RM} ${OBJECTDIR}/_ext/897091312/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/897091312/main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/897091312/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Users/RARogers/sail-trim/MPLAB/gpsAnVane_btMaster.X" -I"C:/CMPE167/include" -I"C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/include" -I"C:/Users/RARogers/sail-trim/MPLAB/bluetoothTest.X" -MMD -MF "${OBJECTDIR}/_ext/897091312/main.o.d" -o ${OBJECTDIR}/_ext/897091312/main.o C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/main.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/523504707/serial.o: C:/Users/RARogers/sail-trim/MPLAB/bluetoothTest.X/serial.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/523504707" 
	@${RM} ${OBJECTDIR}/_ext/523504707/serial.o.d 
	@${RM} ${OBJECTDIR}/_ext/523504707/serial.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/523504707/serial.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Users/RARogers/sail-trim/MPLAB/gpsAnVane_btMaster.X" -I"C:/CMPE167/include" -I"C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/include" -I"C:/Users/RARogers/sail-trim/MPLAB/bluetoothTest.X" -MMD -MF "${OBJECTDIR}/_ext/523504707/serial.o.d" -o ${OBJECTDIR}/_ext/523504707/serial.o C:/Users/RARogers/sail-trim/MPLAB/bluetoothTest.X/serial.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/474142844/Ascii.o: C:/CMPE167/src/Ascii.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/474142844" 
	@${RM} ${OBJECTDIR}/_ext/474142844/Ascii.o.d 
	@${RM} ${OBJECTDIR}/_ext/474142844/Ascii.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/474142844/Ascii.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Users/RARogers/sail-trim/MPLAB/gpsAnVane_btMaster.X" -I"C:/CMPE167/include" -I"C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/include" -I"C:/Users/RARogers/sail-trim/MPLAB/bluetoothTest.X" -MMD -MF "${OBJECTDIR}/_ext/474142844/Ascii.o.d" -o ${OBJECTDIR}/_ext/474142844/Ascii.o C:/CMPE167/src/Ascii.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/41107281/Oled.o: C:/Users/RARogers/MPLABXProjects/gpsAnVane_btMaster.X/src/Oled.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/41107281" 
	@${RM} ${OBJECTDIR}/_ext/41107281/Oled.o.d 
	@${RM} ${OBJECTDIR}/_ext/41107281/Oled.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/41107281/Oled.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Users/RARogers/sail-trim/MPLAB/gpsAnVane_btMaster.X" -I"C:/CMPE167/include" -I"C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/include" -I"C:/Users/RARogers/sail-trim/MPLAB/bluetoothTest.X" -MMD -MF "${OBJECTDIR}/_ext/41107281/Oled.o.d" -o ${OBJECTDIR}/_ext/41107281/Oled.o C:/Users/RARogers/MPLABXProjects/gpsAnVane_btMaster.X/src/Oled.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/41107281/OledDriver.o: C:/Users/RARogers/MPLABXProjects/gpsAnVane_btMaster.X/src/OledDriver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/41107281" 
	@${RM} ${OBJECTDIR}/_ext/41107281/OledDriver.o.d 
	@${RM} ${OBJECTDIR}/_ext/41107281/OledDriver.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/41107281/OledDriver.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Users/RARogers/sail-trim/MPLAB/gpsAnVane_btMaster.X" -I"C:/CMPE167/include" -I"C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/include" -I"C:/Users/RARogers/sail-trim/MPLAB/bluetoothTest.X" -MMD -MF "${OBJECTDIR}/_ext/41107281/OledDriver.o.d" -o ${OBJECTDIR}/_ext/41107281/OledDriver.o C:/Users/RARogers/MPLABXProjects/gpsAnVane_btMaster.X/src/OledDriver.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
else
${OBJECTDIR}/_ext/655534661/AD.o: C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/src/AD.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/655534661" 
	@${RM} ${OBJECTDIR}/_ext/655534661/AD.o.d 
	@${RM} ${OBJECTDIR}/_ext/655534661/AD.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/655534661/AD.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Users/RARogers/sail-trim/MPLAB/gpsAnVane_btMaster.X" -I"C:/CMPE167/include" -I"C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/include" -I"C:/Users/RARogers/sail-trim/MPLAB/bluetoothTest.X" -MMD -MF "${OBJECTDIR}/_ext/655534661/AD.o.d" -o ${OBJECTDIR}/_ext/655534661/AD.o C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/src/AD.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/655534661/BOARD.o: C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/src/BOARD.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/655534661" 
	@${RM} ${OBJECTDIR}/_ext/655534661/BOARD.o.d 
	@${RM} ${OBJECTDIR}/_ext/655534661/BOARD.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/655534661/BOARD.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Users/RARogers/sail-trim/MPLAB/gpsAnVane_btMaster.X" -I"C:/CMPE167/include" -I"C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/include" -I"C:/Users/RARogers/sail-trim/MPLAB/bluetoothTest.X" -MMD -MF "${OBJECTDIR}/_ext/655534661/BOARD.o.d" -o ${OBJECTDIR}/_ext/655534661/BOARD.o C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/src/BOARD.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/655534661/ClosedLoopIntegration.o: C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/src/ClosedLoopIntegration.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/655534661" 
	@${RM} ${OBJECTDIR}/_ext/655534661/ClosedLoopIntegration.o.d 
	@${RM} ${OBJECTDIR}/_ext/655534661/ClosedLoopIntegration.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/655534661/ClosedLoopIntegration.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Users/RARogers/sail-trim/MPLAB/gpsAnVane_btMaster.X" -I"C:/CMPE167/include" -I"C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/include" -I"C:/Users/RARogers/sail-trim/MPLAB/bluetoothTest.X" -MMD -MF "${OBJECTDIR}/_ext/655534661/ClosedLoopIntegration.o.d" -o ${OBJECTDIR}/_ext/655534661/ClosedLoopIntegration.o C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/src/ClosedLoopIntegration.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/655534661/DCM.o: C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/src/DCM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/655534661" 
	@${RM} ${OBJECTDIR}/_ext/655534661/DCM.o.d 
	@${RM} ${OBJECTDIR}/_ext/655534661/DCM.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/655534661/DCM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Users/RARogers/sail-trim/MPLAB/gpsAnVane_btMaster.X" -I"C:/CMPE167/include" -I"C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/include" -I"C:/Users/RARogers/sail-trim/MPLAB/bluetoothTest.X" -MMD -MF "${OBJECTDIR}/_ext/655534661/DCM.o.d" -o ${OBJECTDIR}/_ext/655534661/DCM.o C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/src/DCM.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/655534661/I2C.o: C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/src/I2C.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/655534661" 
	@${RM} ${OBJECTDIR}/_ext/655534661/I2C.o.d 
	@${RM} ${OBJECTDIR}/_ext/655534661/I2C.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/655534661/I2C.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Users/RARogers/sail-trim/MPLAB/gpsAnVane_btMaster.X" -I"C:/CMPE167/include" -I"C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/include" -I"C:/Users/RARogers/sail-trim/MPLAB/bluetoothTest.X" -MMD -MF "${OBJECTDIR}/_ext/655534661/I2C.o.d" -o ${OBJECTDIR}/_ext/655534661/I2C.o C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/src/I2C.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/655534661/INPUT_CAPTURE.o: C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/src/INPUT_CAPTURE.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/655534661" 
	@${RM} ${OBJECTDIR}/_ext/655534661/INPUT_CAPTURE.o.d 
	@${RM} ${OBJECTDIR}/_ext/655534661/INPUT_CAPTURE.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/655534661/INPUT_CAPTURE.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Users/RARogers/sail-trim/MPLAB/gpsAnVane_btMaster.X" -I"C:/CMPE167/include" -I"C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/include" -I"C:/Users/RARogers/sail-trim/MPLAB/bluetoothTest.X" -MMD -MF "${OBJECTDIR}/_ext/655534661/INPUT_CAPTURE.o.d" -o ${OBJECTDIR}/_ext/655534661/INPUT_CAPTURE.o C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/src/INPUT_CAPTURE.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/655534661/LSM9DS1_func.o: C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/src/LSM9DS1_func.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/655534661" 
	@${RM} ${OBJECTDIR}/_ext/655534661/LSM9DS1_func.o.d 
	@${RM} ${OBJECTDIR}/_ext/655534661/LSM9DS1_func.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/655534661/LSM9DS1_func.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Users/RARogers/sail-trim/MPLAB/gpsAnVane_btMaster.X" -I"C:/CMPE167/include" -I"C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/include" -I"C:/Users/RARogers/sail-trim/MPLAB/bluetoothTest.X" -MMD -MF "${OBJECTDIR}/_ext/655534661/LSM9DS1_func.o.d" -o ${OBJECTDIR}/_ext/655534661/LSM9DS1_func.o C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/src/LSM9DS1_func.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/655534661/MatrixFunctions.o: C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/src/MatrixFunctions.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/655534661" 
	@${RM} ${OBJECTDIR}/_ext/655534661/MatrixFunctions.o.d 
	@${RM} ${OBJECTDIR}/_ext/655534661/MatrixFunctions.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/655534661/MatrixFunctions.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Users/RARogers/sail-trim/MPLAB/gpsAnVane_btMaster.X" -I"C:/CMPE167/include" -I"C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/include" -I"C:/Users/RARogers/sail-trim/MPLAB/bluetoothTest.X" -MMD -MF "${OBJECTDIR}/_ext/655534661/MatrixFunctions.o.d" -o ${OBJECTDIR}/_ext/655534661/MatrixFunctions.o C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/src/MatrixFunctions.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/655534661/OpenLoopIntegration.o: C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/src/OpenLoopIntegration.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/655534661" 
	@${RM} ${OBJECTDIR}/_ext/655534661/OpenLoopIntegration.o.d 
	@${RM} ${OBJECTDIR}/_ext/655534661/OpenLoopIntegration.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/655534661/OpenLoopIntegration.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Users/RARogers/sail-trim/MPLAB/gpsAnVane_btMaster.X" -I"C:/CMPE167/include" -I"C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/include" -I"C:/Users/RARogers/sail-trim/MPLAB/bluetoothTest.X" -MMD -MF "${OBJECTDIR}/_ext/655534661/OpenLoopIntegration.o.d" -o ${OBJECTDIR}/_ext/655534661/OpenLoopIntegration.o C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/src/OpenLoopIntegration.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/655534661/gpsLib.o: C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/src/gpsLib.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/655534661" 
	@${RM} ${OBJECTDIR}/_ext/655534661/gpsLib.o.d 
	@${RM} ${OBJECTDIR}/_ext/655534661/gpsLib.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/655534661/gpsLib.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Users/RARogers/sail-trim/MPLAB/gpsAnVane_btMaster.X" -I"C:/CMPE167/include" -I"C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/include" -I"C:/Users/RARogers/sail-trim/MPLAB/bluetoothTest.X" -MMD -MF "${OBJECTDIR}/_ext/655534661/gpsLib.o.d" -o ${OBJECTDIR}/_ext/655534661/gpsLib.o C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/src/gpsLib.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/655534661/serialcomm.o: C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/src/serialcomm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/655534661" 
	@${RM} ${OBJECTDIR}/_ext/655534661/serialcomm.o.d 
	@${RM} ${OBJECTDIR}/_ext/655534661/serialcomm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/655534661/serialcomm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Users/RARogers/sail-trim/MPLAB/gpsAnVane_btMaster.X" -I"C:/CMPE167/include" -I"C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/include" -I"C:/Users/RARogers/sail-trim/MPLAB/bluetoothTest.X" -MMD -MF "${OBJECTDIR}/_ext/655534661/serialcomm.o.d" -o ${OBJECTDIR}/_ext/655534661/serialcomm.o C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/src/serialcomm.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/655534661/timers.o: C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/src/timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/655534661" 
	@${RM} ${OBJECTDIR}/_ext/655534661/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/655534661/timers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/655534661/timers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Users/RARogers/sail-trim/MPLAB/gpsAnVane_btMaster.X" -I"C:/CMPE167/include" -I"C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/include" -I"C:/Users/RARogers/sail-trim/MPLAB/bluetoothTest.X" -MMD -MF "${OBJECTDIR}/_ext/655534661/timers.o.d" -o ${OBJECTDIR}/_ext/655534661/timers.o C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/src/timers.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/897091312/main.o: C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/897091312" 
	@${RM} ${OBJECTDIR}/_ext/897091312/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/897091312/main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/897091312/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Users/RARogers/sail-trim/MPLAB/gpsAnVane_btMaster.X" -I"C:/CMPE167/include" -I"C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/include" -I"C:/Users/RARogers/sail-trim/MPLAB/bluetoothTest.X" -MMD -MF "${OBJECTDIR}/_ext/897091312/main.o.d" -o ${OBJECTDIR}/_ext/897091312/main.o C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/main.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/523504707/serial.o: C:/Users/RARogers/sail-trim/MPLAB/bluetoothTest.X/serial.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/523504707" 
	@${RM} ${OBJECTDIR}/_ext/523504707/serial.o.d 
	@${RM} ${OBJECTDIR}/_ext/523504707/serial.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/523504707/serial.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Users/RARogers/sail-trim/MPLAB/gpsAnVane_btMaster.X" -I"C:/CMPE167/include" -I"C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/include" -I"C:/Users/RARogers/sail-trim/MPLAB/bluetoothTest.X" -MMD -MF "${OBJECTDIR}/_ext/523504707/serial.o.d" -o ${OBJECTDIR}/_ext/523504707/serial.o C:/Users/RARogers/sail-trim/MPLAB/bluetoothTest.X/serial.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/474142844/Ascii.o: C:/CMPE167/src/Ascii.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/474142844" 
	@${RM} ${OBJECTDIR}/_ext/474142844/Ascii.o.d 
	@${RM} ${OBJECTDIR}/_ext/474142844/Ascii.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/474142844/Ascii.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Users/RARogers/sail-trim/MPLAB/gpsAnVane_btMaster.X" -I"C:/CMPE167/include" -I"C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/include" -I"C:/Users/RARogers/sail-trim/MPLAB/bluetoothTest.X" -MMD -MF "${OBJECTDIR}/_ext/474142844/Ascii.o.d" -o ${OBJECTDIR}/_ext/474142844/Ascii.o C:/CMPE167/src/Ascii.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/41107281/Oled.o: C:/Users/RARogers/MPLABXProjects/gpsAnVane_btMaster.X/src/Oled.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/41107281" 
	@${RM} ${OBJECTDIR}/_ext/41107281/Oled.o.d 
	@${RM} ${OBJECTDIR}/_ext/41107281/Oled.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/41107281/Oled.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Users/RARogers/sail-trim/MPLAB/gpsAnVane_btMaster.X" -I"C:/CMPE167/include" -I"C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/include" -I"C:/Users/RARogers/sail-trim/MPLAB/bluetoothTest.X" -MMD -MF "${OBJECTDIR}/_ext/41107281/Oled.o.d" -o ${OBJECTDIR}/_ext/41107281/Oled.o C:/Users/RARogers/MPLABXProjects/gpsAnVane_btMaster.X/src/Oled.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/41107281/OledDriver.o: C:/Users/RARogers/MPLABXProjects/gpsAnVane_btMaster.X/src/OledDriver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/41107281" 
	@${RM} ${OBJECTDIR}/_ext/41107281/OledDriver.o.d 
	@${RM} ${OBJECTDIR}/_ext/41107281/OledDriver.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/41107281/OledDriver.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/Users/RARogers/sail-trim/MPLAB/gpsAnVane_btMaster.X" -I"C:/CMPE167/include" -I"C:/Users/RARogers/sail-trim/MPLABXProjects/gpsAnVIMU_bTMaster.X/include" -I"C:/Users/RARogers/sail-trim/MPLAB/bluetoothTest.X" -MMD -MF "${OBJECTDIR}/_ext/41107281/OledDriver.o.d" -o ${OBJECTDIR}/_ext/41107281/OledDriver.o C:/Users/RARogers/MPLABXProjects/gpsAnVane_btMaster.X/src/OledDriver.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/gpsAnVIMU_bTMaster.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g -mdebugger -D__MPLAB_DEBUGGER_PK3=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/gpsAnVIMU_bTMaster.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -mreserve=data@0x0:0x1FC -mreserve=boot@0x1FC02000:0x1FC02FEF -mreserve=boot@0x1FC02000:0x1FC024FF  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=__MPLAB_DEBUGGER_PK3=1,--defsym=_min_heap_size=200,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/gpsAnVIMU_bTMaster.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/gpsAnVIMU_bTMaster.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=200,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/gpsAnVIMU_bTMaster.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
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