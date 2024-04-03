#include "runcube.h"

#include <pthread.h>
#include <string.h>
#include <stdatomic.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

#include "common.h"
#include <init_window.h>

struct runcube_env_s {
    atomic_int kill;
    wayland_out_env_t * woe;
    wo_rect_t pos;
    unsigned int run_no;
    bool thread_ok;
    pthread_t thread_id;
};

void cube_run(runcube_env_t * const rce, const struct egl * const egl)
{
    egl->draw(rce->run_no++);
    eglSwapBuffers(egl->display, egl->surface);

    usleep(20000);
}

static void *
cube_thread(void * v)
{
    runcube_env_t * const rce = v;
    const struct egl *egl;
    wo_surface_t * wsurf = wo_make_surface_z(rce->woe, 30);

    egl = init_cube_smooth(wo_env_display(rce->woe), wo_surface_egl_window_create(wsurf, rce->pos), rce->pos.w, rce->pos.h, 0);

    while (!atomic_load(&rce->kill)) {
        cube_run(rce, egl);
    }

    // ***** Should have cleanup here but cube demo doesn't bother

    return NULL;
}

runcube_env_t *
runcube_way_start(wayland_out_env_t * const woe, const wo_rect_t * pos)
{
    runcube_env_t * rce = calloc(1, sizeof(*rce));

    if (rce == NULL)
        return NULL;

    rce->woe = wo_env_ref(woe);
    rce->pos = *pos;
    if (pthread_create(&rce->thread_id, NULL, cube_thread, rce) != 0)
        goto fail;
    rce->thread_ok = true;

    return rce;

fail:
    runcube_way_stop(&rce);
    return NULL;
}

void
runcube_way_stop(runcube_env_t ** const ppRce)
{
    runcube_env_t * const rce = *ppRce;
    if (rce == NULL)
        return;
    *ppRce = NULL;

    if (rce->thread_ok) {
        atomic_store(&rce->kill, 1);
        pthread_join(rce->thread_id, NULL);
    }

    free(rce);
}

