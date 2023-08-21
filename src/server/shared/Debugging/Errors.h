/*
* This file is part of the Pandaria 5.4.8 Project. See THANKS file for Copyright information
*
* This program is free software; you can redistribute it and/or modify it
* under the terms of the GNU General Public License as published by the
* Free Software Foundation; either version 2 of the License, or (at your
* option) any later version.
*
* This program is distributed in the hope that it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
* more details.
*
* You should have received a copy of the GNU General Public License along
* with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef TRINITYCORE_ERRORS_H
#define TRINITYCORE_ERRORS_H

#include "Define.h"
#include <string>

namespace Trinity
{
    DECLSPEC_NORETURN void Assert(char const* file, int line, char const* function, std::string debugInfo, char const* message);
    DECLSPEC_NORETURN void Assert(char const* file, int line, char const* function, std::string debugInfo, char const* message, char const* format, ...) ATTR_PRINTF(6, 7);
    DECLSPEC_NORETURN void Fatal(char const* file, int line, char const* function, char const* message) ATTR_NORETURN;

    DECLSPEC_NORETURN void Error(char const* file, int line, char const* function, char const* message) ATTR_NORETURN;

    DECLSPEC_NORETURN void Abort(char const* file, int line, char const* function) ATTR_NORETURN;
    DECLSPEC_NORETURN void Abort(char const* file, int line, char const* function, char const* message, ...) ATTR_NORETURN;

    void Warning(char const* file, int line, char const* function, char const* message);

} // namespace Trinity

std::string GetDebugInfo();

#ifdef _WIN32
#define EXCEPTION_ASSERTION_FAILURE 0xC0000420L
#endif

#define WPAssert(cond, ...) do { if (!(cond)) Trinity::Assert(__FILE__, __LINE__, __FUNCTION__, GetDebugInfo(), #cond, ##__VA_ARGS__); } while(0) 
#define WPAssert_NODEBUGINFO(cond, ...) do { if (!(cond)) Trinity::Assert(__FILE__, __LINE__, __FUNCTION__, "", #cond, ##__VA_ARGS__); } while(0) 
#define WPFatal(cond, msg) do { if (!(cond)) Trinity::Fatal(__FILE__, __LINE__, __FUNCTION__, (msg)); } while (0)
#define WPError(cond, msg) do { if (!(cond)) Trinity::Error(__FILE__, __LINE__, __FUNCTION__, (msg)); } while (0)
#define WPWarning(cond, msg) do { if (!(cond)) Trinity::Warning(__FILE__, __LINE__, __FUNCTION__, (msg)); } while (0)
#define WPAbort() do { Trinity::Abort(__FILE__, __LINE__, __FUNCTION__); } while(0)

#define STR(x) #x
#define STR_(x) STR(x)
#define STR_LINE STR_(__LINE__)
#define DEBUG_STR(x) ("ASSERTION FAILED: " #x " at " __FILE__ ":" STR_LINE )

#ifdef _WIN32
__declspec(noreturn)
#endif

#define ASSERT WPAssert
#define ABORT WPAbort

void LogNotImplementedCall(char const* name);

#define CALL_NOT_IMPLEMENTED() LogNotImplementedCall(__FUNCTION__)

class Exception : public std::exception
{
public:
    Exception() { }
    Exception(std::string const& what) : _what(what) { }
    Exception(char const* what) : _what(what) { }
    Exception(Exception const& other) : _what(other._what) { }
    ~Exception() { }

    char const* what() const throw()
    {
        return _what.c_str();
    }

private:
    std::string _what;
};

#endif
