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

'use strict'

/*!
 * Module dependencies
 */
const MagickCLI = require('../')
const fs = require('fs')

process.chdir(__dirname)

const source = 'js.png'
const outSync = 'jsSync.png'
const outAsync = 'jsAsync.png'
const cmdSync = `magick ${source} -resize 50% ${outSync}`
const cmdAsync = `magick ${source} -resize 50% ${outAsync}`

console.log('Start cleanup ...')
try {
  fs.unlinkSync(outSync)
  fs.unlinkSync(outAsync)
  console.log('Cleanup competed')
} catch (err) {
  console.log('Nothing to clean');
}

describe('Test magick-cli', function () {

    it('Should return the version of ImageMagick', function () {
        console.log(MagickCLI.version())
        expect(MagickCLI.version()).not.toBe(null)
        expect(MagickCLI.version()).toContain("7.");
    })

    it('Should execute ImageMagick command synchronous', function () {
        try {
            MagickCLI.executeSync(cmdSync)
        } catch (err) {
            // Handle err
            throw err
        }
    })

    it('Should execute ImageMagick command asynchronous', function (done) {
        MagickCLI.execute(cmdAsync)
        .then(() => {
            done()
        })
        .catch((err) => {
            console.log(err)
            done()
        })
    })

})