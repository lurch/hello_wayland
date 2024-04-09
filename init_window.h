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


