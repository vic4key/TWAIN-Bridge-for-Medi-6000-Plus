// Medi-6000.Plus.cpp : Implements the exported functions for the DLL application.
//

#include "stdafx.h"
#include "resource.h"
#include "Utilities.h"
#include "Medi-6000.Plus.h"

#include <string>
#include <vector>

#if defined(_M_X64) || defined(__x86_64__)
#include <vic7defs.h>
#pragma comment(lib, "vic64.lib")
#pragma comment(lib, "vicfx64.lib")
#pragma comment(lib, "Vicstats64.lib")
#pragma comment(lib, "Victw64.lib")
#else
#include <VICDEFS.H>
#pragma comment(lib, "VIC32MS.LIB")
#pragma comment(lib, "VCTW32MS.LIB")
#endif

void CALLBACK fnTWAINSelect(HWND hwnd, HINSTANCE hinst, LPSTR lpszCmdLine, int nCmdShow)
{
  // Arguments

  auto args = util::SplitStringA(lpszCmdLine, " ");
  if (args.empty())
  {
    util::MessageBoxErrorA(nullptr, IDS_ARGUMENTS_INCORRECT);
    return;
  }

  HWND hw = nullptr;

  try
  {
    hw = reinterpret_cast<HWND>(std::stoul(args.at(0))); // arg0 -> Window Handle (HWND)
  }
  catch (std::exception& e)
  {
    util::MessageBoxErrorA(nullptr, e.what());
    return;
  }

  // TW Select Source

  auto rcode = TWselectsource(hw);
  if (rcode != NO_ERROR)
  {
    util::MessageBoxErrorA(hw, IDS_SELECT_SOURCE_ERROR);
    return;
  }
}

void CALLBACK fnTWAINAcquire(HWND hwnd, HINSTANCE hinst, LPSTR lpszCmdLine, int nCmdShow)
{
  // Arguments

  auto args = util::SplitStringA(lpszCmdLine, " ");
  if (args.empty())
  {
    util::MessageBoxErrorA(nullptr, IDS_ARGUMENTS_INCORRECT);
    return;
  }

  HWND hw = nullptr;

  try
  {
    hw = reinterpret_cast<HWND>(std::stoul(args.at(0))); // arg0 -> Window Handle (HWND)
  }
  catch (std::exception& e)
  {
    util::MessageBoxErrorA(nullptr, e.what());
    return;
  }

  std::string proName = args.at(1); // arg1 -> Product Name  (String)

  // Acquire / Scan Image

  TWsetproductname(proName.c_str());

  imgdes img = {0};
  auto rcode = TWscanimage(hw, &img);

  if (rcode != NO_ERROR)
  {
    std::string msg = "";

    switch (rcode)
    {
    case TWAIN_SCAN_CANCEL:
      // msg = LoadRCStringA(IDS_TWAIN_SCAN_CANCEL);
      break;

    case TWAIN_NODSM:
      msg = util::LoadRCStringA(IDS_TWAIN_NODSM);
      break;

    case TWAIN_NODS:
      msg = util::LoadRCStringA(IDS_TWAIN_NODS);
      break;

    case TWAIN_BUSY:
      msg = util::LoadRCStringA(IDS_TWAIN_BUSY);
      break;

    case BAD_MEM:
      msg = util::LoadRCStringA(IDS_BAD_MEM);
      break;

    case BAD_CMP:
      msg = util::LoadRCStringA(IDS_BAD_CMP);
      break;

    case BAD_BPP:
      msg = util::LoadRCStringA(IDS_BAD_BPP);
      break;

    default:
      {
        msg = util::LoadRCStringA(IDS_OTHER_ERROR);
        char s[MAXBYTE] = {0};
        sprintf_s(s, MAXBYTE, msg.c_str(), rcode, TWgeterror());
        msg = s;
      }
      break;
    }

    if (!msg.empty())
    {
      util::MessageBoxErrorA(hw, msg.c_str());
    }

    return;
  }

  if (img.ibuff == nullptr)
  {
    util::MessageBoxErrorA(hw, IDS_SCAN_IMAGE_FAILED);
    return;
  }

  // Put the scanned image into memory as PNG image type

  UCHAR * pPNG = nullptr;
  rcode = savepngtobuffer(&pPNG, &img, 0);
  if (rcode != NO_ERROR)
  {
    util::MessageBoxErrorA(hw, IDS_CONVERT_SCANNED_IMAGE_FAILED);
    return;
  }

  DWORD totalSize = BUFFER_SIZE(pPNG);
  if ((totalSize == 0) || (totalSize == INVALID_FILE_SIZE))
  {
    util::MessageBoxErrorA(hw, IDS_SIZE_SCANNED_IMAGE_FAILED);
    return;
  }

  // Send PNG image in the memory to parent application

  COPYDATASTRUCT cd = {0};
  cd.cbData = totalSize;
  cd.lpData = pPNG;

  SendMessageA(hw, WM_COPYDATA, WPARAM(NULL), LPARAM(&cd));

  // Necessary free the PNG buffer but 32-bit version did not support this.
  // freebuffer(pPNG);
}