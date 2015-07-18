#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/Behavior.o \
	${OBJECTDIR}/Common.o \
	${OBJECTDIR}/ConfigurationManager.o \
	${OBJECTDIR}/LocalizationManager.o \
	${OBJECTDIR}/Manager.o \
	${OBJECTDIR}/Map.o \
	${OBJECTDIR}/MoveForward.o \
	${OBJECTDIR}/Particle.o \
	${OBJECTDIR}/PathPlanner.o \
	${OBJECTDIR}/Robot.o \
	${OBJECTDIR}/Turn.o \
	${OBJECTDIR}/WaypointsManager.o \
	${OBJECTDIR}/lodepng.o \
	${OBJECTDIR}/main.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-lplayerc++

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/robo

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/robo: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/robo ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/Behavior.o: Behavior.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/local/include/player-2.0 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Behavior.o Behavior.cpp

${OBJECTDIR}/Common.o: Common.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/local/include/player-2.0 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Common.o Common.cpp

${OBJECTDIR}/ConfigurationManager.o: ConfigurationManager.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/local/include/player-2.0 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ConfigurationManager.o ConfigurationManager.cpp

${OBJECTDIR}/LocalizationManager.o: LocalizationManager.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/local/include/player-2.0 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/LocalizationManager.o LocalizationManager.cpp

${OBJECTDIR}/Manager.o: Manager.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/local/include/player-2.0 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Manager.o Manager.cpp

${OBJECTDIR}/Map.o: Map.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/local/include/player-2.0 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Map.o Map.cpp

${OBJECTDIR}/MoveForward.o: MoveForward.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/local/include/player-2.0 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MoveForward.o MoveForward.cpp

${OBJECTDIR}/Particle.o: Particle.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/local/include/player-2.0 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Particle.o Particle.cpp

${OBJECTDIR}/PathPlanner.o: PathPlanner.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/local/include/player-2.0 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/PathPlanner.o PathPlanner.cpp

${OBJECTDIR}/Robot.o: Robot.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/local/include/player-2.0 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Robot.o Robot.cpp

${OBJECTDIR}/Turn.o: Turn.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/local/include/player-2.0 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Turn.o Turn.cpp

${OBJECTDIR}/WaypointsManager.o: WaypointsManager.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/local/include/player-2.0 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/WaypointsManager.o WaypointsManager.cpp

${OBJECTDIR}/lodepng.o: lodepng.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/local/include/player-2.0 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lodepng.o lodepng.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/local/include/player-2.0 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/robo

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
