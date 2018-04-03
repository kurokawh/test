'use strict';

var Cat = require('./JavaScript1');

console.log('Hello world');



/* Catクラスのインスタンス作成 */
var cat1 = new Cat('タマ', '茶');
console.log(cat1.name); // タマ
cat1.walk(); // タマが歩いてます
// 忍び足です
cat1.mew();  // 茶色のタマがニャーと鳴いてます
// static func
//cat1.staticFunc(); // error: TypeError: cat1.staticFunc is not a function
//console.log(cat1.type()); // error: TypeError: cat1.type is not a function
Cat.staticFunc(); // OK: can call static func of Animal class.
console.log(Cat.type());

var cat2 = new Cat('コタロー', '黒');
console.log(cat2.name); // コタロー
cat2.walk(); // コタローが歩いてます
// 忍び足です
cat2.mew();  // 黒色のコタローがニャーと鳴いてます


class Lion extends Cat {
    constructor(name, color) {
        super('シンバ', 'ゴールド'); // Catクラスのconstructor呼び出し
    }
    run() {
///        super.walk(); // Catクラスのwalkメソッド呼び出し
        console.log('走る！');
    }

    static staticFunc2() {
        console.log('call statifFunc() from staticFunc2()');
        Cat.staticFunc();
    }
    static staticFunc() {
        console.log('Lion.staticFunc() is called');
    }
}

var lion1 = new Lion();
console.log(lion1.name);
lion1.run();
lion1.walk();
lion1.mew();
// static func
//console.log(lion1.staticFunc());  // error: TypeError: lion1.staticFunc is not a function
//console.log(lion1.type());        // error: TypeError
Lion.staticFunc2(); // OK: call Animal.staticFunc() from Lion.staticFunc()
Lion.staticFunc();  // OK: call Lion.staticFunc() not Animal.staticFunc().
console.log(Lion.type()); // OK: call Cat.type()
