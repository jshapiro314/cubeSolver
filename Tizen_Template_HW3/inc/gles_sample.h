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

#ifndef __GLES_SAMPLE_H__
#define __GLES_SAMPLE_H__

#include <app.h>
#include <Elementary.h>
#include <dlog.h>

#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "TIZEN_SAMPLE"

#define LOGI(...)  dlog_print(DLOG_INFO,LOG_TAG,__VA_ARGS__)
#define LOGE(...)  dlog_print(DLOG_ERROR,LOG_TAG,__VA_ARGS__)

typedef struct appdata
{
	const char* name;

	Evas_Object* win;
	Evas_Object* conform;
	Evas_Object* navi;

	const char* cur_sample_name;
	int cur_sample_num;

	int glview_w, glview_h;

	Eina_Bool mouse_down :1;
	Eina_Bool initialized :1;
} appdata_s;

#endif /* __GLES_SAMPLE_H__ */

