/*
 * Copyright cMK Contributors
 *
 * SPDX-License-Identifier: MIT
 */

#define DT_DRV_COMPAT zmk_behavior_tri_state

#include <zephyr/device.h>
#include <drivers/behavior.h>
#include <zephyr/logging/log.h>
#include <zmk/behavior.h>
#include <zmk/behavior_queue.h>
#include <zmk/keymap.h>
#include <zmk/matrix.h>
#include <zmk/event_manager.h>
#include <zmk/events/position_state_changed.h>
#include <zmk/events/layer_state_changed.h>
#include <zmk/hid.h>

LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

#define ZMK_BHV_MAX_ACTIVE_TRI_STATES 10

struct behavior_tri_state_config {
    int32_t ignored_key_positions_len;
    int32_t ignored_layers_len;
    struct zmk_behavior_binding start_behavior;
    struct zmk_behavior_binding continue_behavior;
    struct zmk_behavior_binding end_behavior;
    int32_t ignored_layers;
    int32_t timeout_ms;
    int tap_ms;
    uint8_t ignored_key_positions[];
};

struct active_tri_state {
    bool is_active;
    bool is_pressed;
    bool first_press;
    uint32_t position;
    const struct behavior_tri_state_config *config;
    struct k_work_delayable release_timer;
    int64_t release_at;
    bool timer_started;
    bool timer_cancelled;
};

static int stop_timer(struct active_tri_state *tri_state) {
    int timer_cancel_result = k_work_cancel_delayable(&tri_state->release_timer);
    if (timer_cancel_result == -EINPROGRESS) {
        // too late to cancel, we'll let the timer handler clear up.
        tri_state->timer_cancelled = true;
    }
    return timer_cancel_result;
}

static void reset_timer(int32_t timestamp, struct active_tri_state *tri_state) {
    tri_state->release_at = timestamp + tri_state->config->timeout_ms;
    int32_t ms_left = tri_state->release_at - k_uptime_get();
    if (ms_left > 0) {
        k_work_schedule(&tri_state->release_timer, K_MSEC(ms_left));
        LOG_DBG("Successfully reset tri-state timer");
    }
}

void trigger_end_behavior(struct active_tri_state *si) {
    zmk_behavior_queue_add(si->position, si->config->end_behavior, true, si->config->tap_ms);
    zmk_behavior_queue_add(si->position, si->config->end_behavior, false, 0);
}

void behavior_tri_state_timer_handler(struct k_work *item) {
    struct active_tri_state *tri_state = CONTAINER_OF(item, struct active_tri_state, release_timer);
    if (!tri_state->is_active || tri_state->timer_cancelled || tri_state->is_pressed) {
        return;
    }
    LOG_DBG("Tri-state deactivated due to timer");
    tri_state->is_active = false;
    trigger_end_behavior(tri_state);
}

static void clear_tri_state(struct active_tri_state *tri_state) { tri_state->is_active = false; }

struct active_tri_state active_tri_states[ZMK_BHV_MAX_ACTIVE_TRI_STATES] = {};

static struct active_tri_state *find_tri_state(uint32_t position) {
    for (int i = 0; i < ZMK_BHV_MAX_ACTIVE_TRI_STATES; i++) {
        if (active_tri_states[i].position == position && active_tri_states[i].is_active) {
            return &active_tri_states[i];
        }
    }
    return NULL;
}

static int new_tri_state(uint32_t position, const struct behavior_tri_state_config *config,
                         struct active_tri_state **tri_state) {
    for (int i = 0; i < ZMK_BHV_MAX_ACTIVE_TRI_STATES; i++) {
        struct active_tri_state *const ref_tri_state = &active_tri_states[i];
        if (!ref_tri_state->is_active) {
            ref_tri_state->position = position;
            ref_tri_state->config = config;
            ref_tri_state->is_active = true;
            ref_tri_state->is_pressed = false;
            ref_tri_state->first_press = true;
            *tri_state = ref_tri_state;
            return 0;
        }
    }
    return -ENOMEM;
}

static bool is_other_key_ignored(struct active_tri_state *tri_state, int32_t position) {
    for (int i = 0; i < tri_state->config->ignored_key_positions_len; i++) {
        if (tri_state->config->ignored_key_positions[i] == position) {
            return true;
        }
    }
    return false;
}

static bool is_layer_ignored(struct active_tri_state *tri_state, int32_t layer) {
    if ((BIT(layer) & tri_state->config->ignored_layers) != 0U) {
        return true;
    }
    return false;
}

static int on_tri_state_binding_pressed(struct zmk_behavior_binding *binding,
                                        struct zmk_behavior_binding_event event) {
    const struct device *dev = device_get_binding(binding->behavior_dev);
    const struct behavior_tri_state_config *cfg = dev->config;
    struct active_tri_state *tri_state;
    tri_state = find_tri_state(event.position);
    if (tri_state == NULL) {
        if (new_tri_state(event.position, cfg, &tri_state) == -ENOMEM) {
            LOG_ERR("Unable to create new tri_state. Insufficient space in "
                    "active_tri_states[].");
            return ZMK_BEHAVIOR_OPAQUE;
        }
        LOG_DBG("%d created new tri_state", event.position);
    }
    LOG_DBG("%d tri_state pressed", event.position);
    tri_state->is_pressed = true;
    if (tri_state->first_press) {
        behavior_keymap_binding_pressed((struct zmk_behavior_binding *)&cfg->start_behavior, event);
        behavior_keymap_binding_released((struct zmk_behavior_binding *)&cfg->start_behavior,
                                         event);
