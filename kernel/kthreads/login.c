#include <kthreads.h>
#include <util.h>
#include <colors.h>
#include <gfx/gfxlib.h>
#include <gfx/composition.h>
#include <gfx/theme.h>
#include <gfx/window.h>
#include <gfx/events.h>
#include <kutils.h>
#include <vbe.h>


void __kthread_entry login()
{   
    struct window* w = gfx_new_window(275, 100, 0);
    if(w == NULL){
        warningf("Failed to create window for login");
        return;
    }

    /* set title */
    kernel_gfx_set_title("Welcome to RetrOS-32");

    /* put it in the middle of screen based on window size */
    w->ops->move(w, (vbe_info->width - w->width) / 2, (vbe_info->height - w->height) / 2);

    w->draw->rect(w, 0, 0, 275, 100, 30);
    gfx_draw_contoured_box(10, 10, 275-20, 100-20, 30+1);

    /* draw text */
    w->draw->text(w, 10+10, 10+10,  "Welcome to RetrOS", 0x0);
    w->draw->text(w, 10+10, 10+10+10,  "Please login", 0x0);

    /* ok button */
    gfx_button(10+10, 10+10+10+10, 50, 20, "OK");

    /* icon to the right middle 32x32 */
    gfx_put_icon32(275-10-32, 10+20+10+10);

    while (1)
    {
        struct gfx_event event;
			int ret = gfx_event_loop(&event, GFX_EVENT_BLOCKING);
			if(ret == -1) continue;

			switch (event.event){
			case GFX_EVENT_MOUSE:{
                    /* check if OK is clicked x = event.data, y = event.data2 */
                    if(event.data > 10+10 && event.data < 10+10+50 && event.data2 > 10+10+10+10 && event.data2 < 10+10+10+10+20){
                        /* OK is clicked */
                        start("kclock");
                        pid_t taskbar = start("taskbar");
                        if(taskbar <= 0){
                            warningf("Failed to start taskbar");
                        }

                        dbgprintf("Taskbar started with pid: %d\n", taskbar);

                        gfx_set_taskbar(taskbar);
                        return;
                    }
                }				
				break;
			default:
				break;
			}

    }
}
EXPORT_KTHREAD(login);