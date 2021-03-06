#ifndef CCHARSET_CONVERTER
#define CCHARSET_CONVERTER

/*
 *      Copyright (C) 2005-2013 Team XBMC
 *      http://xbmc.org
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with XBMC; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#include "settings/ISettingCallback.h"
#include "threads/CriticalSection.h"
#include "utils/GlobalsHandling.h"
#include "utils/uXstrings.h"

#include <string>
#include <vector>

class CSetting;

class CCharsetConverter : public ISettingCallback
{
public:
  CCharsetConverter();

  virtual void OnSettingChanged(const CSetting* setting);

  void reset();

  void clear();

  /**
   * Convert UTF-8 string to UTF-32 string.
   * No RTL logical-visual transformation is performed.
   * @param utf8StringSrc       is source UTF-8 string to convert
   * @param utf32StringDst      is output UTF-32 string, empty on any error
   * @param failOnBadChar       if set to true function will fail on invalid character,
   *                            otherwise invalid character will be skipped
   * @return true on successful conversion, false on any error
   */
  bool utf8ToUtf32(const std::string& utf8StringSrc, std::u32string& utf32StringDst, bool failOnBadChar = true);
  /**
   * Convert UTF-8 string to UTF-32 string.
   * No RTL logical-visual transformation is performed.
   * @param utf8StringSrc       is source UTF-8 string to convert
   * @param failOnBadChar       if set to true function will fail on invalid character,
   *                            otherwise invalid character will be skipped
   * @return converted string on successful conversion, empty string on any error
   */
  std::u32string utf8ToUtf32(const std::string& utf8StringSrc, bool failOnBadChar = true);
  /**
   * Convert UTF-8 string to UTF-32 string.
   * RTL logical-visual transformation is optionally performed.
   * Use it for readable text, GUI strings etc.
   * @param utf8StringSrc       is source UTF-8 string to convert
   * @param utf32StringDst      is output UTF-32 string, empty on any error
   * @param bVisualBiDiFlip     allow RTL visual-logical transformation if set to true, must be set
   *                            to false is logical-visual transformation is already done
   * @param forceLTRReadingOrder        force LTR reading order
   * @param failOnBadChar       if set to true function will fail on invalid character,
   *                            otherwise invalid character will be skipped
   * @return true on successful conversion, false on any error
   */
  bool utf8ToUtf32Visual(const std::string& utf8StringSrc, std::u32string& utf32StringDst, bool bVisualBiDiFlip = false, bool forceLTRReadingOrder = false, bool failOnBadChar = false);
  /**
   * Convert UTF-32 string to UTF-8 string.
   * No RTL visual-logical transformation is performed.
   * @param utf32StringSrc      is source UTF-32 string to convert
   * @param utf8StringDst       is output UTF-8 string, empty on any error
   * @param failOnBadChar       if set to true function will fail on invalid character,
   *                            otherwise invalid character will be skipped
   * @return true on successful conversion, false on any error
   */
  bool utf32ToUtf8(const std::u32string& utf32StringSrc, std::string& utf8StringDst, bool failOnBadChar = false);
  /**
   * Convert UTF-32 string to UTF-8 string.
   * No RTL visual-logical transformation is performed.
   * @param utf32StringSrc      is source UTF-32 string to convert
   * @param failOnBadChar       if set to true function will fail on invalid character,
   *                            otherwise invalid character will be skipped
   * @return converted string on successful conversion, empty string on any error
   */
  std::string utf32ToUtf8(const std::u32string& utf32StringSrc, bool failOnBadChar = false);
  /**
   * Convert UTF-32 string to wchar_t string (wstring).
   * No RTL visual-logical transformation is performed.
   * @param utf32StringSrc      is source UTF-32 string to convert
   * @param wStringDst          is output wchar_t string, empty on any error
   * @param failOnBadChar       if set to true function will fail on invalid character,
   *                            otherwise invalid character will be skipped
   * @return true on successful conversion, false on any error
   */
  bool utf32ToW(const std::u32string& utf32StringSrc, std::wstring& wStringDst, bool failOnBadChar = false);
  /**
   * Perform logical to visual flip.
   * @param logicalStringSrc    is source string with logical characters order
   * @param visualStringDst     is output string with visual characters order, empty on any error
   * @param forceLTRReadingOrder        force LTR reading order
   * @return true on success, false otherwise
   */
  bool utf32logicalToVisualBiDi(const std::u32string& logicalStringSrc, std::u32string& visualStringDst, bool forceLTRReadingOrder = false);
  /**
   * Strictly convert wchar_t string (wstring) to UTF-32 string.
   * No RTL visual-logical transformation is performed.
   * @param wStringSrc          is source wchar_t string to convert
   * @param utf32StringDst      is output UTF-32 string, empty on any error
   * @param failOnBadChar       if set to true function will fail on invalid character,
   *                            otherwise invalid character will be skipped
   * @return true on successful conversion, false on any error
   */
  bool wToUtf32(const std::wstring& wStringSrc, std::u32string& utf32StringDst, bool failOnBadChar = false);

  bool utf8ToW(const std::string& utf8StringSrc, std::wstring& wStringDst,
                bool bVisualBiDiFlip = true, bool forceLTRReadingOrder = false,
                bool failOnBadChar = false, bool* bWasFlipped = NULL);

  bool utf16LEtoW(const std::u16string& utf16String, std::wstring& wString);

  bool subtitleCharsetToW(const std::string& stringSrc, std::wstring& wStringDst);

  bool utf8ToStringCharset(const std::string& utf8StringSrc, std::string& stringDst);

  bool utf8ToStringCharset(std::string& stringSrcDst);
  bool utf8ToSystem(std::string& stringSrcDst, bool failOnBadChar = false);

  bool utf8To(const std::string& strDestCharset, const std::string& utf8StringSrc, std::string& stringDst);
  bool utf8To(const std::string& strDestCharset, const std::string& utf8StringSrc, std::u16string& utf16StringDst);
  bool utf8To(const std::string& strDestCharset, const std::string& utf8StringSrc, std::u32string& utf32StringDst);

  bool ToUtf8(const std::string& strSourceCharset, const std::string& stringSrc, std::string& utf8StringDst);

  bool isValidUtf8(const std::string& str);

  bool isValidUtf8(const char* buf, unsigned int len);

  bool wToUTF8(const std::wstring& wStringSrc, std::string& utf8StringDst, bool failOnBadChar = false);
  bool utf16BEtoUTF8(const std::u16string& utf16StringSrc, std::string& utf8StringDst);
  bool utf16LEtoUTF8(const std::u16string& utf16StringSrc, std::string& utf8StringDst);
  bool ucs2ToUTF8(const std::u16string& ucs2StringSrc, std::string& utf8StringDst);

  bool utf8logicalToVisualBiDi(const std::string& utf8StringSrc, std::string& utf8StringDst);

  bool utf32ToStringCharset(const std::u32string& utf32StringSrc, std::string& stringDst);

  std::vector<std::string> getCharsetLabels();
  std::string getCharsetLabelByName(const std::string& charsetName);
  std::string getCharsetNameByLabel(const std::string& charsetLabel);
  bool isBidiCharset(const std::string& charset);

  bool unknownToUTF8(std::string& stringSrcDst);
  bool unknownToUTF8(const std::string& stringSrc, std::string& utf8StringDst, bool failOnBadChar = false);

  bool toW(const std::string& stringSrc, std::wstring& wStringDst, const std::string& enc);
  bool fromW(const std::wstring& wStringSrc, std::string& stringDst, const std::string& enc);

  static void SettingOptionsCharsetsFiller(const CSetting* setting, std::vector< std::pair<std::string, std::string> >& list, std::string& current);
private:
  static const int m_Utf8CharMinSize, m_Utf8CharMaxSize;
};

XBMC_GLOBAL(CCharsetConverter,g_charsetConverter);

size_t iconv_const (void* cd, const char** inbuf, size_t* inbytesleft, char** outbuf, size_t* outbytesleft);

#endif
