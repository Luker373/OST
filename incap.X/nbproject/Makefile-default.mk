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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/incap.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/incap.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=
else
COMPARISON_BUILD=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=C:/Users/Joe/Desktop/incap.X/main.c src/Ascii.c src/BOARD.c src/INPUT_CAPTURE.c src/Oled.c src/OledDriver.c src/serial.c src/timers.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/702734782/main.o ${OBJECTDIR}/src/Ascii.o ${OBJECTDIR}/src/BOARD.o ${OBJECTDIR}/src/INPUT_CAPTURE.o ${OBJECTDIR}/src/Oled.o ${OBJECTDIR}/src/OledDriver.o ${OBJECTDIR}/src/serial.o ${OBJECTDIR}/src/timers.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/702734782/main.o.d ${OBJECTDIR}/src/Ascii.o.d ${OBJECTDIR}/src/BOARD.o.d ${OBJECTDIR}/src/INPUT_CAPTURE.o.d ${OBJECTDIR}/src/Oled.o.d ${OBJECTDIR}/src/OledDriver.o.d ${OBJECTDIR}/src/serial.o.d ${OBJECTDIR}/src/timers.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/702734782/main.o ${OBJECTDIR}/src/Ascii.o ${OBJECTDIR}/src/BOARD.o ${OBJECTDIR}/src/INPUT_CAPTURE.o ${OBJECTDIR}/src/Oled.o ${OBJECTDIR}/src/OledDriver.o ${OBJECTDIR}/src/serial.o ${OBJECTDIR}/src/timers.o

# Source Files
SOURCEFILES=C:/Users/Joe/Desktop/incap.X/main.c src/Ascii.c src/BOARD.c src/INPUT_CAPTURE.c src/Oled.c src/OledDriver.c src/serial.c src/timers.c


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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/incap.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

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
${OBJECTDIR}/_ext/702734782/main.o: C:/Users/Joe/Desktop/incap.X/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/702734782" 
	@${RM} ${OBJECTDIR}/_ext/702734782/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/702734782/main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/702734782/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"include" -MMD -MF "${OBJECTDIR}/_ext/702734782/main.o.d" -o ${OBJECTDIR}/_ext/702734782/main.o C:/Users/Joe/Desktop/incap.X/main.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/Ascii.o: src/Ascii.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/Ascii.o.d 
	@${RM} ${OBJECTDIR}/src/Ascii.o 
	@${FIXDEPS} "${OBJECTDIR}/src/Ascii.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"include" -MMD -MF "${OBJECTDIR}/src/Ascii.o.d" -o ${OBJECTDIR}/src/Ascii.o src/Ascii.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/BOARD.o: src/BOARD.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/BOARD.o.d 
	@${RM} ${OBJECTDIR}/src/BOARD.o 
	@${FIXDEPS} "${OBJECTDIR}/src/BOARD.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"include" -MMD -MF "${OBJECTDIR}/src/BOARD.o.d" -o ${OBJECTDIR}/src/BOARD.o src/BOARD.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/INPUT_CAPTURE.o: src/INPUT_CAPTURE.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/INPUT_CAPTURE.o.d 
	@${RM} ${OBJECTDIR}/src/INPUT_CAPTURE.o 
	@${FIXDEPS} "${OBJECTDIR}/src/INPUT_CAPTURE.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"include" -MMD -MF "${OBJECTDIR}/src/INPUT_CAPTURE.o.d" -o ${OBJECTDIR}/src/INPUT_CAPTURE.o src/INPUT_CAPTURE.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/Oled.o: src/Oled.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/Oled.o.d 
	@${RM} ${OBJECTDIR}/src/Oled.o 
	@${FIXDEPS} "${OBJECTDIR}/src/Oled.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"include" -MMD -MF "${OBJECTDIR}/src/Oled.o.d" -o ${OBJECTDIR}/src/Oled.o src/Oled.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/OledDriver.o: src/OledDriver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/OledDriver.o.d 
	@${RM} ${OBJECTDIR}/src/OledDriver.o 
	@${FIXDEPS} "${OBJECTDIR}/src/OledDriver.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"include" -MMD -MF "${OBJECTDIR}/src/OledDriver.o.d" -o ${OBJECTDIR}/src/OledDriver.o src/OledDriver.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/serial.o: src/serial.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/serial.o.d 
	@${RM} ${OBJECTDIR}/src/serial.o 
	@${FIXDEPS} "${OBJECTDIR}/src/serial.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"include" -MMD -MF "${OBJECTDIR}/src/serial.o.d" -o ${OBJECTDIR}/src/serial.o src/serial.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/timers.o: src/timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/timers.o.d 
	@${RM} ${OBJECTDIR}/src/timers.o 
	@${FIXDEPS} "${OBJECTDIR}/src/timers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"include" -MMD -MF "${OBJECTDIR}/src/timers.o.d" -o ${OBJECTDIR}/src/timers.o src/timers.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD) 
	
else
${OBJECTDIR}/_ext/702734782/main.o: C:/Users/Joe/Desktop/incap.X/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/702734782" 
	@${RM} ${OBJECTDIR}/_ext/702734782/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/702734782/main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/702734782/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"include" -MMD -MF "${OBJECTDIR}/_ext/702734782/main.o.d" -o ${OBJECTDIR}/_ext/702734782/main.o C:/Users/Joe/Desktop/incap.X/main.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/Ascii.o: src/Ascii.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/Ascii.o.d 
	@${RM} ${OBJECTDIR}/src/Ascii.o 
	@${FIXDEPS} "${OBJECTDIR}/src/Ascii.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"include" -MMD -MF "${OBJECTDIR}/src/Ascii.o.d" -o ${OBJECTDIR}/src/Ascii.o src/Ascii.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/BOARD.o: src/BOARD.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/BOARD.o.d 
	@${RM} ${OBJECTDIR}/src/BOARD.o 
	@${FIXDEPS} "${OBJECTDIR}/src/BOARD.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"include" -MMD -MF "${OBJECTDIR}/src/BOARD.o.d" -o ${OBJECTDIR}/src/BOARD.o src/BOARD.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/INPUT_CAPTURE.o: src/INPUT_CAPTURE.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/INPUT_CAPTURE.o.d 
	@${RM} ${OBJECTDIR}/src/INPUT_CAPTURE.o 
	@${FIXDEPS} "${OBJECTDIR}/src/INPUT_CAPTURE.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"include" -MMD -MF "${OBJECTDIR}/src/INPUT_CAPTURE.o.d" -o ${OBJECTDIR}/src/INPUT_CAPTURE.o src/INPUT_CAPTURE.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/Oled.o: src/Oled.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/Oled.o.d 
	@${RM} ${OBJECTDIR}/src/Oled.o 
	@${FIXDEPS} "${OBJECTDIR}/src/Oled.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"include" -MMD -MF "${OBJECTDIR}/src/Oled.o.d" -o ${OBJECTDIR}/src/Oled.o src/Oled.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/OledDriver.o: src/OledDriver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/OledDriver.o.d 
	@${RM} ${OBJECTDIR}/src/OledDriver.o 
	@${FIXDEPS} "${OBJECTDIR}/src/OledDriver.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"include" -MMD -MF "${OBJECTDIR}/src/OledDriver.o.d" -o ${OBJECTDIR}/src/OledDriver.o src/OledDriver.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/serial.o: src/serial.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/serial.o.d 
	@${RM} ${OBJECTDIR}/src/serial.o 
	@${FIXDEPS} "${OBJECTDIR}/src/serial.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"include" -MMD -MF "${OBJECTDIR}/src/serial.o.d" -o ${OBJECTDIR}/src/serial.o src/serial.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/timers.o: src/timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/timers.o.d 
	@${RM} ${OBJECTDIR}/src/timers.o 
	@${FIXDEPS} "${OBJECTDIR}/src/timers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"include" -MMD -MF "${OBJECTDIR}/src/timers.o.d" -o ${OBJECTDIR}/src/timers.o src/timers.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD) 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/incap.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mdebugger -D__MPLAB_DEBUGGER_ICD3=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/incap.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)   -mreserve=data@0x0:0x1FC -mreserve=boot@0x1FC02000:0x1FC02FEF -mreserve=boot@0x1FC02000:0x1FC024FF  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_ICD3=1,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/incap.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/incap.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/incap.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
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
