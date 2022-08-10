/**
NO TITLE
Copyright (C) 2020 ApiGear UG

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
#pragma once

#if defined _WIN32 || defined __CYGWIN__
#ifdef __GNUC__
  #define TEST_TESTBED1_EXPORT __attribute__ ((dllexport))
#else
  #define TEST_TESTBED1_EXPORT __declspec(dllexport)
#endif
#else
  #if __GNUC__ >= 4
    #define TEST_TESTBED1_EXPORT __attribute__ ((visibility ("default")))
  #else
    #define TEST_TESTBED1_EXPORT
  #endif
#endif