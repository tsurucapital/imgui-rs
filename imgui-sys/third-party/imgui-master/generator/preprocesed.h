
struct ImDrawChannel;
struct ImDrawCmd;
struct ImDrawData;
struct ImDrawList;
struct ImDrawListSharedData;
struct ImDrawListSplitter;
struct ImDrawVert;
struct ImFont;
struct ImFontAtlas;
struct ImFontBuilderIO;
struct ImFontConfig;
struct ImFontGlyph;
struct ImFontGlyphRangesBuilder;
struct ImColor;
struct ImGuiContext;
struct ImGuiIO;
struct ImGuiInputTextCallbackData;
struct ImGuiKeyData;
struct ImGuiListClipper;
struct ImGuiOnceUponAFrame;
struct ImGuiPayload;
struct ImGuiPlatformImeData;
struct ImGuiSizeCallbackData;
struct ImGuiStorage;
struct ImGuiStyle;
struct ImGuiTableSortSpecs;
struct ImGuiTableColumnSortSpecs;
struct ImGuiTextBuffer;
struct ImGuiTextFilter;
struct ImGuiViewport;
enum ImGuiKey : int;
enum ImGuiMouseSource : int;
typedef int ImGuiCol;
typedef int ImGuiCond;
typedef int ImGuiDataType;
typedef int ImGuiDir;
typedef int ImGuiMouseButton;
typedef int ImGuiMouseCursor;
typedef int ImGuiSortDirection;
typedef int ImGuiStyleVar;
typedef int ImGuiTableBgTarget;
typedef int ImDrawFlags;
typedef int ImDrawListFlags;
typedef int ImFontAtlasFlags;
typedef int ImGuiBackendFlags;
typedef int ImGuiButtonFlags;
typedef int ImGuiColorEditFlags;
typedef int ImGuiConfigFlags;
typedef int ImGuiComboFlags;
typedef int ImGuiDragDropFlags;
typedef int ImGuiFocusedFlags;
typedef int ImGuiHoveredFlags;
typedef int ImGuiInputTextFlags;
typedef int ImGuiKeyChord;
typedef int ImGuiPopupFlags;
typedef int ImGuiSelectableFlags;
typedef int ImGuiSliderFlags;
typedef int ImGuiTabBarFlags;
typedef int ImGuiTabItemFlags;
typedef int ImGuiTableFlags;
typedef int ImGuiTableColumnFlags;
typedef int ImGuiTableRowFlags;
typedef int ImGuiTreeNodeFlags;
typedef int ImGuiViewportFlags;
typedef int ImGuiWindowFlags;
typedef void* ImTextureID;
typedef unsigned short ImDrawIdx;
typedef unsigned int ImGuiID;
typedef signed char ImS8;
typedef unsigned char ImU8;
typedef signed short ImS16;
typedef unsigned short ImU16;
typedef signed int ImS32;
typedef unsigned int ImU32;
typedef signed long long ImS64;
typedef unsigned long long ImU64;
typedef unsigned short ImWchar16;
typedef unsigned int ImWchar32;
typedef ImWchar32 ImWchar;
typedef int (*ImGuiInputTextCallback)(ImGuiInputTextCallbackData* data);
typedef void (*ImGuiSizeCallback)(ImGuiSizeCallbackData* data);
typedef void* (*ImGuiMemAllocFunc)(size_t sz, void* user_data);
typedef void (*ImGuiMemFreeFunc)(void* ptr, void* user_data);
struct ImVec2
{
    float x, y;
    constexpr ImVec2() : x(0.0f), y(0.0f) { }
    constexpr ImVec2(float _x, float _y) : x(_x), y(_y) { }
    float& operator[] (size_t idx) {                                              ((void) sizeof ((                                             idx == 0 || idx == 1                                             ) ? 1 : 0), __extension__ ({ if (                                             idx == 0 || idx == 1                                             ) ; else __assert_fail (                                             "idx == 0 || idx == 1"                                             , "../imgui/imgui.h", 265, __extension__ __PRETTY_FUNCTION__); }))                                                                            ; return ((float*)(void*)(char*)this)[idx]; }
    float operator[] (size_t idx) const {                                              ((void) sizeof ((                                             idx == 0 || idx == 1                                             ) ? 1 : 0), __extension__ ({ if (                                             idx == 0 || idx == 1                                             ) ; else __assert_fail (                                             "idx == 0 || idx == 1"                                             , "../imgui/imgui.h", 266, __extension__ __PRETTY_FUNCTION__); }))                                                                            ; return ((const float*)(const void*)(const char*)this)[idx]; }
};
struct ImVec4
{
    float x, y, z, w;
    constexpr ImVec4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) { }
    constexpr ImVec4(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) { }
};
namespace ImGui
{
    ImGuiContext* CreateContext(ImFontAtlas* shared_font_atlas =                                                                           ((void *)0)                                                                              );
    void DestroyContext(ImGuiContext* ctx =                                                               ((void *)0)                                                                  );
    ImGuiContext* GetCurrentContext();
    void SetCurrentContext(ImGuiContext* ctx);
    ImGuiIO& GetIO();
    ImGuiStyle& GetStyle();
    void NewFrame();
    void EndFrame();
    void Render();
    ImDrawData* GetDrawData();
    void ShowDemoWindow(bool* p_open =                                                          ((void *)0)                                                             );
    void ShowMetricsWindow(bool* p_open =                                                             ((void *)0)                                                                );
    void ShowDebugLogWindow(bool* p_open =                                                              ((void *)0)                                                                 );
    void ShowStackToolWindow(bool* p_open =                                                               ((void *)0)                                                                  );
    void ShowAboutWindow(bool* p_open =                                                           ((void *)0)                                                              );
    void ShowStyleEditor(ImGuiStyle* ref =                                                              ((void *)0)                                                                 );
    bool ShowStyleSelector(const char* label);
    void ShowFontSelector(const char* label);
    void ShowUserGuide();
    const char* GetVersion();
    void StyleColorsDark(ImGuiStyle* dst =                                                              ((void *)0)                                                                 );
    void StyleColorsLight(ImGuiStyle* dst =                                                               ((void *)0)                                                                  );
    void StyleColorsClassic(ImGuiStyle* dst =                                                                 ((void *)0)                                                                    );
    bool Begin(const char* name, bool* p_open =                                                                   ((void *)0)                                                                      , ImGuiWindowFlags flags = 0);
    void End();
    bool BeginChild(const char* str_id, const ImVec2& size = ImVec2(0, 0), bool border = false, ImGuiWindowFlags flags = 0);
    bool BeginChild(ImGuiID id, const ImVec2& size = ImVec2(0, 0), bool border = false, ImGuiWindowFlags flags = 0);
    void EndChild();
    bool IsWindowAppearing();
    bool IsWindowCollapsed();
    bool IsWindowFocused(ImGuiFocusedFlags flags=0);
    bool IsWindowHovered(ImGuiHoveredFlags flags=0);
    ImDrawList* GetWindowDrawList();
    ImVec2 GetWindowPos();
    ImVec2 GetWindowSize();
    float GetWindowWidth();
    float GetWindowHeight();
    void SetNextWindowPos(const ImVec2& pos, ImGuiCond cond = 0, const ImVec2& pivot = ImVec2(0, 0));
    void SetNextWindowSize(const ImVec2& size, ImGuiCond cond = 0);
    void SetNextWindowSizeConstraints(const ImVec2& size_min, const ImVec2& size_max, ImGuiSizeCallback custom_callback =                                                                                                                                             ((void *)0)                                                                                                                                                , void* custom_callback_data =                                                                                                                                                                                ((void *)0)                                                                                                                                                                                   );
    void SetNextWindowContentSize(const ImVec2& size);
    void SetNextWindowCollapsed(bool collapsed, ImGuiCond cond = 0);
    void SetNextWindowFocus();
    void SetNextWindowScroll(const ImVec2& scroll);
    void SetNextWindowBgAlpha(float alpha);
    void SetWindowPos(const ImVec2& pos, ImGuiCond cond = 0);
    void SetWindowSize(const ImVec2& size, ImGuiCond cond = 0);
    void SetWindowCollapsed(bool collapsed, ImGuiCond cond = 0);
    void SetWindowFocus();
    void SetWindowFontScale(float scale);
    void SetWindowPos(const char* name, const ImVec2& pos, ImGuiCond cond = 0);
    void SetWindowSize(const char* name, const ImVec2& size, ImGuiCond cond = 0);
    void SetWindowCollapsed(const char* name, bool collapsed, ImGuiCond cond = 0);
    void SetWindowFocus(const char* name);
    ImVec2 GetContentRegionAvail();
    ImVec2 GetContentRegionMax();
    ImVec2 GetWindowContentRegionMin();
    ImVec2 GetWindowContentRegionMax();
    float GetScrollX();
    float GetScrollY();
    void SetScrollX(float scroll_x);
    void SetScrollY(float scroll_y);
    float GetScrollMaxX();
    float GetScrollMaxY();
    void SetScrollHereX(float center_x_ratio = 0.5f);
    void SetScrollHereY(float center_y_ratio = 0.5f);
    void SetScrollFromPosX(float local_x, float center_x_ratio = 0.5f);
    void SetScrollFromPosY(float local_y, float center_y_ratio = 0.5f);
    void PushFont(ImFont* font);
    void PopFont();
    void PushStyleColor(ImGuiCol idx, ImU32 col);
    void PushStyleColor(ImGuiCol idx, const ImVec4& col);
    void PopStyleColor(int count = 1);
    void PushStyleVar(ImGuiStyleVar idx, float val);
    void PushStyleVar(ImGuiStyleVar idx, const ImVec2& val);
    void PopStyleVar(int count = 1);
    void PushTabStop(bool tab_stop);
    void PopTabStop();
    void PushButtonRepeat(bool repeat);
    void PopButtonRepeat();
    void PushItemWidth(float item_width);
    void PopItemWidth();
    void SetNextItemWidth(float item_width);
    float CalcItemWidth();
    void PushTextWrapPos(float wrap_local_pos_x = 0.0f);
    void PopTextWrapPos();
    ImFont* GetFont();
    float GetFontSize();
    ImVec2 GetFontTexUvWhitePixel();
    ImU32 GetColorU32(ImGuiCol idx, float alpha_mul = 1.0f);
    ImU32 GetColorU32(const ImVec4& col);
    ImU32 GetColorU32(ImU32 col);
    const ImVec4& GetStyleColorVec4(ImGuiCol idx);
    void Separator();
    void SameLine(float offset_from_start_x=0.0f, float spacing=-1.0f);
    void NewLine();
    void Spacing();
    void Dummy(const ImVec2& size);
    void Indent(float indent_w = 0.0f);
    void Unindent(float indent_w = 0.0f);
    void BeginGroup();
    void EndGroup();
    ImVec2 GetCursorPos();
    float GetCursorPosX();
    float GetCursorPosY();
    void SetCursorPos(const ImVec2& local_pos);
    void SetCursorPosX(float local_x);
    void SetCursorPosY(float local_y);
    ImVec2 GetCursorStartPos();
    ImVec2 GetCursorScreenPos();
    void SetCursorScreenPos(const ImVec2& pos);
    void AlignTextToFramePadding();
    float GetTextLineHeight();
    float GetTextLineHeightWithSpacing();
    float GetFrameHeight();
    float GetFrameHeightWithSpacing();
    void PushID(const char* str_id);
    void PushID(const char* str_id_begin, const char* str_id_end);
    void PushID(const void* ptr_id);
    void PushID(int int_id);
    void PopID();
    ImGuiID GetID(const char* str_id);
    ImGuiID GetID(const char* str_id_begin, const char* str_id_end);
    ImGuiID GetID(const void* ptr_id);
    void TextUnformatted(const char* text, const char* text_end =                                                                                     ((void *)0)                                                                                        );
    void Text(const char* fmt, ...) __attribute__((format(printf, 1, 1 +1)));
    void TextV(const char* fmt, va_list args) __attribute__((format(printf, 1, 0)));
    void TextColored(const ImVec4& col, const char* fmt, ...) __attribute__((format(printf, 2, 2 +1)));
    void TextColoredV(const ImVec4& col, const char* fmt, va_list args) __attribute__((format(printf, 2, 0)));
    void TextDisabled(const char* fmt, ...) __attribute__((format(printf, 1, 1 +1)));
    void TextDisabledV(const char* fmt, va_list args) __attribute__((format(printf, 1, 0)));
    void TextWrapped(const char* fmt, ...) __attribute__((format(printf, 1, 1 +1)));
    void TextWrappedV(const char* fmt, va_list args) __attribute__((format(printf, 1, 0)));
    void LabelText(const char* label, const char* fmt, ...) __attribute__((format(printf, 2, 2 +1)));
    void LabelTextV(const char* label, const char* fmt, va_list args) __attribute__((format(printf, 2, 0)));
    void BulletText(const char* fmt, ...) __attribute__((format(printf, 1, 1 +1)));
    void BulletTextV(const char* fmt, va_list args) __attribute__((format(printf, 1, 0)));
    void SeparatorText(const char* label);
    bool Button(const char* label, const ImVec2& size = ImVec2(0, 0));
    bool SmallButton(const char* label);
    bool InvisibleButton(const char* str_id, const ImVec2& size, ImGuiButtonFlags flags = 0);
    bool ArrowButton(const char* str_id, ImGuiDir dir);
    bool Checkbox(const char* label, bool* v);
    bool CheckboxFlags(const char* label, int* flags, int flags_value);
    bool CheckboxFlags(const char* label, unsigned int* flags, unsigned int flags_value);
    bool RadioButton(const char* label, bool active);
    bool RadioButton(const char* label, int* v, int v_button);
    void ProgressBar(float fraction, const ImVec2& size_arg = ImVec2(-1.17549435082228750796873653722224568e-38F, 0), const char* overlay =                                                                                                                            ((void *)0)                                                                                                                               );
    void Bullet();
    void Image(ImTextureID user_texture_id, const ImVec2& size, const ImVec2& uv0 = ImVec2(0, 0), const ImVec2& uv1 = ImVec2(1, 1), const ImVec4& tint_col = ImVec4(1, 1, 1, 1), const ImVec4& border_col = ImVec4(0, 0, 0, 0));
    bool ImageButton(const char* str_id, ImTextureID user_texture_id, const ImVec2& size, const ImVec2& uv0 = ImVec2(0, 0), const ImVec2& uv1 = ImVec2(1, 1), const ImVec4& bg_col = ImVec4(0, 0, 0, 0), const ImVec4& tint_col = ImVec4(1, 1, 1, 1));
    bool BeginCombo(const char* label, const char* preview_value, ImGuiComboFlags flags = 0);
    void EndCombo();
    bool Combo(const char* label, int* current_item, const char* const items[], int items_count, int popup_max_height_in_items = -1);
    bool Combo(const char* label, int* current_item, const char* items_separated_by_zeros, int popup_max_height_in_items = -1);
    bool Combo(const char* label, int* current_item, bool(*items_getter)(void* data, int idx, const char** out_text), void* data, int items_count, int popup_max_height_in_items = -1);
    bool DragFloat(const char* label, float* v, float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f", ImGuiSliderFlags flags = 0);
    bool DragFloat2(const char* label, float v[2], float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f", ImGuiSliderFlags flags = 0);
    bool DragFloat3(const char* label, float v[3], float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f", ImGuiSliderFlags flags = 0);
    bool DragFloat4(const char* label, float v[4], float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f", ImGuiSliderFlags flags = 0);
    bool DragFloatRange2(const char* label, float* v_current_min, float* v_current_max, float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f", const char* format_max =                                                                                                                                                                                                                               ((void *)0)                                                                                                                                                                                                                                  , ImGuiSliderFlags flags = 0);
    bool DragInt(const char* label, int* v, float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* format = "%d", ImGuiSliderFlags flags = 0);
    bool DragInt2(const char* label, int v[2], float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* format = "%d", ImGuiSliderFlags flags = 0);
    bool DragInt3(const char* label, int v[3], float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* format = "%d", ImGuiSliderFlags flags = 0);
    bool DragInt4(const char* label, int v[4], float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* format = "%d", ImGuiSliderFlags flags = 0);
    bool DragIntRange2(const char* label, int* v_current_min, int* v_current_max, float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* format = "%d", const char* format_max =                                                                                                                                                                                                             ((void *)0)                                                                                                                                                                                                                , ImGuiSliderFlags flags = 0);
    bool DragScalar(const char* label, ImGuiDataType data_type, void* p_data, float v_speed = 1.0f, const void* p_min =                                                                                                                                           ((void *)0)                                                                                                                                              , const void* p_max =                                                                                                                                                                     ((void *)0)                                                                                                                                                                        , const char* format =                                                                                                                                                                                                ((void *)0)                                                                                                                                                                                                   , ImGuiSliderFlags flags = 0);
    bool DragScalarN(const char* label, ImGuiDataType data_type, void* p_data, int components, float v_speed = 1.0f, const void* p_min =                                                                                                                                                            ((void *)0)                                                                                                                                                               , const void* p_max =                                                                                                                                                                                      ((void *)0)                                                                                                                                                                                         , const char* format =                                                                                                                                                                                                                 ((void *)0)                                                                                                                                                                                                                    , ImGuiSliderFlags flags = 0);
    bool SliderFloat(const char* label, float* v, float v_min, float v_max, const char* format = "%.3f", ImGuiSliderFlags flags = 0);
    bool SliderFloat2(const char* label, float v[2], float v_min, float v_max, const char* format = "%.3f", ImGuiSliderFlags flags = 0);
    bool SliderFloat3(const char* label, float v[3], float v_min, float v_max, const char* format = "%.3f", ImGuiSliderFlags flags = 0);
    bool SliderFloat4(const char* label, float v[4], float v_min, float v_max, const char* format = "%.3f", ImGuiSliderFlags flags = 0);
    bool SliderAngle(const char* label, float* v_rad, float v_degrees_min = -360.0f, float v_degrees_max = +360.0f, const char* format = "%.0f deg", ImGuiSliderFlags flags = 0);
    bool SliderInt(const char* label, int* v, int v_min, int v_max, const char* format = "%d", ImGuiSliderFlags flags = 0);
    bool SliderInt2(const char* label, int v[2], int v_min, int v_max, const char* format = "%d", ImGuiSliderFlags flags = 0);
    bool SliderInt3(const char* label, int v[3], int v_min, int v_max, const char* format = "%d", ImGuiSliderFlags flags = 0);
    bool SliderInt4(const char* label, int v[4], int v_min, int v_max, const char* format = "%d", ImGuiSliderFlags flags = 0);
    bool SliderScalar(const char* label, ImGuiDataType data_type, void* p_data, const void* p_min, const void* p_max, const char* format =                                                                                                                                                              ((void *)0)                                                                                                                                                                 , ImGuiSliderFlags flags = 0);
    bool SliderScalarN(const char* label, ImGuiDataType data_type, void* p_data, int components, const void* p_min, const void* p_max, const char* format =                                                                                                                                                                               ((void *)0)                                                                                                                                                                                  , ImGuiSliderFlags flags = 0);
    bool VSliderFloat(const char* label, const ImVec2& size, float* v, float v_min, float v_max, const char* format = "%.3f", ImGuiSliderFlags flags = 0);
    bool VSliderInt(const char* label, const ImVec2& size, int* v, int v_min, int v_max, const char* format = "%d", ImGuiSliderFlags flags = 0);
    bool VSliderScalar(const char* label, const ImVec2& size, ImGuiDataType data_type, void* p_data, const void* p_min, const void* p_max, const char* format =                                                                                                                                                                                   ((void *)0)                                                                                                                                                                                      , ImGuiSliderFlags flags = 0);
    bool InputText(const char* label, char* buf, size_t buf_size, ImGuiInputTextFlags flags = 0, ImGuiInputTextCallback callback =                                                                                                                                                      ((void *)0)                                                                                                                                                         , void* user_data =                                                                                                                                                                              ((void *)0)                                                                                                                                                                                 );
    bool InputTextMultiline(const char* label, char* buf, size_t buf_size, const ImVec2& size = ImVec2(0, 0), ImGuiInputTextFlags flags = 0, ImGuiInputTextCallback callback =                                                                                                                                                                                                  ((void *)0)                                                                                                                                                                                                     , void* user_data =                                                                                                                                                                                                                          ((void *)0)                                                                                                                                                                                                                             );
    bool InputTextWithHint(const char* label, const char* hint, char* buf, size_t buf_size, ImGuiInputTextFlags flags = 0, ImGuiInputTextCallback callback =                                                                                                                                                                                ((void *)0)                                                                                                                                                                                   , void* user_data =                                                                                                                                                                                                        ((void *)0)                                                                                                                                                                                                           );
    bool InputFloat(const char* label, float* v, float step = 0.0f, float step_fast = 0.0f, const char* format = "%.3f", ImGuiInputTextFlags flags = 0);
    bool InputFloat2(const char* label, float v[2], const char* format = "%.3f", ImGuiInputTextFlags flags = 0);
    bool InputFloat3(const char* label, float v[3], const char* format = "%.3f", ImGuiInputTextFlags flags = 0);
    bool InputFloat4(const char* label, float v[4], const char* format = "%.3f", ImGuiInputTextFlags flags = 0);
    bool InputInt(const char* label, int* v, int step = 1, int step_fast = 100, ImGuiInputTextFlags flags = 0);
    bool InputInt2(const char* label, int v[2], ImGuiInputTextFlags flags = 0);
    bool InputInt3(const char* label, int v[3], ImGuiInputTextFlags flags = 0);
    bool InputInt4(const char* label, int v[4], ImGuiInputTextFlags flags = 0);
    bool InputDouble(const char* label, double* v, double step = 0.0, double step_fast = 0.0, const char* format = "%.6f", ImGuiInputTextFlags flags = 0);
    bool InputScalar(const char* label, ImGuiDataType data_type, void* p_data, const void* p_step =                                                                                                                       ((void *)0)                                                                                                                          , const void* p_step_fast =                                                                                                                                                       ((void *)0)                                                                                                                                                          , const char* format =                                                                                                                                                                                  ((void *)0)                                                                                                                                                                                     , ImGuiInputTextFlags flags = 0);
    bool InputScalarN(const char* label, ImGuiDataType data_type, void* p_data, int components, const void* p_step =                                                                                                                                        ((void *)0)                                                                                                                                           , const void* p_step_fast =                                                                                                                                                                        ((void *)0)                                                                                                                                                                           , const char* format =                                                                                                                                                                                                   ((void *)0)                                                                                                                                                                                                      , ImGuiInputTextFlags flags = 0);
    bool ColorEdit3(const char* label, float col[3], ImGuiColorEditFlags flags = 0);
    bool ColorEdit4(const char* label, float col[4], ImGuiColorEditFlags flags = 0);
    bool ColorPicker3(const char* label, float col[3], ImGuiColorEditFlags flags = 0);
    bool ColorPicker4(const char* label, float col[4], ImGuiColorEditFlags flags = 0, const float* ref_col =                                                                                                                                ((void *)0)                                                                                                                                   );
    bool ColorButton(const char* desc_id, const ImVec4& col, ImGuiColorEditFlags flags = 0, const ImVec2& size = ImVec2(0, 0));
    void SetColorEditOptions(ImGuiColorEditFlags flags);
    bool TreeNode(const char* label);
    bool TreeNode(const char* str_id, const char* fmt, ...) __attribute__((format(printf, 2, 2 +1)));
    bool TreeNode(const void* ptr_id, const char* fmt, ...) __attribute__((format(printf, 2, 2 +1)));
    bool TreeNodeV(const char* str_id, const char* fmt, va_list args) __attribute__((format(printf, 2, 0)));
    bool TreeNodeV(const void* ptr_id, const char* fmt, va_list args) __attribute__((format(printf, 2, 0)));
    bool TreeNodeEx(const char* label, ImGuiTreeNodeFlags flags = 0);
    bool TreeNodeEx(const char* str_id, ImGuiTreeNodeFlags flags, const char* fmt, ...) __attribute__((format(printf, 3, 3 +1)));
    bool TreeNodeEx(const void* ptr_id, ImGuiTreeNodeFlags flags, const char* fmt, ...) __attribute__((format(printf, 3, 3 +1)));
    bool TreeNodeExV(const char* str_id, ImGuiTreeNodeFlags flags, const char* fmt, va_list args) __attribute__((format(printf, 3, 0)));
    bool TreeNodeExV(const void* ptr_id, ImGuiTreeNodeFlags flags, const char* fmt, va_list args) __attribute__((format(printf, 3, 0)));
    void TreePush(const char* str_id);
    void TreePush(const void* ptr_id);
    void TreePop();
    float GetTreeNodeToLabelSpacing();
    bool CollapsingHeader(const char* label, ImGuiTreeNodeFlags flags = 0);
    bool CollapsingHeader(const char* label, bool* p_visible, ImGuiTreeNodeFlags flags = 0);
    void SetNextItemOpen(bool is_open, ImGuiCond cond = 0);
    bool Selectable(const char* label, bool selected = false, ImGuiSelectableFlags flags = 0, const ImVec2& size = ImVec2(0, 0));
    bool Selectable(const char* label, bool* p_selected, ImGuiSelectableFlags flags = 0, const ImVec2& size = ImVec2(0, 0));
    bool BeginListBox(const char* label, const ImVec2& size = ImVec2(0, 0));
    void EndListBox();
    bool ListBox(const char* label, int* current_item, const char* const items[], int items_count, int height_in_items = -1);
    bool ListBox(const char* label, int* current_item, bool (*items_getter)(void* data, int idx, const char** out_text), void* data, int items_count, int height_in_items = -1);
    void PlotLines(const char* label, const float* values, int values_count, int values_offset = 0, const char* overlay_text =                                                                                                                                                  ((void *)0)                                                                                                                                                     , float scale_min = 3.40282346638528859811704183484516925e+38F, float scale_max = 3.40282346638528859811704183484516925e+38F, ImVec2 graph_size = ImVec2(0, 0), int stride = sizeof(float));
    void PlotLines(const char* label, float(*values_getter)(void* data, int idx), void* data, int values_count, int values_offset = 0, const char* overlay_text =                                                                                                                                                                                     ((void *)0)                                                                                                                                                                                        , float scale_min = 3.40282346638528859811704183484516925e+38F, float scale_max = 3.40282346638528859811704183484516925e+38F, ImVec2 graph_size = ImVec2(0, 0));
    void PlotHistogram(const char* label, const float* values, int values_count, int values_offset = 0, const char* overlay_text =                                                                                                                                                      ((void *)0)                                                                                                                                                         , float scale_min = 3.40282346638528859811704183484516925e+38F, float scale_max = 3.40282346638528859811704183484516925e+38F, ImVec2 graph_size = ImVec2(0, 0), int stride = sizeof(float));
    void PlotHistogram(const char* label, float(*values_getter)(void* data, int idx), void* data, int values_count, int values_offset = 0, const char* overlay_text =                                                                                                                                                                                         ((void *)0)                                                                                                                                                                                            , float scale_min = 3.40282346638528859811704183484516925e+38F, float scale_max = 3.40282346638528859811704183484516925e+38F, ImVec2 graph_size = ImVec2(0, 0));
    void Value(const char* prefix, bool b);
    void Value(const char* prefix, int v);
    void Value(const char* prefix, unsigned int v);
    void Value(const char* prefix, float v, const char* float_format =                                                                                          ((void *)0)                                                                                             );
    bool BeginMenuBar();
    void EndMenuBar();
    bool BeginMainMenuBar();
    void EndMainMenuBar();
    bool BeginMenu(const char* label, bool enabled = true);
    void EndMenu();
    bool MenuItem(const char* label, const char* shortcut =                                                                               ((void *)0)                                                                                  , bool selected = false, bool enabled = true);
    bool MenuItem(const char* label, const char* shortcut, bool* p_selected, bool enabled = true);
    bool BeginTooltip();
    void EndTooltip();
    void SetTooltip(const char* fmt, ...) __attribute__((format(printf, 1, 1 +1)));
    void SetTooltipV(const char* fmt, va_list args) __attribute__((format(printf, 1, 0)));
    bool BeginItemTooltip();
    void SetItemTooltip(const char* fmt, ...) __attribute__((format(printf, 1, 1 +1)));
    void SetItemTooltipV(const char* fmt, va_list args) __attribute__((format(printf, 1, 0)));
    bool BeginPopup(const char* str_id, ImGuiWindowFlags flags = 0);
    bool BeginPopupModal(const char* name, bool* p_open =                                                                             ((void *)0)                                                                                , ImGuiWindowFlags flags = 0);
    void EndPopup();
    void OpenPopup(const char* str_id, ImGuiPopupFlags popup_flags = 0);
    void OpenPopup(ImGuiID id, ImGuiPopupFlags popup_flags = 0);
    void OpenPopupOnItemClick(const char* str_id =                                                                      ((void *)0)                                                                         , ImGuiPopupFlags popup_flags = 1);
    void CloseCurrentPopup();
    bool BeginPopupContextItem(const char* str_id =                                                                       ((void *)0)                                                                          , ImGuiPopupFlags popup_flags = 1);
    bool BeginPopupContextWindow(const char* str_id =                                                                         ((void *)0)                                                                            , ImGuiPopupFlags popup_flags = 1);
    bool BeginPopupContextVoid(const char* str_id =                                                                       ((void *)0)                                                                          , ImGuiPopupFlags popup_flags = 1);
    bool IsPopupOpen(const char* str_id, ImGuiPopupFlags flags = 0);
    bool BeginTable(const char* str_id, int column, ImGuiTableFlags flags = 0, const ImVec2& outer_size = ImVec2(0.0f, 0.0f), float inner_width = 0.0f);
    void EndTable();
    void TableNextRow(ImGuiTableRowFlags row_flags = 0, float min_row_height = 0.0f);
    bool TableNextColumn();
    bool TableSetColumnIndex(int column_n);
    void TableSetupColumn(const char* label, ImGuiTableColumnFlags flags = 0, float init_width_or_weight = 0.0f, ImGuiID user_id = 0);
    void TableSetupScrollFreeze(int cols, int rows);
    void TableHeadersRow();
    void TableHeader(const char* label);
    ImGuiTableSortSpecs* TableGetSortSpecs();
    int TableGetColumnCount();
    int TableGetColumnIndex();
    int TableGetRowIndex();
    const char* TableGetColumnName(int column_n = -1);
    ImGuiTableColumnFlags TableGetColumnFlags(int column_n = -1);
    void TableSetColumnEnabled(int column_n, bool v);
    void TableSetBgColor(ImGuiTableBgTarget target, ImU32 color, int column_n = -1);
    void Columns(int count = 1, const char* id =                                                                    ((void *)0)                                                                       , bool border = true);
    void NextColumn();
    int GetColumnIndex();
    float GetColumnWidth(int column_index = -1);
    void SetColumnWidth(int column_index, float width);
    float GetColumnOffset(int column_index = -1);
    void SetColumnOffset(int column_index, float offset_x);
    int GetColumnsCount();
    bool BeginTabBar(const char* str_id, ImGuiTabBarFlags flags = 0);
    void EndTabBar();
    bool BeginTabItem(const char* label, bool* p_open =                                                                           ((void *)0)                                                                              , ImGuiTabItemFlags flags = 0);
    void EndTabItem();
    bool TabItemButton(const char* label, ImGuiTabItemFlags flags = 0);
    void SetTabItemClosed(const char* tab_or_docked_window_label);
    void LogToTTY(int auto_open_depth = -1);
    void LogToFile(int auto_open_depth = -1, const char* filename =                                                                                       ((void *)0)                                                                                          );
    void LogToClipboard(int auto_open_depth = -1);
    void LogFinish();
    void LogButtons();
    void LogText(const char* fmt, ...) __attribute__((format(printf, 1, 1 +1)));
    void LogTextV(const char* fmt, va_list args) __attribute__((format(printf, 1, 0)));
    bool BeginDragDropSource(ImGuiDragDropFlags flags = 0);
    bool SetDragDropPayload(const char* type, const void* data, size_t sz, ImGuiCond cond = 0);
    void EndDragDropSource();
    bool BeginDragDropTarget();
    const ImGuiPayload* AcceptDragDropPayload(const char* type, ImGuiDragDropFlags flags = 0);
    void EndDragDropTarget();
    const ImGuiPayload* GetDragDropPayload();
    void BeginDisabled(bool disabled = true);
    void EndDisabled();
    void PushClipRect(const ImVec2& clip_rect_min, const ImVec2& clip_rect_max, bool intersect_with_current_clip_rect);
    void PopClipRect();
    void SetItemDefaultFocus();
    void SetKeyboardFocusHere(int offset = 0);
    void SetNextItemAllowOverlap();
    bool IsItemHovered(ImGuiHoveredFlags flags = 0);
    bool IsItemActive();
    bool IsItemFocused();
    bool IsItemClicked(ImGuiMouseButton mouse_button = 0);
    bool IsItemVisible();
    bool IsItemEdited();
    bool IsItemActivated();
    bool IsItemDeactivated();
    bool IsItemDeactivatedAfterEdit();
    bool IsItemToggledOpen();
    bool IsAnyItemHovered();
    bool IsAnyItemActive();
    bool IsAnyItemFocused();
    ImGuiID GetItemID();
    ImVec2 GetItemRectMin();
    ImVec2 GetItemRectMax();
    ImVec2 GetItemRectSize();
    ImGuiViewport* GetMainViewport();
    ImDrawList* GetBackgroundDrawList();
    ImDrawList* GetForegroundDrawList();
    bool IsRectVisible(const ImVec2& size);
    bool IsRectVisible(const ImVec2& rect_min, const ImVec2& rect_max);
    double GetTime();
    int GetFrameCount();
    ImDrawListSharedData* GetDrawListSharedData();
    const char* GetStyleColorName(ImGuiCol idx);
    void SetStateStorage(ImGuiStorage* storage);
    ImGuiStorage* GetStateStorage();
    bool BeginChildFrame(ImGuiID id, const ImVec2& size, ImGuiWindowFlags flags = 0);
    void EndChildFrame();
    ImVec2 CalcTextSize(const char* text, const char* text_end =                                                                                  ((void *)0)                                                                                     , bool hide_text_after_double_hash = false, float wrap_width = -1.0f);
    ImVec4 ColorConvertU32ToFloat4(ImU32 in);
    ImU32 ColorConvertFloat4ToU32(const ImVec4& in);
    void ColorConvertRGBtoHSV(float r, float g, float b, float& out_h, float& out_s, float& out_v);
    void ColorConvertHSVtoRGB(float h, float s, float v, float& out_r, float& out_g, float& out_b);
    bool IsKeyDown(ImGuiKey key);
    bool IsKeyPressed(ImGuiKey key, bool repeat = true);
    bool IsKeyReleased(ImGuiKey key);
    int GetKeyPressedAmount(ImGuiKey key, float repeat_delay, float rate);
    const char* GetKeyName(ImGuiKey key);
    void SetNextFrameWantCaptureKeyboard(bool want_capture_keyboard);
    bool IsMouseDown(ImGuiMouseButton button);
    bool IsMouseClicked(ImGuiMouseButton button, bool repeat = false);
    bool IsMouseReleased(ImGuiMouseButton button);
    bool IsMouseDoubleClicked(ImGuiMouseButton button);
    int GetMouseClickedCount(ImGuiMouseButton button);
    bool IsMouseHoveringRect(const ImVec2& r_min, const ImVec2& r_max, bool clip = true);
    bool IsMousePosValid(const ImVec2* mouse_pos =                                                                      ((void *)0)                                                                         );
    bool IsAnyMouseDown();
    ImVec2 GetMousePos();
    ImVec2 GetMousePosOnOpeningCurrentPopup();
    bool IsMouseDragging(ImGuiMouseButton button, float lock_threshold = -1.0f);
    ImVec2 GetMouseDragDelta(ImGuiMouseButton button = 0, float lock_threshold = -1.0f);
    void ResetMouseDragDelta(ImGuiMouseButton button = 0);
    ImGuiMouseCursor GetMouseCursor();
    void SetMouseCursor(ImGuiMouseCursor cursor_type);
    void SetNextFrameWantCaptureMouse(bool want_capture_mouse);
    const char* GetClipboardText();
    void SetClipboardText(const char* text);
    void LoadIniSettingsFromDisk(const char* ini_filename);
    void LoadIniSettingsFromMemory(const char* ini_data, size_t ini_size=0);
    void SaveIniSettingsToDisk(const char* ini_filename);
    const char* SaveIniSettingsToMemory(size_t* out_ini_size =                                                                           ((void *)0)                                                                              );
    void DebugTextEncoding(const char* text);
    bool DebugCheckVersionAndDataLayout(const char* version_str, size_t sz_io, size_t sz_style, size_t sz_vec2, size_t sz_vec4, size_t sz_drawvert, size_t sz_drawidx);
    void SetAllocatorFunctions(ImGuiMemAllocFunc alloc_func, ImGuiMemFreeFunc free_func, void* user_data =                                                                                                                              ((void *)0)                                                                                                                                 );
    void GetAllocatorFunctions(ImGuiMemAllocFunc* p_alloc_func, ImGuiMemFreeFunc* p_free_func, void** p_user_data);
    void* MemAlloc(size_t size);
    void MemFree(void* ptr);
}
enum ImGuiWindowFlags_
{
    ImGuiWindowFlags_None = 0,
    ImGuiWindowFlags_NoTitleBar = 1 << 0,
    ImGuiWindowFlags_NoResize = 1 << 1,
    ImGuiWindowFlags_NoMove = 1 << 2,
    ImGuiWindowFlags_NoScrollbar = 1 << 3,
    ImGuiWindowFlags_NoScrollWithMouse = 1 << 4,
    ImGuiWindowFlags_NoCollapse = 1 << 5,
    ImGuiWindowFlags_AlwaysAutoResize = 1 << 6,
    ImGuiWindowFlags_NoBackground = 1 << 7,
    ImGuiWindowFlags_NoSavedSettings = 1 << 8,
    ImGuiWindowFlags_NoMouseInputs = 1 << 9,
    ImGuiWindowFlags_MenuBar = 1 << 10,
    ImGuiWindowFlags_HorizontalScrollbar = 1 << 11,
    ImGuiWindowFlags_NoFocusOnAppearing = 1 << 12,
    ImGuiWindowFlags_NoBringToFrontOnFocus = 1 << 13,
    ImGuiWindowFlags_AlwaysVerticalScrollbar= 1 << 14,
    ImGuiWindowFlags_AlwaysHorizontalScrollbar=1<< 15,
    ImGuiWindowFlags_AlwaysUseWindowPadding = 1 << 16,
    ImGuiWindowFlags_NoNavInputs = 1 << 18,
    ImGuiWindowFlags_NoNavFocus = 1 << 19,
    ImGuiWindowFlags_UnsavedDocument = 1 << 20,
    ImGuiWindowFlags_NoNav = ImGuiWindowFlags_NoNavInputs | ImGuiWindowFlags_NoNavFocus,
    ImGuiWindowFlags_NoDecoration = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse,
    ImGuiWindowFlags_NoInputs = ImGuiWindowFlags_NoMouseInputs | ImGuiWindowFlags_NoNavInputs | ImGuiWindowFlags_NoNavFocus,
    ImGuiWindowFlags_NavFlattened = 1 << 23,
    ImGuiWindowFlags_ChildWindow = 1 << 24,
    ImGuiWindowFlags_Tooltip = 1 << 25,
    ImGuiWindowFlags_Popup = 1 << 26,
    ImGuiWindowFlags_Modal = 1 << 27,
    ImGuiWindowFlags_ChildMenu = 1 << 28,
};
enum ImGuiInputTextFlags_
{
    ImGuiInputTextFlags_None = 0,
    ImGuiInputTextFlags_CharsDecimal = 1 << 0,
    ImGuiInputTextFlags_CharsHexadecimal = 1 << 1,
    ImGuiInputTextFlags_CharsUppercase = 1 << 2,
    ImGuiInputTextFlags_CharsNoBlank = 1 << 3,
    ImGuiInputTextFlags_AutoSelectAll = 1 << 4,
    ImGuiInputTextFlags_EnterReturnsTrue = 1 << 5,
    ImGuiInputTextFlags_CallbackCompletion = 1 << 6,
    ImGuiInputTextFlags_CallbackHistory = 1 << 7,
    ImGuiInputTextFlags_CallbackAlways = 1 << 8,
    ImGuiInputTextFlags_CallbackCharFilter = 1 << 9,
    ImGuiInputTextFlags_AllowTabInput = 1 << 10,
    ImGuiInputTextFlags_CtrlEnterForNewLine = 1 << 11,
    ImGuiInputTextFlags_NoHorizontalScroll = 1 << 12,
    ImGuiInputTextFlags_AlwaysOverwrite = 1 << 13,
    ImGuiInputTextFlags_ReadOnly = 1 << 14,
    ImGuiInputTextFlags_Password = 1 << 15,
    ImGuiInputTextFlags_NoUndoRedo = 1 << 16,
    ImGuiInputTextFlags_CharsScientific = 1 << 17,
    ImGuiInputTextFlags_CallbackResize = 1 << 18,
    ImGuiInputTextFlags_CallbackEdit = 1 << 19,
    ImGuiInputTextFlags_EscapeClearsAll = 1 << 20,
};
enum ImGuiTreeNodeFlags_
{
    ImGuiTreeNodeFlags_None = 0,
    ImGuiTreeNodeFlags_Selected = 1 << 0,
    ImGuiTreeNodeFlags_Framed = 1 << 1,
    ImGuiTreeNodeFlags_AllowOverlap = 1 << 2,
    ImGuiTreeNodeFlags_NoTreePushOnOpen = 1 << 3,
    ImGuiTreeNodeFlags_NoAutoOpenOnLog = 1 << 4,
    ImGuiTreeNodeFlags_DefaultOpen = 1 << 5,
    ImGuiTreeNodeFlags_OpenOnDoubleClick = 1 << 6,
    ImGuiTreeNodeFlags_OpenOnArrow = 1 << 7,
    ImGuiTreeNodeFlags_Leaf = 1 << 8,
    ImGuiTreeNodeFlags_Bullet = 1 << 9,
    ImGuiTreeNodeFlags_FramePadding = 1 << 10,
    ImGuiTreeNodeFlags_SpanAvailWidth = 1 << 11,
    ImGuiTreeNodeFlags_SpanFullWidth = 1 << 12,
    ImGuiTreeNodeFlags_NavLeftJumpsBackHere = 1 << 13,
    ImGuiTreeNodeFlags_CollapsingHeader = ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_NoAutoOpenOnLog,
};
enum ImGuiPopupFlags_
{
    ImGuiPopupFlags_None = 0,
    ImGuiPopupFlags_MouseButtonLeft = 0,
    ImGuiPopupFlags_MouseButtonRight = 1,
    ImGuiPopupFlags_MouseButtonMiddle = 2,
    ImGuiPopupFlags_MouseButtonMask_ = 0x1F,
    ImGuiPopupFlags_MouseButtonDefault_ = 1,
    ImGuiPopupFlags_NoOpenOverExistingPopup = 1 << 5,
    ImGuiPopupFlags_NoOpenOverItems = 1 << 6,
    ImGuiPopupFlags_AnyPopupId = 1 << 7,
    ImGuiPopupFlags_AnyPopupLevel = 1 << 8,
    ImGuiPopupFlags_AnyPopup = ImGuiPopupFlags_AnyPopupId | ImGuiPopupFlags_AnyPopupLevel,
};
enum ImGuiSelectableFlags_
{
    ImGuiSelectableFlags_None = 0,
    ImGuiSelectableFlags_DontClosePopups = 1 << 0,
    ImGuiSelectableFlags_SpanAllColumns = 1 << 1,
    ImGuiSelectableFlags_AllowDoubleClick = 1 << 2,
    ImGuiSelectableFlags_Disabled = 1 << 3,
    ImGuiSelectableFlags_AllowOverlap = 1 << 4,
};
enum ImGuiComboFlags_
{
    ImGuiComboFlags_None = 0,
    ImGuiComboFlags_PopupAlignLeft = 1 << 0,
    ImGuiComboFlags_HeightSmall = 1 << 1,
    ImGuiComboFlags_HeightRegular = 1 << 2,
    ImGuiComboFlags_HeightLarge = 1 << 3,
    ImGuiComboFlags_HeightLargest = 1 << 4,
    ImGuiComboFlags_NoArrowButton = 1 << 5,
    ImGuiComboFlags_NoPreview = 1 << 6,
    ImGuiComboFlags_HeightMask_ = ImGuiComboFlags_HeightSmall | ImGuiComboFlags_HeightRegular | ImGuiComboFlags_HeightLarge | ImGuiComboFlags_HeightLargest,
};
enum ImGuiTabBarFlags_
{
    ImGuiTabBarFlags_None = 0,
    ImGuiTabBarFlags_Reorderable = 1 << 0,
    ImGuiTabBarFlags_AutoSelectNewTabs = 1 << 1,
    ImGuiTabBarFlags_TabListPopupButton = 1 << 2,
    ImGuiTabBarFlags_NoCloseWithMiddleMouseButton = 1 << 3,
    ImGuiTabBarFlags_NoTabListScrollingButtons = 1 << 4,
    ImGuiTabBarFlags_NoTooltip = 1 << 5,
    ImGuiTabBarFlags_FittingPolicyResizeDown = 1 << 6,
    ImGuiTabBarFlags_FittingPolicyScroll = 1 << 7,
    ImGuiTabBarFlags_FittingPolicyMask_ = ImGuiTabBarFlags_FittingPolicyResizeDown | ImGuiTabBarFlags_FittingPolicyScroll,
    ImGuiTabBarFlags_FittingPolicyDefault_ = ImGuiTabBarFlags_FittingPolicyResizeDown,
};
enum ImGuiTabItemFlags_
{
    ImGuiTabItemFlags_None = 0,
    ImGuiTabItemFlags_UnsavedDocument = 1 << 0,
    ImGuiTabItemFlags_SetSelected = 1 << 1,
    ImGuiTabItemFlags_NoCloseWithMiddleMouseButton = 1 << 2,
    ImGuiTabItemFlags_NoPushId = 1 << 3,
    ImGuiTabItemFlags_NoTooltip = 1 << 4,
    ImGuiTabItemFlags_NoReorder = 1 << 5,
    ImGuiTabItemFlags_Leading = 1 << 6,
    ImGuiTabItemFlags_Trailing = 1 << 7,
};
enum ImGuiTableFlags_
{
    ImGuiTableFlags_None = 0,
    ImGuiTableFlags_Resizable = 1 << 0,
    ImGuiTableFlags_Reorderable = 1 << 1,
    ImGuiTableFlags_Hideable = 1 << 2,
    ImGuiTableFlags_Sortable = 1 << 3,
    ImGuiTableFlags_NoSavedSettings = 1 << 4,
    ImGuiTableFlags_ContextMenuInBody = 1 << 5,
    ImGuiTableFlags_RowBg = 1 << 6,
    ImGuiTableFlags_BordersInnerH = 1 << 7,
    ImGuiTableFlags_BordersOuterH = 1 << 8,
    ImGuiTableFlags_BordersInnerV = 1 << 9,
    ImGuiTableFlags_BordersOuterV = 1 << 10,
    ImGuiTableFlags_BordersH = ImGuiTableFlags_BordersInnerH | ImGuiTableFlags_BordersOuterH,
    ImGuiTableFlags_BordersV = ImGuiTableFlags_BordersInnerV | ImGuiTableFlags_BordersOuterV,
    ImGuiTableFlags_BordersInner = ImGuiTableFlags_BordersInnerV | ImGuiTableFlags_BordersInnerH,
    ImGuiTableFlags_BordersOuter = ImGuiTableFlags_BordersOuterV | ImGuiTableFlags_BordersOuterH,
    ImGuiTableFlags_Borders = ImGuiTableFlags_BordersInner | ImGuiTableFlags_BordersOuter,
    ImGuiTableFlags_NoBordersInBody = 1 << 11,
    ImGuiTableFlags_NoBordersInBodyUntilResize = 1 << 12,
    ImGuiTableFlags_SizingFixedFit = 1 << 13,
    ImGuiTableFlags_SizingFixedSame = 2 << 13,
    ImGuiTableFlags_SizingStretchProp = 3 << 13,
    ImGuiTableFlags_SizingStretchSame = 4 << 13,
    ImGuiTableFlags_NoHostExtendX = 1 << 16,
    ImGuiTableFlags_NoHostExtendY = 1 << 17,
    ImGuiTableFlags_NoKeepColumnsVisible = 1 << 18,
    ImGuiTableFlags_PreciseWidths = 1 << 19,
    ImGuiTableFlags_NoClip = 1 << 20,
    ImGuiTableFlags_PadOuterX = 1 << 21,
    ImGuiTableFlags_NoPadOuterX = 1 << 22,
    ImGuiTableFlags_NoPadInnerX = 1 << 23,
    ImGuiTableFlags_ScrollX = 1 << 24,
    ImGuiTableFlags_ScrollY = 1 << 25,
    ImGuiTableFlags_SortMulti = 1 << 26,
    ImGuiTableFlags_SortTristate = 1 << 27,
    ImGuiTableFlags_SizingMask_ = ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_SizingFixedSame | ImGuiTableFlags_SizingStretchProp | ImGuiTableFlags_SizingStretchSame,
};
enum ImGuiTableColumnFlags_
{
    ImGuiTableColumnFlags_None = 0,
    ImGuiTableColumnFlags_Disabled = 1 << 0,
    ImGuiTableColumnFlags_DefaultHide = 1 << 1,
    ImGuiTableColumnFlags_DefaultSort = 1 << 2,
    ImGuiTableColumnFlags_WidthStretch = 1 << 3,
    ImGuiTableColumnFlags_WidthFixed = 1 << 4,
    ImGuiTableColumnFlags_NoResize = 1 << 5,
    ImGuiTableColumnFlags_NoReorder = 1 << 6,
    ImGuiTableColumnFlags_NoHide = 1 << 7,
    ImGuiTableColumnFlags_NoClip = 1 << 8,
    ImGuiTableColumnFlags_NoSort = 1 << 9,
    ImGuiTableColumnFlags_NoSortAscending = 1 << 10,
    ImGuiTableColumnFlags_NoSortDescending = 1 << 11,
    ImGuiTableColumnFlags_NoHeaderLabel = 1 << 12,
    ImGuiTableColumnFlags_NoHeaderWidth = 1 << 13,
    ImGuiTableColumnFlags_PreferSortAscending = 1 << 14,
    ImGuiTableColumnFlags_PreferSortDescending = 1 << 15,
    ImGuiTableColumnFlags_IndentEnable = 1 << 16,
    ImGuiTableColumnFlags_IndentDisable = 1 << 17,
    ImGuiTableColumnFlags_IsEnabled = 1 << 24,
    ImGuiTableColumnFlags_IsVisible = 1 << 25,
    ImGuiTableColumnFlags_IsSorted = 1 << 26,
    ImGuiTableColumnFlags_IsHovered = 1 << 27,
    ImGuiTableColumnFlags_WidthMask_ = ImGuiTableColumnFlags_WidthStretch | ImGuiTableColumnFlags_WidthFixed,
    ImGuiTableColumnFlags_IndentMask_ = ImGuiTableColumnFlags_IndentEnable | ImGuiTableColumnFlags_IndentDisable,
    ImGuiTableColumnFlags_StatusMask_ = ImGuiTableColumnFlags_IsEnabled | ImGuiTableColumnFlags_IsVisible | ImGuiTableColumnFlags_IsSorted | ImGuiTableColumnFlags_IsHovered,
    ImGuiTableColumnFlags_NoDirectResize_ = 1 << 30,
};
enum ImGuiTableRowFlags_
{
    ImGuiTableRowFlags_None = 0,
    ImGuiTableRowFlags_Headers = 1 << 0,
};
enum ImGuiTableBgTarget_
{
    ImGuiTableBgTarget_None = 0,
    ImGuiTableBgTarget_RowBg0 = 1,
    ImGuiTableBgTarget_RowBg1 = 2,
    ImGuiTableBgTarget_CellBg = 3,
};
enum ImGuiFocusedFlags_
{
    ImGuiFocusedFlags_None = 0,
    ImGuiFocusedFlags_ChildWindows = 1 << 0,
    ImGuiFocusedFlags_RootWindow = 1 << 1,
    ImGuiFocusedFlags_AnyWindow = 1 << 2,
    ImGuiFocusedFlags_NoPopupHierarchy = 1 << 3,
    ImGuiFocusedFlags_RootAndChildWindows = ImGuiFocusedFlags_RootWindow | ImGuiFocusedFlags_ChildWindows,
};
enum ImGuiHoveredFlags_
{
    ImGuiHoveredFlags_None = 0,
    ImGuiHoveredFlags_ChildWindows = 1 << 0,
    ImGuiHoveredFlags_RootWindow = 1 << 1,
    ImGuiHoveredFlags_AnyWindow = 1 << 2,
    ImGuiHoveredFlags_NoPopupHierarchy = 1 << 3,
    ImGuiHoveredFlags_AllowWhenBlockedByPopup = 1 << 5,
    ImGuiHoveredFlags_AllowWhenBlockedByActiveItem = 1 << 7,
    ImGuiHoveredFlags_AllowWhenOverlappedByItem = 1 << 8,
    ImGuiHoveredFlags_AllowWhenOverlappedByWindow = 1 << 9,
    ImGuiHoveredFlags_AllowWhenDisabled = 1 << 10,
    ImGuiHoveredFlags_NoNavOverride = 1 << 11,
    ImGuiHoveredFlags_AllowWhenOverlapped = ImGuiHoveredFlags_AllowWhenOverlappedByItem | ImGuiHoveredFlags_AllowWhenOverlappedByWindow,
    ImGuiHoveredFlags_RectOnly = ImGuiHoveredFlags_AllowWhenBlockedByPopup | ImGuiHoveredFlags_AllowWhenBlockedByActiveItem | ImGuiHoveredFlags_AllowWhenOverlapped,
    ImGuiHoveredFlags_RootAndChildWindows = ImGuiHoveredFlags_RootWindow | ImGuiHoveredFlags_ChildWindows,
    ImGuiHoveredFlags_ForTooltip = 1 << 12,
    ImGuiHoveredFlags_Stationary = 1 << 13,
    ImGuiHoveredFlags_DelayNone = 1 << 14,
    ImGuiHoveredFlags_DelayShort = 1 << 15,
    ImGuiHoveredFlags_DelayNormal = 1 << 16,
    ImGuiHoveredFlags_NoSharedDelay = 1 << 17,
};
enum ImGuiDragDropFlags_
{
    ImGuiDragDropFlags_None = 0,
    ImGuiDragDropFlags_SourceNoPreviewTooltip = 1 << 0,
    ImGuiDragDropFlags_SourceNoDisableHover = 1 << 1,
    ImGuiDragDropFlags_SourceNoHoldToOpenOthers = 1 << 2,
    ImGuiDragDropFlags_SourceAllowNullID = 1 << 3,
    ImGuiDragDropFlags_SourceExtern = 1 << 4,
    ImGuiDragDropFlags_SourceAutoExpirePayload = 1 << 5,
    ImGuiDragDropFlags_AcceptBeforeDelivery = 1 << 10,
    ImGuiDragDropFlags_AcceptNoDrawDefaultRect = 1 << 11,
    ImGuiDragDropFlags_AcceptNoPreviewTooltip = 1 << 12,
    ImGuiDragDropFlags_AcceptPeekOnly = ImGuiDragDropFlags_AcceptBeforeDelivery | ImGuiDragDropFlags_AcceptNoDrawDefaultRect,
};
enum ImGuiDataType_
{
    ImGuiDataType_S8,
    ImGuiDataType_U8,
    ImGuiDataType_S16,
    ImGuiDataType_U16,
    ImGuiDataType_S32,
    ImGuiDataType_U32,
    ImGuiDataType_S64,
    ImGuiDataType_U64,
    ImGuiDataType_Float,
    ImGuiDataType_Double,
    ImGuiDataType_COUNT
};
enum ImGuiDir_
{
    ImGuiDir_None = -1,
    ImGuiDir_Left = 0,
    ImGuiDir_Right = 1,
    ImGuiDir_Up = 2,
    ImGuiDir_Down = 3,
    ImGuiDir_COUNT
};
enum ImGuiSortDirection_
{
    ImGuiSortDirection_None = 0,
    ImGuiSortDirection_Ascending = 1,
    ImGuiSortDirection_Descending = 2
};
enum ImGuiKey : int
{
    ImGuiKey_None = 0,
    ImGuiKey_Tab = 512,
    ImGuiKey_LeftArrow,
    ImGuiKey_RightArrow,
    ImGuiKey_UpArrow,
    ImGuiKey_DownArrow,
    ImGuiKey_PageUp,
    ImGuiKey_PageDown,
    ImGuiKey_Home,
    ImGuiKey_End,
    ImGuiKey_Insert,
    ImGuiKey_Delete,
    ImGuiKey_Backspace,
    ImGuiKey_Space,
    ImGuiKey_Enter,
    ImGuiKey_Escape,
    ImGuiKey_LeftCtrl, ImGuiKey_LeftShift, ImGuiKey_LeftAlt, ImGuiKey_LeftSuper,
    ImGuiKey_RightCtrl, ImGuiKey_RightShift, ImGuiKey_RightAlt, ImGuiKey_RightSuper,
    ImGuiKey_Menu,
    ImGuiKey_0, ImGuiKey_1, ImGuiKey_2, ImGuiKey_3, ImGuiKey_4, ImGuiKey_5, ImGuiKey_6, ImGuiKey_7, ImGuiKey_8, ImGuiKey_9,
    ImGuiKey_A, ImGuiKey_B, ImGuiKey_C, ImGuiKey_D, ImGuiKey_E, ImGuiKey_F, ImGuiKey_G, ImGuiKey_H, ImGuiKey_I, ImGuiKey_J,
    ImGuiKey_K, ImGuiKey_L, ImGuiKey_M, ImGuiKey_N, ImGuiKey_O, ImGuiKey_P, ImGuiKey_Q, ImGuiKey_R, ImGuiKey_S, ImGuiKey_T,
    ImGuiKey_U, ImGuiKey_V, ImGuiKey_W, ImGuiKey_X, ImGuiKey_Y, ImGuiKey_Z,
    ImGuiKey_F1, ImGuiKey_F2, ImGuiKey_F3, ImGuiKey_F4, ImGuiKey_F5, ImGuiKey_F6,
    ImGuiKey_F7, ImGuiKey_F8, ImGuiKey_F9, ImGuiKey_F10, ImGuiKey_F11, ImGuiKey_F12,
    ImGuiKey_Apostrophe,
    ImGuiKey_Comma,
    ImGuiKey_Minus,
    ImGuiKey_Period,
    ImGuiKey_Slash,
    ImGuiKey_Semicolon,
    ImGuiKey_Equal,
    ImGuiKey_LeftBracket,
    ImGuiKey_Backslash,
    ImGuiKey_RightBracket,
    ImGuiKey_GraveAccent,
    ImGuiKey_CapsLock,
    ImGuiKey_ScrollLock,
    ImGuiKey_NumLock,
    ImGuiKey_PrintScreen,
    ImGuiKey_Pause,
    ImGuiKey_Keypad0, ImGuiKey_Keypad1, ImGuiKey_Keypad2, ImGuiKey_Keypad3, ImGuiKey_Keypad4,
    ImGuiKey_Keypad5, ImGuiKey_Keypad6, ImGuiKey_Keypad7, ImGuiKey_Keypad8, ImGuiKey_Keypad9,
    ImGuiKey_KeypadDecimal,
    ImGuiKey_KeypadDivide,
    ImGuiKey_KeypadMultiply,
    ImGuiKey_KeypadSubtract,
    ImGuiKey_KeypadAdd,
    ImGuiKey_KeypadEnter,
    ImGuiKey_KeypadEqual,
    ImGuiKey_GamepadStart,
    ImGuiKey_GamepadBack,
    ImGuiKey_GamepadFaceLeft,
    ImGuiKey_GamepadFaceRight,
    ImGuiKey_GamepadFaceUp,
    ImGuiKey_GamepadFaceDown,
    ImGuiKey_GamepadDpadLeft,
    ImGuiKey_GamepadDpadRight,
    ImGuiKey_GamepadDpadUp,
    ImGuiKey_GamepadDpadDown,
    ImGuiKey_GamepadL1,
    ImGuiKey_GamepadR1,
    ImGuiKey_GamepadL2,
    ImGuiKey_GamepadR2,
    ImGuiKey_GamepadL3,
    ImGuiKey_GamepadR3,
    ImGuiKey_GamepadLStickLeft,
    ImGuiKey_GamepadLStickRight,
    ImGuiKey_GamepadLStickUp,
    ImGuiKey_GamepadLStickDown,
    ImGuiKey_GamepadRStickLeft,
    ImGuiKey_GamepadRStickRight,
    ImGuiKey_GamepadRStickUp,
    ImGuiKey_GamepadRStickDown,
    ImGuiKey_MouseLeft, ImGuiKey_MouseRight, ImGuiKey_MouseMiddle, ImGuiKey_MouseX1, ImGuiKey_MouseX2, ImGuiKey_MouseWheelX, ImGuiKey_MouseWheelY,
    ImGuiKey_ReservedForModCtrl, ImGuiKey_ReservedForModShift, ImGuiKey_ReservedForModAlt, ImGuiKey_ReservedForModSuper,
    ImGuiKey_COUNT,
    ImGuiMod_None = 0,
    ImGuiMod_Ctrl = 1 << 12,
    ImGuiMod_Shift = 1 << 13,
    ImGuiMod_Alt = 1 << 14,
    ImGuiMod_Super = 1 << 15,
    ImGuiMod_Shortcut = 1 << 11,
    ImGuiMod_Mask_ = 0xF800,
    ImGuiKey_NamedKey_BEGIN = 512,
    ImGuiKey_NamedKey_END = ImGuiKey_COUNT,
    ImGuiKey_NamedKey_COUNT = ImGuiKey_NamedKey_END - ImGuiKey_NamedKey_BEGIN,
    ImGuiKey_KeysData_SIZE = ImGuiKey_COUNT,
    ImGuiKey_KeysData_OFFSET = 0,
};
enum ImGuiNavInput
{
    ImGuiNavInput_Activate, ImGuiNavInput_Cancel, ImGuiNavInput_Input, ImGuiNavInput_Menu, ImGuiNavInput_DpadLeft, ImGuiNavInput_DpadRight, ImGuiNavInput_DpadUp, ImGuiNavInput_DpadDown,
    ImGuiNavInput_LStickLeft, ImGuiNavInput_LStickRight, ImGuiNavInput_LStickUp, ImGuiNavInput_LStickDown, ImGuiNavInput_FocusPrev, ImGuiNavInput_FocusNext, ImGuiNavInput_TweakSlow, ImGuiNavInput_TweakFast,
    ImGuiNavInput_COUNT,
};
enum ImGuiConfigFlags_
{
    ImGuiConfigFlags_None = 0,
    ImGuiConfigFlags_NavEnableKeyboard = 1 << 0,
    ImGuiConfigFlags_NavEnableGamepad = 1 << 1,
    ImGuiConfigFlags_NavEnableSetMousePos = 1 << 2,
    ImGuiConfigFlags_NavNoCaptureKeyboard = 1 << 3,
    ImGuiConfigFlags_NoMouse = 1 << 4,
    ImGuiConfigFlags_NoMouseCursorChange = 1 << 5,
    ImGuiConfigFlags_IsSRGB = 1 << 20,
    ImGuiConfigFlags_IsTouchScreen = 1 << 21,
};
enum ImGuiBackendFlags_
{
    ImGuiBackendFlags_None = 0,
    ImGuiBackendFlags_HasGamepad = 1 << 0,
    ImGuiBackendFlags_HasMouseCursors = 1 << 1,
    ImGuiBackendFlags_HasSetMousePos = 1 << 2,
    ImGuiBackendFlags_RendererHasVtxOffset = 1 << 3,
};
enum ImGuiCol_
{
    ImGuiCol_Text,
    ImGuiCol_TextDisabled,
    ImGuiCol_WindowBg,
    ImGuiCol_ChildBg,
    ImGuiCol_PopupBg,
    ImGuiCol_Border,
    ImGuiCol_BorderShadow,
    ImGuiCol_FrameBg,
    ImGuiCol_FrameBgHovered,
    ImGuiCol_FrameBgActive,
    ImGuiCol_TitleBg,
    ImGuiCol_TitleBgActive,
    ImGuiCol_TitleBgCollapsed,
    ImGuiCol_MenuBarBg,
    ImGuiCol_ScrollbarBg,
    ImGuiCol_ScrollbarGrab,
    ImGuiCol_ScrollbarGrabHovered,
    ImGuiCol_ScrollbarGrabActive,
    ImGuiCol_CheckMark,
    ImGuiCol_SliderGrab,
    ImGuiCol_SliderGrabActive,
    ImGuiCol_Button,
    ImGuiCol_ButtonHovered,
    ImGuiCol_ButtonActive,
    ImGuiCol_Header,
    ImGuiCol_HeaderHovered,
    ImGuiCol_HeaderActive,
    ImGuiCol_Separator,
    ImGuiCol_SeparatorHovered,
    ImGuiCol_SeparatorActive,
    ImGuiCol_ResizeGrip,
    ImGuiCol_ResizeGripHovered,
    ImGuiCol_ResizeGripActive,
    ImGuiCol_Tab,
    ImGuiCol_TabHovered,
    ImGuiCol_TabActive,
    ImGuiCol_TabUnfocused,
    ImGuiCol_TabUnfocusedActive,
    ImGuiCol_PlotLines,
    ImGuiCol_PlotLinesHovered,
    ImGuiCol_PlotHistogram,
    ImGuiCol_PlotHistogramHovered,
    ImGuiCol_TableHeaderBg,
    ImGuiCol_TableBorderStrong,
    ImGuiCol_TableBorderLight,
    ImGuiCol_TableRowBg,
    ImGuiCol_TableRowBgAlt,
    ImGuiCol_TextSelectedBg,
    ImGuiCol_DragDropTarget,
    ImGuiCol_NavHighlight,
    ImGuiCol_NavWindowingHighlight,
    ImGuiCol_NavWindowingDimBg,
    ImGuiCol_ModalWindowDimBg,
    ImGuiCol_COUNT
};
enum ImGuiStyleVar_
{
    ImGuiStyleVar_Alpha,
    ImGuiStyleVar_DisabledAlpha,
    ImGuiStyleVar_WindowPadding,
    ImGuiStyleVar_WindowRounding,
    ImGuiStyleVar_WindowBorderSize,
    ImGuiStyleVar_WindowMinSize,
    ImGuiStyleVar_WindowTitleAlign,
    ImGuiStyleVar_ChildRounding,
    ImGuiStyleVar_ChildBorderSize,
    ImGuiStyleVar_PopupRounding,
    ImGuiStyleVar_PopupBorderSize,
    ImGuiStyleVar_FramePadding,
    ImGuiStyleVar_FrameRounding,
    ImGuiStyleVar_FrameBorderSize,
    ImGuiStyleVar_ItemSpacing,
    ImGuiStyleVar_ItemInnerSpacing,
    ImGuiStyleVar_IndentSpacing,
    ImGuiStyleVar_CellPadding,
    ImGuiStyleVar_ScrollbarSize,
    ImGuiStyleVar_ScrollbarRounding,
    ImGuiStyleVar_GrabMinSize,
    ImGuiStyleVar_GrabRounding,
    ImGuiStyleVar_TabRounding,
    ImGuiStyleVar_ButtonTextAlign,
    ImGuiStyleVar_SelectableTextAlign,
    ImGuiStyleVar_SeparatorTextBorderSize,
    ImGuiStyleVar_SeparatorTextAlign,
    ImGuiStyleVar_SeparatorTextPadding,
    ImGuiStyleVar_COUNT
};
enum ImGuiButtonFlags_
{
    ImGuiButtonFlags_None = 0,
    ImGuiButtonFlags_MouseButtonLeft = 1 << 0,
    ImGuiButtonFlags_MouseButtonRight = 1 << 1,
    ImGuiButtonFlags_MouseButtonMiddle = 1 << 2,
    ImGuiButtonFlags_MouseButtonMask_ = ImGuiButtonFlags_MouseButtonLeft | ImGuiButtonFlags_MouseButtonRight | ImGuiButtonFlags_MouseButtonMiddle,
    ImGuiButtonFlags_MouseButtonDefault_ = ImGuiButtonFlags_MouseButtonLeft,
};
enum ImGuiColorEditFlags_
{
    ImGuiColorEditFlags_None = 0,
    ImGuiColorEditFlags_NoAlpha = 1 << 1,
    ImGuiColorEditFlags_NoPicker = 1 << 2,
    ImGuiColorEditFlags_NoOptions = 1 << 3,
    ImGuiColorEditFlags_NoSmallPreview = 1 << 4,
    ImGuiColorEditFlags_NoInputs = 1 << 5,
    ImGuiColorEditFlags_NoTooltip = 1 << 6,
    ImGuiColorEditFlags_NoLabel = 1 << 7,
    ImGuiColorEditFlags_NoSidePreview = 1 << 8,
    ImGuiColorEditFlags_NoDragDrop = 1 << 9,
    ImGuiColorEditFlags_NoBorder = 1 << 10,
    ImGuiColorEditFlags_AlphaBar = 1 << 16,
    ImGuiColorEditFlags_AlphaPreview = 1 << 17,
    ImGuiColorEditFlags_AlphaPreviewHalf= 1 << 18,
    ImGuiColorEditFlags_HDR = 1 << 19,
    ImGuiColorEditFlags_DisplayRGB = 1 << 20,
    ImGuiColorEditFlags_DisplayHSV = 1 << 21,
    ImGuiColorEditFlags_DisplayHex = 1 << 22,
    ImGuiColorEditFlags_Uint8 = 1 << 23,
    ImGuiColorEditFlags_Float = 1 << 24,
    ImGuiColorEditFlags_PickerHueBar = 1 << 25,
    ImGuiColorEditFlags_PickerHueWheel = 1 << 26,
    ImGuiColorEditFlags_InputRGB = 1 << 27,
    ImGuiColorEditFlags_InputHSV = 1 << 28,
    ImGuiColorEditFlags_DefaultOptions_ = ImGuiColorEditFlags_Uint8 | ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_PickerHueBar,
    ImGuiColorEditFlags_DisplayMask_ = ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_DisplayHSV | ImGuiColorEditFlags_DisplayHex,
    ImGuiColorEditFlags_DataTypeMask_ = ImGuiColorEditFlags_Uint8 | ImGuiColorEditFlags_Float,
    ImGuiColorEditFlags_PickerMask_ = ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_PickerHueBar,
    ImGuiColorEditFlags_InputMask_ = ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_InputHSV,
};
enum ImGuiSliderFlags_
{
    ImGuiSliderFlags_None = 0,
    ImGuiSliderFlags_AlwaysClamp = 1 << 4,
    ImGuiSliderFlags_Logarithmic = 1 << 5,
    ImGuiSliderFlags_NoRoundToFormat = 1 << 6,
    ImGuiSliderFlags_NoInput = 1 << 7,
    ImGuiSliderFlags_InvalidMask_ = 0x7000000F,
};
enum ImGuiMouseButton_
{
    ImGuiMouseButton_Left = 0,
    ImGuiMouseButton_Right = 1,
    ImGuiMouseButton_Middle = 2,
    ImGuiMouseButton_COUNT = 5
};
enum ImGuiMouseCursor_
{
    ImGuiMouseCursor_None = -1,
    ImGuiMouseCursor_Arrow = 0,
    ImGuiMouseCursor_TextInput,
    ImGuiMouseCursor_ResizeAll,
    ImGuiMouseCursor_ResizeNS,
    ImGuiMouseCursor_ResizeEW,
    ImGuiMouseCursor_ResizeNESW,
    ImGuiMouseCursor_ResizeNWSE,
    ImGuiMouseCursor_Hand,
    ImGuiMouseCursor_NotAllowed,
    ImGuiMouseCursor_COUNT
};
enum ImGuiMouseSource : int
{
    ImGuiMouseSource_Mouse = 0,
    ImGuiMouseSource_TouchScreen,
    ImGuiMouseSource_Pen,
    ImGuiMouseSource_COUNT
};
enum ImGuiCond_
{
    ImGuiCond_None = 0,
    ImGuiCond_Always = 1 << 0,
    ImGuiCond_Once = 1 << 1,
    ImGuiCond_FirstUseEver = 1 << 2,
    ImGuiCond_Appearing = 1 << 3,
};
struct ImNewWrapper {};
inline void* operator new(size_t, ImNewWrapper, void* ptr) { return ptr; }
inline void operator delete(void*, ImNewWrapper, void*) {}
template<typename T> void IM_DELETE(T* p) { if (p) { p->~T(); ImGui::MemFree(p); } }
template<typename T>
struct ImVector
{
    int Size;
    int Capacity;
    T* Data;
    typedef T value_type;
    typedef value_type* iterator;
    typedef const value_type* const_iterator;
    inline ImVector() { Size = Capacity = 0; Data =                                                                                          ((void *)0)                                                                                             ; }
    inline ImVector(const ImVector<T>& src) { Size = Capacity = 0; Data =                                                                                          ((void *)0)                                                                                             ; operator=(src); }
    inline ImVector<T>& operator=(const ImVector<T>& src) { clear(); resize(src.Size); if (src.Data) memcpy(Data, src.Data, (size_t)Size * sizeof(T)); return *this; }
    inline ~ImVector() { if (Data) ImGui::MemFree(Data); }
    inline void clear() { if (Data) { Size = Capacity = 0; ImGui::MemFree(Data); Data =                                                                                                                     ((void *)0)                                                                                                                        ; } }
    inline void clear_delete() { for (int n = 0; n < Size; n++) IM_DELETE(Data[n]); clear(); }
    inline void clear_destruct() { for (int n = 0; n < Size; n++) Data[n].~T(); clear(); }
    inline bool empty() const { return Size == 0; }
    inline int size() const { return Size; }
    inline int size_in_bytes() const { return Size * (int)sizeof(T); }
    inline int max_size() const { return 0x7FFFFFFF / (int)sizeof(T); }
    inline int capacity() const { return Capacity; }
    inline T& operator[](int i) {                                                              ((void) sizeof ((                                                             i >= 0 && i < Size                                                             ) ? 1 : 0), __extension__ ({ if (                                                             i >= 0 && i < Size                                                             ) ; else __assert_fail (                                                             "i >= 0 && i < Size"                                                             , "../imgui/imgui.h", 1840, __extension__ __PRETTY_FUNCTION__); }))                                                                                          ; return Data[i]; }
    inline const T& operator[](int i) const {                                                              ((void) sizeof ((                                                             i >= 0 && i < Size                                                             ) ? 1 : 0), __extension__ ({ if (                                                             i >= 0 && i < Size                                                             ) ; else __assert_fail (                                                             "i >= 0 && i < Size"                                                             , "../imgui/imgui.h", 1841, __extension__ __PRETTY_FUNCTION__); }))                                                                                          ; return Data[i]; }
    inline T* begin() { return Data; }
    inline const T* begin() const { return Data; }
    inline T* end() { return Data + Size; }
    inline const T* end() const { return Data + Size; }
    inline T& front() {                                                              ((void) sizeof ((                                                             Size > 0                                                             ) ? 1 : 0), __extension__ ({ if (                                                             Size > 0                                                             ) ; else __assert_fail (                                                             "Size > 0"                                                             , "../imgui/imgui.h", 1847, __extension__ __PRETTY_FUNCTION__); }))                                                                                ; return Data[0]; }
    inline const T& front() const {                                                              ((void) sizeof ((                                                             Size > 0                                                             ) ? 1 : 0), __extension__ ({ if (                                                             Size > 0                                                             ) ; else __assert_fail (                                                             "Size > 0"                                                             , "../imgui/imgui.h", 1848, __extension__ __PRETTY_FUNCTION__); }))                                                                                ; return Data[0]; }
    inline T& back() {                                                              ((void) sizeof ((                                                             Size > 0                                                             ) ? 1 : 0), __extension__ ({ if (                                                             Size > 0                                                             ) ; else __assert_fail (                                                             "Size > 0"                                                             , "../imgui/imgui.h", 1849, __extension__ __PRETTY_FUNCTION__); }))                                                                                ; return Data[Size - 1]; }
    inline const T& back() const {                                                              ((void) sizeof ((                                                             Size > 0                                                             ) ? 1 : 0), __extension__ ({ if (                                                             Size > 0                                                             ) ; else __assert_fail (                                                             "Size > 0"                                                             , "../imgui/imgui.h", 1850, __extension__ __PRETTY_FUNCTION__); }))                                                                                ; return Data[Size - 1]; }
    inline void swap(ImVector<T>& rhs) { int rhs_size = rhs.Size; rhs.Size = Size; Size = rhs_size; int rhs_cap = rhs.Capacity; rhs.Capacity = Capacity; Capacity = rhs_cap; T* rhs_data = rhs.Data; rhs.Data = Data; Data = rhs_data; }
    inline int _grow_capacity(int sz) const { int new_capacity = Capacity ? (Capacity + Capacity / 2) : 8; return new_capacity > sz ? new_capacity : sz; }
    inline void resize(int new_size) { if (new_size > Capacity) reserve(_grow_capacity(new_size)); Size = new_size; }
    inline void resize(int new_size, const T& v) { if (new_size > Capacity) reserve(_grow_capacity(new_size)); if (new_size > Size) for (int n = Size; n < new_size; n++) memcpy(&Data[n], &v, sizeof(v)); Size = new_size; }
    inline void shrink(int new_size) {                                                              ((void) sizeof ((                                                             new_size <= Size                                                             ) ? 1 : 0), __extension__ ({ if (                                                             new_size <= Size                                                             ) ; else __assert_fail (                                                             "new_size <= Size"                                                             , "../imgui/imgui.h", 1856, __extension__ __PRETTY_FUNCTION__); }))                                                                                        ; Size = new_size; }
    inline void reserve(int new_capacity) { if (new_capacity <= Capacity) return; T* new_data = (T*)ImGui::MemAlloc((size_t)new_capacity * sizeof(T)); if (Data) { memcpy(new_data, Data, (size_t)Size * sizeof(T)); ImGui::MemFree(Data); } Data = new_data; Capacity = new_capacity; }
    inline void reserve_discard(int new_capacity) { if (new_capacity <= Capacity) return; if (Data) ImGui::MemFree(Data); Data = (T*)ImGui::MemAlloc((size_t)new_capacity * sizeof(T)); Capacity = new_capacity; }
    inline void push_back(const T& v) { if (Size == Capacity) reserve(_grow_capacity(Size + 1)); memcpy(&Data[Size], &v, sizeof(v)); Size++; }
    inline void pop_back() {                                                              ((void) sizeof ((                                                             Size > 0                                                             ) ? 1 : 0), __extension__ ({ if (                                                             Size > 0                                                             ) ; else __assert_fail (                                                             "Size > 0"                                                             , "../imgui/imgui.h", 1862, __extension__ __PRETTY_FUNCTION__); }))                                                                                ; Size--; }
    inline void push_front(const T& v) { if (Size == 0) push_back(v); else insert(Data, v); }
    inline T* erase(const T* it) {                                                              ((void) sizeof ((                                                             it >= Data && it < Data + Size                                                             ) ? 1 : 0), __extension__ ({ if (                                                             it >= Data && it < Data + Size                                                             ) ; else __assert_fail (                                                             "it >= Data && it < Data + Size"                                                             , "../imgui/imgui.h", 1864, __extension__ __PRETTY_FUNCTION__); }))                                                                                                      ; const ptrdiff_t off = it - Data; memmove(Data + off, Data + off + 1, ((size_t)Size - (size_t)off - 1) * sizeof(T)); Size--; return Data + off; }
    inline T* erase(const T* it, const T* it_last){                                                              ((void) sizeof ((                                                             it >= Data && it < Data + Size && it_last >= it && it_last <= Data + Size                                                             ) ? 1 : 0), __extension__ ({ if (                                                             it >= Data && it < Data + Size && it_last >= it && it_last <= Data + Size                                                             ) ; else __assert_fail (                                                             "it >= Data && it < Data + Size && it_last >= it && it_last <= Data + Size"                                                             , "../imgui/imgui.h", 1865, __extension__ __PRETTY_FUNCTION__); }))                                                                                                                                                 ; const ptrdiff_t count = it_last - it; const ptrdiff_t off = it - Data; memmove(Data + off, Data + off + count, ((size_t)Size - (size_t)off - (size_t)count) * sizeof(T)); Size -= (int)count; return Data + off; }
    inline T* erase_unsorted(const T* it) {                                                              ((void) sizeof ((                                                             it >= Data && it < Data + Size                                                             ) ? 1 : 0), __extension__ ({ if (                                                             it >= Data && it < Data + Size                                                             ) ; else __assert_fail (                                                             "it >= Data && it < Data + Size"                                                             , "../imgui/imgui.h", 1866, __extension__ __PRETTY_FUNCTION__); }))                                                                                                      ; const ptrdiff_t off = it - Data; if (it < Data + Size - 1) memcpy(Data + off, Data + Size - 1, sizeof(T)); Size--; return Data + off; }
    inline T* insert(const T* it, const T& v) {                                                              ((void) sizeof ((                                                             it >= Data && it <= Data + Size                                                             ) ? 1 : 0), __extension__ ({ if (                                                             it >= Data && it <= Data + Size                                                             ) ; else __assert_fail (                                                             "it >= Data && it <= Data + Size"                                                             , "../imgui/imgui.h", 1867, __extension__ __PRETTY_FUNCTION__); }))                                                                                                       ; const ptrdiff_t off = it - Data; if (Size == Capacity) reserve(_grow_capacity(Size + 1)); if (off < (int)Size) memmove(Data + off + 1, Data + off, ((size_t)Size - (size_t)off) * sizeof(T)); memcpy(&Data[off], &v, sizeof(v)); Size++; return Data + off; }
    inline bool contains(const T& v) const { const T* data = Data; const T* data_end = Data + Size; while (data < data_end) if (*data++ == v) return true; return false; }
    inline T* find(const T& v) { T* data = Data; const T* data_end = Data + Size; while (data < data_end) if (*data == v) break; else ++data; return data; }
    inline const T* find(const T& v) const { const T* data = Data; const T* data_end = Data + Size; while (data < data_end) if (*data == v) break; else ++data; return data; }
    inline bool find_erase(const T& v) { const T* it = find(v); if (it < Data + Size) { erase(it); return true; } return false; }
    inline bool find_erase_unsorted(const T& v) { const T* it = find(v); if (it < Data + Size) { erase_unsorted(it); return true; } return false; }
    inline int index_from_ptr(const T* it) const {                                                              ((void) sizeof ((                                                             it >= Data && it < Data + Size                                                             ) ? 1 : 0), __extension__ ({ if (                                                             it >= Data && it < Data + Size                                                             ) ; else __assert_fail (                                                             "it >= Data && it < Data + Size"                                                             , "../imgui/imgui.h", 1873, __extension__ __PRETTY_FUNCTION__); }))                                                                                                      ; const ptrdiff_t off = it - Data; return (int)off; }
};
struct ImGuiStyle
{
    float Alpha;
    float DisabledAlpha;
    ImVec2 WindowPadding;
    float WindowRounding;
    float WindowBorderSize;
    ImVec2 WindowMinSize;
    ImVec2 WindowTitleAlign;
    ImGuiDir WindowMenuButtonPosition;
    float ChildRounding;
    float ChildBorderSize;
    float PopupRounding;
    float PopupBorderSize;
    ImVec2 FramePadding;
    float FrameRounding;
    float FrameBorderSize;
    ImVec2 ItemSpacing;
    ImVec2 ItemInnerSpacing;
    ImVec2 CellPadding;
    ImVec2 TouchExtraPadding;
    float IndentSpacing;
    float ColumnsMinSpacing;
    float ScrollbarSize;
    float ScrollbarRounding;
    float GrabMinSize;
    float GrabRounding;
    float LogSliderDeadzone;
    float TabRounding;
    float TabBorderSize;
    float TabMinWidthForCloseButton;
    ImGuiDir ColorButtonPosition;
    ImVec2 ButtonTextAlign;
    ImVec2 SelectableTextAlign;
    float SeparatorTextBorderSize;
    ImVec2 SeparatorTextAlign;
    ImVec2 SeparatorTextPadding;
    ImVec2 DisplayWindowPadding;
    ImVec2 DisplaySafeAreaPadding;
    float MouseCursorScale;
    bool AntiAliasedLines;
    bool AntiAliasedLinesUseTex;
    bool AntiAliasedFill;
    float CurveTessellationTol;
    float CircleTessellationMaxError;
    ImVec4 Colors[ImGuiCol_COUNT];
    float HoverStationaryDelay;
    float HoverDelayShort;
    float HoverDelayNormal;
    ImGuiHoveredFlags HoverFlagsForTooltipMouse;
    ImGuiHoveredFlags HoverFlagsForTooltipNav;
    ImGuiStyle();
    void ScaleAllSizes(float scale_factor);
};
struct ImGuiKeyData
{
    bool Down;
    float DownDuration;
    float DownDurationPrev;
    float AnalogValue;
};
struct ImGuiIO
{
    ImGuiConfigFlags ConfigFlags;
    ImGuiBackendFlags BackendFlags;
    ImVec2 DisplaySize;
    float DeltaTime;
    float IniSavingRate;
    const char* IniFilename;
    const char* LogFilename;
    void* UserData;
    ImFontAtlas*Fonts;
    float FontGlobalScale;
    bool FontAllowUserScaling;
    ImFont* FontDefault;
    ImVec2 DisplayFramebufferScale;
    bool MouseDrawCursor;
    bool ConfigMacOSXBehaviors;
    bool ConfigInputTrickleEventQueue;
    bool ConfigInputTextCursorBlink;
    bool ConfigInputTextEnterKeepActive;
    bool ConfigDragClickToInputText;
    bool ConfigWindowsResizeFromEdges;
    bool ConfigWindowsMoveFromTitleBarOnly;
    float ConfigMemoryCompactTimer;
    float MouseDoubleClickTime;
    float MouseDoubleClickMaxDist;
    float MouseDragThreshold;
    float KeyRepeatDelay;
    float KeyRepeatRate;
    bool ConfigDebugBeginReturnValueOnce;
    bool ConfigDebugBeginReturnValueLoop;
    bool ConfigDebugIgnoreFocusLoss;
    bool ConfigDebugIniSettings;
    const char* BackendPlatformName;
    const char* BackendRendererName;
    void* BackendPlatformUserData;
    void* BackendRendererUserData;
    void* BackendLanguageUserData;
    const char* (*GetClipboardTextFn)(void* user_data);
    void (*SetClipboardTextFn)(void* user_data, const char* text);
    void* ClipboardUserData;
    void (*SetPlatformImeDataFn)(ImGuiViewport* viewport, ImGuiPlatformImeData* data);
    void* _UnusedPadding;
    ImWchar PlatformLocaleDecimalPoint;
    void AddKeyEvent(ImGuiKey key, bool down);
    void AddKeyAnalogEvent(ImGuiKey key, bool down, float v);
    void AddMousePosEvent(float x, float y);
    void AddMouseButtonEvent(int button, bool down);
    void AddMouseWheelEvent(float wheel_x, float wheel_y);
    void AddMouseSourceEvent(ImGuiMouseSource source);
    void AddFocusEvent(bool focused);
    void AddInputCharacter(unsigned int c);
    void AddInputCharacterUTF16(ImWchar16 c);
    void AddInputCharactersUTF8(const char* str);
    void SetKeyEventNativeData(ImGuiKey key, int native_keycode, int native_scancode, int native_legacy_index = -1);
    void SetAppAcceptingEvents(bool accepting_events);
    void ClearEventsQueue();
    void ClearInputKeys();
    bool WantCaptureMouse;
    bool WantCaptureKeyboard;
    bool WantTextInput;
    bool WantSetMousePos;
    bool WantSaveIniSettings;
    bool NavActive;
    bool NavVisible;
    float Framerate;
    int MetricsRenderVertices;
    int MetricsRenderIndices;
    int MetricsRenderWindows;
    int MetricsActiveWindows;
    int MetricsActiveAllocations;
    ImVec2 MouseDelta;
    int KeyMap[ImGuiKey_COUNT];
    bool KeysDown[ImGuiKey_COUNT];
    float NavInputs[ImGuiNavInput_COUNT];
    ImGuiContext* Ctx;
    ImVec2 MousePos;
    bool MouseDown[5];
    float MouseWheel;
    float MouseWheelH;
    ImGuiMouseSource MouseSource;
    bool KeyCtrl;
    bool KeyShift;
    bool KeyAlt;
    bool KeySuper;
    ImGuiKeyChord KeyMods;
    ImGuiKeyData KeysData[ImGuiKey_KeysData_SIZE];
    bool WantCaptureMouseUnlessPopupClose;
    ImVec2 MousePosPrev;
    ImVec2 MouseClickedPos[5];
    double MouseClickedTime[5];
    bool MouseClicked[5];
    bool MouseDoubleClicked[5];
    ImU16 MouseClickedCount[5];
    ImU16 MouseClickedLastCount[5];
    bool MouseReleased[5];
    bool MouseDownOwned[5];
    bool MouseDownOwnedUnlessPopupClose[5];
    bool MouseWheelRequestAxisSwap;
    float MouseDownDuration[5];
    float MouseDownDurationPrev[5];
    float MouseDragMaxDistanceSqr[5];
    float PenPressure;
    bool AppFocusLost;
    bool AppAcceptingEvents;
    ImS8 BackendUsingLegacyKeyArrays;
    bool BackendUsingLegacyNavInputArray;
    ImWchar16 InputQueueSurrogate;
    ImVector<ImWchar> InputQueueCharacters;
    ImGuiIO();
};
struct ImGuiInputTextCallbackData
{
    ImGuiContext* Ctx;
    ImGuiInputTextFlags EventFlag;
    ImGuiInputTextFlags Flags;
    void* UserData;
    ImWchar EventChar;
    ImGuiKey EventKey;
    char* Buf;
    int BufTextLen;
    int BufSize;
    bool BufDirty;
    int CursorPos;
    int SelectionStart;
    int SelectionEnd;
    ImGuiInputTextCallbackData();
    void DeleteChars(int pos, int bytes_count);
    void InsertChars(int pos, const char* text, const char* text_end =                                                                                      ((void *)0)                                                                                         );
    void SelectAll() { SelectionStart = 0; SelectionEnd = BufTextLen; }
    void ClearSelection() { SelectionStart = SelectionEnd = BufTextLen; }
    bool HasSelection() const { return SelectionStart != SelectionEnd; }
};
struct ImGuiSizeCallbackData
{
    void* UserData;
    ImVec2 Pos;
    ImVec2 CurrentSize;
    ImVec2 DesiredSize;
};
struct ImGuiPayload
{
    void* Data;
    int DataSize;
    ImGuiID SourceId;
    ImGuiID SourceParentId;
    int DataFrameCount;
    char DataType[32 + 1];
    bool Preview;
    bool Delivery;
    ImGuiPayload() { Clear(); }
    void Clear() { SourceId = SourceParentId = 0; Data =                                                            ((void *)0)                                                               ; DataSize = 0; memset(DataType, 0, sizeof(DataType)); DataFrameCount = -1; Preview = Delivery = false; }
    bool IsDataType(const char* type) const { return DataFrameCount != -1 && strcmp(type, DataType) == 0; }
    bool IsPreview() const { return Preview; }
    bool IsDelivery() const { return Delivery; }
};
struct ImGuiTableColumnSortSpecs
{
    ImGuiID ColumnUserID;
    ImS16 ColumnIndex;
    ImS16 SortOrder;
    ImGuiSortDirection SortDirection : 8;
    ImGuiTableColumnSortSpecs() { memset(this, 0, sizeof(*this)); }
};
struct ImGuiTableSortSpecs
{
    const ImGuiTableColumnSortSpecs* Specs;
    int SpecsCount;
    bool SpecsDirty;
    ImGuiTableSortSpecs() { memset(this, 0, sizeof(*this)); }
};
struct ImGuiOnceUponAFrame
{
    ImGuiOnceUponAFrame() { RefFrame = -1; }
    mutable int RefFrame;
    operator bool() const { int current_frame = ImGui::GetFrameCount(); if (RefFrame == current_frame) return false; RefFrame = current_frame; return true; }
};
struct ImGuiTextFilter
{
    ImGuiTextFilter(const char* default_filter = "");
    bool Draw(const char* label = "Filter (inc,-exc)", float width = 0.0f);
    bool PassFilter(const char* text, const char* text_end =                                                                            ((void *)0)                                                                               ) const;
    void Build();
    void Clear() { InputBuf[0] = 0; Build(); }
    bool IsActive() const { return !Filters.empty(); }
    struct ImGuiTextRange
    {
        const char* b;
        const char* e;
        ImGuiTextRange() { b = e =                                                                  ((void *)0)                                                                     ; }
        ImGuiTextRange(const char* _b, const char* _e) { b = _b; e = _e; }
        bool empty() const { return b == e; }
        void split(char separator, ImVector<ImGuiTextRange>* out) const;
    };
    char InputBuf[256];
    ImVector<ImGuiTextRange>Filters;
    int CountGrep;
};
struct ImGuiTextBuffer
{
    ImVector<char> Buf;
    static char EmptyString[1];
    ImGuiTextBuffer() { }
    inline char operator[](int i) const {                                                  ((void) sizeof ((                                                 Buf.Data !=                                                  ((void *)0)) ? 1 : 0), __extension__ ({ if (                                                 Buf.Data !=                                                  ((void *)0)) ; else __assert_fail (                                                 "Buf.Data != ((void *)0)"                                                 , "../imgui/imgui.h", 2306, __extension__ __PRETTY_FUNCTION__); }))                                                                            ; return Buf.Data[i]; }
    const char* begin() const { return Buf.Data ? &Buf.front() : EmptyString; }
    const char* end() const { return Buf.Data ? &Buf.back() : EmptyString; }
    int size() const { return Buf.Size ? Buf.Size - 1 : 0; }
    bool empty() const { return Buf.Size <= 1; }
    void clear() { Buf.clear(); }
    void reserve(int capacity) { Buf.reserve(capacity); }
    const char* c_str() const { return Buf.Data ? Buf.Data : EmptyString; }
    void append(const char* str, const char* str_end =                                                                      ((void *)0)                                                                         );
    void appendf(const char* fmt, ...) __attribute__((format(printf, 2, 2 +1)));
    void appendfv(const char* fmt, va_list args) __attribute__((format(printf, 2, 0)));
};
struct ImGuiStorage
{
    struct ImGuiStoragePair
    {
        ImGuiID key;
        union { int val_i; float val_f; void* val_p; };
        ImGuiStoragePair(ImGuiID _key, int _val_i) { key = _key; val_i = _val_i; }
        ImGuiStoragePair(ImGuiID _key, float _val_f) { key = _key; val_f = _val_f; }
        ImGuiStoragePair(ImGuiID _key, void* _val_p) { key = _key; val_p = _val_p; }
    };
    ImVector<ImGuiStoragePair> Data;
    void Clear() { Data.clear(); }
    int GetInt(ImGuiID key, int default_val = 0) const;
    void SetInt(ImGuiID key, int val);
    bool GetBool(ImGuiID key, bool default_val = false) const;
    void SetBool(ImGuiID key, bool val);
    float GetFloat(ImGuiID key, float default_val = 0.0f) const;
    void SetFloat(ImGuiID key, float val);
    void* GetVoidPtr(ImGuiID key) const;
    void SetVoidPtr(ImGuiID key, void* val);
    int* GetIntRef(ImGuiID key, int default_val = 0);
    bool* GetBoolRef(ImGuiID key, bool default_val = false);
    float* GetFloatRef(ImGuiID key, float default_val = 0.0f);
    void** GetVoidPtrRef(ImGuiID key, void* default_val =                                                                       ((void *)0)                                                                          );
    void SetAllInt(int val);
    void BuildSortByKey();
};
struct ImGuiListClipper
{
    ImGuiContext* Ctx;
    int DisplayStart;
    int DisplayEnd;
    int ItemsCount;
    float ItemsHeight;
    float StartPosY;
    void* TempData;
    ImGuiListClipper();
    ~ImGuiListClipper();
    void Begin(int items_count, float items_height = -1.0f);
    void End();
    bool Step();
    inline void IncludeItemByIndex(int item_index) { IncludeItemsByIndex(item_index, item_index + 1); }
    void IncludeItemsByIndex(int item_begin, int item_end);
};
struct ImColor
{
    ImVec4 Value;
    constexpr ImColor() { }
    constexpr ImColor(float r, float g, float b, float a = 1.0f) : Value(r, g, b, a) { }
    constexpr ImColor(const ImVec4& col) : Value(col) {}
    constexpr ImColor(int r, int g, int b, int a = 255) : Value((float)r * (1.0f / 255.0f), (float)g * (1.0f / 255.0f), (float)b * (1.0f / 255.0f), (float)a* (1.0f / 255.0f)) {}
    constexpr ImColor(ImU32 rgba) : Value((float)((rgba >> 0) & 0xFF) * (1.0f / 255.0f), (float)((rgba >> 8) & 0xFF) * (1.0f / 255.0f), (float)((rgba >> 16) & 0xFF) * (1.0f / 255.0f), (float)((rgba >> 24) & 0xFF) * (1.0f / 255.0f)) {}
    inline operator ImU32() const { return ImGui::ColorConvertFloat4ToU32(Value); }
    inline operator ImVec4() const { return Value; }
    inline void SetHSV(float h, float s, float v, float a = 1.0f){ ImGui::ColorConvertHSVtoRGB(h, s, v, Value.x, Value.y, Value.z); Value.w = a; }
    static ImColor HSV(float h, float s, float v, float a = 1.0f) { float r, g, b; ImGui::ColorConvertHSVtoRGB(h, s, v, r, g, b); return ImColor(r, g, b, a); }
};
typedef void (*ImDrawCallback)(const ImDrawList* parent_list, const ImDrawCmd* cmd);
struct ImDrawCmd
{
    ImVec4 ClipRect;
    ImTextureID TextureId;
    unsigned int VtxOffset;
    unsigned int IdxOffset;
    unsigned int ElemCount;
    ImDrawCallback UserCallback;
    void* UserCallbackData;
    ImDrawCmd() { memset(this, 0, sizeof(*this)); }
    inline ImTextureID GetTexID() const { return TextureId; }
};
struct ImDrawVert
{
    ImVec2 pos;
    ImVec2 uv;
    ImU32 col;
};
struct ImDrawCmdHeader
{
    ImVec4 ClipRect;
    ImTextureID TextureId;
    unsigned int VtxOffset;
};
struct ImDrawChannel
{
    ImVector<ImDrawCmd> _CmdBuffer;
    ImVector<ImDrawIdx> _IdxBuffer;
};
struct ImDrawListSplitter
{
    int _Current;
    int _Count;
    ImVector<ImDrawChannel> _Channels;
    inline ImDrawListSplitter() { memset(this, 0, sizeof(*this)); }
    inline ~ImDrawListSplitter() { ClearFreeMemory(); }
    inline void Clear() { _Current = 0; _Count = 1; }
    void ClearFreeMemory();
    void Split(ImDrawList* draw_list, int count);
    void Merge(ImDrawList* draw_list);
    void SetCurrentChannel(ImDrawList* draw_list, int channel_idx);
};
enum ImDrawFlags_
{
    ImDrawFlags_None = 0,
    ImDrawFlags_Closed = 1 << 0,
    ImDrawFlags_RoundCornersTopLeft = 1 << 4,
    ImDrawFlags_RoundCornersTopRight = 1 << 5,
    ImDrawFlags_RoundCornersBottomLeft = 1 << 6,
    ImDrawFlags_RoundCornersBottomRight = 1 << 7,
    ImDrawFlags_RoundCornersNone = 1 << 8,
    ImDrawFlags_RoundCornersTop = ImDrawFlags_RoundCornersTopLeft | ImDrawFlags_RoundCornersTopRight,
    ImDrawFlags_RoundCornersBottom = ImDrawFlags_RoundCornersBottomLeft | ImDrawFlags_RoundCornersBottomRight,
    ImDrawFlags_RoundCornersLeft = ImDrawFlags_RoundCornersBottomLeft | ImDrawFlags_RoundCornersTopLeft,
    ImDrawFlags_RoundCornersRight = ImDrawFlags_RoundCornersBottomRight | ImDrawFlags_RoundCornersTopRight,
    ImDrawFlags_RoundCornersAll = ImDrawFlags_RoundCornersTopLeft | ImDrawFlags_RoundCornersTopRight | ImDrawFlags_RoundCornersBottomLeft | ImDrawFlags_RoundCornersBottomRight,
    ImDrawFlags_RoundCornersDefault_ = ImDrawFlags_RoundCornersAll,
    ImDrawFlags_RoundCornersMask_ = ImDrawFlags_RoundCornersAll | ImDrawFlags_RoundCornersNone,
};
enum ImDrawListFlags_
{
    ImDrawListFlags_None = 0,
    ImDrawListFlags_AntiAliasedLines = 1 << 0,
    ImDrawListFlags_AntiAliasedLinesUseTex = 1 << 1,
    ImDrawListFlags_AntiAliasedFill = 1 << 2,
    ImDrawListFlags_AllowVtxOffset = 1 << 3,
};
struct ImDrawList
{
    ImVector<ImDrawCmd> CmdBuffer;
    ImVector<ImDrawIdx> IdxBuffer;
    ImVector<ImDrawVert> VtxBuffer;
    ImDrawListFlags Flags;
    unsigned int _VtxCurrentIdx;
    ImDrawListSharedData* _Data;
    const char* _OwnerName;
    ImDrawVert* _VtxWritePtr;
    ImDrawIdx* _IdxWritePtr;
    ImVector<ImVec4> _ClipRectStack;
    ImVector<ImTextureID> _TextureIdStack;
    ImVector<ImVec2> _Path;
    ImDrawCmdHeader _CmdHeader;
    ImDrawListSplitter _Splitter;
    float _FringeScale;
    ImDrawList(ImDrawListSharedData* shared_data) { memset(this, 0, sizeof(*this)); _Data = shared_data; }
    ~ImDrawList() { _ClearFreeMemory(); }
    void PushClipRect(const ImVec2& clip_rect_min, const ImVec2& clip_rect_max, bool intersect_with_current_clip_rect = false);
    void PushClipRectFullScreen();
    void PopClipRect();
    void PushTextureID(ImTextureID texture_id);
    void PopTextureID();
    inline ImVec2 GetClipRectMin() const { const ImVec4& cr = _ClipRectStack.back(); return ImVec2(cr.x, cr.y); }
    inline ImVec2 GetClipRectMax() const { const ImVec4& cr = _ClipRectStack.back(); return ImVec2(cr.z, cr.w); }
    void AddLine(const ImVec2& p1, const ImVec2& p2, ImU32 col, float thickness = 1.0f);
    void AddRect(const ImVec2& p_min, const ImVec2& p_max, ImU32 col, float rounding = 0.0f, ImDrawFlags flags = 0, float thickness = 1.0f);
    void AddRectFilled(const ImVec2& p_min, const ImVec2& p_max, ImU32 col, float rounding = 0.0f, ImDrawFlags flags = 0);
    void AddRectFilledMultiColor(const ImVec2& p_min, const ImVec2& p_max, ImU32 col_upr_left, ImU32 col_upr_right, ImU32 col_bot_right, ImU32 col_bot_left);
    void AddQuad(const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, const ImVec2& p4, ImU32 col, float thickness = 1.0f);
    void AddQuadFilled(const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, const ImVec2& p4, ImU32 col);
    void AddTriangle(const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, ImU32 col, float thickness = 1.0f);
    void AddTriangleFilled(const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, ImU32 col);
    void AddCircle(const ImVec2& center, float radius, ImU32 col, int num_segments = 0, float thickness = 1.0f);
    void AddCircleFilled(const ImVec2& center, float radius, ImU32 col, int num_segments = 0);
    void AddNgon(const ImVec2& center, float radius, ImU32 col, int num_segments, float thickness = 1.0f);
    void AddNgonFilled(const ImVec2& center, float radius, ImU32 col, int num_segments);
    void AddText(const ImVec2& pos, ImU32 col, const char* text_begin, const char* text_end =                                                                                                         ((void *)0)                                                                                                            );
    void AddText(const ImFont* font, float font_size, const ImVec2& pos, ImU32 col, const char* text_begin, const char* text_end =                                                                                                                                              ((void *)0)                                                                                                                                                 , float wrap_width = 0.0f, const ImVec4* cpu_fine_clip_rect =                                                                                                                                                                                                                ((void *)0)                                                                                                                                                                                                                   );
    void AddPolyline(const ImVec2* points, int num_points, ImU32 col, ImDrawFlags flags, float thickness);
    void AddConvexPolyFilled(const ImVec2* points, int num_points, ImU32 col);
    void AddBezierCubic(const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, const ImVec2& p4, ImU32 col, float thickness, int num_segments = 0);
    void AddBezierQuadratic(const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, ImU32 col, float thickness, int num_segments = 0);
    void AddImage(ImTextureID user_texture_id, const ImVec2& p_min, const ImVec2& p_max, const ImVec2& uv_min = ImVec2(0, 0), const ImVec2& uv_max = ImVec2(1, 1), ImU32 col = (((ImU32)(255)<<24) | ((ImU32)(255)<<16) | ((ImU32)(255)<<8) | ((ImU32)(255)<<0)));
    void AddImageQuad(ImTextureID user_texture_id, const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, const ImVec2& p4, const ImVec2& uv1 = ImVec2(0, 0), const ImVec2& uv2 = ImVec2(1, 0), const ImVec2& uv3 = ImVec2(1, 1), const ImVec2& uv4 = ImVec2(0, 1), ImU32 col = (((ImU32)(255)<<24) | ((ImU32)(255)<<16) | ((ImU32)(255)<<8) | ((ImU32)(255)<<0)));
    void AddImageRounded(ImTextureID user_texture_id, const ImVec2& p_min, const ImVec2& p_max, const ImVec2& uv_min, const ImVec2& uv_max, ImU32 col, float rounding, ImDrawFlags flags = 0);
    inline void PathClear() { _Path.Size = 0; }
    inline void PathLineTo(const ImVec2& pos) { _Path.push_back(pos); }
    inline void PathLineToMergeDuplicate(const ImVec2& pos) { if (_Path.Size == 0 || memcmp(&_Path.Data[_Path.Size - 1], &pos, 8) != 0) _Path.push_back(pos); }
    inline void PathFillConvex(ImU32 col) { AddConvexPolyFilled(_Path.Data, _Path.Size, col); _Path.Size = 0; }
    inline void PathStroke(ImU32 col, ImDrawFlags flags = 0, float thickness = 1.0f) { AddPolyline(_Path.Data, _Path.Size, col, flags, thickness); _Path.Size = 0; }
    void PathArcTo(const ImVec2& center, float radius, float a_min, float a_max, int num_segments = 0);
    void PathArcToFast(const ImVec2& center, float radius, int a_min_of_12, int a_max_of_12);
    void PathBezierCubicCurveTo(const ImVec2& p2, const ImVec2& p3, const ImVec2& p4, int num_segments = 0);
    void PathBezierQuadraticCurveTo(const ImVec2& p2, const ImVec2& p3, int num_segments = 0);
    void PathRect(const ImVec2& rect_min, const ImVec2& rect_max, float rounding = 0.0f, ImDrawFlags flags = 0);
    void AddCallback(ImDrawCallback callback, void* callback_data);
    void AddDrawCmd();
    ImDrawList* CloneOutput() const;
    inline void ChannelsSplit(int count) { _Splitter.Split(this, count); }
    inline void ChannelsMerge() { _Splitter.Merge(this); }
    inline void ChannelsSetCurrent(int n) { _Splitter.SetCurrentChannel(this, n); }
    void PrimReserve(int idx_count, int vtx_count);
    void PrimUnreserve(int idx_count, int vtx_count);
    void PrimRect(const ImVec2& a, const ImVec2& b, ImU32 col);
    void PrimRectUV(const ImVec2& a, const ImVec2& b, const ImVec2& uv_a, const ImVec2& uv_b, ImU32 col);
    void PrimQuadUV(const ImVec2& a, const ImVec2& b, const ImVec2& c, const ImVec2& d, const ImVec2& uv_a, const ImVec2& uv_b, const ImVec2& uv_c, const ImVec2& uv_d, ImU32 col);
    inline void PrimWriteVtx(const ImVec2& pos, const ImVec2& uv, ImU32 col) { _VtxWritePtr->pos = pos; _VtxWritePtr->uv = uv; _VtxWritePtr->col = col; _VtxWritePtr++; _VtxCurrentIdx++; }
    inline void PrimWriteIdx(ImDrawIdx idx) { *_IdxWritePtr = idx; _IdxWritePtr++; }
    inline void PrimVtx(const ImVec2& pos, const ImVec2& uv, ImU32 col) { PrimWriteIdx((ImDrawIdx)_VtxCurrentIdx); PrimWriteVtx(pos, uv, col); }
    void _ResetForNewFrame();
    void _ClearFreeMemory();
    void _PopUnusedDrawCmd();
    void _TryMergeDrawCmds();
    void _OnChangedClipRect();
    void _OnChangedTextureID();
    void _OnChangedVtxOffset();
    int _CalcCircleAutoSegmentCount(float radius) const;
    void _PathArcToFastEx(const ImVec2& center, float radius, int a_min_sample, int a_max_sample, int a_step);
    void _PathArcToN(const ImVec2& center, float radius, float a_min, float a_max, int num_segments);
};
struct ImDrawData
{
    bool Valid;
    int CmdListsCount;
    int TotalIdxCount;
    int TotalVtxCount;
    ImVector<ImDrawList*> CmdLists;
    ImVec2 DisplayPos;
    ImVec2 DisplaySize;
    ImVec2 FramebufferScale;
    ImGuiViewport* OwnerViewport;
    ImDrawData() { Clear(); }
    void Clear();
    void AddDrawList(ImDrawList* draw_list);
    void DeIndexAllBuffers();
    void ScaleClipRects(const ImVec2& fb_scale);
};
struct ImFontConfig
{
    void* FontData;
    int FontDataSize;
    bool FontDataOwnedByAtlas;
    int FontNo;
    float SizePixels;
    int OversampleH;
    int OversampleV;
    bool PixelSnapH;
    ImVec2 GlyphExtraSpacing;
    ImVec2 GlyphOffset;
    const ImWchar* GlyphRanges;
    float GlyphMinAdvanceX;
    float GlyphMaxAdvanceX;
    bool MergeMode;
    unsigned int FontBuilderFlags;
    float RasterizerMultiply;
    ImWchar EllipsisChar;
    char Name[40];
    ImFont* DstFont;
    ImFontConfig();
};
struct ImFontGlyph
{
    unsigned int Colored : 1;
    unsigned int Visible : 1;
    unsigned int Codepoint : 30;
    float AdvanceX;
    float X0, Y0, X1, Y1;
    float U0, V0, U1, V1;
};
struct ImFontGlyphRangesBuilder
{
    ImVector<ImU32> UsedChars;
    ImFontGlyphRangesBuilder() { Clear(); }
    inline void Clear() { int size_in_bytes = (0x10FFFF + 1) / 8; UsedChars.resize(size_in_bytes / (int)sizeof(ImU32)); memset(UsedChars.Data, 0, (size_t)size_in_bytes); }
    inline bool GetBit(size_t n) const { int off = (int)(n >> 5); ImU32 mask = 1u << (n & 31); return (UsedChars[off] & mask) != 0; }
    inline void SetBit(size_t n) { int off = (int)(n >> 5); ImU32 mask = 1u << (n & 31); UsedChars[off] |= mask; }
    inline void AddChar(ImWchar c) { SetBit(c); }
    void AddText(const char* text, const char* text_end =                                                                     ((void *)0)                                                                        );
    void AddRanges(const ImWchar* ranges);
    void BuildRanges(ImVector<ImWchar>* out_ranges);
};
struct ImFontAtlasCustomRect
{
    unsigned short Width, Height;
    unsigned short X, Y;
    unsigned int GlyphID;
    float GlyphAdvanceX;
    ImVec2 GlyphOffset;
    ImFont* Font;
    ImFontAtlasCustomRect() { Width = Height = 0; X = Y = 0xFFFF; GlyphID = 0; GlyphAdvanceX = 0.0f; GlyphOffset = ImVec2(0, 0); Font =                                                                                                                                                ((void *)0)                                                                                                                                                   ; }
    bool IsPacked() const { return X != 0xFFFF; }
};
enum ImFontAtlasFlags_
{
    ImFontAtlasFlags_None = 0,
    ImFontAtlasFlags_NoPowerOfTwoHeight = 1 << 0,
    ImFontAtlasFlags_NoMouseCursors = 1 << 1,
    ImFontAtlasFlags_NoBakedLines = 1 << 2,
};
struct ImFontAtlas
{
    ImFontAtlas();
    ~ImFontAtlas();
    ImFont* AddFont(const ImFontConfig* font_cfg);
    ImFont* AddFontDefault(const ImFontConfig* font_cfg =                                                                              ((void *)0)                                                                                 );
    ImFont* AddFontFromFileTTF(const char* filename, float size_pixels, const ImFontConfig* font_cfg =                                                                                                                           ((void *)0)                                                                                                                              , const ImWchar* glyph_ranges =                                                                                                                                                               ((void *)0)                                                                                                                                                                  );
    ImFont* AddFontFromMemoryTTF(void* font_data, int font_size, float size_pixels, const ImFontConfig* font_cfg =                                                                                                                                       ((void *)0)                                                                                                                                          , const ImWchar* glyph_ranges =                                                                                                                                                                           ((void *)0)                                                                                                                                                                              );
    ImFont* AddFontFromMemoryCompressedTTF(const void* compressed_font_data, int compressed_font_size, float size_pixels, const ImFontConfig* font_cfg =                                                                                                                                                                             ((void *)0)                                                                                                                                                                                , const ImWchar* glyph_ranges =                                                                                                                                                                                                                 ((void *)0)                                                                                                                                                                                                                    );
    ImFont* AddFontFromMemoryCompressedBase85TTF(const char* compressed_font_data_base85, float size_pixels, const ImFontConfig* font_cfg =                                                                                                                                                                ((void *)0)                                                                                                                                                                   , const ImWchar* glyph_ranges =                                                                                                                                                                                                    ((void *)0)                                                                                                                                                                                                       );
    void ClearInputData();
    void ClearTexData();
    void ClearFonts();
    void Clear();
    bool Build();
    void GetTexDataAsAlpha8(unsigned char** out_pixels, int* out_width, int* out_height, int* out_bytes_per_pixel =                                                                                                                                           ((void *)0)                                                                                                                                              );
    void GetTexDataAsRGBA32(unsigned char** out_pixels, int* out_width, int* out_height, int* out_bytes_per_pixel =                                                                                                                                           ((void *)0)                                                                                                                                              );
    bool IsBuilt() const { return Fonts.Size > 0 && TexReady; }
    void SetTexID(ImTextureID id) { TexID = id; }
    const ImWchar* GetGlyphRangesDefault();
    const ImWchar* GetGlyphRangesGreek();
    const ImWchar* GetGlyphRangesKorean();
    const ImWchar* GetGlyphRangesJapanese();
    const ImWchar* GetGlyphRangesChineseFull();
    const ImWchar* GetGlyphRangesChineseSimplifiedCommon();
    const ImWchar* GetGlyphRangesCyrillic();
    const ImWchar* GetGlyphRangesThai();
    const ImWchar* GetGlyphRangesVietnamese();
    int AddCustomRectRegular(int width, int height);
    int AddCustomRectFontGlyph(ImFont* font, ImWchar id, int width, int height, float advance_x, const ImVec2& offset = ImVec2(0, 0));
    ImFontAtlasCustomRect* GetCustomRectByIndex(int index) {                                                                  ((void) sizeof ((                                                                 index >= 0                                                                 ) ? 1 : 0), __extension__ ({ if (                                                                 index >= 0                                                                 ) ; else __assert_fail (                                                                 "index >= 0"                                                                 , "../imgui/imgui.h", 2928, __extension__ __PRETTY_FUNCTION__); }))                                                                                      ; return &CustomRects[index]; }
    void CalcCustomRectUV(const ImFontAtlasCustomRect* rect, ImVec2* out_uv_min, ImVec2* out_uv_max) const;
    bool GetMouseCursorTexData(ImGuiMouseCursor cursor, ImVec2* out_offset, ImVec2* out_size, ImVec2 out_uv_border[2], ImVec2 out_uv_fill[2]);
    ImFontAtlasFlags Flags;
    ImTextureID TexID;
    int TexDesiredWidth;
    int TexGlyphPadding;
    bool Locked;
    void* UserData;
    bool TexReady;
    bool TexPixelsUseColors;
    unsigned char* TexPixelsAlpha8;
    unsigned int* TexPixelsRGBA32;
    int TexWidth;
    int TexHeight;
    ImVec2 TexUvScale;
    ImVec2 TexUvWhitePixel;
    ImVector<ImFont*> Fonts;
    ImVector<ImFontAtlasCustomRect> CustomRects;
    ImVector<ImFontConfig> ConfigData;
    ImVec4 TexUvLines[(63) + 1];
    const ImFontBuilderIO* FontBuilderIO;
    unsigned int FontBuilderFlags;
    int PackIdMouseCursors;
    int PackIdLines;
};
struct ImFont
{
    ImVector<float> IndexAdvanceX;
    float FallbackAdvanceX;
    float FontSize;
    ImVector<ImWchar> IndexLookup;
    ImVector<ImFontGlyph> Glyphs;
    const ImFontGlyph* FallbackGlyph;
    ImFontAtlas* ContainerAtlas;
    const ImFontConfig* ConfigData;
    short ConfigDataCount;
    ImWchar FallbackChar;
    ImWchar EllipsisChar;
    short EllipsisCharCount;
    float EllipsisWidth;
    float EllipsisCharStep;
    bool DirtyLookupTables;
    float Scale;
    float Ascent, Descent;
    int MetricsTotalSurface;
    ImU8 Used4kPagesMap[(0x10FFFF +1)/4096/8];
    ImFont();
    ~ImFont();
    const ImFontGlyph*FindGlyph(ImWchar c) const;
    const ImFontGlyph*FindGlyphNoFallback(ImWchar c) const;
    float GetCharAdvance(ImWchar c) const { return ((int)c < IndexAdvanceX.Size) ? IndexAdvanceX[(int)c] : FallbackAdvanceX; }
    bool IsLoaded() const { return ContainerAtlas !=                                                                                               ((void *)0)                                                                                                  ; }
    const char* GetDebugName() const { return ConfigData ? ConfigData->Name : "<unknown>"; }
    ImVec2 CalcTextSizeA(float size, float max_width, float wrap_width, const char* text_begin, const char* text_end =                                                                                                                                            ((void *)0)                                                                                                                                               , const char** remaining =                                                                                                                                                                           ((void *)0)                                                                                                                                                                              ) const;
    const char* CalcWordWrapPositionA(float scale, const char* text, const char* text_end, float wrap_width) const;
    void RenderChar(ImDrawList* draw_list, float size, const ImVec2& pos, ImU32 col, ImWchar c) const;
    void RenderText(ImDrawList* draw_list, float size, const ImVec2& pos, ImU32 col, const ImVec4& clip_rect, const char* text_begin, const char* text_end, float wrap_width = 0.0f, bool cpu_fine_clip = false) const;
    void BuildLookupTable();
    void ClearOutputData();
    void GrowIndex(int new_size);
    void AddGlyph(const ImFontConfig* src_cfg, ImWchar c, float x0, float y0, float x1, float y1, float u0, float v0, float u1, float v1, float advance_x);
    void AddRemapChar(ImWchar dst, ImWchar src, bool overwrite_dst = true);
    void SetGlyphVisible(ImWchar c, bool visible);
    bool IsGlyphRangeUnused(unsigned int c_begin, unsigned int c_last);
};
enum ImGuiViewportFlags_
{
    ImGuiViewportFlags_None = 0,
    ImGuiViewportFlags_IsPlatformWindow = 1 << 0,
    ImGuiViewportFlags_IsPlatformMonitor = 1 << 1,
    ImGuiViewportFlags_OwnedByApp = 1 << 2,
};
struct ImGuiViewport
{
    ImGuiViewportFlags Flags;
    ImVec2 Pos;
    ImVec2 Size;
    ImVec2 WorkPos;
    ImVec2 WorkSize;
    void* PlatformHandleRaw;
    ImGuiViewport() { memset(this, 0, sizeof(*this)); }
    ImVec2 GetCenter() const { return ImVec2(Pos.x + Size.x * 0.5f, Pos.y + Size.y * 0.5f); }
    ImVec2 GetWorkCenter() const { return ImVec2(WorkPos.x + WorkSize.x * 0.5f, WorkPos.y + WorkSize.y * 0.5f); }
};
struct ImGuiPlatformImeData
{
    bool WantVisible;
    ImVec2 InputPos;
    float InputLineHeight;
    ImGuiPlatformImeData() { memset(this, 0, sizeof(*this)); }
};
namespace ImGui
{
    ImGuiKey GetKeyIndex(ImGuiKey key);
}