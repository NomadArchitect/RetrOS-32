/**
 * @file windowserver.c
 * @author Joe Bayer (joexbayer)
 * @brief Windowserver implementation
 * @version 0.1
 * @date 2023-11-12
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <gfx/windowserver.h>
#include <keyboard.h>
#include <gfx/gfxlib.h>
#include <scheduler.h>
#include <gfx/events.h>
#include <memory.h>
#include <fs/fs.h>
#include <vbe.h>

static int ws_init(struct windowserver* ws);
static int ws_add(struct windowserver* ws, struct window* window);
static int ws_remove(struct windowserver* ws, struct window* window);
static int ws_fullscreen(struct windowserver* ws, struct window* window);
static int ws_set_background(struct windowserver* ws, color_t color);
static int ws_set_background_file(struct windowserver* ws, const char* path);
static int ws_draw(struct windowserver* ws);
static int ws_destroy(struct windowserver* ws);

static struct window_server_ops ws_default_ops = {
    .init = ws_init,
    .add = ws_add,
    .remove = ws_remove,
    .fullscreen = ws_fullscreen,
    .set_background = ws_set_background,
    .set_background_file = ws_set_background_file,
    .draw = ws_draw,
    .destroy = ws_destroy
};

static int ws_init(struct windowserver* ws)
{
    ERR_ON_NULL(ws);

    dbgprintf("[WSERVER] Initializing window manager.\n");

    ws->sleep_time = WINDOW_SERVER_SLEEP_TIME;
    ws->_is_fullscreen = false;

    struct windowmanager* wm = wm_new(0);
    if(wm == NULL){
        ws->ops->destroy(ws);
        return -ERROR_ALLOC;
    }
    ws->_wm = wm;
    ws->workspace = 0;


    ws->background = palloc(VBE_SIZE());
    if(ws->background == NULL){
        wm->ops->destroy(wm);
        ws->ops->destroy(ws);
        return -ERROR_ALLOC;
    }

    SET_FlAG(ws->flags, WINDOW_SERVER_INITIALIZED);
    return 0;
}

static int ws_add(struct windowserver* ws, struct window* window)
{
    ERR_ON_NULL(ws);
    ERR_ON_NULL(window);
    WS_VALIDATE(ws);

    if(ws->_wm->ops->add(ws->_wm, window) < 0){
        return -ERROR_OPS_CORRUPTED;
    }

    return 0;
}

static int ws_remove(struct windowserver* ws, struct window* window)
{
    ERR_ON_NULL(ws);
    ERR_ON_NULL(window);
    WS_VALIDATE(ws);

    if(ws->_wm->ops->remove(ws->_wm, window) < 0){
        return -ERROR_OPS_CORRUPTED;
    }

    return 0;
}

static int ws_fullscreen(struct windowserver* ws, struct window* window)
{
    ERR_ON_NULL(ws);
    ERR_ON_NULL(window);
    WS_VALIDATE(ws);

    if(ws->_is_fullscreen){
        
         /* store and backup original window information */
        window->inner_width = window->width-16;
        window->inner_height = window->height-16;

        window->inner = ws->_tmp;
        window->pitch = window->inner_width;
        window->y = 10;
        window->x = 10;

        ws->_is_fullscreen = false;

    } else {
        window->inner_width = vbe_info->width;
        window->inner_height = vbe_info->height;

        /* save old window */
        ws->_tmp = window->inner;

        /* set new window */
        window->inner = ws->_wm->composition_buffer;
        window->pitch = vbe_info->width;

        window->y = 0;
        window->x = 0;

        ws->_is_fullscreen = true;
    }

    return 0;
}

static int ws_set_background(struct windowserver* ws, color_t color)
{
    ERR_ON_NULL(ws);
    WS_VALIDATE(ws);

    memset(ws->background, color, VBE_SIZE());

    return 0;
}

static int ws_set_background_file(struct windowserver* ws, const char* path)
{
    ERR_ON_NULL(ws);
    ERR_ON_NULL(path);
    WS_VALIDATE(ws);

    int originalWidth = 320;   // Original image width
    int originalHeight = 240;  // Original image height
    int targetWidth = vbe_info->width;     // Target screen width
    int targetHeight = vbe_info->height;    // Target screen height

     /* upscale image */
    float scaleX = (float)targetWidth / (float)originalWidth;
    float scaleY = (float)targetHeight / (float)originalHeight;

    ubyte_t* temp = kalloc(320*240);
    if(temp == NULL){
        return -ERROR_ALLOC;
    }

    int ret = fs_load_from_file(path, temp, 320*240);
    if(ret <= 0){
        dbgprintf("[WSERVER] Could not read background file: %d.\n", ret);
        kfree(temp);
        return -ERROR_FILE_NOT_FOUND;
    }

    ubyte_t* temp_window = kalloc(320*240);
    if(temp_window == NULL){
        kfree(temp);
        return -ERROR_ALLOC;
    }

    dbgprintf("[WSERVER] Decoding background file %x.\n", ws->background);

    int out;
    run_length_decode(temp, ret, temp_window, &out);

    for (int i = 0; i < originalWidth; i++){
        for (int j = 0; j < originalHeight; j++){
            // Calculate the position on the screen based on the scaling factors
            int screenX = (int)(i * scaleX);
            int screenY = (int)(j * scaleY);

            // Retrieve the pixel value from the original image
            unsigned char pixelValue = rgb_to_vga(temp_window[j * originalWidth + i]);

            // Set the pixel value on the screen at the calculated position
            for (int x = 0; x < scaleX; x++){
                for (int y = 0; y < scaleY; y++){
                    vesa_put_pixel(ws->background, screenX + x, screenY + y, pixelValue);
                }
            }
        }
    }

    kfree(temp);
    kfree(temp_window);
    return ERROR_OK;
}

static int __ws_key_event(struct windowserver* ws, unsigned char key)
{
    ERR_ON_NULL(ws);
    WS_VALIDATE(ws);


    if(key == 0){return ERROR_OK;}

    switch (key){
    case F4:{
            /* Workspace changes */
            if(ws->taskbar != NULL){
                ws->_wm->ops->remove(ws->_wm, ws->taskbar->gfx_window);
            }

            ws->workspace = (ws->workspace+1)%WM_MAX_WORKSPACES;
            ws->_wm->ops->workspace(ws->_wm, ws->workspace);
            ws->window_changes = 1;
            
            if(ws->taskbar != NULL){
                ws->_wm->ops->add(ws->_wm, ws->taskbar->gfx_window);
            }
        }
        break;
    case F9: {
            /* Maximize current focus windows */
            struct window* w = ws->_wm->windows;
            if(w == NULL){break;}

            w->ops->maximize(w);
            struct gfx_event e = {
                .data = w->inner_width,
                .data2 = w->inner_height,
                .event = GFX_EVENT_RESOLUTION
            };
            gfx_push_event(w, &e);
        }
        break;
    case F10:{
            /* Fullscreen of window current in focus*/
            struct window* w = ws->_wm->windows;

            ws->ops->fullscreen(ws, w);

            struct gfx_event e = {
                .data = w->inner_width,
                .data2 = w->inner_height,
                .event = GFX_EVENT_RESOLUTION
            };
            gfx_push_event(w, &e);
        }
        break;
    case TAB: {
            dbgprintf("[WSERVER] Switching focus.\n");
            ws->_wm->ops->push_back(ws->_wm, ws->_wm->windows);
        }
        break;
    default: {
            /* sends keyboard event to userspace */
            struct gfx_event e = {
                .data = key,
                .event = GFX_EVENT_KEYBOARD
            };
            gfx_push_event(ws->_wm->windows, &e);
        }
        break;
    }

    return 0;
}

static int ws_draw(struct windowserver* ws)
{
    ERR_ON_NULL(ws);
    WS_VALIDATE(ws);
    
    /* get state variables */
    int mouse_changed = mouse_get_event(&ws->m);
    get_current_time(&ws->time);
    ws->window_changes = ws->_wm->ops->changes(ws->_wm);
    unsigned char key = kb_get_char();

    __ws_key_event(ws, key);
    
    if(ws->window_changes && !ws->_is_fullscreen){
        memcpy(ws->_wm->composition_buffer, ws->background, ws->_wm->composition_buffer_size);

        ws->_wm->ops->draw(ws->_wm, ws->_wm->windows);
    }

    /* Move out of this module */
    kernel_yield();

    ENTER_CRITICAL();
    /* Copy buffer over to framebuffer. */
    memcpy((uint8_t*)vbe_info->framebuffer, ws->_wm->composition_buffer, ws->_wm->composition_buffer_size);

    LEAVE_CRITICAL();

    if(mouse_changed){
        /* internal mouse event for windows */
        ws->_wm->ops->mouse_event(ws->_wm, ws->m.x, ws->m.y, ws->m.flags);
    }
    vesa_put_icon16((uint8_t*)vbe_info->framebuffer, ws->m.x, ws->m.y);

    return ERROR_OK;
}

struct windowserver* ws_new()
{
    struct windowserver* ws = (struct windowserver*)kalloc(sizeof(struct windowserver));
    if(ws == NULL){
        return NULL;
    }

    ws->ops = &ws_default_ops;
    kref_init(&ws->_krefs);

    if(ws->ops->init(ws) < 0){
        kfree(ws);
        return NULL;
    }


    kref_get(&ws->_krefs);
    return ws;
}

static int ws_destroy(struct windowserver* ws)
{
    ERR_ON_NULL(ws);
    WS_VALIDATE(ws);

    if(kref_put(&ws->_krefs) > 0){
        return ERROR_OK;
    }

    ws->_wm->ops->destroy(ws->_wm);

    kfree(ws);
    return ERROR_OK;
}