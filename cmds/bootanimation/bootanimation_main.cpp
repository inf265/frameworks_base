/*
 * Copyright (C) 2007 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define LOG_TAG "BootAnimation"

#include <cutils/properties.h>

#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>

#include <utils/Log.h>
#include <utils/threads.h>

#if defined(HAVE_PTHREADS)
# include <pthread.h>
# include <sys/resource.h>
#endif

#include "BootAnimation.h"

using namespace android;

// ---------------------------------------------------------------------------

int main(int argc, char** argv)
{
    ALOGI("boot_animation_process start  000, built at '%s', on '%s'.", __TIME__, __DATE__);

#if defined(HAVE_PTHREADS)
    setpriority(PRIO_PROCESS, 0, ANDROID_PRIORITY_DISPLAY);
#endif

    char value[PROPERTY_VALUE_MAX];
    property_get("debug.sf.nobootanimation", value, "0");
    int noBootAnimation = atoi(value);
   // ALOGI( "boot animation disabled  noBootAnimation===%d",noBootAnimation);
    if (!noBootAnimation) {

        sp<ProcessState> proc(ProcessState::self());
        ProcessState::self()->startThreadPool();
 ALOGI("boot_animation_process 000000000000000===%s",argv[1]);
        // create the boot animation object
	sp<BootAnimation> boot ;
        if (argc > 1) {
            if (strcmp(argv[1], "shutdown") == 0) {
		     boot = new BootAnimation(true);
		     boot->isShutdown(true);
		  //   ALOGI("boot_animation_process 111111111111111");
            }
        }else {
		boot = new BootAnimation(false);
		//ALOGI("boot_animation_process 22222222222222222");
	}
        IPCThreadState::self()->joinThreadPool();

    }
    return 0;
}
