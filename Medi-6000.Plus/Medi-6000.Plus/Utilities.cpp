// Utilities.h : Implements the exported functions for the DLL application.
//

#include "stdafx.h"
#include "Utilities.h"

namespace util
{
  std::string LoadRCStringA(resid_t resid)
  {
    std::string result = "";

    char s[MAXBYTE] = {0};

    if (LoadStringA(nullptr, resid, s, sizeof(s)) == 0)
    {
      return result;
    }

    result = s;

    return result;
  };

  int MessageBoxErrorA(HWND hw, const std::string& msg)
  {
    return MessageBoxA(hw, msg.c_str(), "Error", MB_OK | MB_ICONERROR);
  }

  int MessageBoxErrorA(HWND hw, resid_t resid)
  {
    auto msg = LoadRCStringA(resid);
    return MessageBoxErrorA(hw, msg);
  }

  std::vector<std::string> SplitStringA(const std::string& text, const std::string& separator)
  {
    std::vector<std::string> l;
    l.clear();

    if (text.empty())
    {
      return l;
    }

    std::string s(text), sep(separator), sub;
    int start = 0, end = 0;

    end = s.find(sep);
    while (end != std::string::npos) {
      sub = s.substr(start, end - start);
      l.push_back(std::string(sub.c_str()));
      start = end + sep.length();
      end = s.find(sep, start);
    }

    sub = s.substr(start, end);
    l.push_back(std::string(sub.c_str()));

    return l;
  }
};