

######################################################################################
### 1) Include the sources
######################################################################################

INCLUDE_DIRECTORIES(${EO_SOURCE_DIR}/src)
INCLUDE_DIRECTORIES(${EO_SOURCE_DIR}/src/ga)
INCLUDE_DIRECTORIES(${EO_SOURCE_DIR}/src/utils)

######################################################################################



######################################################################################
### 2) Specify where CMake can find the libraries
######################################################################################

IF(NOT WIN32 OR CYGWIN)  
  LINK_DIRECTORIES(${EO_BINARY_DIR}/lib)
ENDIF(NOT WIN32 OR CYGWIN)

# especially for Visual Studio
IF(WIN32 AND NOT CYGWIN)  
  	LINK_DIRECTORIES(${EO_BINARY_DIR}\\lib\\${CMAKE_BUILD_TYPE})
ENDIF(WIN32 AND NOT CYGWIN) 

######################################################################################



######################################################################################
### 3) Define your targets
######################################################################################

# no matter what is the OS, hopefully
ADD_EXECUTABLE(FirstBitEA FirstBitEA.cpp) 
ADD_EXECUTABLE(FirstRealEA FirstRealEA.cpp) 
ADD_EXECUTABLE(exercise2.3 exercise2.3.cpp) 

ADD_DEPENDENCIES(FirstBitEA eo eoutils ga)
ADD_DEPENDENCIES(FirstRealEA eo eoutils ga)
ADD_DEPENDENCIES(exercise2.3 eo eoutils ga)
######################################################################################



######################################################################################
### 4) Optionnal
######################################################################################

SET(FIRSTBITEA_VERSION ${GLOBAL_VERSION})
SET_TARGET_PROPERTIES(FirstBitEA PROPERTIES VERSION "${FIRSTBITEA_VERSION}")

SET(FIRSTREALEA_VERSION ${GLOBAL_VERSION})
SET_TARGET_PROPERTIES(FirstRealEA PROPERTIES VERSION "${FIRSTREALEA_VERSION}")

SET(EXERCICE23_VERSION ${GLOBAL_VERSION})
SET_TARGET_PROPERTIES(exercise2.3 PROPERTIES VERSION "${EXERCICE23_VERSION}")
######################################################################################



######################################################################################
### 5) Link the librairies for the targets
######################################################################################

TARGET_LINK_LIBRARIES(FirstBitEA eo eoutils ga)
TARGET_LINK_LIBRARIES(FirstRealEA eo eoutils ga)
TARGET_LINK_LIBRARIES(exercise2.3 eo eoutils ga)

######################################################################################



######################################################################################
### 6) Windows advanced config - especially for Microsoft Visual Studio 8
######################################################################################

  IF(CMAKE_CXX_COMPILER MATCHES cl)
   IF(NOT WITH_SHARED_LIBS)
     IF(CMAKE_GENERATOR STREQUAL "Visual Studio 8 2005")
       SET(CMAKE_CXX_FLAGS "/nologo /W3 /Gy")
       SET(CMAKE_CXX_FLAGS_DEBUG "/MTd /Z7 /Od")
       SET(CMAKE_CXX_FLAGS_RELEASE "/MT /O2")
       SET(CMAKE_CXX_FLAGS_MINSIZEREL "/MT /O2")
       SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO "/MTd /Z7 /Od")
       SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:CONSOLE")
       
     ENDIF(CMAKE_GENERATOR STREQUAL "Visual Studio 8 2005")
   ENDIF(NOT WITH_SHARED_LIBS)
  ENDIF(CMAKE_CXX_COMPILER MATCHES cl)
######################################################################################
