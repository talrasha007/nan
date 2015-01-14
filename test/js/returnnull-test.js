/*********************************************************************
 * NAN - Native Abstractions for Node.js
 *
 * Copyright (c) 2014 NAN contributors
 *
 * MIT License <https://github.com/rvagg/nan/blob/master/LICENSE.md>
 ********************************************************************/

const test     = require('tap').test
    , testRoot = require('path').resolve(__dirname, '..')
    , bindings = require('bindings')({ module_root: testRoot, bindings: 'returnnull' });

test('returnnull', function (t) {
  t.plan(3);
  t.type(bindings.r, 'function');
  t.equal(bindings.r('a string value'), null);
  t.equal(bindings.r(), null);
});
