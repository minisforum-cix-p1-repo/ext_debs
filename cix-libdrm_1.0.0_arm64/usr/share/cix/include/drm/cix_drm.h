/*
 * Copyright (C) 2023 Fancy Fang <fancy.fang@cixtech.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * Authors:
 *    Fancy Fang <fancy.fang@cixtech.com>
 */

#ifndef CIX_DRM_H_
#define CIX_DRM_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

struct cix_bo;
struct cix_device;

struct afbc_info {
	uint64_t modifier;
	uint32_t crop_left;
	uint32_t crop_right;
	uint32_t crop_top;
	uint32_t crop_bottom;
};

/* device APIs */
struct cix_device *cix_device_create(void);
int cix_device_parse(struct cix_device *dev, int argc, char **argv);
void cix_device_get_drm_fd(struct cix_device *dev, int *fd);
void cix_device_get_buffer_type(struct cix_device *dev, int *buffer_type);
int cix_device_get_plane_format(struct cix_device *dev,  uint32_t i, uint32_t *format);
int cix_device_get_plane_size(struct cix_device *dev,  uint32_t i, uint32_t *width, uint32_t *height);
int cix_device_get_planes_usage(struct cix_device *dev, uint32_t **planes);
void cix_device_get_pipes(struct cix_device *dev, uint32_t *npipes);
uint32_t cix_device_pipe_has_wb_connector(struct cix_device *dev, uint32_t pipe_id);
int cix_device_pipe_get_wb_info(struct cix_device *dev, uint32_t pipe_id,
		unsigned int *fourcc, unsigned int *width, unsigned int *height);
int cix_device_pipe_set_wb_connector(struct cix_device *dev, uint32_t pipe_id, struct cix_bo *bo);
struct cix_bo *cix_device_pipe_get_wb_bo(struct cix_device *dev, uint32_t pipe_id);
int cix_device_pipe_poll_wb_fence(struct cix_device *dev, uint32_t pipe_id);
int cix_device_close(struct cix_device *dev);

int cix_device_set_mode(struct cix_device *dev);
void cix_device_clear_mode(struct cix_device *dev);
int cix_device_set_plane(struct cix_device *dev, uint32_t plane, struct cix_bo *bo);
void cix_device_clear_planes(struct cix_device *dev);
int cix_device_commit(struct cix_device *dev, uint32_t flags);

/* bo APIs */
int cix_bo_get_fb(struct cix_bo *bo);
struct cix_bo *
cix_bo_new(int fd, uint32_t w, uint32_t h, uint32_t format);
void cix_bo_del(struct cix_bo *bo);
struct cix_bo *
cix_bo_from_dmabuf(int fd, uint32_t width, uint32_t height,	uint32_t format,
			int nfds, int *prime_fds, uint32_t *pPitches,
			uint32_t *pOffsets, uint32_t *pSizes, struct afbc_info *afbc);
int cix_bo_to_dmabuf(struct cix_bo *bo);
void *cix_bo_map(struct cix_bo *bo);
void cix_bo_unmap(struct cix_bo *bo);
int cix_bo_add_fb(int fd, struct cix_bo *bo, uint32_t flags);
struct cix_bo *cix_bo_ref(struct cix_bo *bo);
struct cix_bo *cix_bo_from_name(int fd, uint32_t name);
int cix_bo_get_name(struct cix_bo *bo, uint32_t *name);

#ifdef __cplusplus
}
#endif

#endif
