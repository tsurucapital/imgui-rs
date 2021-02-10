use crate::ImColor32;
use sys::ImDrawList;

use super::Ui;
use crate::legacy::ImDrawCornerFlags;
use crate::render::renderer::TextureId;

use std::marker::PhantomData;

/// Object implementing the custom draw API.
///
/// Called from [`Ui::get_window_draw_list`], [`Ui::get_background_draw_list`] or [`Ui::get_foreground_draw_list`].
/// No more than one instance of this structure can live in a program at the same time.
/// The program will panic on creating a second instance.
pub struct DrawListMut<'ui> {
    draw_list: *mut ImDrawList,
    _phantom: PhantomData<&'ui Ui<'ui>>,
}

static DRAW_LIST_LOADED: std::sync::atomic::AtomicBool = std::sync::atomic::AtomicBool::new(false);

impl<'ui> Drop for DrawListMut<'ui> {
    fn drop(&mut self) {
        DRAW_LIST_LOADED.store(false, std::sync::atomic::Ordering::Release);
    }
}

impl<'ui> DrawListMut<'ui> {
    fn lock_draw_list() {
        let already_loaded = DRAW_LIST_LOADED
            .compare_exchange(
                false,
                true,
                std::sync::atomic::Ordering::Acquire,
                std::sync::atomic::Ordering::Relaxed,
            )
            .is_err();
        if already_loaded {
            panic!("DrawListMut is already loaded! You can only load one instance of it!")
        }
    }

    pub(crate) fn window(_: &Ui<'ui>) -> Self {
        Self::lock_draw_list();
        Self {
            draw_list: unsafe { sys::igGetWindowDrawList() },
            _phantom: PhantomData,
        }
    }

    pub(crate) fn background(_: &Ui<'ui>) -> Self {
        Self::lock_draw_list();
        Self {
            draw_list: unsafe { sys::igGetBackgroundDrawList() },
            _phantom: PhantomData,
        }
    }

    pub(crate) fn foreground(_: &Ui<'ui>) -> Self {
        Self::lock_draw_list();
        Self {
            draw_list: unsafe { sys::igGetForegroundDrawList() },
            _phantom: PhantomData,
        }
    }

    /// Split into *channels_count* drawing channels.
    /// At the end of the closure, the channels are merged. The objects
    /// are then drawn in the increasing order of their channel number, and not
    /// in the order they were called.
    ///
    /// # Example
    ///
    /// ```rust,no_run
    /// # use imgui::*;
    /// fn custom_drawing(ui: &Ui) {
    ///     let draw_list = ui.get_window_draw_list();
    ///     draw_list.channels_split(2, |channels| {
    ///         channels.set_current(1);
    ///         // ... Draw channel 1
    ///         channels.set_current(0);
    ///         // ... Draw channel 0
    ///     });
    /// }
    /// ```
    pub fn channels_split<F: FnOnce(&ChannelsSplit)>(&self, channels_count: u32, f: F) {
        unsafe { sys::ImDrawList_ChannelsSplit(self.draw_list, channels_count as i32) };
        f(&ChannelsSplit {
            draw_list: self,
            channels_count,
        });
        unsafe { sys::ImDrawList_ChannelsMerge(self.draw_list) };
    }
}

/// Represent the drawing interface within a call to [`channels_split`].
///
/// [`channels_split`]: DrawListMut::channels_split
pub struct ChannelsSplit<'ui> {
    draw_list: &'ui DrawListMut<'ui>,
    channels_count: u32,
}

impl<'ui> ChannelsSplit<'ui> {
    /// Change current channel.
    ///
    /// Panic if channel_index overflows the number of channels.
    pub fn set_current(&self, channel_index: u32) {
        assert!(
            channel_index < self.channels_count,
            "Channel cannot be set! Provided channel index ({}) is higher than channel count ({}).",
            channel_index,
            self.channels_count
        );
        unsafe {
            sys::ImDrawList_ChannelsSetCurrent(self.draw_list.draw_list, channel_index as i32)
        };
    }
}

/// Drawing functions
impl<'ui> DrawListMut<'ui> {
    /// Returns a line from point `p1` to `p2` with color `c`.
    pub fn add_line<C>(&'ui self, p1: [f32; 2], p2: [f32; 2], c: C) -> Line<'ui>
    where
        C: Into<ImColor32>,
    {
        Line::new(self, p1, p2, c)
    }

    /// Returns a rectangle whose upper-left corner is at point `p1`
    /// and lower-right corner is at point `p2`, with color `c`.
    pub fn add_rect<C>(&'ui self, p1: [f32; 2], p2: [f32; 2], c: C) -> Rect<'ui>
    where
        C: Into<ImColor32>,
    {
        Rect::new(self, p1, p2, c)
    }

    /// Draw a rectangle whose upper-left corner is at point `p1`
    /// and lower-right corner is at point `p2`.
    /// The remains parameters are the respective color of the corners
    /// in the counter-clockwise starting from the upper-left corner
    /// first.
    pub fn add_rect_filled_multicolor<C1, C2, C3, C4>(
        &self,
        p1: [f32; 2],
        p2: [f32; 2],
        col_upr_left: C1,
        col_upr_right: C2,
        col_bot_right: C3,
        col_bot_left: C4,
    ) where
        C1: Into<ImColor32>,
        C2: Into<ImColor32>,
        C3: Into<ImColor32>,
        C4: Into<ImColor32>,
    {
        unsafe {
            sys::ImDrawList_AddRectFilledMultiColor(
                self.draw_list,
                p1.into(),
                p2.into(),
                col_upr_left.into().into(),
                col_upr_right.into().into(),
                col_bot_right.into().into(),
                col_bot_left.into().into(),
            );
        }
    }

    /// Returns a triangle with the given 3 vertices `p1`, `p2` and `p3`
    /// and color `c`.
    pub fn add_triangle<C>(
        &'ui self,
        p1: [f32; 2],
        p2: [f32; 2],
        p3: [f32; 2],
        c: C,
    ) -> Triangle<'ui>
    where
        C: Into<ImColor32>,
    {
        Triangle::new(self, p1, p2, p3, c)
    }

    /// Returns a circle with the given `center`, `radius` and `color`.
    pub fn add_circle<C>(&'ui self, center: [f32; 2], radius: f32, color: C) -> Circle<'ui>
    where
        C: Into<ImColor32>,
    {
        Circle::new(self, center, radius, color)
    }

    /// Draw a text whose upper-left corner is at point `pos`.
    pub fn add_text<C, T>(&self, pos: [f32; 2], col: C, text: T)
    where
        C: Into<ImColor32>,
        T: AsRef<str>,
    {
        use std::os::raw::c_char;

        let text = text.as_ref();
        unsafe {
            let start = text.as_ptr() as *const c_char;
            let end = (start as usize + text.len()) as *const c_char;
            sys::ImDrawList_AddTextVec2(self.draw_list, pos.into(), col.into().into(), start, end)
        }
    }

    /// Returns a Bezier curve stretching from `pos0` to `pos1`, whose
    /// curvature is defined by `cp0` and `cp1`.
    pub fn add_bezier_curve<C>(
        &'ui self,
        pos0: [f32; 2],
        cp0: [f32; 2],
        cp1: [f32; 2],
        pos1: [f32; 2],
        color: C,
    ) -> BezierCurve<'ui>
    where
        C: Into<ImColor32>,
    {
        BezierCurve::new(self, pos0, cp0, cp1, pos1, color)
    }

    /// Push a clipping rectangle on the stack, run `f` and pop it.
    ///
    /// Clip all drawings done within the closure `f` in the given
    /// rectangle.
    pub fn with_clip_rect<F>(&self, min: [f32; 2], max: [f32; 2], f: F)
    where
        F: FnOnce(),
    {
        unsafe { sys::ImDrawList_PushClipRect(self.draw_list, min.into(), max.into(), false) }
        f();
        unsafe { sys::ImDrawList_PopClipRect(self.draw_list) }
    }

    /// Push a clipping rectangle on the stack, run `f` and pop it.
    ///
    /// Clip all drawings done within the closure `f` in the given
    /// rectangle. Intersect with all clipping rectangle previously on
    /// the stack.
    pub fn with_clip_rect_intersect<F>(&self, min: [f32; 2], max: [f32; 2], f: F)
    where
        F: FnOnce(),
    {
        unsafe { sys::ImDrawList_PushClipRect(self.draw_list, min.into(), max.into(), true) }
        f();
        unsafe { sys::ImDrawList_PopClipRect(self.draw_list) }
    }
}

/// # Images
impl<'ui> DrawListMut<'ui> {
    /// Draw the specified image in the rect specified by `p_min` to
    /// `p_max`.
    ///
    /// # Examples
    ///
    /// ```
    /// # use imgui::*;
    /// fn custom_button(ui: &Ui, img_id: TextureId) {
    ///     // Tint image red
    ///
    ///     // Invisible button is good widget to customise with custom image
    ///     ui.invisible_button(im_str!("custom_button"), [100.0, 20.0]);
    ///
    ///     // Red tint when button is hovered, no tint otherwise
    ///     let overlay_color = if ui.is_item_hovered() {
    ///         [1.0, 0.6, 0.6, 1.0]
    ///     } else {
    ///         [1.0, 1.0, 1.0, 1.0]
    ///     };
    ///
    ///     // Get draw list and draw image over invisible button
    ///     let draw_list = ui.get_window_draw_list();
    ///     draw_list
    ///         .add_image(img_id, ui.item_rect_min(), ui.item_rect_max())
    ///         .col(overlay_color)
    ///         .build();
    /// }
    /// ```
    pub fn add_image(&'ui self, texture_id: TextureId, p_min: [f32; 2], p_max: [f32; 2]) -> Image {
        Image::new(self, texture_id, p_min, p_max)
    }

    /// Draw the specified image to a quad with the specified
    /// coordinates. Similar to [`DrawListMut::add_image`] but this
    /// method is able to draw non-rectangle images.
    pub fn add_image_quad(
        &'ui self,
        texture_id: TextureId,
        p1: [f32; 2],
        p2: [f32; 2],
        p3: [f32; 2],
        p4: [f32; 2],
    ) -> ImageQuad {
        ImageQuad::new(self, texture_id, p1, p2, p3, p4)
    }

    /// Draw the speciied image, with rounded corners
    pub fn add_image_rounded(
        &'ui self,
        texture_id: TextureId,
        p_min: [f32; 2],
        p_max: [f32; 2],
        rounding: f32,
    ) -> ImageRounded {
        ImageRounded::new(self, texture_id, p_min, p_max, rounding)
    }
}

/// Represents a line about to be drawn
#[must_use = "should call .build() to draw the object"]
pub struct Line<'ui> {
    p1: [f32; 2],
    p2: [f32; 2],
    color: ImColor32,
    thickness: f32,
    draw_list: &'ui DrawListMut<'ui>,
}

impl<'ui> Line<'ui> {
    fn new<C>(draw_list: &'ui DrawListMut, p1: [f32; 2], p2: [f32; 2], c: C) -> Self
    where
        C: Into<ImColor32>,
    {
        Self {
            p1,
            p2,
            color: c.into(),
            thickness: 1.0,
            draw_list,
        }
    }

    /// Set line's thickness (default to 1.0 pixel)
    pub fn thickness(mut self, thickness: f32) -> Self {
        self.thickness = thickness;
        self
    }

    /// Draw the line on the window
    pub fn build(self) {
        unsafe {
            sys::ImDrawList_AddLine(
                self.draw_list.draw_list,
                self.p1.into(),
                self.p2.into(),
                self.color.into(),
                self.thickness,
            )
        }
    }
}

/// Represents a rectangle about to be drawn
#[must_use = "should call .build() to draw the object"]
pub struct Rect<'ui> {
    p1: [f32; 2],
    p2: [f32; 2],
    color: ImColor32,
    rounding: f32,
    flags: ImDrawCornerFlags,
    thickness: f32,
    filled: bool,
    draw_list: &'ui DrawListMut<'ui>,
}

impl<'ui> Rect<'ui> {
    fn new<C>(draw_list: &'ui DrawListMut, p1: [f32; 2], p2: [f32; 2], c: C) -> Self
    where
        C: Into<ImColor32>,
    {
        Self {
            p1,
            p2,
            color: c.into(),
            rounding: 0.0,
            flags: ImDrawCornerFlags::All,
            thickness: 1.0,
            filled: false,
            draw_list,
        }
    }

    /// Set rectangle's corner rounding (default to 0.0: no rounding).
    /// By default all corners are rounded if this value is set.
    pub fn rounding(mut self, rounding: f32) -> Self {
        self.rounding = rounding;
        self
    }

    /// Set flag to indicate if rectangle's top-left corner will be rounded.
    pub fn round_top_left(mut self, value: bool) -> Self {
        self.flags.set(ImDrawCornerFlags::TopLeft, value);
        self
    }

    /// Set flag to indicate if rectangle's top-right corner will be rounded.
    pub fn round_top_right(mut self, value: bool) -> Self {
        self.flags.set(ImDrawCornerFlags::TopRight, value);
        self
    }

    /// Set flag to indicate if rectangle's bottom-left corner will be rounded.
    pub fn round_bot_left(mut self, value: bool) -> Self {
        self.flags.set(ImDrawCornerFlags::BotLeft, value);
        self
    }

    /// Set flag to indicate if rectangle's bottom-right corner will be rounded.
    pub fn round_bot_right(mut self, value: bool) -> Self {
        self.flags.set(ImDrawCornerFlags::BotRight, value);
        self
    }

    /// Set rectangle's thickness (default to 1.0 pixel).
    pub fn thickness(mut self, thickness: f32) -> Self {
        self.thickness = thickness;
        self
    }

    /// Set to `true` to make a filled rectangle (default to `false`).
    pub fn filled(mut self, filled: bool) -> Self {
        self.filled = filled;
        self
    }

    /// Draw the rectangle on the window.
    pub fn build(self) {
        if self.filled {
            unsafe {
                sys::ImDrawList_AddRectFilled(
                    self.draw_list.draw_list,
                    self.p1.into(),
                    self.p2.into(),
                    self.color.into(),
                    self.rounding,
                    self.flags.bits(),
                );
            }
        } else {
            unsafe {
                sys::ImDrawList_AddRect(
                    self.draw_list.draw_list,
                    self.p1.into(),
                    self.p2.into(),
                    self.color.into(),
                    self.rounding,
                    self.flags.bits(),
                    self.thickness,
                );
            }
        }
    }
}

/// Represents a triangle about to be drawn on the window
#[must_use = "should call .build() to draw the object"]
pub struct Triangle<'ui> {
    p1: [f32; 2],
    p2: [f32; 2],
    p3: [f32; 2],
    color: ImColor32,
    thickness: f32,
    filled: bool,
    draw_list: &'ui DrawListMut<'ui>,
}

impl<'ui> Triangle<'ui> {
    fn new<C>(draw_list: &'ui DrawListMut, p1: [f32; 2], p2: [f32; 2], p3: [f32; 2], c: C) -> Self
    where
        C: Into<ImColor32>,
    {
        Self {
            p1,
            p2,
            p3,
            color: c.into(),
            thickness: 1.0,
            filled: false,
            draw_list,
        }
    }

    /// Set triangle's thickness (default to 1.0 pixel)
    pub fn thickness(mut self, thickness: f32) -> Self {
        self.thickness = thickness;
        self
    }

    /// Set to `true` to make a filled triangle (default to `false`).
    pub fn filled(mut self, filled: bool) -> Self {
        self.filled = filled;
        self
    }

    /// Draw the triangle on the window.
    pub fn build(self) {
        if self.filled {
            unsafe {
                sys::ImDrawList_AddTriangleFilled(
                    self.draw_list.draw_list,
                    self.p1.into(),
                    self.p2.into(),
                    self.p3.into(),
                    self.color.into(),
                )
            }
        } else {
            unsafe {
                sys::ImDrawList_AddTriangle(
                    self.draw_list.draw_list,
                    self.p1.into(),
                    self.p2.into(),
                    self.p3.into(),
                    self.color.into(),
                    self.thickness,
                )
            }
        }
    }
}

/// Represents a circle about to be drawn
#[must_use = "should call .build() to draw the object"]
pub struct Circle<'ui> {
    center: [f32; 2],
    radius: f32,
    color: ImColor32,
    num_segments: u32,
    thickness: f32,
    filled: bool,
    draw_list: &'ui DrawListMut<'ui>,
}

impl<'ui> Circle<'ui> {
    pub fn new<C>(draw_list: &'ui DrawListMut, center: [f32; 2], radius: f32, color: C) -> Self
    where
        C: Into<ImColor32>,
    {
        Self {
            center,
            radius,
            color: color.into(),
            num_segments: 0,
            thickness: 1.0,
            filled: false,
            draw_list,
        }
    }

    /// Set number of segment used to draw the circle, default to 0.
    /// Add more segments if you want a smoother circle.
    pub fn num_segments(mut self, num_segments: u32) -> Self {
        self.num_segments = num_segments;
        self
    }

    /// Set circle's thickness (default to 1.0 pixel)
    pub fn thickness(mut self, thickness: f32) -> Self {
        self.thickness = thickness;
        self
    }

    /// Set to `true` to make a filled circle (default to `false`).
    pub fn filled(mut self, filled: bool) -> Self {
        self.filled = filled;
        self
    }

    /// Draw the circle on the window.
    pub fn build(self) {
        if self.filled {
            unsafe {
                sys::ImDrawList_AddCircleFilled(
                    self.draw_list.draw_list,
                    self.center.into(),
                    self.radius,
                    self.color.into(),
                    self.num_segments as i32,
                )
            }
        } else {
            unsafe {
                sys::ImDrawList_AddCircle(
                    self.draw_list.draw_list,
                    self.center.into(),
                    self.radius,
                    self.color.into(),
                    self.num_segments as i32,
                    self.thickness,
                )
            }
        }
    }
}

/// Represents a Bezier curve about to be drawn
#[must_use = "should call .build() to draw the object"]
pub struct BezierCurve<'ui> {
    pos0: [f32; 2],
    cp0: [f32; 2],
    pos1: [f32; 2],
    cp1: [f32; 2],
    color: ImColor32,
    thickness: f32,
    /// If num_segments is not set, the bezier curve is auto-tessalated.
    num_segments: Option<u32>,
    draw_list: &'ui DrawListMut<'ui>,
}

impl<'ui> BezierCurve<'ui> {
    fn new<C>(
        draw_list: &'ui DrawListMut,
        pos0: [f32; 2],
        cp0: [f32; 2],
        cp1: [f32; 2],
        pos1: [f32; 2],
        c: C,
    ) -> Self
    where
        C: Into<ImColor32>,
    {
        Self {
            pos0,
            cp0,
            cp1,
            pos1,
            color: c.into(),
            thickness: 1.0,
            num_segments: None,
            draw_list,
        }
    }

    /// Set curve's thickness (default to 1.0 pixel)
    pub fn thickness(mut self, thickness: f32) -> Self {
        self.thickness = thickness;
        self
    }

    /// Set number of segments used to draw the Bezier curve. If not set, the
    /// bezier curve is auto-tessalated.
    pub fn num_segments(mut self, num_segments: u32) -> Self {
        self.num_segments = Some(num_segments);
        self
    }

    /// Draw the curve on the window.
    pub fn build(self) {
        unsafe {
            sys::ImDrawList_AddBezierCubic(
                self.draw_list.draw_list,
                self.pos0.into(),
                self.cp0.into(),
                self.cp1.into(),
                self.pos1.into(),
                self.color.into(),
                self.thickness,
                self.num_segments.unwrap_or(0) as i32,
            )
        }
    }
}

/// Represents a image about to be drawn
#[must_use = "should call .build() to draw the object"]
pub struct Image<'ui> {
    texture_id: TextureId,
    p_min: [f32; 2],
    p_max: [f32; 2],
    uv_min: [f32; 2],
    uv_max: [f32; 2],
    col: ImColor32,
    draw_list: &'ui DrawListMut<'ui>,
}

impl<'ui> Image<'ui> {
    fn new(
        draw_list: &'ui DrawListMut,
        texture_id: TextureId,
        p_min: [f32; 2],
        p_max: [f32; 2],
    ) -> Self {
        Self {
            texture_id,
            p_min,
            p_max,
            uv_min: [0.0, 0.0],
            uv_max: [1.0, 1.0],
            col: [1.0, 1.0, 1.0, 1.0].into(),
            draw_list,
        }
    }

    /// Set uv_min (default `[0.0, 0.0]`)
    pub fn uv_min(mut self, uv_min: [f32; 2]) -> Self {
        self.uv_min = uv_min;
        self
    }
    /// Set uv_max (default `[1.0, 1.0]`)
    pub fn uv_max(mut self, uv_max: [f32; 2]) -> Self {
        self.uv_max = uv_max;
        self
    }

    /// Set color tint (default: no tint/white `[1.0, 1.0, 1.0, 1.0]`)
    pub fn col<C>(mut self, col: C) -> Self
    where
        C: Into<ImColor32>,
    {
        self.col = col.into();
        self
    }

    /// Draw the image on the window.
    pub fn build(self) {
        use std::os::raw::c_void;

        unsafe {
            sys::ImDrawList_AddImage(
                self.draw_list.draw_list,
                self.texture_id.id() as *mut c_void,
                self.p_min.into(),
                self.p_max.into(),
                self.uv_min.into(),
                self.uv_max.into(),
                self.col.into(),
            );
        }
    }
}

/// Represents a image about to be drawn
#[must_use = "should call .build() to draw the object"]
pub struct ImageQuad<'ui> {
    texture_id: TextureId,
    p1: [f32; 2],
    p2: [f32; 2],
    p3: [f32; 2],
    p4: [f32; 2],
    uv1: [f32; 2],
    uv2: [f32; 2],
    uv3: [f32; 2],
    uv4: [f32; 2],
    col: ImColor32,
    draw_list: &'ui DrawListMut<'ui>,
}

impl<'ui> ImageQuad<'ui> {
    fn new(
        draw_list: &'ui DrawListMut,
        texture_id: TextureId,
        p1: [f32; 2],
        p2: [f32; 2],
        p3: [f32; 2],
        p4: [f32; 2],
    ) -> Self {
        Self {
            texture_id,
            p1,
            p2,
            p3,
            p4,
            uv1: [0.0, 0.0],
            uv2: [1.0, 0.0],
            uv3: [1.0, 1.0],
            uv4: [0.0, 1.0],
            col: [1.0, 1.0, 1.0, 1.0].into(),
            draw_list,
        }
    }

    /// Set uv coordinates of each point of the quad. If not called, defaults are:
    ///
    /// ```
    /// uv1: [0, 0],
    /// uv2: [1, 0],
    /// uv3: [1, 1],
    /// uv4: [0, 1],
    /// ```
    pub fn uv(mut self, uv1: [f32; 2], uv2: [f32; 2], uv3: [f32; 2], uv4: [f32; 2]) -> Self {
        self.uv1 = uv1;
        self.uv2 = uv2;
        self.uv3 = uv3;
        self.uv4 = uv4;
        self
    }

    /// Set color tint (default: no tint/white `[1.0, 1.0, 1.0, 1.0]`)
    pub fn col<C>(mut self, col: C) -> Self
    where
        C: Into<ImColor32>,
    {
        self.col = col.into();
        self
    }

    /// Draw the image on the window.
    pub fn build(self) {
        use std::os::raw::c_void;

        unsafe {
            sys::ImDrawList_AddImageQuad(
                self.draw_list.draw_list,
                self.texture_id.id() as *mut c_void,
                self.p1.into(),
                self.p2.into(),
                self.p3.into(),
                self.p4.into(),
                self.uv1.into(),
                self.uv2.into(),
                self.uv3.into(),
                self.uv4.into(),
                self.col.into(),
            );
        }
    }
}

/// Represents a image about to be drawn
#[must_use = "should call .build() to draw the object"]
pub struct ImageRounded<'ui> {
    texture_id: TextureId,
    p_min: [f32; 2],
    p_max: [f32; 2],
    uv_min: [f32; 2],
    uv_max: [f32; 2],
    col: ImColor32,
    rounding: f32,
    rounding_corners: ImDrawCornerFlags,
    draw_list: &'ui DrawListMut<'ui>,
}

impl<'ui> ImageRounded<'ui> {
    fn new(
        draw_list: &'ui DrawListMut,
        texture_id: TextureId,
        p_min: [f32; 2],
        p_max: [f32; 2],
        rounding: f32,
    ) -> Self {
        Self {
            texture_id,
            p_min,
            p_max,
            uv_min: [0.0, 0.0],
            uv_max: [1.0, 1.0],
            col: [1.0, 1.0, 1.0, 1.0].into(),
            rounding,
            rounding_corners: ImDrawCornerFlags::All,
            draw_list,
        }
    }

    /// Set uv_min (default `[0.0, 0.0]`)
    pub fn uv_min(mut self, uv_min: [f32; 2]) -> Self {
        self.uv_min = uv_min;
        self
    }
    /// Set uv_max (default `[1.0, 1.0]`)
    pub fn uv_max(mut self, uv_max: [f32; 2]) -> Self {
        self.uv_max = uv_max;
        self
    }

    /// Set color tint (default: no tint/white `[1.0, 1.0, 1.0, 1.0]`)
    pub fn col<C>(mut self, col: C) -> Self
    where
        C: Into<ImColor32>,
    {
        self.col = col.into();
        self
    }

    /// Set flag to indicate rounding on all all corners.
    pub fn round_all(mut self, value: bool) -> Self {
        self.rounding_corners.set(ImDrawCornerFlags::All, value);
        self
    }

    /// Set flag to indicate if image's top-left corner will be rounded.
    pub fn round_top_left(mut self, value: bool) -> Self {
        self.rounding_corners.set(ImDrawCornerFlags::TopLeft, value);
        self
    }

    /// Set flag to indicate if image's top-right corner will be rounded.
    pub fn round_top_right(mut self, value: bool) -> Self {
        self.rounding_corners
            .set(ImDrawCornerFlags::TopRight, value);
        self
    }

    /// Set flag to indicate if image's bottom-left corner will be rounded.
    pub fn round_bot_left(mut self, value: bool) -> Self {
        self.rounding_corners.set(ImDrawCornerFlags::BotLeft, value);
        self
    }

    /// Set flag to indicate if image's bottom-right corner will be rounded.
    pub fn round_bot_right(mut self, value: bool) -> Self {
        self.rounding_corners
            .set(ImDrawCornerFlags::BotRight, value);
        self
    }

    /// Draw the image on the window.
    pub fn build(self) {
        use std::os::raw::c_void;

        unsafe {
            sys::ImDrawList_AddImageRounded(
                self.draw_list.draw_list,
                self.texture_id.id() as *mut c_void,
                self.p_min.into(),
                self.p_max.into(),
                self.uv_min.into(),
                self.uv_max.into(),
                self.col.into(),
                self.rounding.into(),
                self.rounding_corners.bits(),
            );
        }
    }
}
