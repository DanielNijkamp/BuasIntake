/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus' Graphical User Interface
// Copyright (C) 2012-2024 Bruno Van de Velde (vdv_b@tgui.eu)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef TGUI_CANVAS_GLES2_HPP
#define TGUI_CANVAS_GLES2_HPP

#include <TGUI/Backend/Renderer/GLES2/BackendTextureGLES2.hpp>

#if !TGUI_BUILD_AS_CXX_MODULE
    #include <TGUI/Backend/Renderer/BackendRenderTarget.hpp>
    #include <TGUI/Widgets/CanvasBase.hpp>
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TGUI_MODULE_EXPORT namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// CanvasGLES2 provides a way to directly render OpenGL ES contents on a widget
    ///
    /// When gui.draw() is called, all widgets are drawn at once. If you wish to have custom OpenGL ES rendering inbetween
    /// TGUI widgets (e.g. draw to the background of a child window) then you need to use a CanvasGLES2 widget.
    ///
    /// The canvas widget is essentially just a wrapper around a framebuffer and its texture. You draw your OpenGL ES contents on
    /// top of the canvas instead of on the window. The canvas is then added to the gui between the widgets where you want the
    /// rendering to appear.
    ///
    /// You can redraw the contents of the canvas at any time, but make sure to always start by calling bindFramebuffer and
    /// end the rendering by calling glBindFramebuffer again.
    ///
    /// Example:
    /// @code
    /// auto canvas = tgui::CanvasGLES2::create({400, 300});
    /// gui.add(canvas);
    ///
    /// canvas->bindFramebuffer();              // Let drawing happen on the canvas instead of the window
    /// glClear(GL_COLOR_BUFFER_BIT);           // Clear the contents of the canvas (with color set with glClearColor)
    /// // Draw whatever you want to draw on the canvas here
    /// glBindFramebuffer(GL_FRAMEBUFFER, 0);   // Let further drawing happen on the window again
    /// @endcode
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class TGUI_API CanvasGLES2 : public CanvasBase
    {
    public:

        using Ptr = std::shared_ptr<CanvasGLES2>; //!< Shared widget pointer
        using ConstPtr = std::shared_ptr<const CanvasGLES2>; //!< Shared constant widget pointer

        static constexpr const char StaticWidgetType[] = "CanvasGLES2"; //!< Type name of the widget


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /// @brief Constructor
        /// @param typeName     Type of the widget
        /// @param initRenderer Should the renderer be initialized? Should be true unless a derived class initializes it.
        /// @see create
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        CanvasGLES2(const char* typeName = StaticWidgetType, bool initRenderer = true);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Copy constructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        CanvasGLES2(const CanvasGLES2& copy);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Default move constructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        CanvasGLES2(CanvasGLES2&& copy) = default;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Destructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ~CanvasGLES2() override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Overload of copy assignment operator
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        CanvasGLES2& operator= (const CanvasGLES2& right);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Default move assignment operator
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        CanvasGLES2& operator= (CanvasGLES2&& right) = default;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Creates a new canvas widget
        ///
        /// @param size  Size of the canvas
        ///
        /// @return The new canvas
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD static CanvasGLES2::Ptr create(const Layout2d& size = {"100%", "100%"});


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Makes a copy of another canvas
        ///
        /// @param canvas  The other canvas
        ///
        /// @return The new canvas
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD static CanvasGLES2::Ptr copy(const CanvasGLES2::ConstPtr& canvas);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the size of the widget
        ///
        /// @param size  The new size of the widget
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setSize(const Layout2d& size) override;
        using Widget::setSize;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Draw the widget to a render target
        ///
        /// @param target Render target to draw to
        /// @param states Current render states
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void draw(BackendRenderTarget& target, RenderStates states) const override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Binds the framebuffer of the canvas
        ///
        /// @return id of internal framebuffer that was just bound by this function
        ///
        /// This will call glBindFramebuffer and glFramebufferTexture2D on the internal texture.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        unsigned int bindFramebuffer() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Makes a copy of the widget
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD Widget::Ptr clone() const override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:

        unsigned int m_textureId = 0;
        unsigned int m_frameBuffer = 0;
        Vector2u m_textureSize;
        Vector2u m_usedTextureSize;
        std::shared_ptr<BackendTextureGLES2> m_backendTexture = std::make_shared<BackendTextureGLES2>();
    };
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // TGUI_CANVAS_GLES2_HPP
