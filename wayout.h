#ifndef _WAYOUT_H
#define _WAYOUT_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

struct wo_surface_s;
typedef struct wo_surface_s wo_surface_t;
struct wo_fb_s;
typedef struct wo_fb_s wo_fb_t;
struct wo_window_s;
typedef struct wo_window_s wo_window_t;
struct wo_env_s
typedef struct wo_env_s wo_env_t;

struct dmabuf_h;
struct wl_display;
struct wl_egl_window;

typedef struct wo_rect_s {
    int32_t x, y;
    uint32_t w, h;
} wo_rect_t;

typedef void (* wo_surface_window_resize_fn)(void * v, wo_surface_t * wos, const wo_rect_t size);

typedef struct wo_surface_fns_s {
    wo_surface_window_resize_fn resize_fn;
} wo_surface_fns_t;

wo_surface_t * wo_make_surface_z(wo_env_t * dpo, const wo_surface_fns_t * fns, unsigned int z);
void wo_surface_unref(wo_surface_t ** ppWs);
wo_surface_t * wo_surface_ref(wo_surface_t * const wos);

wo_fb_t * wo_fb_new_dh(wo_env_t * const woe, const w, const h, uint32_t fmt, uint64_t mod,
             unsigned int objs, struct dmabuf_h ** dhs,
             unsigned int planes, const size_t * offsets, const size_t * strides, const unsigned int * obj_nos);
wo_fb_t * wo_fb_new_rgba_pixel(wo_env_t * const woe, const uint32_t r, const uint32_t g, const uint32_t b, const uint32_t a);
wo_fb_t * wo_make_fb(wo_env_t * dpo, uint32_t width, uint32_t height, uint32_t fmt, uint64_t mod);
wo_fb_t * wo_fb_ref(wo_fb_t * wfb);
void wo_fb_unref(wo_fb_t ** ppwfb);

typedef bool (* wo_fb_pre_delete_fn)(void * v, struct wo_fb_s * wofb);
typedef void (* wo_fb_on_delete_fn)(void * v);

void wo_fb_on_delete_set(wo_fb_t * const wofb, wo_fb_on_delete_fn const fn, void * const v);
void wo_fb_pre_delete_set(wo_fb_t * const wofb, wo_fb_pre_delete_fn const fn, void * const v);
void wo_fb_pre_delete_unset(wo_fb_t * const wofb);

unsigned int wo_fb_width(const wo_fb_t * wfb);
unsigned int wo_fb_height(const wo_fb_t * wfb);
unsigned int wo_fb_pitch(const wo_fb_t * wfb, const unsigned int plane);
void * wo_fb_data(const wo_fb_t * wfb, const unsigned int plane);

void wo_fb_crop_frac_set(wo_fb_t * wfb, const wo_rect_t crop);

void wo_fb_write_start(wo_fb_t * wfb);
void wo_fb_write_end(wo_fb_t * wfb);
void wo_fb_read_start(wo_fb_t * wfb);
void wo_fb_read_end(wo_fb_t * wfb);

int wo_surface_commit(wo_surface_t * wsurf);

int wo_surface_dst_pos_set(wo_surface_t * const wos);
unsigned int wo_surface_dst_width(const wo_surface_t * const wos);
unsigned int wo_surface_dst_height(const wo_surface_t * const wos);
wo_env_t * wo_surface_env(const wo_surface_t * const wos);

int wo_surface_attach_fb(wo_surface_t * wsurf, wo_fb_t * wfb, const wo_rect_t dst_pos);
int wo_surface_detach_fb(wo_surface_t * wsurf);
// make wl_egl_window from surface
struct wl_egl_window * wo_surface_egl_window_create(wo_surface_t * wsurf, const wo_rect_t dst_pos);

// Window size, x,y zero - wayland doesn't admit position
wo_rect_t wo_window_size(const wo_window_t * const wowin);
wo_window_t * wo_window_new(wo_env_t * const woe, bool fullscreen, const wo_rect_t pos, const char * const title);
void wo_window_unref(wo_window_t ** const ppWowin);
wo_window_t * wo_window_ref(wo_window_t * const wowin);
wo_env_t * wo_window_env(const wo_window_t * wowin);

struct wl_display * wo_env_display(const wo_env_t * const woe);

wo_env_t * wo_env_ref(wo_env_t * const woe);
void wo_env_unref(wo_env_t ** const ppWoe);
wo_env_t * wo_env_new_default(void);

#ifdef __cplusplus
}
#endif

#endif
