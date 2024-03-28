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

struct wo_surface_s;
typedef struct wo_surface_s wo_surface_t;
struct wo_fb_s;
typedef struct wo_fb_s wo_fb_t;

struct dmabuf_h;

wo_surface_t * wo_make_surface(wayland_out_env_t * dpo);

wo_fb_t * wo_make_fb(wayland_out_env_t * dpo, struct dmabuf_h * dh, uint32_t fmt, uint32_t width, uint32_t height);

int wo_surfece_attach_fb(wo_surface_t * wsurf, wo_fb_t * wfb);
