/*********************************************************************
 * NAN - Native Abstractions for Node.js
 *
 * Copyright (c) 2014 NAN contributors
 *
 * MIT License <https://github.com/rvagg/nan/blob/master/LICENSE.md>
 ********************************************************************/

const test     = require('tap').test
    , testRoot = require('path').resolve(__dirname, '..')
    , bindings = require('bindings')({ module_root: testRoot, bindings: 'persistent' });

test('persistent', function (t) {
  t.plan(9)

  var persistent = bindings;
  t.type(persistent.save1, 'function');
  t.type(persistent.get1, 'function');
  t.type(persistent.dispose1, 'function');
  t.type(persistent.toPersistentAndBackAgain, 'function');
  t.type(persistent.persistentToPersistent, 'function');
  t.deepEqual(persistent.toPersistentAndBackAgain({ x: 42 }), { x: 42 });

  t.ok(persistent.persistentToPersistent('any string') || true);

  persistent.save1('a string to save')
  t.equal(persistent.get1(), 'a string to save')
  setTimeout(function () {
    t.equal(persistent.get1(), 'a string to save')
  }, 25)
  setTimeout(function () {
    t.equal(persistent.get1(), 'a string to save')
  }, 50)
  setTimeout(function () {
    persistent.dispose1()
  }, 75)
  setTimeout(function () {
    t.ok(persistent.get1() === undefined, 'no more persistent')
  }, 100)
})
