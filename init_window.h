#include <stdint.h>

#include "libavutil/rational.h"

struct wayland_out_env_s;
typedef struct wayland_out_env_s wayland_out_env_t;

#define WOUT_FLAG_FULLSCREEN 1
#define WOUT_FLAG_NO_WAIT    2

struct AVFrame;
struct AVCodecContext;

int egl_wayland_out_get_buffer2(struct AVCodecContext *s, struct AVFrame *frame, int flags);
void egl_wayland_out_modeset(struct wayland_out_env_s * dpo, int w, int h, AVRational frame_rate);
int egl_wayland_out_display(struct wayland_out_env_s * dpo, struct AVFrame * frame);
struct wayland_out_env_s * egl_wayland_out_new(unsigned int flags);
struct wayland_out_env_s * dmabuf_wayland_out_new(unsigned int flags);
void egl_wayland_out_delete(struct wayland_out_env_s * dpo);
void egl_wayland_out_unref(struct wayland_out_env_s ** ppdpo);

struct wo_surface_s;
typedef struct wo_surface_s wo_surface_t;
struct wo_fb_s;
typedef struct wo_fb_s wo_fb_t;

struct dmabuf_h;

typedef struct wo_rect_s {
    int32_t x, y;
    uint32_t w, h;
} wo_rect_t;

wo_surface_t * wo_make_surface(wayland_out_env_t * dpo);
void wo_surface_unref(wo_surface_t ** ppWs);

wo_fb_t * wo_make_fb(wayland_out_env_t * dpo, uint32_t width, uint32_t height, uint32_t fmt, uint64_t mod);
wo_fb_t * wo_fb_ref(wo_fb_t * wfb);
void wo_fb_unref(wo_fb_t ** ppwfb);

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

int wo_surface_attach_fb(wo_surface_t * wsurf, wo_fb_t * wfb, const wo_rect_t dst_pos);
int wo_surface_dettach_fb(wo_surface_t * wsurf);
