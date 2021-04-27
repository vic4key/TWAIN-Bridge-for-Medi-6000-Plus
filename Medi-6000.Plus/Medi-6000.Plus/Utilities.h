// Utilities.h : Defines the exported functions for the DLL application.
//

#pragma once

#include <string>
#include <vector>

typedef unsigned int resid_t;

namespace util
{
  /**
   * Load a string from application resource.
   * @param[in] resid The resource ID of a string.
   * @return The resource string.
   */
  std::string LoadRCStringA(resid_t resid);

  /**
   * Display an error message.
   * @param[in] hw The window handle.
   * @param[in] msg The message.
   * @return The message result.
   */
  int MessageBoxErrorA(HWND hw, const std::string& msg);

  /**
   * Display an error message.
   * @param[in] hw The window handle.
   * @param[in] resid The resource ID of a string.
   * @return The message result.
   */
  int MessageBoxErrorA(HWND hw, resid_t resid);

  /**
   * Split string to a list of sub-string by a separator string.
   * @param[in] text The string.
   * @param[in] separator The separator.
   * @return List of sub-string.
   */
  std::vector<std::string> SplitStringA(const std::string& text, const std::string& separator);
};