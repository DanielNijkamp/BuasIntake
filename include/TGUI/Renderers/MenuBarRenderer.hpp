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


#ifndef TGUI_MENU_BAR_RENDERER_HPP
#define TGUI_MENU_BAR_RENDERER_HPP


#include <TGUI/Renderers/WidgetRenderer.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TGUI_MODULE_EXPORT namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Renderer for the MenuBar widget
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class TGUI_API MenuBarRenderer : public WidgetRenderer
    {
    public:

        using WidgetRenderer::WidgetRenderer;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the background color of the menu bar
        ///
        /// @param backgroundColor  The new background color
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setBackgroundColor(Color backgroundColor);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the background color
        ///
        /// @return Background color
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD Color getBackgroundColor() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the background color of the selected item
        ///
        /// @param backgroundColor  The new selected item background color
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setSelectedBackgroundColor(Color backgroundColor);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the background color of the selected item
        ///
        /// @return Selected item background color
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD Color getSelectedBackgroundColor() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the color of the text
        ///
        /// @param textColor  The new text color
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setTextColor(Color textColor);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the color of the text
        ///
        /// @return Text color
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD Color getTextColor() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the color of the text from the selected item
        ///
        /// @param textColor  The new selected text color
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setSelectedTextColor(Color textColor);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the color of the text from the selected item
        ///
        /// @return Selected text color
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD Color getSelectedTextColor() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the color of the text when disabled
        /// @param textColor  The new text color
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setTextColorDisabled(Color textColor);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the color of the text when disabled
        /// @return Text color
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD Color getTextColorDisabled() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the color of the separators
        /// @param separatorColor  The new separator color
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setSeparatorColor(Color separatorColor);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the color of the separators
        /// @return Separator color
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD Color getSeparatorColor() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the image that is used to fill the entire menu bar
        ///
        /// @param texture  The background texture
        ///
        /// When this image is set, the background color property will be ignored.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setTextureBackground(const Texture& texture);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the image that is used to fill the entire menu bar
        ///
        /// @return Background texture
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD const Texture& getTextureBackground() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the image that is displayed when the menu item is not selected
        ///
        /// @param texture  New item background texture
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setTextureItemBackground(const Texture& texture);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the image that is displayed when the menu item is not selected
        ///
        /// @return Item background texture
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD const Texture& getTextureItemBackground() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the image that is used as background of the selected menu item
        ///
        /// @param texture  New selected item background texture
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setTextureSelectedItemBackground(const Texture& texture);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the image that is used as background of the selected menu item
        ///
        /// @return Selected item background texture
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD const Texture& getTextureSelectedItemBackground() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the distance between the text and the side of the menu item
        ///
        /// @param distanceToSide  distance between the text and the side of the menu item
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setDistanceToSide(float distanceToSide);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the distance between the text and the side of the menu item
        ///
        /// @return Distance between the text and the side of the menu item
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD float getDistanceToSide() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the height of the separators
        /// @param thickness  The new separator thickness
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setSeparatorThickness(float thickness);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the height of the separators
        /// @return Separator thickness
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD float getSeparatorThickness() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the distance between the separator and the menu items above and below it
        /// @param padding  Padding above and below the separator
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setSeparatorVerticalPadding(float padding);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the distance between the separator and the menu items above and below it
        /// @return Padding above and below the separator
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD float getSeparatorVerticalPadding() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the distance between the separator and the sides of the menu
        /// @param padding  Padding next to the separator
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setSeparatorSidePadding(float padding);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the distance between the separator and the sides of the menu
        /// @return Padding next to the separator
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD float getSeparatorSidePadding() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // TGUI_MENU_BAR_RENDERER_HPP
