#include "gles_sample.h"
#include "sample/sample_view.h"

ELEMENTARY_GLVIEW_GLOBAL_DEFINE()

SampleView::SampleView(void* data) :
	mGLView(NULL),
	mViewRenderer(NULL)
{
	mGLView = CreateView(data);
	mViewRenderer = new BasicRenderer();

}

SampleView::~SampleView()
{
	Release();
}

void SampleView::Release()
{
	if (mViewRenderer)
	{
		delete mViewRenderer;
		mViewRenderer = NULL;
	}
}

static void
mouse_down_cb(void* data, Evas* e, Evas_Object* obj, void* event_info)
{
	LOGI("mouse_down_cb: touch on\n");
	appdata_s* ad = static_cast<appdata_s *>(evas_object_data_get(obj, "ad"));
	SampleView* sv = static_cast<SampleView *>(evas_object_data_get(obj, "sv"));
	Evas_Event_Mouse_Down* ev = static_cast<Evas_Event_Mouse_Down *>(event_info);

	sv->TouchOn();
	LOGI("Touch Point (x,y): (%d,%d)\n", ev->canvas.x, ev->canvas.y);
	sv->SetTouchPoint(static_cast<float>(ev->canvas.x), static_cast<float>(ev->canvas.y));

	ad->mouse_down = EINA_TRUE;
}

static void
mouse_move_cb(void* data, Evas* e, Evas_Object* obj, void* event_info)
{
	LOGI("mouse_move_cb: touch move\n");
	SampleView* sv = static_cast<SampleView *>(evas_object_data_get(obj, "sv"));
	Evas_Event_Mouse_Move* ev = static_cast<Evas_Event_Mouse_Move *>(event_info);

	LOGI("Touch Point (x,y): (%d,%d)\n", ev->cur.canvas.x, ev->cur.canvas.y);
	sv->SetTouchPoint(static_cast<float>(ev->cur.canvas.x), static_cast<float>(ev->cur.canvas.y));
}

static void
mouse_up_cb(void* data, Evas* e, Evas_Object* obj, void* event_info)
{
	LOGI("mouse_up_cb: touch off\n");
	appdata_s* ad = static_cast<appdata_s *>(data);
	SampleView* sv = static_cast<SampleView *>(evas_object_data_get(obj, "sv"));

	sv->TouchOff();
	ad->mouse_down = EINA_FALSE;
}


static void
resize_glview(Evas_Object* obj)
{
	LOGE("resize_glview\n");
	appdata_s* ad = static_cast<appdata_s *>(evas_object_data_get(obj, "ad"));
	elm_glview_size_get(obj, &ad->glview_w, &ad->glview_h);
	SampleView* sv = static_cast<SampleView *>(evas_object_data_get(obj, "sv"));
	sv->OnWindowUpdate(ad->glview_w, ad->glview_h);
	sv->RebindVbo();
	//    update_window(ad->glview_w, ad->glview_h);
}

static void
draw_glview(Evas_Object* obj)
{
	SampleView* sv = static_cast<SampleView *>(evas_object_data_get(obj, "sv"));
	sv->OnStep();
	glFlush();
	//    step();
}

static void
init_glview(Evas_Object* obj)
{
	LOGE("init_glview\n");
	SampleView* sv = static_cast<SampleView *>(evas_object_data_get(obj, "sv"));
	if (sv == NULL)
	LOGE("null ptr??\n");

	sv->OnInit();
	LOGE("init_glview??\n");
	//    init(ad->cur_sample_num, obj);
}

static void
del_glview(Evas_Object* obj)
{
	LOGE("del_glview\n");
	SampleView* sv = static_cast<SampleView *>(evas_object_data_get(obj, "sv"));
	sv->Release();
}

static void
del_anim_cb(void* data, Evas* evas, Evas_Object* obj, void* event_info)
{
	Ecore_Animator* ani = static_cast<Ecore_Animator *>(evas_object_data_get(obj, "ani"));
	ecore_animator_del(ani);
}

static Eina_Bool
anim_cb(void* data)
{
	// notify glview should be updated again
	elm_glview_changed_set(static_cast<Evas_Object *>(data));
	return EINA_TRUE;
}

Evas_Object*
SampleView::CreateView(void* data) const
{
	appdata_s* ad = static_cast<appdata_s *>(data);

	/* Create and initialize GLView */
	//Evas_Object* glview = elm_glview_version_add(ad->navi, EVAS_GL_GLES_3_X);
	Evas_Object* glview = elm_glview_add(ad->navi);
	ELEMENTARY_GLVIEW_GLOBAL_USE(glview);

	evas_object_size_hint_align_set(glview, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_size_hint_weight_set(glview, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);


	/* Request a surface with alpha and a depth buffer */
	elm_glview_mode_set(glview, ELM_GLVIEW_DEPTH);

	/* The resize policy tells GLView what to do with the surface when it
	 * resizes. ELM_GLVIEW_RESIZE_POLICY_RECREATE will tell it to
	 * destroy the current surface and recreate it to the new size.
	 */
	elm_glview_resize_policy_set(glview, ELM_GLVIEW_RESIZE_POLICY_RECREATE);

	/* The render policy sets how GLView should render GL code.
	 * ELM_GLVIEW_RENDER_POLICY_ON_DEMAND will have the GL callback
	 * called only when the object is visible.
	 * ELM_GLVIEW_RENDER_POLICY_ALWAYS would cause the callback to be
	 * called even if the object were hidden.
	 */
	elm_glview_render_policy_set(glview, ELM_GLVIEW_RENDER_POLICY_ON_DEMAND);

	/* The initialize callback function gets registered here */
	elm_glview_init_func_set(glview, init_glview);

	/* The delete callback function gets registered here */
	elm_glview_del_func_set(glview, del_glview);

	/* The resize callback function gets registered here */
	elm_glview_resize_func_set(glview, resize_glview);

	/* The render callback function gets registered here */
	elm_glview_render_func_set(glview, draw_glview);

	/* This adds an animator so that the app will regularly
	 * trigger updates of the GLView using elm_glview_changed_set().
	 *
	 * NOTE: If you delete GL, this animator will keep running trying to access
	 * GL so this animator needs to be deleted with ecore_animator_del().
	 */
	Ecore_Animator* ani = ecore_animator_add(anim_cb, glview);
	evas_object_event_callback_add(glview, EVAS_CALLBACK_DEL, del_anim_cb, glview);
	//
	evas_object_event_callback_add(glview, EVAS_CALLBACK_MOUSE_DOWN, mouse_down_cb, ad);
	evas_object_event_callback_add(glview, EVAS_CALLBACK_MOUSE_UP, mouse_up_cb, ad);
	evas_object_event_callback_add(glview, EVAS_CALLBACK_MOUSE_MOVE, mouse_move_cb, ad);

	evas_object_data_set(glview, "ad", ad);
	evas_object_data_set(glview, "ani", ani);
	evas_object_data_set(glview, "sv", this);

	return glview;
}

