/*******************************************************************************
 * Copyright (c) 2017 Nicola Del Gobbo
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not
 * use this file except in compliance with the License. You may obtain a copy of
 * the license at http://www.apache.org/licenses/LICENSE-2.0
 *
 * THIS CODE IS PROVIDED ON AN *AS IS* BASIS, WITHOUT WARRANTIES OR CONDITIONS
 * OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION ANY
 * IMPLIED WARRANTIES OR CONDITIONS OF TITLE, FITNESS FOR A PARTICULAR PURPOSE,
 * MERCHANTABLITY OR NON-INFRINGEMENT.
 *
 * See the Apache Version 2.0 License for specific language governing
 * permissions and limitations under the License.
 *
 * Contributors - initial API implementation:
 * Nicola Del Gobbo <nicoladelgobbo@gmail.com>
 * Mauro Doganieri <mauro.doganieri@gmail.com>
 ******************************************************************************/

#ifndef MAGICK_CLI_H
#define MAGICK_CLI_H

#include <sstream>
#include <string>
#include <mutex>
#include <exception>


#include <node.h>                       
#include <v8.h>
#include <nan.h>

using namespace Nan;
using namespace v8;
using namespace std;

// MagickCore
#include <MagickCore/MagickCore.h>
#include <MagickCore/studio.h>
#include <MagickCore/exception.h>
#include <MagickCore/image.h>

// MagickWand
#include <MagickWand/MagickWand.h>
#include <MagickWand/magick-cli.h>

#endif //MAGICK_CLI_H