/*
 * Copyright (c) 2015 Samsung Electronics Co., Ltd All Rights Reserved
 *
 * Licensed under the Apache License, Version 2.0 (the License);
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <efl_extension.h>

#include "gles_sample.h"
#include "sample/launcher_interface.h"

static Eina_Bool
naviframe_pop_cb(void* data, Elm_Object_Item* it)
{
	LOGI("naviframe_pop_cb");
	appdata_s* ad = (appdata_s *) data;

	/* Let window go to hide state. */
	elm_win_lower(ad->win);

	return EINA_FALSE;
}

static void
win_delete_request_cb(void* data, Evas_Object* obj, void* event_info)
{
	ui_app_exit();
}

static void
create_indicator(appdata_s* ad)
{
	elm_win_conformant_set(ad->win, EINA_TRUE);

	elm_win_indicator_mode_set(ad->win, ELM_WIN_INDICATOR_SHOW);
	//elm_win_indicator_opacity_set(ad->win, ELM_WIN_INDICATOR_TRANSPARENT);
	elm_win_indicator_opacity_set(ad->win, ELM_WIN_INDICATOR_OPAQUE);
}

static Evas_Object*
add_win(const char* name)
{
	Evas_Object* win;

	elm_config_accel_preference_set("opengl");
	win = elm_win_util_standard_add(name, "ComputerGraphicsHW3");

	if (!win)
		return NULL;

	if (elm_win_wm_rotation_supported_get(win))
	{
		int rots[4] = {0, 90, 180, 270};
		elm_win_wm_rotation_available_rotations_set(win, rots, 4);
	}

	evas_object_show(win);

	return win;
}


static void
list_selected_cb(void* data, Evas_Object* obj, void* event_info)
{
	LOGI("list_selected_cb\n");
	Elm_Object_Item* it = (Elm_Object_Item *) event_info;
	elm_list_item_selected_set(it, EINA_FALSE);
}

static void
list_item_select_cb(void* data, Evas_Object* obj, void* event_info)
{
	LOGI("list_item_select_cb: list item selected\n");

	appdata_s* ad = (appdata_s *) data;
	Elm_Object_Item* it = (Elm_Object_Item *) event_info;

	// get the name of the item
	ad->cur_sample_name = elm_object_item_text_get(it);

	// get index of the item
	int cnt = 0;
	Elm_Object_Item* iter = it;
	for (; iter != NULL; iter = elm_list_item_prev(iter))
		cnt++;
	LOGI("Sample num: %d\n", cnt);
	ad->cur_sample_num = cnt;

	// create glview for each menu
	Evas_Object* view = get_sample_view(ad);
	elm_naviframe_item_push(ad->navi, ad->cur_sample_name, NULL, NULL, view, NULL);
}

static Evas_Object*
create_main_list(appdata_s* ad)
{
	Evas_Object* list;

	/* List */
	list = elm_list_add(ad->navi);
	elm_list_mode_set(list, ELM_LIST_COMPRESS);
	evas_object_smart_callback_add(list, "selected", list_selected_cb, NULL);

	/* Main Menu Items Here */
	elm_list_item_append(list, "[HW1]Color Teapot", NULL, NULL, list_item_select_cb, ad);
	elm_list_item_append(list, "[HW2]Fragment Lighting", NULL, NULL, list_item_select_cb, ad);
	elm_list_item_append(list, "[HW3]Normal mapping", NULL, NULL, list_item_select_cb, ad);

	elm_list_go(list);

	return list;
}

static bool
app_create(void* data)
{
    /* Hook to take necessary actions before main event loop starts
     * Initialize UI resources and application's data
     * If this function returns true, the main loop of application starts
     * If this function returns false, the application is terminated. */

	appdata_s* ad = (appdata_s *) data;

	if (!data)
		return false;

	/* Create the window */
	ad->win = add_win(ad->name);

	if (!ad->win)
		return false;

	create_indicator(ad);

	evas_object_smart_callback_add(ad->win, "delete,request", win_delete_request_cb, NULL);

	// add conformant
	ad->conform = elm_conformant_add(ad->win);
	evas_object_size_hint_weight_set(ad->conform, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_win_resize_object_add(ad->win, ad->conform);
	evas_object_show(ad->conform);

	// add navi frame
	ad->navi = elm_naviframe_add(ad->conform);
	eext_object_event_callback_add(ad->navi, EEXT_CALLBACK_BACK, eext_naviframe_back_cb, ad); // back key cb
	evas_object_size_hint_weight_set(ad->navi, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_object_content_set(ad->conform, ad->navi);
	evas_object_show(ad->navi);

	Evas_Object* main_list = create_main_list(ad);
	Elm_Object_Item* navi_item = elm_naviframe_item_push(ad->navi, "ComputerGraphics HW2", NULL, NULL, main_list, NULL);
	elm_naviframe_item_pop_cb_set(navi_item, naviframe_pop_cb, ad);

	evas_object_show(ad->win);

	/* Return true: the main loop will now start running */
	return true;
}

static void
app_control(app_control_h app_control, void* data)
{
	/* Handle the launch request. */
}

static void
app_pause(void* data)
{
	/* Take necessary actions when application becomes invisible. */
}

static void
app_resume(void* data)
{
	/* Take necessary actions when application becomes visible. */
}

static void
app_terminate(void* data)
{
	/* Release all resources. */
	release_loader();
}

int
main(int argc, char* argv[])
{
	appdata_s ad = {NULL,};
	int ret;

	ui_app_lifecycle_callback_s event_callback = {NULL,};

	ad.name = "tizen_gles_sample";

	event_callback.create = app_create;
	event_callback.terminate = app_terminate;
	event_callback.pause = app_pause;
	event_callback.resume = app_resume;
	event_callback.app_control = app_control;

	ret = ui_app_main(argc, argv, &event_callback, &ad);
	if (ret != APP_ERROR_NONE)
	{
		dlog_print(DLOG_ERROR, LOG_TAG, "The application failed to start, and returned %d", ret);
	}

	return ret;
}

