/*********************************************************************
 * NAN - Native Abstractions for Node.js
 *
 * Copyright (c) 2014 NAN contributors
 *
 * MIT License <https://github.com/rvagg/nan/blob/master/LICENSE.md>
 ********************************************************************/

const test     = require('tap').test
    , testRoot = require('path').resolve(__dirname, '..')
    , bindings = require('bindings')({ module_root: testRoot, bindings: 'asyncworkererror' });

test('asyncworkererror', function (t) {
  var worker = bindings.a
  t.type(worker, 'function')
  worker(function (err) {
    t.ok(err)
    t.equal(err.message, 'Error')
    t.end()
  })
})
