/* SPDX-FileCopyrightText: 2024 Google LLC */
/* SPDX-License-Identifier: Apache-2.0 */

#pragma once

#include <applib/graphics/gtypes.h>

#if !PUBLIC_SDK
#include <board/display.h>
#endif

//! PreferredContentSize represents the display scale of all the app's UI components. The enum
//! contains all sizes that all platforms as a whole are capable of displaying, but each individual
//! platform may not be able to display all sizes.
//! @note As of version 4.1, platforms other than Emery cannot display extra large and Emery itself
//! cannot display small.
typedef enum PreferredContentSize {
  PreferredContentSizeSmall,
  PreferredContentSizeMedium,
  PreferredContentSizeLarge,
  PreferredContentSizeExtraLarge,
  NumPreferredContentSizes,
} PreferredContentSize;

#if !PUBLIC_SDK
//! Use display height to determine default content size: larger displays (>= 200px height) use
//! Large
#if PBL_DISPLAY_HEIGHT >= 200
#define PreferredContentSizeDefault PreferredContentSizeLarge
#else
#define PreferredContentSizeDefault PreferredContentSizeMedium
#endif
#endif

//! @internal
//! Switch on a PreferredContentSize. Defaults to SMALL value.
//! @note Optimal use of this does _not_ call a function for the `SIZE` argument! If you do, it
//! will be _evaluated on every comparison_, which is unlikely to be what you want!
#define PREFERRED_CONTENT_SIZE_SWITCH(SIZE, SMALL, MEDIUM, LARGE, EXTRALARGE) \
  ((SIZE == PreferredContentSizeMedium)       ? (MEDIUM)                      \
   : (SIZE == PreferredContentSizeLarge)      ? (LARGE)                       \
   : (SIZE == PreferredContentSizeExtraLarge) ? (EXTRALARGE)                  \
                                              : (SMALL))

//! Returns the user's preferred content size representing the scale of all the app's UI components
//! should use for display.
//! @return The user's \ref PreferredContentSize setting.
PreferredContentSize preferred_content_size(void);

//! System theme color palette.
typedef struct SystemThemeColors {
  GColor8 primary_color;        //!< Primary accent / highlight color
  GColor8 primary_text_color;   //!< Legible text color over primary_color
  GColor8 secondary_color;      //!< Secondary accent color
  GColor8 secondary_text_color; //!< Legible text color over secondary_color
  GColor8 background_color;     //!< Window / menu background color
  GColor8 text_color;           //!< Primary text color over background_color
  GColor8 subtitle_color;       //!< Secondary / subtitle text color over background_color
} SystemThemeColors;

//! Populates `colors_out` with the active system theme color palette.
//! @param[out] colors_out Pointer to a \ref SystemThemeColors struct to populate.
void system_theme_get_colors(SystemThemeColors *colors_out);

//! @return The active system theme's primary accent color.
GColor system_theme_get_primary_color(void);

//! @return The active system theme's secondary accent color.
GColor system_theme_get_secondary_color(void);

//! @return The active system theme's background color.
GColor system_theme_get_background_color(void);

//! @return The active system theme's primary text color.
GColor system_theme_get_text_color(void);
