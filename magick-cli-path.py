#*******************************************************************************
# Copyright (c) 2017 Nicola Del Gobbo
# Licensed under the Apache License, Version 2.0 (the "License"); you may not
# use this file except in compliance with the License. You may obtain a copy of
# the license at http://www.apache.org/licenses/LICENSE-2.0
# 
# THIS CODE IS PROVIDED ON AN *AS IS* BASIS, WITHOUT WARRANTIES OR CONDITIONS
# OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION ANY
# IMPLIED WARRANTIES OR CONDITIONS OF TITLE, FITNESS FOR A PARTICULAR PURPOSE,
# MERCHANTABLITY OR NON-INFRINGEMENT.
# 
# See the Apache Version 2.0 License for specific language governing
# permissions and limitations under the License.
# 
# Contributors - initial API implementation:
# Nicola Del Gobbo <nicoladelgobbo@gmail.com>
# ******************************************************************************

import _winreg

def get_regvalue(regkey, regvalue):

    explorer = _winreg.OpenKey(
        _winreg.HKEY_LOCAL_MACHINE,
        regkey,
        0,
        _winreg.KEY_READ | _winreg.KEY_WOW64_64KEY
    )
    
    value, type = _winreg.QueryValueEx(explorer, regvalue)

    return value

print get_regvalue('SOFTWARE\\ImageMagick\\Current', 'LibPath')