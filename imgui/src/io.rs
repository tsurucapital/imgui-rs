use bitflags::bitflags;
use sys::{ImGuiContext, ImGuiMouseSource, ImWchar};
use std::f32;
use std::ops::{Index, IndexMut};
use std::os::raw::{c_char, c_void};
use std::time::Duration;

use crate::fonts::atlas::FontAtlas;
use crate::fonts::font::Font;
use crate::input::keyboard::Key;
use crate::input::mouse::MouseButton;
use crate::internal::{ImVector, RawCast};
use crate::sys;

bitflags! {
    /// Configuration flags
    #[repr(transparent)]
    pub struct ConfigFlags: u32 {
        /// Master keyboard navigation enable flag.
        ///
        /// `frame()` will automatically fill `io.nav_inputs` based on `io.keys_down`.
        const NAV_ENABLE_KEYBOARD = sys::ImGuiConfigFlags_NavEnableKeyboard;
        /// Master gamepad navigation enable flag.
        ///
        /// This is mostly to instruct the backend to fill `io.nav_inputs`. The backend
        /// also needs to set `BackendFlags::HasGamepad`.
        const NAV_ENABLE_GAMEPAD = sys::ImGuiConfigFlags_NavEnableGamepad;
        /// Instruction navigation to move the mouse cursor.
        ///
        /// May be useful on TV/console systems where moving a virtual mouse is awkward.
        /// Will update `io.mouse_pos` and set `io.want_set_mouse_pos = true`. If enabled,
        /// you *must* honor `io.want_set_mouse_pos`, or imgui-rs will react as if the mouse is
        /// jumping around back and forth.
        const NAV_ENABLE_SET_MOUSE_POS = sys::ImGuiConfigFlags_NavEnableSetMousePos;
        /// Instruction navigation to not set the `io.want_capture_keyboard` flag when
        /// `io.nav_active` is set.
        const NAV_NO_CAPTURE_KEYBOARD = sys::ImGuiConfigFlags_NavNoCaptureKeyboard;
        /// Instruction imgui-rs to clear mouse position/buttons in `frame()`.
        ///
        /// This allows ignoring the mouse information set by the backend.
        const NO_MOUSE = sys::ImGuiConfigFlags_NoMouse;
        /// Instruction backend to not alter mouse cursor shape and visibility.
        ///
        /// Use if the backend cursor changes are interfering with yours and you don't want to use
        /// `set_mouse_cursor` to change the mouse cursor. You may want to honor requests from
        /// imgui-rs by reading `get_mouse_cursor` yourself instead.
        const NO_MOUSE_CURSOR_CHANGE = sys::ImGuiConfigFlags_NoMouseCursorChange;
        /// Application is SRGB-aware.
        ///
        /// Not used by core imgui-rs.
        const IS_SRGB = sys::ImGuiConfigFlags_IsSRGB;
        /// Application is using a touch screen instead of a mouse.
        ///
        /// Not used by core imgui-rs.
        const IS_TOUCH_SCREEN = sys::ImGuiConfigFlags_IsTouchScreen;

        #[cfg(feature = "docking")]
        const DOCKING_ENABLE = sys::ImGuiConfigFlags_DockingEnable;

        #[cfg(feature = "docking")]
        const VIEWPORTS_ENABLE = sys::ImGuiConfigFlags_ViewportsEnable;
    }
}

#[cfg(feature = "docking")]
bitflags! {
    #[repr(transparent)]
    pub struct ViewportFlags: u32 {
        const IS_PLATFORM_WINDOW = sys::ImGuiViewportFlags_IsPlatformWindow;
        const IS_PLATFORM_MONITOR = sys::ImGuiViewportFlags_IsPlatformMonitor;
        const OWNED_BY_APP = sys::ImGuiViewportFlags_OwnedByApp;
        const NO_DECORATION = sys::ImGuiViewportFlags_NoDecoration;
        const NO_TASK_BAR_ICON = sys::ImGuiViewportFlags_NoTaskBarIcon;
        const NO_FOCUS_ON_APPEARING = sys::ImGuiViewportFlags_NoFocusOnAppearing;
        const NO_FOCUS_ON_CLICK = sys::ImGuiViewportFlags_NoFocusOnClick;
        const NO_INPUTS = sys::ImGuiViewportFlags_NoInputs;
        const NO_RENDERER_CLEAR = sys::ImGuiViewportFlags_NoRendererClear;
        const TOP_MOST = sys::ImGuiViewportFlags_TopMost;
        const IS_MINIMIZED = sys::ImGuiViewportFlags_IsMinimized;
        const IS_FOCUSED = sys::ImGuiViewportFlags_IsFocused;
        const NO_AUTO_MERGE = sys::ImGuiViewportFlags_NoAutoMerge;
        const CAN_HOST_OTHER_WINDOWS = sys::ImGuiViewportFlags_CanHostOtherWindows;
    }
}

bitflags! {
    /// Backend capabilities
    #[repr(transparent)]
    pub struct BackendFlags: u32 {
        /// Backend supports gamepad and currently has one connected
        const HAS_GAMEPAD = sys::ImGuiBackendFlags_HasGamepad;
        /// Backend supports honoring `get_mouse_cursor` value to change the OS cursor shape
        const HAS_MOUSE_CURSORS = sys::ImGuiBackendFlags_HasMouseCursors;
        /// Backend supports `io.want_set_mouse_pos` requests to reposition the OS mouse position.
        ///
        /// Only used if `ConfigFlags::NavEnableSetMousePos` is set.
        const HAS_SET_MOUSE_POS = sys::ImGuiBackendFlags_HasSetMousePos;
        /// Backend renderer supports DrawCmd::vtx_offset.
        ///
        /// This enables output of large meshes (64K+ vertices) while still using 16-bits indices.
        const RENDERER_HAS_VTX_OFFSET = sys::ImGuiBackendFlags_RendererHasVtxOffset;

        #[cfg(feature = "docking")]
        /// Set if the platform backend supports viewports.
        const PLATFORM_HAS_VIEWPORTS = sys::ImGuiBackendFlags_PlatformHasViewports;
        #[cfg(feature = "docking")]
        /// Set if the renderer backend supports viewports.
        const RENDERER_HAS_VIEWPORTS = sys::ImGuiBackendFlags_RendererHasViewports;
    }
}

/// An input identifier for navigation
#[repr(u32)]
#[derive(Copy, Clone, Debug, Hash, Eq, PartialEq)]
pub enum NavInput {
    Activate = sys::ImGuiNavInput_Activate,
    Cancel = sys::ImGuiNavInput_Cancel,
    Input = sys::ImGuiNavInput_Input,
    Menu = sys::ImGuiNavInput_Menu,
    DpadLeft = sys::ImGuiNavInput_DpadLeft,
    DpadRight = sys::ImGuiNavInput_DpadRight,
    DpadUp = sys::ImGuiNavInput_DpadUp,
    DpadDown = sys::ImGuiNavInput_DpadDown,
    LStickLeft = sys::ImGuiNavInput_LStickLeft,
    LStickRight = sys::ImGuiNavInput_LStickRight,
    LStickUp = sys::ImGuiNavInput_LStickUp,
    LStickDown = sys::ImGuiNavInput_LStickDown,
    FocusPrev = sys::ImGuiNavInput_FocusPrev,
    FocusNext = sys::ImGuiNavInput_FocusNext,
    TweakSlow = sys::ImGuiNavInput_TweakSlow,
    TweakFast = sys::ImGuiNavInput_TweakFast,
}

impl NavInput {
    /// All possible `NavInput` variants
    pub const VARIANTS: [NavInput; NavInput::COUNT] = [
        NavInput::Activate,
        NavInput::Cancel,
        NavInput::Input,
        NavInput::Menu,
        NavInput::DpadLeft,
        NavInput::DpadRight,
        NavInput::DpadUp,
        NavInput::DpadDown,
        NavInput::LStickLeft,
        NavInput::LStickRight,
        NavInput::LStickUp,
        NavInput::LStickDown,
        NavInput::FocusPrev,
        NavInput::FocusNext,
        NavInput::TweakSlow,
        NavInput::TweakFast,
    ];
    /// Amount of internal/hidden variants (not exposed by imgui-rs)
    const INTERNAL_COUNT: usize = 0;
    /// Total count of `NavInput` variants
    pub const COUNT: usize = sys::ImGuiNavInput_COUNT as usize - NavInput::INTERNAL_COUNT;
}

#[test]
fn test_nav_input_variants() {
    for (idx, &value) in NavInput::VARIANTS.iter().enumerate() {
        assert_eq!(idx, value as usize);
    }
}

/// Settings and inputs/outputs for imgui-rs
#[repr(C)]
pub struct Io {
    /// Flags set by user/application
    pub config_flags: ConfigFlags,
    /// Flags set by backend
    pub backend_flags: BackendFlags,
    /// Main display size in pixels
    pub display_size: [f32; 2],
    /// Time elapsed since last frame, in seconds
    pub delta_time: f32,
    /// Minimum time between saving positions/sizes to .ini file, in seconds
    pub ini_saving_rate: f32,

    pub(crate) ini_filename: *const c_char,
    pub(crate) log_filename: *const c_char,

    user_data: *mut c_void,
    pub(crate) fonts: *mut FontAtlas,

    /// Global scale for all fonts
    pub font_global_scale: f32,
    /// Allow user to scale text of individual window with CTRL+wheel
    pub font_allow_user_scaling: bool,

    pub(crate) font_default: *mut Font,

    /// For retina display or other situations where window coordinates are different from
    /// framebuffer coordinates
    pub display_framebuffer_scale: [f32; 2],

    #[cfg(feature = "docking")]
    pub config_docking_no_split: bool,
    #[cfg(feature = "docking")]
    pub config_docking_with_shift: bool,
    #[cfg(feature = "docking")]
    pub config_docking_always_tab_bar: bool,
    #[cfg(feature = "docking")]
    pub config_docking_transparent_payload: bool,
    #[cfg(feature = "docking")]
    pub config_viewports_no_auto_merge: bool,
    #[cfg(feature = "docking")]
    pub config_viewports_no_task_bar_icon: bool,
    #[cfg(feature = "docking")]
    pub config_viewports_no_decoration: bool,
    #[cfg(feature = "docking")]
    pub config_viewports_no_default_parent: bool,

    /// Request imgui-rs to draw a mouse cursor for you
    pub mouse_draw_cursor: bool,
    /// macOS-style input behavior.
    ///
    /// Defaults to true on Apple platforms. Changes in behavior:
    ///
    /// * Text editing cursor movement using Alt instead of Ctrl
    /// * Shortcuts using Cmd/Super instead of Ctrl
    /// * Line/text start and end using Cmd+Arrows instead of Home/End
    /// * Double-click selects by word instead of selecting the whole text
    /// * Multi-selection in lists uses Cmd/Super instead of Ctrl
    pub config_mac_os_behaviors: bool,
    /// Enable input queue trickling: some types of events submitted during the same frame (e.g. button down + up)
    /// will be spread over multiple frames, improving interactions with low framerates.
    pub config_input_trickle_event_queue: bool,
    /// Set to false to disable blinking cursor
    pub config_input_text_cursor_blink: bool,
    /// Pressing Enter will keep item active and select contents (single-line only).
    pub config_input_text_enter_keep_active: bool,
    /// Enable turning DragXXX widgets into text input with a simple mouse
    /// click-release (without moving). Not desirable on devices without a
    /// keyboard.
    pub config_drag_click_to_input_text: bool,
    /// Enable resizing of windows from their edges and from the lower-left corner.
    ///
    /// Requires `HasMouserCursors` in `backend_flags`, because it needs mouse cursor feedback.
    pub config_windows_resize_from_edges: bool,
    /// Set to true to only allow moving windows when clicked+dragged from the title bar.
    ///
    /// Windows without a title bar are not affected.
    pub config_windows_move_from_title_bar_only: bool,
    /// Compact memory usage when unused.
    ///
    /// Set to -1.0 to disable.
    pub config_memory_compact_timer: f32,

    /// Time for a double-click, in seconds
    pub mouse_double_click_time: f32,
    /// Distance threshold to stay in to validate a double-click, in pixels
    pub mouse_double_click_max_dist: f32,
    /// Distance threshold before considering we are dragging
    pub mouse_drag_threshold: f32,
    /// When holding a key/button, time before it starts repeating, in seconds
    pub key_repeat_delay: f32,
    /// When holding a key/button, rate at which it repeats, in seconds
    pub key_repeat_rate: f32,

    pub config_debug_begin_return_value_once: bool,
    pub config_debug_begin_return_value_loop: bool,
    pub config_debug_ignore_focus_loss: bool,
    pub config_debug_ini_settings: bool,

    pub(crate) backend_platform_name: *const c_char,
    pub(crate) backend_renderer_name: *const c_char,
    pub(crate) backend_platform_user_data: *mut c_void,
    pub(crate) backend_renderer_user_data: *mut c_void,
    backend_language_user_data: *mut c_void,
    pub(crate) get_clipboard_text_fn:
        Option<unsafe extern "C" fn(user_data: *mut c_void) -> *const c_char>,
    pub(crate) set_clipboard_text_fn:
        Option<unsafe extern "C" fn(user_data: *mut c_void, text: *const c_char)>,
    pub(crate) clipboard_user_data: *mut c_void,
    pub set_platform_ime_data_fn: Option<
        unsafe extern "C" fn(
            viewport: *mut sys::ImGuiViewport,
            data: *mut sys::ImGuiPlatformImeData,
        ),
    >,
    unused_padding: *mut c_void,
    pub platform_locale_decimal_point: ImWchar,
    /// When true, imgui-rs will use the mouse inputs, so do not dispatch them to your main
    /// game/application
    pub want_capture_mouse: bool,
    /// When true, imgui-rs will use the keyboard inputs, so do not dispatch them to your main
    /// game/application
    pub want_capture_keyboard: bool,
    /// Mobile/console: when true, you may display an on-screen keyboard.
    ///
    /// This is set by imgui-rs when it wants textual keyboard input to happen.
    pub want_text_input: bool,
    /// Mouse position has been altered, so the backend should reposition the mouse on the next
    /// frame.
    ///
    /// Set only when `ConfigFlags::NavEnableSetMousePos` is enabled.
    pub want_set_mouse_pos: bool,
    /// When manual .ini load/save is active (`ini_filename` is `None`), this will be set to notify
    /// your application that you can call `save_ini_settings` and save the settings yourself.
    ///
    /// *Important*: You need to clear this flag yourself
    pub want_save_ini_settings: bool,
    /// Keyboard/Gamepad navigation is currently allowed
    pub nav_active: bool,
    /// Keyboard/Gamepad navigation is visible and allowed
    pub nav_visible: bool,
    /// Application framerate estimation, in frames per second.
    ///
    /// Rolling average estimation based on `io.delta_time` over 120 frames.
    pub framerate: f32,
    /// Vertices output during last rendering
    pub metrics_render_vertices: i32,
    /// Indices output during last rendering (= number of triangles * 3)
    pub metrics_render_indices: i32,
    /// Number of visible windows
    pub metrics_render_windows: i32,
    /// Number of active windows
    pub metrics_active_windows: i32,
    /// Number of active internal imgui-rs allocations
    pub metrics_active_allocations: i32,
    /// Mouse delta.
    ///
    /// Note that this is zero if either current or previous position is invalid ([f32::MAX,
    /// f32::MAX]), so a disappearing/reappearing mouse won't have a huge delta.
    pub mouse_delta: [f32; 2],
    /// Map of indices into the `keys_down` entries array, which represent your "native" keyboard
    /// state
    pub key_map: [u32; sys::ImGuiKey_COUNT as usize],
    /// Keyboard keys that are pressed (indexing defined by the user/application)
    pub keys_down: [bool; sys::ImGuiKey_COUNT as usize],
    /// Gamepad inputs.
    ///
    /// Cleared back to zero after each frame. Keyboard keys will be auto-mapped and written
    /// here by `frame()`.
    pub nav_inputs: [f32; NavInput::COUNT + NavInput::INTERNAL_COUNT],
    pub ctx: *mut ImGuiContext,
    /// Mouse position, in pixels.
    ///
    /// Set to [f32::MAX, f32::MAX] if mouse is unavailable (on another screen, etc.).
    pub mouse_pos: [f32; 2],
    /// Mouse buttons: 0=left, 1=right, 2=middle + extras
    pub mouse_down: [bool; 5],
    /// Mouse wheel (vertical).
    ///
    /// 1 unit scrolls about 5 lines of text.
    pub mouse_wheel: f32,
    /// Mouse wheel (horizontal).
    ///
    /// Most users don't have a mouse with a horizontal wheel, and may not be filled by all
    /// backends.
    pub mouse_wheel_h: f32,
    pub mouse_source: ImGuiMouseSource,
    #[cfg(feature = "docking")]
    mouse_hovered_viewport: sys::ImGuiID,
    /// Keyboard modifier pressed: Control
    pub key_ctrl: bool,
    /// Keyboard modifier pressed: Shift
    pub key_shift: bool,
    /// Keyboard modifier pressed: Alt
    pub key_alt: bool,
    /// Keyboard modifier pressed: Cmd/Super/Windows
    pub key_super: bool,
    key_mods: sys::ImGuiKeyChord,
    keys_data: [sys::ImGuiKeyData; sys::ImGuiKey_COUNT as usize],

    pub want_capture_mouse_unless_popup_close: bool,

    mouse_pos_prev: [f32; 2],
    mouse_clicked_pos: [[f32; 2]; 5],
    mouse_clicked_time: [f64; 5],
    mouse_clicked: [bool; 5],
    mouse_double_clicked: [bool; 5],
    mouse_clicked_count: [u16; 5],
    mouse_clicked_last_count: [u16; 5],
    mouse_released: [bool; 5],
    mouse_down_owned: [bool; 5],
    mouse_down_owned_unless_popup_close: [bool; 5],
    mouse_wheel_request_axis_swap: bool,
    mouse_down_duration: [f32; 5],
    mouse_down_duration_prev: [f32; 5],
    #[cfg(feature = "docking")]
    mouse_drag_max_distance_abs: [sys::ImVec2; 5],
    mouse_drag_max_distance_sqr: [f32; 5],
    pen_pressure: f32,

    /// Clear buttons state when focus is lost (this is useful so
    /// e.g. releasing Alt after focus loss on Alt-Tab doesn't trigger
    /// the Alt menu toggle)
    pub app_focus_lost: bool,

    app_accepting_events: bool,
    backend_using_legacy_key_arrays: sys::ImS8,
    backend_using_legacy_nav_input_array: bool,

    input_queue_surrogate: sys::ImWchar16,
    input_queue_characters: ImVector<sys::ImWchar>,
}

unsafe impl RawCast<sys::ImGuiIO> for Io {}

impl Io {
    /// Queue new character input
    #[doc(alias = "AddInputCharactersUTF8")]
    pub fn add_input_character(&mut self, character: char) {
        let mut buf = [0; 5];
        character.encode_utf8(&mut buf);
        unsafe {
            sys::ImGuiIO_AddInputCharactersUTF8(self.raw_mut(), buf.as_ptr() as *const _);
        }
    }
    /// Clear character input buffer
    #[doc(alias = "ClearInputKeys")]
    pub fn clear_input_keys(&mut self) {
        unsafe {
            sys::ImGuiIO_ClearInputKeys(self.raw_mut());
        }
    }
    /// Peek character input buffer, return a copy of entire buffer
    pub fn peek_input_characters(&self) -> String {
        self.input_queue_characters().collect()
    }

    /// Returns a view of the data in the input queue (without copying it).
    ///
    /// The returned iterator is a simple mapping over a slice more or less what
    /// you need for random access to the data (Rust has no
    /// `RandomAccessIterator`, or we'd use that).
    pub fn input_queue_characters(
        &self,
    ) -> impl DoubleEndedIterator<Item = char> + ExactSizeIterator + Clone + '_ {
        self.input_queue_characters
            .as_slice()
            .iter()
            // TODO: are the values in the buffer guaranteed to be valid unicode
            // scalar values? if so we can just expose this as a `&[char]`...
            .map(|c| core::char::from_u32(*c).unwrap_or(core::char::REPLACEMENT_CHARACTER))
    }

    pub fn update_delta_time(&mut self, delta: Duration) {
        self.delta_time = delta.as_secs_f32().max(f32::MIN_POSITIVE);
    }

    pub fn add_mouse_pos_event(&mut self, pos: [f32; 2]) {
        unsafe {
            sys::ImGuiIO_AddMousePosEvent(self.raw_mut(), pos[0], pos[1]);
        }
    }

    pub fn add_mouse_button_event(&mut self, button: MouseButton, down: bool) {
        unsafe {
            sys::ImGuiIO_AddMouseButtonEvent(self.raw_mut(), button as i32, down);
        }
    }

    pub fn add_mouse_wheel_event(&mut self, wheel: [f32; 2]) {
        unsafe {
            sys::ImGuiIO_AddMouseWheelEvent(self.raw_mut(), wheel[0], wheel[1]);
        }
    }

    pub fn add_key_event(&mut self, key: Key, down: bool) {
        unsafe {
            sys::ImGuiIO_AddKeyEvent(self.raw_mut(), key as u32, down);
        }
    }

    pub fn add_key_analog_event(&mut self, key: Key, down: bool, value: f32) {
        unsafe {
            sys::ImGuiIO_AddKeyAnalogEvent(self.raw_mut(), key as u32, down, value);
        }
    }
}

impl Index<Key> for Io {
    type Output = u32;
    fn index(&self, index: Key) -> &u32 {
        &self.key_map[index as usize]
    }
}

impl IndexMut<Key> for Io {
    fn index_mut(&mut self, index: Key) -> &mut u32 {
        &mut self.key_map[index as usize]
    }
}

impl Index<NavInput> for Io {
    type Output = f32;
    fn index(&self, index: NavInput) -> &f32 {
        &self.nav_inputs[index as usize]
    }
}

impl IndexMut<NavInput> for Io {
    fn index_mut(&mut self, index: NavInput) -> &mut f32 {
        &mut self.nav_inputs[index as usize]
    }
}

impl Index<MouseButton> for Io {
    type Output = bool;
    fn index(&self, index: MouseButton) -> &bool {
        &self.mouse_down[index as usize]
    }
}

impl IndexMut<MouseButton> for Io {
    fn index_mut(&mut self, index: MouseButton) -> &mut bool {
        &mut self.mouse_down[index as usize]
    }
}

#[test]
#[cfg(test)]
fn test_io_memory_layout() {
    use std::mem;
    assert_eq!(mem::size_of::<Io>(), mem::size_of::<sys::ImGuiIO>());
    assert_eq!(mem::align_of::<Io>(), mem::align_of::<sys::ImGuiIO>());
    use sys::ImGuiIO;
    macro_rules! assert_field_offset {
        ($l:ident, $r:ident) => {
            assert_eq!(
                memoffset::offset_of!(Io, $l),
                memoffset::offset_of!(ImGuiIO, $r)
            );
        };
    }

    // We move this test into a Thread with a larger stack
    // since the stack size of the default thread is not large enough in
    // debug mode.
    std::thread::Builder::new()
        .stack_size(4 * 1024 * 1024)
        .spawn(|| {
            assert_field_offset!(config_flags, ConfigFlags);
            assert_field_offset!(backend_flags, BackendFlags);
            assert_field_offset!(display_size, DisplaySize);
            assert_field_offset!(delta_time, DeltaTime);
            assert_field_offset!(ini_saving_rate, IniSavingRate);
            assert_field_offset!(ini_filename, IniFilename);
            assert_field_offset!(log_filename, LogFilename);
            assert_field_offset!(mouse_double_click_time, MouseDoubleClickTime);
            assert_field_offset!(mouse_double_click_max_dist, MouseDoubleClickMaxDist);
            assert_field_offset!(mouse_drag_threshold, MouseDragThreshold);
            assert_field_offset!(key_repeat_delay, KeyRepeatDelay);
            assert_field_offset!(key_repeat_rate, KeyRepeatRate);
            assert_field_offset!(user_data, UserData);
            assert_field_offset!(fonts, Fonts);
            assert_field_offset!(font_global_scale, FontGlobalScale);
            assert_field_offset!(font_allow_user_scaling, FontAllowUserScaling);
            assert_field_offset!(font_default, FontDefault);
            assert_field_offset!(display_framebuffer_scale, DisplayFramebufferScale);
            assert_field_offset!(mouse_draw_cursor, MouseDrawCursor);
            assert_field_offset!(config_mac_os_behaviors, ConfigMacOSXBehaviors);
            assert_field_offset!(
                config_input_trickle_event_queue,
                ConfigInputTrickleEventQueue
            );
            assert_field_offset!(config_input_text_cursor_blink, ConfigInputTextCursorBlink);
            assert_field_offset!(
                config_input_text_enter_keep_active,
                ConfigInputTextEnterKeepActive
            );
            assert_field_offset!(
                config_windows_resize_from_edges,
                ConfigWindowsResizeFromEdges
            );
            assert_field_offset!(
                config_windows_move_from_title_bar_only,
                ConfigWindowsMoveFromTitleBarOnly
            );
            assert_field_offset!(backend_platform_name, BackendPlatformName);
            assert_field_offset!(backend_renderer_name, BackendRendererName);
            assert_field_offset!(backend_platform_user_data, BackendPlatformUserData);
            assert_field_offset!(backend_renderer_user_data, BackendRendererUserData);
            assert_field_offset!(backend_language_user_data, BackendLanguageUserData);
            assert_field_offset!(get_clipboard_text_fn, GetClipboardTextFn);
            assert_field_offset!(set_clipboard_text_fn, SetClipboardTextFn);
            assert_field_offset!(clipboard_user_data, ClipboardUserData);
            assert_field_offset!(set_platform_ime_data_fn, SetPlatformImeDataFn);
            assert_field_offset!(unused_padding, _UnusedPadding);
            assert_field_offset!(want_capture_mouse, WantCaptureMouse);
            assert_field_offset!(want_capture_keyboard, WantCaptureKeyboard);
            assert_field_offset!(want_text_input, WantTextInput);
            assert_field_offset!(want_set_mouse_pos, WantSetMousePos);
            assert_field_offset!(want_save_ini_settings, WantSaveIniSettings);
            assert_field_offset!(nav_active, NavActive);
            assert_field_offset!(nav_visible, NavVisible);
            assert_field_offset!(framerate, Framerate);
            assert_field_offset!(metrics_render_vertices, MetricsRenderVertices);
            assert_field_offset!(metrics_render_indices, MetricsRenderIndices);
            assert_field_offset!(metrics_render_windows, MetricsRenderWindows);
            assert_field_offset!(metrics_active_windows, MetricsActiveWindows);
            assert_field_offset!(metrics_active_allocations, MetricsActiveAllocations);
            assert_field_offset!(mouse_delta, MouseDelta);
            assert_field_offset!(key_map, KeyMap);
            assert_field_offset!(keys_down, KeysDown);
            assert_field_offset!(nav_inputs, NavInputs);
            assert_field_offset!(mouse_pos, MousePos);
            assert_field_offset!(mouse_down, MouseDown);
            assert_field_offset!(mouse_wheel, MouseWheel);
            assert_field_offset!(mouse_wheel_h, MouseWheelH);
            assert_field_offset!(key_ctrl, KeyCtrl);
            assert_field_offset!(key_shift, KeyShift);
            assert_field_offset!(key_alt, KeyAlt);
            assert_field_offset!(key_super, KeySuper);
            assert_field_offset!(key_mods, KeyMods);
            assert_field_offset!(keys_data, KeysData);
            assert_field_offset!(
                want_capture_mouse_unless_popup_close,
                WantCaptureMouseUnlessPopupClose
            );
            assert_field_offset!(mouse_pos_prev, MousePosPrev);
            assert_field_offset!(mouse_clicked_pos, MouseClickedPos);
            assert_field_offset!(mouse_clicked_time, MouseClickedTime);
            assert_field_offset!(mouse_clicked, MouseClicked);
            assert_field_offset!(mouse_double_clicked, MouseDoubleClicked);
            assert_field_offset!(mouse_clicked_count, MouseClickedCount);
            assert_field_offset!(mouse_clicked_last_count, MouseClickedLastCount);
            assert_field_offset!(mouse_released, MouseReleased);
            assert_field_offset!(mouse_down_owned, MouseDownOwned);
            assert_field_offset!(mouse_down_duration, MouseDownDuration);
            assert_field_offset!(mouse_down_duration_prev, MouseDownDurationPrev);
            assert_field_offset!(mouse_drag_max_distance_sqr, MouseDragMaxDistanceSqr);
            assert_field_offset!(pen_pressure, PenPressure);
            assert_field_offset!(app_focus_lost, AppFocusLost);
            assert_field_offset!(app_accepting_events, AppAcceptingEvents);
            assert_field_offset!(backend_using_legacy_key_arrays, BackendUsingLegacyKeyArrays);
            assert_field_offset!(
                backend_using_legacy_nav_input_array,
                BackendUsingLegacyNavInputArray
            );
            assert_field_offset!(input_queue_surrogate, InputQueueSurrogate);
            assert_field_offset!(input_queue_characters, InputQueueCharacters);
        })
        .unwrap()
        .join()
        .unwrap();
}
