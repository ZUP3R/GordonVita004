#include <stdint.h>
#include <math.h>

#include <psp2/avconfig.h>
#include <psp2/ctrl.h>
#include <psp2/audioout.h>
#include <psp2/kernel/processmgr.h>
#include <psp2/kernel/threadmgr.h>
#include <psp2/power.h>
#include <psp2/rtc.h>
#include <psp2/shellutil.h>

#include "soloud.h"
#include "soloud_wav.h"
#include "soloud_speech.h"

#include <vita2d.h>

SoLoud::Soloud gSoloud;
SoLoud::Wav gWave;
volatile int toggle = 0;

uint64_t tick()
{
    SceRtcTick tiq;
    sceRtcGetCurrentTick(&tiq);
    return tiq.tick;
}

int main(int argc, char *argv[]) 
{
    sceShellUtilInitEvents(0);
    sceShellUtilLock(SCE_SHELL_UTIL_LOCK_TYPE_PS_BTN);

    vita2d_init();

    gSoloud.init();
    gWave.load("app0:/res/haha.ogg");
    gWave.setLooping(true);
    gSoloud.play(gWave);
    
    vita2d_texture *_1 = vita2d_load_PNG_file("app0:res/1.png");
    vita2d_texture *_2 = vita2d_load_PNG_file("app0:res/2.png");
    
    uint64_t t = 0;

	for(;;) {
        sceKernelPowerTick(SCE_KERNEL_POWER_TICK_DEFAULT);

        if(!t)
            t = tick();

        if((t + 400000) < tick()) {
            t = 0;
            toggle = !toggle;
        }
        
        vita2d_set_clear_color(toggle == 0 ? 0xFFFFFFFF : 0xFF000000);
        vita2d_start_drawing();
        vita2d_clear_screen();

        sceAVConfigSetSystemVol(30);

        int brightness = 0xFFFF;
        sceAVConfigGetDisplayMaxBrightness(&brightness);
        sceAVConfigSetDisplayBrightness(brightness);
       
        SceCtrlData pad;
        sceCtrlPeekBufferPositive(0, &pad, 1);
        if(pad.buttons == (SCE_CTRL_LTRIGGER | SCE_CTRL_RTRIGGER | SCE_CTRL_CROSS))
            sceShellUtilUnlock(SCE_SHELL_UTIL_LOCK_TYPE_PS_BTN);
        
        
        vita2d_texture *now = toggle == 0 ? _1 : _2;
        if(now)
            vita2d_draw_texture(now, 960/2 - 870/2, 0);
        
        vita2d_end_drawing();
        vita2d_swap_buffers();
	}

    vita2d_fini();
    vita2d_free_texture(_1);
    vita2d_free_texture(_2);

	sceKernelExitProcess(0);
	return 0;
}
