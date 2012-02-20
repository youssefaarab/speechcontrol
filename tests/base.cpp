/**  This file is part of SpeechControl
 *
 *  Copyright (C) 2012 Jacky Alciné <jackyalcine@gmail.com>
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Library General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Library General Public License for more details.
 *
 *  You should have received a copy of the GNU Library General Public License
 *  along with this library; see the file COPYING.LIB.  If not, write to
 *  the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 *  Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_EXECINFO
#include <execinfo.h>
#endif

#include <cpptest-assert.h>

#include "base.hpp"

SpeechControl::TestModule::TestModule()
{
    TEST_ADD( TestModule::handleTest)
}

void SpeechControl::TestModule::handleTest()
{
    dumpBacktrace();
}

void SpeechControl::TestModule::dumpBacktrace()
{
#ifdef HAVE_EXECINFO
    TEST_THROWS_NOTHING_MSG(1,"Backtrace dumping support not implemented.")
#else
    TEST_THROWS_NOTHING_MSG(1,"Support for backtraces weren't enabled.")
#endif
}