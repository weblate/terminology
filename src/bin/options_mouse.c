#include "private.h"

#include <Elementary.h>
#include <assert.h>
#include "config.h"
#include "termio.h"
#include "options.h"
#include "options_mouse.h"
#include "main.h"

typedef struct _Mouse_Ctx {
     Evas_Object *term;
     Config *config;
} Mouse_Ctx;

static void
_cb_op_helper_inline_chg(void *data,
                         Evas_Object *obj,
                         void *_event EINA_UNUSED)
{
   Mouse_Ctx *ctx = data;
   Config *config = ctx->config;
   Evas_Object *term = ctx->term;

   config->helper.inline_please = elm_check_state_get(obj);
   termio_config_update(term);
   windows_update();
   config_save(config);
}

static void
_cb_op_helper_email_chg(void *data,
                        Evas_Object *obj,
                        void *_event EINA_UNUSED)
{
   Mouse_Ctx *ctx = data;
   Config *config = ctx->config;
   Evas_Object *term = ctx->term;
   char *txt;

   if (config->helper.email)
     {
        eina_stringshare_del(config->helper.email);
        config->helper.email = NULL;
     }
   txt = elm_entry_markup_to_utf8(elm_object_text_get(obj));
   if (txt)
     {
        config->helper.email = eina_stringshare_add(txt);
        free(txt);
     }
   termio_config_update(term);
   windows_update();
   config_save(config);
}

static void
_cb_op_helper_url_image_chg(void *data,
                            Evas_Object *obj,
                            void *_event EINA_UNUSED)
{
   Mouse_Ctx *ctx = data;
   Config *config = ctx->config;
   Evas_Object *term = ctx->term;
   char *txt;

   if (config->helper.url.image)
     {
        eina_stringshare_del(config->helper.url.image);
        config->helper.url.image = NULL;
     }
   txt = elm_entry_markup_to_utf8(elm_object_text_get(obj));
   if (txt)
     {
        config->helper.url.image = eina_stringshare_add(txt);
        free(txt);
     }
   termio_config_update(term);
   windows_update();
   config_save(config);
}

static void
_cb_op_helper_url_video_chg(void *data,
                            Evas_Object *obj,
                            void *_event EINA_UNUSED)
{
   Mouse_Ctx *ctx = data;
   Config *config = ctx->config;
   Evas_Object *term = ctx->term;
   char *txt;

   if (config->helper.url.video)
     {
        eina_stringshare_del(config->helper.url.video);
        config->helper.url.video = NULL;
     }
   txt = elm_entry_markup_to_utf8(elm_object_text_get(obj));
   if (txt)
     {
        config->helper.url.video = eina_stringshare_add(txt);
        free(txt);
     }
   termio_config_update(term);
   windows_update();
   config_save(config);
}

static void
_cb_op_helper_url_general_chg(void *data,
                              Evas_Object *obj,
                              void *_event EINA_UNUSED)
{
   Mouse_Ctx *ctx = data;
   Config *config = ctx->config;
   Evas_Object *term = ctx->term;
   char *txt;

   if (config->helper.url.general)
     {
        eina_stringshare_del(config->helper.url.general);
        config->helper.url.general = NULL;
     }
   txt = elm_entry_markup_to_utf8(elm_object_text_get(obj));
   if (txt)
     {
        config->helper.url.general = eina_stringshare_add(txt);
        free(txt);
     }
   termio_config_update(term);
   windows_update();
   config_save(config);
}

static void
_cb_op_helper_local_image_chg(void *data,
                              Evas_Object *obj,
                              void *_event EINA_UNUSED)
{
   Mouse_Ctx *ctx = data;
   Config *config = ctx->config;
   Evas_Object *term = ctx->term;
   char *txt;

   if (config->helper.local.image)
     {
        eina_stringshare_del(config->helper.local.image);
        config->helper.local.image = NULL;
     }
   txt = elm_entry_markup_to_utf8(elm_object_text_get(obj));
   if (txt)
     {
        config->helper.local.image = eina_stringshare_add(txt);
        free(txt);
     }
   termio_config_update(term);
   windows_update();
   config_save(config);
}

static void
_cb_op_helper_local_video_chg(void *data,
                              Evas_Object *obj,
                              void *_event EINA_UNUSED)
{
   Mouse_Ctx *ctx = data;
   Config *config = ctx->config;
   Evas_Object *term = ctx->term;
   char *txt;

   if (config->helper.local.video)
     {
        eina_stringshare_del(config->helper.local.video);
        config->helper.local.video = NULL;
     }
   txt = elm_entry_markup_to_utf8(elm_object_text_get(obj));
   if (txt)
     {
        config->helper.local.video = eina_stringshare_add(txt);
        free(txt);
     }
   termio_config_update(term);
   windows_update();
   config_save(config);
}

static void
_cb_op_helper_local_general_chg(void *data,
                                Evas_Object *obj,
                                void *_event EINA_UNUSED)
{
   Mouse_Ctx *ctx = data;
   Config *config = ctx->config;
   Evas_Object *term = ctx->term;
   char *txt;

   if (config->helper.local.general)
     {
        eina_stringshare_del(config->helper.local.general);
        config->helper.local.general = NULL;
     }
   txt = elm_entry_markup_to_utf8(elm_object_text_get(obj));
   if (txt)
     {
        config->helper.local.general = eina_stringshare_add(txt);
        free(txt);
     }
   termio_config_update(term);
   windows_update();
   config_save(config);
}

static void
_parent_del_cb(void *data,
               Evas *_e EINA_UNUSED,
               Evas_Object *_obj EINA_UNUSED,
               void *_event_info EINA_UNUSED)
{
   Mouse_Ctx *ctx = data;

   free(ctx);
}

void
options_mouse(Evas_Object *opbox, Evas_Object *term)
{
   Config *config = termio_config_get(term);
   Evas_Object *o, *tb, *sc, *fr, *bx;
   char *txt;
   int row = 0;
   Mouse_Ctx *ctx;

   ctx = calloc(1, sizeof(*ctx));
   assert(ctx);

   ctx->config = config;
   ctx->term = term;

   fr = o = elm_frame_add(opbox);
   evas_object_size_hint_weight_set(o, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(o, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_object_text_set(o, _("Mouse"));
   elm_box_pack_end(opbox, o);
   evas_object_show(o);

   evas_object_event_callback_add(o, EVAS_CALLBACK_DEL,
                                  _parent_del_cb, ctx);

   bx = o = elm_box_add(opbox);
   evas_object_size_hint_weight_set(o, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(o, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_object_content_set(fr, o);
   evas_object_show(o);

   o = elm_check_add(opbox);
   evas_object_size_hint_weight_set(o, EVAS_HINT_EXPAND, 0.0);
   evas_object_size_hint_align_set(o, EVAS_HINT_FILL, 0.5);
   elm_object_text_set(o, _("Inline if possible"));
   elm_check_state_set(o, config->helper.inline_please);
   elm_box_pack_end(bx, o);
   evas_object_show(o);
   evas_object_smart_callback_add(o, "changed",
                                  _cb_op_helper_inline_chg, ctx);

   OPTIONS_SEPARATOR;

   sc = o = elm_scroller_add(opbox);
   elm_scroller_content_min_limit(sc, EINA_TRUE, EINA_FALSE);
   evas_object_size_hint_weight_set(o, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(o, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_box_pack_end(bx, o);
   evas_object_show(o);

   tb = o = elm_table_add(opbox);
   evas_object_size_hint_weight_set(o, EVAS_HINT_EXPAND, 0.0);
   evas_object_size_hint_align_set(o, EVAS_HINT_FILL, 0.0);
   elm_object_content_set(sc, o);
   evas_object_show(o);

   o = elm_label_add(tb);
   evas_object_size_hint_weight_set(o, 0.0, 0.0);
   evas_object_size_hint_align_set(o, 0.0, 0.5);
   elm_object_text_set(o, _("E-mail:"));
   elm_table_pack(tb, o, 0, row, 1, 1);
   evas_object_show(o);

   o = elm_entry_add(tb);
   evas_object_size_hint_weight_set(o, EVAS_HINT_EXPAND, 0.0);
   evas_object_size_hint_align_set(o, EVAS_HINT_FILL, 0.5);
   elm_entry_single_line_set(o, EINA_TRUE);
   elm_entry_scrollable_set(o, EINA_TRUE);
   elm_scroller_policy_set(o, ELM_SCROLLER_POLICY_OFF, ELM_SCROLLER_POLICY_OFF);
   txt = elm_entry_utf8_to_markup(config->helper.email);
   if (txt)
     {
        elm_object_text_set(o, txt);
        free(txt);
     }
   elm_table_pack(tb, o, 1, row, 1, 1);
   evas_object_show(o);
   evas_object_smart_callback_add(o, "changed",
                                  _cb_op_helper_email_chg, ctx);
   row++;

   o = elm_separator_add(opbox);
   evas_object_size_hint_weight_set(o, EVAS_HINT_EXPAND, 0.0);
   evas_object_size_hint_align_set(o, EVAS_HINT_FILL, 0.5);
   elm_separator_horizontal_set(o, EINA_TRUE);
   elm_table_pack(tb, o, 0, row, 2, 1);
   evas_object_show(o);
   row++;

   o = elm_label_add(tb);
   evas_object_size_hint_weight_set(o, 0.0, 0.0);
   evas_object_size_hint_align_set(o, 0.0, 0.5);
   elm_object_text_set(o, _("URL (Images):"));
   elm_table_pack(tb, o, 0, row, 1, 1);
   evas_object_show(o);

   o = elm_entry_add(tb);
   evas_object_size_hint_weight_set(o, EVAS_HINT_EXPAND, 0.0);
   evas_object_size_hint_align_set(o, EVAS_HINT_FILL, 0.5);
   elm_entry_single_line_set(o, EINA_TRUE);
   elm_entry_scrollable_set(o, EINA_TRUE);
   elm_scroller_policy_set(o, ELM_SCROLLER_POLICY_OFF, ELM_SCROLLER_POLICY_OFF);
   txt = elm_entry_utf8_to_markup(config->helper.url.image);
   if (txt)
     {
        elm_object_text_set(o, txt);
        free(txt);
     }
   elm_table_pack(tb, o, 1, row, 1, 1);
   evas_object_show(o);
   evas_object_smart_callback_add(o, "changed",
                                  _cb_op_helper_url_image_chg, ctx);
   row++;

   o = elm_label_add(tb);
   evas_object_size_hint_weight_set(o, 0.0, 0.0);
   evas_object_size_hint_align_set(o, 0.0, 0.5);
   elm_object_text_set(o, _("URL (Video):"));
   elm_table_pack(tb, o, 0, row, 1, 1);
   evas_object_show(o);

   o = elm_entry_add(tb);
   evas_object_size_hint_weight_set(o, EVAS_HINT_EXPAND, 0.0);
   evas_object_size_hint_align_set(o, EVAS_HINT_FILL, 0.5);
   elm_entry_single_line_set(o, EINA_TRUE);
   elm_entry_scrollable_set(o, EINA_TRUE);
   elm_scroller_policy_set(o, ELM_SCROLLER_POLICY_OFF, ELM_SCROLLER_POLICY_OFF);
   txt = elm_entry_utf8_to_markup(config->helper.url.video);
   if (txt)
     {
        elm_object_text_set(o, txt);
        free(txt);
     }
   elm_table_pack(tb, o, 1, row, 1, 1);
   evas_object_show(o);
   evas_object_smart_callback_add(o, "changed",
                                  _cb_op_helper_url_video_chg, ctx);
   row++;

   o = elm_label_add(tb);
   evas_object_size_hint_weight_set(o, 0.0, 0.0);
   evas_object_size_hint_align_set(o, 0.0, 0.5);
   elm_object_text_set(o, _("URL (All):"));
   elm_table_pack(tb, o, 0, row, 1, 1);
   evas_object_show(o);

   o = elm_entry_add(tb);
   evas_object_size_hint_weight_set(o, EVAS_HINT_EXPAND, 0.0);
   evas_object_size_hint_align_set(o, EVAS_HINT_FILL, 0.5);
   elm_entry_single_line_set(o, EINA_TRUE);
   elm_entry_scrollable_set(o, EINA_TRUE);
   elm_scroller_policy_set(o, ELM_SCROLLER_POLICY_OFF, ELM_SCROLLER_POLICY_OFF);
   txt = elm_entry_utf8_to_markup(config->helper.url.general);
   if (txt)
     {
        elm_object_text_set(o, txt);
        free(txt);
     }
   elm_table_pack(tb, o, 1, row, 1, 1);
   evas_object_show(o);
   evas_object_smart_callback_add(o, "changed",
                                  _cb_op_helper_url_general_chg, ctx);
   row++;

   o = elm_separator_add(opbox);
   evas_object_size_hint_weight_set(o, EVAS_HINT_EXPAND, 0.0);
   evas_object_size_hint_align_set(o, EVAS_HINT_FILL, 0.5);
   elm_separator_horizontal_set(o, EINA_TRUE);
   elm_table_pack(tb, o, 0, row, 2, 1);
   evas_object_show(o);
   row++;

   o = elm_label_add(tb);
   evas_object_size_hint_weight_set(o, 0.0, 0.0);
   evas_object_size_hint_align_set(o, 0.0, 0.5);
   elm_object_text_set(o, _("Local (Images):"));
   elm_table_pack(tb, o, 0, row, 1, 1);
   evas_object_show(o);

   o = elm_entry_add(tb);
   evas_object_size_hint_weight_set(o, EVAS_HINT_EXPAND, 0.0);
   evas_object_size_hint_align_set(o, EVAS_HINT_FILL, 0.5);
   elm_entry_single_line_set(o, EINA_TRUE);
   elm_entry_scrollable_set(o, EINA_TRUE);
   elm_scroller_policy_set(o, ELM_SCROLLER_POLICY_OFF, ELM_SCROLLER_POLICY_OFF);
   txt = elm_entry_utf8_to_markup(config->helper.local.image);
   if (txt)
     {
        elm_object_text_set(o, txt);
        free(txt);
     }
   elm_table_pack(tb, o, 1, row, 1, 1);
   evas_object_show(o);
   evas_object_smart_callback_add(o, "changed",
                                  _cb_op_helper_local_image_chg, ctx);
   row++;

   o = elm_label_add(tb);
   evas_object_size_hint_weight_set(o, 0.0, 0.0);
   evas_object_size_hint_align_set(o, 0.0, 0.5);
   elm_object_text_set(o, _("Local (Video):"));
   elm_table_pack(tb, o, 0, row, 1, 1);
   evas_object_show(o);

   o = elm_entry_add(tb);
   evas_object_size_hint_weight_set(o, EVAS_HINT_EXPAND, 0.0);
   evas_object_size_hint_align_set(o, EVAS_HINT_FILL, 0.5);
   elm_entry_single_line_set(o, EINA_TRUE);
   elm_entry_scrollable_set(o, EINA_TRUE);
   elm_scroller_policy_set(o, ELM_SCROLLER_POLICY_OFF, ELM_SCROLLER_POLICY_OFF);
   txt = elm_entry_utf8_to_markup(config->helper.local.video);
   if (txt)
     {
        elm_object_text_set(o, txt);
        free(txt);
     }
   elm_table_pack(tb, o, 1, row, 1, 1);
   evas_object_show(o);
   evas_object_smart_callback_add(o, "changed",
                                  _cb_op_helper_local_video_chg, ctx);
   row++;

   o = elm_label_add(tb);
   evas_object_size_hint_weight_set(o, 0.0, 0.0);
   evas_object_size_hint_align_set(o, 0.0, 0.5);
   elm_object_text_set(o, _("Local (All):"));
   elm_table_pack(tb, o, 0, row, 1, 1);
   evas_object_show(o);

   o = elm_entry_add(tb);
   evas_object_size_hint_weight_set(o, EVAS_HINT_EXPAND, 0.0);
   evas_object_size_hint_align_set(o, EVAS_HINT_FILL, 0.5);
   elm_entry_single_line_set(o, EINA_TRUE);
   elm_entry_scrollable_set(o, EINA_TRUE);
   elm_scroller_policy_set(o, ELM_SCROLLER_POLICY_OFF, ELM_SCROLLER_POLICY_OFF);
   txt = elm_entry_utf8_to_markup(config->helper.local.general);
   if (txt)
     {
        elm_object_text_set(o, txt);
        free(txt);
     }
   elm_table_pack(tb, o, 1, row, 1, 1);
   evas_object_show(o);
   evas_object_smart_callback_add(o, "changed",
                                  _cb_op_helper_local_general_chg, ctx);
   row++;

   evas_object_size_hint_weight_set(opbox, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(opbox, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_show(o);
}