/*
 * Copyright (c) 2014 Samsung Electronics Co., Ltd All Rights Reserved
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

#include <app.h>
#include <Elementary_GL_Helpers.h>
#include <efl_extension.h>
#include "rubikscuge.h"
#include "rubikscuge_utils.h"

ELEMENTARY_GLVIEW_GLOBAL_DEFINE();

const float cube_vertices[] =
{
	-0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f,  0.5f,
	 0.5f, -0.5f,  0.5f,
	 0.5f, -0.5f, -0.5f,
	-0.5f,  0.5f, -0.5f,
	-0.5f,  0.5f,  0.5f,
	 0.5f,  0.5f,  0.5f,
	 0.5f,  0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,
	-0.5f,  0.5f, -0.5f,
	 0.5f,  0.5f, -0.5f,
	 0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,
	 0.5f,  0.5f,  0.5f,
	 0.5f, -0.5f,  0.5f,
	-0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f, -0.5f,
	 0.5f, -0.5f, -0.5f,
	 0.5f, -0.5f,  0.5f,
	 0.5f,  0.5f,  0.5f,
	 0.5f,  0.5f, -0.5f
};

const int cube_indices_count = 36;
const unsigned short cube_indices[] =
{
	 0,  2,  1,
	 0,  3,  2,
	 4,  5,  6,
	 4,  6,  7,
	 8,  9, 10,
	 8, 10, 11,
	12, 15, 14,
	12, 14, 13,
	16, 17, 18,
	16, 18, 19,
	20, 23, 22,
	20, 22, 21
};

const float cube_colors[] =
{
	//white side
	1.0, 1.0, 1.0, 1.0,
	1.0, 1.0, 1.0, 1.0,
	1.0, 1.0, 1.0, 1.0,
	1.0, 1.0, 1.0, 1.0,

	//yellow side
	1.0, 1.0, 0.0, 1.0,
	1.0, 1.0, 0.0, 1.0,
	1.0, 1.0, 0.0, 1.0,
	1.0, 1.0, 0.0, 1.0,

	//blue side
	0.0, 0.0, 1.0, 1.0,
	0.0, 0.0, 1.0, 1.0,
	0.0, 0.0, 1.0, 1.0,
	0.0, 0.0, 1.0, 1.0,

	//green side
	0.0, 1.0, 0.0, 1.0,
	0.0, 1.0, 0.0, 1.0,
	0.0, 1.0, 0.0, 1.0,
	0.0, 1.0, 0.0, 1.0,

	//red side
	1.0, 0.0, 0.0, 1.0,
	1.0, 0.0, 0.0, 1.0,
	1.0, 0.0, 0.0, 1.0,
	1.0, 0.0, 0.0, 1.0,

	//orange side
	1.0, 0.647, 0.0, 1.0,
	1.0, 0.647, 0.0, 1.0,
	1.0, 0.647, 0.0, 1.0,
	1.0, 0.647, 0.0, 1.0
};

/* Vertex Shader Source */
static const char vertex_shader[] =
		"uniform mat4 u_mvpMatrix;\n"
		"attribute vec4 a_position;\n"
		"attribute vec4 a_color;\n"
		"varying vec4 v_color;\n"
		"\n"
		"void main()\n"
		"{\n"
		"    v_color = a_color;\n"
		"    gl_Position = u_mvpMatrix * a_position;\n"
		"}";

/* Fragment Shader Source */
static const char fragment_shader[] =
		"#ifdef GL_ES\n"
		"precision mediump float;\n"
		"#endif\n"
		"varying vec4 v_color;\n"
		"\n"
		"void main (void)\n"
		"{\n"
		"    gl_FragColor = v_color;\n"
		"}";

static void win_back_cb(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s *ad = data;
	/* Let window go to hidden state. */
	elm_win_lower(ad->win);
}

static void init_shaders(Evas_Object *obj)
{
	appdata_s *ad = evas_object_data_get(obj, "ad");
	const char *p;

	p = vertex_shader;
	ad->vtx_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(ad->vtx_shader, 1, &p, NULL);
	glCompileShader(ad->vtx_shader);

	p = fragment_shader;
	ad->fgmt_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(ad->fgmt_shader, 1, &p, NULL);
	glCompileShader(ad->fgmt_shader);

	ad->program = glCreateProgram();
	glAttachShader(ad->program, ad->vtx_shader);
	glAttachShader(ad->program, ad->fgmt_shader);

	glLinkProgram(ad->program);

	ad->idx_position = glGetAttribLocation(ad->program, "a_position");
	ad->idx_color = glGetAttribLocation(ad->program, "a_color");
	ad->idx_mvp = glGetUniformLocation(ad->program, "u_mvpMatrix");

	glUseProgram(ad->program);
}

static void
mouse_down_cb(void *data, Evas *e , Evas_Object *obj , void *event_info)
{
	appdata_s *ad = data;
	ad->mouse_down = EINA_TRUE;
}

static void
mouse_move_cb(void *data, Evas *e , Evas_Object *obj , void *event_info)
{
	Evas_Event_Mouse_Move *ev;
	ev = (Evas_Event_Mouse_Move *)event_info;
	appdata_s *ad = data;
	float dx = 0, dy = 0;

	if(ad->mouse_down) {
		dx = ev->cur.canvas.x - ev->prev.canvas.x;
		dy = ev->cur.canvas.y - ev->prev.canvas.y;
		ad->xangle += dy;
		ad->yangle += dx;
	}
}

static void
mouse_up_cb(void *data, Evas *e , Evas_Object *obj , void *event_info)
{
	appdata_s *ad = data;
	ad->mouse_down = EINA_FALSE;
}

static void resize_gl(Evas_Object *obj)
{
	appdata_s *ad = evas_object_data_get(obj, "ad");

	elm_glview_size_get(obj, &ad->glview_w, &ad->glview_h);
}

static void draw_gl(Evas_Object *obj)
{
	appdata_s *ad = evas_object_data_get(obj, "ad");
	float model[16], view[16];
	float aspect;

	if (!ad)
		return;

	init_matrix(model);
	init_matrix(view);

	aspect = (float) ad->glview_w / (float) ad->glview_h;

	view_set_perspective(view, 60.0f, aspect, 1.0f, 20.0f);

	translate_xyz(model, 0.0f, 0.0f, -2.5f);
	rotate_xyz(model, ad->xangle, ad->yangle, 0.0f);

	multiply_matrix(ad->mvp, view, model);

	glViewport(0, 0, ad->glview_w, ad->glview_h);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glVertexAttribPointer(ad->idx_position, 3, GL_FLOAT, GL_FALSE,
			3 * sizeof(float), cube_vertices);
	glVertexAttribPointer(ad->idx_color, 4, GL_FLOAT, GL_FALSE,
			4 * sizeof(float), cube_colors);

	glEnableVertexAttribArray(ad->idx_position);
	glEnableVertexAttribArray(ad->idx_color);

	glUniformMatrix4fv(ad->idx_mvp, 1, GL_FALSE, ad->mvp);

	glDrawElements(GL_TRIANGLES, cube_indices_count, GL_UNSIGNED_SHORT,
			cube_indices);

	glFlush();

	display_fps();
}

static void init_gl(Evas_Object *obj)
{
	appdata_s *ad = evas_object_data_get(obj, "ad");

	if (!ad->initialized) {
		init_shaders(obj);
		glEnable(GL_DEPTH_TEST);
		ad->initialized = EINA_TRUE;
	}

	ad->xangle = 45.0f;
	ad->yangle = 45.0f;
}

static void del_gl(Evas_Object *obj)
{
	appdata_s *ad = evas_object_data_get(obj, "ad");

	glDeleteShader(ad->vtx_shader);
	glDeleteShader(ad->fgmt_shader);
	glDeleteProgram(ad->program);

	evas_object_data_del((Evas_Object*) obj, "ad");
}

static void del_anim(void *data, Evas *evas, Evas_Object *obj, void *event_info)
{
	appdata_s *ad = data;
	ecore_animator_del(ad->ani);
}

static Eina_Bool anim(void *data)
{
	elm_glview_changed_set(data);
	return EINA_TRUE;
}

static void
win_delete_request_cb(void *data , Evas_Object *obj , void *event_info)
{
	ui_app_exit();
}

static void create_indicator(appdata_s *ad)
{
	elm_win_conformant_set(ad->win, EINA_TRUE);

	elm_win_indicator_mode_set(ad->win, ELM_WIN_INDICATOR_SHOW);
	elm_win_indicator_opacity_set(ad->win, ELM_WIN_INDICATOR_TRANSPARENT);

	ad->conform = elm_conformant_add(ad->win);
	evas_object_size_hint_weight_set(ad->conform, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_win_resize_object_add(ad->win, ad->conform);
	evas_object_show(ad->conform);
}

static Evas_Object* add_win(const char *name)
{
	Evas_Object *win;

	elm_config_accel_preference_set("opengl");
	win = elm_win_util_standard_add(name, "OpenGL example: Cube");

	if (!win)
		return NULL;

	if (elm_win_wm_rotation_supported_get(win)) {
		int rots[4] = { 0, 90, 180, 270 };
		elm_win_wm_rotation_available_rotations_set(win, rots, 4);
	}

	evas_object_show(win);

	return win;
}

static bool app_create(void *data)
{
	/* Hook to take necessary actions before main event loop starts
	 * Initialize UI resources and application's data
	 * If this function returns true, the main loop of application starts
	 * If this function returns false, the application is terminated. */

	Evas_Object *gl;
	appdata_s *ad = data;

	if (!data)
		return false;

	/* Create the window */
	ad->win = add_win(ad->name);

	if (!ad->win)
		return false;

	create_indicator(ad);
	evas_object_smart_callback_add(ad->win, "delete,request", win_delete_request_cb, NULL);
	eext_object_event_callback_add(ad->win, EEXT_CALLBACK_BACK, win_back_cb, ad);

	/* Create and initialize GLView */
	gl = elm_glview_add(ad->conform);
	ELEMENTARY_GLVIEW_GLOBAL_USE(gl);
	evas_object_size_hint_align_set(gl, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_size_hint_weight_set(gl, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

	/* Request a surface with alpha and a depth buffer */
	elm_glview_mode_set(gl, ELM_GLVIEW_DEPTH);

	/* The resize policy tells GLView what to do with the surface when it
	 * resizes. ELM_GLVIEW_RESIZE_POLICY_RECREATE will tell it to
	 * destroy the current surface and recreate it to the new size.
	 */
	elm_glview_resize_policy_set(gl, ELM_GLVIEW_RESIZE_POLICY_RECREATE);

	/* The render policy sets how GLView should render GL code.
	 * ELM_GLVIEW_RENDER_POLICY_ON_DEMAND will have the GL callback
	 * called only when the object is visible.
	 * ELM_GLVIEW_RENDER_POLICY_ALWAYS would cause the callback to be
	 * called even if the object were hidden.
	 */
	elm_glview_render_policy_set(gl, ELM_GLVIEW_RENDER_POLICY_ON_DEMAND);

	/* The initialize callback function gets registered here */
	elm_glview_init_func_set(gl, init_gl);

	/* The delete callback function gets registered here */
	elm_glview_del_func_set(gl, del_gl);

	/* The resize callback function gets registered here */
	elm_glview_resize_func_set(gl, resize_gl);

	/* The render callback function gets registered here */
	elm_glview_render_func_set(gl, draw_gl);

	/* Add the GLView to the conformant and show it */
	elm_object_content_set(ad->conform, gl);
	evas_object_show(gl);

	elm_object_focus_set(gl, EINA_TRUE);

	/* This adds an animator so that the app will regularly
	 * trigger updates of the GLView using elm_glview_changed_set().
	 *
	 * NOTE: If you delete GL, this animator will keep running trying to access
	 * GL so this animator needs to be deleted with ecore_animator_del().
	 */
	ad->ani = ecore_animator_add(anim, gl);
	evas_object_data_set(gl, "ad", ad);
	evas_object_event_callback_add(gl, EVAS_CALLBACK_DEL, del_anim, gl);

	evas_object_event_callback_add(gl, EVAS_CALLBACK_MOUSE_DOWN, mouse_down_cb, ad);
	evas_object_event_callback_add(gl, EVAS_CALLBACK_MOUSE_UP, mouse_up_cb, ad);
	evas_object_event_callback_add(gl, EVAS_CALLBACK_MOUSE_MOVE, mouse_move_cb, ad);

	evas_object_show(ad->win);

	/* Return true: the main loop will now start running */
	return true;
}

static void app_control(app_control_h app_control, void *data)
{
	/* Handle the launch request. */
}

static void app_pause(void *data)
{
	appdata_s *ad = data;
	ecore_animator_freeze(ad->ani);
}

static void app_resume(void *data)
{
	appdata_s *ad = data;
	ecore_animator_thaw(ad->ani);
}

static void app_terminate(void *data)
{
	/* Release all resources. */
}

int main(int argc, char *argv[])
{
	appdata_s ad = { NULL, };
	int ret = 0;

	ui_app_lifecycle_callback_s event_callback = {NULL,};

	ad.name = "rubikscuge";

	event_callback.create = app_create;
	event_callback.terminate = app_terminate;
	event_callback.pause = app_pause;
	event_callback.resume = app_resume;
	event_callback.app_control = app_control;

	ret = ui_app_main(argc, argv, &event_callback, &ad);
	if (ret != APP_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "The application failed to start, and returned %d", ret);
	}

	return ret;
}
