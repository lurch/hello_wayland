#ifndef CUBE_RUNCUBE_H
#define CUBE_RUNCUBE_H

struct runcube_env_s;
typedef struct runcube_env_s runcube_env_t;

struct wayland_out_env_s;
struct wo_rect_s;

runcube_env_t * runcube_way_start(struct wayland_out_env_s * const woe, const struct wo_rect_s * pos);
void runcube_way_stop(runcube_env_t ** const ppRce);

#endif

