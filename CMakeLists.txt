cmake_minimum_required(VERSION 2.8)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  if(DEFINED ENV{VITASDK})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VITASDK}/share/vita.toolchain.cmake" CACHE PATH "toolchain file")
  else()
    message(FATAL_ERROR "Please define VITASDK to point to your SDK path!")
  endif()
endif()

project(GordonVita004)
include("${VITASDK}/share/vita.cmake" REQUIRED)

set(VITA_APP_NAME "Gordon Vita 004")
set(VITA_TITLEID  "GVITAV004")
set(VITA_VERSION  "13.37")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

add_executable(${PROJECT_NAME}
  src/main.cpp
)

target_link_libraries(${PROJECT_NAME}
  soloud
  pthread
  m
  SceDisplay_stub
  SceCtrl_stub
  SceAudio_stub
  SceRtc_stub
  SceCommonDialog_stub
  vita2d
  png
  ScePgf_stub
  SceGxm_stub
  SceSysmodule_stub
  SceShellSvc_stub
  SceAVConfig_stub
  z
  freetype
)

vita_create_self(eboot.bin ${PROJECT_NAME})
vita_create_vpk(${VITA_TITLEID}.vpk ${VITA_TITLEID} eboot.bin
  VERSION ${VITA_VERSION}
  NAME ${VITA_APP_NAME}
  FILE res/haha.ogg res/haha.ogg
  FILE res/1.png res/1.png
  FILE res/2.png res/2.png
  FILE sce_sys/icon0.png sce_sys/icon0.png
  FILE sce_sys/livearea/contents/bg.png FILE sce_sys/livearea/contents/bg.png
  FILE sce_sys/livearea/contents/startup.png FILE sce_sys/livearea/contents/startup.png
  FILE sce_sys/livearea/contents/template.xml FILE sce_sys/livearea/contents/template.xml
)
